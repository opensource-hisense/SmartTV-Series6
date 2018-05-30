///////////////////////////////////////////////////////////////////////////////////////////////////
//
// * Copyright (c) 2006 - 2007 MStar Semiconductor, Inc.
// This program is free software.
// You can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation;
// either version 2 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with this program;
// if not, write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// file    mdrv_tuner_io.c
/// @brief  TUNER Driver Interface
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////


//-------------------------------------------------------------------------------------------------
//  Include Files
//-------------------------------------------------------------------------------------------------
//#include "MsCommon.h"
#include <linux/autoconf.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/delay.h>
#include <linux/kdev_t.h>
#include <linux/slab.h>
#include <linux/mm.h>
#include <linux/ioport.h>
#include <linux/interrupt.h>
#include <linux/workqueue.h>
#include <linux/poll.h>
#include <linux/wait.h>
#include <linux/cdev.h>
#include <linux/time.h>
#include <linux/timer.h>
#include <asm/io.h>
#include <linux/semaphore.h>
#include <linux/platform_device.h>
#if defined(CONFIG_COMPAT)
#include <linux/compat.h>
#endif

#include "mst_devid.h"

#include "mdrv_tuner.h"
#include "mdrv_tuner_io.h"
#include "mdrv_iic_io.h"

//-------------------------------------------------------------------------------------------------
//  Driver Compiler Options
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Local Defines
//-------------------------------------------------------------------------------------------------

#define TUNER_PRINT(fmt, args...)        printk("[TUNER][%05d] " fmt, __LINE__, ## args)
static struct class *tuner_class;
typedef struct
{
    S32                          s32MajorTUNER;
    S32                          s32MinorTUNER;
    struct cdev                 cDevice;
    struct file_operations      TUNERFop;
    struct fasync_struct        *async_queue; /* asynchronous readers */
} TUNER_ModHandle_t;


#define MOD_TUNER_DEVICE_COUNT         1
#define MOD_TUNER_NAME                 "tuner" //"ModTUNER"
#define MOD_TUNER_SUPPORT_NUM   16

//-------------------------------------------------------------------------------------------------
//  Global Variables
//-------------------------------------------------------------------------------------------------
//DECLARE_MUTEX(PfModeSem);


//--------------------------------------------------------------------------------------------------
// Forward declaration
//--------------------------------------------------------------------------------------------------
static int                      _MDrv_TUNER_Open (struct inode *inode, struct file *filp);
static int                      _MDrv_TUNER_Release(struct inode *inode, struct file *filp);
static ssize_t                  _MDrv_TUNER_Read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos);
static ssize_t                  _MDrv_TUNER_Write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos);
static unsigned int             _MDrv_TUNER_Poll(struct file *filp, poll_table *wait);
#ifdef HAVE_UNLOCKED_IOCTL
static long _MDrv_TUNER_Ioctl(struct file *filp, unsigned int cmd, unsigned long arg);
#else
static int _MDrv_TUNER_Ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg);
#endif
#if defined(CONFIG_COMPAT)
static long _Compat_MDrv_TUNER_Ioctl(struct file *filp, unsigned int cmd, unsigned long arg);
#endif
static int                      _MDrv_TUNER_Fasync(int fd, struct file *filp, int mode);

extern void MDrv_IIC_Init(void);
extern B16 MDrv_SW_IIC_ConfigBus(IIC_BusCfg_t* pBusCfg);

//-------------------------------------------------------------------------------------------------
//  Local Variables
//-------------------------------------------------------------------------------------------------

static TUNER_ModHandle_t TUNERDev=
{
    .s32MajorTUNER = MDRV_MAJOR_TUNER,
    .s32MinorTUNER = MDRV_MINOR_TUNER,
    .cDevice =
    {
        .kobj = {.name= MOD_TUNER_NAME, },
        .owner = THIS_MODULE,
    },
    .TUNERFop =
    {
        .open =     _MDrv_TUNER_Open,
        .release =  _MDrv_TUNER_Release,
        .read =     _MDrv_TUNER_Read,
        .write =    _MDrv_TUNER_Write,
        .poll =     _MDrv_TUNER_Poll,
        #ifdef HAVE_UNLOCKED_IOCTL
        .unlocked_ioctl = _MDrv_TUNER_Ioctl,
        #else        
        .ioctl = _MDrv_TUNER_Ioctl,
        #endif 
        #if defined(CONFIG_COMPAT)
        .compat_ioctl = _Compat_MDrv_TUNER_Ioctl,
        #endif
        .fasync =   _MDrv_TUNER_Fasync,
    },
};

extern const char match_name[16];
static int tuner[MOD_TUNER_SUPPORT_NUM],param_num;
module_param_array(tuner,int,&param_num,0644);

//-------------------------------------------------------------------------------------------------
//  Debug Functions
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Local Functions
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Global Functions
//-------------------------------------------------------------------------------------------------

static int _MDrv_TUNER_Open (struct inode *inode, struct file *filp)
{
    TUNER_ModHandle_t *dev;
    
    TUNER_PRINT("%s is invoked\n", __FUNCTION__);

    dev = container_of(inode->i_cdev, TUNER_ModHandle_t , cDevice);
    filp->private_data = dev;
    return 0;
}

static int _MDrv_TUNER_Release(struct inode *inode, struct file *filp)
{
    TUNER_PRINT("%s is invoked\n", __FUNCTION__);
    return 0;
}

static ssize_t _MDrv_TUNER_Read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
    TUNER_PRINT("%s is invoked\n", __FUNCTION__);
    return 0;
}

static ssize_t _MDrv_TUNER_Write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos)
{
    TUNER_PRINT("%s is invoked\n", __FUNCTION__);
    return 0;
}

static unsigned int _MDrv_TUNER_Poll(struct file *filp, poll_table *wait)
{
    TUNER_PRINT("%s is invoked\n", __FUNCTION__);
    return 0;
}

static int _MDrv_TUNER_Fasync(int fd, struct file *filp, int mode)
{
    TUNER_PRINT("%s is invoked\n", __FUNCTION__);
    return 0;
}

#if defined(CONFIG_COMPAT)
static long _Compat_MDrv_TUNER_Ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    U8 u8;
    U32 u32, ret;
    compat_uptr_t ptr;
    MS_TUNER_ExtendCommend_Info __user *ExtendCommend_Info;
    COMPAT_MS_TUNER_ExtendCommend_Info __user *COMPAT_ExtendCommend_Info;

    TUNER_PRINT("%s is invoked\n", __FUNCTION__);	

    switch(cmd)
    {
        case MDRV_TUNER_ExtendCommand:
            COMPAT_ExtendCommend_Info = compat_ptr(arg);
            ExtendCommend_Info = (MS_TUNER_ExtendCommend_Info *)compat_alloc_user_space(sizeof(MS_TUNER_ExtendCommend_Info));
            if (ExtendCommend_Info == NULL)
                return -EFAULT;     
            get_user(u8, &COMPAT_ExtendCommend_Info->u8SubCmd);
            put_user(u8, &ExtendCommend_Info->u8SubCmd);
            get_user(u32, &COMPAT_ExtendCommend_Info->u32Param1);
            put_user(u32, &ExtendCommend_Info->u32Param1);
            get_user(u32, &COMPAT_ExtendCommend_Info->u32Param2);
            put_user(u32, &ExtendCommend_Info->u32Param2);
            get_user(ptr, &COMPAT_ExtendCommend_Info->pvoidParam3);
            put_user(ptr, &ExtendCommend_Info->pvoidParam3);
            get_user(u32, &COMPAT_ExtendCommend_Info->retval);
            put_user(u32, &ExtendCommend_Info->retval);
			
            ret = filp->f_op->unlocked_ioctl(filp, cmd, (unsigned long)ExtendCommend_Info);            
			
            get_user(u8, &ExtendCommend_Info->u8SubCmd);
            put_user(u8, &COMPAT_ExtendCommend_Info->u8SubCmd);
            get_user(u32, &ExtendCommend_Info->u32Param1);
            put_user(u32, &COMPAT_ExtendCommend_Info->u32Param1);
            get_user(u32, &ExtendCommend_Info->u32Param2);
            put_user(u32, &COMPAT_ExtendCommend_Info->u32Param2);
            get_user(ptr, &ExtendCommend_Info->pvoidParam3);
            put_user(ptr, &COMPAT_ExtendCommend_Info->pvoidParam3);
            get_user(u32, &ExtendCommend_Info->retval);
            put_user(u32, &COMPAT_ExtendCommend_Info->retval);            
            return ret;
			
        case MDRV_TUNER_Connect:
        case MDRV_TUNER_Disconnect:
        case MDRV_TUNER_ATV_SetTune:
        case MDRV_TUNER_DVBS_SetTune:
        case MDRV_TUNER_DTV_SetTune:
        case MDRV_TUNER_TunerInit:
        case MDRV_TUNER_ConfigAGCMode:
        case MDRV_TUNER_SetTunerInScanMode:
        case MDRV_TUNER_SetTunerFinetuneMode:
        case MDRV_TUNER_GetCableStatus:
        case MDRV_TUNER_TunerReset:
        case MDRV_TUNER_IsLocked:
        case MDRV_TUNER_GetRSSI:
            return filp->f_op->unlocked_ioctl(filp, cmd,(unsigned long)compat_ptr(arg));
        default:
            TUNER_PRINT("ioctl: unknown command\n");
            return -ENOTTY;
    }
    return 0;
}
#endif

#ifdef HAVE_UNLOCKED_IOCTL
static long _MDrv_TUNER_Ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
#else
static int _MDrv_TUNER_Ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)
#endif
{
    MS_TUNER_TunerInit_Info TunerInit_Info = {0};
    MS_TUNER_ATV_SetTune_Info ATV_SetTune_Info = {0};
    MS_TUNER_DVBS_SetTune_Info DVBS_SetTune_Info = {0};
    MS_TUNER_DTV_SetTune_Info DTV_SetTune_Info = {0};
    MS_TUNER_ExtendCommend_Info ExtendCommend_Info = {0};
    MS_TUNER_Common_Info Common_Info = {0};
    MS_TUNER_GetRSSI_Info GetRSSI_Info = {0};
    int retval=0, minor;
    IIC_BusCfg_t BusCfg = {0};

    minor = iminor(filp->f_path.dentry->d_inode);
    TUNER_PRINT("%s is invoked, device minor is %d\n", __FUNCTION__, minor);	

    if ((TUNER_IOC_MAGIC!= _IOC_TYPE(cmd)) || (_IOC_NR(cmd)> TUNER_IOC_MAXNR))
    {
        return -ENOTTY;
    }

    switch(cmd)
    {
        case MDRV_TUNER_Connect:
            TUNER_PRINT("ioctl: MDRV_TUNER_Connect\n");
            retval=MDrv_TUNER_Connect(minor);
            if (copy_to_user((int *) arg, &retval, sizeof(int)))
            {
 	            return -EFAULT;
            }
            break;
        case MDRV_TUNER_Disconnect:
            TUNER_PRINT("ioctl: MDRV_TUNER_Disconnect\n");
            retval=MDrv_TUNER_Disconnect(minor);
            if (copy_to_user((int *) arg, &retval, sizeof(int)))
            {
 	            return -EFAULT;
            }
            break;
        case MDRV_TUNER_ATV_SetTune:
            TUNER_PRINT("ioctl: MDRV_TUNER_ATV_SetTune\n");
            if (copy_from_user(&ATV_SetTune_Info, (MS_TUNER_ATV_SetTune_Info *) arg, sizeof(MS_TUNER_ATV_SetTune_Info)))
            {
 	            return -EFAULT;
            }
            retval=MDrv_TUNER_ATV_SetTune(minor, ATV_SetTune_Info.u32FreqKHz, ATV_SetTune_Info.eBand, ATV_SetTune_Info.eMode, ATV_SetTune_Info.otherMode);
            ATV_SetTune_Info.retval = retval;
            if (copy_to_user((MS_TUNER_ATV_SetTune_Info *) arg, &ATV_SetTune_Info, sizeof(MS_TUNER_ATV_SetTune_Info)))
            {
 	            return -EFAULT;
            }
            break;
        case MDRV_TUNER_DVBS_SetTune:
            TUNER_PRINT("ioctl: MDRV_TUNER_DVBS_SetTune\n");
            if (copy_from_user(&DVBS_SetTune_Info, (MS_TUNER_DVBS_SetTune_Info *) arg, sizeof(MS_TUNER_DVBS_SetTune_Info)))
            {
 	            return -EFAULT;
            }
            retval=MDrv_TUNER_DVBS_SetTune(minor, DVBS_SetTune_Info.u16CenterFreqMHz, DVBS_SetTune_Info.u32SymbolRateKs);
            DVBS_SetTune_Info.retval = retval;
            if (copy_to_user((MS_TUNER_DVBS_SetTune_Info *) arg, &DVBS_SetTune_Info, sizeof(MS_TUNER_DVBS_SetTune_Info)))
            {
 	            return -EFAULT;
            }
            break;
        case MDRV_TUNER_DTV_SetTune:
            TUNER_PRINT("ioctl: MDRV_TUNER_DTV_SetTune\n");
            if (copy_from_user(&DTV_SetTune_Info, (MS_TUNER_DTV_SetTune_Info *) arg, sizeof(MS_TUNER_DTV_SetTune_Info)))
            {
 	            return -EFAULT;
            }
            retval=MDrv_TUNER_DTV_SetTune(minor, DTV_SetTune_Info.freq, DTV_SetTune_Info.eBandWidth, DTV_SetTune_Info.eMode);
            DTV_SetTune_Info.retval = retval;
            if (copy_to_user((MS_TUNER_DTV_SetTune_Info *) arg, &DTV_SetTune_Info, sizeof(MS_TUNER_DTV_SetTune_Info)))
            {
 	            return -EFAULT;
            }
            break;
        case MDRV_TUNER_ExtendCommand:
            TUNER_PRINT("ioctl: MDRV_TUNER_ExtendCommand\n");
            if (copy_from_user(&ExtendCommend_Info, (MS_TUNER_ExtendCommend_Info *) arg, sizeof(MS_TUNER_ExtendCommend_Info)))
            {
 	            return -EFAULT;
            }
            retval=MDrv_TUNER_ExtendCommand(minor, ExtendCommend_Info.u8SubCmd, ExtendCommend_Info.u32Param1, ExtendCommend_Info.u32Param2, ExtendCommend_Info.pvoidParam3);
            ExtendCommend_Info.retval = retval;
            if (copy_to_user((MS_TUNER_ExtendCommend_Info *) arg, &ExtendCommend_Info, sizeof(MS_TUNER_ExtendCommend_Info)))
            {
 	            return -EFAULT;
            }
            break;
        case MDRV_TUNER_TunerInit:
            TUNER_PRINT("ioctl: MDRV_TUNER_TunerInit\n");
			if (copy_from_user(&TunerInit_Info, (MS_TUNER_TunerInit_Info *) arg, sizeof(MS_TUNER_TunerInit_Info)))
            {
 	            return -EFAULT;
            }
            
            MDrv_IIC_Init();

            BusCfg.u8ChIdx = TunerInit_Info.u8ChIdx;
            BusCfg.u16PadSCL = TunerInit_Info.u16PadSCL;
            BusCfg.u16PadSDA = TunerInit_Info.u16PadSDA;
            BusCfg.u16SpeedKHz = TunerInit_Info.u16SpeedKHz;
            BusCfg.u8Enable = TRUE;
            MDrv_SW_IIC_ConfigBus(&BusCfg);
            
            retval=MDrv_TUNER_TunerInit(minor,TunerInit_Info.u8SlaveId);
            if (copy_to_user((int *) arg, &retval, sizeof(int)))
            {
 	            return -EFAULT;
            }
            break;
        case MDRV_TUNER_ConfigAGCMode:
            TUNER_PRINT("ioctl: MDRV_TUNER_ConfigAGCMode\n");
            if (copy_from_user(&Common_Info, (MS_TUNER_Common_Info *) arg, sizeof(MS_TUNER_Common_Info)))
            {
 	            return -EFAULT;
            }
            retval=MDrv_TUNER_ConfigAGCMode(minor, Common_Info.u32param);
            Common_Info.retval = retval;
            if (copy_to_user((MS_TUNER_Common_Info *) arg, &Common_Info, sizeof(MS_TUNER_Common_Info)))
            {
 	            return -EFAULT;
            }
            break;
        case MDRV_TUNER_SetTunerInScanMode:
            TUNER_PRINT("ioctl: MDRV_TUNER_SetTunerInScanMode\n");
            if (copy_from_user(&Common_Info, (MS_TUNER_Common_Info *) arg, sizeof(MS_TUNER_Common_Info)))
            {
 	            return -EFAULT;
            }
            retval=MDrv_TUNER_SetTunerInScanMode(minor, Common_Info.u32param);
            Common_Info.retval = retval;
            if (copy_to_user((MS_TUNER_Common_Info *) arg, &Common_Info, sizeof(MS_TUNER_Common_Info)))
            {
 	            return -EFAULT;
            }
            break;
        case MDRV_TUNER_SetTunerFinetuneMode:
            TUNER_PRINT("ioctl: MDRV_TUNER_SetTunerFinetuneMode\n");
            if (copy_from_user(&Common_Info, (MS_TUNER_Common_Info *) arg, sizeof(MS_TUNER_Common_Info)))
            {
 	            return -EFAULT;
            }
            retval=MDrv_TUNER_SetTunerInFinetuneMode(minor, Common_Info.u32param);
            Common_Info.retval = retval;
            if (copy_to_user((MS_TUNER_Common_Info *) arg, &Common_Info, sizeof(MS_TUNER_Common_Info)))
            {
 	            return -EFAULT;
            }
            break;
        case MDRV_TUNER_GetCableStatus:
            TUNER_PRINT("ioctl: MDRV_TUNER_GetCableStatus\n");
            if (copy_from_user(&Common_Info, (MS_TUNER_Common_Info *) arg, sizeof(MS_TUNER_Common_Info)))
            {
 	            return -EFAULT;
            }
            retval=MDrv_TUNER_GetCableStatus(minor, Common_Info.u32param);
            Common_Info.retval = retval;
            if (copy_to_user((MS_TUNER_Common_Info *) arg, &Common_Info, sizeof(MS_TUNER_Common_Info)))
            {
 	            return -EFAULT;
            }
            break;
        case MDRV_TUNER_TunerReset:
            TUNER_PRINT("ioctl: MDRV_TUNER_TunerReset\n");
            retval=MDrv_TUNER_TunerReset(minor);
            if (copy_to_user((int *) arg, &retval, sizeof(int)))
            {
 	            return -EFAULT;
            }
            break;
        case MDRV_TUNER_IsLocked:
            TUNER_PRINT("ioctl: MDRV_TUNER_IsLocked\n");
            retval=MDrv_TUNER_IsLocked(minor);
            if (copy_to_user((int *) arg, &retval, sizeof(int)))
            {
 	            return -EFAULT;
            }
            break;
        case MDRV_TUNER_GetRSSI:
            TUNER_PRINT("ioctl: MDRV_TUNER_GetRSSI\n");
            retval=MDrv_TUNER_GetRSSI(minor, GetRSSI_Info.u16Gain, GetRSSI_Info.u8DType);
            GetRSSI_Info.retval = retval;
            if (copy_to_user((MS_TUNER_GetRSSI_Info *) arg, &GetRSSI_Info, sizeof(MS_TUNER_GetRSSI_Info)))
            {
 	            return -EFAULT;
            }
            break;
        default:
            TUNER_PRINT("ioctl: unknown command\n");
            return -ENOTTY;
    }
    return 0;
}

static int mod_tuner_init(struct platform_device *pdev)
{
    S32         s32Ret;
    dev_t       dev;

    TUNER_PRINT("%s is invoked\n", __FUNCTION__);
    TUNERDev.s32MinorTUNER = pdev->id;
    TUNER_PRINT("TUNERDev.s32MinorTUNER: %d\nTUNERDev.s32MajorTUNER: %d\n", TUNERDev.s32MinorTUNER, TUNERDev.s32MajorTUNER);
    tuner_class = class_create(THIS_MODULE, "tuner");
    if (IS_ERR(tuner_class))
    {
        return PTR_ERR(tuner_class);
    }

    if (TUNERDev.s32MajorTUNER)
    {
        dev = MKDEV(TUNERDev.s32MajorTUNER, TUNERDev.s32MinorTUNER);
        s32Ret = register_chrdev_region(dev, MOD_TUNER_DEVICE_COUNT, MOD_TUNER_NAME);
    }
    else
    {
        s32Ret = alloc_chrdev_region(&dev, TUNERDev.s32MinorTUNER, MOD_TUNER_DEVICE_COUNT, MOD_TUNER_NAME);
        TUNERDev.s32MajorTUNER = MAJOR(dev);
    }

    if ( 0 > s32Ret)
    {
        TUNER_PRINT("Unable to get major %d\n", TUNERDev.s32MajorTUNER);
        return s32Ret;
    }

    cdev_init(&TUNERDev.cDevice, &TUNERDev.TUNERFop);
    if (0!= (s32Ret= cdev_add(&TUNERDev.cDevice, dev, MOD_TUNER_DEVICE_COUNT)))
    {
        TUNER_PRINT("Unable add a character device\n");
        unregister_chrdev_region(dev, MOD_TUNER_DEVICE_COUNT);
        return s32Ret;
    }
    device_create(tuner_class, NULL, dev, NULL, MOD_TUNER_NAME);
	  return 0;
}

static void mod_tuner_exit(void)
{
    TUNER_PRINT("%s is invoked\n", __FUNCTION__);

    cdev_del(&TUNERDev.cDevice);
    unregister_chrdev_region(MKDEV(TUNERDev.s32MajorTUNER, TUNERDev.s32MinorTUNER), MOD_TUNER_DEVICE_COUNT);
}

static int mstar_tuner_drv_probe(struct platform_device *pdev)
{
    int retval=0;
    if( !(pdev->name) || strcmp(pdev->name,match_name)
        || pdev->id!=0)
    {
        retval = -ENXIO;
    }

    retval = mod_tuner_init(pdev);
    if(!retval)
    {
        pdev->dev.platform_data=&TUNERDev;
    }	
	  return retval;
}

static int mstar_tuner_drv_remove(struct platform_device *pdev)
{
    if( !(pdev->name) || strcmp(pdev->name,match_name)
        || pdev->id!=0)
    {
        return -1;
    }

    mod_tuner_exit();
    pdev->dev.platform_data=NULL;
    return 0;
}

static int mstar_tuner_drv_suspend(struct platform_device *dev, pm_message_t state)
{
    TUNER_PRINT("%s is invoked\n", __FUNCTION__);
    MDrv_TUNER_Suspend();
    return 0;
}
static int mstar_tuner_drv_resume(struct platform_device *dev)
{
    TUNER_PRINT("%s is invoked\n", __FUNCTION__);
    MDrv_TUNER_Resume();
    return 0;
}

static struct platform_driver Mstar_tuner_driver = {
    .probe      = mstar_tuner_drv_probe,
    .remove 	= mstar_tuner_drv_remove,
    .suspend    = mstar_tuner_drv_suspend,
    .resume     = mstar_tuner_drv_resume,

    .driver = {
        .name = match_name,
        .owner = THIS_MODULE,
    }
};
static struct platform_device Mstar_tuner_device[MOD_TUNER_SUPPORT_NUM];

static int __init mstar_tuner_drv_init_module(void)
{
    int retval=0, i;
    TUNER_PRINT("%s is invoked\n", __FUNCTION__);
    
    for(i=0; i<param_num && i<MOD_TUNER_SUPPORT_NUM; i++)
    {
        Mstar_tuner_device[i].name=match_name;
        Mstar_tuner_device[i].id=tuner[i];
        platform_device_register(&(Mstar_tuner_device[i]));
    }

    retval = platform_driver_register(&Mstar_tuner_driver);
    return retval;
}

static void __exit mstar_tuner_drv_exit_module(void)
{
    platform_driver_unregister(&Mstar_tuner_driver);
}

module_init(mstar_tuner_drv_init_module);
module_exit(mstar_tuner_drv_exit_module);

MODULE_AUTHOR("MSTAR");
MODULE_DESCRIPTION("TUNER driver");
MODULE_LICENSE("GPL");

