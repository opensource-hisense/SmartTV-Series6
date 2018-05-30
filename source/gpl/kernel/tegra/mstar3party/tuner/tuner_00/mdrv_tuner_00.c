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
/// file    mdrv_tuner.c
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

#include "mst_devid.h"
#include "mdrv_types.h"

//-------------------------------------------------------------------------------------------------
//  Driver Compiler Options
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Local Defines
//-------------------------------------------------------------------------------------------------
#define TUNER_PRINT(fmt, args...)        //printk("[%s][%05d] " fmt, match_name, __LINE__, ## args)

//-------------------------------------------------------------------------------------------------
//  Global Variables
//-------------------------------------------------------------------------------------------------
const char match_name[16]="Mstar-tuner-00";

//--------------------------------------------------------------------------------------------------
// Forward declaration
//--------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Local Variables
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Debug Functions
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Local Functions
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Global Functions
//-------------------------------------------------------------------------------------------------
int MDrv_TUNER_Connect(int minor)
{
    TUNER_PRINT("%s is invoked\n", __FUNCTION__);
    return 0;
}

int MDrv_TUNER_Disconnect(int minor)
{
    TUNER_PRINT("%s is invoked\n", __FUNCTION__);
    return 0;
}

int MDrv_TUNER_ATV_SetTune(int minor, U32 u32FreqKHz, U32 eBand, U32 eMode, U8 otherMode)
{
    TUNER_PRINT("%s is invoked\n", __FUNCTION__);
    return 0;
}

int MDrv_TUNER_DVBS_SetTune(int minor, U16 u16CenterFreqMHz, U32 u32SymbolRateKs)
{
    TUNER_PRINT("%s is invoked\n", __FUNCTION__);
    return 0;
}

int MDrv_TUNER_DTV_SetTune(int minor, U32 freq, U32 eBandWidth, U32 eMode)
{
    TUNER_PRINT("%s is invoked\n", __FUNCTION__);
    return 0;
}

int MDrv_TUNER_ExtendCommand(int minor, U8 u8SubCmd, U32 u32Param1, U32 u32Param2, void* pvoidParam3)
{
    TUNER_PRINT("%s is invoked\n", __FUNCTION__);
    return 0;
}

int MDrv_TUNER_TunerInit(int minor)
{
    TUNER_PRINT("%s is invoked\n", __FUNCTION__);
    return 0;
}

int MDrv_TUNER_ConfigAGCMode(int minor, U32 eMode)
{
    TUNER_PRINT("%s is invoked\n", __FUNCTION__);
    return 0;
}

int MDrv_TUNER_SetTunerInScanMode(int minor, U32 bScan)
{
    TUNER_PRINT("%s is invoked\n", __FUNCTION__);
    return 0;
}

int MDrv_TUNER_SetTunerInFinetuneMode(int minor, U32 bFinetune)
{
    TUNER_PRINT("%s is invoked\n", __FUNCTION__);
    return 0;
}

int MDrv_TUNER_GetCableStatus(int minor, U32 eStatus)
{
    TUNER_PRINT("%s is invoked\n", __FUNCTION__);
    return 0;
}

int MDrv_TUNER_TunerReset(int minor)
{
    TUNER_PRINT("%s is invoked\n", __FUNCTION__);
    return 0;
}

int MDrv_TUNER_IsLocked(int minor)
{
    TUNER_PRINT("%s is invoked\n", __FUNCTION__);
    return 0;
}

int MDrv_TUNER_GetRSSI(int minor, U16 u16Gain, U8 u8DType)
{
    TUNER_PRINT("%s is invoked\n", __FUNCTION__);
    return 0;
}

int MDrv_TUNER_Suspend(void)
{
    return 0;
}

int MDrv_TUNER_Resume(void)
{
    return 0;
}


