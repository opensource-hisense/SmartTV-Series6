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

/* FILE NAME:  c_bt_mw_gatt.h
 * AUTHOR: Xuemei Yang
 * PURPOSE:
 *      It provides GATTC and GATTS API to APP.
 * NOTES:
 */


#ifndef _C_BT_MW_GATT_H_
#define _C_BT_MW_GATT_H_

/* INCLUDE FILE DECLARATIONS
 */

#include "u_bt_mw_gatt.h"

/* NAMING CONSTANT DECLARATIONS
 */

/* MACRO FUNCTION DECLARATIONS
 */


/* DATA TYPE DECLARATIONS
 */


/******************** gattc ********************/
/**
 * FUNCTION NAME: c_btm_bt_gattc_base_init
 * PURPOSE:
 *      The function is used to register APP callback function.
 * INPUT:
 *      func               -- gatt client app callback function structure
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS                    -- Operate success.
 *      BT_ERR_STATUS_PARM_INVALID    -- paramter invalid.
 * NOTES:
 *      None
 */
extern INT32 c_btm_bt_gattc_base_init(BT_APP_GATTC_CB_FUNC_T *func);

/**
 * FUNCTION NAME: c_btm_bt_gattc_register_app_sync
 * PURPOSE:
 *      The function is used to synchronous register gatt client APP.
 * INPUT:
 *      uuid               -- app uuid
 * OUTPUT:
 *      client_if          -- registered app identifer
 * RETURN:
 *      BT_SUCCESS                        -- Operate success.
 *      BT_ERR_STATUS_FAIL                -- Operate fail.
 *      BT_ERR_STATUS_PARM_INVALID        -- paramter is invalid.
 * NOTES:
 *      None
 */
extern INT32 c_btm_bt_gattc_register_app_sync(CHAR *uuid, INT32 *client_if);

/**
 * FUNCTION NAME: c_btm_bt_gattc_register_app
 * PURPOSE:
 *      The function is used to register gatt client APP.
 * INPUT:
 *      uuid               -- app uuid
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS                        -- Operate success.
 *      BT_ERR_STATUS_FAIL                -- Operate fail.
 *      BT_ERR_STATUS_PARM_INVALID        -- paramter is invalid.
 * NOTES:
 *      None
 */
extern INT32 c_btm_bt_gattc_register_app(CHAR *uuid);

/**
 * FUNCTION NAME: c_btm_bt_gattc_unregister_app
 * PURPOSE:
 *      The function is used to deregister gatt client APP.
 * INPUT:
 *      client_if              -- registered app identifer
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS                        -- Operate success.
 *      BT_ERR_STATUS_FAIL                -- Operate fail.
 *      BT_ERR_STATUS_PARM_INVALID        -- paramter is invalid.
 * NOTES:
 *      None
 */
extern INT32 c_btm_bt_gattc_unregister_app(INT32 client_if);

/**
 * FUNCTION NAME: c_btm_bt_gattc_scan
 * PURPOSE:
 *      The function is used for gatt client scan remote device.
 * INPUT:
 *      client_if              -- registered app identifer
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS                        -- Operate success.
 *      BT_ERR_STATUS_FAIL                -- Operate fail.
 *      BT_ERR_STATUS_PARM_INVALID        -- paramter is invalid.
 * NOTES:
 *      None
 */
extern INT32 c_btm_bt_gattc_scan();

/**
 * FUNCTION NAME: c_btm_bt_gattc_stop_scan
 * PURPOSE:
 *      The function is used for gatt client stop scan remote device.
 * INPUT:
 *      client_if              -- registered app identifer
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS                        -- Operate success.
 *      BT_ERR_STATUS_FAIL                -- Operate fail.
 *      BT_ERR_STATUS_PARM_INVALID        -- paramter is invalid.
 * NOTES:
 *      None
 */
extern INT32 c_btm_bt_gattc_stop_scan();

/**
 * FUNCTION NAME: c_btm_bt_gattc_open
 * PURPOSE:
 *      The function is used for gatt client connect with remote device.
 * INPUT:
 *      client_if              -- registered app identifer
 *      bt_addr                -- remote device bt address
 *      is_direct              -- is direct connection or background connection
 *      transport              -- transport type:(0 : auto, 1 : BREDR, 2 : LE)
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS                        -- Operate success.
 *      BT_ERR_STATUS_FAIL                -- Operate fail.
 *      BT_ERR_STATUS_PARM_INVALID        -- paramter is invalid.
 * NOTES:
 *      None
 */
extern INT32 c_btm_bt_gattc_open(INT32 client_if, CHAR *bt_addr, UINT8 is_direct, INT32 transport);

/**
 * FUNCTION NAME: c_btm_bt_gattc_close
 * PURPOSE:
 *      The function is used for gatt client disconnect with remote device.
 * INPUT:
 *      client_if              -- registered app identifer
 *      bt_addr                -- remote device bt address
 *      conn_id                -- connection id
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS                        -- Operate success.
 *      BT_ERR_STATUS_FAIL                -- Operate fail.
 *      BT_ERR_STATUS_PARM_INVALID        -- paramter is invalid.
 * NOTES:
 *      None
 */
extern INT32 c_btm_bt_gattc_close(INT32 client_if, CHAR *bt_addr, INT32 conn_id);

/**
 * FUNCTION NAME: c_btm_bt_gattc_listen
 * PURPOSE:
 *      The function is used for gatt client listening operation.
 * INPUT:
 *      client_if              -- registered app identifer
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS                        -- Operate success.
 *      BT_ERR_STATUS_FAIL                -- Operate fail.
 *      BT_ERR_STATUS_PARM_INVALID        -- paramter is invalid.
 * NOTES:
 *      None
 */
extern INT32 c_btm_bt_gattc_listen(INT32 client_if);

/**
 * FUNCTION NAME: c_btm_bt_gattc_refresh
 * PURPOSE:
 *      The function is used for gatt client refresh operation.
 * INPUT:
 *      client_if              -- registered app identifer
 *      bt_addr                -- remote device bt address
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS                        -- Operate success.
 *      BT_ERR_STATUS_FAIL                -- Operate fail.
 *      BT_ERR_STATUS_PARM_INVALID        -- paramter is invalid.
 * NOTES:
 *      None
 */
extern INT32 c_btm_bt_gattc_refresh(INT32 client_if, CHAR *bt_addr);

/**
 * FUNCTION NAME: c_btm_bt_gattc_search_service
 * PURPOSE:
 *      The function is used for gatt client search service on the remote device.
 * INPUT:
 *      conn_id                -- connection id
 *      uuid                   -- service uuid
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS                        -- Operate success.
 *      BT_ERR_STATUS_FAIL                -- Operate fail.
 *      BT_ERR_STATUS_PARM_INVALID        -- paramter is invalid.
 * NOTES:
 *      None
 */
extern INT32 c_btm_bt_gattc_search_service(INT32 conn_id, CHAR *uuid);

extern INT32 c_btm_bt_gattc_get_gatt_db(INT32 conn_id);

/**
 * FUNCTION NAME: c_btm_bt_gattc_get_char
 * PURPOSE:
 *      The function is used for gatt client get characiteristic on loacal cache database.
 * INPUT:
 *      conn_id                -- connection id
 *      service_uuid           -- service uuid
 *      service_inst_id        -- service instance id
 *      start_uuid             -- first charateristic uuid
 *      start_inst_id          -- first charateristic instance id
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS                        -- Operate success.
 *      BT_ERR_STATUS_FAIL                -- Operate fail.
 *      BT_ERR_STATUS_PARM_INVALID        -- paramter is invalid.
 * NOTES:
 *      None
 */
extern INT32 c_btm_bt_gattc_get_char(INT32 conn_id,
                               CHAR *service_uuid,
                               INT32 service_inst_id,
                               CHAR *start_uuid,
                               INT32 start_inst_id);

/**
 * FUNCTION NAME: c_btm_bt_gattc_get_descr
 * PURPOSE:
 *      The function is used for gatt client get char description on loacal cache database.
 * INPUT:
 *      conn_id                -- connection id
 *      service_uuid           -- service uuid
 *      service_inst_id        -- service instance id
 *      char_uuid             -- first charateristic uuid
 *      char_inst_id          -- first charateristic instance id
 *      start_uuid             -- first char description uuid
 *      start_inst_id          -- first char description instance id
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS                        -- Operate success.
 *      BT_ERR_STATUS_FAIL                -- Operate fail.
 *      BT_ERR_STATUS_PARM_INVALID        -- paramter is invalid.
 * NOTES:
 *      None
 */
extern INT32 c_btm_bt_gattc_get_descr(INT32 conn_id,
                                CHAR *service_uuid,
                                INT32 service_inst_id,
                                CHAR *char_uuid,
                                INT32 char_inst_id,
                                CHAR *start_uuid,
                                INT32 start_inst_id);

/**
 * FUNCTION NAME: c_btm_bt_gattc_get_incl_service
 * PURPOSE:
 *      The function is used for gatt client get included service on loacal cache database.
 * INPUT:
 *      conn_id                -- connection id
 *      service_uuid           -- service uuid
 *      service_inst_id        -- service instance id
 *      incl_uuid              -- included service uuid
 *      incl_inst_id           -- included service instance id
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS                        -- Operate success.
 *      BT_ERR_STATUS_FAIL                -- Operate fail.
 *      BT_ERR_STATUS_PARM_INVALID        -- paramter is invalid.
 * NOTES:
 *      None
 */
extern INT32 c_btm_bt_gattc_get_incl_service(INT32 conn_id,
                                       CHAR *service_uuid,
                                       INT32 service_inst_id,
                                       CHAR *incl_uuid,
                                       INT32 incl_inst_id);

/**
 * FUNCTION NAME: c_btm_bt_gattc_read_char
 * PURPOSE:
 *      The function is used for gatt client read characteristic from remote device
 * INPUT:
 *      conn_id                -- connection id
 *      service_uuid           -- service uuid
 *      service_inst_id        -- service instance id
 *      char_uuid              -- characteristic uuid
 *      char_inst_id           -- characteristic instance id
 *      auth_req               -- authentication request flag
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS                        -- Operate success.
 *      BT_ERR_STATUS_FAIL                -- Operate fail.
 *      BT_ERR_STATUS_PARM_INVALID        -- paramter is invalid.
 * NOTES:
 *      None
 */
extern INT32 c_btm_bt_gattc_read_char(INT32 conn_id,
                                          INT32 char_handle,
                                INT32 auth_req);

/**
 * FUNCTION NAME: c_btm_bt_gattc_read_descr
 * PURPOSE:
 *      The function is used for gatt client read char description from remote device
 * INPUT:
 *      conn_id                -- connection id
 *      service_uuid           -- service uuid
 *      service_inst_id        -- service instance id
 *      char_uuid              -- characteristic uuid
 *      char_inst_id           -- characteristic instance id
 *      descr_uuid              -- char descriptor uuid
 *      descr_inst_id           -- char descriptor instance id
 *      auth_req               -- authentication request flag
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS                        -- Operate success.
 *      BT_ERR_STATUS_FAIL                -- Operate fail.
 *      BT_ERR_STATUS_PARM_INVALID        -- paramter is invalid.
 * NOTES:
 *      None
 */
extern INT32 c_btm_bt_gattc_read_descr(INT32 conn_id,
                                           INT32 descr_handle,
                                 INT32 auth_req);

/**
 * FUNCTION NAME: c_btm_bt_gattc_write_char
 * PURPOSE:
 *      The function is used for gatt client write characteristic to remote device
 * INPUT:
 *      conn_id                -- connection id
 *      service_uuid           -- service uuid
 *      service_inst_id        -- service instance id
 *      char_uuid              -- characteristic uuid
 *      char_inst_id           -- characteristic instance id
 *      write_type             -- write type(1:WRITE_TYPE_NO_RSP  2:WRITE_TYPE_REQUEST  3:WRITE_TYPE_PREPARE)
 *      len                    -- write characteristic value length
 *      auth_req               -- authentication request flag
 *      value                  -- write characteristic value
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS                        -- Operate success.
 *      BT_ERR_STATUS_FAIL                -- Operate fail.
 *      BT_ERR_STATUS_PARM_INVALID        -- paramter is invalid.
 * NOTES:
 *      None
 */
extern INT32 c_btm_bt_gattc_write_char(INT32 conn_id,
                                           INT32 char_handle,
                                 INT32 write_type,
                                 INT32 len,
                                 INT32 auth_req,
                                 CHAR *value);

extern INT32 c_btm_bt_gattc_execute_write(INT32 conn_id, INT32 execute);


/**
 * FUNCTION NAME: c_btm_bt_gattc_write_descr
 * PURPOSE:
 *      The function is used for gatt client write char description to remote device
 * INPUT:
 *      conn_id                -- connection id
 *      service_uuid           -- service uuid
 *      service_inst_id        -- service instance id
 *      char_uuid              -- characteristic uuid
 *      char_inst_id           -- characteristic instance id
 *      descr_uuid              -- char description uuid
 *      descr_inst_id           -- char description instance id
 *      write_type             -- write type(1:WRITE_TYPE_NO_RSP  2:WRITE_TYPE_REQUEST  3:WRITE_TYPE_PREPARE)
 *      len                    -- write characteristic value length
 *      auth_req               -- authentication request flag
 *      value                  -- write characteristic value
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS                        -- Operate success.
 *      BT_ERR_STATUS_FAIL                -- Operate fail.
 *      BT_ERR_STATUS_PARM_INVALID        -- paramter is invalid.
 * NOTES:
 *      None
 */
extern INT32 c_btm_bt_gattc_write_descr(INT32 conn_id,
                                            INT32 descr_handle,
                                  INT32 write_type,
                                  INT32 len,
                                  INT32 auth_req,
                                  CHAR *value);

/**
 * FUNCTION NAME: c_btm_bt_gattc_reg_noti
 * PURPOSE:
 *      The function is used for gatt client register notification
 * INPUT:
 *      client_if              -- registered client app identifier
 *      bt_addr                -- remote device bt address
 *      service_uuid           -- service uuid
 *      service_inst_id        -- service instance id
 *      char_uuid              -- characteristic uuid
 *      char_inst_id           -- characteristic instance id
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS                        -- Operate success.
 *      BT_ERR_STATUS_FAIL                -- Operate fail.
 *      BT_ERR_STATUS_PARM_INVALID        -- paramter is invalid.
 * NOTES:
 *      None
 */
extern INT32 c_btm_bt_gattc_reg_noti(INT32 client_if,
                               CHAR *bt_addr,
                                         INT32 char_handle);

/**
 * FUNCTION NAME: c_btm_bt_gattc_dereg_noti
 * PURPOSE:
 *      The function is used for gatt client deregister notification
 * INPUT:
 *      client_if              -- registered client app identifier
 *      bt_addr                -- remote device bt address
 *      service_uuid           -- service uuid
 *      service_inst_id        -- service instance id
 *      char_uuid              -- characteristic uuid
 *      char_inst_id           -- characteristic instance id
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS                        -- Operate success.
 *      BT_ERR_STATUS_FAIL                -- Operate fail.
 *      BT_ERR_STATUS_PARM_INVALID        -- paramter is invalid.
 * NOTES:
 *      None
 */
extern INT32 c_btm_bt_gattc_dereg_noti(INT32 client_if,
                                 CHAR *bt_addr,
                                           INT32 char_handle);

/**
 * FUNCTION NAME: c_btm_bt_gattc_read_rssi
 * PURPOSE:
 *      The function is used for gatt client read the received signal strength indicator
 * INPUT:
 *      client_if              -- registered client app identifier
 *      bt_addr                -- remote device bt address
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS                        -- Operate success.
 *      BT_ERR_STATUS_FAIL                -- Operate fail.
 *      BT_ERR_STATUS_PARM_INVALID        -- paramter is invalid.
 * NOTES:
 *      None
 */
extern INT32 c_btm_bt_gattc_read_rssi(INT32 client_if, CHAR *bt_addr);

/**
 * FUNCTION NAME: c_btm_bt_gattc_get_connect_result_info
 * PURPOSE:
 *      The function is used for gatt client to get connection result information
 * INPUT:
 *      None
 * OUTPUT:
 *      connect_rst_info       -- connection result information
 * RETURN:
 *      None
 * NOTES:
 *      None
 */
extern VOID c_btm_bt_gattc_get_connect_result_info(BT_GATTC_CONNECT_RST_T *connect_rst_info);

/**
 * FUNCTION NAME: c_btm_bt_gattc_get_disconnect_result_info
 * PURPOSE:
 *      The function is used for gatt client to get disconnection result information
 * INPUT:
 *      None
 * OUTPUT:
 *      disconnect_rst_info       -- disconnection result information
 * RETURN:
 *      None
 * NOTES:
 *      None
 */
extern VOID c_btm_bt_gattc_get_disconnect_result_info(BT_GATTC_CONNECT_RST_T *disconnect_rst_info);

/**
 * FUNCTION NAME: c_btm_bt_gattc_read_rssi_result_info
 * PURPOSE:
 *      The function is used for gatt client to read received signal strength indicator result inforamtion
 * INPUT:
 *      None
 * OUTPUT:
 *      get_remote_rssi_info     -- received signal strength indicator result inforamtion
 * RETURN:
 *      None
 * NOTES:
 *      None
 */
extern VOID c_btm_bt_gattc_read_rssi_result_info(BT_GATTC_GET_REMOTE_RSSI_T *get_remote_rssi_info);

/**
 * FUNCTION NAME: c_btm_bt_gattc_conn_parameter_update
 * PURPOSE:
 *      The function is used for gatt client to update connection paramters
 * INPUT:
 *      bt_addr                -- remote device bt address
 *      min_interval           -- the minimum allowed connection interval
 *      max_interval           -- the maximum allowed connection interval
 *      latency                -- the maximum allowed connection latency
 *      timeout                -- define the link supervision timeout
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS                        -- Operate success.
 *      BT_ERR_STATUS_FAIL                -- Operate fail.
 *      BT_ERR_STATUS_PARM_INVALID        -- paramter is invalid.
 * NOTES:
 *      None
 */
extern INT32 c_btm_bt_gattc_conn_parameter_update(CHAR *bt_addr,INT32 min_interval,INT32 max_interval,
        												   INT32 latency,INT32 timeout);

/**
 * FUNCTION NAME: c_btm_bt_gattc_set_scan_parameters
 * PURPOSE:
 *      The function is used for gatt client to set scan paramters
 * INPUT:
 *      scan_interval          -- how frequently the controller should scan
 *      scan_window            -- how long the controller should scan
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS                        -- Operate success.
 *      BT_ERR_STATUS_FAIL                -- Operate fail.
 *      BT_ERR_STATUS_PARM_INVALID        -- paramter is invalid.
 * NOTES:
 *      None
 */
extern INT32 c_btm_bt_gattc_set_scan_parameters(INT32 client_if, INT32 scan_interval, INT32 scan_window);

/**
 * FUNCTION NAME: c_btm_bt_gattc_multi_adv_enable
 * PURPOSE:
 *      The function is used for gatt to enable multiple advertising
 * INPUT:
 *      client_if              -- registered client app identifier
 *      min_interval           -- minimum advertising interval
 *      max_interval           -- maximum advertising interval
 *      adv_type               -- advertising type(0:ADV_IND  1:ADV_DIRECT_IND   2:ADV_SCAN_IND
 *                                                 3:ADV_NONCONN_IND  4:SCAN_RSP)
 *      chnl_map               -- advertising channel map
 *      tx_power               -- transmit power(unit in dBm)
 *      timeout_s              -- not used.
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS                        -- Operate success.
 *      BT_ERR_STATUS_FAIL                -- Operate fail.
 *      BT_ERR_STATUS_PARM_INVALID        -- paramter is invalid.
 * NOTES:
 *      None
 */
extern INT32 c_btm_bt_gattc_multi_adv_enable(INT32 client_if,
                                       INT32 min_interval,
                                       INT32 max_interval,
                                       INT32 adv_type,
                                       INT32 chnl_map,
                                       INT32 tx_power,
                                       INT32 timeout_s);

/**
 * FUNCTION NAME: c_btm_bt_gattc_multi_adv_enable_sync
 * PURPOSE:
 *      The function is used for gatt to enable multiple advertising
 * INPUT:
 *      client_if              -- registered client app identifier
 *      min_interval           -- minimum advertising interval
 *      max_interval           -- maximum advertising interval
 *      adv_type               -- advertising type(0:ADV_IND  1:ADV_DIRECT_IND   2:ADV_SCAN_IND
 *                                                 3:ADV_NONCONN_IND  4:SCAN_RSP)
 *      chnl_map               -- advertising channel map
 *      tx_power               -- transmit power(unit in dBm)
 *      timeout_s              -- not used.
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS                        -- Operate success.
 *      BT_ERR_STATUS_FAIL                -- Operate fail.
 *      BT_ERR_STATUS_PARM_INVALID        -- paramter is invalid.
 * NOTES:
 *      None
 */
extern INT32 c_btm_bt_gattc_multi_adv_enable_sync(INT32 client_if,
                                       INT32 min_interval,
                                       INT32 max_interval,
                                       INT32 adv_type,
                                       INT32 chnl_map,
                                       INT32 tx_power,
                                       INT32 timeout_s);


/**
 * FUNCTION NAME: c_btm_bt_gattc_multi_adv_update
 * PURPOSE:
 *      The function is used for gatt to update multiple advertising parameters
 * INPUT:
 *      client_if              -- registered client app identifier
 *      min_interval           -- minimum advertising interval
 *      max_interval           -- maximum advertising interval
 *      adv_type               -- advertising type(0:ADV_IND  1:ADV_DIRECT_IND   2:ADV_SCAN_IND
 *                                                 3:ADV_NONCONN_IND  4:SCAN_RSP)
 *      chnl_map               -- advertising channel map
 *      tx_power               -- transmit power(unit in dBm)
 *      timeout_s              -- not used.
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS                        -- Operate success.
 *      BT_ERR_STATUS_FAIL                -- Operate fail.
 *      BT_ERR_STATUS_PARM_INVALID        -- paramter is invalid.
 * NOTES:
 *      None
 */
extern INT32 c_btm_bt_gattc_multi_adv_update(INT32 client_if,
                                       INT32 min_interval,
                                       INT32 max_interval,
                                       INT32 adv_type,
                                       INT32 chnl_map,
                                       INT32 tx_power,
                                       INT32 timeout_s);

/**
 * FUNCTION NAME: c_btm_bt_gattc_multi_adv_setdata
 * PURPOSE:
 *      The function is used for gatt to set multiple advertising data
 * INPUT:
 *      client_if              -- registered client app identifier
 *      set_scan_rsp           -- set scan response flag
 *      include_name           -- include device name flag
 *      include_txpower        -- include transmit power flag
 *      appearance             -- appearance data
 *      manufacturer_len       -- manufacturer data length
 *      manufacturer_data      -- manufacturer data
 *      service_data_len       -- service data length
 *      service_data           -- service data
 *      service_uuid_len       -- service uuid length
 *      service_uuid           -- service uuid
 *      le_name_len            -- device name length
 *      le_name                -- device name
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS                        -- Operate success.
 *      BT_ERR_STATUS_FAIL                -- Operate fail.
 *      BT_ERR_STATUS_PARM_INVALID        -- paramter is invalid.
 * NOTES:
 *      None
 */
extern INT32 c_btm_bt_gattc_multi_adv_setdata(INT32 client_if,
                                        UINT8 set_scan_rsp,
                                        UINT8 include_name,
                                        UINT8 include_txpower,
                                        INT32 appearance,
                                        INT32 manufacturer_len,
                                        CHAR* manufacturer_data,
                                        INT32 service_data_len,
                                        CHAR* service_data,
                                        INT32 service_uuid_len,
                                        CHAR* service_uuid);

/**
 * FUNCTION NAME: c_btm_bt_gattc_multi_adv_setdata_sync
 * PURPOSE:
 *      The function is used for gatt to set multiple advertising data
 * INPUT:
 *      client_if              -- registered client app identifier
 *      set_scan_rsp           -- set scan response flag
 *      include_name           -- include device name flag
 *      include_txpower        -- include transmit power flag
 *      appearance             -- appearance data
 *      manufacturer_len       -- manufacturer data length
 *      manufacturer_data      -- manufacturer data
 *      service_data_len       -- service data length
 *      service_data           -- service data
 *      service_uuid_len       -- service uuid length
 *      service_uuid           -- service uuid
 *      le_name_len            -- device name length
 *      le_name                -- device name
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS                        -- Operate success.
 *      BT_ERR_STATUS_FAIL                -- Operate fail.
 *      BT_ERR_STATUS_PARM_INVALID        -- paramter is invalid.
 * NOTES:
 *      None
 */
extern INT32 c_btm_bt_gattc_multi_adv_setdata_sync(INT32 client_if,
                                        UINT8 set_scan_rsp,
                                        UINT8 include_name,
                                        UINT8 include_txpower,
                                        INT32 appearance,
                                        INT32 manufacturer_len,
                                        CHAR* manufacturer_data,
                                        INT32 service_data_len,
                                        CHAR* service_data,
                                        INT32 service_uuid_len,
                                        CHAR* service_uuid);


/**
 * FUNCTION NAME: c_btm_bt_gattc_multi_adv_disable
 * PURPOSE:
 *      The function is used for gatt to disable multiple advertising
 * INPUT:
 *      client_if              -- registered client app identifier
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS                        -- Operate success.
 *      BT_ERR_STATUS_FAIL                -- Operate fail.
 *      BT_ERR_STATUS_PARM_INVALID        -- paramter is invalid.
 * NOTES:
 *      None
 */
extern INT32 c_btm_bt_gattc_multi_adv_disable(INT32 client_if);

extern INT32 c_btm_bt_gattc_batchscan_cfg_storage(INT32 client_if, INT32 batch_scan_full_max,
                                                INT32 batch_scan_trunc_max, INT32 batch_scan_notify_threshold);

extern INT32 c_btm_bt_gattc_batchscan_enb_batch_scan(INT32 client_if, INT32 scan_mode,
                        INT32 scan_interval, INT32 scan_window, INT32 addr_type, INT32 discard_rule);

extern INT32 c_btm_bt_gattc_batchscan_dis_batch_scan(INT32 client_if);

extern INT32 c_btm_bt_gattc_batchscan_read_reports(INT32 client_if, INT32 scan_mode);

extern INT32 c_btm_gattc_scan_filter_param_setup(bluetooth_gatt_filt_param_setup_t scan_filt_param);
extern INT32 c_btm_gattc_scan_filter_enable(INT32 client_if);
extern INT32 c_btm_gattc_scan_filter_disable(INT32 client_if);
extern INT32 c_btm_gattc_scan_filter_add_remove(INT32 client_if, INT32 action,
                                             INT32 filt_type, INT32 filt_index, INT32 company_id,
                                             INT32 company_id_mask, const CHAR *p_uuid,
                                             const CHAR *p_uuid_mask, const CHAR *bd_addr,
                                             CHAR addr_type, INT32 data_len, CHAR *p_data, INT32 mask_len,
                                             CHAR *p_mask);
extern INT32 c_btm_gattc_scan_filter_clear(INT32 client_if, INT32 filt_index);

extern INT32 c_btm_gattc_get_device_type(CHAR *bt_addr);


extern INT32 c_btm_gattc_set_local_le_name(INT32 client_if, CHAR *le_name);

extern INT32 c_btm_gattc_set_local_disc_mode(INT32 client_if, INT32 disc_mode);

extern INT32 c_btm_gattc_get_local_adv_rpa(INT32 client_if);

extern INT32 c_btm_gattc_configure_mtu(INT32 conn_id, INT32 mtu);

extern INT32 c_btm_gattc_test_command(INT32 command, BT_GATTC_TEST_PARAMS_T test_params);

extern INT32 c_btm_gattc_read_using_char_uuid(INT32 conn_id,
                                                        INT32 start_handle,
                                                        INT32 end_handle,
                                                        CHAR *uuid,
                                                        INT32 auth_req);

extern INT32 c_btm_gattc_read_long_characteristic(INT32 conn_id,
                                                    INT32 handle,
                                                    INT32 offset,
                                                    INT32 auth_req);

extern INT32 c_btm_gattc_read_multi_characteristic(INT32 conn_id,
                                                 INT32 num_attr,
                                                 UINT16 *handles,
                                                 INT32 auth_req);

extern INT32 c_btm_gattc_read_long_descr(INT32 conn_id,
                                                 INT32 handle,
                                                 INT32 offset,
                                                 INT32 auth_req);

extern INT32 c_btm_gattc_write_long_characteristic(INT32 conn_id,
                                                     INT32 char_handle,
                                                     INT32 write_type,
                                                     INT32 len,
                                                     INT32 offset,
                                                     INT32 auth_req,
                                                     CHAR *value);

extern INT32 c_btm_gattc_write_long_descr(INT32 conn_id,
                                                     INT32 descr_handle,
                                                     INT32 write_type,
                                                     INT32 len,
                                                     INT32 offset,
                                                     INT32 auth_req,
                                                     CHAR *value);
extern INT32 c_btm_gattc_set_pts_flag(UINT8 pts_flag);

/******************** gatts ********************/
/**
 * FUNCTION NAME: c_btm_bt_gatts_base_init
 * PURPOSE:
 *      The function is used to gatt server register APP callback function.
 * INPUT:
 *      func               -- gatt server app callback function structure
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS                    -- Operate success.
 *      BT_ERR_STATUS_PARM_INVALID    -- paramter invalid.
 * NOTES:
 *      None
 */
extern INT32 c_btm_bt_gatts_base_init(BT_APP_GATTS_CB_FUNC_T *func);

/**
 * FUNCTION NAME: c_btm_bt_gatts_register_server_sync
 * PURPOSE:
 *      The function is used to synchronous register gatt server APP.
 * INPUT:
 *      uuid               -- app uuid
 * OUTPUT:
 *      server_if          -- registered app identifer
 * RETURN:
 *      BT_SUCCESS                        -- Operate success.
 *      BT_ERR_STATUS_FAIL                -- Operate fail.
 *      BT_ERR_STATUS_PARM_INVALID        -- paramter is invalid.
 * NOTES:
 *      None
 */
extern INT32 c_btm_bt_gatts_register_server_sync(CHAR *uuid, INT32 *server_if);

/**
 * FUNCTION NAME: c_btm_bt_gatts_register_server
 * PURPOSE:
 *      The function is used to register gatt server APP.
 * INPUT:
 *      uuid               -- app uuid
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS                        -- Operate success.
 *      BT_ERR_STATUS_FAIL                -- Operate fail.
 *      BT_ERR_STATUS_PARM_INVALID        -- paramter is invalid.
 * NOTES:
 *      None
 */
extern INT32 c_btm_bt_gatts_register_server(CHAR *uuid);

/**
 * FUNCTION NAME: c_btm_bt_gatts_unregister_server
 * PURPOSE:
 *      The function is used to deregister gatt server APP.
 * INPUT:
 *      server_if              -- registered app identifer
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS                        -- Operate success.
 *      BT_ERR_STATUS_FAIL                -- Operate fail.
 *      BT_ERR_STATUS_PARM_INVALID        -- paramter is invalid.
 * NOTES:
 *      None
 */
extern INT32 c_btm_bt_gatts_unregister_server(INT32 server_if);

/**
 * FUNCTION NAME: c_btm_bt_gattc_open
 * PURPOSE:
 *      The function is used for gatt server connect with remote device.
 * INPUT:
 *      server_if              -- registered app identifer
 *      bt_addr                -- remote device bt address
 *      is_direct              -- is direct connection or background connection
 *      transport              -- transport type:(0 : auto, 1 : BREDR, 2 : LE)
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS                        -- Operate success.
 *      BT_ERR_STATUS_FAIL                -- Operate fail.
 *      BT_ERR_STATUS_PARM_INVALID        -- paramter is invalid.
 * NOTES:
 *      None
 */
extern INT32 c_btm_bt_gatts_open(INT32 server_if, CHAR *bt_addr, UINT8 is_direct, INT32 transport);

/**
 * FUNCTION NAME: c_btm_bt_gatts_close
 * PURPOSE:
 *      The function is used for gatt server disconnect with remote device.
 * INPUT:
 *      server_if              -- registered app identifer
 *      bt_addr                -- remote device bt address
 *      conn_id                -- connection id
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS                        -- Operate success.
 *      BT_ERR_STATUS_FAIL                -- Operate fail.
 *      BT_ERR_STATUS_PARM_INVALID        -- paramter is invalid.
 * NOTES:
 *      None
 */
extern INT32 c_btm_bt_gatts_close(INT32 server_if, CHAR *bt_addr, INT32 conn_id);

/**
 * FUNCTION NAME: c_btm_bt_gatts_gatts_add_service_sync
 * PURPOSE:
 *      The function is used for gatt server synchronous add service to database.
 * INPUT:
 *      server_if              -- registered app identifer
 *      service_uuid           -- service uuid
 *      is_primary             -- is primary service or not
 *      number                 -- handle number
 * OUTPUT:
 *      srvc_handle            -- added service start handle
 * RETURN:
 *      BT_SUCCESS                        -- Operate success.
 *      BT_ERR_STATUS_FAIL                -- Operate fail.
 *      BT_ERR_STATUS_PARM_INVALID        -- paramter is invalid.
 * NOTES:
 *      None
 */
extern INT32 c_btm_bt_gatts_gatts_add_service_sync(INT32 server_if, CHAR *service_uuid,
                                                    UINT8 is_primary,
                                                    INT32 number, INT32 *srvc_handle);

/**
 * FUNCTION NAME: c_btm_bt_gatts_add_service
 * PURPOSE:
 *      The function is used for gatt server add service to database.
 * INPUT:
 *      server_if              -- registered app identifer
 *      service_uuid           -- service uuid
 *      is_primary             -- is primary service or not
 *      number                 -- handle number
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS                        -- Operate success.
 *      BT_ERR_STATUS_FAIL                -- Operate fail.
 *      BT_ERR_STATUS_PARM_INVALID        -- paramter is invalid.
 * NOTES:
 *      None
 */
extern INT32 c_btm_bt_gatts_add_service(INT32 server_if,
                                  CHAR *service_uuid,
                                  UINT8 is_primary,
                                  INT32 number);

/**
 * FUNCTION NAME: c_btm_bt_gatts_add_included_service
 * PURPOSE:
 *      The function is used for gatt server add included service to database.
 * INPUT:
 *      server_if              -- registered app identifer
 *      service_handle         -- added service start handle
 *      included_handle        -- include service handle
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS                        -- Operate success.
 *      BT_ERR_STATUS_FAIL                -- Operate fail.
 *      BT_ERR_STATUS_PARM_INVALID        -- paramter is invalid.
 * NOTES:
 *      None
 */
extern INT32 c_btm_bt_gatts_add_included_service(INT32 server_if,
                                            INT32 service_handle,
                                            INT32 included_handle);

/**
 * FUNCTION NAME: c_btm_bt_gatts_add_char_sync
 * PURPOSE:
 *      The function is used for gatt server synchronous add characteristic to database.
 * INPUT:
 *      server_if              -- registered app identifer
 *      service_handle         -- added service start handle
 *      char_uuid              -- characteristic uuid
 *      properties             -- characteristic properties
 *      permissions            -- access characteristic permissions
 * OUTPUT:
 *      char_handle            -- added characteristic handle
 * RETURN:
 *      BT_SUCCESS                        -- Operate success.
 *      BT_ERR_STATUS_FAIL                -- Operate fail.
 *      BT_ERR_STATUS_PARM_INVALID        -- paramter is invalid.
 * NOTES:
 *      None
 */
extern INT32 c_btm_bt_gatts_add_char_sync(INT32 server_if, INT32 service_handle, CHAR *char_uuid,
                                          INT32 properties, INT32 permissions, INT32 *char_handle);

/**
 * FUNCTION NAME: c_btm_bt_gatts_add_char
 * PURPOSE:
 *      The function is used for gatt server add characteristic to database.
 * INPUT:
 *      server_if              -- registered app identifer
 *      service_handle         -- added service start handle
 *      char_uuid              -- characteristic uuid
 *      properties             -- characteristic properties
 *      permissions            -- access characteristic permissions
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS                        -- Operate success.
 *      BT_ERR_STATUS_FAIL                -- Operate fail.
 *      BT_ERR_STATUS_PARM_INVALID        -- paramter is invalid.
 * NOTES:
 *      None
 */
extern INT32 c_btm_bt_gatts_add_char(INT32 server_if,
                               INT32 service_handle,
                               CHAR *uuid,
                               INT32 properties,
                               INT32 permissions);

/**
 * FUNCTION NAME: c_btm_bt_gatts_add_desc
 * PURPOSE:
 *      The function is used for gatt server add char description to database.
 * INPUT:
 *      server_if              -- registered app identifer
 *      service_handle         -- added service start handle
 *      uuid                   -- char description uuid
 *      permissions            -- access char description permissions
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS                        -- Operate success.
 *      BT_ERR_STATUS_FAIL                -- Operate fail.
 *      BT_ERR_STATUS_PARM_INVALID        -- paramter is invalid.
 * NOTES:
 *      None
 */
extern INT32 c_btm_bt_gatts_add_desc(INT32 server_if,
                               INT32 service_handle,
                               CHAR *uuid,
                               INT32 permissions);

/**
 * FUNCTION NAME: c_btm_bt_gatts_start_service
 * PURPOSE:
 *      The function is used for gatt server start service.
 * INPUT:
 *      server_if              -- registered app identifer
 *      service_handle         -- added service start handle
 *      transport              -- transport type:(0 : auto, 1 : BREDR, 2 : LE)
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS                        -- Operate success.
 *      BT_ERR_STATUS_FAIL                -- Operate fail.
 *      BT_ERR_STATUS_PARM_INVALID        -- paramter is invalid.
 * NOTES:
 *      None
 */
extern INT32 c_btm_bt_gatts_start_service(INT32 server_if, INT32 service_handle, INT32 transport);

/**
 * FUNCTION NAME: c_btm_bt_gatts_start_service_sync
 * PURPOSE:
 *      The function is used for gatt server start service.
 * INPUT:
 *      server_if              -- registered app identifer
 *      service_handle         -- added service start handle
 *      transport              -- transport type:(0 : auto, 1 : BREDR, 2 : LE)
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS                        -- Operate success.
 *      BT_ERR_STATUS_FAIL                -- Operate fail.
 *      BT_ERR_STATUS_PARM_INVALID        -- paramter is invalid.
 * NOTES:
 *      None
 */
extern INT32 c_btm_bt_gatts_start_service_sync(INT32 server_if, INT32 service_handle, INT32 transport);

/**
 * FUNCTION NAME: c_btm_bt_gatts_stop_service
 * PURPOSE:
 *      The function is used for gatt server stop service.
 * INPUT:
 *      server_if              -- registered app identifer
 *      service_handle         -- added service start handle
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS                        -- Operate success.
 *      BT_ERR_STATUS_FAIL                -- Operate fail.
 *      BT_ERR_STATUS_PARM_INVALID        -- paramter is invalid.
 * NOTES:
 *      None
 */
extern INT32 c_btm_bt_gatts_stop_service(INT32 server_if, INT32 service_handle);

/**
 * FUNCTION NAME: c_btm_bt_gatts_delete_service
 * PURPOSE:
 *      The function is used for gatt server delete service.
 * INPUT:
 *      server_if              -- registered app identifer
 *      service_handle         -- added service start handle
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS                        -- Operate success.
 *      BT_ERR_STATUS_FAIL                -- Operate fail.
 *      BT_ERR_STATUS_PARM_INVALID        -- paramter is invalid.
 * NOTES:
 *      None
 */
extern INT32 c_btm_bt_gatts_delete_service(INT32 server_if, INT32 service_handle);

/**
 * FUNCTION NAME: c_btm_bt_gatts_send_indication
 * PURPOSE:
 *      The function is used for gatt server send indication to remote device.
 * INPUT:
 *      server_if              -- registered app identifer
 *      attribute_handle       -- send indication attribute handle
 *      conn_id                -- connection id
 *      fg_confirm             -- is need confirmation or not
 *      p_value                -- send indication value
 *      value_len              -- send indication value length
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS                        -- Operate success.
 *      BT_ERR_STATUS_FAIL                -- Operate fail.
 *      BT_ERR_STATUS_PARM_INVALID        -- paramter is invalid.
 * NOTES:
 *      None
 */
extern INT32 c_btm_bt_gatts_send_indication(INT32 server_if,
                                      INT32 attribute_handle,
                                      INT32 conn_id,
                                      INT32 fg_confirm,
                                      CHAR *p_value,
                                      INT32 value_len);

/**
 * FUNCTION NAME: c_btm_bt_gatts_send_response
 * PURPOSE:
 *      The function is used for gatt server send response to remote device.
 * INPUT:
 *      conn_id                -- connection id
 *      trans_id               -- transaction id
 *      status                 -- send response status
 *      handle                 -- send response handle
 *      p_value                -- send response value
 *      value_len              -- send response value length
 *      auth_req               -- authentication request
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS                        -- Operate success.
 *      BT_ERR_STATUS_FAIL                -- Operate fail.
 *      BT_ERR_STATUS_PARM_INVALID        -- paramter is invalid.
 * NOTES:
 *      None
 */
extern INT32 c_btm_bt_gatts_send_response(INT32 conn_id,
                                    INT32 trans_id,
                                    INT32 status,
                                    INT32 handle,
                                    CHAR *p_value,
                                    INT32 value_len,
                                    INT32 auth_req);

/**
 * FUNCTION NAME: c_btm_bt_gatt_parse_adv_data
 * PURPOSE:
 *      The function is used for gatt to parse advertising data.
 * INPUT:
 *      adv_data               -- advertising data
 * OUTPUT:
 *      None
 * RETURN:
 *      None
 * NOTES:
 *      None
 */
extern VOID c_btm_bt_gatt_parse_adv_data (UINT8 *adv_data);

/**
 * FUNCTION NAME: c_btm_bt_gatts_get_connect_result_info
 * PURPOSE:
 *      The function is used for gatt server to get connection result information.
 * INPUT:
 *      None
 * OUTPUT:
 *      connect_rst_info       -- connection result information
 * RETURN:
 *      None
 * NOTES:
 *      None
 */
extern VOID c_btm_bt_gatts_get_connect_result_info(BT_GATTS_CONNECT_RST_T *connect_rst_info);

/**
 * FUNCTION NAME: c_btm_bt_gatts_get_disconnect_result_info
 * PURPOSE:
 *      The function is used for gatt server to get disconnection result information.
 * INPUT:
 *      None
 * OUTPUT:
 *      disconnect_rst_info     -- disconnection result information
 * RETURN:
 *      None
 * NOTES:
 *      None
 */
extern VOID c_btm_bt_gatts_get_disconnect_result_info(BT_GATTS_CONNECT_RST_T *disconnect_rst_info);

extern VOID c_btm_bt_gatts_mtu_changed_cbk(INT32 conn_id, INT32 mtu);

extern VOID c_btm_bt_gatts_request_exec_write_cbk(INT32 conn_id, INT32 trans_id, CHAR *bda, INT32 exec_write);

/**
 * FUNCTION NAME: c_btm_gatt_reg_nfy
 * PURPOSE:
 *      The function is used for gatt server to register callback for app.
 * INPUT:
 *      pf_nfy                 -- gatt write attribute value callback for app
 *      pv_tag                 -- app delegate data
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS                        -- Operate success.
 * NOTES:
 *      None
 */
extern INT32 c_btm_gatt_reg_nfy(a_mtkapi_bt_gatt_nfy_fct_cbk pf_nfy, VOID * pv_tag);

/**
 * FUNCTION NAME: c_btm_gatt_reg_evt
 * PURPOSE:
 *      Not used.
 * INPUT:
 *      pf_evt                 -- not used
 *      pv_tag                 -- app delegate data
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS                        -- Operate success.
 * NOTES:
 *      None
 */
extern INT32 c_btm_gatt_reg_evt(a_mtkapi_bt_gatt_evt_fct_cbk pf_evt, VOID * pv_tag);

//extern VOID c_btm_gatt_power_on();
//extern VOID otherInitAfterBtInit(VOID);

/**
 * FUNCTION NAME: c_btm_gatt_initialize
 * PURPOSE:
 *      The function is used for gatt server to do initilization.
 * INPUT:
 *      None
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS                        -- Operate success.
 *      BT_ERR_STATUS_FAIL                -- Operate fail.
 *      BT_ERR_STATUS_PARM_INVALID        -- paramter is invalid.
 * NOTES:
 *      None
 */
extern INT32 c_btm_gatt_initialize();

/**
 * FUNCTION NAME: c_btm_gatt_finalize
 * PURPOSE:
 *      The function is used for gatt server to do uninitilization.
 * INPUT:
 *      None
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS                        -- Operate success.
 *      BT_ERR_STATUS_FAIL                -- Operate fail.
 *      BT_ERR_STATUS_PARM_INVALID        -- paramter is invalid.
 * NOTES:
 *      None
 */
extern INT32 c_btm_gatt_finalize();

/**
 * FUNCTION NAME: c_btm_gatt_setDelegate
 * PURPOSE:
 *      The function is used for setting up an observer which should notified whenever a characteristic is written to,
 *      but not used in MW.
 * INPUT:
 *      delegate       -- observer
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS                        -- Operate success.
 * NOTES:
 *      None
 */
extern INT32 c_btm_gatt_setDelegate(INT32 delegate);

/**
 * FUNCTION NAME: c_btm_gatt_onCharacteristicWrite
 * PURPOSE:
 *      The function is used for whenever a characteristic is written to,
 *      but not used in MW.
 * INPUT:
 *      service_uuid         -- service uuid which include the characteristic
 *      char_uuid            -- characteristic uuid
 *      value                -- characteristic value
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS                        -- Operate success.
 * NOTES:
 *      None
 */
extern INT32 c_btm_gatt_onCharacteristicWrite(CHAR * service_uuid, CHAR * char_uuid, CHAR * value);

/**
 * FUNCTION NAME: c_btm_gatt_isSupported
 * PURPOSE:
 *      The function is used to judge the device supports bluetooth operations or not.
 * INPUT:
 *      None
 * OUTPUT:
 *      None
 * RETURN:
 *      TRUE      -- support bluetooth operations.
 * NOTES:
 *      None
 */
extern BOOL c_btm_gatt_isSupported();

/**
 * FUNCTION NAME: c_btm_gatt_createService
 * PURPOSE:
 *      The function is used to create a GATT service with the specified service uuid.
 * INPUT:
 *      service_uuid         -- service uuid which need to be created
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS                        -- Operate success.
 *      BT_ERR_STATUS_FAIL                -- Operate fail.
 *      BT_ERR_STATUS_PARM_INVALID        -- paramter is invalid.
 * NOTES:
 *      None
 */
extern INT32 c_btm_gatt_createService(CHAR * service_uuid);

/**
 * FUNCTION NAME: c_btm_gatt_destroyService
 * PURPOSE:
 *      The function is used to destroy a GATT service with the specified service uuid.
 * INPUT:
 *      service_uuid         -- service uuid which need to be desctoryed
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS                        -- Operate success.
 *      BT_ERR_STATUS_FAIL                -- Operate fail.
 *      BT_ERR_STATUS_PARM_INVALID        -- paramter is invalid.
 * NOTES:
 *      None
 */
extern INT32 c_btm_gatt_destroyService(CHAR * service_uuid);

/**
 * FUNCTION NAME: c_btm_gatt_startService
 * PURPOSE:
 *      The function is used to start a created GATT service, this triggers advertising, and enables
 *      connections to the service, enabling attribute I/O.
 * INPUT:
 *      service_uuid         -- service uuid which need to be started
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS                        -- Operate success.
 *      BT_ERR_STATUS_FAIL                -- Operate fail.
 *      BT_ERR_STATUS_PARM_INVALID        -- paramter is invalid.
 * NOTES:
 *      None
 */
extern INT32 c_btm_gatt_startService(CHAR * service_uuid);



/**
 * FUNCTION NAME: c_btm_gatt_stopService
 * PURPOSE:
 *      The function is used to stop a started GATT service, disable advertisenment, and disable
 *      connections.
 * INPUT:
 *      service_uuid         -- service uuid which need to be stopped.
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS                        -- Operate success.
 *      BT_ERR_STATUS_FAIL                -- Operate fail.
 *      BT_ERR_STATUS_PARM_INVALID        -- paramter is invalid.
 * NOTES:
 *      None
 */
extern INT32 c_btm_gatt_stopService(CHAR * service_uuid);

/**
 * FUNCTION NAME: c_btm_gatt_setDeviceName
 * PURPOSE:
 *      The function is used to set local device name, this can be included in advertisments or scan responses.
 * INPUT:
 *      name         -- local device name.
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS                    -- Operate success.
 *      BT_ERR_STATUS_NOMEM           -- no memory.
 *      BT_ERR_STATUS_PARM_INVALID    -- paramter is invalid.
 * NOTES:
 *      None
 */
extern INT32 c_btm_gatt_setDeviceName(CHAR * name);

/**
 * FUNCTION NAME: c_btm_gatt_setAdvertisement
 * PURPOSE:
 *      The function is used to set advertisment, customizes the payload data of the GAP service advertisment.
 * INPUT:
 *      service_uuid         -- the created service uuid
 *      advertised_uuid      -- uuid to put in the complete list of 16bit service class uuid field of the payload.
 *      advertise_data       -- data to put in the service data field of the payload.
 *      manufacturer_data    -- the value to put in the manufacturer specific data field of the payload.
 *      transmit_name        -- if true, the name set by SetDeviceName is sent in Local Name field.
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS                    -- Operate success.
 *      BT_ERR_STATUS_NOMEM           -- no memory.
 *      BT_ERR_STATUS_PARM_INVALID    -- paramter is invalid.
 *      BT_ERR_STATUS_FAIL            -- Operate fail.
 * NOTES:
 *      None
 */
extern INT32 c_btm_gatt_setAdvertisement(CHAR * service_uuid, CHAR * advertised_uuid,
                                  CHAR * advertise_data, CHAR * manufacturer_data, BOOL transmit_name);

/**
 * FUNCTION NAME: c_btm_gatt_setScanResponse
 * PURPOSE:
 *      The function is used to set scan response data, customizes the payload data of the GAP scan response.
 * INPUT:
 *      service_uuid         -- the created service uuid
 *      advertised_uuid      -- uuid to put in the complete list of 16bit service class uuid field of the payload.
 *      advertise_data       -- data to put in the service data field of the payload.
 *      manufacturer_data    -- the value to put in the manufacturer specific data field of the payload.
 *      transmit_name        -- if true, the name set by SetDeviceName is sent in Local Name field.
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS                    -- Operate success.
 *      BT_ERR_STATUS_NOMEM           -- no memory.
 *      BT_ERR_STATUS_PARM_INVALID    -- paramter is invalid.
 *      BT_ERR_STATUS_FAIL            -- Operate fail.
 * NOTES:
 *      None
 */
extern INT32 c_btm_gatt_setScanResponse(CHAR * service_uuid, CHAR * advertised_uuid,
                                        CHAR * advertise_data, CHAR * manufacturer_data,
                                        BOOL transmit_name);

/**
 * FUNCTION NAME: c_btm_gatt_addCharacteristic
 * PURPOSE:
 *      The function is used to create a GATT characteristic, this should be done prior to starting.
 * INPUT:
 *      service_uuid         -- the created service uuid
 *      attribute_uuid       -- the uuid of the characteristic to add.
 *      control_uuid         -- gatt characteristics have a max length of 512 btyes. For data longer than this,
 *                              there is an additional control_uuid to specify which 512 btye block of that data
 *                              should be displayed in th characteristic with attribute_id, it should be readable
 *                              and writable.
 *      option               -- list if options(read,write,notify).
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS                    -- Operate success.
 *      BT_ERR_STATUS_NOMEM           -- no memory.
 *      BT_ERR_STATUS_PARM_INVALID    -- paramter is invalid.
 *      BT_ERR_STATUS_FAIL                -- Operate fail.
 * NOTES:
 *      None
 */
extern INT32 c_btm_gatt_addCharacteristic(CHAR * service_uuid, CHAR * attribute_uuid,
                                          CHAR * control_uuid, CHAR * option);

/**
 * FUNCTION NAME: c_btm_gatt_setCharacteristicValue
 * PURPOSE:
 *      The function is used to set the value of a readable attribute.
 * INPUT:
 *      service_uuid         -- the created service uuid
 *      attribute_uuid       -- uthe uuid of the char to set value.
 *      value                -- new value to associate with the characteristic. The value may be truncated to 512 bytes
 *                              if a control_uuid was not specified when the attribute was created.
 *      length               -- the value length.
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS                    -- Operate success.
 *      BT_ERR_STATUS_NOMEM           -- no memory.
 *      BT_ERR_STATUS_PARM_INVALID    -- paramter is invalid.
 *      BT_ERR_STATUS_FAIL                -- Operate fail.
 * NOTES:
 *      None
 */
extern INT32 c_btm_gatt_setCharacteristicValue(CHAR * service_uuid, CHAR  * attribute_uuid, CHAR * value, UINT32 length);

#endif /*  _C_BT_MW_GATT_H_  */

