
#include <linux/pm.h>
#include <linux/suspend.h>
#include <linux/cpuidle.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/err.h>
#include <linux/slab.h>
#include <linux/pm_clock.h>
#include <linux/platform_device.h>
#include <linux/delay.h>
#include <linux/irq.h>
#include <linux/bitrev.h>
#include <linux/console.h>
#include <asm/cpuidle.h>
#include <asm/io.h>
#include <asm/tlbflush.h>
#include <asm/suspend.h>
#include <chip_setup.h>
#include <asm/cacheflush.h>
#include <linux/cpu_pm.h>




static int mstar_pwrdown_idle(struct cpuidle_device *dev,
				struct cpuidle_driver *drv,
				int index)
{
 
       if(dev->cpu == 0)
       {
	     return 0;
       }

	     cpu_pm_enter();
	
	     cpu_pm_exit();
	     return index;
}

static struct cpuidle_driver mstar_idle_driver = {
	.name			= "mstar_idle",
	.owner			= THIS_MODULE,
	.states[0]		= ARM_CPUIDLE_WFI_STATE,
	.states[1]		= {
		.enter			= mstar_pwrdown_idle,
		.exit_latency		= 10,
		.target_residency	= 100000,
		.flags			= CPUIDLE_FLAG_TIME_VALID,
		.name			= "cpu power down",
		.desc			= "power down",
	},
	.state_count = 1,
};


static int __init mstar_cpuidle_init(void)
{

	return cpuidle_register(&mstar_idle_driver, NULL);
}

module_init(mstar_cpuidle_init);

