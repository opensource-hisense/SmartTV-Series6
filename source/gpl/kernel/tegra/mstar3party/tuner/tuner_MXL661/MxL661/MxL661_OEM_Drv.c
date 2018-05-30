/*****************************************************************************************
 *
 * FILE NAME          : MxL661_OEM_Drv.c
 * 
 * AUTHOR             : Dong Liu 
 *
 * DATE CREATED       : 01/23/2011  
 *
 * DESCRIPTION        : This file contains I2C driver and Sleep functins that 
 *                      OEM should implement for MxL661 APIs
 *                             
 *****************************************************************************************
 *                Copyright (c) 2010, MaxLinear, Inc.
 ****************************************************************************************/
#if 1//kdrv
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

#endif
#include "MxL661_OEM_Drv.h"

#if 0//kdrv
#include "mapi_i2c.h"
#include <unistd.h>
#endif
#if 1 //kdrv
//extern bool MDrv_SW_IIC_WriteBytes(u16 u16BusNumSlave, u8 u8AddrCnt, u8* pu8Addr, u16 u16BufLen, u8* pu8Buf);
//extern bool MDrv_SW_IIC_ReadBytes(u16 u16BusNumSlave, u8 u8AddrCnt, u8* pu8Addr, u16 u16BufLen, u8* pu8Buf);
extern S32 MDrv_SW_IIC_Write(U8 u8BusNum, U8 u8SlaveID, U8 u8AddrCnt, U8* pu8Addr, U16 u16BufLen, U8* pu8Buf);
extern S32 MDrv_SW_IIC_Read(U8 u8BusNum, U8 u8SlaveID, U8 u8AddrCnt, U8* pu8Addr, U16 u16BufLen, U8* pu8Buf);
#include "mdrv_iic_io.h"
#define    printTun_dev(fmt, args...)
#endif

//mapi_i2c *mx661_iptr = NULL; //kdrv
/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxLWare661_OEM_WriteRegister
--| 
--| AUTHOR        : Brenndon Lee
--|
--| DATE CREATED  : 7/30/2009
--|
--| DESCRIPTION   : This function does I2C write operation.
--|
--| RETURN VALUE  : True or False
--|
--|-------------------------------------------------------------------------------------*/

MXL_STATUS MxLWare661_OEM_WriteRegister(UINT8 I2cSlaveAddr, UINT8 RegAddr, UINT8 RegData)
{
  MXL_STATUS status = MXL_TRUE;
   
  // OEM should implement I2C write protocol that complies with MxL661 I2C
  // format.

  // 8 bit Register Write Protocol:
  // +------+-+-----+-+-+----------+-+----------+-+-+
  // |MASTER|S|SADDR|W| |RegAddr   | |RegData(L)| |P|
  // +------+-+-----+-+-+----------+-+----------+-+-+
  // |SLAVE |         |A|          |A|          |A| |
  // +------+---------+-+----------+-+----------+-+-+
  // Legends: SADDR (I2c slave address), S (Start condition), A (Ack), N(NACK), 
  // P(Stop condition)
  
  I2cSlaveAddr = I2cSlaveAddr;
  RegAddr = RegAddr;
  RegData =RegData;
  
#if 0 //kdrv extern iic
  if(mx661_iptr == NULL)
      mx661_iptr = mapi_i2c::GetI2C_Dev(TUNER1);

  if (mx661_iptr->WriteBytes(1, &RegAddr, 1, &RegData) == MAPI_FALSE)
    printf("MX661 I2C write error!\n");
  else
    status = MXL_TRUE;
#else
  MDrv_SW_IIC_Write(0x1,  I2cSlaveAddr, 1, &RegAddr, 1, &RegData);
#endif
  return status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxLWare661_OEM_ReadRegister
--| 
--| AUTHOR        : Brenndon Lee
--|
--| DATE CREATED  : 7/30/2009
--|
--| DESCRIPTION   : This function does I2C read operation.
--|
--| RETURN VALUE  : True or False
--|
--|---------------------------------------------------------------------------*/

MXL_STATUS MxLWare661_OEM_ReadRegister(UINT8 I2cSlaveAddr, UINT8 RegAddr, UINT8 *DataPtr)
{
  MXL_STATUS status = MXL_TRUE;
  
  // OEM should implement I2C read protocol that complies with MxL661 I2C
  // format.

  // 8 bit Register Read Protocol:
  // +------+-+-----+-+-+----+-+----------+-+-+
  // |MASTER|S|SADDR|W| |0xFB| |RegAddr   | |P|
  // +------+-+-----+-+-+----+-+----------+-+-+
  // |SLAVE |         |A|    |A|          |A| |
  // +------+-+-----+-+-+----+-+----------+-+-+
  // +------+-+-----+-+-+-----+--+-+
  // |MASTER|S|SADDR|R| |     |MN|P|
  // +------+-+-----+-+-+-----+--+-+
  // |SLAVE |         |A|Data |  | |
  // +------+---------+-+-----+--+-+
  // Legends: SADDR(I2c slave address), S(Start condition), MA(Master Ack), MN(Master NACK), 
  // P(Stop condition)
  
  I2cSlaveAddr = I2cSlaveAddr;
  RegAddr = RegAddr;
  *DataPtr = *DataPtr;
 
  UINT8 data[2];
  data[0] = 0xFB;
  data[1] = RegAddr;

#if 0 //kdrv extern iic
  if(mx661_iptr == NULL)
      mx661_iptr = mapi_i2c::GetI2C_Dev(TUNER1);

  if (mx661_iptr->ReadBytes(2, data, 1, DataPtr) == MAPI_FALSE)
    printf("MX661 I2C write error!\n");
#else
  MDrv_SW_IIC_Read(0x1, I2cSlaveAddr, 2, data, 1, DataPtr);
#endif

  return status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxLWare661_OEM_Sleep
--| 
--| AUTHOR        : Dong Liu
--|
--| DATE CREATED  : 01/10/2010
--|
--| DESCRIPTION   : This function complete sleep operation. WaitTime is in ms unit
--|
--| RETURN VALUE  : None
--|
--|-------------------------------------------------------------------------------------*/

void MxLWare661_OEM_Sleep(UINT16 DelayTimeInMs)
{
  // OEM should implement sleep operation 
#if 0 //kdrv
  usleep(1000*DelayTimeInMs);
#else
  msleep(DelayTimeInMs);
#endif
}
