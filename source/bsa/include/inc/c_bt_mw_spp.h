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

#ifndef _C_BT_MW_SPP_H_
#define _C_BT_MW_SPP_H_

#include "u_bluetooth.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/


/******************** SPP ********************/
/*for certification use*/

/**
 * FUNCTION NAME: c_btm_bt_spp_connect
 * PURPOSE:
 *      The function is used to SPP connect with uuid.
 * INPUT:
 *      addr -- the device address that to connect.
 *      uuid -- using this uuid to connect.
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS           -- Operate success.
 *      BT_ERR_STATUS_FAIL   -- Operate fail.
 * NOTES:
 *      None
 */
INT32 c_btm_bt_spp_connect(CHAR *addr, CHAR *uuid);

/**
 * FUNCTION NAME: c_btm_bt_spp_disconnect
 * PURPOSE:
 *      The function is used to SPP disconnect with port id.
 * INPUT:
 *      port -- the port id to disconnect.
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS           -- Operate success.
 *      BT_ERR_STATUS_FAIL   -- Operate fail.
 * NOTES:
 *      None
 */
INT32 c_btm_bt_spp_disconnect(UINT8 port);

/**
 * FUNCTION NAME: c_btm_bt_spp_send_data
 * PURPOSE:
 *      The function is used to send data with port id.
 * INPUT:
 *      str -- the string to send.
 *      len -- the string length to send.
 *      port -- the port id to send.
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS           -- Operate success.
 *      BT_ERR_STATUS_FAIL   -- Operate fail.
 * NOTES:
 *      None
 */
INT32 c_btm_bt_spp_send_data(CHAR* str, INT32 len, UINT8 port);

/**
 * FUNCTION NAME: c_btm_bt_spp_send_data_fromfilet
 * PURPOSE:
 *      The function is used to send file data with port id.
 * INPUT:
 *      filename -- the file to send, the file name should have absolute path and file name.
 *      port -- the port id to send.
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS           -- Operate success.
 *      BT_ERR_STATUS_FAIL   -- Operate fail.
 * NOTES:
 *      None
 */
INT32 c_btm_bt_spp_send_data_fromfilet(CHAR *filename, UINT8 port);


/*normal use*/
/**
 * FUNCTION NAME: c_btm_spp_connectwithUUID_async
 * PURPOSE:
 *      The function is used to SPP connect with uuid asynchronously.
 * INPUT:
 *      addr -- the device address that to connect.
 *      uuid -- using this uuid to connect.
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS           -- Operate success.
 *      BT_ERR_STATUS_FAIL   -- Operate fail.
 * NOTES:
 *      None
 */
INT32 c_btm_spp_connectwithUUID_async(CHAR* addr, CHAR* uuid);

/**
 * FUNCTION NAME: c_btm_spp_connectwithUUID
 * PURPOSE:
 *      The function is used to SPP connect with uuid synchronously.
 * INPUT:
 *      addr -- the device address that to connect.
 *      uuid -- using this uuid to connect.
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS           -- Operate success.
 *      BT_ERR_STATUS_FAIL   -- Operate fail.
 * NOTES:
 *      None
 */
INT32 c_btm_spp_connectwithUUID(CHAR* addr, CHAR* uuid);

/**
 * FUNCTION NAME: c_btm_spp_disconnect
 * PURPOSE:
 *      The function is used to SPP disconnect with uuid.
 * INPUT:
 *      uuid -- the uuid to disconnect.
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS           -- Operate success.
 *      BT_ERR_STATUS_FAIL   -- Operate fail.
 * NOTES:
 *      None
 */
INT32 c_btm_spp_disconnect(CHAR *uuid);

/**
 * FUNCTION NAME: c_btm_bt_spp_send_data
 * PURPOSE:
 *      The function is used to send data with uuid.
 * INPUT:
 *      str -- the string to send.
 *      len -- the string length to send.
 *      uuid -- the uuid to send.
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS           -- Operate success.
 *      BT_ERR_STATUS_FAIL   -- Operate fail.
 * NOTES:
 *      None
 */
INT32 c_btm_spp_send_data(CHAR* str, INT32 len, CHAR *uuid);

/**
 * FUNCTION NAME: c_btm_spp_send_data_fromfilet
 * PURPOSE:
 *      The function is used to send file data with uuid.
 * INPUT:
 *      filename -- the file to send, the file name should have absolute path and file name.
 *      uuid -- the uuid to send.
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS           -- Operate success.
 *      BT_ERR_STATUS_FAIL   -- Operate fail.
 * NOTES:
 *      None
 */
INT32 c_btm_spp_send_data_fromfilet(CHAR* filename, CHAR *uuid);

/**
 * FUNCTION NAME: c_btm_spp_enable_devb
 * PURPOSE:
 *      The function is used to enable deviceB, the platform is deviceB.
 * INPUT:
 *      uuid -- the uuid to connect/send/disconnect.
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS           -- Operate success.
 *      BT_ERR_STATUS_FAIL   -- Operate fail.
 * NOTES:
 *      None
 */
INT32 c_btm_spp_enable_devb(CHAR* uuid);

/**
 * FUNCTION NAME: c_btm_spp_disable_devb
 * PURPOSE:
 *      The function is used to disable deviceB, the platform is deviceB.
 * INPUT:
 *      uuid -- the uuid to disable.
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS           -- Operate success.
 *      BT_ERR_STATUS_FAIL   -- Operate fail.
 * NOTES:
 *      None
 */
INT32 c_btm_spp_disable_devb(CHAR *uuid);

#endif /*  _BT_MW_SPP_H_ */
