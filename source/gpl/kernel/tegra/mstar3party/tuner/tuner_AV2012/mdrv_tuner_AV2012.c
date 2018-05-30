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

#include "mdrv_tuner_datatype.h"


//-------------------------------------------------------------------------------------------------
//  Driver Compiler Options
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Local Defines
//-------------------------------------------------------------------------------------------------
#define malloc(x) kmalloc(x, GFP_KERNEL)
#define free kfree
#define printf TUNER_PRINT
#define TUNER_PRINT(fmt, args...)        printk("[%s][%05d] " fmt, match_name, __LINE__, ## args)

#ifndef UNUSED //to avoid compile warnings...
#define UNUSED(var) (void)((var) = (var))
#endif

#define mcSHOW_HW_MSG(fmt, args...)
#if 1 //kdrv
extern S32 MDrv_SW_IIC_Write(U8 u8BusNum, U8 u8SlaveID, U8 u8AddrCnt, U8* pu8Addr, U16 u16BufLen, U8* pu8Buf);
extern S32 MDrv_SW_IIC_Read(U8 u8BusNum, U8 u8SlaveID, U8 u8AddrCnt, U8* pu8Addr, U16 u16BufLen, U8* pu8Buf);
#include "mdrv_iic_io.h"
#define    printTun_dev(fmt, args...)
#endif

#define MAX_TUNER_DEV_NUM                     1

#define AV2012_I2C_ADDR                       ((U8)  0xC0)
#define  TUNER_CRYSTAL_FREQ         27
static U8 _u8SlaveID = AV2012_I2C_ADDR;



//-------------------------------------------------------------------------------------------------
//  Global Variables
//-------------------------------------------------------------------------------------------------
const char match_name[16]="Mstar-AV2012";
#if 0//(FRONTEND_TUNER_TYPE==TUNER_AV2011)
U8 TunerInitialSetting[2][42]=
{
    {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B,  0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29},
    {0x38, 0x00, 0x00, 0x50, 0x1F, 0xA3, 0xFD, 0x58, 0x0E, 0x82, 0x88, 0xB4, 0xD6, 0x40, 0x94,0x9A, 0x66, 0x40, 0x80, 0x2B, 0x6A, 0x50, 0x91, 0x27, 0x8F, 0xCC, 0x21, 0x10, 0x80,0x02, 0xF5, 0x7F, 0x4A, 0x9B, 0xE0, 0xE0, 0x36, 0x00, 0xAB, 0x97, 0xC5, 0xA8}
};

#else
U8 TunerInitialSetting[2][42]=
{
    {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B,  0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29},
    {0x38, 0x00, 0x00, 0x50, 0x1F, 0xA3, 0xFD, 0x00, 0x0E, 0x82, 0x88, 0xB4, 0x96, 0x40, 0x5B,0x6A, 0x66, 0x40, 0x80, 0x2B, 0x6A, 0x50, 0x91, 0x27, 0x8F, 0xCC, 0x21, 0x10, 0x80,0x00, 0xF5, 0x7F, 0x4A, 0x9B, 0xE0, 0xE0, 0x36, 0x02, 0xAB, 0x97, 0xC5, 0xA8}
};
#endif

//--------------------------------------------------------------------------------------------------
// Forward declaration
//--------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Local Variables
//-------------------------------------------------------------------------------------------------

static s_Tuner_dev_info *p_dev = NULL;
static s_Tuner_dev_info dev[MAX_TUNER_DEV_NUM] = 
{ 
  {E_TUNER_DTV_DVB_S_MODE, E_CLOSE, 0, 0,0,0,0,0,0,0,0},
};

//-------------------------------------------------------------------------------------------------
//  Debug Functions
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Local Functions
//-------------------------------------------------------------------------------------------------
//*--------------------------------------------------------------------------------------
//* Function Name       : platform_ms_delay
//* Object              :
//* Input Parameters    :   MS_U32 tms
//*
//* Output Parameters   :   void
//*--------------------------------------------------------------------------------------
static void platform_ms_delay(U32 DelayTimeInMs)
{

    // OEM should implement sleep operation 
   #if 0 //kdrv
   /* Variable declarations */
  usleep(1000*DelayTimeInMs);
   #else
   msleep(DelayTimeInMs);
   #endif    
    return;
}
bool AV2012_WriteReg(U8 u8SlaveID, U8 u8Addr, U8 u8Data)
{
    S32 bRet=1;
    U8 u8Value[2];
    u8Value[0]=u8Addr;
    u8Value[1]=u8Data;
    bRet&=MDrv_SW_IIC_Write(0, u8SlaveID, 0, NULL, 2, u8Value);
    return bRet;
}
bool AV2012_ReadReg(U8 u8SlaveID, U8 u8Addr, U8 *u8Data)
{
    S32 bRet=1;
    // bRet&=MDrv_IIC_Write(u8SlaveID, 0, 0, &u8Addr, 1);
    bRet&=MDrv_SW_IIC_Write(0, u8SlaveID, 0, NULL, 1, &u8Addr);
    // bRet&=MDrv_IIC_Read(u8SlaveID, 0, 0, u8Data, 1);
    bRet&= MDrv_SW_IIC_Read(0,u8SlaveID, 0, NULL, 1, u8Data);
    return bRet;
}


void AV2012_SlaveID_Check(void)
{
     TUNER_PRINT("%s is invoked\n", __FUNCTION__);
     U8 regValue;

      _u8SlaveID = 0xC0;
      do
      {
          regValue=(char) (0x38);
          if(AV2012_WriteReg(_u8SlaveID,0,regValue))
          {
              regValue = 0;
              if(AV2012_ReadReg(_u8SlaveID,0,&regValue))
              {
                    if(regValue == 0x38)
                    {
                        break;
                    }
              }
          }
          _u8SlaveID += 0x02;
      }while(_u8SlaveID <= 0xC6);
      if(_u8SlaveID > 0xC6)
      {
          _u8SlaveID = AV2012_I2C_ADDR;
      }
      TUNER_PRINT(" _u8SlaveID 0x%x\n",_u8SlaveID);
}

//-------------------------------------------------------------------------------------------------
//  Global Functions
//-------------------------------------------------------------------------------------------------
int MDrv_TUNER_Connect(int minor)
{
    TUNER_PRINT("%s is invoked\n", __FUNCTION__);
    p_dev=&(dev[minor]);
    return 0;
}

int MDrv_TUNER_Disconnect(int minor)
{
    TUNER_PRINT("%s is invoked\n", __FUNCTION__);
    p_dev=&(dev[minor]);
    return 0;
}

int MDrv_TUNER_ATV_SetTune(int minor, U32 u32FreqKHz, U32 eBand, U32 eMode, U8 otherMode)
{
    TUNER_PRINT("%s is invoked\n", __FUNCTION__);
    return 0;
}

int MDrv_TUNER_DVBS_SetTune(int minor, U16 u16CenterFreqMHz, U32 u32SymbolRateKs)
{

    BOOL bRet=TRUE;
    BOOL bAutoScan=FALSE;
    U32 u32FracN;
    U32 BW;
    U32 BF;
    U8 u8Reg[8];
    TUNER_PRINT("%s is invoked\n", __FUNCTION__);
    p_dev=&(dev[minor]);

    if (p_dev->e_status != E_WORKING)
    {
        printf("[Error]%s,%d\n",__FILE__,__LINE__);
        return FALSE;
    }
    p_dev->e_std = E_TUNER_DTV_DVB_S_MODE;
    p_dev->u32_freq = u16CenterFreqMHz;
    p_dev->u32_symbolrate = u32SymbolRateKs;
    if (u32SymbolRateKs == 0) //auto-scan mode
    {
        bAutoScan = TRUE;
    }
    platform_ms_delay(50);
    u32FracN = (u16CenterFreqMHz + TUNER_CRYSTAL_FREQ/2)/TUNER_CRYSTAL_FREQ;
    if(u32FracN > 0xff)
    {
        u32FracN = 0xff;
    }
    u8Reg[0]=(U8) (u32FracN & 0xff);
    u32FracN = (u16CenterFreqMHz<<17)/TUNER_CRYSTAL_FREQ;
    u32FracN = (u32FracN & 0x1ffff);
    u8Reg[1]=(U8) ((u32FracN>>9)&0xff);
    u8Reg[2]=(U8) ((u32FracN>>1)&0xff);
    u8Reg[3]=(U8) (((u32FracN<<7)&0x80) | 0x50); // default is 0x50
    // Channel Filter Bandwidth Setting.
    if(bAutoScan==TRUE)//requested by BB
    {
        u8Reg[5] = 0xA3; //BW=27MHz
    }
    else
    {
        // rolloff is 35%
        BW = u32SymbolRateKs*135/200;
        // monsen 20080726, BB request low IF when sym < 6.5MHz
        // add 6M when Rs<6.5M,
        if(u32SymbolRateKs<6500)
        {
            BW = BW + 6000;
        }
        // add 2M for LNB frequency shifting
        BW = BW + 2000;
        // add 8% margin since fc is not very accurate
        BW = BW*108/100;
        // Bandwidth can be tuned from 4M to 40M
        if( BW< 4000)
        {
            BW = 4000;
        }
        if( BW> 40000)
        {
            BW = 40000;
        }
        BF = (BW*127 + 21100/2) / (21100); // BW(MHz) * 1.27 / 211KHz
        u8Reg[5] = (U8)BF;
    }
    // Sequence 4
    // Send Reg0 ->Reg4
    platform_ms_delay(5);
    bRet&=AV2012_WriteReg(_u8SlaveID, 0x00, u8Reg[0]);
    bRet&=AV2012_WriteReg(_u8SlaveID, 0x01, u8Reg[1]);
    bRet&=AV2012_WriteReg(_u8SlaveID, 0x02, u8Reg[2]);
    bRet&=AV2012_WriteReg(_u8SlaveID, 0x03, u8Reg[3]);
    platform_ms_delay(5);
    // Sequence 5
    // Send Reg5
    bRet&=AV2012_WriteReg(_u8SlaveID, 0x05, u8Reg[5]);
    platform_ms_delay(5);
    // Fine-tune Function Control
    //Tuner fine-tune gain function block. bit2.
    //not auto-scan case. enable block function. FT_block=1, FT_EN=1
    if (bAutoScan==FALSE)
    {
        u8Reg[6] = 0x06;
        bRet&=AV2012_WriteReg(_u8SlaveID, 0x25, u8Reg[6]);
        platform_ms_delay(5);
        //Disable RFLP at Lock Channel sequence after reg[37]
        //RFLP=OFF at Lock Channel sequence
        // RFLP can be Turned OFF, only at Receving mode.
        u8Reg[7] = 0xD6;
        bRet&=AV2012_WriteReg(_u8SlaveID, 0x0C, u8Reg[7]);
    }
    return bRet;
}

int MDrv_TUNER_DTV_SetTune(int minor, U32 freq, U32 eBandWidth, U32 eMode)
{
    TUNER_PRINT("%s is invoked\n", __FUNCTION__);
    return 0;
}

int MDrv_TUNER_ExtendCommand(int minor, U8 u8SubCmd, U32 u32Param1, U32 u32Param2, void* pvoidParam3)
{
    TUNER_PRINT("%s is invoked\n", __FUNCTION__);
    
    p_dev=&(dev[minor]);
    return 0;
}

int MDrv_TUNER_TunerInit(int minor, u8 u8Slave)
{

    BOOL bRet = TRUE;
    U8 index;
    TUNER_PRINT("%s is invoked\n", __FUNCTION__);
    _u8SlaveID=u8Slave;
    
    if (minor < MAX_TUNER_DEV_NUM)
    {
        p_dev=&(dev[minor]);
        if ( (p_dev->e_status == E_CLOSE)
            || (p_dev->e_status == E_SUSPEND) )
        {

            AV2012_SlaveID_Check();
            TUNER_PRINT(" _u8SlaveID 0x%x\n",_u8SlaveID);
            for (index=0; index < 12; index++)
            {
                bRet&=AV2012_WriteReg(_u8SlaveID, TunerInitialSetting[0][index], TunerInitialSetting[1][index]);
            }
            platform_ms_delay(1);
            for (index=13; index < 42; index++)
            {
                bRet&=AV2012_WriteReg(_u8SlaveID, TunerInitialSetting[0][index], TunerInitialSetting[1][index]);
            }
            platform_ms_delay(1);
            bRet&=AV2012_WriteReg(_u8SlaveID, TunerInitialSetting[0][12], TunerInitialSetting[1][12]);
            platform_ms_delay(100);
            for (index=0; index < 12; index++)
            {
                bRet&=AV2012_WriteReg(_u8SlaveID, TunerInitialSetting[0][index], TunerInitialSetting[1][index]);
            }
            platform_ms_delay(1);
            for (index=13; index < 42; index++)
            {
                bRet&=AV2012_WriteReg(_u8SlaveID, TunerInitialSetting[0][index], TunerInitialSetting[1][index]);
            }
            platform_ms_delay(1);
            bRet&=AV2012_WriteReg(_u8SlaveID, TunerInitialSetting[0][12], TunerInitialSetting[1][12]);
            platform_ms_delay(50);
                
            if(bRet== FALSE)
            {
                TUNER_PRINT("tuner init fail\n");
            }
            else
            {
                p_dev->e_status = E_WORKING;               
            }
        }        
    }
    else
    {
        bRet = FALSE;
    }    
    return bRet;
}


int MDrv_TUNER_ConfigAGCMode(int minor, U32 eMode)
{
    TUNER_PRINT("%s is invoked\n", __FUNCTION__);
    return FALSE;
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

    BOOL bRet=TRUE;
    U8 u8Data = 0;
    TUNER_PRINT("%s is invoked\n", __FUNCTION__);    
    p_dev=&(dev[minor]);
    bRet&=AV2012_ReadReg(_u8SlaveID, 0x0B, &u8Data);
    if (bRet==FALSE)
    {
        return bRet;
    }
    else
    {
        if ((u8Data&0x03)!=0x03)
        {
            bRet=FALSE;
        }
    }
    //printf("Tuner Status 0x%x\n", u8Data);
    return bRet;
}

int MDrv_TUNER_GetRSSI(int minor, U16 u16Gain, U8 u8DType)
{
    TUNER_PRINT("%s is invoked\n", __FUNCTION__);
    return 0;
}

int MDrv_TUNER_Suspend(void)
{
    U8 i = 0;
    
    for (i=0; i<MAX_TUNER_DEV_NUM; i++)
    {
        if (dev[i].e_status == E_WORKING)
        {
            dev[i].e_status = E_SUSPEND;
            //dev[i].pre_bw = E_RF_CH_BAND_INVALID;
            //dev[i].s16Prev_finetune = 0;
            //dev[i].m_bInATVScanMode = 0;
            //dev[i].m_bInfinttuneMode = 0;
        }
    }
#if 0//kdrv_temp
    if (NULL != api) {
        free(api);
        api = NULL;
    }
#endif
    return 0;
}


int MDrv_TUNER_Resume(void)
{
    U8 i = 0;
    BOOL ret_code = FALSE;
    TUNER_PRINT("%s is invoked\n", __FUNCTION__);    
    for (i=0; i<MAX_TUNER_DEV_NUM; i++)
    {
        if (dev[i].e_status == E_SUSPEND)
        {
            if (MDrv_TUNER_TunerInit((int)i,_u8SlaveID)==TRUE)
            {
                if (dev[i].e_std == E_TUNER_DTV_DVB_S_MODE)
                {
                    ret_code = MDrv_TUNER_DVBS_SetTune((int)i, dev[i].u32_freq, dev[i].u32_symbolrate);
                    if (ret_code == FALSE)
                    {
                        printf("Error, DTV_SetTune fail after resume.%d.%d.%d.%d\n",i,dev[i].u32_freq,dev[i].u32_eband_bandwidth,dev[i].u32_eMode);
                    }
                }
                else
                {
                    printf("Warnning, Undefine STD after resume...indx=%d,std=%d\n",i,dev[i].e_std);
                }
            }
            else
            {
                printf("Error, Tuner resume init fail...\n");
                ret_code = FALSE;
            }
        }
    }    

    return ret_code;
}

