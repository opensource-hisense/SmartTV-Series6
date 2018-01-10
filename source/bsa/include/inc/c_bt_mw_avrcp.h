/********************************************************************************************
 *     LEGAL DISCLAIMER
 *
 *     (Header of MediaTek Software/Firmware Release or Documentation)
 *
 *     BY OPENING OR USING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 *     THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE") RECEIVED
 *     FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON AN "AS-IS" BASIS
 *     ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES, EXPRESS OR IMPLIED,
 *     INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR
 *     A PARTICULAR PURPOSE OR NONINFRINGEMENT. NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY
 *     WHATSOEVER WITH RESPECT TO THE SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY,
 *     INCORPORATED IN, OR SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK
 *     ONLY TO SUCH THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
 *     NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S SPECIFICATION
 *     OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
 *
 *     BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE LIABILITY WITH
 *     RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE, AT MEDIATEK'S OPTION,
 *     TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE, OR REFUND ANY SOFTWARE LICENSE
 *     FEES OR SERVICE CHARGE PAID BY BUYER TO MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 *     THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE WITH THE LAWS
 *     OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF LAWS PRINCIPLES.
 ************************************************************************************************/

#ifndef __C_BT_MW_AVRCP_H__
#define __C_BT_MW_AVRCP_H__

 /******************** AVRCP ********************/

 INT32 c_btm_avrcp_get_mediaInfo(avrcp_medioInfo_t *mediaInfo);

 INT32 c_btm_avrcp_get_play_status(bt_player_status_values_t *pt_playStatus);

 INT32 c_btm_avrcp_passthrough_cmd(BTCmdType bt_cmd_type, BTN_ACTION button_action);

 INT32 c_btm_bt_avrcp_get_capabilities(avrcp_apability_type_t type);

 INT32 c_btm_register_avrcp_notification(CHAR* pNotificationStr);
 INT32 c_btm_set_volume(UINT8 i4_volume);

 /*for PTS test*/
 INT32 c_btm_set_trackstatus(CHAR *ptrack_status);
 INT32 c_btm_send_volume_change_rsp_handler(UINT8 u1_volume);


 INT32 c_btm_send_track_change_rsp_handler(UINT8 u1track_selected);


 INT32 c_btm_set_large_element_attribute_response_handler(UINT8 u1enable);


 INT32 c_btm_send_pts_test_handler(UINT8 fgenable);


 INT32 c_btm_bt_avrcp_get_capabilities(avrcp_apability_type_t type);


#endif /* __C_BT_MW_AVRCP_H__ */
