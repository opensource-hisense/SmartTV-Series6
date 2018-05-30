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
/// @file   mdrv_tuner.h
/// @brief  TUNER Driver Interface
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _DRV_TUNER_H_
#define _DRV_TUNER_H_

#include <asm/types.h>
#include "mdrv_types.h"
#if defined(CONFIG_COMPAT)
#include <linux/compat.h>
#endif

//-------------------------------------------------------------------------------------------------
//  Driver Capability
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------
typedef struct __attribute__((__packed__))
{
    U32 u32param;
    U32 retval;
} MS_TUNER_Common_Info, *PMS_TUNER_Common_Info;

typedef struct __attribute__((__packed__))
{
    U8 u8ChIdx;
    U16 u16PadSCL;
    U16 u16PadSDA;
    U8 u8SlaveId;
    U16 u16SpeedKHz;
    U32 retval;
} MS_TUNER_TunerInit_Info, *PMS_TUNER_TunerInit_Info;

typedef struct __attribute__((__packed__))
{
    U32 u32FreqKHz;
    U32 eBand;
    U32 eMode;
    U8 otherMode;
    U32 retval;
} MS_TUNER_ATV_SetTune_Info, *PMS_TUNER_ATV_SetTune_Info;

typedef struct __attribute__((__packed__))
{
    U16 u16CenterFreqMHz;
    U32 u32SymbolRateKs;
    U32 retval;
} MS_TUNER_DVBS_SetTune_Info, *PMS_TUNER_DVBS_SetTune_Info;

typedef struct __attribute__((__packed__))
{
    U32 freq;
    U32 eBandWidth;
    U32 eMode;
    U32 retval;
} MS_TUNER_DTV_SetTune_Info, *PMS_TUNER_DTV_SetTune_Info;

typedef struct __attribute__((__packed__))
{
    U8 u8SubCmd;
    U32 u32Param1;
    U32 u32Param2;
    void* pvoidParam3;
    U32 retval;
} MS_TUNER_ExtendCommend_Info, *PMS_TUNER_ExtendCommend_Info;

#if defined(CONFIG_COMPAT)
typedef struct __attribute__((__packed__))
{
    U8 u8SubCmd;
    U32 u32Param1;
    U32 u32Param2;
    compat_uptr_t pvoidParam3;
    U32 retval;
} COMPAT_MS_TUNER_ExtendCommend_Info, *COMPAT_PMS_TUNER_ExtendCommend_Info;
#endif

typedef struct __attribute__((__packed__))
{
    U16 u16Gain;
    U8 u8DType;
    U32 retval;
} MS_TUNER_GetRSSI_Info, *PMS_TUNER_GetRSSI_Info;

//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------
#define TUNER_IOC_MAGIC    't'

#define MDRV_TUNER_Connect    _IOR(TUNER_IOC_MAGIC, 0, U32)
#define MDRV_TUNER_Disconnect    _IOR(TUNER_IOC_MAGIC, 1, U32)
#define MDRV_TUNER_ATV_SetTune    _IOWR(TUNER_IOC_MAGIC, 2, MS_TUNER_ATV_SetTune_Info)
#define MDRV_TUNER_DVBS_SetTune    _IOWR(TUNER_IOC_MAGIC, 3, MS_TUNER_DVBS_SetTune_Info)
#define MDRV_TUNER_DTV_SetTune    _IOWR(TUNER_IOC_MAGIC, 4, MS_TUNER_DTV_SetTune_Info)
#if defined(CONFIG_COMPAT)
#define MDRV_TUNER_ExtendCommand    _IOWR(TUNER_IOC_MAGIC, 5, COMPAT_MS_TUNER_ExtendCommend_Info)
#else
#define MDRV_TUNER_ExtendCommand    _IOWR(TUNER_IOC_MAGIC, 5, MS_TUNER_ExtendCommend_Info)
#endif
#define MDRV_TUNER_TunerInit    _IOR(TUNER_IOC_MAGIC, 6, MS_TUNER_TunerInit_Info)
#define MDRV_TUNER_ConfigAGCMode    _IOWR(TUNER_IOC_MAGIC, 7, MS_TUNER_Common_Info)
#define MDRV_TUNER_SetTunerInScanMode    _IOWR(TUNER_IOC_MAGIC, 8, MS_TUNER_Common_Info)
#define MDRV_TUNER_SetTunerFinetuneMode    _IOWR(TUNER_IOC_MAGIC, 9, MS_TUNER_Common_Info)
#define MDRV_TUNER_GetCableStatus    _IOR(TUNER_IOC_MAGIC, 10, MS_TUNER_Common_Info)
#define MDRV_TUNER_TunerReset    _IOR(TUNER_IOC_MAGIC, 11, U32)
#define MDRV_TUNER_IsLocked    _IOR(TUNER_IOC_MAGIC, 12, U32)
#define MDRV_TUNER_GetRSSI    _IOR(TUNER_IOC_MAGIC, 13, MS_TUNER_GetRSSI_Info)
#define TUNER_IOC_MAXNR    14

//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------


#endif // _DRV_TUNER_H_

