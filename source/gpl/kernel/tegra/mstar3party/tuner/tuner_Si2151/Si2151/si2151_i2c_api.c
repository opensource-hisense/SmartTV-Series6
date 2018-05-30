//<MStar Software>
///////////////////////////////////////////////////////////////////////////////////////////////////
//
// * Copyright (c) 2010 - 2012 MStar Semiconductor, Inc.
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
#include "si2151_i2c_api.h"

/***********************************************************************/
/*              I2C Interface                                          */
/***********************************************************************/
/***********************************************************************/
/*                                                                     */
/*   FUNCTION DESCRIPTION                        u1I2cRead             */
/*                                                                     */
/*                                                                     */
/*   ROUTINES CALLED                                                   */
/*                                                                     */
/*   INPUTS                                                            */
/*      U8 u1RegAddr - Register Address to read                     */
/*      U8 u2ByteCount - number of bytes to read                    */
/*                                                                     */
/*   OUTPUTS                                                           */
/*      U8 *pu1Buffer - read data bytes are copied to this buffer   */
/*                                                                     */
/*   RETURN:                                                           */
/*    0 for success                                                    */
/*    non-zero for failure                                             */
/*                                                                     */
/***********************************************************************/
#if 1 //kdrv
extern S32 MDrv_SW_IIC_Write(U8 u8ChIIC, U8 u8SlaveID, U8 u8AddrCnt, U8* pu8Addr, U32 u32BufLen, U8* pu8Buf);
extern S32 MDrv_SW_IIC_Read(U8 u8ChIIC, U8 u8SlaveID, U8 u8AddrCnt, U8* pu8Addr, U32 u32BufLen, U8* pu8Buf);
#define    printTun_dev(fmt, args...)
#endif


U8 SI215X_ucI2cReadOnly(U8 aSlaveAddr, U8 *apData, U16 aDataSize)
{
    U8 ret = 0;
    U32 i = 0;
#if 0 //kdrv extern iic
    if (platform_I2CRead(0xff,aSlaveAddr,NULL,0,apData,aDataSize) == 0)
    {
        printTun_dev(("%s(): [IIC] TUNER READ : NG -> ", __FUNCTION__));
        ret = 1;
    }
#else
    MDrv_SW_IIC_Read(0x1, aSlaveAddr, 0, 0, aDataSize, apData);
#endif    
    // -----> Print IIC data
    printTun_dev(("<0x%02x> : ",  aSlaveAddr));
    for( i = 0; i < aDataSize ; i++ ){
        printTun_dev(("0x%02x ", apData[i]));
    }
    printTun_dev(("\n"));
    // <----- Print IIC data

    return ret;
}

U8 SI215X_ucI2cWriteOnly(U8 aSlaveAddr, U8 *apData, U16 aDataSize)
{

    U8 ret = 0;
    U32 i = 0;
#if 0 //kdrv extern iic
    if (platform_I2CWrite(0xff,aSlaveAddr,NULL,0,apData,aDataSize) == 0)
    {
        printTun_dev(("%s(): [IIC] TUNER WRITE : NG -> ", __FUNCTION__));
        ret = 1;
    }
#else
    MDrv_SW_IIC_Write(0x1, aSlaveAddr, 0, 0, aDataSize, apData);
#endif
// -----> Print IIC data
    printTun_dev(("<0x%02x> : ",  aSlaveAddr));
    for( i = 0; i < aDataSize ; i++ ){
        printTun_dev(("0x%02x ", apData[i]));
    }
    printTun_dev(("\n"));
    // <----- Print IIC data

    return ret;
}
