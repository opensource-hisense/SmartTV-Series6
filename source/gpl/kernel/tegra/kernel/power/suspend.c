/*
 * kernel/power/suspend.c - Suspend to RAM and standby functionality.
 *
 * Copyright (c) 2003 Patrick Mochel
 * Copyright (c) 2003 Open Source Development Lab
 * Copyright (c) 2009 Rafael J. Wysocki <rjw@sisk.pl>, Novell Inc.
 *
 * This file is released under the GPLv2.
 */

#include <linux/string.h>
#include <linux/delay.h>
#include <linux/errno.h>
#include <linux/init.h>
#include <linux/console.h>
#include <linux/cpu.h>
#include <linux/syscalls.h>
#include <linux/gfp.h>
#include <linux/io.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/export.h>
#include <linux/suspend.h>
#include <linux/syscore_ops.h>
#include <linux/ftrace.h>
#include <linux/rtc.h>
#include <trace/events/power.h>

#include "power.h"
#include <mstar/mpatch_macro.h>
#if defined(CONFIG_MSTAR_PM)
#include <mdrv_pm.h>
#endif

#ifdef CONFIG_MP_CMA_PATCH_MBOOT_STR_USE_CMA
#include <mdrv_cma_pool.h>
#endif

#ifdef CONFIG_MSTAR_IPAPOOL
#include <mdrv_ipa_pool.h>
#endif
#ifdef CONFIG_MP_R2_STR_ENABLE
#include "../../drivers/mstar2/include/mdrv_types.h"
#include "../../drivers/mstar2/include/mdrv_mstypes.h"
#include "../../drivers/mstar2/drv/mbx/mdrv_mbx.h"
#include "../../drivers/mstar2/drv/mbx/mapi_mbx.h"
extern unsigned long get_str_handshake_addr();
#endif
#ifdef CONFIG_CPU_FREQ_DEFAULT_GOV_ONDEMAND
#ifdef CONFIG_MSTAR_CPU_calibrating
extern atomic_t ac_str_cpufreq;
extern atomic_t disable_dvfs;
extern int __CPU_calibrating_proc_write(const unsigned long idx);
extern void change_cpus_timer(char *caller, unsigned int target_freq);
extern struct mutex mstar_cpufreq_lock;
#endif
#endif

const char *const pm_states[PM_SUSPEND_MAX] = {
	[PM_SUSPEND_FREEZE]	= "freeze",
	[PM_SUSPEND_STANDBY]	= "standby",
	[PM_SUSPEND_MEM]	= "mem",
};

#if (MP_USB_STR_PATCH==1)
typedef enum
{
    E_STR_NONE,
    E_STR_IN_SUSPEND,
    E_STR_IN_RESUME
}EN_STR_STATUS;

static EN_STR_STATUS enStrStatus=E_STR_NONE;

bool is_suspending(void)
{
    return (enStrStatus == E_STR_IN_SUSPEND);
}
EXPORT_SYMBOL_GPL(is_suspending);
#endif

static const struct platform_suspend_ops *suspend_ops;

static bool need_suspend_ops(suspend_state_t state)
{
	return !!(state > PM_SUSPEND_FREEZE);
}

static DECLARE_WAIT_QUEUE_HEAD(suspend_freeze_wait_head);
static bool suspend_freeze_wake;

static void freeze_begin(void)
{
	suspend_freeze_wake = false;
}

static void freeze_enter(void)
{
	wait_event(suspend_freeze_wait_head, suspend_freeze_wake);
}

void freeze_wake(void)
{
	suspend_freeze_wake = true;
	wake_up(&suspend_freeze_wait_head);
}
EXPORT_SYMBOL_GPL(freeze_wake);

/**
 * suspend_set_ops - Set the global suspend method table.
 * @ops: Suspend operations to use.
 */
void suspend_set_ops(const struct platform_suspend_ops *ops)
{
	lock_system_sleep();
	suspend_ops = ops;
	unlock_system_sleep();
}
EXPORT_SYMBOL_GPL(suspend_set_ops);

bool valid_state(suspend_state_t state)
{
	if (state == PM_SUSPEND_FREEZE) {
#ifdef CONFIG_PM_DEBUG
		if (pm_test_level != TEST_NONE &&
		    pm_test_level != TEST_FREEZER &&
		    pm_test_level != TEST_DEVICES &&
		    pm_test_level != TEST_PLATFORM) {
			printk(KERN_WARNING "Unsupported pm_test mode for "
					"freeze state, please choose "
					"none/freezer/devices/platform.\n");
			return false;
		}
#endif
			return true;
	}
	/*
	 * PM_SUSPEND_STANDBY and PM_SUSPEND_MEMORY states need lowlevel
	 * support and need to be valid to the lowlevel
	 * implementation, no valid callback implies that none are valid.
	 */
	return suspend_ops && suspend_ops->valid && suspend_ops->valid(state);
}

/**
 * suspend_valid_only_mem - Generic memory-only valid callback.
 *
 * Platform drivers that implement mem suspend only and only need to check for
 * that in their .valid() callback can use this instead of rolling their own
 * .valid() callback.
 */
int suspend_valid_only_mem(suspend_state_t state)
{
	return state == PM_SUSPEND_MEM;
}
EXPORT_SYMBOL_GPL(suspend_valid_only_mem);

static int suspend_test(int level)
{
#ifdef CONFIG_PM_DEBUG
	if (pm_test_level == level) {
		printk(KERN_INFO "suspend debug: Waiting for 5 seconds.\n");
		mdelay(5000);
		return 1;
	}
#endif /* !CONFIG_PM_DEBUG */
	return 0;
}

/**
 * suspend_prepare - Prepare for entering system sleep state.
 *
 * Common code run for every system sleep state that can be entered (except for
 * hibernation).  Run suspend notifiers, allocate the "suspend" console and
 * freeze processes.
 */
static int suspend_prepare(suspend_state_t state)
{
	int error;

	if (need_suspend_ops(state) && (!suspend_ops || !suspend_ops->enter))
		return -EPERM;

	pm_prepare_console();

	error = pm_notifier_call_chain(PM_SUSPEND_PREPARE);
	if (error)
		goto Finish;

#ifdef CONFIG_CPU_FREQ_DEFAULT_GOV_ONDEMAND
#ifdef CONFIG_MSTAR_CPU_calibrating
	/* Disable DVFS before suspend */
	mutex_lock(&mstar_cpufreq_lock);
    atomic_set(&disable_dvfs, 1);
    printk("\033[0;32;31m%s %d Disable DVFS in STR\033[m\n",__func__,__LINE__);
	mutex_unlock(&mstar_cpufreq_lock);
	
	/* Reset cpufreq and voltage to default setting */
    printk("\033[36mFunction = %s, Line = %d,  setting cpufreq to %d\033[m\n", __PRETTY_FUNCTION__, __LINE__, atomic_read(&ac_str_cpufreq)); // joe.liu
    change_cpus_timer((char *)__FUNCTION__, atomic_read(&ac_str_cpufreq));
    mdelay(100);
#endif
#endif

	error = suspend_freeze_processes();

#ifdef CONFIG_MP_CMA_PATCH_MBOOT_STR_USE_CMA
	/* allocate all freed cma_memory from a mboot co-buffer cma_region, 
	 * to prevent the kernel data is still @ the mboot co-buffer cma_region,
	 * and thus, the kernel data will be corrupted by mboot
	 */

#ifdef CONFIG_MSTAR_CMAPOOL
	str_reserve_mboot_cma_buffer();
#else

#ifdef CONFIG_MSTAR_IPAPOOL
	str_reserve_mboot_ipa_str_pool_buffer();
#endif

#endif

#endif

	if (!error)
		return 0;

	suspend_stats.failed_freeze++;
	dpm_save_failed_step(SUSPEND_FREEZE);
 Finish:
	pm_notifier_call_chain(PM_POST_SUSPEND);

#ifdef CONFIG_CPU_FREQ_DEFAULT_GOV_ONDEMAND
#ifdef CONFIG_MSTAR_CPU_calibrating
	/* Enable DVFS after resume, this is error case */
	mutex_lock(&mstar_cpufreq_lock);
    atomic_set(&disable_dvfs, 0);
    printk("\033[0;32;31m%s %d Enable DVFS in STR (Error case)\033[m\n",__func__,__LINE__);
	mutex_unlock(&mstar_cpufreq_lock);
#endif
#endif

	pm_restore_console();
	return error;
}

/* default implementation */
void __attribute__ ((weak)) arch_suspend_disable_irqs(void)
{
	local_irq_disable();
}

/* default implementation */
void __attribute__ ((weak)) arch_suspend_enable_irqs(void)
{
	local_irq_enable();
}

/**
 * suspend_enter - Make the system enter the given sleep state.
 * @state: System sleep state to enter.
 * @wakeup: Returns information that the sleep state should not be re-entered.
 *
 * This function should be called after devices have been suspended.
 */
static int suspend_enter(suspend_state_t state, bool *wakeup)
{
	int error;

	if (need_suspend_ops(state) && suspend_ops->prepare) {
		error = suspend_ops->prepare();
		if (error)
			goto Platform_finish;
	}

	error = dpm_suspend_end(PMSG_SUSPEND);
	if (error) {
		printk(KERN_ERR "PM: Some devices failed to power down\n");
		goto Platform_finish;
	}

	if (need_suspend_ops(state) && suspend_ops->prepare_late) {
		error = suspend_ops->prepare_late();
		if (error)
			goto Platform_wake;
	}

	if (suspend_test(TEST_PLATFORM))
		goto Platform_wake;

	/*
	 * PM_SUSPEND_FREEZE equals
	 * frozen processes + suspended devices + idle processors.
	 * Thus we should invoke freeze_enter() soon after
	 * all the devices are suspended.
	 */
	if (state == PM_SUSPEND_FREEZE) {
		freeze_enter();
		goto Platform_wake;
	}

	error = disable_nonboot_cpus();
	if (error || suspend_test(TEST_CPUS))
		goto Enable_cpus;

	arch_suspend_disable_irqs();
	BUG_ON(!irqs_disabled());

	error = syscore_suspend();
	if (!error) {
#if defined(CONFIG_MP_MSTAR_STR_BASE)
        if(is_mstar_str()){
            *wakeup = false;
        }else
#endif
		*wakeup = pm_wakeup_pending();
		if (!(suspend_test(TEST_CORE) || *wakeup)) {
			printk(KERN_DEBUG "\033[35mFunction = %s, Line = %d, do mstar_pm_enter\033[m\n", __PRETTY_FUNCTION__, __LINE__); // joe.liu
			error = suspend_ops->enter(state);
			printk(KERN_DEBUG "\033[35mFunction = %s, Line = %d, leave mstar_pm_enter\033[m\n", __PRETTY_FUNCTION__, __LINE__); // joe.liu
			events_check_enabled = false;
#if defined(CONFIG_MP_MSTAR_STR_BASE)
            set_state_value(STENT_RESUME_FROM_SUSPEND);
#endif
		}
#if (MP_USB_STR_PATCH==1)
		enStrStatus=E_STR_IN_RESUME;
#endif
		syscore_resume();
	}

	arch_suspend_enable_irqs();
	BUG_ON(irqs_disabled());

 Enable_cpus:
	enable_nonboot_cpus(); //leo test

 Platform_wake:
	if (need_suspend_ops(state) && suspend_ops->wake)
		suspend_ops->wake();

	dpm_resume_start(PMSG_RESUME);

 Platform_finish:
	if (need_suspend_ops(state) && suspend_ops->finish)
		suspend_ops->finish();

	return error;
}

/**
 * suspend_devices_and_enter - Suspend devices and enter system sleep state.
 * @state: System sleep state to enter.
 */
int suspend_devices_and_enter(suspend_state_t state)
{
	int error;
	bool wakeup = false;

	if (need_suspend_ops(state) && !suspend_ops)
		return -ENOSYS;

	trace_machine_suspend(state);
	if (need_suspend_ops(state) && suspend_ops->begin) {
		error = suspend_ops->begin(state);
		if (error)
			goto Close;
	}
	suspend_console();
	ftrace_stop();
	suspend_test_start();
	error = dpm_suspend_start(PMSG_SUSPEND);
	if (error) {
		printk(KERN_ERR "PM: Some devices failed to suspend\n");
		goto Recover_platform;
	}
	suspend_test_finish("suspend devices");
	if (suspend_test(TEST_DEVICES))
		goto Recover_platform;

	do {
		error = suspend_enter(state, &wakeup);
	} while (!error && !wakeup && need_suspend_ops(state)
		&& suspend_ops->suspend_again && suspend_ops->suspend_again());

 Resume_devices:
	suspend_test_start();
	dpm_resume_end(PMSG_RESUME);
	suspend_test_finish("resume devices");
	ftrace_start();
	resume_console();
 Close:
	if (need_suspend_ops(state) && suspend_ops->end)
		suspend_ops->end();
	trace_machine_suspend(PWR_EVENT_EXIT);
	return error;

 Recover_platform:
	if (need_suspend_ops(state) && suspend_ops->recover)
		suspend_ops->recover();
	goto Resume_devices;
}

/**
 * suspend_finish - Clean up before finishing the suspend sequence.
 *
 * Call platform code to clean up, restart processes, and free the console that
 * we've allocated. This routine is not called for hibernation.
 */
static void suspend_finish(void)
{
#ifdef CONFIG_CPU_FREQ_DEFAULT_GOV_ONDEMAND
#ifdef CONFIG_MSTAR_CPU_calibrating
	/* Enable DVFS after resume, add this before suspend_thaw_processes, before user_mode processes wake_up */
	mutex_lock(&mstar_cpufreq_lock);
	atomic_set(&disable_dvfs, 0);
	printk("\033[0;32;31m%s %d Enable DVFS in STR\033[m\n",__func__,__LINE__);
	mutex_unlock(&mstar_cpufreq_lock);
#endif
#endif

#ifdef CONFIG_MP_CMA_PATCH_MBOOT_STR_USE_CMA
	/* free all pre-allocated cma_memory from a mboot co-buffer cma_region */

#ifdef CONFIG_MSTAR_CMAPOOL
	str_release_mboot_cma_buffer();
#else

#ifdef CONFIG_MSTAR_IPAPOOL
	str_release_mboot_ipa_str_pool_buffer();
#endif

#endif

#endif

	suspend_thaw_processes();
	pm_notifier_call_chain(PM_POST_SUSPEND);
	pm_restore_console();
}

#ifdef CONFIG_MP_R2_STR_ENABLE
u32 kernel_read_phys(u64 phys_addr)
{
    u32 phys_addr_page = phys_addr & 0xFFFFE000;
    u32 phys_offset    = phys_addr & 0x00001FFF;
    u32 map_size       = phys_offset + sizeof(u32);
    u32 ret = 0xDEADBEEF;
    void *mem_mapped = ioremap_nocache(phys_addr_page, map_size);
    if (NULL != mem_mapped) {
        ret = (u32)ioread32(((u8*)mem_mapped) + phys_offset);
        iounmap(mem_mapped);
    }

    return ret;
}
#endif

/**
 * enter_state - Do common work needed to enter system sleep state.
 * @state: System sleep state to enter.
 *
 * Make sure that no one else is trying to put the system into a sleep state.
 * Fail if that's not the case.  Otherwise, prepare for system suspend, make the
 * system enter the given sleep state and clean up after wakeup.
 */
static int enter_state(suspend_state_t state)
{
	int error;
#if defined(CONFIG_MP_MSTAR_STR_BASE)
    int bresumefromsuspend=0;
#endif
#ifdef CONFIG_MP_R2_STR_ENABLE
volatile unsigned long u64TEESTRBOOTFLAG;
#endif
	if (!valid_state(state))
		return -ENODEV;

	if (!mutex_trylock(&pm_mutex))
		return -EBUSY;
#if defined(CONFIG_MSTAR_PM)
    extern PM_Result MDrv_PM_CopyBin2Sram(void);
    MDrv_PM_CopyBin2Sram();
#endif

#if defined(CONFIG_MP_MSTAR_STR_BASE)
    set_state_entering();
#if (MP_USB_STR_PATCH==1)
	enStrStatus=E_STR_IN_SUSPEND;
#endif
try_again:
#endif

	if (state == PM_SUSPEND_FREEZE)
		freeze_begin();

	printk(KERN_INFO "PM: Syncing filesystems ... ");
	sys_sync();
	printk("done.\n");

	pr_debug("PM: Preparing system for %s sleep\n", pm_states[state]);
	error = suspend_prepare(state);
	if (error)
		goto Unlock;

#ifdef CONFIG_MP_R2_STR_ENABLE
#define MIU0_BASE               0x20000000
#define STR_FLAG_SUSPEND_FINISH 0xFFFF8888
	u64TEESTRBOOTFLAG = get_str_handshake_addr();
	if(u64TEESTRBOOTFLAG != 0) {

		printk(KERN_INFO "PM: Send MBX to TEE for STR_Suspend  ... \n");
		//1. Setup Suspend Flag to 0
		printk(KERN_INFO "PM: u64TEESTRBOOTFLAG => Addr = 0x%x  !!!!\n", u64TEESTRBOOTFLAG );
		printk(KERN_INFO "PM: u64TEESTRBOOTFLAG => Value = 0x%x !!!! \n",kernel_read_phys(u64TEESTRBOOTFLAG));

		//2. Send Mailbox to TEE (PA!!!)
		MApi_MBX_NotifyTeetoSuspend(u64TEESTRBOOTFLAG - MIU0_BASE);

		//3. Waiting TEE to finish susepnd jobs
		while( kernel_read_phys(u64TEESTRBOOTFLAG) != STR_FLAG_SUSPEND_FINISH )
		{
			mdelay(400);
			printk(KERN_INFO "PM: Waiting TEE suspend done signal!!! 0x%x \n", kernel_read_phys(u64TEESTRBOOTFLAG));
		}
	}
	else printk(KERN_INFO "Normal STR flow\n");
#endif

	if (suspend_test(TEST_FREEZER))
		goto Finish;

	pr_debug("PM: Entering %s sleep\n", pm_states[state]);
	pm_restrict_gfp_mask();
	error = suspend_devices_and_enter(state);
	pm_restore_gfp_mask();

 Finish:
	pr_debug("PM: Finishing wakeup.\n");
 #if defined(CONFIG_MP_MSTAR_STR_BASE)
    if(STENT_RESUME_FROM_SUSPEND == get_state_value()){
        clear_state_entering();
        bresumefromsuspend=1;
    }
#endif
	suspend_finish();
 Unlock:
 #if defined(CONFIG_MP_MSTAR_STR_BASE)
 #if defined(CONFIG_MSTAR_STR_ACOFF_ON_ERR)
    if(error)
    {
        extern void mstar_str_notifypmerror_off(void);
        mstar_str_notifypmerror_off(); //it won't return, wait pm to power off
    }
 #endif

    if(is_mstar_str() && bresumefromsuspend==0){
        schedule_timeout_interruptible(HZ);
        goto try_again;
    }
 #if (MP_USB_STR_PATCH==1)
	enStrStatus=E_STR_NONE;
 #endif
 #endif
	mutex_unlock(&pm_mutex);
	return error;
}

static void pm_suspend_marker(char *annotation)
{
	struct timespec ts;
	struct rtc_time tm;

	getnstimeofday(&ts);
	rtc_time_to_tm(ts.tv_sec, &tm);
	pr_info("PM: suspend %s %d-%02d-%02d %02d:%02d:%02d.%09lu UTC\n",
		annotation, tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
		tm.tm_hour, tm.tm_min, tm.tm_sec, ts.tv_nsec);
}

/**
 * pm_suspend - Externally visible function for suspending the system.
 * @state: System sleep state to enter.
 *
 * Check if the value of @state represents one of the supported states,
 * execute enter_state() and update system suspend statistics.
 */
int pm_suspend(suspend_state_t state)
{
	int error;

	if (state <= PM_SUSPEND_ON || state >= PM_SUSPEND_MAX)
		return -EINVAL;

	pm_suspend_marker("entry");
	error = enter_state(state);
	if (error) {
		suspend_stats.fail++;
		dpm_save_failed_errno(error);
	} else {
		suspend_stats.success++;
	}
	pm_suspend_marker("exit");
	return error;
}
EXPORT_SYMBOL(pm_suspend);
