/*
 *  drivers/cpufreq/cpufreq_ondemand.c
 *
 *  Copyright (C)  2001 Russell King
 *            (C)  2003 Venkatesh Pallipadi <venkatesh.pallipadi@intel.com>.
 *                      Jun Nakajima <jun.nakajima@intel.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/cpufreq.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/kernel_stat.h>
#include <linux/kobject.h>
#include <linux/module.h>
#include <linux/mutex.h>
#include <linux/percpu-defs.h>
#include <linux/slab.h>
#include <linux/sysfs.h>
#include <linux/tick.h>
#include <linux/types.h>
#include <linux/cpu.h>

#include "cpufreq_governor.h"

/* add this two head file for dvfs_hotplug */
#include <mstar/mpatch_macro.h>
#include <chip_dvfs_calibrating.h>

/* On-demand governor macros */
#define DEF_FREQUENCY_DOWN_DIFFERENTIAL		(10)
#define DEF_FREQUENCY_UP_THRESHOLD		(80)
#define DEF_SAMPLING_DOWN_FACTOR		(1)
#define MAX_SAMPLING_DOWN_FACTOR		(100000)
#define MICRO_FREQUENCY_DOWN_DIFFERENTIAL	(3)
#ifdef CONFIG_MP_DVFS_ONDEMAND_HIGH_PERFORMANCE
#define MICRO_FREQUENCY_UP_THRESHOLD		(80)
#else
#define MICRO_FREQUENCY_UP_THRESHOLD		(95)
#endif
#define MICRO_FREQUENCY_MIN_SAMPLE_RATE		(10000)
#define MIN_FREQUENCY_UP_THRESHOLD		(11)
#define MAX_FREQUENCY_UP_THRESHOLD		(100)

#ifdef CONFIG_MP_DVFS_ONDEMAND_HIGH_PERFORMANCE
#define DECREASE_CPUFREQ_COUNT	(6)
#endif

static DEFINE_PER_CPU(struct od_cpu_dbs_info_s, od_cpu_dbs_info);

static struct od_ops od_ops;
#ifdef CONFIG_MP_DVFS_FORCE_SET_TARGET_FREQ
unsigned int forcibly_set_target_flag = 0;
unsigned int over_thermal_flag = 0;
#endif
#if defined(CONFIG_MP_DVFS_CPUHOTPLUG_USE_ONLINE_CPU_MAX_LOAD) || defined(CONFIG_MP_DVFS_CPUHOTPLUG_USE_ONLINE_CPU_AVERAGE_LOAD)
extern struct mutex mstar_cpuload_lock;
extern unsigned int mstar_cpu_load_freq[CONFIG_NR_CPUS];
#endif
#ifdef CONFIG_MP_DVFS_CPUHOTPLUG
extern void update_mstar_cpu_dvfs_hotplug_workload_table(void);
extern struct mutex mstar_cpuload_threshold;
extern Cpu_Dvfs_Hotplug_Scenario mstar_cpu_dvfs_hotplug_scenario[CPU_DVFS_HOTPLUG_LEVEL_MAX];
extern Cpu_Dvfs_Hotplug_Total_Workload_Region mstar_cpu_dvfs_hotplug_workload_table[CPU_DVFS_HOTPLUG_LEVEL_MAX];
#endif

#ifndef CONFIG_CPU_FREQ_DEFAULT_GOV_ONDEMAND
static struct cpufreq_governor cpufreq_gov_ondemand;
#endif

static unsigned int default_powersave_bias;

static void ondemand_powersave_bias_init_cpu(int cpu)
{
	struct od_cpu_dbs_info_s *dbs_info = &per_cpu(od_cpu_dbs_info, cpu);

	dbs_info->freq_table = cpufreq_frequency_get_table(cpu);
	dbs_info->freq_lo = 0;
}

/*
 * Not all CPUs want IO time to be accounted as busy; this depends on how
 * efficient idling at a higher frequency/voltage is.
 * Pavel Machek says this is not so for various generations of AMD and old
 * Intel systems.
 * Mike Chan (android.com) claims this is also not true for ARM.
 * Because of this, whitelist specific known (series) of CPUs by default, and
 * leave all others up to the user.
 */
static int should_io_be_busy(void)
{
#if defined(CONFIG_X86)
	/*
	 * For Intel, Core 2 (model 15) and later have an efficient idle.
	 */
	if (boot_cpu_data.x86_vendor == X86_VENDOR_INTEL &&
			boot_cpu_data.x86 == 6 &&
			boot_cpu_data.x86_model >= 15)
		return 1;
#endif
	return 0;
}

/*
 * Find right freq to be set now with powersave_bias on.
 * Returns the freq_hi to be used right now and will set freq_hi_jiffies,
 * freq_lo, and freq_lo_jiffies in percpu area for averaging freqs.
 */
static unsigned int generic_powersave_bias_target(struct cpufreq_policy *policy,
		unsigned int freq_next, unsigned int relation)
{
	unsigned int freq_req, freq_reduc, freq_avg;
	unsigned int freq_hi, freq_lo;
	unsigned int index = 0;
	unsigned int jiffies_total, jiffies_hi, jiffies_lo;
	struct od_cpu_dbs_info_s *dbs_info = &per_cpu(od_cpu_dbs_info,
						   policy->cpu);
	struct dbs_data *dbs_data = policy->governor_data;
	struct od_dbs_tuners *od_tuners = dbs_data->tuners;

	if (!dbs_info->freq_table) {
		dbs_info->freq_lo = 0;
		dbs_info->freq_lo_jiffies = 0;
		return freq_next;
	}

	cpufreq_frequency_table_target(policy, dbs_info->freq_table, freq_next,
			relation, &index);
	freq_req = dbs_info->freq_table[index].frequency;
	freq_reduc = freq_req * od_tuners->powersave_bias / 1000;
	freq_avg = freq_req - freq_reduc;

	/* Find freq bounds for freq_avg in freq_table */
	index = 0;
	cpufreq_frequency_table_target(policy, dbs_info->freq_table, freq_avg,
			CPUFREQ_RELATION_H, &index);
	freq_lo = dbs_info->freq_table[index].frequency;
	index = 0;
	cpufreq_frequency_table_target(policy, dbs_info->freq_table, freq_avg,
			CPUFREQ_RELATION_L, &index);
	freq_hi = dbs_info->freq_table[index].frequency;

	/* Find out how long we have to be in hi and lo freqs */
	if (freq_hi == freq_lo) {
		dbs_info->freq_lo = 0;
		dbs_info->freq_lo_jiffies = 0;
		return freq_lo;
	}
	jiffies_total = usecs_to_jiffies(od_tuners->sampling_rate);
	jiffies_hi = (freq_avg - freq_lo) * jiffies_total;
	jiffies_hi += ((freq_hi - freq_lo) / 2);
	jiffies_hi /= (freq_hi - freq_lo);
	jiffies_lo = jiffies_total - jiffies_hi;
	dbs_info->freq_lo = freq_lo;
	dbs_info->freq_lo_jiffies = jiffies_lo;
	dbs_info->freq_hi_jiffies = jiffies_hi;
	return freq_hi;
}

static void ondemand_powersave_bias_init(void)
{
	int i;
	for_each_online_cpu(i) {
		ondemand_powersave_bias_init_cpu(i);
	}
}

static void dbs_freq_increase(struct cpufreq_policy *p, unsigned int freq)
{
	struct dbs_data *dbs_data = p->governor_data;
	struct od_dbs_tuners *od_tuners = dbs_data->tuners;

	if (od_tuners->powersave_bias)
		freq = od_ops.powersave_bias_target(p, freq,
				CPUFREQ_RELATION_H);
	else if (p->cur == p->max)
		return;

	__cpufreq_driver_target(p, freq, od_tuners->powersave_bias ?
			CPUFREQ_RELATION_L : CPUFREQ_RELATION_H);
}

#if defined(CONFIG_MP_DVFS_CPUHOTPLUG) || defined(CONFIG_MP_DVFS_CPUHOTPLUG_USE_ONLINE_CPU_MAX_LOAD)
#define CPU_HOTPLUG_MSG KERN_DEBUG
#endif

#ifdef CONFIG_MP_DVFS_CPUHOTPLUG
static int mstar_cpu_dvfs_hotplug_scenario_index = 0;
static void mstar_od_check_cpu(int cpu, unsigned int load_freq)	// the load_freq is cur_freq * cur_load (absolute cpu_load_freq)
{
	struct od_cpu_dbs_info_s *dbs_info = &per_cpu(od_cpu_dbs_info, cpu);
	struct cpufreq_policy *policy = dbs_info->cdbs.cur_policy;
	struct dbs_data *dbs_data = policy->governor_data;
	struct od_dbs_tuners *od_tuners = dbs_data->tuners;

	int level_index = -1;
	unsigned int freq_next = 0;
	unsigned int region_high, region_min;
	unsigned int total_cpu_nr = 0;
	int i = 0;
	unsigned int mstar_load_freq = 0;

	dbs_info->freq_lo = 0;
#if defined(CONFIG_MP_DVFS_CPUHOTPLUG_USE_ONLINE_CPU_MAX_LOAD) && defined(CONFIG_MP_DVFS_CPUHOTPLUG_USE_ONLINE_CPU_AVERAGE_LOAD)
#error "you can not define both CONFIG_MP_DVFS_CPUHOTPLUG_USE_ONLINE_CPU_MAX_LOAD and CONFIG_MP_DVFS_CPUHOTPLUG_USE_ONLINE_CPU_AVERAGE_LOAD"
#endif

/* step_1: decide mstar_load_freq(max_cpu_load_freq or cpu0_load_freq) */
#ifdef CONFIG_MP_DVFS_CPUHOTPLUG_USE_ONLINE_CPU_MAX_LOAD
	int j = 0;
	if(cpu == 0)	// use max_cpu_load_freq among all online cpus
	{
		mutex_lock(&mstar_cpuload_lock);
		for_each_online_cpu(i)
		{
			if(mstar_load_freq < mstar_cpu_load_freq[i])
			{
				j = i;
				mstar_load_freq = mstar_cpu_load_freq[i];
			}
			//printk(CPU_HOTPLUG_MSG "\033[35mFunction = %s, Line = %d, cpu_load_freq of cpu%d is %3u\033[m\n", __PRETTY_FUNCTION__, __LINE__, i, mstar_cpu_load_freq[i]);
		}
		mutex_unlock(&mstar_cpuload_lock);
		printk(CPU_HOTPLUG_MSG "\033[35m[Max Case] Function = %s, Line = %d, max_cpu_load_freq of cpu%d is %3u\033[m\n", __PRETTY_FUNCTION__, __LINE__, j, mstar_load_freq);
	}
	else
		return;
#elif defined(CONFIG_MP_DVFS_CPUHOTPLUG_USE_ONLINE_CPU_AVERAGE_LOAD)
	int cpu_cnt = 0;
	if(cpu == 0)	// use the average cpu_load_freq among all online cpus
	{
		mutex_lock(&mstar_cpuload_lock);
		for_each_online_cpu(i)
		{
			mstar_load_freq += mstar_cpu_load_freq[i];
			//printk(CPU_HOTPLUG_MSG "\033[35mFunction = %s, Line = %d, cpu_load_freq of cpu%d is %3u\033[m\n", __PRETTY_FUNCTION__, __LINE__, i, mstar_cpu_load_freq[i]);
			cpu_cnt++;
		}
		mutex_unlock(&mstar_cpuload_lock);
		mstar_load_freq /= cpu_cnt;
		printk(CPU_HOTPLUG_MSG "\033[35m[Average Case] Function = %s, Line = %d, average_cpu_load_freq among cpu_cnt(%d) is %3u\033[m\n", __PRETTY_FUNCTION__, __LINE__, cpu_cnt, mstar_load_freq);
	}
	else
		return;
#else
	mstar_load_freq = load_freq;	// use load_freq, which is the max load_freq of policy->cpus

	if(cpu == 0)
	{
		printk(CPU_HOTPLUG_MSG "\033[35m[CPU0 Case] Function = %s, Line = %d, [cpu%d] max_cpu_load_freq is %u\033[m\n", __PRETTY_FUNCTION__, __LINE__, cpu, mstar_load_freq);
		//printk(CPU_HOTPLUG_MSG "\033[35mFunction = %s, Line = %d, [cpu%d] cpu_load is %3u\033[m\n", __PRETTY_FUNCTION__, __LINE__, cpu, mstar_load_freq/policy->cur);
	}
	else
		return;
#endif
/* step_1: decide mstar_load_freq(max_cpu_load_freq or cpu0_load_freq) */


/* step_2: use mstar_load_freq to decide the next scenario */
	/* Check for frequency increase, change to max cpu_freq */
	if (mstar_load_freq > od_tuners->up_threshold * policy->cur)
	{
		level_index = CPU_DVFS_HOTPLUG_LEVEL_MAX - 1;

		if(cpu == 0) // policy->cpu == 0, but the sampling_work owner maybe not cpu0, it will be one of policy->cpus
		{
			printk(CPU_HOTPLUG_MSG "\033[31m[MAX_CASE] load:%3u, cur_freq:%7u, num_online_cpus:%d ==> level_index:%2d\033[m\n\n", (mstar_load_freq/policy->cur), policy->cur, num_online_cpus(), level_index);
			dbs_info->mstar_hotplug_rate_mult = mstar_cpu_dvfs_hotplug_scenario[level_index].sample_rate_mult;		// adjust the mstar_hotplug_rate_mult, which to change the sample_rate
			mstar_cpu_dvfs_hotplug_scenario_index = level_index;
		}

		/* according to the cpu_load to decide the cpu_nr and target_freq */
		total_cpu_nr = mstar_cpu_dvfs_hotplug_scenario[level_index].total_cpu_nr;
		freq_next = mstar_cpu_dvfs_hotplug_scenario[level_index].target_freq;

		/* combine total_cpu_nr with freq_next, the leftest 4 bits will be total_cpu_nr */
		freq_next = freq_next | (total_cpu_nr << 28);

		__cpufreq_driver_target(policy, freq_next, CPUFREQ_RELATION_L);

		if(cpu == 0) // policy->cpu == 0, but the sampling_work owner maybe not cpu0, it will be one of policy->cpus
		{
			mutex_lock(&mstar_cpuload_threshold);
			od_tuners->up_threshold = mstar_cpu_dvfs_hotplug_scenario[level_index].mstar_up_threshold;
			od_tuners->adj_up_threshold = mstar_cpu_dvfs_hotplug_scenario[level_index].mstar_adj_up_threshold;
			mutex_unlock(&mstar_cpuload_threshold);
		}
		return;
	}

	/*
	 * The optimal frequency is the frequency that is the lowest that can
	 * support the current CPU usage without triggering the up policy. To be
	 * safe, we focus 10 points under the threshold.
	 */
	if (mstar_load_freq < od_tuners->adj_up_threshold * policy->cur)
	{
		freq_next = mstar_load_freq * num_online_cpus();	// to get the total workload: cpu_nr * cpu_load * cpu_freq

		for(i = 0; i < CPU_DVFS_HOTPLUG_LEVEL_MAX; i++)
		{
			region_min = mstar_cpu_dvfs_hotplug_workload_table[i].supported_workload_lower_bound;
			region_high = mstar_cpu_dvfs_hotplug_workload_table[i].supported_workload_upper_bound;

			if( (region_min <= freq_next) && (freq_next < region_high) )
				break;
		}
		level_index = i;

		if(level_index >= CPU_DVFS_HOTPLUG_LEVEL_MAX)
		{
			printk(KERN_ERR "\033[31mFunction = %s, Line = %d, unknown mstar_load_freq %u\033[m\n", __PRETTY_FUNCTION__, __LINE__, mstar_load_freq);
			BUG_ON(1);
		}

		if(cpu == 0) // policy->cpu == 0, but the sampling_work owner maybe not cpu0, it will be one of policy->cpus
		{
			printk(CPU_HOTPLUG_MSG "\033[31m[NORMAL_CASE] load:%3u, cur_freq:%7u, num_online_cpus:%d ==> level_index:%2d\033[m\n\n", (mstar_load_freq/policy->cur), policy->cur, num_online_cpus(), level_index);
			dbs_info->mstar_hotplug_rate_mult = mstar_cpu_dvfs_hotplug_scenario[level_index].sample_rate_mult;		// adjust the mstar_hotplug_rate_mult, which to change the sample_rate
			mstar_cpu_dvfs_hotplug_scenario_index = level_index;
		}

		/* according to the cpu_load to decide the cpu_nr and target_freq */
		total_cpu_nr = mstar_cpu_dvfs_hotplug_scenario[level_index].total_cpu_nr;
		freq_next = mstar_cpu_dvfs_hotplug_scenario[level_index].target_freq;

		/* combine total_cpu_nr with freq_next, the leftest 4 bits will be total_cpu_nr */
		freq_next = freq_next | (total_cpu_nr << 28);

		__cpufreq_driver_target(policy, freq_next, CPUFREQ_RELATION_L);

		if(cpu == 0) // policy->cpu == 0, but the sampling_work owner maybe not cpu0, it will be one of policy->cpus
		{
			mutex_lock(&mstar_cpuload_threshold);
			od_tuners->up_threshold = mstar_cpu_dvfs_hotplug_scenario[level_index].mstar_up_threshold;
			od_tuners->adj_up_threshold = mstar_cpu_dvfs_hotplug_scenario[level_index].mstar_adj_up_threshold;
			mutex_unlock(&mstar_cpuload_threshold);
		}

		return;
	}
/* step_2: use mstar_load_freq to decide the next scenario */

	if(cpu == 0) // policy->cpu == 0, but the sampling_work owner maybe not cpu0, it will be one of policy->cpus
	{
		printk(CPU_HOTPLUG_MSG "\033[31m[NO_CHANGE_CASE] load:%3u, cur_freq:%7u, num_online_cpus:%d ==> mstar_cpu_dvfs_hotplug_scenario_index:%2d\033[m\n\n",
			(mstar_load_freq/policy->cur), policy->cur, num_online_cpus(), mstar_cpu_dvfs_hotplug_scenario_index);
	}
}
#else
/*
 * Every sampling_rate, we check, if current idle time is less than 20%
 * (default), then we try to increase frequency. Every sampling_rate, we look
 * for the lowest frequency which can sustain the load while keeping idle time
 * over 30%. If such a frequency exist, we try to decrease to this frequency.
 *
 * Any frequency increase takes it to the maximum frequency. Frequency reduction
 * happens at minimum steps of 5% (default) of current frequency
 */
static void od_check_cpu(int cpu, unsigned int load_freq)
{
	struct od_cpu_dbs_info_s *dbs_info = &per_cpu(od_cpu_dbs_info, cpu);
	struct cpufreq_policy *policy = dbs_info->cdbs.cur_policy;
	struct dbs_data *dbs_data = policy->governor_data;
	struct od_dbs_tuners *od_tuners = dbs_data->tuners;

#ifdef CONFIG_MP_DVFS_ONDEMAND_HIGH_PERFORMANCE
	static unsigned int cpufreq_cnt = DECREASE_CPUFREQ_COUNT;
#endif

#ifdef CONFIG_MP_DVFS_FLOW_DEBUG_MESSAGE
	if(cpu == 0)
		printk("{");
#endif

	dbs_info->freq_lo = 0;

#ifdef CONFIG_MP_DVFS_CPUHOTPLUG_USE_ONLINE_CPU_MAX_LOAD
	int i, j = 0;
	unsigned int mstar_load_freq = 0;
	if(cpu == 0)	// use max_cpu_load_freq among all online cpus
	{
		mutex_lock(&mstar_cpuload_lock);
		for_each_online_cpu(i)
		{
			if(mstar_load_freq < mstar_cpu_load_freq[i])
			{
				j = i;
				mstar_load_freq = mstar_cpu_load_freq[i];
			}
			//printk(CPU_HOTPLUG_MSG "\033[35mFunction = %s, Line = %d, cpu_load_freq of cpu%d is %3u\033[m\n", __PRETTY_FUNCTION__, __LINE__, i, mstar_cpu_load_freq[i]);
		}
		mutex_unlock(&mstar_cpuload_lock);
		printk(CPU_HOTPLUG_MSG "\033[35m[Max Case] Function = %s, Line = %d, max_cpu_load_freq of cpu%d is %3u\033[m\n", __PRETTY_FUNCTION__, __LINE__, j, mstar_load_freq);
	}
	else
		return;

	load_freq = mstar_load_freq;
#endif


	/* Check for frequency increase, change to max cpu_freq */
	if (load_freq > od_tuners->up_threshold * policy->cur) {
		/* If switching to max speed, apply sampling_down_factor
		 * Here means the sampling_delay time can be increase or decrease (delay = sampling_rate * rate_mult)
		 * the next sampling_delay can be changed by changing rate_mult
		 */
		if (policy->cur < policy->max)
		{
			dbs_info->rate_mult = od_tuners->sampling_down_factor;
		}
		dbs_freq_increase(policy, policy->max);
#ifdef CONFIG_MP_DVFS_FLOW_DEBUG_MESSAGE
		if(cpu == 0)
			printk("1}");
#endif
		return;
	}

	/* Check for frequency decrease */
	/* if we cannot reduce the frequency anymore, break out early,
	 * the exception case is that the setting of forcibly_set_target_flag or over_thermal_flag will cause the set_target_freq continue,
	 * this exception case usually occurs when T_Sensor callback checking gets a unusual result
	 */
	if ( (policy->cur == policy->min)
#ifdef CONFIG_MP_DVFS_FORCE_SET_TARGET_FREQ
&& (forcibly_set_target_flag == 0) && (over_thermal_flag == 0)
#endif
	)
	{
#ifdef CONFIG_MP_DVFS_FLOW_DEBUG_MESSAGE
		if(cpu == 0)
			printk("2}");
#endif
		return;
	}

	/*
	 * The optimal frequency is the frequency that is the lowest that can
	 * support the current CPU usage without triggering the up policy. To be
	 * safe, we focus 10 points under the threshold.
	 */
	if (load_freq < od_tuners->adj_up_threshold
			* policy->cur) {
		unsigned int freq_next;

#ifdef CONFIG_MP_DVFS_ONDEMAND_HIGH_PERFORMANCE
		 if(cpufreq_cnt++ <= DECREASE_CPUFREQ_COUNT)
     {
        return;
     }

		cpufreq_cnt = 0;

#endif

#ifdef CONFIG_MP_DVFS_ONDEMAND_HIGH_PERFORMANCE
    freq_next = load_freq / od_tuners->adj_up_threshold + policy->cpuinfo.min_freq;	/* lower freq */
#else
		freq_next = load_freq / od_tuners->adj_up_threshold;	/* lower freq */
#endif

		/* No longer fully busy, reset rate_mult */
		dbs_info->rate_mult = 1;

		if (freq_next < policy->min)
			freq_next = policy->min;

		if (!od_tuners->powersave_bias) {
			__cpufreq_driver_target(policy, freq_next,
					CPUFREQ_RELATION_L);
#ifdef CONFIG_MP_DVFS_FLOW_DEBUG_MESSAGE
			if(cpu == 0)
				printk("3}");
#endif
			return;
		}

		freq_next = od_ops.powersave_bias_target(policy, freq_next,
					CPUFREQ_RELATION_L);
		__cpufreq_driver_target(policy, freq_next, CPUFREQ_RELATION_L);
	}

#ifdef CONFIG_MP_DVFS_FLOW_DEBUG_MESSAGE
	if(cpu == 0)
		printk("4}");
#endif
}
#endif

static void od_dbs_timer(struct work_struct *work)
{
	struct od_cpu_dbs_info_s *dbs_info =
		container_of(work, struct od_cpu_dbs_info_s, cdbs.work.work);
	unsigned int cpu = dbs_info->cdbs.cur_policy->cpu;
	struct od_cpu_dbs_info_s *core_dbs_info = &per_cpu(od_cpu_dbs_info,
			cpu);
	struct dbs_data *dbs_data = dbs_info->cdbs.cur_policy->governor_data;
	struct od_dbs_tuners *od_tuners = dbs_data->tuners;
	int delay = 0, sample_type = core_dbs_info->sample_type;
	bool modify_all = true;

	mutex_lock(&core_dbs_info->cdbs.timer_mutex);
	if (!need_load_eval(&core_dbs_info->cdbs, od_tuners->sampling_rate)) {
		modify_all = false;
		goto max_delay;
	}

	/* Common NORMAL_SAMPLE setup */
	core_dbs_info->sample_type = OD_NORMAL_SAMPLE;
	if (sample_type == OD_SUB_SAMPLE) {
		delay = core_dbs_info->freq_lo_jiffies;
		__cpufreq_driver_target(core_dbs_info->cdbs.cur_policy,
				core_dbs_info->freq_lo, CPUFREQ_RELATION_H);
	} else {
		dbs_check_cpu(dbs_data, cpu);
		if (core_dbs_info->freq_lo) {
			/* Setup timer for SUB_SAMPLE */
			core_dbs_info->sample_type = OD_SUB_SAMPLE;
			delay = core_dbs_info->freq_hi_jiffies;
		}
	}

max_delay:
	if (!delay)
		delay = delay_for_sampling_rate(od_tuners->sampling_rate
				* core_dbs_info->rate_mult
#ifdef CONFIG_MP_DVFS_CPUHOTPLUG
				* core_dbs_info->mstar_hotplug_rate_mult
#endif
				);

	gov_queue_work(dbs_data, dbs_info->cdbs.cur_policy, delay, modify_all);
	mutex_unlock(&core_dbs_info->cdbs.timer_mutex);
}

/************************** sysfs interface ************************/
static struct common_dbs_data od_dbs_cdata;

/**
 * update_sampling_rate - update sampling rate effective immediately if needed.
 * @new_rate: new sampling rate
 *
 * If new rate is smaller than the old, simply updating
 * dbs_tuners_int.sampling_rate might not be appropriate. For example, if the
 * original sampling_rate was 1 second and the requested new sampling rate is 10
 * ms because the user needs immediate reaction from ondemand governor, but not
 * sure if higher frequency will be required or not, then, the governor may
 * change the sampling rate too late; up to 1 second later. Thus, if we are
 * reducing the sampling rate, we need to make the new value effective
 * immediately.
 */
static void update_sampling_rate(struct dbs_data *dbs_data,
		unsigned int new_rate)
{
	struct od_dbs_tuners *od_tuners = dbs_data->tuners;
	int cpu;

	od_tuners->sampling_rate = new_rate = max(new_rate,
			dbs_data->min_sampling_rate);

	for_each_online_cpu(cpu) {
		struct cpufreq_policy *policy;
		struct od_cpu_dbs_info_s *dbs_info;
		unsigned long next_sampling, appointed_at;

		policy = cpufreq_cpu_get(cpu);
		if (!policy)
			continue;
		if (policy->governor != &cpufreq_gov_ondemand) {
			cpufreq_cpu_put(policy);
			continue;
		}
		dbs_info = &per_cpu(od_cpu_dbs_info, cpu);
		cpufreq_cpu_put(policy);

		mutex_lock(&dbs_info->cdbs.timer_mutex);

		if (!delayed_work_pending(&dbs_info->cdbs.work)) {
			mutex_unlock(&dbs_info->cdbs.timer_mutex);
			continue;
		}

		next_sampling = jiffies + usecs_to_jiffies(new_rate);
		appointed_at = dbs_info->cdbs.work.timer.expires;

		if (time_before(next_sampling, appointed_at)) {

			mutex_unlock(&dbs_info->cdbs.timer_mutex);
			cancel_delayed_work_sync(&dbs_info->cdbs.work);
			mutex_lock(&dbs_info->cdbs.timer_mutex);

			gov_queue_work(dbs_data, dbs_info->cdbs.cur_policy,
					usecs_to_jiffies(new_rate), true);

		}
		mutex_unlock(&dbs_info->cdbs.timer_mutex);
	}
}

static ssize_t store_sampling_rate(struct dbs_data *dbs_data, const char *buf,
		size_t count)
{
	unsigned int input;
	int ret;
	ret = sscanf(buf, "%u", &input);
	if (ret != 1)
		return -EINVAL;

	update_sampling_rate(dbs_data, input);
	return count;
}

static ssize_t store_io_is_busy(struct dbs_data *dbs_data, const char *buf,
		size_t count)
{
	struct od_dbs_tuners *od_tuners = dbs_data->tuners;
	unsigned int input;
	int ret;
	unsigned int j;

	ret = sscanf(buf, "%u", &input);
	if (ret != 1)
		return -EINVAL;
	od_tuners->io_is_busy = !!input;

	/* we need to re-evaluate prev_cpu_idle */
	for_each_online_cpu(j) {
		struct od_cpu_dbs_info_s *dbs_info = &per_cpu(od_cpu_dbs_info,
									j);
		dbs_info->cdbs.prev_cpu_idle = get_cpu_idle_time(j,
			&dbs_info->cdbs.prev_cpu_wall, od_tuners->io_is_busy);
	}
	return count;
}

static ssize_t store_up_threshold(struct dbs_data *dbs_data, const char *buf,
		size_t count)
{
	struct od_dbs_tuners *od_tuners = dbs_data->tuners;
	unsigned int input;
	int ret;
#ifdef CONFIG_MP_DVFS_CPUHOTPLUG
	int i = 0;
#endif
	ret = sscanf(buf, "%u", &input);

	if (ret != 1 || input > MAX_FREQUENCY_UP_THRESHOLD ||
			input < MIN_FREQUENCY_UP_THRESHOLD) {
		return -EINVAL;
	}
	/* Calculate the new adj_up_threshold */
#ifdef CONFIG_MP_DVFS_CPUHOTPLUG
	mutex_lock(&mstar_cpuload_threshold);
	od_tuners->adj_up_threshold += input;
	od_tuners->adj_up_threshold -= od_tuners->up_threshold;

	od_tuners->up_threshold = input;

	for(i = 0; i < CPU_DVFS_HOTPLUG_LEVEL_MAX; i++)
	{
		mstar_cpu_dvfs_hotplug_scenario[i].mstar_up_threshold = od_tuners->up_threshold;
		mstar_cpu_dvfs_hotplug_scenario[i].mstar_adj_up_threshold = od_tuners->adj_up_threshold;
	}
	printk("\033[31mFunction = %s, Line = %d, set get_mstar_up_threshold: %d\033[m\n", __PRETTY_FUNCTION__, __LINE__, od_tuners->up_threshold);
	printk("\033[31mFunction = %s, Line = %d, set get_mstar_adj_up_threshold: %d\033[m\n", __PRETTY_FUNCTION__, __LINE__, od_tuners->adj_up_threshold);

	mutex_unlock(&mstar_cpuload_threshold);

	update_mstar_cpu_dvfs_hotplug_workload_table();
#else
	od_tuners->adj_up_threshold += input;
	od_tuners->adj_up_threshold -= od_tuners->up_threshold;

	od_tuners->up_threshold = input;
#endif
	return count;
}

static ssize_t store_sampling_down_factor(struct dbs_data *dbs_data,
		const char *buf, size_t count)
{
	struct od_dbs_tuners *od_tuners = dbs_data->tuners;
	unsigned int input, j;
	int ret;
	ret = sscanf(buf, "%u", &input);

	if (ret != 1 || input > MAX_SAMPLING_DOWN_FACTOR || input < 1)
		return -EINVAL;
	od_tuners->sampling_down_factor = input;

	/* Reset down sampling multiplier in case it was active */
	for_each_online_cpu(j) {
		struct od_cpu_dbs_info_s *dbs_info = &per_cpu(od_cpu_dbs_info,
				j);
		dbs_info->rate_mult = 1;
	}
	return count;
}

static ssize_t store_ignore_nice_load(struct dbs_data *dbs_data,
		const char *buf, size_t count)
{
	struct od_dbs_tuners *od_tuners = dbs_data->tuners;
	unsigned int input;
	int ret;

	unsigned int j;

	ret = sscanf(buf, "%u", &input);
	if (ret != 1)
		return -EINVAL;

	if (input > 1)
		input = 1;

	if (input == od_tuners->ignore_nice_load) { /* nothing to do */
		return count;
	}
	od_tuners->ignore_nice_load = input;

	/* we need to re-evaluate prev_cpu_idle */
	for_each_online_cpu(j) {
		struct od_cpu_dbs_info_s *dbs_info;
		dbs_info = &per_cpu(od_cpu_dbs_info, j);
		dbs_info->cdbs.prev_cpu_idle = get_cpu_idle_time(j,
			&dbs_info->cdbs.prev_cpu_wall, od_tuners->io_is_busy);
		if (od_tuners->ignore_nice_load)
			dbs_info->cdbs.prev_cpu_nice =
				kcpustat_cpu(j).cpustat[CPUTIME_NICE];

	}
	return count;
}

static ssize_t store_powersave_bias(struct dbs_data *dbs_data, const char *buf,
		size_t count)
{
	struct od_dbs_tuners *od_tuners = dbs_data->tuners;
	unsigned int input;
	int ret;
	ret = sscanf(buf, "%u", &input);

	if (ret != 1)
		return -EINVAL;

	if (input > 1000)
		input = 1000;

	od_tuners->powersave_bias = input;
	ondemand_powersave_bias_init();
	return count;
}

show_store_one(od, sampling_rate);
show_store_one(od, io_is_busy);
show_store_one(od, up_threshold);
show_store_one(od, sampling_down_factor);
show_store_one(od, ignore_nice_load);
show_store_one(od, powersave_bias);
declare_show_sampling_rate_min(od);

gov_sys_pol_attr_rw(sampling_rate);
gov_sys_pol_attr_rw(io_is_busy);
gov_sys_pol_attr_rw(up_threshold);
gov_sys_pol_attr_rw(sampling_down_factor);
gov_sys_pol_attr_rw(ignore_nice_load);
gov_sys_pol_attr_rw(powersave_bias);
gov_sys_pol_attr_ro(sampling_rate_min);

static struct attribute *dbs_attributes_gov_sys[] = {
	&sampling_rate_min_gov_sys.attr,
	&sampling_rate_gov_sys.attr,
	&up_threshold_gov_sys.attr,
	&sampling_down_factor_gov_sys.attr,
	&ignore_nice_load_gov_sys.attr,
	&powersave_bias_gov_sys.attr,
	&io_is_busy_gov_sys.attr,
	NULL
};

static struct attribute_group od_attr_group_gov_sys = {
	.attrs = dbs_attributes_gov_sys,
	.name = "ondemand",
};

static struct attribute *dbs_attributes_gov_pol[] = {
	&sampling_rate_min_gov_pol.attr,
	&sampling_rate_gov_pol.attr,
	&up_threshold_gov_pol.attr,
	&sampling_down_factor_gov_pol.attr,
	&ignore_nice_load_gov_pol.attr,
	&powersave_bias_gov_pol.attr,
	&io_is_busy_gov_pol.attr,
	NULL
};

static struct attribute_group od_attr_group_gov_pol = {
	.attrs = dbs_attributes_gov_pol,
	.name = "ondemand",
};

/************************** sysfs end ************************/

static int od_init(struct dbs_data *dbs_data)
{
	struct od_dbs_tuners *tuners;
	u64 idle_time;
	int cpu;
#ifdef CONFIG_MP_DVFS_CPUHOTPLUG
	int i = 0;
#endif

	tuners = kzalloc(sizeof(struct od_dbs_tuners), GFP_KERNEL);
	if (!tuners) {
		pr_err("%s: kzalloc failed\n", __func__);
		return -ENOMEM;
	}

	cpu = get_cpu();
	idle_time = get_cpu_idle_time_us(cpu, NULL);
	put_cpu();
	if (idle_time != -1ULL) {
		/* Idle micro accounting is supported. Use finer thresholds */
		tuners->up_threshold = MICRO_FREQUENCY_UP_THRESHOLD;
		tuners->adj_up_threshold = MICRO_FREQUENCY_UP_THRESHOLD -
			MICRO_FREQUENCY_DOWN_DIFFERENTIAL;
		/*
		 * In nohz/micro accounting case we set the minimum frequency
		 * not depending on HZ, but fixed (very low). The deferred
		 * timer might skip some samples if idle/sleeping as needed.
		*/
		dbs_data->min_sampling_rate = MICRO_FREQUENCY_MIN_SAMPLE_RATE;
	} else {
		tuners->up_threshold = DEF_FREQUENCY_UP_THRESHOLD;
		tuners->adj_up_threshold = DEF_FREQUENCY_UP_THRESHOLD -
			DEF_FREQUENCY_DOWN_DIFFERENTIAL;

		/* For correct statistics, we need 10 ticks for each measure */
		dbs_data->min_sampling_rate = MIN_SAMPLING_RATE_RATIO *
			jiffies_to_usecs(10);
	}

#ifdef CONFIG_MP_DVFS_CPUHOTPLUG
	mutex_lock(&mstar_cpuload_threshold);

	for(i = 0; i < CPU_DVFS_HOTPLUG_LEVEL_MAX; i++)
	{
		mstar_cpu_dvfs_hotplug_scenario[i].mstar_up_threshold = tuners->up_threshold;
		mstar_cpu_dvfs_hotplug_scenario[i].mstar_adj_up_threshold = tuners->adj_up_threshold;
	}
	printk("\033[31mFunction = %s, Line = %d, set get_mstar_up_threshold: %d\033[m\n", __PRETTY_FUNCTION__, __LINE__, tuners->up_threshold);
	printk("\033[31mFunction = %s, Line = %d, set get_mstar_adj_up_threshold: %d\033[m\n", __PRETTY_FUNCTION__, __LINE__, tuners->adj_up_threshold);

	mutex_unlock(&mstar_cpuload_threshold);

	update_mstar_cpu_dvfs_hotplug_workload_table();
#endif

	tuners->sampling_down_factor = DEF_SAMPLING_DOWN_FACTOR;
	tuners->ignore_nice_load = 0;
	tuners->powersave_bias = default_powersave_bias;
	tuners->io_is_busy = should_io_be_busy();

	dbs_data->tuners = tuners;
	mutex_init(&dbs_data->mutex);
	return 0;
}

static void od_exit(struct dbs_data *dbs_data)
{
	kfree(dbs_data->tuners);
}

define_get_cpu_dbs_routines(od_cpu_dbs_info);

static struct od_ops od_ops = {
	.powersave_bias_init_cpu = ondemand_powersave_bias_init_cpu,
	.powersave_bias_target = generic_powersave_bias_target,
	.freq_increase = dbs_freq_increase,
};

static struct common_dbs_data od_dbs_cdata = {
	.governor = GOV_ONDEMAND,
	.attr_group_gov_sys = &od_attr_group_gov_sys,
	.attr_group_gov_pol = &od_attr_group_gov_pol,
	.get_cpu_cdbs = get_cpu_cdbs,
	.get_cpu_dbs_info_s = get_cpu_dbs_info_s,
	.gov_dbs_timer = od_dbs_timer,
#ifdef CONFIG_MP_DVFS_CPUHOTPLUG
	.gov_check_cpu = mstar_od_check_cpu,
#else
	.gov_check_cpu = od_check_cpu,
#endif
	.gov_ops = &od_ops,
	.init = od_init,
	.exit = od_exit,
};

static void od_set_powersave_bias(unsigned int powersave_bias)
{
	struct cpufreq_policy *policy;
	struct dbs_data *dbs_data;
	struct od_dbs_tuners *od_tuners;
	unsigned int cpu;
	cpumask_t done;

	default_powersave_bias = powersave_bias;
	cpumask_clear(&done);

	get_online_cpus();
	for_each_online_cpu(cpu) {
		if (cpumask_test_cpu(cpu, &done))
			continue;

		policy = per_cpu(od_cpu_dbs_info, cpu).cdbs.cur_policy;
		if (!policy)
			continue;

		cpumask_or(&done, &done, policy->cpus);

		if (policy->governor != &cpufreq_gov_ondemand)
			continue;

		dbs_data = policy->governor_data;
		od_tuners = dbs_data->tuners;
		od_tuners->powersave_bias = default_powersave_bias;
	}
	put_online_cpus();
}

void od_register_powersave_bias_handler(unsigned int (*f)
		(struct cpufreq_policy *, unsigned int, unsigned int),
		unsigned int powersave_bias)
{
	od_ops.powersave_bias_target = f;
	od_set_powersave_bias(powersave_bias);
}
EXPORT_SYMBOL_GPL(od_register_powersave_bias_handler);

void od_unregister_powersave_bias_handler(void)
{
	od_ops.powersave_bias_target = generic_powersave_bias_target;
	od_set_powersave_bias(0);
}
EXPORT_SYMBOL_GPL(od_unregister_powersave_bias_handler);

static int od_cpufreq_governor_dbs(struct cpufreq_policy *policy,
		unsigned int event)
{
	return cpufreq_governor_dbs(policy, &od_dbs_cdata, event);
}

#ifndef CONFIG_CPU_FREQ_DEFAULT_GOV_ONDEMAND
static
#endif
struct cpufreq_governor cpufreq_gov_ondemand = {
	.name			= "ondemand",
	.governor		= od_cpufreq_governor_dbs,
	.max_transition_latency	= TRANSITION_LATENCY_LIMIT,
	.owner			= THIS_MODULE,
};

static int __init cpufreq_gov_dbs_init(void)
{
	return cpufreq_register_governor(&cpufreq_gov_ondemand);
}

static void __exit cpufreq_gov_dbs_exit(void)
{
	cpufreq_unregister_governor(&cpufreq_gov_ondemand);
}

MODULE_AUTHOR("Venkatesh Pallipadi <venkatesh.pallipadi@intel.com>");
MODULE_AUTHOR("Alexey Starikovskiy <alexey.y.starikovskiy@intel.com>");
MODULE_DESCRIPTION("'cpufreq_ondemand' - A dynamic cpufreq governor for "
	"Low Latency Frequency Transition capable processors");
MODULE_LICENSE("GPL");

#ifdef CONFIG_CPU_FREQ_DEFAULT_GOV_ONDEMAND
fs_initcall(cpufreq_gov_dbs_init);
#else
module_init(cpufreq_gov_dbs_init);
#endif
module_exit(cpufreq_gov_dbs_exit);
