/*******************************************************************************
 * LEGAL DISCLAIMER
 *
 * (Header of MediaTek Software/Firmware Release or Documentation)
 *
 * BY OPENING OR USING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND
 * AGREES THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK
 * SOFTWARE") RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO
 * BUYER ON AN "AS-IS" BASISONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL
 * WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR
 * NONINFRINGEMENT. NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH
 * RESPECT TO THE SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY,
 * INCORPORATED IN, OR SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO
 * LOOK ONLY TO SUCH THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO.
 * MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES
 * MADE TO BUYER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN
 * FORUM.
 *
 * BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE
 * LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY BUYER TO
 * MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 * THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE WITH
 * THE LAWS OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF LAWS
 * PRINCIPLES.
 ******************************************************************************/

/* FILE NAME:  u_bt_mw_common.h
 * AUTHOR: Hongliang Hu
 * PURPOSE:
 *      It provides bluetooth common structure to APP.
 * NOTES:
 */


#ifndef _U_BLUETOOTH_H_
#define _U_BLUETOOTH_H_

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/

//#include "u_common.h"
#include "config/c_mw_config.h"
#include "u_bt_mw_common.h"
#include "u_bt_mw_avrcp.h"
#include "u_bt_mw_a2dp.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/



typedef enum
{
    BT_SPP_CONNECT = 0,
    BT_SPP_DISCONNECT = 1,
    BT_SPP_RECV_DATA = 2,
    BT_SPP_CONNECT_FAIL,
    BT_SPP_DISCONNECT_FAIL,
    BT_SPP_MAX
}BT_SPP_EVENT;

typedef enum
{
    BT_HID_CONNECTED = 0,
    BT_HID_CONNECTING = 1,
    BT_HID_DISCONNECTED = 2,
    BT_HID_DISCONNECTING = 3,
    BT_HID_CONNECT_FAIL,
    BT_HID_DISCONNECT_FAIL,
    BT_HID_CONNECTION_REJECT
}BT_HID_EVENT;

typedef enum
{
    BT_PAIRED_STATUS = 0,
    BT_CONNECTED_STATUS = 1,
}BT_STATUS;

typedef struct _BT_SPP_CBK_STRUCT
{
    CHAR *uuid;
    CHAR *spp_data;
    UINT8 uuid_len;
    UINT8 spp_data_len;
    BT_SPP_EVENT bt_spp_event_type;
}BT_SPP_CBK_STRUCT;

typedef struct _BT_HID_CBK_STRUCT
{
    CHAR current_addr[MAX_BDADDR_LEN];
    BOOL bt_get_dev_hid_history_done;
    BT_HID_EVENT bt_hid_event_type;
}BT_HID_CBK_STRUCT;

typedef struct _BT_HID_STATUS_STRUCT
{
    BT_STATUS          status;
    CHAR               bdAddr[MAX_BDADDR_LEN];
}BT_HID_STATUS_STRUCT;

typedef struct _BT_HID_STATUS_STRUCT_LIST
{
    UINT32             head_idx;
    UINT32             dev_num;
    BT_HID_STATUS_STRUCT device_list[MAX_HID_DEV_NUM];
}BT_HID_STATUS_STRUCT_LIST;

typedef struct _BT_TARGET_DEV_INFO
{
    UINT8              fg_istv;/*target device is TV or not*/
    UINT32             u4delay_value;/*target device is TV or not*/
    CHAR               bdAddr[MAX_BDADDR_LEN];/* Bluetooth Address */
    CHAR               name[MAX_NAME_LEN];/* Name of device */
    UINT32  cod;                         // Class of Device
    UINT32  device_type;
}BT_TARGET_DEV_INFO;

typedef struct _BT_TARGET_DEV_LIST
{
    UINT32             head_idx;
    UINT32             dev_num;
    BT_TARGET_DEV_INFO device_list[MAX_DEV_NUM];
}BT_TARGET_DEV_LIST;

typedef struct _BT_HID_TARGET_DEV_LIST
{
    UINT32             head_idx;
    UINT32             dev_num;
    BT_TARGET_DEV_INFO device_list[MAX_HID_DEV_NUM];
}BT_HID_TARGET_DEV_LIST;

typedef struct _BT_DEV_MAPPING_INFO
{
    CHAR               bdAddr[MAX_BDADDR_LEN];/* Bluetooth Address */
    CHAR               name[MAX_NAME_LEN];/* Name of device */
    BOOL             ready;
    BOOL             is_notify;
    UINT32          cod;
    INT16           rssi;
    UINT32          devicetype;
}BT_DEV_MAPPING_INFO;

typedef struct _BT_DEV_MAPPING_LIST
{
    UINT32              head_idx;
    UINT32              dev_num;
    BT_DEV_MAPPING_INFO mapping_list[MAX_MAPPING_SCAN_NUM];
}BT_DEV_MAPPING_LIST;

typedef struct _BT_DEV_LIST_IN_NAMES
{
    UINT32             head_idx;
    UINT32             dev_num;
    BT_TARGET_DEV_INFO *device_list;
}BT_DEV_LIST_IN_NAMES;


typedef struct _BT_GAP_SCAN_RESULT
{
    CHAR               name[MAX_NAME_LEN];/* Name of device */
    UINT32            cod;          /* Class of Device */
    UINT8              isPaired;
    CHAR               bdAddr[MAX_BDADDR_LEN];/* Bluetooth Address */
    UINT32            service;    /* Service supported */
    INT16            rssi;    /* Service supported */
    UINT32           devicetype; /* device type*/
}BT_GAP_SCAN_RESULT;

typedef struct _BT_GAP_SCAN_RESULT_S
{
    INT32                                       inqNum;
    INT32                                       inquiring;
    BT_GAP_SCAN_RESULT                inqResult[MAX_INQU_NUM];
}BT_GAP_SCAN_RESULT_S;

typedef struct _BT_GAP_SDP_RESULT
{
    CHAR               service[MAX_STR_LEN];
    CHAR               bdAddr[MAX_BDADDR_LEN];
}BT_GAP_SDP_RESULT;

typedef struct _BT_GAP_LOCAL_PROPERTIES_RESULT
{
    CHAR              bdAddr[MAX_BDADDR_LEN];
    CHAR              name[MAX_NAME_LEN];
    UINT8             powered;
    UINT8             scan_mode;
    UINT32            disctimeout;
}BT_GAP_LOCAL_PROPERTIES_RESULT;

typedef struct _BT_GAP_CBK_PARMS
{
    BT_GAP_SCAN_RESULT_S                                scanResults;
    BT_GAP_SDP_RESULT                                     sdpResult;
    BT_GAP_LOCAL_PROPERTIES_RESULT                propResult;
}BT_GAP_CBK_PARMS;

typedef struct _BT_A2DP_UPLOAD_INFO
{
    INT32            sample_freq;
    UINT8            channel_num;
    BOOL             fgNeedMuteACP;
}BT_A2DP_UPLOAD_INFO;

typedef enum _BT_A2DP_UPLOAD_SAMPLERATE_LEVEL_E
{
    BT_A2DP_UPLOAD_SAMPLERATE_LEVE_INIT = 0,
    BT_A2DP_UPLOAD_SAMPLERATE_LEVE_48 = 1,
    BT_A2DP_UPLOAD_SAMPLERATE_LEVE_96
}bt_a2dp_upload_samplerate_level;

typedef enum audio_conn_type_e
{
    CONN_TYPE_INVALID = 0,
    CONN_TYPE_A2DP,
    CONN_TYPE_AVCTP,
    CONN_TYPE_END
}audio_conn_type_t;

typedef enum pairing_key_type_s
{
    PIN_CODE = 0,
    PASSKEY,
    Key_TYPE_END
} pairing_key_type_t;

typedef struct pairing_key_value_s
{
    pairing_key_type_t key_type;
    CHAR pin_code[MAX_PIN_LEN]; /* When key_type=PIN_CODE, this value is available*/
    UINT32 key_value; /* When key_type=PASS_KEY, this value is available*/
} pairing_key_value_t;
//typedef VOID (*BtGapCbk)(BT_GAP_EVENT bt_gap_event, BT_GAP_CBK_PARMS bt_gap_result);
typedef VOID (*BtAppEventCbk)(BTEvent bt_event);
typedef VOID (*BtAppSppCbk)(BT_SPP_CBK_STRUCT *pt_spp_struct);
typedef VOID (*BtAppHidCbk)(BT_HID_CBK_STRUCT *pt_hid_struct);
typedef VOID (*BtRemoteCbk)(BT_DEV_MAPPING_LIST *pt_remote_struct);
typedef VOID (*BtAppGapInquiryResponseCbk)(BT_GAP_SCAN_RESULT* pt_result);
typedef VOID (*BtAppA2dpUploadInfoCbk)(BT_A2DP_UPLOAD_INFO* pt_upload_info, BOOL fg_only_check_mute);
/*A2DP SRC use this cbk notify APP layer do playback operation*/
typedef VOID (*BtAppA2dpPlaybackCtrlCbk)(BTPlayState bt_playback_cmd);
typedef VOID (*BtAppA2dpResetAudioCbk)(VOID);
typedef VOID (*BtAppGapGetPairingKeyCbk)(pairing_key_value_t *bt_pairing_key, UINT8 *fg_accept);

typedef struct _BT_APP_CB_FUNC
{
    BtAppEventCbk bt_event_cb;
    BtAppGapGetPairingKeyCbk bt_get_pairing_key_cb;
    BtAppA2dpUploadInfoCbk bt_upload_info_cb;
    BtAppA2dpPlaybackCtrlCbk bt_playback_ctrl_cb;
    BtAppA2dpResetAudioCbk bt_reset_audio_cb;
    BtAppAvrcpPlayStateChangeCbk bt_play_change_cb;
    BtAppAvrcpVolumeChangeCbk bt_volume_change_cb;
    BtAppAvrcpTrackChangeCbk bt_track_change_cb;
    BtAppAvrcpMediaStatusCbk bt_media_playstatus_cb;
    BtAppAvrcpAbsoluteVolumeCbk bt_absolute_volume_cb;
    BtAppAvrcpCmdCbk bt_avrcp_cmd_cb;
    BtAppAvrcpGetPlayStatusCbk bt_get_play_status_cb;
    BtAppHidCbk bt_hid_cb;
    BtAppSppCbk bt_spp_cb;
	BtRemoteCbk bt_remote_cb;
}BT_APP_CB_FUNC;

typedef INT32 (*BtUploadInitCbk)(VOID);
typedef INT32 (*BtUploadStartCbk)(VOID);
typedef INT32 (*BtUploadStopCbk)(VOID);
typedef INT32 (*BtUploadDeinitCbk)(VOID);

typedef struct _BT_AUDIO_SRC_CB_FUNC
{
    BtUploadInitCbk bt_upd_init_cb;
    BtUploadStartCbk bt_upd_start_cb;
    BtUploadStopCbk bt_upd_stop_cb;
    BtUploadDeinitCbk bt_upd_deinit_cb;
}BT_AUDIO_SRC_CB_FUNC;

typedef INT32 (*BtPlayerInitCbk)(INT32 trackFreq, INT32 channelType);
typedef INT32 (*BtPlayerStartCbk)(VOID);
typedef INT32 (*BtPlayerPauseCbk)(VOID);
typedef INT32 (*BtPlayerStopCbk)(VOID);
typedef INT32 (*BtPlayerDeinitCbk)(VOID);
typedef INT32 (*BtPlayerPushDataCbk)(VOID *audioBuffer, INT32 bufferLen);

typedef struct _BT_PLAYER_SNK_CB_FUNC
{
    BtPlayerInitCbk player_init_cb;
    BtPlayerStartCbk player_start_cb;
    BtPlayerPauseCbk player_pause_cb;
    BtPlayerStopCbk player_stop_cb;
    BtPlayerDeinitCbk player_deinit_cb;
    BtPlayerPushDataCbk player_push_data_cb;
}BT_PLAYER_SNK_CB_FUNC;

typedef enum _BT_AUDIO_CODEC_TYPE
{
    BT_AUDIO_SBC    = 0x01,
    BT_AUDIO_AAC    = 0x02,
    BT_AUDIO_LDAC   = 0x04,
    BT_AUDIO_UNKONW = 0x10
}BT_AUDIO_CODEC_TYPE;

typedef enum bt_a2dp_status_e
{
    BT_A2DP_UNINIT = 0,
    BT_A2DP_START,
    BT_A2DP_SUSPEND,
    BT_A2DP_END
}bt_a2dp_status_t;

typedef enum _BT_AUDIO_QUALITY
{
    BT_QUALITY_AUTO    = 0x0,
    BT_QUALITY_SOUND_QUALITY    = 0x01,
    BT_QUALITY_STANDARD   = 0x02,
    BT_QUALITY_CONNECTON = 0x03,
    BT_QUALITY_UNKONW
}BT_AUDIO_QUALITY;

typedef enum _BT_A2DP_ROLE
{
    BT_A2DP_ROLE_SRC        = 0x0,
    BT_A2DP_ROLE_SINK       = 0x1,
    BT_A2DP_ROLE_UNKONW     = 0x2,
}BT_A2DP_ROLE;

typedef enum _BT_A2DP_ENABLED_ROLE
{
    BT_A2DP_ENABLED_SINK            = 0x01,
    BT_A2DP_ENABLED_SRC             = 0x02,
    BT_A2DP_ENABLED_UNKONW          = 0x10,
}BT_A2DP_ENABLED_ROLE;


#endif /*  _U_BLUETOOTH_H_ */

