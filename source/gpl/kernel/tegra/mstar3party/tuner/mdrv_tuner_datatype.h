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


#ifndef _MDRV_TUNER_DATATYPE_H_
#define _MDRV_TUNER_DATATYPE_H_


/// the scan frequency step
typedef enum
{
    /// 31.25 KHz
    E_FREQ_STEP_31_25KHz = 0x00,
    /// 50 KHz
    E_FREQ_STEP_50KHz    = 0x01,
    /// 62.5 KHz
    E_FREQ_STEP_62_5KHz  = 0x02,
    /// invalid
    E_FREQ_STEP_INVALD
} EN_FREQ_STEP;

/// the RF band
typedef enum
{
    /// VHF low
    E_RFBAND_VHF_LOW,
    /// VHF high
    E_RFBAND_VHF_HIGH,
    /// UHF
    E_RFBAND_UHF,
    /// invalid
    E_RFBAND_INVALID,
} RFBAND;

/// the RF channel bandwidth
typedef enum
{
    /// 6 MHz
    E_RF_CH_BAND_6MHz = 0x01,
    /// 7 MHz
    E_RF_CH_BAND_7MHz = 0x02,
    /// 8 MHz
    E_RF_CH_BAND_8MHz = 0x03,
    /// others...
    E_RF_CH_BAND_1MHz,
    E_RF_CH_BAND_1p7MHz,
    E_RF_CH_BAND_2MHz,
    E_RF_CH_BAND_3MHz,
    E_RF_CH_BAND_4MHz,
    E_RF_CH_BAND_5MHz,
    E_RF_CH_BAND_9MHz,
    E_RF_CH_BAND_10MHz,    
    /// invalid
    E_RF_CH_BAND_INVALID
} RF_CHANNEL_BANDWIDTH;

/// the tuner mode
typedef enum
{
    /// DTV, DVBT
    E_TUNER_DTV_DVB_T_MODE = 0x00,
    /// DTV, DVBC
    E_TUNER_DTV_DVB_C_MODE ,
    /// DTV, DVBS
    E_TUNER_DTV_DVB_S_MODE ,
    /// DTV, DTMB
    E_TUNER_DTV_DTMB_MODE ,
    /// DTV, ATSC
    E_TUNER_DTV_ATSC_MODE ,
    /// ATV, PAL
    E_TUNER_ATV_PAL_MODE ,
    /// ATV, SECAM-L'
    E_TUNER_ATV_SECAM_L_PRIME_MODE ,
    /// ATV, NTSC
    E_TUNER_ATV_NTSC_MODE ,
    /// DTV, ISDB
    E_TUNER_DTV_ISDB_MODE ,
    /// DTV, DVBT2
    E_TUNER_DTV_DVB_T2_MODE,
    /// others...
    E_TUNER_DTV_DVB_C2_MODE,
    E_TUNER_DTV_J83B_MODE,  
    E_TUNER_DTV_ISDB_C_MODE ,
    E_TUNER_DTV_DVB_S2_MODE ,
    E_TUNER_DTV_ISDB_S_MODE ,    
    /// invalid
    E_TUNER_INVALID
} EN_TUNER_MODE;

/// the cable status
typedef enum
{
    /// Unknow
    E_CABLE_UNKNOW,
    /// Cable inserted
    E_CABLE_INSERTED,
    /// Cable removed
    E_CABLE_REMOVED
} EN_CABLE_STATUS;


// MJ? shall we use namespace in kernal mode?
// namespace mapi_tuner_datatype
// {
    /// the subcommand type for tuner
    typedef enum
    {
        /// get frequency step
        E_TUNER_SUBCMD_GET_FREQ_STEP,
        /// get IF frequency
        E_TUNER_SUBCMD_GET_IF_FREQ,
        /// get L-prime IF frequency
        E_TUNER_SUBCMD_GET_L_PRIME_IF_FREQ,
        /// get VHF low, minimum frequency
        E_TUNER_SUBCMD_GET_VHF_LOWMIN_FREQ,
        /// get VHF low, maximum frequency
        E_TUNER_SUBCMD_GET_VHF_LOWMAX_FREQ,
        /// get VHF high, minimum frequency
        E_TUNER_SUBCMD_GET_VHF_HIGHMIN_FREQ,
        /// get VHF high, maximum frequency
        E_TUNER_SUBCMD_GET_VHF_HIGHMAX_FREQ,
        /// get UHF, minimum frequency
        E_TUNER_SUBCMD_GET_UHF_MIN_FREQ,
        /// get UHF, maximum frequency
        E_TUNER_SUBCMD_GET_UHF_MAX_FREQ,
        /// get vif tuner type
        E_TUNER_SUBCMD_GET_VIF_TUNER_TYPE,
        /// get vif parameter for RF/Silicon tuner
        E_TUNER_SUBCMD_GET_VIF_PARA,
        /// get ATV VIF Notch and SOS Filter
        E_TUNER_SUBCMD_GET_VIF_NOTCH_SOSFILTER,
        /// get DTV IF frequency
        E_TUNER_SUBCMD_GET_DTV_IF_FREQ,
        /// get IQ SWAP
        E_TUNER_SUBCMD_GET_IQ_SWAP,
        /// get RF Table
        E_TUNER_SUBCMD_GET_RF_TABLE,
        /// get RF Level
        E_TUNER_SUBCMD_GET_RF_LEVEL,
        /// get demod config
        E_TUNER_SUBCMD_GET_DEMOD_CONFIG,
        /// get peaking parameter
        E_TUNER_SUBCMD_GET_PEAKING_PARAMETER,
        /// check RF robustness
        E_TUNER_SUBCMD_CHECK_RF_ROBUSTNESS,
        /// get temp eratrre
        E_TUNER_SUBCMD_GETJTEMPERATRRE,
        /// add customized code here
        E_TUNER_SUBCMD_USER_DEFINE,
        /// select AGC pin
        E_TUNER_SUBCMD_SELECT_AGC_PIN,
        /// invalid
        E_TUNER_SUBCMD_INVALD
    } EN_TUNER_SUBCOMMAND;

    /// tuner No
    typedef enum
    {
        // Tuner 1
        EN_TUNER_1 = 0,
        // Tuner 2
        EN_TUNER_2,
        // Tuner number
        EN_TUNER_MAX
    }EN_TUNER_NUMBER;
// };

/// Audio SIF Standard Type
typedef enum
{
    ///< Audio standard BG
    E_AUDIOSTANDARD_BG_                     = 0x00,
    ///< Audio standard BG A2
    E_AUDIOSTANDARD_BG_A2_                  = 0x01,
    ///< Audio standard BG NICAM
    E_AUDIOSTANDARD_BG_NICAM_               = 0x02,
    ///< Audio standard I
    E_AUDIOSTANDARD_I_                      = 0x03,
    ///< Audio standard DK
    E_AUDIOSTANDARD_DK_                     = 0x04,
    ///< Audio standard DK1 A2
    E_AUDIOSTANDARD_DK1_A2_                 = 0x05,
    ///< Audio standard DK2 A2
    E_AUDIOSTANDARD_DK2_A2_                 = 0x06,
    ///< Audio standard DK3 A2
    E_AUDIOSTANDARD_DK3_A2_                 = 0x07,
    ///< Audio standard DK NICAM
    E_AUDIOSTANDARD_DK_NICAM_               = 0x08,
    ///< Audio standard L
    E_AUDIOSTANDARD_L_                      = 0x09,
    ///< Audio standard M
    E_AUDIOSTANDARD_M_                      = 0x0A,
    ///< Audio standard M BTSC
    E_AUDIOSTANDARD_M_BTSC_                 = 0x0B,
    ///< Audio standard M A2
    E_AUDIOSTANDARD_M_A2_                   = 0x0C,
    ///< Audio standard M EIA J
    E_AUDIOSTANDARD_M_EIA_J_                = 0x0D,
    ///< Not Audio standard
    E_AUDIOSTANDARD_NOTSTANDARD_            = 0x0F
} AUDIOSTANDARD_TYPE_;

///VIF Sound system
typedef enum
{
    ///VIF Sound B
    E_VIF_SOUND_B_STEREO_A2,
    ///VIF Sound B
    E_VIF_SOUND_B_MONO_NICAM,
    ///VIF Sound GH
    E_VIF_SOUND_GH_STEREO_A2,
    ///VIF Sound GH
    E_VIF_SOUND_GH_MONO_NICAM,
    ///VIF Sound I
    E_VIF_SOUND_I,
    ///VIF Sound DK1
    E_VIF_SOUND_DK1_STEREO_A2,
    ///VIF Sound DK2
    E_VIF_SOUND_DK2_STEREO_A2,
    ///VIF Sound 3
    E_VIF_SOUND_DK3_STEREO_A2,
    ///VIF Sound 4
    E_VIF_SOUND_DK_MONO_NICAM,
    ///VIF Sound L
    E_VIF_SOUND_L,
    ///VIF Sound LL
    E_VIF_SOUND_LL,
    ///VIF Sound MN
    E_VIF_SOUND_MN,
    ///EN_VIF_SOUND_SYSTEM enum Numbers
    E_VIF_SOUND_NUMS
} EN_VIF_SOUND_SYSTEM;


/// the cable status
typedef enum
{
    // Before init success.
    E_CLOSE,
    // Init success.
    E_WORKING,
    // Under suspend mode.
    E_SUSPEND,
    // Number of tuner status.
    E_TUNER_STATUS_NUM
} E_TUNER_STATUS;


/// stVIFInitialIn
typedef struct 
{
    U8 VifTop;
    U8 VifIfBaseFreq;
    U8 VifTunerStepSize;
    U8 VifSawArch;
    U16 VifVgaMaximum;
    U16 VifVgaMinimum;
    U16 GainDistributionThr;
    U8 VifAgcVgaBase;
    U8 VifAgcVgaOffs;
    U8 VifAgcRefNegative;
    U8 VifAgcRefPositive;
    U8 VifDagc1Ref;
    U8 VifDagc2Ref;
    U16 VifDagc1GainOv;
    U16 VifDagc2GainOv;
    U8 VifCrKf1;
    U8 VifCrKp1;
    U8 VifCrKi1;
    U8 VifCrKp2;
    U8 VifCrKi2;
    U8 VifCrKp;
    U8 VifCrKi;
    U16 VifCrLockThr;
    U16 VifCrThr;
    U32 VifCrLockNum;
    U32 VifCrUnlockNum;
    U16 VifCrPdErrMax;
    int VifCrLockLeakySel;
    int VifCrPdX2;
    int VifCrLpfSel;
    int VifCrPdModeSel;
    int VifCrKpKiAdjust;
    U8 VifCrKpKiAdjustGear;
    U8 VifCrKpKiAdjustThr1;
    U8 VifCrKpKiAdjustThr2;
    U8 VifCrKpKiAdjustThr3;
    int VifDynamicTopAdjust;
    U8 VifDynamicTopMin;
    int VifAmHumDetection;
    int VifClampgainClampSel;
    U8 VifClampgainSyncbottRef;
    U8 VifClampgainSyncheightRef;
    U8 VifClampgainKc;
    U8 VifClampgainKg;
    int VifClampgainClampOren;
    int VifClampgainGainOren;
    U16 VifClampgainClampOvNegative;
    U16 VifClampgainGainOvNegative;
    U16 VifClampgainClampOvPositive;
    U16 VifClampgainGainOvPositive;
    U8 VifClampgainClampMin;
    U8 VifClampgainClampMax;
    U8 VifClampgainGainMin;
    U8 VifClampgainGainMax;
    U16 VifClampgainPorchCnt;
    U8 VifPeakingFilterB_VHF_L;
    U8 VifYcDelayFilterB_VHF_L;
    U8 VifGroupDelayFilterB_VHF_L;
    U8 VifPeakingFilterGH_VHF_L;
    U8 VifYcDelayFilterGH_VHF_L;
    U8 VifGroupDelayFilterGH_VHF_L;
    U8 VifPeakingFilterDK_VHF_L;
    U8 VifYcDelayFilterDK_VHF_L;
    U8 VifGroupDelayFilterDK_VHF_L;
    U8 VifPeakingFilterI_VHF_L;
    U8 VifYcDelayFilterI_VHF_L;
    U8 VifGroupDelayFilterI_VHF_L;
    U8 VifPeakingFilterL_VHF_L;
    U8 VifYcDelayFilterL_VHF_L;
    U8 VifGroupDelayFilterL_VHF_L;
    U8 VifPeakingFilterLL_VHF_L;
    U8 VifYcDelayFilterLL_VHF_L;
    U8 VifGroupDelayFilterLL_VHF_L;
    U8 VifPeakingFilterMN_VHF_L;
    U8 VifYcDelayFilterMN_VHF_L;
    U8 VifGroupDelayFilterMN_VHF_L;

    U8 VifPeakingFilterB_VHF_H;
    U8 VifYcDelayFilterB_VHF_H;
    U8 VifGroupDelayFilterB_VHF_H;
    U8 VifPeakingFilterGH_VHF_H;
    U8 VifYcDelayFilterGH_VHF_H;
    U8 VifGroupDelayFilterGH_VHF_H;
    U8 VifPeakingFilterDK_VHF_H;
    U8 VifYcDelayFilterDK_VHF_H;
    U8 VifGroupDelayFilterDK_VHF_H;
    U8 VifPeakingFilterI_VHF_H;
    U8 VifYcDelayFilterI_VHF_H;
    U8 VifGroupDelayFilterI_VHF_H;
    U8 VifPeakingFilterL_VHF_H;
    U8 VifYcDelayFilterL_VHF_H;
    U8 VifGroupDelayFilterL_VHF_H;
    U8 VifPeakingFilterLL_VHF_H;
    U8 VifYcDelayFilterLL_VHF_H;
    U8 VifGroupDelayFilterLL_VHF_H;
    U8 VifPeakingFilterMN_VHF_H;
    U8 VifYcDelayFilterMN_VHF_H;
    U8 VifGroupDelayFilterMN_VHF_H;

    U8 VifPeakingFilterB_UHF;
    U8 VifYcDelayFilterB_UHF;
    U8 VifGroupDelayFilterB_UHF;
    U8 VifPeakingFilterGH_UHF;
    U8 VifYcDelayFilterGH_UHF;
    U8 VifGroupDelayFilterGH_UHF;
    U8 VifPeakingFilterDK_UHF;
    U8 VifYcDelayFilterDK_UHF;
    U8 VifGroupDelayFilterDK_UHF;
    U8 VifPeakingFilterI_UHF;
    U8 VifYcDelayFilterI_UHF;
    U8 VifGroupDelayFilterI_UHF;
    U8 VifPeakingFilterL_UHF;
    U8 VifYcDelayFilterL_UHF;
    U8 VifGroupDelayFilterL_UHF;
    U8 VifPeakingFilterLL_UHF;
    U8 VifYcDelayFilterLL_UHF;
    U8 VifGroupDelayFilterLL_UHF;
    U8 VifPeakingFilterMN_UHF;
    U8 VifYcDelayFilterMN_UHF;
    U8 VifGroupDelayFilterMN_UHF;
    U8 ChinaDescramblerBox;
    U8 VifDelayReduce;
    int VifOverModulation;

    int VifOverModulationDetect;
    int VifACIDetect;
    U8 VifACIAGCREF;
    U8 VifADCOverflowAGCREF;
    U8 VifChanelScanAGCREF;
    U8 VifACIDetTHR1;
    U8 VifACIDetTHR2;
    U8 VifACIDetTHR3;
    U8 VifACIDetTHR4;

    U8 VifFreqBand;
    U16 VifSos21FilterC0;
    U16 VifSos21FilterC1;
    U16 VifSos21FilterC2;
    U16 VifSos21FilterC3;
    U16 VifSos21FilterC4;
    U16 VifSos22FilterC0;
    U16 VifSos22FilterC1;
    U16 VifSos22FilterC2;
    U16 VifSos22FilterC3;
    U16 VifSos22FilterC4;
    U16 VifSos31FilterC0;
    U16 VifSos31FilterC1;
    U16 VifSos31FilterC2;
    U16 VifSos31FilterC3;
    U16 VifSos31FilterC4;
    U16 VifSos32FilterC0;
    U16 VifSos32FilterC1;
    U16 VifSos32FilterC2;
    U16 VifSos32FilterC3;
    U16 VifSos32FilterC4;
    U8 VifTunerType;
    U32 VifCrRate_B;
    int VifCrInvert_B;
    U32 VifCrRate_GH;
    int VifCrInvert_GH;
    U32 VifCrRate_DK;
    int VifCrInvert_DK;
    U32 VifCrRate_I;
    int VifCrInvert_I;
    U32 VifCrRate_L;
    int VifCrInvert_L;
    U32 VifCrRate_LL;
    int VifCrInvert_LL;
    U32 VifCrRate_MN;
    int VifCrInvert_MN;
    U8 VifReserve;
} stVIFInitialIn;


typedef struct
{
    S16   power_db;
    U8   sar3_val;
}DMD_RFAGC_SSI;

typedef struct
{
    S16   power_db;
    U8   agc_val;
}DMD_IFAGC_SSI;

typedef struct
{
    S16   attn_db;
    U8   agc_err;
}DMD_IFAGC_ERR;

typedef struct
{
    DMD_RFAGC_SSI *pRfagcSsi;
    U16 u16RfagcSsi_Size;
    DMD_IFAGC_SSI *pIfagcSsi_LoRef; 
    U16 u16IfagcSsi_LoRef_Size;    
    DMD_IFAGC_SSI *pIfagcSsi_HiRef;   
    U16 u16IfagcSsi_HiRef_Size;    
    DMD_IFAGC_ERR *pIfagcErr_LoRef;  
    U16 u16IfagcErr_LoRef_Size;    
    DMD_IFAGC_ERR *pIfagcErr_HiRef;    
    U16 u16IfagcErr_HiRef_Size;    
}DMD_SSI_TABLE;

typedef struct
{
    EN_TUNER_MODE          e_std;
    E_TUNER_STATUS         e_status;
    RF_CHANNEL_BANDWIDTH   pre_bw;
    U32                    u32_freq;
    U32                    u32_eband_bandwidth;
    U32                    u32_eMode;
    U32                    u32_symbolrate;
    U8                     u8_otherMode; 
    S16                    s16Prev_finetune;
    int                    m_bInATVScanMode;
    int                    m_bInfinttuneMode;       
}s_Tuner_dev_info;

#endif
