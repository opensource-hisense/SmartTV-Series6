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

/* FILE NAME:  u_bt_mw_avrcp.h
 * AUTHOR: Hongliang Hu
 * PURPOSE:
 *      It provides bluetooth avrcp structure to APP.
 * NOTES:
 */


#ifndef _U_BT_MW_AVRCP_H_
#define _U_BT_MW_AVRCP_H_

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/

//#include "u_common.h"
#include "u_bt_mw_common.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

#define BT_AVRCP_UID_SIZE                       8
#define BT_AVRCP_MAX_ATTRIBUTE_NUM              4
#define BT_AVRCP_MAX_APP_SETTINGS               8

typedef enum
{
    BT_PLAY_STATE_STOP = 0x00,         /* Stopped */
    BT_PLAY_STATE_PLAY = 0x01,     /* Playing */
    BT_PLAY_STATE_PAUSE = 0x02,        /* Paused  */
    BT_PLAY_STATUS_FWD_SEEK = 0x03,    /* Fwd Seek*/
    BT_PLAY_STATUS_REV_SEEK = 0x04,    /* Rev Seek*/
    BT_PLAY_STATE_FIRST_PLAY = 0x05,   /*first start to play*/
    BT_PLAY_STATUS_ERROR = 0xFF,    /* Error   */

    BT_PLAY_STATE_MAX

} BTPlayState;

typedef enum
{
    BT_MEDIA_INFO_OK        = 0x0001,         // can get media information.
    BT_PLAY_STATUS_OK       = 0x0002,     // can get play status.
    BT_PLAY_STATUS_FAIL     = 0x0003,     // can't get play status.
    BT_MEDIA_INFO_FAIL      = 0x0004,     // can'T get media information.
    BT_MEDIA_INFO_UPDATE    = 0x0005,

    BT_MEDIA_PLAY_MAX

} BTMediaPlayState;

typedef enum
{
    BT_CMD_TYPE_PLAY = 0, // play command.
    BT_CMD_TYPE_PAUSE, // pause command.
    BT_CMD_TYPE_FWD,
    BT_CMD_TYPE_BWD,
    BT_CMD_TYPE_FFWD,
    BT_CMD_TYPE_RWD,
    BT_CMD_TYPE_STOP, // stop command.
    BT_CMD_TYPE_VOLUME_UP,
    BT_CMD_TYPE_VOLUME_DOWN,

    BT_CMD_TYPE_MAX

} BTCmdType;

typedef enum
{
    BT_VOLUME_TYPE_UP = 0,
    BT_VOLUME_TYPE_DOWN

}BTVolType;

typedef enum
{
    BT_GET_VOLUME        = 0x0001,         // get volume from app.
    BT_SEND_VOLUME       = 0x0002     // send volume to app.
} BTAbsoluteVolumeType;

typedef struct avrcp_medioInfo_s
{
    UINT8 title[MAX_NAME_STR_LEN];
    UINT8 artist[MAX_NAME_STR_LEN];
    UINT8 album[MAX_NAME_STR_LEN];
    UINT32 current_track_number;
    UINT32 number_of_tracks;
    UINT8 genre[MAX_NAME_STR_LEN];
    UINT32 position;
    //UINT32 track_duration;
}avrcp_medioInfo_t;

typedef enum AVRCP_PLAYSTATUS_E
{
    AVRCP_STATUS_STOPPED = 0x00,  /* Stopped */
    AVRCP_STATUS_PLAYING = 0x01, /* Playing */
    AVRCP_STATUS_PAUSED = 0x02,    /* Paused  */
    AVRCP_STATUS_FORWARDSEEK= 0x03,    /* Fwd Seek*/
    AVRCP_STATUS_REWINDSEEK= 0x04,    /* Rev Seek*/
    AVRCP_STATUS_END = 0xFF,    /* Error   */
}bt_avrcp_playstatus_t;

typedef enum SYS_ENABLE_E
{
    DISABLED,
    ENABLED
}sys_enable_t;

typedef enum AVRCP_MODE_E
{
    AVRCP_MODE_TG = 0,
    AVRCP_MODE_CT,
    AVRCP_MODE_END
}bt_avrcp_mode_t;

typedef enum AVRCP_CAPABILITY_TYPE__E
{
    CAPABILITY_COMPANYID,
    CAPABILITY_EVENTS,
    CAPABILITY_UNKNOWN
}avrcp_apability_type_t;


typedef struct player_status_values_s
{
    UINT32 song_length; /* Total Length of playing Song in milliseconds*/
    UINT32 song_position; /* Current position of playing Song in milliseconds elapsed */
    bt_avrcp_playstatus_t play_status; /* current status of playing song */

} bt_player_status_values_t;

typedef struct
{
    UINT8 num_attr;
    UINT8 attr_ids[BT_AVRCP_UID_SIZE];
    UINT8 attr_values[BT_AVRCP_MAX_APP_SETTINGS];
} bt_player_settings_t;

typedef struct
{
    bt_avrcp_playstatus_t play_status;
    UINT8 track[BT_AVRCP_UID_SIZE]; /* queue position in NowPlaying */
    UINT32 song_pos;
    bt_player_settings_t player_setting;
    UINT8 battery_status;
    UINT16  uid_counter;
    UINT16  id;  //
    UINT8   count;  //EVENT_PLAYER_APPLICATION_SETTING_CHANGED
    UINT8   attribute_id[BT_AVRCP_MAX_ATTRIBUTE_NUM];  //EVENT_PLAYER_APPLICATION_SETTING_CHANGED
    UINT8   attribute_value[BT_AVRCP_MAX_ATTRIBUTE_NUM];  //EVENT_PLAYER_APPLICATION_SETTING_CHANGED
    UINT16   result;
    UINT8   error_code;
    UINT8    volume;
} bt_register_notification_t;

typedef VOID (*BtAppAvrcpPlayStateChangeCbk)(BTPlayState bt_playstate);
typedef VOID (*BtAppAvrcpVolumeChangeCbk)(BTVolType bt_volume);
typedef VOID (*BtAppAvrcpTrackChangeCbk)(UINT32 bt_track_index);
typedef VOID (*BtAppAvrcpMediaStatusCbk)(BTMediaPlayState bt_status);
typedef VOID (*BtAppAvrcpAbsoluteVolumeCbk)(BTAbsoluteVolumeType flag, UINT8 *bt_absolute_volume);
typedef VOID (*BtAppAvrcpGetPlayStatusCbk)(BTPlayState *bt_playstatus);
/*****************************************************************************
 * FUNCTION
 *  BtAppAvrcpCmdCbk,AVRCP target role for passthrough(A2DP SRC)
 *
 * PARAMETERS
 *  bt_cmd_type     [IN]
 *  press               [IN] 1: press, 0: release
 *
 *****************************************************************************/
typedef VOID (*BtAppAvrcpCmdCbk)(BTCmdType bt_cmd_type, UINT8 press);

typedef enum _BTN_ACTION_E
{
    BUTTON_ACT_PRESS = 0,
    BUTTON_ACT_RELEASE,
    BUTTON_ACT_AUTO,
    BUTTON_ACT_END
}BTN_ACTION;


#endif /*  _U_BT_MW_AVRCP_H_ */

