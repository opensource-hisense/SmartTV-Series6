#ifndef C_BT_MW_MANAGER_H
#define C_BT_MW_MANAGER_H


#include "u_bluetooth.h"
#include "c_bt_mw_gap.h"
#if (ENABLE_A2DP_SRC || ENABLE_A2DP_SINK)
#include "c_bt_mw_a2dp_common.h"
#endif

#if ENABLE_A2DP_SRC
#include "c_bt_mw_a2dp_src.h"
#endif

#if ENABLE_A2DP_SINK
#include "c_bt_mw_a2dp_snk.h"
#endif

/*-----------------------------------------------------------------------------
                    functions declarations
 ----------------------------------------------------------------------------*/
INT32 c_btm_bt_base_init(BT_APP_CB_FUNC *func);

INT32 c_btm_bluetooth_on_off(BOOL fg_on);

INT32 c_btm_btstart(const CHAR *ps_mode, UINT32 u4_overtime);

INT32 c_btm_stop(BOOL fg_keep_conn, BOOL fg_discard_data);



/******************** GAP ********************/
INT32 c_btm_get_local_dev_info(BT_GAP_LOCAL_PROPERTIES_RESULT* ps_dev_info);

INT32 c_btm_get_target_addr(CHAR *addr);

INT32 c_btm_get_target_info(BT_TARGET_DEV_INFO *pt_target_dev_info);

INT32 c_btm_del_paired_av_dev_one(BT_TARGET_DEV_INFO *pt_device_info);

INT32 c_btm_del_paired_av_dev_all(VOID);

INT32 c_btm_clear_dev_info(VOID);

INT32 c_btm_save_device_history(VOID);


/******************** A2DP ********************/
INT32 c_btm_connecting(CHAR* ps_mac);

BT_MODE_TYPE c_btm_get_mode(VOID);

INT32 c_btm_bt_auto_disconnection(VOID);

#endif /*  C_BT_MW_MANAGER_H  */
