//<MStar Software>
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
#ifndef _PD_I2C_API_H_
#define _PD_I2C_API_H_
#if 1 //kdrv
#include "mdrv_types.h"
#endif

U8 SI215X_ucI2cReadOnly(U8 ucI2cAddr, U8 *pucBuffer, U16 ucByteCount);
U8 SI215X_ucI2cWriteOnly(U8 ucI2cAddr, U8 *pucBuffer, U16 ucByteCount);

#endif /*_PD_I2C_API_H_*/
