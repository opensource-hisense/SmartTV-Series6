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

/* FILE NAME:  u_bt_mw_gatt.h
 * AUTHOR: Xuemei Yang
 * PURPOSE:
 *      It provides GATTC and GATTS structure to APP.
 * NOTES:
 */


#ifndef _U_BT_MW_GATT_H_
#define _U_BT_MW_GATT_H_

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/

//#include "u_common.h"
#include "u_bt_mw_common.h"

#define BT_GATT_MAX_ATTR_LEN 600
#define BT_GATT_MAX_UUID_LEN 37
#define BT_GATT_MAX_MTU_SIZE 517
#define BT_GATT_MIN_MTU_SIZE 23

#define MTK_LINUX_GATT           1

#if MTK_LINUX_GATT
#define MTK_LINUX_GATTC_LE_NAME  1
#define MTK_LINUX_GATTC_RPA      1
#define MTK_LINUX_GATTC_PTS_TEST 0
#define MTK_LINUX_GATTC_DISC_MODE 1
#else
#define MTK_LINUX_GATTC_LE_NAME  0
#define MTK_LINUX_GATTC_RPA      0
#define MTK_LINUX_GATTC_PTS_TEST 0
#define MTK_LINUX_GATTC_DISC_MODE 0
#endif

/** GATT ID adding instance id tracking to the UUID */
typedef struct
{
    CHAR  uuid[BT_GATT_MAX_UUID_LEN];
    UINT8 inst_id;
} BT_GATT_ID_T;


/** GATT Service ID also identifies the service type (primary/secondary) */
typedef struct
{
    BT_GATT_ID_T    id;
    UINT8 is_primary;
} BT_GATTS_SRVC_ID_T;


typedef struct
{
    INT32 client_if;
    CHAR uuid[BT_GATT_MAX_UUID_LEN];
} BT_GATTC_REG_CLIENT_T;


typedef struct
{
    INT32 rssi;
    CHAR btaddr[MAX_BDADDR_LEN];
    CHAR uuid[BT_GATT_MAX_UUID_LEN];
    CHAR manu_spec_data[MAX_STR_LEN];
    CHAR name[MAX_NAME_LEN];
} BT_GATTC_SCAN_RST_T;

typedef struct
{
    INT32 conn_id;
    INT32 client_if;
    CHAR btaddr[MAX_BDADDR_LEN];
} BT_GATTC_CONNECT_RST_T;

typedef struct
{
    INT32 conn_id;
    BT_GATTS_SRVC_ID_T srvc_id;
} BT_GATTC_SEARCH_RST_T;


typedef struct
{
    INT32 conn_id;
    INT32 char_prop;
    BT_GATTS_SRVC_ID_T srvc_id;
    BT_GATT_ID_T char_id;
} BT_GATTC_GET_CHAR_RST_T;

typedef struct
{
    INT32 conn_id;
    BT_GATTS_SRVC_ID_T srvc_id;
    BT_GATT_ID_T char_id;
    BT_GATT_ID_T descr_id;
} BT_GATTC_GET_DESCR_RST_T;

typedef struct
{
    INT32 conn_id;
    BT_GATTS_SRVC_ID_T srvc_id;
    BT_GATTS_SRVC_ID_T incl_srvc_id;
} BT_GATTC_GET_INCL_RST_T;

typedef struct
{
    INT32 conn_id;
    INT32 registered;
    UINT32 handle;
} BT_GATTC_GET_REG_NOTI_RST_T;

/** Attribute change notification parameters */
typedef struct
{
    UINT8             value[BT_GATT_MAX_ATTR_LEN];
    CHAR             bda[MAX_BDADDR_LEN];
    UINT32           handle;
    UINT32            len;
    UINT8             is_notify;
} BT_GATT_NOTI_PARAMS_T;


typedef struct
{
    INT32 conn_id;
    BT_GATT_NOTI_PARAMS_T notify_data;
} BT_GATTC_GET_NOTIFY_T;

/** Buffer type for unformatted reads/writes */
typedef struct
{
    UINT8             value[BT_GATT_MAX_ATTR_LEN];
    UINT32            len;
} BT_GATT_UNFORMATTED_VALUE_T;

/** Parameters for GATT read operations */
typedef struct
{
    UINT32            handle;
    BT_GATT_UNFORMATTED_VALUE_T value;
    UINT32            value_type;
    UINT8             status;
} BT_GATT_READ_PARAMS_T;

typedef struct
{
    INT32 conn_id;
    BT_GATT_READ_PARAMS_T read_data;
} BT_GATTC_READ_CHAR_RST_T;

/** Parameters for GATT write operations */

typedef struct
{
    INT32 status;
    INT32 conn_id;
    UINT32 handle;
} BT_GATTC_WRITE_CHAR_RST_T;

typedef struct
{
    INT32 conn_id;
    BT_GATT_READ_PARAMS_T read_data;
} BT_GATTC_READ_DESCR_RST_T;


typedef struct
{
    INT32 status;
    INT32 conn_id;
    UINT32 handle;
} BT_GATTC_WRITE_DESCR_RST_T;

typedef struct
{
    INT32 client_if;
    CHAR btaddr[MAX_BDADDR_LEN];
    INT32 rssi;
} BT_GATTC_GET_REMOTE_RSSI_T;

typedef enum
{
    BT_GATT_REGISTER_CLIENT = 0,
    BT_GATT_CONNECT,
    BT_GATT_DISCONNECT,
    BT_GATT_GET_RSSI_DONE,

    BT_GATT_EVENT_MAX
}BT_GATTC_EVENT_T;

typedef struct
{
    int client_if;
    int action;
    int avbl_space;
} bluetooth_gatt_scan_filter_param_t;

typedef struct
{
    int client_if;
    int enable;
} bluetooth_gatt_scan_filter_status_t;

typedef struct
{
    int client_if;
    int action;
    int filt_type;
    int avbl_space;
} bluetooth_gatt_scan_filter_cfg_t;

typedef struct
{
    UINT8  client_if;
    UINT8  action;
    UINT8  filt_index;
    UINT32 feat_seln;
    UINT32 list_logic_type;
    UINT8  filt_logic_type;
    UINT8  rssi_high_thres;
    UINT8  rssi_low_thres;
    UINT8  dely_mode;
    UINT32 found_timeout;
    UINT32 lost_timeout;
    UINT8  found_timeout_cnt;
    UINT32  num_of_tracking_entries;
} bluetooth_gatt_filt_param_setup_t;

typedef enum
{
    BLUETOOTH_GATT_DB_PRIMARY_SERVICE,
    BLUETOOTH_GATT_DB_SECONDARY_SERVICE,
    BLUETOOTH_GATT_DB_INCLUDED_SERVICE,
    BLUETOOTH_GATT_DB_CHARACTERISTIC,
    BLUETOOTH_GATT_DB_DESCRIPTOR,
} bluetooth_gatt_db_attribute_type_t;

typedef struct
{
    UINT32           id;
    CHAR            uuid[BT_GATT_MAX_UUID_LEN];
    bluetooth_gatt_db_attribute_type_t type;
    UINT32            attribute_handle;

    /*
     * If |type| is |BTGATT_DB_PRIMARY_SERVICE|, or
     * |BTGATT_DB_SECONDARY_SERVICE|, this contains the start and end attribute
     * handles.
     */
    UINT32            start_handle;
    UINT32            end_handle;

    /*
     * If |type| is |BTGATT_DB_CHARACTERISTIC|, this contains the properties of
     * the characteristic.
     */
    UINT8             properties;
} bluetooth_gatt_db_element_t;

typedef struct
{
    INT32 conn_id;
    INT32 count;
    bluetooth_gatt_db_element_t *gatt_db_element;
}BT_GATTC_GET_GATT_DB_T;

typedef struct
{
    CHAR                *bda1;
    CHAR                *uuid1;
    UINT32              u1;
    UINT32              u2;
    UINT32              u3;
    UINT32              u4;
    UINT32              u5;
} BT_GATTC_TEST_PARAMS_T;

typedef VOID (*BtAppGATTCEventCbk)(BT_GATTC_EVENT_T bt_gatt_event);
typedef VOID (*BtAppGATTCRegClientCbk)(BT_GATTC_REG_CLIENT_T *pt_reg_client_result);
typedef VOID (*BtAppGATTCScanCbk)(BT_GATTC_SCAN_RST_T *pt_scan_result);
typedef VOID (*BtAppGATTCSearchCbk)(BT_GATTC_SEARCH_RST_T *pt_search_result);
typedef VOID (*BtAppGATTCGetGattDbCbk)(BT_GATTC_GET_GATT_DB_T *pt_get_gatt_db_result);
typedef VOID (*BtAppGATTCGetCharCbk)(BT_GATTC_GET_CHAR_RST_T *pt_get_char_result);
typedef VOID (*BtAppGATTCGetDescCbk)(BT_GATTC_GET_DESCR_RST_T *pt_get_desc_result);
typedef VOID (*BtAppGATTCGetIncludedCbk)(BT_GATTC_GET_INCL_RST_T *pt_get_included_result);
typedef VOID (*BtAppGATTCGetRegNotiCbk)(BT_GATTC_GET_REG_NOTI_RST_T *pt_get_reg_noti_result);
typedef VOID (*BtAppGATTCNotifyCbk)(BT_GATTC_GET_NOTIFY_T *pt_notify);
typedef VOID (*BtAppGATTCReadCharCbk)(BT_GATTC_READ_CHAR_RST_T *pt_read_char);
typedef VOID (*BtAppGATTCWriteCharCbk)(BT_GATTC_WRITE_CHAR_RST_T *pt_write_char);
typedef VOID (*BtAppGATTCReadDescCbk)(BT_GATTC_READ_DESCR_RST_T *pt_read_desc);
typedef VOID (*BtAppGATTCWriteDescCbk)(BT_GATTC_WRITE_DESCR_RST_T *pt_write_desc);
typedef VOID (*BtAppGATTScanFilterParamCbk)(bluetooth_gatt_scan_filter_param_t *pt_scan_filter_param);
typedef VOID (*BtAppGATTScanFilterStatusCbk)(bluetooth_gatt_scan_filter_status_t *pt_scan_filter_status);
typedef VOID (*BtAppGATTScanFilterCfgCbk)(bluetooth_gatt_scan_filter_cfg_t *pt_scan_filter_cfg);
typedef VOID (*BtAppGATTGetDeviceNameCbk)(CHAR *pt_DeviceName);


typedef struct
{
    BtAppGATTCEventCbk bt_gatt_event_cb;
    BtAppGATTCRegClientCbk bt_gatt_reg_client_cb;
    BtAppGATTCScanCbk bt_gatt_scan_cb;
    BtAppGATTCSearchCbk bt_gatt_search_cb;
    BtAppGATTCGetGattDbCbk bt_gatt_get_gatt_db_cb;
    BtAppGATTCGetCharCbk bt_gatt_get_char_cb;
    BtAppGATTCGetDescCbk bt_gatt_get_desc_cb;
    BtAppGATTCGetIncludedCbk bt_gatt_get_included_cb;
    BtAppGATTCGetRegNotiCbk bt_gatt_get_reg_noti_cb;
    BtAppGATTCNotifyCbk bt_gatt_notify_cb;
    BtAppGATTCReadCharCbk bt_gatt_read_char_cb;
    BtAppGATTCWriteCharCbk bt_gatt_write_char_cb;
    BtAppGATTCReadDescCbk bt_gatt_read_desc_cb;
    BtAppGATTCWriteDescCbk bt_gatt_write_desc_cb;
    BtAppGATTScanFilterParamCbk bt_gatt_scan_filter_param_cb;
    BtAppGATTScanFilterStatusCbk bt_gatt_scan_filter_status_cb;
    BtAppGATTScanFilterCfgCbk bt_gatt_scan_filter_cfg_cb;
    BtAppGATTGetDeviceNameCbk bt_gatt_get_device_name_cb;
}BT_APP_GATTC_CB_FUNC_T;

/*GATTS struct*/
typedef enum
{
    BT_GATTS_REGISTER_SERVER = 0,
    BT_GATTS_CONNECT,
    BT_GATTS_DISCONNECT,
    BT_GATTS_GET_RSSI_DONE,

    BT_GATTS_EVENT_MAX
}BT_GATTS_EVENT_T;

typedef enum
{
    BT_GATTS_START_SRVC = 0,
    BT_GATTS_STOP_SRVC,
    BT_GATTS_DEL_SRVC,

    BT_GATTS_SRVC_OP_MAX
}BT_GATTS_SRVC_OP_TYPE_T;

typedef struct
{
    INT32 server_if;
    CHAR app_uuid[BT_GATT_MAX_UUID_LEN];
} BT_GATTS_REG_SERVER_RST_T;

typedef struct
{
    INT32 conn_id;
    INT32 server_if;
    CHAR btaddr[MAX_BDADDR_LEN];
} BT_GATTS_CONNECT_RST_T;

typedef struct
{
    INT32 server_if;
    BT_GATTS_SRVC_ID_T srvc_id;
    INT32 srvc_handle;
} BT_GATTS_ADD_SRVC_RST_T;

typedef struct
{
    INT32 server_if;
    INT32 srvc_handle;
    INT32 incl_srvc_handle;
} BT_GATTS_ADD_INCL_RST_T;

typedef struct
{
    INT32 server_if;
    CHAR uuid[BT_GATT_MAX_UUID_LEN];
    INT32 srvc_handle;
    INT32 char_handle;
} BT_GATTS_ADD_CHAR_RST_T ;

typedef struct
{
    INT32 server_if;
    CHAR uuid[BT_GATT_MAX_UUID_LEN];
    INT32 srvc_handle;
    INT32 descr_handle;
} BT_GATTS_ADD_DESCR_RST_T;

typedef struct
{
    INT32 server_if;
    INT32 srvc_handle;
} BT_GATTS_SRVC_RST_T;

typedef struct
{
    INT32 conn_id;
    INT32 trans_id;
    CHAR btaddr[MAX_BDADDR_LEN];
    INT32 attr_handle;
    INT32 offset;
    UINT8 is_long;
} BT_GATTS_REQ_READ_RST_T;

typedef struct
{
    INT32 conn_id;
    INT32 trans_id;
    CHAR btaddr[MAX_BDADDR_LEN];
    INT32 attr_handle;
    INT32 offset;
    INT32 length;
    UINT8 need_rsp;
    UINT8 is_prep;
    UINT8 value[BT_GATT_MAX_ATTR_LEN];
} BT_GATTS_REQ_WRITE_RST_T;

typedef struct
{
    INT32 conn_id;
    INT32 trans_id;
    CHAR btaddr[MAX_BDADDR_LEN];
    INT32 exec_write;
} BT_GATTS_EXEC_WRITE_RST_T;

typedef VOID (*BtAppGATTSEventCbk)(BT_GATTS_EVENT_T bt_gatts_event);
typedef VOID (*BtAppGATTSRegServerCbk)(BT_GATTS_REG_SERVER_RST_T *bt_gatts_reg_server);
typedef VOID (*BtAppGATTSAddSrvcCbk)(BT_GATTS_ADD_SRVC_RST_T *bt_gatts_add_srvc);
typedef VOID (*BtAppGATTSAddInclCbk)(BT_GATTS_ADD_INCL_RST_T *bt_gatts_add_incl);
typedef VOID (*BtAppGATTSAddCharCbk)(BT_GATTS_ADD_CHAR_RST_T *bt_gatts_add_char);
typedef VOID (*BtAppGATTSAddDescCbk)(BT_GATTS_ADD_DESCR_RST_T *bt_gatts_add_desc);
typedef VOID (*BtAppGATTSOpSrvcCbk)(BT_GATTS_SRVC_OP_TYPE_T op_type, BT_GATTS_SRVC_RST_T *bt_gatts_srvc);
typedef VOID (*BtAppGATTSReqReadCbk)(BT_GATTS_REQ_READ_RST_T *bt_gatts_read);
typedef VOID (*BtAppGATTSReqWriteCbk)(BT_GATTS_REQ_WRITE_RST_T *bt_gatts_write);
typedef VOID (*BtAppGATTSIndSentCbk)(INT32 conn_id, INT32 status);

typedef struct _BT_APP_GATTS_CB_FUNC
{
    BtAppGATTSEventCbk bt_gatts_event_cb;
    BtAppGATTSRegServerCbk bt_gatts_reg_server_cb;
    BtAppGATTSAddSrvcCbk bt_gatts_add_srvc_cb;
    BtAppGATTSAddInclCbk bt_gatts_add_incl_cb;
    BtAppGATTSAddCharCbk bt_gatts_add_char_cb;
    BtAppGATTSAddDescCbk bt_gatts_add_desc_cb;
    BtAppGATTSOpSrvcCbk bt_gatts_op_srvc_cb;
    BtAppGATTSReqReadCbk bt_gatts_req_read_cb;
    BtAppGATTSReqWriteCbk bt_gatts_req_write_cb;
    BtAppGATTSIndSentCbk bt_gatts_ind_sent_cb;

}BT_APP_GATTS_CB_FUNC_T;

#if 1
#define MAX_C4TV_SETUP_INFO 256
#define MAX_C4TV_UUID_HANDLE 256
#define CONTROL_UUID_BLOCK_SIZE 512
#define ATTRIBUTE_VALUE_MEM_SIZE (16*1024)//8192
#define BTM_GATTS_SERVER_UUID  "49557E51-D815-11E4-8830-0800200C9A66"
#define BTM_GATTC_APP_UUID  "49557E50-D815-11E4-8830-0800200C9A66"

typedef enum
{
    C4TV_SETUP_INFO_TYPE_E_NULL = 0,
    C4TV_SETUP_INFO_TYPE_E_ADV,
    C4TV_SETUP_INFO_TYPE_E_SCAN,
    C4TV_SETUP_INFO_TYPE_E_CHAR,

    C4TV_SETUP_INFO_TYPE_E_LAST
}c4tv_setup_info_type_e;

typedef struct
{
    CHAR bt_service_uuid[BT_GATT_MAX_UUID_LEN];
    CHAR bt_advertised_uuid[BT_GATT_MAX_UUID_LEN];
    CHAR *service_uuid;
    CHAR *advertised_uuid;
    CHAR *advertise_data;
    CHAR *manufacturer_data;
}c4tv_setup_info_adv_t;

typedef struct
{
    CHAR bt_service_uuid[BT_GATT_MAX_UUID_LEN];
    CHAR bt_advertised_uuid[BT_GATT_MAX_UUID_LEN];
    CHAR *service_uuid;
    CHAR *advertised_uuid;
    CHAR *advertise_data;
    CHAR *manufacturer_data;
}c4tv_setup_info_scan_t;

typedef struct
{
    CHAR bt_service_uuid[BT_GATT_MAX_UUID_LEN];
    CHAR bt_attribute_uuid[BT_GATT_MAX_UUID_LEN];
    CHAR bt_control_uuid[BT_GATT_MAX_UUID_LEN];
    CHAR * service_uuid;
    CHAR * attribute_uuid;
    CHAR * control_uuid;
    CHAR * value;
    INT32 value_len;
    INT32 control_index;
    INT32 option;
    CHAR * read_value;
    INT32 read_value_len;
}c4tv_setup_info_attr_t;

typedef struct
{
    c4tv_setup_info_type_e type;
    union
    {
        c4tv_setup_info_adv_t adv;
        c4tv_setup_info_scan_t scan;
        c4tv_setup_info_attr_t attr;
    }u;
    INT32 ctrl_flag;
}c4tv_setup_info_t;

typedef enum
{
    C4TV_UUID_HANDLE_TYPE_E_NULL = 0,
    C4TV_UUID_HANDLE_TYPE_E_SRVC,
    C4TV_UUID_HANDLE_TYPE_E_CHAR,

    C4TV_UUID_HANDLE_TYPE_E_LAST
}c4tv_uuid_handle_type_e;

typedef struct
{
    c4tv_uuid_handle_type_e type;
    CHAR uuid[BT_GATT_MAX_UUID_LEN];
    INT32 handle;
}c4tv_uuid_handle_t;


typedef void (* a_mtkapi_bt_gatt_nfy_fct_cbk)(CHAR * service_uuid, CHAR * characteristic_uuid, CHAR * value, VOID * pv_tag);
typedef void (* a_mtkapi_bt_gatt_evt_fct_cbk)(UINT32 event, UINT32 value, VOID * pv_tag);

#endif

#endif /*  _U_BT_MW_GATT_H_ */




