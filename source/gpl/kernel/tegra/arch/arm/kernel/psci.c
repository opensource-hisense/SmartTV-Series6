/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * Copyright (C) 2012 ARM Limited
 *
 * Author: Will Deacon <will.deacon@arm.com>
 */

#define pr_fmt(fmt) "psci: " fmt

#include <linux/init.h>
#include <linux/of.h>

#include <asm/compiler.h>
#include <asm/errno.h>
#include <asm/opcodes-sec.h>
#include <asm/opcodes-virt.h>
#include <asm/psci.h>
#include <linux/delay.h>
#ifdef CONFIG_MP_TRUSTZONE_PATCH
#include <chip_setup.h>
#include <linux/percpu.h>
#include <asm/cacheflush.h>
#endif

struct psci_operations psci_ops;

static int (*invoke_psci_fn)(u32, u32, u32, u32);

enum psci_function {
	PSCI_FN_CPU_SUSPEND,
	PSCI_FN_CPU_ON,
	PSCI_FN_CPU_OFF,
	PSCI_FN_MIGRATE,
	PSCI_FN_AFFINITY_INFO,
	PSCI_FN_MAX,
};

static u32 psci_function_id[PSCI_FN_MAX];

static int psci_to_linux_errno(int errno)
{
	switch (errno) {
	case PSCI_RET_SUCCESS:
		return 0;
	case PSCI_RET_EOPNOTSUPP:
		return -EOPNOTSUPP;
	case PSCI_RET_EINVAL:
		return -EINVAL;
	case PSCI_RET_EPERM:
		return -EPERM;
	};

	return -EINVAL;
}

#define PSCI_POWER_STATE_ID_MASK	0xffff
#define PSCI_POWER_STATE_ID_SHIFT	0
#define PSCI_POWER_STATE_TYPE_MASK	0x1
#define PSCI_POWER_STATE_TYPE_SHIFT	16
#define PSCI_POWER_STATE_AFFL_MASK	0x3
#define PSCI_POWER_STATE_AFFL_SHIFT	24

#ifdef CONFIG_MP_TRUSTZONE_PATCH
#define PSCI_VERSION			0x84000000
#define PSCI_CPU_SUSPEND_AARCH32	0x84000001
#define PSCI_CPU_SUSPEND_AARCH64	0xc4000001
#define PSCI_CPU_OFF			0x84000002
#define PSCI_CPU_ON_AARCH32		0x84000003
#define PSCI_CPU_ON_AARCH64		0xc4000003
#define PSCI_AFFINITY_INFO_AARCH32	0x84000004
#define PSCI_AFFINITY_INFO_AARCH64	0xc4000004
#define PSCI_MIG_AARCH32		0x84000005
#define PSCI_MIG_AARCH64		0xc4000005
#define PSCI_MIG_INFO_TYPE		0x84000006
#define PSCI_MIG_INFO_UP_CPU_AARCH32	0x84000007
#define PSCI_MIG_INFO_UP_CPU_AARCH64	0xc4000007
#define PSCI_SYSTEM_OFF			0x84000008
#define PSCI_SYSTEM_RESET		0x84000009
#define PSCI_FEATURES			0x8400000A

#define PSCI_MSTAR_ARMv8_64BIT	0x0
#define PSCI_MSTAR_ARMv8_32BIT	0x1
#define PSCI_MSTAR_ARMv7_32BIT	0x3
#define PSCI_MSTAR_ARM_MODE_MSAK 0xff

#define PSCI_MSTAR_USER_DRIVER	0x0000
#define PSCI_MSTAR_KERNEL_DRIVER	0x0100
#define PSCI_MSTAR_DRIVER_MODE_MSAK 0xff00

/* PSCI v0.2 affinity level state returned by AFFINITY_INFO */
#define PSCI_AFFINITY_LEVEL_ON		0
#define PSCI_AFFINITY_LEVEL_OFF		1
#define PSCI_AFFINITY_LEVEL_ON_PENDING	2

#define PSCI_MSTAR_WFE		0
#define PSCI_MSTAR_WFI		1
#endif //#ifdef CONFIG_MP_TRUSTZONE_PATCH

static u32 psci_power_state_pack(struct psci_power_state state)
{
	return	((state.id & PSCI_POWER_STATE_ID_MASK)
			<< PSCI_POWER_STATE_ID_SHIFT)	|
		((state.type & PSCI_POWER_STATE_TYPE_MASK)
			<< PSCI_POWER_STATE_TYPE_SHIFT)	|
		((state.affinity_level & PSCI_POWER_STATE_AFFL_MASK)
			<< PSCI_POWER_STATE_AFFL_SHIFT);
}

/*
 * The following two functions are invoked via the invoke_psci_fn pointer
 * and will not be inlined, allowing us to piggyback on the AAPCS.
 */
static noinline int __invoke_psci_fn_hvc(u32 function_id, u32 arg0, u32 arg1,
					 u32 arg2)
{
	asm volatile(
			__asmeq("%0", "r0")
			__asmeq("%1", "r1")
			__asmeq("%2", "r2")
			__asmeq("%3", "r3")
			__HVC(0)
		: "+r" (function_id)
		: "r" (arg0), "r" (arg1), "r" (arg2));

	return function_id;
}

static noinline int __invoke_psci_fn_smc(u32 function_id, u32 arg0, u32 arg1,
					 u32 arg2)
{
	asm volatile(
			__asmeq("%0", "r0")
			__asmeq("%1", "r1")
			__asmeq("%2", "r2")
			__asmeq("%3", "r3")
			__SMC(0)
		: "+r" (function_id)
		: "r" (arg0), "r" (arg1), "r" (arg2));

	return function_id;
}

static int psci_affinity_info(unsigned long target_affinity,
		unsigned long lowest_affinity_level)
{
	int err;
	u32 fn;

	fn = psci_function_id[PSCI_FN_AFFINITY_INFO];
	err = invoke_psci_fn(fn, target_affinity, lowest_affinity_level, 0);
	return err;
}

static int psci_cpu_suspend(struct psci_power_state state,
			    unsigned long entry_point)
{
	int err;
	u32 fn, power_state;

	fn = psci_function_id[PSCI_FN_CPU_SUSPEND];
	power_state = psci_power_state_pack(state);
#ifdef CONFIG_MP_TRUSTZONE_PATCH
	err = invoke_psci_fn(fn, power_state, entry_point, PSCI_MSTAR_ARMv8_32BIT | PSCI_MSTAR_USER_DRIVER);
#else
	err = invoke_psci_fn(fn, power_state, entry_point, 0);
#endif
	return psci_to_linux_errno(err);
}

static int psci_cpu_off(struct psci_power_state state)
{
	int err;
	u32 fn, power_state;

	fn = psci_function_id[PSCI_FN_CPU_OFF];
	power_state = psci_power_state_pack(state);
#ifdef CONFIG_MP_TRUSTZONE_PATCH
#if CONFIG_MSTAR_CPU_HOTPLUG
	err = invoke_psci_fn(fn, power_state, PSCI_MSTAR_WFI, 0);
#else
	err = invoke_psci_fn(fn, power_state, PSCI_MSTAR_WFE, 0);
#endif
#else
	err = invoke_psci_fn(fn, power_state, 0, 0);
#endif
	return psci_to_linux_errno(err);
}

static int psci_cpu_on(unsigned long cpuid, unsigned long entry_point)
{
	int err;
	u32 fn;

	fn = psci_function_id[PSCI_FN_CPU_ON];
#ifdef CONFIG_MP_TRUSTZONE_PATCH
	err = invoke_psci_fn(fn, cpuid, entry_point, PSCI_MSTAR_ARMv8_32BIT | PSCI_MSTAR_USER_DRIVER);
#else
	err = invoke_psci_fn(fn, cpuid, entry_point, 0);
#endif
	return psci_to_linux_errno(err);
}

static int psci_migrate(unsigned long cpuid)
{
	int err;
	u32 fn;

	fn = psci_function_id[PSCI_FN_MIGRATE];
	err = invoke_psci_fn(fn, cpuid, 0, 0);
	return psci_to_linux_errno(err);
}

static const struct of_device_id psci_of_match[] __initconst = {
	{ .compatible = "arm,psci",	},
	{},
};

#ifdef CONFIG_MP_TRUSTZONE_PATCH
uint32_t isPSCI = PSCI_RET_EOPNOTSUPP;
extern char UTOPIA_MODE[10];

int _ms_psci_ops_set(void)
{
	invoke_psci_fn = __invoke_psci_fn_smc;

	//There is no need to use other functions
	//We only use psci_ops.cpu_on now
	//But add here for next time ( CPU Hot Plug ?)
	psci_function_id[PSCI_FN_MIGRATE] = PSCI_MIG_AARCH32;
	psci_ops.migrate = psci_migrate;

	psci_function_id[PSCI_FN_CPU_SUSPEND] = PSCI_CPU_SUSPEND_AARCH32;
	psci_ops.cpu_suspend = psci_cpu_suspend;

	psci_function_id[PSCI_FN_CPU_OFF] = PSCI_CPU_OFF;
	psci_ops.cpu_off = psci_cpu_off;

	psci_function_id[PSCI_FN_CPU_ON] = PSCI_CPU_ON_AARCH32;
	psci_ops.cpu_on = psci_cpu_on;

	psci_function_id[PSCI_FN_AFFINITY_INFO] = PSCI_AFFINITY_INFO_AARCH32;
	psci_ops.affinity_info = psci_affinity_info;
}
#endif

static int __init psci_init(void)
{
	struct device_node *np;
	const char *method;
	u32 id;

#ifdef CONFIG_MP_TRUSTZONE_PATCH
	//not from dts , check smc to set the function ptr
	uint64_t BA;

	isPSCI = PSCI_RET_EOPNOTSUPP;
	printk("\033[0;33;31m [CPU_OPS] %s %d %s\033[m\n",__func__,__LINE__,UTOPIA_MODE);
	if(strncmp(UTOPIA_MODE,"optee",5) == 0)
	{
		BA = virt_to_phys((uint32_t*)&isPSCI);

		Chip_Flush_Cache_All_Single();
		__asm__ __volatile__(
			".arch_extension sec\n\t"
			"ldr r0,=0xb200585b \n\t"
			"mov r1,%0 \n\t"
			"smc #0  \n\t"
			:
			: "r"(BA)
			: "r0","r1"
		);
		Chip_Flush_Cache_All_Single();
		printk("\033[0;33;31m [CPU_OPS] %s %d %x\033[m\n",__func__,__LINE__,isPSCI);
	}
	if(PSCI_RET_SUCCESS == isPSCI)
	{
		_ms_psci_ops_set();
		return 0;
	}
#else//the nice flow would be read from dts file
	np = of_find_matching_node(NULL, psci_of_match);
	if (!np)
		return 0;

	pr_info("probing function IDs from device-tree\n");

	if (of_property_read_string(np, "method", &method)) {
		pr_warning("missing \"method\" property\n");
		goto out_put_node;
	}

	if (!strcmp("hvc", method)) {
		invoke_psci_fn = __invoke_psci_fn_hvc;
	} else if (!strcmp("smc", method)) {
		invoke_psci_fn = __invoke_psci_fn_smc;
	} else {
		pr_warning("invalid \"method\" property: %s\n", method);
		goto out_put_node;
	}

	if (!of_property_read_u32(np, "cpu_suspend", &id)) {
		psci_function_id[PSCI_FN_CPU_SUSPEND] = id;
		psci_ops.cpu_suspend = psci_cpu_suspend;
	}

	if (!of_property_read_u32(np, "cpu_off", &id)) {
		psci_function_id[PSCI_FN_CPU_OFF] = id;
		psci_ops.cpu_off = psci_cpu_off;
	}

	if (!of_property_read_u32(np, "cpu_on", &id)) {
		psci_function_id[PSCI_FN_CPU_ON] = id;
		psci_ops.cpu_on = psci_cpu_on;
	}

	if (!of_property_read_u32(np, "migrate", &id)) {
		psci_function_id[PSCI_FN_MIGRATE] = id;
		psci_ops.migrate = psci_migrate;
	}

out_put_node:
	of_node_put(np);
#endif
	return 0;
}

#ifdef CONFIG_MP_TRUSTZONE_PATCH
//we use secondary_startup install of vexpress_secondary_startup
//because in PSCI we don't need to sync secondary CPU (? just in flow)
extern void secondary_startup(void);

int __cpuinit cpu_psci_boot_secondary(unsigned int cpu,
					 struct task_struct *idle)
{
    int ret = -ENODEV;

	if (psci_ops.cpu_on)
		ret = psci_ops.cpu_on(cpu,
				       __pa(secondary_startup));
	return ret;
}

void cpu_psci_die(unsigned int cpu)
{
	int ret;
	/*
	 * There are no known implementations of PSCI actually using the
	 * power state field, pass a sensible default for now.
	 */
	struct psci_power_state state = {
		.type = PSCI_POWER_STATE_TYPE_POWER_DOWN,
	};

	ret = psci_ops.cpu_off(state);

	pr_crit("unable to power off CPU%u (%d)\n", cpu, ret);
}

static DEFINE_PER_CPU_SHARED_ALIGNED(struct psci_power_state, psci_state);

int cpu_psci_suspend(unsigned long index,void *entry_point)
{
	unsigned int cpu = smp_processor_id();
	struct psci_power_state *state = &per_cpu(psci_state, cpu);

	if (!state)
		return -EOPNOTSUPP;

	state[index].type = 1;
	return psci_ops.cpu_suspend(state[index], virt_to_phys(entry_point));
}

int cpu_psci_cpu_kill(unsigned int cpu)
{
	int err, i;

	if (!psci_ops.affinity_info)
		return 1;
	/*
	 * cpu_kill could race with cpu_die and we can
	 * potentially end up declaring this cpu undead
	 * while it is dying. So, try again a few times.
	 */

	for (i = 0; i < 10; i++) {
		err = psci_ops.affinity_info(cpu, 0);
		if (err == PSCI_AFFINITY_LEVEL_OFF) {
			pr_info("CPU%d killed.\n", cpu);
			return 1;
		}

		msleep(10);
		pr_info("Retrying again to check for CPU kill\n");
	}

	pr_warn("CPU%d may not have shut down cleanly (AFFINITY_INFO reports %d)\n",
			cpu, err);
	/* Make op_cpu_kill() fail. */
	return 0;
}
#endif//#ifdef CONFIG_MP_TRUSTZONE_PATCH
early_initcall(psci_init);
