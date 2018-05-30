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

#ifndef _DRV_TUNER_IO_H_
#define _DRV_TUNER_IO_H_

#include <asm/types.h>
#include "mdrv_types.h"

//-------------------------------------------------------------------------------------------------
//  Driver Capability
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------
int MDrv_TUNER_Connect(int minor);
int MDrv_TUNER_Disconnect(int minor);
int MDrv_TUNER_ATV_SetTune(int minor, U32 u32FreqKHz, U32 eBand, U32 eMode, U8 otherMode);
int MDrv_TUNER_DVBS_SetTune(int minor, U16 u16CenterFreqMHz, U32 u32SymbolRateKs);
int MDrv_TUNER_DTV_SetTune(int minor, U32 freq, U32 eBandWidth, U32 eMode);
int MDrv_TUNER_ExtendCommand(int minor, U8 u8SubCmd, U32 u32Param1, U32 u32Param2, void* pvoidParam3);
int MDrv_TUNER_TunerInit(int minor, U8 u8SlaveId);
int MDrv_TUNER_ConfigAGCMode(int minor, U32 eMode);
int MDrv_TUNER_SetTunerInScanMode(int minor, U32 bScan);
int MDrv_TUNER_SetTunerInFinetuneMode(int minor, U32 bFinetune);
int MDrv_TUNER_GetCableStatus(int minor, U32 eStatus);
int MDrv_TUNER_TunerReset(int minor);
int MDrv_TUNER_IsLocked(int minor);
int MDrv_TUNER_GetRSSI(int minor, U16 u16Gain, U8 u8DType);
int MDrv_TUNER_Suspend(void);
int MDrv_TUNER_Resume(void);


#endif // _DRV_TUNER_IO_H_

