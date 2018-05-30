/*
 *  A mstar dummy rtc driver
 *  ToDo : Implement the real rtc...
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/time.h>
#include <linux/platform_device.h>
#include <linux/rtc.h>

#include <linux/delay.h>


#ifdef CONFIG_MSTAR_RTC
//#include "mdrv_types.h"
/// data type unsigned char, data length 1 byte
typedef unsigned char                          U8;                                 // 1 byte
/// data type unsigned short, data length 2 byte
typedef unsigned short                         U16;                                // 2 bytes
/// data type unsigned int, data length 4 byte
typedef unsigned int                         U32;                                // 4 bytes

//#include "mdrv_rtc.h"

typedef struct
{
    U8 u8PmRtcIndex;
    U32 u32RtcCtrlWord;
    U32 u32RtcSetMatchCounter;
    U32 u32RtcGetMatchCounter;
    U32 u32RtcSetCounter;
    U32 u32RtcGetCounter;
} PM_RtcParam;
extern void MDrv_RTC_Init(PM_RtcParam *pPmRtcParam);
extern void MDrv_RTC_SetCount(PM_RtcParam *pPmRtcParam);                             
extern U32 MDrv_RTC_GetCount(PM_RtcParam *pPmRtcParam);
extern void MDrv_RTC_SetMatchCount(PM_RtcParam *pPmRtcParam);
extern U32 MDrv_RTC_GetMatchCount(PM_RtcParam *pPmRtcParam);  
#endif

static int mstar_get_time(struct device *dev, struct rtc_time *tm)
{
#if 1

	struct timeval time;
	do_gettimeofday(&time);

    // if the time before jan 1 2007, for it to jan 1 2007 to avoid android reboot.
    if(time.tv_sec < 1167652800)
        time.tv_sec = 1167652800;

    rtc_time_to_tm(time.tv_sec, tm);
	return rtc_valid_tm(tm);

#else

    //MDrv_RTC_GetCount(0);


    return 0;
#endif
}

static int mstar_set_time(struct device *dev, struct rtc_time *tm)
{
#if 1

    unsigned long time;
    rtc_tm_to_time(tm, &time);
    do_settimeofday((struct timespec *)&time);  //!?
	return 0;
#else

    //printk(KERN_EMERG "==RTC== %s, %d\n" , __FUNCTION__, __LINE__);
    //MDrv_RTC_SetTime();

    return 0;
#endif
}

static int mstar_set_alarm(struct device *dev, struct rtc_wkalrm *tm)
{
    
    return 0;
}

static int mstar_get_alarm(struct device *dev, struct rtc_wkalrm *tm)
{

    return 0;
}

static const struct rtc_class_ops mstar_rtc_ops = {
	.read_time = mstar_get_time,
	.set_time = mstar_set_time,
	.read_alarm = mstar_get_alarm,
	.set_alarm = mstar_set_alarm,
};

#if defined(CONFIG_ARM64)
static const struct of_device_id mstar_rtc_dt_match[] = {
	{ .compatible = "mstar-rtc", },
	{}
};
MODULE_DEVICE_TABLE(of, mstar_rtc_dt_match);
#endif

struct mstar_rtc {
	struct rtc_device *rtc;
	int rtc_alarm_irq;
	int rtc_base;
	int rtc_read_base;
	int rtc_write_base;
	int alarm_rw_base;
	u8  ctrl_reg;
	struct device *rtc_dev;
	spinlock_t ctrl_reg_lock;
};



static int __init mstar_rtc_probe(struct platform_device *dev)
{
	struct rtc_device *rtc;
    
    #ifdef CONFIG_MSTAR_RTC
    U32 u32GetCounter; 
    PM_RtcParam pmRtcParam;
    #endif
 
	rtc = rtc_device_register("rtc-mstar", &dev->dev, &mstar_rtc_ops,THIS_MODULE);
    if (IS_ERR(rtc))
    {
        return PTR_ERR(rtc);
    }
    platform_set_drvdata(dev, rtc);

    #ifdef CONFIG_MSTAR_RTC
    pmRtcParam.u8PmRtcIndex = 1;
    pmRtcParam.u32RtcCtrlWord = 12000000ul;
    pmRtcParam.u32RtcSetMatchCounter = 0;
    pmRtcParam.u32RtcGetMatchCounter = 0;
    pmRtcParam.u32RtcSetCounter = 0;
    pmRtcParam.u32RtcGetCounter = 0;
    MDrv_RTC_Init((PM_RtcParam*)&pmRtcParam);

    #endif	
    //printk(KERN_EMERG "==RTC== %s, %d\n" , __FUNCTION__, __LINE__);

    return 0;
}

static int __exit mstar_rtc_remove(struct platform_device *dev)
{
	struct rtc_device *rtc = platform_get_drvdata(dev);

	rtc_device_unregister(rtc);

	return 0;
}

static struct platform_driver mstar_rtc_driver = {
	.driver = {
		.name = "rtc-mstar",
		.owner = THIS_MODULE,
#if defined(CONFIG_ARM64)
		.of_match_table = mstar_rtc_dt_match,
#endif
	},
	.remove = __exit_p(mstar_rtc_remove),
};

static int __init mstar_rtc_init(void)
{
    int ret;

    //printk(KERN_EMERG "==RTC== %s, %d\n" , __FUNCTION__, __LINE__);
    ret = platform_driver_probe(&mstar_rtc_driver, mstar_rtc_probe);
	return ret;
}

static void __exit mstar_rtc_fini(void)
{
	platform_driver_unregister(&mstar_rtc_driver);
}

module_init(mstar_rtc_init);
module_exit(mstar_rtc_fini);

MODULE_AUTHOR("Mstarsemi");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("mstar RTC driver");
MODULE_ALIAS("platform:rtc-mstar");
