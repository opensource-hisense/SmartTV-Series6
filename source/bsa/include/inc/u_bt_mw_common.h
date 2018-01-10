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


#ifndef _U_BT_MW_COMMON_H_
#define _U_BT_MW_COMMON_H_

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <errno.h>
//#include <assert.h>
//#include <x_typedef.h>
//#include "u_common.h"
#include "config/c_mw_config.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

#define             MAX_BDADDR_LEN                   ((UINT32)      18)
#define             MAX_NAME_LEN                       ((UINT32)     249)
#define             MAX_INQU_NUM                       ((UINT32)     32)
#define             MAX_STR_LEN                         ((UINT32)      128)
#define             PAIRING                             "PAIRING"
#define             CONNECTING                          "CONNECTING"
#define             PLAYING                             "PLAYING"
#define             OFF                                 "OFF"
#define             MAX_PIN_LEN                   ((UINT32)      16)

#if (ENABLE_VIVA || ENABLE_PHANTOM)
#define             MAX_DEV_NUM                       ((UINT32)     8)
#else
#define             MAX_DEV_NUM                       ((UINT32)     9)
#endif

#define             MAX_MAPPING_NUM                   ((UINT32)     10)
#define             MAX_MAPPING_SCAN_NUM                   ((UINT32)     30)

#define             MAX_HID_DEV_NUM                       ((UINT32)     4)
#define             MAX_HID_CONN_NUM                      ((UINT32)     3)

#define BT_INQUIRY_FILTER_TYPE_NO 0
#define BT_INQUIRY_FILTER_TYPE_A2DP_SRC (1<<0)
#define BT_INQUIRY_FILTER_TYPE_A2DP_SNK (1<<1)
#define BT_INQUIRY_FILTER_TYPE_HID (1<<2)
#define BT_INQUIRY_FILTER_TYPE_DS4 (1<<3)
#define BT_INQUIRY_FILTER_TYPE_A2DP_HID (1<<4)
#define AVRCP_CHARSET_UTF8          0x006A
#define MAX_NAME_STR_LEN 255

typedef enum _BT_ERR_TYPE
{
    BT_ERR_SUCCESS = 0,
    BT_ERR_NULL_POINTER = -2,
    BT_ERR_OUT_OF_RANGE = -3,
    BT_ERR_UNKNOWN_CMD = -4,
    BT_ERR_INVALID_PARAM = -5,
    BT_ERR_INVALID_PARAM_NUMS = -6,
    BT_ERR_NOT_SUPPORT = -7,
    BT_ERR_FAILED = -1,
    BT_ERR_SYS_CALL_FAILED = -8,
    BT_ERR_END = -100
}BT_ERR_TYPE;


typedef enum
{
    BT_SUCCESS = 0,
    BT_ERR_STATUS_FAIL = -1,
    BT_ERR_STATUS_NOT_READY = -2,
    BT_ERR_STATUS_NOMEM = -3,
    BT_ERR_STATUS_BUSY = -4,
    BT_ERR_STATUS_DONE = -5,        /* request already completed */
    BT_ERR_STATUS_UNSUPPORTED = -6,
    BT_ERR_STATUS_PARM_INVALID = -7,
    BT_ERR_STATUS_UNHANDLED = -8,
    BT_ERR_STATUS_AUTH_FAILURE = -9,
    BT_ERR_STATUS_RMT_DEV_DOWN = -10,
    BT_ERR_STATUS_INVALID_PARM_NUMS = -11,
    BT_ERR_STATUS_NULL_POINTER = -12,
    BT_ERR_STATUS_END = -100
} BT_ERR_STATUS_T;

typedef enum
{
    /*common message*/
    BT_OFF_MODE = 0, // when wait mode starts.
    BT_CONNECT_MODE = 1, // when connect mode starts.
    BT_PAIRING_MODE = 2, // when paring mode starts.
    BT_PLAYING_MODE = 3,
    BT_EXIT = 4, // when Bluetooth is disabled.
    BT_GAP_STATE_BONDED = 5, // when paring is completed.
    BT_PAIRING_TIMEOUT = 6, // when paring is timed out.
    BT_CONNECT_COMING = 7,
    BT_CONNECT_MISSING = 8, // when connection is missing
    BT_DISCONNECTED = 9, //when Bluetooth is disconnected.
    BT_CONNECT_SUCCESS = 10, // when connection is completed
    BT_CONNECT_TIMEOUT = 11, // when auto-connect is timed out
    BT_GET_DEV_HISTORY_DONE = 12,
    BT_POWER_ON = 13, // when Bluetooth is enabled or power on.
    BT_GAP_STATE_NONE = 14,
    /*a2dp message*/
    BT_2ND_CONNECT_COMMING = 20, /* The 2nd connection request */
    BT_2ND_CONNECT_FAIL, /* The 2nd connection fail */
    BT_SUPPORT_SCMS_T,
    BT_A2DP_CONNECTION_SUCCESS,/* A2DP connection established successful*/
    BT_GET_CODEC_INFORMATION_SUCCESS,
    BT_A2DP_UP_SAMPLE_2FS,/*Audio APP do upsample*/
    /*avrcp message*/
    BT_AVRCP_CONNECTION_SUCCESS = 30,/* AVRCP connection established successful*/
    BT_SUPPORT_AVRCP_1_3,/* support AVRCP 1.3*/
    BT_NOT_SUPPORT_AVRCP_1_3,/* does not support AVRCP 1.3*/
    BT_REGISTER_PS_SUCCESS,/* support play status change callback*/
    BT_REGISTER_PS_FAIL,/* does not support play status change callback*/
    /*hid message*/
    BT_HIDD_CONNECTION_SUCCESS = 40,/*HID device connection established successful*/
    BT_HIDD_CONNECTION_FAIL,/*HID device connection established fail*/
    BT_HIDD_DISCONNECTION_SUCCESS,/*HID device connection disconnected successful*/
    BT_HIDD_REJECT_3ND_CONNECTION,/*reject HID 3rd connection*/

    BT_EVENT_MAX
} BTEvent;

typedef enum
{
    MW_AUD_DVD_Media_type = 1,/*special media only support 48 or 44.1*/
    MW_AUD_DEFAULT_Media_type = 2,/*normal media can support all sample rate*/
    MW_AUD_ERROR_Media_type
} MW_AUD_digital_Media_type;

typedef enum
{
    BT_GAP_POWERED_ON   =0, /* Init Cnf */
    BT_GAP_POWERED_OFF, /* Deinit Cnf */
    BT_GAP_INQ_CANCELLED, /* Inquiry canclled */
    BT_GAP_INQ_COMPLETE, /* Inquiry Complete */
    BT_GAP_SDP_RESPONSE, /* SDP response */
    BT_GAP_PINCODE_IND, /* Pincode indication from bluez to MMI */
    BT_GAP_PASSKEY_IND, /* Passkey indication from bluez to MMI */
    BT_GAP_PAIR_CNF, /* Pairing Confirm indication */
    BT_GAP_DEVICE_FOUND, /* Device found during inquiry */
    BT_GAP_LOCAL_PROP, /* Local bluetooth device properties */
    BT_GAP_PAIR_ERR, /* Pairing Error failure */
    BT_GAP_REMOVE_BOND, /* Remove Bond response */
    BT_GAP_PAIR_DEV, /* Paired device bdaddr */
    BT_GAP_PAIR_DEV_CNF, /* Indicate end of Paired device list */
    BT_GAP_PAIRING_TIMEOUT,
    BT_GAP_PAIR_MODE_CHANGED,    /* Indicate Pairing mode set */
    BT_GAP_DISC_MODE_CHANGED,    /* Indicate Discovery mode set */
    BT_GAP_NAME_CHANGED,
    BT_GAP_LINK_LOSS_RECONNECT_SPEAKER,
    BT_OFF,
    BT_AVRCP_EVENT_CONNECT_IND                          ,
    BT_AVRCP_EVENT_CONNECT_CNF                          ,
    BT_GET_PLAY_STATUS_REJECT                           ,
    BT_GET_ELEMENT_ATTRIBUTES_REJECT                    ,
    BT_OTHER_REJECT                                     ,
    BT_AVRCP_CONNECT_TIMEOUT                            ,
    BT_AVRCP_EVENT_DISCONNECTED_IND                     ,
    BT_AVRCP_EVENT_DISCONNECTED_CNF                     ,
    BT_AVRCP_EVENT_PLAYER_SETTINGS_IND                  ,
    BT_AVRCP_EVENT_GET_PLAY_STATUS_IND                  ,
    BT_AVRCP_EVENT_PROPERTY_CHANGED_IND                 ,
    BT_AVRCP_EVENT_TRACK_CHANGED_IND                    ,
    BT_AVRCP_EVENT_ELEMENT_ATTRIBUTE_IND                ,
    BT_AVRCP_EVENT_REGISTER_NOTIFICATION_IND            ,
    BT_AVRCP_EVENT_LIST_ATTRIBUTE_VALUES                ,
    BT_AVRCP_EVENT_MOVETO_NEXT_GROUP_STATUS             ,
    BT_AVRCP_EVENT_MOVETO_PREVIOUS_GROUP_STATUS         ,
    BT_AVRCP_EVENT_PANEL_PASSTROUGH_CFM                 ,
    BT_AVRCP_EVENT_SET_PLAYER_PROPERTY_REQ              ,
    BT_AVRCP_EVENT_SET_ATTRIBUTE_VALUES                 ,
    BT_AVRCP_EVENT_VOLUME_DOWN                          ,
    BT_AVRCP_EVENT_VOLUME_UP                 ,

    BLUETOOTH_EVENT_PLAYBACK_STATUS_CHANGED             ,
    BLUETOOTH_EVENT_TRACK_CHANGED                       ,
    BLUETOOTH_EVENT_TRACK_REACHED_END                   ,
    BLUETOOTH_EVENT_TRACK_REACHED_START                 ,
    BLUETOOTH_EVENT_PLAYBACK_POS_CHANGED                ,
    BLUETOOTH_EVENT_PLAYER_APPLICATION_SETTING_CHANGED  ,


    /*This Event is sent to indicate that stream is opened, union parameter stream_info will be having stream specific parameters.*/
    BLUETOOTH_A2DP_EVENT_STREAM_OPEN_IND,
    BLUETOOTH_A2DP_EVENT_STREAM_OPEN_CNF,

    /* This Event is sent to pass the remote Codec Configuration Information to MMI in case GET_Capabilites is initiated by MMI*/
    BLUETOOTH_A2DP_EVENT_STREAM_CONFIG,

    /*This Event is sent to indicate MMI the remote configuration Event. MMI needs to call SET Configuration response after matching capabilities*/
    BLUETOOTH_A2DP_GET_CONFIG_IND,

    /*This Event is sent to indicate GET Capability Request is completed*/
    //#define BLUETOOTH_A2DP_GET_CAP_CNF 0x05

    /*This Event is sent to indicate that Stream is Closed,union parameter stream_info will be having stream specific parameters.*/
    BLUETOOTH_A2DP_EVENT_STREAM_CLOSED_IND,
    BLUETOOTH_A2DP_EVENT_STREAM_CLOSED_CNF,

    /*This Event is to indicate to MMI that AVDTP START Command is received from remote. MMI Can accept or reject the Request*/
    //#define A2DP_EVENT_STREAM_START_IND 0x07

    /*This Event is to indicate to MMI that AVDTP Stream has Started*/
    BLUETOOTH_A2DP_EVENT_STREAM_STARTED_IND,
    BLUETOOTH_A2DP_EVENT_STREAM_STARTED_CNF,

    /*This Event is to indicate to MMI that AVDTP Stream is suspended*/
    BLUETOOTH_A2DP_EVENT_STREAM_SUSPENDED_IND,
    BLUETOOTH_A2DP_EVENT_STREAM_SUSPENDED_CNF,

    /*This Event is to indicate to MMI that stream is Aborted*/
    BLUETOOTH_A2DP_EVENT_STREAM_ABORTED_IND,
    BLUETOOTH_A2DP_EVENT_STREAM_ABORTED_CNF,


    BT_EVT_MAX
}BT_EVT_TYPE;


typedef enum
{
    BT_MODE_CLOSE = 0,
    BT_MODE_PAIRING = 1,
    BT_MODE_CONNECTING,
    BT_MODE_PLAYING,
    BT_MODE_OFF,
    BT_MODE_MAX
}BT_MODE_TYPE;




#endif /*  _U_BT_MW_COMMON_H_ */

