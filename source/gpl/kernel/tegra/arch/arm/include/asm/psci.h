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
 */

#ifndef __ASM_ARM_PSCI_H
#define __ASM_ARM_PSCI_H

#define PSCI_POWER_STATE_TYPE_STANDBY		0
#define PSCI_POWER_STATE_TYPE_POWER_DOWN	1

#ifdef CONFIG_MP_TRUSTZONE_PATCH
#define PSCI_RET_SUCCESS		0
#define PSCI_RET_EOPNOTSUPP		-1
#define PSCI_RET_EINVAL			-2
#define PSCI_RET_EPERM			-3
#endif

struct psci_power_state {
	u16	id;
	u8	type;
	u8	affinity_level;
};

struct psci_operations {
	int (*cpu_suspend)(struct psci_power_state state,
			   unsigned long entry_point);
	int (*cpu_off)(struct psci_power_state state);
	int (*cpu_on)(unsigned long cpuid, unsigned long entry_point);
	int (*migrate)(unsigned long cpuid);
	int (*affinity_info)(unsigned long target_affinity,
			unsigned long lowest_affinity_level);
};

extern struct psci_operations psci_ops;

#ifdef CONFIG_MP_TRUSTZONE_PATCH
int __cpuinit cpu_psci_boot_secondary(unsigned int cpu,struct task_struct *idle);
void cpu_psci_die(unsigned int cpu);
int cpu_psci_suspend(unsigned long index,void *entry_point);
int cpu_psci_cpu_kill(unsigned int cpu);
#endif

#endif /* __ASM_ARM_PSCI_H */
