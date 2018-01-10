/*******************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2013
*
*  BY OPENING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
*  THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
*  RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON
*  AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
*  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
*  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
*  NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
*  SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
*  SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK ONLY TO SUCH
*  THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
*  NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S
*  SPECIFICATION OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
*
*  BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE
*  LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
*  AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
*  OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY BUYER TO
*  MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
*
*  THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE
*  WITH THE LAWS OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF
*  LAWS PRINCIPLES.  ANY DISPUTES, CONTROVERSIES OR CLAIMS ARISING THEREOF AND
*  RELATED THERETO SHALL BE SETTLED BY ARBITRATION IN SAN FRANCISCO, CA, UNDER
*  THE RULES OF THE INTERNATIONAL CHAMBER OF COMMERCE (ICC).
*
*******************************************************************************/

/* FILE NAME:  c_bt_mw_hid.h
 * AUTHOR: zwei chen
 * PURPOSE:
 *      It provides HID HOST  API to APP.
 * NOTES:
 */


#ifndef __C_BT_MW_HIDH_H__
#define __C_BT_MW_HIDH_H__

#define MTK_LINUX_HIDH_PTS_TEST 0

/****************************************************
 * FUNCTION NAME: c_bt_hid_activate
 * PURPOSE:
 *      The function is used to activate hid
 * INPUT:
 *      None
 *
 * OUTPUT:
 *      None
 * RETURN:
 *      INT32:error code
 * NOTES:
 *      None
 */
#if 0
INT32 c_bt_hid_activate(VOID);
#endif

/****************************************************
 * FUNCTION NAME: c_bt_hid_deactivate
 * PURPOSE:
 *      The function is used to deactivate hid
 * INPUT:
 *      None
 *
 * OUTPUT:
 *      None
 * RETURN:
 *      INT32:error code
 * NOTES:
 *      None
 */
#if 0
INT32 c_bt_hid_deactivate(VOID);
#endif

/****************************************************
 * FUNCTION NAME: c_bt_hid_init
 * PURPOSE:
 *      The function is used to init hid profile
 * INPUT:
 *      None
 *
 * OUTPUT:
 *      None
 * RETURN:
 *      INT32:error code
 * NOTES:
 *      None
 */
INT32 c_bt_hid_init(VOID);

/****************************************************
 * FUNCTION NAME: c_bt_hid_deinit
 * PURPOSE:
 *      The function is used to deinit hid profile
 * INPUT:
 *      None
 *
 * OUTPUT:
 *      None
 * RETURN:
 *      INT32:error code
 * NOTES:
 *      None
 */
INT32 c_bt_hid_deinit(VOID);

/****************************************************
 * FUNCTION NAME: c_bt_hid_connect
 * PURPOSE:
 *      The function is used to connect  hid device
 * INPUT:
 *      pbt_addr:device address
 *
 * OUTPUT:
 *      None
 * RETURN:
 *      INT32:error code
 * NOTES:
 *      None
 */
INT32 c_bt_hid_connect(char *pbt_addr);

/****************************************************
 * FUNCTION NAME: c_bt_hid_disconnect
 * PURPOSE:
 *      The function is used to disconnect  hid device
 * INPUT:
 *      pbt_addr:device address
 *
 * OUTPUT:
 *      None
 * RETURN:
 *      INT32:error code
 * NOTES:
 *      None
 */
INT32 c_bt_hid_disconnect(char *pbt_addr);

/****************************************************
 * FUNCTION NAME: c_bt_hid_set_output_report
 * PURPOSE:
 *      The function is used to set output report
 * INPUT:
 *      pbt_addr:device address
 *      preport_data: output report data
 * OUTPUT:
 *      None
 * RETURN:
 *      INT32:error code
 * NOTES:
 *      None
 */
INT32 c_bt_hid_set_output_report(char *pbt_addr, char *preport_data);

/****************************************************
 * FUNCTION NAME: c_bt_hid_get_input_report
 * PURPOSE:
 *      The function is used to get input report
 * INPUT:
 *      pbt_addr:device address
 *      reportId: report id
 *     bufferSize : size of the buffer for input data
 * OUTPUT:
 *      None
 * RETURN:
 *      INT32:error code
 * NOTES:
 *      None
 */
INT32 c_bt_hid_get_input_report(char *pbt_addr, int reportId, int bufferSize);

/****************************************************
 * FUNCTION NAME: c_bt_hid_get_output_report
 * PURPOSE:
 *      The function is used to get output report
 * INPUT:
 *      pbt_addr:device address
 *      reportId: report id
 *     bufferSize : size of the buffer for output data
 * OUTPUT:
 *      None
 * RETURN:
 *      INT32:error code
 * NOTES:
 *      None
 */
INT32 c_bt_hid_get_output_report(char *pbt_addr, int reportId, int bufferSize);

/****************************************************
 * FUNCTION NAME: c_bt_hid_set_input_report
 * PURPOSE:
 *      The function is used to set input report
 * INPUT:
 *      pbt_addr:device address
 *      preport_data: input report data
 *
 * OUTPUT:
 *      None
 * RETURN:
 *      INT32:error code
 * NOTES:
 *      None
 */
INT32 c_bt_hid_set_input_report(char *pbt_addr, char *preport_data);

/****************************************************
 * FUNCTION NAME: c_bt_hid_get_feature_report
 * PURPOSE:
 *      The function is used to get feature report
 * INPUT:
 *      pbt_addr:device address
 *      reportId: report id
 *     bufferSize : size of the buffer for feature data
 * OUTPUT:
 *      None
 * RETURN:
 *      INT32:error code
 * NOTES:
 *      None
 */
INT32 c_bt_hid_get_feature_report(char *pbt_addr, int reportId, int bufferSize);

/****************************************************
 * FUNCTION NAME: c_bt_hid_set_feature_report
 * PURPOSE:
 *      The function is used to set feature report
 * INPUT:
 *      pbt_addr:device address
 *      preport_data: input report data
 *
 * OUTPUT:
 *      None
 * RETURN:
 *      INT32:error code
 * NOTES:
 *      None
 */
INT32 c_bt_hid_set_feature_report(char *pbt_addr, char *preport_data);

#if defined(MTK_LINUX_HIDH_PTS_TEST) && (MTK_LINUX_HIDH_PTS_TEST == TRUE)
/****************************************************
 * FUNCTION NAME: c_bt_hid_virtual_unplug
 * PURPOSE:
 *      The function is used to send virtual unplug request for test
 * INPUT:
 *      pbt_addr:device address
 *
 * OUTPUT:
 *      None
 * RETURN:
 *      INT32:error code
 * NOTES:
 *      None
 */

INT32 c_bt_hid_virtual_unplug(char *pbt_addr);

/****************************************************
 * FUNCTION NAME: c_bt_hid_send_data
 * PURPOSE:
 *      The function is used to send data for test
 * INPUT:
 *      pbt_addr:device address
 *      psend_data: input send data
 *
 * OUTPUT:
 *      None
 * RETURN:
 *      INT32:error code
 * NOTES:
 *      None
 */
INT32 c_bt_hid_send_data(char *pbt_addr, char *psend_data);
#endif

/****************************************************
 * FUNCTION NAME: c_bt_hid_get_protocol
 * PURPOSE:
 *      The function is used to get  protocol
 * INPUT:
 *      pbt_addr:device address
 *
 *
 * OUTPUT:
 *      None
 * RETURN:
 *      INT32:error code
 * NOTES:
 *      None
 */
INT32 c_bt_hid_get_protocol(char *pbt_addr);

/****************************************************
 * FUNCTION NAME: c_bt_hid_set_protocol
 * PURPOSE:
 *      The function is used to set  protocol
 * INPUT:
 *      pbt_addr:device address
 *      protocol_mode: protocol mode:boot or report mode
 *
 * OUTPUT:
 *      None
 * RETURN:
 *      INT32:error code
 * NOTES:
 *      None
 */
INT32 c_bt_hid_set_protocol(char *pbt_addr, int protocol_mode);

/****************************************************
 * FUNCTION NAME: c_bt_hid_send_control
 * PURPOSE:
 *      The function is used to suspend or exit suspend mode
 * INPUT:
 *      pbt_addr:device address
 *      pcontrol_mode: suspend or exit suspend mode
 *
 * OUTPUT:
 *      None
 * RETURN:
 *      INT32:error code
 * NOTES:
 *      None
 */
EXPORT_SYMBOL INT32 c_bt_hid_send_control(char *pbt_addr, int pcontrol_mode);

/****************************************************
 * FUNCTION NAME: c_btm_bluetooth_hid_set_output_report
 * PURPOSE:
 *      The function is used to set output report
 * INPUT:
 *      pbt_addr:device address
 *      preport_data: output report data
 * OUTPUT:
 *      None
 * RETURN:
 *      INT32:error code
 * NOTES:
 *      None
 */
extern INT32 c_btm_bluetooth_hid_set_output_report(char *pbt_addr, char *preport_data);

/****************************************************
 * FUNCTION NAME: c_btm_get_paired_hid_dev_list
 * PURPOSE:
 *      The function is used to get device history list and its paired or connected status.
 * INPUT:
 *      None
 *
 * OUTPUT:
 *      pt_device_list: hid device history list
 *      pt_hid_status_list: hid device paired or connected status.
 * RETURN:
 *      INT32:error code
 * NOTES:
 *      None
 */
extern INT32 c_btm_get_paired_hid_dev_list(BT_HID_TARGET_DEV_LIST *pt_device_list, BT_HID_STATUS_STRUCT_LIST *pt_hid_status_list);
extern INT32 c_btm_get_hid_target_info(BT_TARGET_DEV_INFO *pt_target_dev_info);
/****************************************************
 * FUNCTION NAME: c_btm_del_paired_hid_dev_one
 * PURPOSE:
 *      The function is used to delete one paired hid device
 * INPUT:
 *      pt_device_info: device info: address and name
 *
 * OUTPUT:
 *      None
 * RETURN:
 *      INT32:error code
 * NOTES:
 *      remove one item from paired device histroy, not do unpair operation
 */
extern INT32 c_btm_del_paired_hid_dev_one(BT_TARGET_DEV_INFO *pt_device_info);

/****************************************************
 * FUNCTION NAME: c_btm_del_paired_hid_dev_all
 * PURPOSE:
 *      The function is used to delete all paired device
 * INPUT:
 *      None
 *
 * OUTPUT:
 *      None
 * RETURN:
 *      INT32:error code
 * NOTES:
 *      None
 */
extern INT32 c_btm_del_paired_hid_dev_all(VOID);

/****************************************************
 * FUNCTION NAME: c_btm_connect_hid_sources
 * PURPOSE:
 *      The function is used to call HID connection
 * INPUT:
 *      *addr               -- device address
 *
 * OUTPUT:
 *      None
 * RETURN:
 *      INT32:error code
 * NOTES:
 *      None
 */
extern INT32 c_btm_connect_hid_sources(char *addr);

/****************************************************
 * FUNCTION NAME: c_btm_disconnect_hid_sources
 * PURPOSE:
 *      The function is used to call HID disconnect
 * INPUT:
 *      *addr               -- device address
 *
 * OUTPUT:
 *      None
 * RETURN:
 *      INT32:error code
 * NOTES:
 *      None
 */
extern INT32 c_btm_disconnect_hid_sources(char *addr);

/****************************************************
 * FUNCTION NAME: c_btm_hid_auto_disconnection
 * PURPOSE:
 *      The function is used to disconnect all hid connected device.
 * INPUT:
 *      None
 * OUTPUT:
 *      None
 * RETURN:
 *      INT32:error code
 * NOTES:
 *      None
 */
extern INT32 c_btm_hid_auto_disconnection(VOID);

#endif

