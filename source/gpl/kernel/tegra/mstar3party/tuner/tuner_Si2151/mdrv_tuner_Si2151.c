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

#include <linux/slab.h>
#include "Si2151/Si2151_typedefs.h"
#include "Si2151/Si2151_L1_API.h"
#include "Si2151/Si2151_L2_API.h"

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

#define C_Si2151_LO_ADDRESS             ((U8)  0xC0)
U8 _u8SlaveID=0;
//PLL lock check parameters
#define C_Si2151_PF_TO_CF_SHIFT_B 2250 /*KHZ*/
#define C_Si2151_PF_TO_CF_SHIFT_G 2750 /*KHZ*/
#define C_Si2151_PF_TO_CF_SHIFT_DK 2750 /*KHZ*/
#define C_Si2151_PF_TO_CF_SHIFT_I  2750 /*KHZ*/
#define C_Si2151_PF_TO_CF_SHIFT_L  2750 /*KHZ*/
#define C_Si2151_PF_TO_CF_SHIFT_M  1750 /*KHZ*/
#define C_Si2151_PF_TO_CF_SHIFT_L1 2750 /*KHZ*/


// center frequencies
#define C_Si2151_IF_CENTER_B  4750 /*KHZ*/
#define C_Si2151_IF_CENTER_GH 4250 /*KHZ*/
#define C_Si2151_IF_CENTER_DK 5250 /*KHZ*/
#define C_Si2151_IF_CENTER_I  4750 /*KHZ*/
#define C_Si2151_IF_CENTER_L  5250 /*KHZ*/
#define C_Si2151_IF_CENTER_L1 5250 /*KHZ*/
#define C_Si2151_IF_CENTER_M  4250 /*KHZ*/
#define C_Si2151_IF_CENTER_N  4250 /*KHZ*/
#define C_Si2151_IF_FREQUENCY          ((U16)  6000)  /* kHz */

#define TN_FREQ_STEP                    E_FREQ_STEP_62_5KHz //E_FREQ_STEP_50KHz

#define TUNER_VHF_LOWMIN_FREQ             46250L
#define TUNER_VHF_LOWMAX_FREQ             142000L
#define TUNER_VHF_HIGHMIN_FREQ            149000L
#define TUNER_VHF_HIGHMAX_FREQ            426000L
#define TUNER_UHF_MIN_FREQ_UK             470000L
#define TUNER_UHF_MIN_FREQ                434000L
#define TUNER_UHF_MAX_FREQ                863250L

#define VIF_TUNER_TYPE                  1                   // 0: RF Tuner; 1: Silicon Tuner
#define VIF_CR_RATE_B                   0x000A5ED1 // 4.75M + 2.25M   // [21:0], CR_RATE for 7.0 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_B                 0                       // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_GH                  0x000A5ED1 // 4.25M + 2.75M       // [21:0], CR_RATE for 7.0 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_GH                0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_DK                  0x000BDA13 // 5.25M + 2.75M   // [21:0], CR_RATE for 8.0 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_DK                0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_I                   0x000B1C72 // 4.75M + 2.75M          // [21:0], CR_RATE for 7.5 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_I                 0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_L                   0x000BDA13 // 5.25M + 2.75M   // [21:0], CR_RATE for 8.0 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_L                 0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_LL                  0x000BDA13 // 5.25M + 2.75M  // [21:0], CR_RATE for 8.0 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_LL                0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_MN                  0x0008E38E // 4.25 + 1.75M  // [21:0], CR_RATE for 6.0 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_MN                0                   // Video carrier position; 0: high side; 1:low side

#define TUNER_DTV_IQ_SWAP               1 // iq swap
#define TUNER_VIF_TAGC_ODMODE           0 // IF AGC OD MODE
#define TUNER_DVB_IF_AGC_MODE           0

#define DBG_TUNER(x)  // x

#define MAX_TUNER_DEV_NUM 2

// VideoIF = 7.0M
U16 VIF_A1_A2_SOS11_SOS12_B_Stereo_A2[16]=
{
 0x03C0,0x0628,0x0418,
 0x03C7,0x0628,0x0411,
 0x0143,0x0628,0x0200,0x06B0,0x0200,
 0x03C0,0x0628,0x0200,0x0418,0x0200
};

// VideoIF = 7.0M
U16 VIF_A1_A2_SOS11_SOS12_B_Mono_NICAM[16]=
{
 0x03C0,0x0628,0x0418,
 0x03C9,0x0628,0x040E,
 0x0143,0x0628,0x0200,0x06B0,0x0200,
 0x03C0,0x0628,0x0200,0x0418,0x0200
};

// VideoIF = 7.0M
U16 VIF_A1_A2_SOS11_SOS12_GH_Stereo_A2[16]=
{
 0x03C0,0x0628,0x0418,
 0x03C7,0x0628,0x0411,
 0x00B9,0x0628,0x0200,0x0740,0x0200,
 0x03C0,0x0628,0x0200,0x0418,0x0200
};

// VideoIF = 7.0M
U16 VIF_A1_A2_SOS11_SOS12_GH_Mono_NICAM[16]=
{
 0x03C0,0x0628,0x0418,
 0x03C9,0x0628,0x040E,
 0x00B9,0x0628,0x0200,0x0740,0x0200,
 0x03C0,0x0628,0x0200,0x0418,0x0200
};

// VideoIF = 8.0M
U16 VIF_A1_A2_SOS11_SOS12_DK1_Stereo_A2[16]=
{
 0x03C0,0x0628,0x0418,
 0x03B8,0x0628,0x0421,
 0x00B9,0x0628,0x0200,0x0740,0x0200,
 0x03C0,0x0628,0x0200,0x0418,0x0200
};

// VideoIF = 8.0M
U16 VIF_A1_A2_SOS11_SOS12_DK2_Stereo_A2[16]=
{
 0x03C0,0x0628,0x0418,
 0x03C7,0x0628,0x0411,
 0x00B9,0x0628,0x0200,0x0740,0x0200,
 0x03C0,0x0628,0x0200,0x0418,0x0200
};

// VideoIF = 8.0M
U16 VIF_A1_A2_SOS11_SOS12_DK3_Stereo_A2[16]=
{
 0x03C0,0x0628,0x0418,
 0x03A2,0x0628,0x0437,
 0x00B9,0x0628,0x0200,0x0740,0x0200,
 0x03C0,0x0628,0x0200,0x0418,0x0200
};

// VideoIF = 8.0M
U16 VIF_A1_A2_SOS11_SOS12_DK_Mono_NICAM[16]=
{
 0x03C0,0x0628,0x0418,
 0x03A7,0x0628,0x0432,
 0x00B9,0x0628,0x0200,0x0740,0x0200,
 0x03C0,0x0628,0x0200,0x0418,0x0200
};

// VideoIF = 7.5M
U16 VIF_A1_A2_SOS11_SOS12_I[16]=
{
 0x03C0,0x0628,0x0418,
 0x03CE,0x0628,0x040A,
 0x00B9,0x0628,0x0200,0x0740,0x0200,
 0x03C0,0x0628,0x0200,0x0418,0x0200
};

// VideoIF = 6.0M
U16 VIF_A1_A2_SOS11_SOS12_MN[16]=
{
 0x03C0,0x0628,0x0418,
 0x03C6,0x0628,0x0412,
 0x01C6,0x0628,0x0200,0x0627,0x0200,
 0x03C0,0x0628,0x0200,0x0418,0x0200
};

// VideoIF = 8.0M
U16 VIF_A1_A2_SOS11_SOS12_L[16]=
{
 0x03C0,0x0628,0x0418,
 0x03A7,0x0628,0x0432,
 0x00B9,0x0628,0x0200,0x0740,0x0200,
 0x03C0,0x0628,0x0200,0x0418,0x0200
};

// VideoIF = 8.0M
U16 VIF_A1_A2_SOS11_SOS12_LP[16]=
{
 0x03C0,0x0628,0x0418,
 0x03A7,0x0628,0x0432,
 0x00B9,0x0628,0x0200,0x0740,0x0200,
 0x03C0,0x0628,0x0200,0x0418,0x0200
};

    
typedef enum SI_Network
{
    SI_network_none        = 0x00,    /**< No network */
    SI_network_dvbt1       = 0x01,    /**< DVB-T (Terrestrial) */
    SI_network_dvbs1       = 0x02,    /**< DVB-S (Satellite)   */
    SI_network_dvbc        = 0x04,    /**< DVB-C (Cable) */
    SI_network_analog      = 0x08,    /**< Analog */
    SI_network_dvbt2       = 0x10,    /**< DVB-T2 (Terrestrial) */
    SI_network_dvbs2       = 0x20,    /**< DVB-S2 (Satellite)   */
    SI_network_dvbt        = 0x11,    /**< DVB-T, DVB-T2 (Terrestrial) */
    SI_network_dvbs        = 0x22,    /**< DVB-S, DVB-S2 (Satellite)   */
    SI_network_ip          = 0x40,    /**< IP network   */
    SI_network_fm          = 0x80     /**< Fm Radio    */
} SI_Network;

typedef enum SI_AnalogTVSystem
{
    si_tv_system_m,
    si_tv_system_bg,
    si_tv_system_i,
    si_tv_system_dk,
    si_tv_system_l,
    si_tv_system_lp,
    si_tv_system_invalid
}SI_AnalogTVSystem;

typedef enum
{
    E_Network_Type_DVBT =1,
    E_Network_Type_DVBC ,
    E_Network_Type_Analog_T ,
    E_Network_Type_Analog_C ,
    E_Network_Type_DVBT2, 
    E_Network_Type_ATSC, 
    E_Network_Type_ISDBT, 
    E_Network_Type_ISDBC, 
    E_Network_Type_DVBS, 
    E_Network_Type_DTMB,
    E_Network_Type_QAM_US,    
} Network_Type;


//-------------------------------------------------------------------------------------------------
//  Global Variables
//-------------------------------------------------------------------------------------------------
const char match_name[16]="Mstar-Si2151";

//--------------------------------------------------------------------------------------------------
// Forward declaration
//--------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Local Variables
//-------------------------------------------------------------------------------------------------
static L1_Si2151_Context *api = NULL;

static s_Tuner_dev_info *p_dev = NULL;
static s_Tuner_dev_info dev[MAX_TUNER_DEV_NUM] = 
{ 
  {E_TUNER_DTV_DVB_T_MODE, E_CLOSE, E_RF_CH_BAND_8MHz, 0,0,0,0,0,0,0,0},
  {E_TUNER_DTV_DVB_T_MODE, E_CLOSE, E_RF_CH_BAND_8MHz, 0,0,0,0,0,0,0,0},
};

//-------------------------------------------------------------------------------------------------
//  Debug Functions
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Local Functions
//-------------------------------------------------------------------------------------------------

static SI_AnalogTVSystem Atv_system_enum_conversion(EN_TUNER_MODE eMode,AUDIOSTANDARD_TYPE_ OtherMode)
{

    SI_AnalogTVSystem ret_atv_sys = si_tv_system_invalid;
    
    switch (eMode) 
    {
        case E_TUNER_ATV_PAL_MODE:
            {
                switch(OtherMode)
                {
                    case E_AUDIOSTANDARD_BG_:
                    case E_AUDIOSTANDARD_BG_A2_:
                    case E_AUDIOSTANDARD_BG_NICAM_:
                        ret_atv_sys = si_tv_system_bg;
                        break;
                    case E_AUDIOSTANDARD_I_:
                        ret_atv_sys = si_tv_system_i;
                        break;
                    case E_AUDIOSTANDARD_DK_:
                    case E_AUDIOSTANDARD_DK1_A2_:
                    case E_AUDIOSTANDARD_DK2_A2_:
                    case E_AUDIOSTANDARD_DK3_A2_:  
                    case E_AUDIOSTANDARD_DK_NICAM_:
                        ret_atv_sys = si_tv_system_dk;
                        break;
                    case E_AUDIOSTANDARD_L_:
                        ret_atv_sys = si_tv_system_l;
                        break;                        
                    case E_AUDIOSTANDARD_M_:
                    case E_AUDIOSTANDARD_M_BTSC_:   
                    case E_AUDIOSTANDARD_M_A2_:
                    case E_AUDIOSTANDARD_M_EIA_J_:
                        ret_atv_sys = si_tv_system_m;
                        break;                            
                    case E_AUDIOSTANDARD_NOTSTANDARD_:
                    default:
                        ret_atv_sys = si_tv_system_dk;
                        break;
                }
            }
            break;    
        case E_TUNER_ATV_SECAM_L_PRIME_MODE:
            ret_atv_sys = si_tv_system_lp;
            break;
//        case E_TUNER_ATV_SECAM_L_MODE:
//            ret_atv_sys = si_tv_system_l;
//            break;            
        case E_TUNER_ATV_NTSC_MODE:
            ret_atv_sys = si_tv_system_m;
            break;
        case E_TUNER_DTV_ISDB_MODE:
        case E_TUNER_DTV_DVB_T_MODE:
        case E_TUNER_DTV_DVB_C_MODE:
        case E_TUNER_DTV_DVB_S_MODE:
        case E_TUNER_DTV_DTMB_MODE:
        case E_TUNER_DTV_ATSC_MODE:           
        case E_TUNER_DTV_DVB_T2_MODE:
        default:
            ret_atv_sys = si_tv_system_invalid;
            break;
    }

    return ret_atv_sys;
}

static Network_Type Dtv_system_enum_conversion(EN_TUNER_MODE eMode)
{
    Network_Type ret_dtv_sys = E_Network_Type_ISDBT;

    switch (eMode) 
    {
        case E_TUNER_DTV_ISDB_MODE:
            ret_dtv_sys = E_Network_Type_ISDBT;
            break;
        case E_TUNER_DTV_DVB_T_MODE:
            ret_dtv_sys = E_Network_Type_DVBT;
            break;            
        case E_TUNER_DTV_DVB_C_MODE:
            ret_dtv_sys = E_Network_Type_DVBC;
            break;            
        case E_TUNER_DTV_DVB_S_MODE:
            ret_dtv_sys = E_Network_Type_DVBS;
            break;            
        case E_TUNER_DTV_DTMB_MODE:
            ret_dtv_sys = E_Network_Type_DTMB;
            break;            
        case E_TUNER_DTV_ATSC_MODE:
            ret_dtv_sys = E_Network_Type_ATSC;
            break;            
        case E_TUNER_DTV_DVB_T2_MODE:
            ret_dtv_sys = E_Network_Type_DVBT2;
            break;
#if 0            
        case E_TUNER_DTV_QAM_US_MODE:
            ret_dtv_sys = E_Network_Type_QAM_US;
            break;
#endif
        case E_TUNER_ATV_PAL_MODE:   
        case E_TUNER_ATV_SECAM_L_PRIME_MODE:
        case E_TUNER_ATV_NTSC_MODE:            
        default:
            ret_dtv_sys = E_Network_Type_DVBT;
            break;
    }
    return ret_dtv_sys;
}


static int Si2151_GetRSSILevel(S16 *strength_100dBm)
{
    int return_code = 0;
    if ((return_code=Si2151_L1_TUNER_STATUS(api))!=0) {
        mcSHOW_HW_MSG((" [Silabs]: ERROR_READING_COMMAND Si2151_TUNER_STATUS\n"));
        return return_code;
    }
    *strength_100dBm=100*(S16)(api->rsp->tuner_status.rssi);    
    return TRUE;
}


/* Setup properties to switch standards. */
static void SetIfDemod(RF_CHANNEL_BANDWIDTH eBandWidth, Network_Type eNetworktype, SI_AnalogTVSystem TV_SYS)
{
    // set a global here to save the video standard,  because it's not always available from the caller.
    if(TV_SYS == si_tv_system_invalid)
    {
        switch (eNetworktype)
        {
           case E_Network_Type_DVBT:
                api->prop->dtv_mode.modulation = Si2151_DTV_MODE_PROP_MODULATION_DVBT;
                if(eBandWidth == E_RF_CH_BAND_6MHz)
                    api->prop->dtv_mode.bw = Si2151_DTV_MODE_PROP_BW_BW_6MHZ;
                else if (eBandWidth == E_RF_CH_BAND_7MHz)
                    api->prop->dtv_mode.bw = Si2151_DTV_MODE_PROP_BW_BW_7MHZ;
                else
                    api->prop->dtv_mode.bw = Si2151_DTV_MODE_PROP_BW_BW_8MHZ;

                api->prop->dtv_mode.invert_spectrum = Si2151_DTV_MODE_PROP_INVERT_SPECTRUM_INVERTED;

                if (Si2151_L1_SetProperty2(api, Si2151_DTV_MODE_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_DTV_MODE_PROP\n"));
                }
                api->prop->dtv_agc_speed.if_agc_speed = Si2151_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO;
                api->prop->dtv_agc_speed.agc_decim = Si2151_DTV_AGC_SPEED_PROP_AGC_DECIM_OFF;
                if (Si2151_L1_SetProperty2(api, Si2151_DTV_AGC_SPEED_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_DTV_AGC_SPEED_PROP\n"));
                }
                api->prop->dtv_initial_agc_speed_period.period = 0;
                if (Si2151_L1_SetProperty2(api, Si2151_DTV_INITIAL_AGC_SPEED_PERIOD_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_DTV_INITIAL_AGC_SPEED_PERIOD_PROP\n"));
                }
                /* AMP=17 to get IF_AGC=1.24Vrms in DVB-T when AMP is controlled by demod AGC (DTV_AGC_SOURCE=DLIF_AGC_3DB) */
                api->prop->dtv_lif_out.amp =20; //wayne
                printf("***[SetIfDemod_DVB-T] dtv_lif_out.amp = %d ",api->prop->dtv_lif_out.amp);
                if (Si2151_L1_SetProperty2(api, Si2151_DTV_LIF_OUT_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_DTV_LIF_OUT_PROP\n"));
                }
                api->prop->dtv_lif_freq.offset =C_Si2151_IF_FREQUENCY;
                if (Si2151_L1_SetProperty2(api, Si2151_DTV_LIF_FREQ_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_DTV_LIF_FREQ_PROP\n"));
                }
                break;
           case E_Network_Type_DVBT2:
                api->prop->dtv_mode.modulation = Si2151_DTV_MODE_PROP_MODULATION_DVBT;
                if(eBandWidth == E_RF_CH_BAND_8MHz)
                    api->prop->dtv_mode.bw = Si2151_DTV_MODE_PROP_BW_BW_8MHZ;
                else if (eBandWidth == E_RF_CH_BAND_7MHz)
                    api->prop->dtv_mode.bw = Si2151_DTV_MODE_PROP_BW_BW_7MHZ;
                else
                    api->prop->dtv_mode.bw = Si2151_DTV_MODE_PROP_BW_BW_6MHZ;
                api->prop->dtv_mode.invert_spectrum = Si2151_DTV_MODE_PROP_INVERT_SPECTRUM_INVERTED;

                if (Si2151_L1_SetProperty2(api, Si2151_DTV_MODE_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_DTV_MODE_PROP\n"));
                }
                api->prop->dtv_agc_speed.if_agc_speed = Si2151_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_39;
                api->prop->dtv_agc_speed.agc_decim = Si2151_DTV_AGC_SPEED_PROP_AGC_DECIM_4;
                if (Si2151_L1_SetProperty2(api, Si2151_DTV_AGC_SPEED_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_DTV_AGC_SPEED_PROP\n"));
                }
                api->prop->dtv_initial_agc_speed_period.period = 210;
                if (Si2151_L1_SetProperty2(api, Si2151_DTV_INITIAL_AGC_SPEED_PERIOD_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_DTV_INITIAL_AGC_SPEED_PERIOD_PROP\n"));
                }
                /* AMP=32 to get IF_AGC=1.24Vrms in DVB-T2 when AMP is controlled by demod AGC (DTV_AGC_SOURCE=DLIF_AGC_3DB) */
                api->prop->dtv_lif_out.amp =25;
                printf("***[SetIfDemod_DVB-T2] dtv_lif_out.amp = %d ",api->prop->dtv_lif_out.amp);
                if (Si2151_L1_SetProperty2(api, Si2151_DTV_LIF_OUT_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_DTV_LIF_OUT_PROP\n"));
                }
                api->prop->dtv_lif_freq.offset =C_Si2151_IF_FREQUENCY;
                if (Si2151_L1_SetProperty2(api, Si2151_DTV_LIF_FREQ_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_DTV_LIF_FREQ_PROP\n"));
                }
                break;
           case E_Network_Type_DVBC:
                api->prop->dtv_mode.modulation = Si2151_DTV_MODE_PROP_MODULATION_DVBC;
                api->prop->dtv_mode.bw = Si2151_DTV_MODE_PROP_BW_BW_8MHZ;
                api->prop->dtv_mode.invert_spectrum = Si2151_ATV_VIDEO_MODE_PROP_INVERT_SPECTRUM_INVERTED;

                if (Si2151_L1_SetProperty2(api, Si2151_DTV_MODE_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_DTV_MODE_PROP\n"));
                }
                api->prop->dtv_agc_speed.if_agc_speed = Si2151_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO;
                api->prop->dtv_agc_speed.agc_decim = Si2151_DTV_AGC_SPEED_PROP_AGC_DECIM_OFF;
                if (Si2151_L1_SetProperty2(api, Si2151_DTV_AGC_SPEED_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_DTV_AGC_SPEED_PROP\n"));
                }
                api->prop->dtv_initial_agc_speed_period.period = 0;
                if (Si2151_L1_SetProperty2(api, Si2151_DTV_INITIAL_AGC_SPEED_PERIOD_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_DTV_INITIAL_AGC_SPEED_PERIOD_PROP\n"));
                }
                /* AMP=14 to get IF_AGC=1.20Vrms in DVB-C when AMP is controlled by demod AGC (DTV_AGC_SOURCE=DLIF_AGC_3DB) */
                api->prop->dtv_lif_out.amp =20;	
                printf("***[SetIfDemod_DVB-C] dtv_lif_out.amp = %d ",api->prop->dtv_lif_out.amp);

                if (Si2151_L1_SetProperty2(api, Si2151_DTV_LIF_OUT_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_DTV_LIF_OUT_PROP\n"));
                }
                api->prop->dtv_lif_freq.offset =C_Si2151_IF_FREQUENCY;
                if (Si2151_L1_SetProperty2(api, Si2151_DTV_LIF_FREQ_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_DTV_LIF_FREQ_PROP\n"));
                }
                break;
           case E_Network_Type_ISDBT:
                api->prop->dtv_mode.modulation = Si2151_DTV_MODE_PROP_MODULATION_ISDBT;
                api->prop->dtv_mode.bw = Si2151_DTV_MODE_PROP_BW_BW_6MHZ;
                api->prop->dtv_mode.invert_spectrum = Si2151_DTV_MODE_PROP_INVERT_SPECTRUM_INVERTED;
                if (Si2151_L1_SetProperty2(api, Si2151_DTV_MODE_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_DTV_MODE_PROP\n"));
                }
                api->prop->dtv_agc_speed.if_agc_speed = Si2151_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO;
                api->prop->dtv_agc_speed.agc_decim = Si2151_DTV_AGC_SPEED_PROP_AGC_DECIM_OFF;
                if (Si2151_L1_SetProperty2(api, Si2151_DTV_AGC_SPEED_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_DTV_AGC_SPEED_PROP\n"));
                }
                api->prop->dtv_initial_agc_speed_period.period = 0;
                if (Si2151_L1_SetProperty2(api, Si2151_DTV_INITIAL_AGC_SPEED_PERIOD_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_DTV_INITIAL_AGC_SPEED_PERIOD_PROP\n"));
                }
                /* AMP=55 to get IF_AGC 1.0v in MSB1400 on 149B-C01A when AMP is controlled by demod AGC (DTV_AGC_SOURCE=DLIF_AGC_3DB) */
                api->prop->dtv_lif_out.amp =37;
                printf("***[SetIfDemod_ISDBT] dtv_lif_out.amp = %d ",api->prop->dtv_lif_out.amp);
                if (Si2151_L1_SetProperty2(api, Si2151_DTV_LIF_OUT_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_DTV_LIF_OUT_PROP\n"));
                }
                
                api->prop->dtv_lif_freq.offset =C_Si2151_IF_FREQUENCY;
                if (Si2151_L1_SetProperty2(api, Si2151_DTV_LIF_FREQ_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_DTV_LIF_FREQ_PROP\n"));
                }
                break;
           case E_Network_Type_ATSC:
                api->prop->dtv_mode.modulation = Si2151_DTV_MODE_PROP_MODULATION_ATSC;
                api->prop->dtv_mode.bw = Si2151_DTV_MODE_PROP_BW_BW_6MHZ;
                api->prop->dtv_mode.invert_spectrum = Si2151_DTV_MODE_PROP_INVERT_SPECTRUM_NORMAL;

                if (Si2151_L1_SetProperty2(api, Si2151_DTV_MODE_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_DTV_MODE_PROP\n"));
                }
                api->prop->dtv_agc_speed.if_agc_speed = Si2151_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO;
                api->prop->dtv_agc_speed.agc_decim = Si2151_DTV_AGC_SPEED_PROP_AGC_DECIM_OFF;
                if (Si2151_L1_SetProperty2(api, Si2151_DTV_AGC_SPEED_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_DTV_AGC_SPEED_PROP\n"));
                }
                api->prop->dtv_initial_agc_speed_period.period = 0;
                if (Si2151_L1_SetProperty2(api, Si2151_DTV_INITIAL_AGC_SPEED_PERIOD_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_DTV_INITIAL_AGC_SPEED_PERIOD_PROP\n"));
                }
                /* AMP=17 to get IF_AGC=1.24Vrms in DVB-T when AMP is controlled by demod AGC (DTV_AGC_SOURCE=DLIF_AGC_3DB) */
                api->prop->dtv_lif_out.amp =20;
                printf("***[SetIfDemod_ATSC] dtv_lif_out.amp = %d ",api->prop->dtv_lif_out.amp);
                
                if (Si2151_L1_SetProperty2(api, Si2151_DTV_LIF_OUT_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_DTV_LIF_OUT_PROP\n"));
                }
                api->prop->dtv_lif_freq.offset = C_Si2151_IF_FREQUENCY;
                if (Si2151_L1_SetProperty2(api, Si2151_DTV_LIF_FREQ_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_DTV_LIF_FREQ_PROP\n"));
                }
                 api->prop->tuner_return_loss.mode = Si2151_TUNER_RETURN_LOSS_PROP_MODE_TERRESTRIAL;
                 if (Si2151_L1_SetProperty2(api, Si2151_TUNER_RETURN_LOSS_PROP_CODE) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_TUNER_RETURN_LOSS_PROP_CODE\n"));
                }

                api->prop->dtv_pga_limits.max = 56;
                api->prop->dtv_pga_limits.min = 24;
                if (Si2151_L1_SetProperty2(api,Si2151_DTV_PGA_LIMITS_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_DTV_PGA_LIMITS_PROP\n"));
                }

                break;
           case E_Network_Type_QAM_US:
                api->prop->dtv_mode.modulation = Si2151_DTV_MODE_PROP_MODULATION_QAM_US;
                api->prop->dtv_mode.bw = Si2151_DTV_MODE_PROP_BW_BW_6MHZ;
                api->prop->dtv_mode.invert_spectrum = Si2151_DTV_MODE_PROP_INVERT_SPECTRUM_NORMAL;

                if (Si2151_L1_SetProperty2(api, Si2151_DTV_MODE_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_DTV_MODE_PROP\n"));
                }
                api->prop->dtv_agc_speed.if_agc_speed = Si2151_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO;
                api->prop->dtv_agc_speed.agc_decim = Si2151_DTV_AGC_SPEED_PROP_AGC_DECIM_OFF;
                if (Si2151_L1_SetProperty2(api, Si2151_DTV_AGC_SPEED_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_DTV_AGC_SPEED_PROP\n"));
                }
                api->prop->dtv_initial_agc_speed_period.period = 0;
                if (Si2151_L1_SetProperty2(api, Si2151_DTV_INITIAL_AGC_SPEED_PERIOD_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_DTV_INITIAL_AGC_SPEED_PERIOD_PROP\n"));
                }
                /* AMP=17 to get IF_AGC=1.24Vrms in DVB-T when AMP is controlled by demod AGC (DTV_AGC_SOURCE=DLIF_AGC_3DB) */
                api->prop->dtv_lif_out.amp =20;
                printf("***[SetIfDemod_QAM_US] dtv_lif_out.amp = %d ",api->prop->dtv_lif_out.amp);

                if (Si2151_L1_SetProperty2(api, Si2151_DTV_LIF_OUT_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_DTV_LIF_OUT_PROP\n"));
                }
                api->prop->dtv_lif_freq.offset = C_Si2151_IF_FREQUENCY;
                if (Si2151_L1_SetProperty2(api, Si2151_DTV_LIF_FREQ_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_DTV_LIF_FREQ_PROP\n"));
                }

                api->prop->tuner_return_loss.mode = Si2151_TUNER_RETURN_LOSS_PROP_MODE_TERRESTRIAL;
                 if (Si2151_L1_SetProperty2(api, Si2151_TUNER_RETURN_LOSS_PROP_CODE) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_TUNER_RETURN_LOSS_PROP_CODE\n"));
                }
                api->prop->dtv_pga_limits.max = 56;
                api->prop->dtv_pga_limits.min = 24;
                if (Si2151_L1_SetProperty2(api,Si2151_DTV_PGA_LIMITS_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_DTV_PGA_LIMITS_PROP\n"));
                }
                break;                
           case E_Network_Type_DTMB:
                api->prop->dtv_mode.modulation = Si2151_DTV_MODE_PROP_MODULATION_DTMB;
                api->prop->dtv_mode.bw = Si2151_DTV_MODE_PROP_BW_BW_8MHZ;
                api->prop->dtv_mode.invert_spectrum = Si2151_DTV_MODE_PROP_INVERT_SPECTRUM_INVERTED;
                if (Si2151_L1_SetProperty2(api, Si2151_DTV_MODE_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_DTV_MODE_PROP\n"));
                }
                api->prop->dtv_agc_speed.if_agc_speed = Si2151_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO;
                api->prop->dtv_agc_speed.agc_decim = Si2151_DTV_AGC_SPEED_PROP_AGC_DECIM_OFF;
                if (Si2151_L1_SetProperty2(api, Si2151_DTV_AGC_SPEED_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_DTV_AGC_SPEED_PROP\n"));
                }
                api->prop->dtv_initial_agc_speed_period.period = 0;
                if (Si2151_L1_SetProperty2(api, Si2151_DTV_INITIAL_AGC_SPEED_PERIOD_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_DTV_INITIAL_AGC_SPEED_PERIOD_PROP\n"));
                }
                /* AMP=55 to get IF_AGC 1.0v in MSB1400 on 149B-C01A when AMP is controlled by demod AGC (DTV_AGC_SOURCE=DLIF_AGC_3DB) */
                api->prop->dtv_lif_out.amp =27;
                printf("***[SetIfDemod_DTMB] dtv_lif_out.amp = %d ",api->prop->dtv_lif_out.amp);

                if (Si2151_L1_SetProperty2(api, Si2151_DTV_LIF_OUT_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_DTV_LIF_OUT_PROP\n"));
                }
                
                api->prop->dtv_lif_freq.offset =C_Si2151_IF_FREQUENCY;
                if (Si2151_L1_SetProperty2(api, Si2151_DTV_LIF_FREQ_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_DTV_LIF_FREQ_PROP\n"));
                }
                break;    
           case E_Network_Type_ISDBC:    
           case E_Network_Type_Analog_T:
           case E_Network_Type_Analog_C:
           case E_Network_Type_DVBS:   
           default:
                printf("[Error]%s,%s,%d\n",__FILE__,__FUNCTION__,__LINE__);
                break;                
        }
    }
    else
    {
        switch (TV_SYS)
        {
            case si_tv_system_bg:                
                api->prop->atv_video_mode.invert_spectrum = Si2151_ATV_VIDEO_MODE_PROP_INVERT_SPECTRUM_INVERTED;
                if (Si2151_L1_SetProperty2(api, Si2151_ATV_VIDEO_MODE_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_ATV_VIDEO_MODE_PROP\n"));
                }
                break;
            case si_tv_system_dk:
                api->prop->atv_video_mode.video_sys = Si2151_ATV_VIDEO_MODE_PROP_VIDEO_SYS_DK;
                api->prop->atv_video_mode.invert_spectrum = Si2151_ATV_VIDEO_MODE_PROP_INVERT_SPECTRUM_INVERTED;
                if (Si2151_L1_SetProperty2(api, Si2151_ATV_VIDEO_MODE_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_ATV_VIDEO_MODE_PROP\n"));
                }
                api->prop->atv_lif_freq.offset = C_Si2151_IF_CENTER_DK;
                if (Si2151_L1_SetProperty2(api, Si2151_ATV_LIF_FREQ_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_ATV_LIF_FREQ_PROP\n"));
                }
                break;
            case si_tv_system_i:
                api->prop->atv_video_mode.video_sys = Si2151_ATV_VIDEO_MODE_PROP_VIDEO_SYS_I;
                api->prop->atv_video_mode.invert_spectrum = Si2151_ATV_VIDEO_MODE_PROP_INVERT_SPECTRUM_INVERTED;
                if (Si2151_L1_SetProperty2(api, Si2151_ATV_VIDEO_MODE_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_ATV_VIDEO_MODE_PROP\n"));
                }
                api->prop->atv_lif_freq.offset = C_Si2151_IF_CENTER_I;
                if (Si2151_L1_SetProperty2(api, Si2151_ATV_LIF_FREQ_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_ATV_LIF_FREQ_PROP\n"));
                }
                break;
            case si_tv_system_m:
                api->prop->atv_video_mode.video_sys = Si2151_ATV_VIDEO_MODE_PROP_VIDEO_SYS_M;
                api->prop->atv_video_mode.invert_spectrum = Si2151_ATV_VIDEO_MODE_PROP_INVERT_SPECTRUM_INVERTED;
                if (Si2151_L1_SetProperty2(api, Si2151_ATV_VIDEO_MODE_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_ATV_VIDEO_MODE_PROP\n"));
                }
                api->prop->atv_lif_freq.offset = C_Si2151_IF_CENTER_M;
                if (Si2151_L1_SetProperty2(api, Si2151_ATV_LIF_FREQ_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_ATV_LIF_FREQ_PROP\n"));
                }
                break;
            case si_tv_system_l:
                api->prop->atv_video_mode.video_sys = Si2151_ATV_VIDEO_MODE_PROP_VIDEO_SYS_L;
                api->prop->atv_video_mode.invert_spectrum = Si2151_ATV_VIDEO_MODE_PROP_INVERT_SPECTRUM_INVERTED;
                if (Si2151_L1_SetProperty2(api, Si2151_ATV_VIDEO_MODE_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_ATV_VIDEO_MODE_PROP\n"));
                }
                api->prop->atv_lif_freq.offset = C_Si2151_IF_CENTER_L;
                if (Si2151_L1_SetProperty2(api, Si2151_ATV_LIF_FREQ_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_ATV_LIF_FREQ_PROP\n"));
                }
                api->prop->atv_lif_out.offset = Si2151_ATV_LIF_OUT_PROP_OFFSET_DEFAULT;
                break;
            case si_tv_system_lp:
                api->prop->atv_video_mode.video_sys = Si2151_ATV_VIDEO_MODE_PROP_VIDEO_SYS_LP;
                api->prop->atv_video_mode.invert_spectrum = Si2151_ATV_VIDEO_MODE_PROP_INVERT_SPECTRUM_INVERTED;
                if (Si2151_L1_SetProperty2(api, Si2151_ATV_VIDEO_MODE_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_ATV_VIDEO_MODE_PROP\n"));
                }
                api->prop->atv_lif_freq.offset = C_Si2151_IF_CENTER_L1;
                if (Si2151_L1_SetProperty2(api, Si2151_ATV_LIF_FREQ_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_ATV_LIF_FREQ_PROP\n"));
                }
                break;
            case si_tv_system_invalid:
            default:
                break;
        }
    }
}

static U32 Si2151_GetDefaultIF(U32 Freq, SI_AnalogTVSystem TV_SYS)
{
    U32 offset=0;
    switch (TV_SYS)
    {
        case si_tv_system_bg:
            if (Freq < 300000)
            {
                offset = C_Si2151_IF_CENTER_B;
                break;
            }
            if (Freq >= 300000)
            {
                offset = C_Si2151_IF_CENTER_GH;
                break;
            }
            break;
        case si_tv_system_dk:
            offset = C_Si2151_IF_CENTER_DK;
            break;
        case si_tv_system_i:
            offset = C_Si2151_IF_CENTER_I;
            break;
        case si_tv_system_m:
            offset = C_Si2151_IF_CENTER_M;
            break;
        case si_tv_system_l:
            offset = C_Si2151_IF_CENTER_L;
            break;
        case si_tv_system_lp:
            offset = C_Si2151_IF_CENTER_L1;
            break;
        case si_tv_system_invalid:
        default:
            printf("[Error]%s, %s, %d\n",__FILE__,__FUNCTION__,__LINE__);
            break;
    }
    return offset;
}
/*
int mdev_ATV_GetSignalStrength_Si2151(U16 *strength)
{
    float Prel = 0.0;
    float f_ssi = 0;
    float ch_power_db_a=0;
    float ch_power_db=0;

    ch_power_db_a = ch_power_db_a;
    Prel = Prel;
     
    ch_power_db = Si2151_GetRSSILevel(&ch_power_db);
    //the range of Si2151 strength if -5 to -75
    if ( ch_power_db < -75)
    {
        ch_power_db=-75;
    }
    else if ( ch_power_db >-5)
    {
        ch_power_db=-5;
    }
    f_ssi=(((-4)-(ch_power_db))*100)/72;
    *strength = (U16)(100-f_ssi);
    mcSHOW_HW_MSG((">>> SSI_CH_PWR(dB) = %f , Score = %f<<<\n", ch_power_db, f_ssi));
    mcSHOW_HW_MSG((">>> SSI = %d <<<\n", (int)*strength));
    return TRUE;
}
*/
static int device_tuner_si_2151_init(void)
{
    int retb=FALSE, error;

    if (NULL == api) {
        api = (L1_Si2151_Context *)malloc(sizeof(L1_Si2151_Context));
    }
    /* Software Init */
    Si2151_L1_API_Init(api,C_Si2151_LO_ADDRESS);
    /*** below power up setting is for successfully excuting Si2151_LoadFirmware_16 */
    api->cmd->power_up.clock_mode =  Si2151_POWER_UP_CMD_CLOCK_MODE_XTAL;
    api->cmd->power_up.en_xout    =  Si2151_POWER_UP_CMD_EN_XOUT_EN_XOUT;
    if (Si2151_Init(api) != 0 )
    {
        printf("\n");
        printf("ERROR ----------------------------------\n");
        printf("ERROR initializing the Si2151!\n");
        printf("ERROR ----------------------------------\n");
        printf("\n");
        retb = FALSE;
    }
    else
    {
        /*** Enable external AGC1 control pin*/
        error=Si2151_L1_CONFIG_PINS (api,
                                                             Si2151_CONFIG_PINS_CMD_GPIO1_MODE_NO_CHANGE,
                                                             Si2151_CONFIG_PINS_CMD_GPIO1_READ_DO_NOT_READ,
                                                             Si2151_CONFIG_PINS_CMD_GPIO2_MODE_NO_CHANGE,
                                                             Si2151_CONFIG_PINS_CMD_GPIO2_READ_DO_NOT_READ,
                                                             Si2151_CONFIG_PINS_CMD_AGC1_MODE_ATV_DTV_AGC,
                                                             Si2151_CONFIG_PINS_CMD_AGC1_READ_DO_NOT_READ,
                                                             Si2151_CONFIG_PINS_CMD_AGC2_MODE_NO_CHANGE,
                                                             Si2151_CONFIG_PINS_CMD_AGC2_READ_DO_NOT_READ,
                                                             Si2151_CONFIG_PINS_CMD_XOUT_MODE_NO_CHANGE);
        printf ("Si2151_L1_CONFIG_PINS, ATV_DTV_AGC1, error 0x%02x: %s\n", error, Si2151_L1_API_ERROR_TEXT(error));
        retb = TRUE;
    }
    return retb;
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
    int retb = FALSE;
    U32 freqHz = 0;
    int freq_offset=0;
    U32 timeout = 0;
    S16 s16Finetune = 0;
    SI_AnalogTVSystem TV_SYS = si_tv_system_invalid;    
    U8 previous_video_sys = 0;

    TUNER_PRINT("%s is invoked\n", __FUNCTION__);
    DBG_TUNER(printf("%s, %d, Freq=%d Khz, eBand=%d, mode=%d, otherMode=%d\n",__FUNCTION__,__LINE__,u32FreqKHz,eBand,eMode,otherMode);)
    
    eBand = eBand;

    p_dev=&(dev[minor]);

    if (p_dev->e_status != E_WORKING)
    {
        printf("[Error]%s,%d\n",__FILE__,__LINE__);
        return FALSE;
    }

    p_dev->e_std = E_TUNER_ATV_PAL_MODE;
    p_dev->u32_freq = u32FreqKHz;
    p_dev->u32_eband_bandwidth = eBand;
    p_dev->u32_eMode = eMode;
    p_dev->u8_otherMode = otherMode;

    previous_video_sys = api->prop->atv_video_mode.video_sys;

    TV_SYS = Atv_system_enum_conversion(eMode,(AUDIOSTANDARD_TYPE_)otherMode);

    DBG_TUNER(printf ("ATV_SetTune freq = %d; SYS = %d...........\n", u32FreqKHz, TV_SYS);)

    if(s16Finetune!=0)
    {
        u32FreqKHz -= (s16Finetune*625/10); //re-calcuate original freq w/o finetune
        //for example, current frequency is 224250KHz, if AnalogFinetune is set to +1(+62.5KHz), that means middleware will call u32FreqKHz:224313KHz(224250+63) Finetune:1
    }

    /* set the following properties back to their defaults in case it was optimized for DTMB application in DTV_SetTune()*/
    api->prop->tuner_return_loss_optimize.config               = Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_CONFIG_DISABLE;
    api->prop->tuner_return_loss_optimize_2.thld               =    31; /* (default    31) */
    api->prop->tuner_return_loss_optimize_2.window             =     0; /* (default     0) */
    api->prop->tuner_return_loss_optimize_2.engagement_delay   =    15; /* (default    15) */
    api->prop->tuner_tf1_boundary_offset.tf1_boundary_offset   =     0;        

    api->prop->tuner_return_loss_optimize.thld                 =     0;
    api->prop->tuner_return_loss_optimize.engagement_delay     =     7;
    api->prop->tuner_return_loss_optimize.disengagement_delay  =    10;

    if (Si2151_L1_SetProperty2(api, Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP) != 0)
    {
        mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP\n"));
    }
    if (Si2151_L1_SetProperty2(api, Si2151_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP) != 0)
    {
        mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP\n"));
    }
    if (Si2151_L1_SetProperty2(api, Si2151_TUNER_TF1_BOUNDARY_OFFSET_PROP) != 0)
    {
        mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_TUNER_TF1_BOUNDARY_OFFSET_PROP\n"));
    }

    /* do not go through SetIfdemod if same TV_SYS is used but only frequency is changed*/
    switch (TV_SYS)
    {
        case si_tv_system_bg:                
            if(u32FreqKHz < 300000)
            {
                freqHz = (u32FreqKHz * 1000) + C_Si2151_PF_TO_CF_SHIFT_B*1000;
            }
            else
            {
                freqHz = (u32FreqKHz * 1000) + C_Si2151_PF_TO_CF_SHIFT_G*1000;
            }
            api->prop->tuner_lo_injection.band_1      = Si2151_TUNER_LO_INJECTION_PROP_BAND_1_HIGH_SIDE;
            api->prop->tuner_lo_injection.band_2      = Si2151_TUNER_LO_INJECTION_PROP_BAND_2_LOW_SIDE;
            api->prop->tuner_lo_injection.band_3      = Si2151_TUNER_LO_INJECTION_PROP_BAND_3_LOW_SIDE;
            if (Si2151_L1_SetProperty2(api,Si2151_TUNER_LO_INJECTION_PROP) != 0)
            {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_TUNER_LO_INJECTION_PROP\n"));
            }
            if (u32FreqKHz < 300000 && previous_video_sys != Si2151_ATV_VIDEO_MODE_PROP_VIDEO_SYS_B )
            {
                api->prop->atv_video_mode.video_sys=Si2151_ATV_VIDEO_MODE_PROP_VIDEO_SYS_B;
                api->prop->atv_lif_freq.offset = C_Si2151_IF_CENTER_B;
                if (Si2151_L1_SetProperty2(api, Si2151_ATV_LIF_FREQ_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_ATV_LIF_FREQ_PROP\n"));
                }                     
                SetIfDemod(E_RF_CH_BAND_8MHz, E_Network_Type_Analog_T, TV_SYS);
                break;
            }
            if (u32FreqKHz >= 300000 && previous_video_sys != Si2151_ATV_VIDEO_MODE_PROP_VIDEO_SYS_GH)
            {
                api->prop->atv_video_mode.video_sys=Si2151_ATV_VIDEO_MODE_PROP_VIDEO_SYS_GH;
                api->prop->atv_lif_freq.offset = C_Si2151_IF_CENTER_GH;
                if (Si2151_L1_SetProperty2(api, Si2151_ATV_LIF_FREQ_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_ATV_LIF_FREQ_PROP\n"));
                }
                SetIfDemod(E_RF_CH_BAND_8MHz, E_Network_Type_Analog_T, TV_SYS);
                break;
            }
            break;
        case si_tv_system_dk:
            freqHz = (u32FreqKHz * 1000) + C_Si2151_PF_TO_CF_SHIFT_DK*1000;
            api->prop->tuner_lo_injection.band_1      = Si2151_TUNER_LO_INJECTION_PROP_BAND_1_HIGH_SIDE;
            api->prop->tuner_lo_injection.band_2      = Si2151_TUNER_LO_INJECTION_PROP_BAND_2_HIGH_SIDE;
            api->prop->tuner_lo_injection.band_3      = Si2151_TUNER_LO_INJECTION_PROP_BAND_3_HIGH_SIDE;
            if (Si2151_L1_SetProperty2(api,Si2151_TUNER_LO_INJECTION_PROP) != 0)
            {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_TUNER_LO_INJECTION_PROP\n"));
            }
            if (previous_video_sys != Si2151_ATV_VIDEO_MODE_PROP_VIDEO_SYS_DK)
            {
                SetIfDemod(E_RF_CH_BAND_8MHz, E_Network_Type_Analog_T, TV_SYS);
            }
            break;
        case si_tv_system_i:
            freqHz = (u32FreqKHz * 1000) + C_Si2151_PF_TO_CF_SHIFT_I*1000;
            api->prop->tuner_lo_injection.band_1      = Si2151_TUNER_LO_INJECTION_PROP_BAND_1_HIGH_SIDE;
            api->prop->tuner_lo_injection.band_2      = Si2151_TUNER_LO_INJECTION_PROP_BAND_2_HIGH_SIDE;
            api->prop->tuner_lo_injection.band_3      = Si2151_TUNER_LO_INJECTION_PROP_BAND_3_HIGH_SIDE;
            if (Si2151_L1_SetProperty2(api,Si2151_TUNER_LO_INJECTION_PROP) != 0)
            {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_TUNER_LO_INJECTION_PROP\n"));
            }
            if (previous_video_sys != Si2151_ATV_VIDEO_MODE_PROP_VIDEO_SYS_I)
            {
                SetIfDemod(E_RF_CH_BAND_8MHz, E_Network_Type_Analog_T, TV_SYS);
            }
            break;
        case si_tv_system_m:
            freqHz = (u32FreqKHz * 1000) + C_Si2151_PF_TO_CF_SHIFT_M*1000;
            api->prop->tuner_lo_injection.band_1      = Si2151_TUNER_LO_INJECTION_PROP_BAND_1_HIGH_SIDE;
            api->prop->tuner_lo_injection.band_2      = Si2151_TUNER_LO_INJECTION_PROP_BAND_2_HIGH_SIDE;
            api->prop->tuner_lo_injection.band_3      = Si2151_TUNER_LO_INJECTION_PROP_BAND_3_HIGH_SIDE;
            if (Si2151_L1_SetProperty2(api,Si2151_TUNER_LO_INJECTION_PROP) != 0)
            {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_TUNER_LO_INJECTION_PROP\n"));
            }
            if (previous_video_sys != Si2151_ATV_VIDEO_MODE_PROP_VIDEO_SYS_M)
            {
                SetIfDemod(E_RF_CH_BAND_8MHz, E_Network_Type_Analog_T, TV_SYS);
            }
            break;
        case si_tv_system_l:
            freqHz = (u32FreqKHz * 1000) + C_Si2151_PF_TO_CF_SHIFT_L*1000;
            api->prop->tuner_lo_injection.band_1      = Si2151_TUNER_LO_INJECTION_PROP_BAND_1_HIGH_SIDE;
            api->prop->tuner_lo_injection.band_2      = Si2151_TUNER_LO_INJECTION_PROP_BAND_2_LOW_SIDE;
            api->prop->tuner_lo_injection.band_3      = Si2151_TUNER_LO_INJECTION_PROP_BAND_3_LOW_SIDE;
            if (Si2151_L1_SetProperty2(api,Si2151_TUNER_LO_INJECTION_PROP) != 0)
            {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_TUNER_LO_INJECTION_PROP\n"));
            }
            if (previous_video_sys != Si2151_ATV_VIDEO_MODE_PROP_VIDEO_SYS_L)
            {
                SetIfDemod(E_RF_CH_BAND_8MHz, E_Network_Type_Analog_T, TV_SYS);
            }
            break;
        case si_tv_system_lp:
            freqHz = (u32FreqKHz * 1000) - C_Si2151_PF_TO_CF_SHIFT_L1*1000;
            api->prop->tuner_lo_injection.band_1      = Si2151_TUNER_LO_INJECTION_PROP_BAND_1_HIGH_SIDE;
            api->prop->tuner_lo_injection.band_2      = Si2151_TUNER_LO_INJECTION_PROP_BAND_2_LOW_SIDE;
            api->prop->tuner_lo_injection.band_3      = Si2151_TUNER_LO_INJECTION_PROP_BAND_3_LOW_SIDE;
            if (Si2151_L1_SetProperty2(api,Si2151_TUNER_LO_INJECTION_PROP) != 0)
            {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_TUNER_LO_INJECTION_PROP\n"));
            }
            if (previous_video_sys != Si2151_ATV_VIDEO_MODE_PROP_VIDEO_SYS_LP)
            {
                SetIfDemod(E_RF_CH_BAND_8MHz, E_Network_Type_Analog_T, TV_SYS);
            }
            break;
        case si_tv_system_invalid:
        default:                
            printf("[Error]%s, %s, %d\n", __FILE__,__FUNCTION__,__LINE__);
            break;
    }

    if(s16Finetune!=0)
    {
        freq_offset= (int) (s16Finetune*625/10);// 1 FinetuneStep is 62.5KHz
        api->prop->atv_lif_freq.offset = (unsigned int)(freq_offset+Si2151_GetDefaultIF(u32FreqKHz, TV_SYS));
        if (Si2151_L1_SetProperty2(api, Si2151_ATV_LIF_FREQ_PROP) != 0)
        {
            mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_ATV_LIF_FREQ_PROP\n"));
        }
    }
    else
    {
        if(p_dev->s16Prev_finetune!=0)  // current finetune=0, previous finetune!=0, restore original lif_freq_offset
        {
            api->prop->atv_lif_freq.offset = Si2151_GetDefaultIF(u32FreqKHz, TV_SYS);
            if (Si2151_L1_SetProperty2(api, Si2151_ATV_LIF_FREQ_PROP) != 0)
            {
                mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_ATV_LIF_FREQ_PROP\n"));
            }
        }
    }
    p_dev->s16Prev_finetune = s16Finetune;

    if (freqHz < Si2151_TUNER_TUNE_FREQ_CMD_FREQ_MIN || freqHz > Si2151_TUNER_TUNE_FREQ_CMD_FREQ_MAX)
    {
        printf("[Silabs]:<= Frequency out of Range\n");
        mcSHOW_HW_MSG((" [Silabs]: <= Frequency out of Range\n"));
        return FALSE;
    }

    if(p_dev->m_bInATVScanMode == TRUE)
    {
        if (Si2151_L1_ATV_SCAN_TUNE(api, freqHz) != 0)
        {
            printf("[Silabs]:Error Si2151_L1_ATV_SCAN_TUNE\n");
            mcSHOW_HW_MSG((" [Silabs]: Error Si2151_L1_ATV_SCAN_TUNE\n"));
            return FALSE;
        }

        //system_wait(40); //wait 40ms
        // usleep(35000);  //wait 35ms
        msleep(35);
        retb = TRUE;
        DBG_TUNER(printf("!!!!!!!!!!!!!ATV_SCAN_TUNE complete..................................\n");)

    }
    else
    {
        if (Si2151_L1_TUNER_TUNE_FREQ(api,Si2151_TUNER_TUNE_FREQ_CMD_MODE_ATV,  freqHz) != 0)
        {
            printf("[Silabs]:Error Si2151_L1_TUNER_TUNE_FREQ\n");
            mcSHOW_HW_MSG((" [Silabs]: Error Si2151_L1_TUNER_TUNE_FREQ\n"));
        }

        /* wait for TUNINT, timeout is 36ms */
        timeout = 36;
        // start_time = MsOS_GetSystemTime();
        while( (timeout--) > 0)
        {
            if (Si2151_L1_CheckStatus(api) != 0)
                return FALSE;
            if (api->status->tunint)
            {
                DBG_TUNER(printf("!!!!!!!!!!!!!LOCK..................................\n");)
                retb = TRUE;
                break;
            }
            mdelay(1);
        }

        /* wait for ATVINT, timeout is 110ms */
        timeout = 110;
        // start_time = MsOS_GetSystemTime();
        while( (timeout--) > 0 )
        {
            if (Si2151_L1_CheckStatus(api) != 0)
                return FALSE;
            if (api->status->atvint)
            {
                DBG_TUNER(printf("!!!!!!!!!!!!!ATV ----------LOCK....................\n");)
                retb = TRUE;
                break;
            }
            mdelay(1);
        }
    }

    return retb;   
}

int MDrv_TUNER_DVBS_SetTune(int minor, U16 u16CenterFreqMHz, U32 u32SymbolRateKs)
{
    TUNER_PRINT("%s is invoked\n", __FUNCTION__);
    return 0;
}

int MDrv_TUNER_DTV_SetTune(int minor, U32 freq, U32 eBandWidth, U32 eMode)
{    
    int retb = FALSE;
    U32 freqHz = 0;
    U32 timeout = 0;
    Network_Type eNetworktype = E_Network_Type_DVBT;
    unsigned char previous_dtv_mode = 0;
    unsigned char previous_agc_speed = 0;

    TUNER_PRINT("%s is invoked\n", __FUNCTION__);
    DBG_TUNER(printf("%s, %d, Freq=%d Hz, bw=%d, mode=%d\n",__FUNCTION__,__LINE__,freq,eBandWidth,eMode);)

    eNetworktype = Dtv_system_enum_conversion(eMode);

    p_dev=&(dev[minor]);

    if (p_dev->e_status != E_WORKING)
    {
        printf("[Error]%s,%d\n",__FILE__,__LINE__);
        return FALSE;
    }

    previous_dtv_mode=api->prop->dtv_mode.modulation;
    previous_agc_speed=api->prop->dtv_agc_speed.if_agc_speed;

    DBG_TUNER(printf ("Si2151_TunerSetFreq freq = %d; Band = %d Network = %d\n", (U16)freq,eBandWidth, eNetworktype);)

    p_dev->e_std = E_TUNER_DTV_DVB_T_MODE;
    p_dev->u32_freq = freq;
    p_dev->u32_eband_bandwidth = eBandWidth;
    p_dev->u32_eMode = eMode;

    api->prop->tuner_lo_injection.band_1      = Si2151_TUNER_LO_INJECTION_PROP_BAND_1_HIGH_SIDE;
    api->prop->tuner_lo_injection.band_2      = Si2151_TUNER_LO_INJECTION_PROP_BAND_2_LOW_SIDE;
    api->prop->tuner_lo_injection.band_3      = Si2151_TUNER_LO_INJECTION_PROP_BAND_3_LOW_SIDE;
    if (Si2151_L1_SetProperty2(api,Si2151_TUNER_LO_INJECTION_PROP) != 0)
    {
            mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_TUNER_LO_INJECTION_PROP\n"));
    }

    /* Set the Tuner return loss optimize and TF1 boundary if in DTMB mode, otherwise reset it to default values */
    if (eNetworktype == E_Network_Type_DTMB)
    {
        api->prop->tuner_return_loss_optimize.config               =    91;
        api->prop->tuner_return_loss_optimize_2.thld               =    15; /* (default    31) */
        api->prop->tuner_return_loss_optimize_2.window             =     5; /* (default     0) */
        api->prop->tuner_return_loss_optimize_2.engagement_delay   =     3; /* (default    15) */
        api->prop->tuner_tf1_boundary_offset.tf1_boundary_offset   =    22;
    }
    else
    {
        api->prop->tuner_return_loss_optimize.config               = Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_CONFIG_DISABLE;
        api->prop->tuner_return_loss_optimize_2.thld               =    31; /* (default    31) */
        api->prop->tuner_return_loss_optimize_2.window             =     0; /* (default     0) */
        api->prop->tuner_return_loss_optimize_2.engagement_delay   =    15; /* (default    15) */
        api->prop->tuner_tf1_boundary_offset.tf1_boundary_offset   =     0;
    }

    /* set the remaining optimize values to their defaults */
    api->prop->tuner_return_loss_optimize.thld                 =     0;
    api->prop->tuner_return_loss_optimize.engagement_delay     =     7;
    api->prop->tuner_return_loss_optimize.disengagement_delay  =    10;

    if (Si2151_L1_SetProperty2(api, Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP) != 0)
    {
        mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP\n"));
    }
    if (Si2151_L1_SetProperty2(api, Si2151_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP) != 0)
    {
        mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP\n"));
    }
    if (Si2151_L1_SetProperty2(api, Si2151_TUNER_TF1_BOUNDARY_OFFSET_PROP) != 0)
    {
        mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2151_TUNER_TF1_BOUNDARY_OFFSET_PROP\n"));
    }

    switch (eNetworktype)
    {
       case E_Network_Type_DVBT:
            if ( (previous_dtv_mode != Si2151_DTV_MODE_PROP_MODULATION_DVBT)
                || (previous_agc_speed!=Si2151_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO)
                || (eBandWidth != p_dev->pre_bw)
                )
                SetIfDemod(eBandWidth, eNetworktype, si_tv_system_invalid);
            break;                
       case E_Network_Type_DVBT2:
            if ( (previous_dtv_mode != Si2151_DTV_MODE_PROP_MODULATION_DVBT)
                || (previous_agc_speed!=Si2151_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_39)
                || (eBandWidth != p_dev->pre_bw)
               )
                SetIfDemod(eBandWidth, eNetworktype, si_tv_system_invalid);
            break;
       case E_Network_Type_DVBC:
            if (previous_dtv_mode != Si2151_DTV_MODE_PROP_MODULATION_DVBC)
                SetIfDemod(eBandWidth, eNetworktype, si_tv_system_invalid);
            break;
       case E_Network_Type_ISDBT:
            if (previous_dtv_mode != Si2151_DTV_MODE_PROP_MODULATION_ISDBT)
                SetIfDemod(eBandWidth, eNetworktype, si_tv_system_invalid);
            break;             
       case E_Network_Type_ISDBC:
            if (previous_dtv_mode != Si2151_DTV_MODE_PROP_MODULATION_ISDBC)
                SetIfDemod(eBandWidth, eNetworktype, si_tv_system_invalid);
            break;       
       case E_Network_Type_DTMB:  
            if (previous_dtv_mode != Si2151_DTV_MODE_PROP_MODULATION_DTMB)
                SetIfDemod(eBandWidth, eNetworktype, si_tv_system_invalid);
            break;   
       case E_Network_Type_ATSC:
            if (previous_dtv_mode != Si2151_DTV_MODE_PROP_MODULATION_ATSC)
                SetIfDemod(eBandWidth, eNetworktype, si_tv_system_invalid);
            break;            
       case E_Network_Type_QAM_US:
            if (previous_dtv_mode != Si2151_DTV_MODE_PROP_MODULATION_QAM_US)
                SetIfDemod(eBandWidth, eNetworktype, si_tv_system_invalid);
            break;
       case E_Network_Type_Analog_T:
       case E_Network_Type_Analog_C:
       case E_Network_Type_DVBS:   
       default:
            printf("[Error]%s,%s,%d\n",__FILE__,__FUNCTION__,__LINE__);
            break;
    }

    if (eMode == E_TUNER_DTV_ATSC_MODE)
        freqHz = (U32)(freq * 1000);
    else
        freqHz = (U32)(freq * 1000000);

    if (freqHz < Si2151_TUNER_TUNE_FREQ_CMD_FREQ_MIN || freqHz > Si2151_TUNER_TUNE_FREQ_CMD_FREQ_MAX)
    {
        printf("[Silabs]:<= Frequency out of Range\n");
        mcSHOW_HW_MSG((" [Silabs]: <= Frequency out of Range\n"));
        return FALSE;
    }

    if (Si2151_L1_TUNER_TUNE_FREQ(api,Si2151_TUNER_TUNE_FREQ_CMD_MODE_DTV,  freqHz) != 0)
    {
        printf("[Silabs]:Error Si2151_L1_TUNER_TUNE_FREQ\n");
        mcSHOW_HW_MSG((" [Silabs]: Error Si2151_L1_TUNER_TUNE_FREQ\n"));
        return FALSE;
    }

    /* wait for TUNINT, timeout is 36ms */
    timeout = 36;
    // start_time = MsOS_GetSystemTime();
    while( (timeout--) > 0 )
    {
        if (Si2151_L1_CheckStatus(api) != 0)
            return FALSE;
        if (api->status->tunint)
        {
            retb = TRUE; 
            DBG_TUNER(printf("!!!!!!!!!!!!!LOCK...................\n");)
            break;
        }
        mdelay(1);
    }
    /* wait for DTVINT, timeout is 10ms */
    timeout = 10;
    // start_time = MsOS_GetSystemTime();
    while( (timeout--) > 0 )
    {
        if (Si2151_L1_CheckStatus(api) != 0)
            return FALSE;
        if (api->status->dtvint)
        {
            DBG_TUNER(printf("!!!!!!!!!!!!!DTV ----------LOCK................\n");)
            retb = TRUE;
            break;
        }
        mdelay(1);
    }

    if (retb == TRUE)
        p_dev->pre_bw = eBandWidth;
    
    return retb;
}

int MDrv_TUNER_ExtendCommand(int minor, U8 u8SubCmd, U32 u32Param1, U32 u32Param2, void* pvoidParam3)
{
    TUNER_PRINT("%s is invoked\n", __FUNCTION__);
    DBG_TUNER(printf("%s, %d, u8SubCmd=%d, u32Param1=%d, u32Param2=%d\n",__FUNCTION__,__LINE__,u8SubCmd,u32Param1,u32Param2);)

    p_dev=&(dev[minor]);

    switch(u8SubCmd)
    {
        case E_TUNER_SUBCMD_GET_FREQ_STEP:
        {
            EN_FREQ_STEP *eFreqStep = (EN_FREQ_STEP*)pvoidParam3;
            *eFreqStep = TN_FREQ_STEP;
        }
            break;

        case E_TUNER_SUBCMD_GET_IF_FREQ:
        {
            U16 *u16IFFreq = (U16 *)pvoidParam3;
            *u16IFFreq = C_Si2151_IF_CENTER_B;
        }
            break;

        case E_TUNER_SUBCMD_GET_L_PRIME_IF_FREQ:
        {
            U16 *u16IFFreq = (U16 *)pvoidParam3;
            *u16IFFreq = C_Si2151_IF_CENTER_L1;
        }
            break;

        case E_TUNER_SUBCMD_GET_VHF_LOWMIN_FREQ:
        {
            U32 *u32Freq = (U32 *)pvoidParam3;
            *u32Freq = TUNER_VHF_LOWMIN_FREQ;
        }
            break;

        case E_TUNER_SUBCMD_GET_VHF_LOWMAX_FREQ:
        {
            U32 *u32Freq = (U32 *)pvoidParam3;
            *u32Freq = TUNER_VHF_LOWMAX_FREQ;
        }
            break;

        case E_TUNER_SUBCMD_GET_VHF_HIGHMIN_FREQ:
        {
            U32 *u32Freq = (U32 *)pvoidParam3;
            *u32Freq = TUNER_VHF_HIGHMIN_FREQ;
        }
            break;

        case E_TUNER_SUBCMD_GET_VHF_HIGHMAX_FREQ:
        {
            U32 *u32Freq = (U32 *)pvoidParam3;
            *u32Freq = TUNER_VHF_HIGHMAX_FREQ;
        }
            break;

        case E_TUNER_SUBCMD_GET_UHF_MIN_FREQ:
        {
            U32 *u32Freq = (U32 *)pvoidParam3;
            *u32Freq = TUNER_UHF_MIN_FREQ;
        }
            break;

        case E_TUNER_SUBCMD_GET_UHF_MAX_FREQ:
        {
            U32 *u32Freq = (U32 *)pvoidParam3;
            *u32Freq = TUNER_UHF_MAX_FREQ;
        }
            break;

        case E_TUNER_SUBCMD_GET_VIF_TUNER_TYPE:
        {
            U8 *u8VifTunerType = (U8 *)pvoidParam3;
            *u8VifTunerType = VIF_TUNER_TYPE;
        }
            break;
        case E_TUNER_SUBCMD_GET_VIF_PARA:
        {
            stVIFInitialIn *p_stVIFInitialIn = (stVIFInitialIn *)pvoidParam3;

            p_stVIFInitialIn->VifCrRate_B = VIF_CR_RATE_B;
            p_stVIFInitialIn->VifCrInvert_B = VIF_CR_INVERT_B;
            p_stVIFInitialIn->VifCrRate_GH = VIF_CR_RATE_GH;
            p_stVIFInitialIn->VifCrInvert_GH = VIF_CR_INVERT_GH;
            p_stVIFInitialIn->VifCrRate_DK = VIF_CR_RATE_DK;
            p_stVIFInitialIn->VifCrInvert_DK = VIF_CR_INVERT_DK;
            p_stVIFInitialIn->VifCrRate_I = VIF_CR_RATE_I;
            p_stVIFInitialIn->VifCrInvert_I = VIF_CR_INVERT_I;
            p_stVIFInitialIn->VifCrRate_L = VIF_CR_RATE_L;
            p_stVIFInitialIn->VifCrInvert_L = VIF_CR_INVERT_L;
            p_stVIFInitialIn->VifCrRate_LL = VIF_CR_RATE_LL;
            p_stVIFInitialIn->VifCrInvert_LL = VIF_CR_INVERT_LL;
            p_stVIFInitialIn->VifCrRate_MN = VIF_CR_RATE_MN;
            p_stVIFInitialIn->VifCrInvert_MN = VIF_CR_INVERT_MN;
        }
            break;
        case E_TUNER_SUBCMD_GET_VIF_NOTCH_SOSFILTER:
        {
            U16 *pu16_vif_notch_coef = NULL;
            U16 *pu16_list = (U16*)pvoidParam3;
            U8 indx = 0;
            
            switch((EN_VIF_SOUND_SYSTEM)u32Param1)
            {
                case E_VIF_SOUND_B_STEREO_A2:                    
                    pu16_vif_notch_coef = VIF_A1_A2_SOS11_SOS12_B_Stereo_A2;
                    break;
                    
                case E_VIF_SOUND_B_MONO_NICAM:
                    pu16_vif_notch_coef = VIF_A1_A2_SOS11_SOS12_B_Mono_NICAM;
                    break;

                case E_VIF_SOUND_GH_STEREO_A2:
                    pu16_vif_notch_coef = VIF_A1_A2_SOS11_SOS12_GH_Stereo_A2;
                    break;

                case E_VIF_SOUND_GH_MONO_NICAM:
                    pu16_vif_notch_coef = VIF_A1_A2_SOS11_SOS12_GH_Mono_NICAM;
                    break;

                case E_VIF_SOUND_I:
                    pu16_vif_notch_coef = VIF_A1_A2_SOS11_SOS12_I;
                    break;
                case E_VIF_SOUND_DK1_STEREO_A2:
                    pu16_vif_notch_coef = VIF_A1_A2_SOS11_SOS12_DK1_Stereo_A2;
                    break;

                case E_VIF_SOUND_DK2_STEREO_A2:
                    pu16_vif_notch_coef = VIF_A1_A2_SOS11_SOS12_DK2_Stereo_A2;
                    break;

                case E_VIF_SOUND_DK3_STEREO_A2:
                    pu16_vif_notch_coef = VIF_A1_A2_SOS11_SOS12_DK3_Stereo_A2;
                    break;

                case E_VIF_SOUND_DK_MONO_NICAM:
                    pu16_vif_notch_coef = VIF_A1_A2_SOS11_SOS12_DK_Mono_NICAM;
                    break;

                case E_VIF_SOUND_L:
                    pu16_vif_notch_coef = VIF_A1_A2_SOS11_SOS12_L;
                    break;

                case E_VIF_SOUND_LL:
                    pu16_vif_notch_coef = VIF_A1_A2_SOS11_SOS12_LP;
                    break;

                case E_VIF_SOUND_MN:
                    pu16_vif_notch_coef = VIF_A1_A2_SOS11_SOS12_MN;
                    break;
                default:
                    printf("Error:%s(),%d\n",__func__,__LINE__);
                    return FALSE;
                    break;
            }
            
            if (pu16_vif_notch_coef == NULL) return FALSE;

            for (indx = 0;indx < 16;indx++)
            {
                *(pu16_list+indx) = *(pu16_vif_notch_coef+indx);
            }
              
        }
            break;          
        case E_TUNER_SUBCMD_GET_DTV_IF_FREQ:
        {
            switch (u32Param1) // demod mode
            {
                case E_TUNER_DTV_DVB_T2_MODE:
                    switch(u32Param2) // bandwidth
                    {
                        case E_RF_CH_BAND_6MHz:
                            *((U32 *)pvoidParam3)=C_Si2151_IF_FREQUENCY;
                            break;
                        case E_RF_CH_BAND_7MHz:
                            *((U32 *)pvoidParam3)=C_Si2151_IF_FREQUENCY;
                            break;
                        case E_RF_CH_BAND_8MHz:
                            *((U32 *)pvoidParam3)=C_Si2151_IF_FREQUENCY;
                            break;
                        default:
                            printf("Error:%s(),%d\n",__func__,__LINE__);
                            return FALSE;
                            break;
                    }
                    break;
                case E_TUNER_DTV_DVB_T_MODE:
                    switch(u32Param2) // bandwidth
                    {
                        case E_RF_CH_BAND_6MHz:
                            *((U32 *)pvoidParam3)=C_Si2151_IF_FREQUENCY;
                            break;
                        case E_RF_CH_BAND_7MHz:
                            *((U32 *)pvoidParam3)=C_Si2151_IF_FREQUENCY;
                            break;
                        case E_RF_CH_BAND_8MHz:
                            *((U32 *)pvoidParam3)=C_Si2151_IF_FREQUENCY;
                            break;
                        default:
                            printf("Error:%s(),%d\n",__func__,__LINE__);
                            return FALSE;
                            break;
                    }
                    break;
                case E_TUNER_DTV_DVB_C_MODE:
                    switch(u32Param2)
                    {
                        case E_RF_CH_BAND_6MHz:
                        case E_RF_CH_BAND_7MHz:
                        case E_RF_CH_BAND_8MHz:
                            *((U32 *)pvoidParam3)=C_Si2151_IF_FREQUENCY;
                            break;
                        default:
                            printf("Error:%s(),%d\n",__func__,__LINE__);
                            return FALSE;
                            break;
                    }
                    break;
                case E_TUNER_DTV_ATSC_MODE:
                case E_TUNER_DTV_DTMB_MODE:
                case E_TUNER_DTV_ISDB_MODE:                    
                    *((U32 *)pvoidParam3)=C_Si2151_IF_FREQUENCY;
                    break;
                default:
                    printf("Error:%s(),%d\n",__func__,__LINE__);
                    return FALSE;
                    break;
            }
        }
            break;
        case E_TUNER_SUBCMD_GET_IQ_SWAP:
        {
            U8 *u8IqSwap = (U8 *)pvoidParam3;
            if (E_TUNER_DTV_ATSC_MODE == u32Param1)
            {
                *u8IqSwap = 0;
            }
            else
            {
                *u8IqSwap = TUNER_DTV_IQ_SWAP;
                if ( u32Param1 )
                {
                    *u8IqSwap ^= 0x01;
                }
            }
        }
            break;
        case E_TUNER_SUBCMD_GET_RF_TABLE:
        {
            (*(DMD_SSI_TABLE **)pvoidParam3)=NULL; // if not used, should return NULL;
            return FALSE;
        }
            break;

        case E_TUNER_SUBCMD_GET_RF_LEVEL:
        {
            S16 ssi_100dbm = 0;
            Si2151_GetRSSILevel(&ssi_100dbm); 
            *((S16 *)pvoidParam3) = ssi_100dbm;
            return TRUE;
        }
            break;

        case E_TUNER_SUBCMD_GET_DEMOD_CONFIG:
        {

            switch (u32Param1) // demod mode
            {
                case E_TUNER_DTV_DVB_T_MODE:
                    *((U8 **)pvoidParam3)=NULL;
                    break;
                case E_TUNER_DTV_DVB_C_MODE:
                    *((U8 **)pvoidParam3)=NULL;
                    break;
                case E_TUNER_ATV_PAL_MODE:
                case E_TUNER_ATV_SECAM_L_PRIME_MODE:
                case E_TUNER_ATV_NTSC_MODE:
                {
                    U32 *u32AgcOdMode = (U32 *)pvoidParam3;
                    *u32AgcOdMode = TUNER_VIF_TAGC_ODMODE;
                }
                    break;
                case E_TUNER_DTV_DVB_T2_MODE:
                {
                    U8 *u8if_AgcMode = (U8 *)pvoidParam3;
                    *u8if_AgcMode = TUNER_DVB_IF_AGC_MODE;
                }
                  break;
                default:
                    printf("Error:%s(),%d\n",__func__,__LINE__);
                    return FALSE;
                    break;
            }
        }
            break;
        default:
            UNUSED(u8SubCmd);
            UNUSED(u32Param1);
            UNUSED(u32Param2);
            UNUSED(pvoidParam3);
            return FALSE;
            break;
    }


    
    return TRUE;
}

int MDrv_TUNER_TunerInit(int minor, u8 u8Slave)
{   
    int ret = TRUE;

    TUNER_PRINT("%s is invoked\n", __FUNCTION__);
    _u8SlaveID=u8Slave; 
    TUNER_PRINT(" _u8SlaveID 0x%x\n",_u8SlaveID);
    if (minor < MAX_TUNER_DEV_NUM)
    {
        p_dev=&(dev[minor]);
        if ( (p_dev->e_status == E_CLOSE)
            || (p_dev->e_status == E_SUSPEND) )
        {
            if(device_tuner_si_2151_init()==FALSE)
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
        ret = FALSE;
    }    
    return ret;
}

int MDrv_TUNER_ConfigAGCMode(int minor, U32 eMode)
{
    TUNER_PRINT("%s is invoked\n", __FUNCTION__);
    return 0;
}

int MDrv_TUNER_SetTunerInScanMode(int minor, U32 bScan)
{
    TUNER_PRINT("%s is invoked\n", __FUNCTION__);
    if(p_dev->m_bInATVScanMode != bScan)
    {
        p_dev->m_bInATVScanMode = bScan;
    }
    return TRUE;
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
    U8 i = 0;
    
    for (i=0; i<MAX_TUNER_DEV_NUM; i++)
    {
        if (dev[i].e_status == E_WORKING)
        {
            dev[i].e_status = E_SUSPEND;
            dev[i].pre_bw = E_RF_CH_BAND_INVALID;
            dev[i].s16Prev_finetune = 0;
            dev[i].m_bInATVScanMode = 0;
            dev[i].m_bInfinttuneMode = 0;
        }
    }
    
    if (NULL != api) {
        free(api);
        api = NULL;
    }

    return 0;
}

int MDrv_TUNER_Resume(void)
{
    U8 i = 0;
    int ret_code = 0;
    
    for (i=0; i<MAX_TUNER_DEV_NUM; i++)
    {
        if (dev[i].e_status == E_SUSPEND)
        {
            if (MDrv_TUNER_TunerInit((int)i,_u8SlaveID)==TRUE)
            {
                if (dev[i].e_std == E_TUNER_DTV_DVB_T_MODE)
                {
                    ret_code = MDrv_TUNER_DTV_SetTune((int)i, dev[i].u32_freq, dev[i].u32_eband_bandwidth,dev[i].u32_eMode);
                    if (ret_code == FALSE)
                    {
                        printf("Error, DTV_SetTune fail after resume.%d.%d.%d.%d\n",i,dev[i].u32_freq,dev[i].u32_eband_bandwidth,dev[i].u32_eMode);
                    }
                }
                else if (dev[i].e_std == E_TUNER_ATV_PAL_MODE)
                {
                    ret_code = MDrv_TUNER_ATV_SetTune((int)i, dev[i].u32_freq, dev[i].u32_eband_bandwidth, dev[i].u32_eMode, dev[i].u8_otherMode);
                    if (ret_code == FALSE)
                    {
                        printf("Error, ATV_SetTune fail after resume.%d.%d.%d.%d.%d\n",i,dev[i].u32_freq,dev[i].u32_eband_bandwidth,dev[i].u32_eMode,dev[i].u8_otherMode);
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


