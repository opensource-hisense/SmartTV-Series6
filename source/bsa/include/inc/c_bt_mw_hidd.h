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

/* FILE NAME:  c_bt_mw_hidd.c
 * AUTHOR: zwei chen
 * PURPOSE:
 *      It provides HID device  API to APP.
 * NOTES:
 */

#ifndef __C_BT_MW_HIDD_H__
#define __C_BT_MW_HIDD_H__

/****************************************************
 * FUNCTION NAME: c_bt_hidd_activate
 * PURPOSE:
 *      The function is used to activate hid device
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
INT32 c_bt_hidd_activate(VOID);

/****************************************************
 * FUNCTION NAME: c_bt_hidd_deactivate 
 * PURPOSE:
 *      The function is used to deactivate hid device
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
INT32 c_bt_hidd_deactivate(VOID);


/****************************************************
 * FUNCTION NAME: c_bt_hidd_init
 * PURPOSE:
 *      The function is used to init hid profile for hid device
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
INT32 c_bt_hidd_init(VOID);

/****************************************************
 * FUNCTION NAME: c_bt_hidd_deinit
 * PURPOSE:
 *      The function is used to deinit hid profile for hid device
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
INT32 c_bt_hidd_deinit(VOID);

/****************************************************
 * FUNCTION NAME: c_bt_hidd_connect
 * PURPOSE:
 *      The function is used to connect  hid host
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
INT32 c_bt_hidd_connect(char *pbt_addr);

/****************************************************
 * FUNCTION NAME: c_bt_hid_disconnect
 * PURPOSE:
 *      The function is used to disconnect  hid host
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
INT32 c_bt_hidd_disconnect(CHAR *pbt_addr);

/****************************************************
 * FUNCTION NAME: c_bt_hidd_send_keyboard_data
 * PURPOSE:
 *      The function is used to sent  keyboard data
 * INPUT:
 *      data:keyboard data
 *      dataSize: data size
 *      
 * OUTPUT:
 *      None
 * RETURN:
 *      INT32:error code
 * NOTES:
 *      None
 */
INT32 c_bt_hidd_send_keyboard_data(char *data, int dataSize);

/****************************************************
 * FUNCTION NAME: c_bt_hidd_send_mouse_data
 * PURPOSE:
 *      The function is used to sent  mouse data
 * INPUT:
 *      data:keyboard data
 *      dataSize: data size
 *      
 * OUTPUT:
 *      None
 * RETURN:
 *      INT32:error code
 * NOTES:
 *      None
 */
INT32 c_bt_hidd_send_mouse_data(char *data, int dataSize);

/****************************************************
 * FUNCTION NAME: c_bt_hidd_send_consumer_data
 * PURPOSE:
 *      The function is used to sent  consumer data
 * INPUT:
 *      data:keyboard data
 *      dataSize: data size
 *      
 * OUTPUT:
 *      None
 * RETURN:
 *      INT32:error code
 * NOTES:
 *      None
 */
INT32 c_bt_hidd_send_consumer_data(char *data, int dataSize);

/****************************************************
 * FUNCTION NAME: c_bt_hidd_send_data
 * PURPOSE:
 *      The function is used to sent   data
 * INPUT:
 *      data:keyboard data
 *      dataSize: data size
 *      
 * OUTPUT:
 *      None
 * RETURN:
 *      INT32:error code
 * NOTES:
 *      None
 */
INT32 c_bt_hidd_send_data(char *data, int dataSize);

#endif


