/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRM_SYNC_STORE__
#define __DRM_SYNC_STORE__

#include <drmsyncstorecontext.h>
#include <drmxmlbuilder.h>
#include <drmviewrights.h>

ENTER_PK_NAMESPACE;

DRM_API DRM_BOOL DRM_CALL DRM_SNC_IsLicenseSyncSupported(DRM_VOID);
DRM_API DRM_BOOL DRM_CALL DRM_SNC_IsLicenseSyncUnsupported(DRM_VOID);

/* Sync store helper functions */
DRM_API DRM_RESULT DRM_SNC_GetStoreDataForKID(
    __in                                         DRM_SYNC_CONTEXT           *f_pcontextSYN,
    __in                                   const DRM_KID                    *f_pkid,
    __in_opt                                     DRM_DST_SLOT_HINT          *f_pslotHint,
    __out_opt                                    DRM_LICENSE_STATE_DATA     *f_plsd,
    __out_ecount_opt(*f_pcchContentHeader)       DRM_WCHAR                  *f_pwszContentHeader,
    __inout_ecount_opt(1)                        DRM_DWORD                  *f_pcchContentHeader );

DRM_API DRM_RESULT DRM_SNC_GetLicenseDataForKID(
    __in  DRM_DST                    *f_pDatastore,
    __in  DRM_VIEW_RIGHTS_CONTEXT    *f_pcontextViewRightsIn,
    __out DRM_LICENSE_STATE_DATA     *f_plsd );

DRM_API DRM_RESULT DRM_SNC_SetStoreDataForKID(
    __in           DRM_SYNC_CONTEXT          *f_pcontextSYN,
    __in     const DRM_KID                   *f_pkid,
    __in_opt       DRM_DST_SLOT_HINT         *f_pslotHint,
    __in_opt const DRM_LICENSE_STATE_DATA    *f_plsd,
    __in_opt const DRM_STRING                *f_pdstrContentHeader,
    __in           DRM_BOOL                   f_fCreateIfNotExisting );

DRM_API DRM_BOOL DRM_SNC_IsSyncRequired(
    __in_opt DRM_VOID                  *pOEMContext,
    __in     DRM_DWORD                  cMaxCountIn,
    __in     DRM_DWORD                  cMaxHoursIn,
    __in     DRM_LICENSE_STATE_DATA    *plsd,
    __inout  DRM_UINT64                *pui64ThreshholdTime );

DRM_API DRM_BOOL DRM_SNC_IsStoreRefreshRequired(
    __in DRM_VOID               *f_pOEMContext,
    __in DRM_LICENSE_STATE_DATA *f_plsd );

/* low-level access to the sync store */

/**********************************************************************
 *                     PUBLIC FUNCTION DRM_SNC_OpenStore
 **********************************************************************/

DRM_API DRM_RESULT DRM_CALL DRM_SNC_OpenStore(
    __in  DRM_DST                *f_pDatastore,
    __out DRM_SYNC_CONTEXT       *f_pcontextSYN );

/**********************************************************************
 *                     PUBLIC FUNCTION DRM_SNC_CloseStore
 **********************************************************************/

DRM_API DRM_RESULT DRM_CALL DRM_SNC_CloseStore(
    __in  DRM_SYNC_CONTEXT       *f_pcontextSYN );


/**********************************************************************
 *                    PUBLIC FUNCTION DRM_SNC_InitEnum
 ***********************************************************************/

DRM_API DRM_RESULT DRM_CALL DRM_SNC_InitEnum(
    __in  DRM_SYNC_CONTEXT       *f_pcontextSYN,
    __out DRM_SYNC_ENUM_CONTEXT  *f_pcontextSYNEnum );

DRM_API DRM_RESULT DRM_CALL DRM_SNC_EnumNext(
    __in  DRM_SYNC_ENUM_CONTEXT  *f_pcontextSYNEnum,
    __out DRM_KID                *f_pkid,
    __out DRM_DST_SLOT_HINT      *f_pslotHint );

DRM_API DRM_RESULT DRM_CALL DRM_SNC_GetSyncStoreEntry(
    __in                                       DRM_SYNC_CONTEXT        *f_pcontextSYN,
    __in                                 const DRM_KID                 *f_pkid,
    __out_opt                                  DRM_LICENSE_STATE_DATA  *f_plsd,
    __out_ecount_opt(*f_pcchContentHeader)     DRM_WCHAR               *f_pwszContentHeader,
    __inout_opt                                DRM_DWORD               *f_pcchContentHeader );

typedef enum _DRM_SYNC_UPDATE_CATEGORY
{
    DRM_SYNC_UPDATE_AGGREGATE,
    DRM_SYNC_UPDATE_FORCE_SYNC,
    DRM_SYNC_UPDATE_NO_LICENSE,
} DRM_SYNC_UPDATE_CATEGORY;


DRM_API DRM_RESULT DRM_CALL DRM_SNC_UpdateKID(
    __in           DRM_SYNC_CONTEXT          *f_pcontextSYN,
    __in_opt       DRM_VIEW_RIGHTS_CONTEXT   *f_pcontextViewRightsIn,
    __in     const DRM_KID                   *f_pkid,
    __in_opt const DRM_CONST_STRING          *f_pdstrContentHeader,
    __in           DRM_SYNC_UPDATE_CATEGORY   f_eSyncCategory );

#define DRM_SYNC_IGNORE_THRESHOLD_PARAMETER    0xFFFFFFFF

/* inner implementations of DRM_Manager-level Sync API */

DRM_API DRM_RESULT DRM_CALL DRM_SNC_DidLicenseExpire(
    __in            DRM_SYNC_CONTEXT          *f_pcontextSync,
    __in_opt        DRM_VIEW_RIGHTS_CONTEXT   *f_pcontextViewRights,
    __in            DRM_DST                   *f_pDatastore,
    __in      const DRM_KID                   *f_pKID,
    __out           DRM_BOOL                  *f_pfExpired );

DRM_API DRM_RESULT DRM_CALL DRM_SNC_GenerateSyncChallenge(
    __in      DRM_SYNC_CONTEXT            *f_pcontextSync,
    __in      DRM_VIEW_RIGHTS_CONTEXT     *f_pcontextViewRights,
    __in      DRM_DST                     *f_pDatastore,
    __in      DRM_STACK_ALLOCATOR_CONTEXT *f_pcontextStack,
    __in      DRM_DWORD                    f_cMaxCount,
    __in      DRM_DWORD                    f_cMaxHours,
    __in      DRM_DWORD                    f_iKIDStart,
    __in      DRM_DWORD                    f_cKIDs,
    __out_opt DRM_DWORD                   *f_piKIDNext,
    __out_opt DRM_DWORD                   *f_pcKIDs,
    __out_opt _XMBContext                 *f_pbChallenge,
    __inout   DRM_DWORD                   *f_pcbChallenge );


/*********************************************************************
** Function: DRM_SNC_DeleteKID
**
** Synopsis: delete the indicated KID from the sync store; its absense
**           is not an error
**
** Parameters:
**
** [f_pcontextSYN]          -- initialized SYNC context
** [f_pkid]                 -- pointer to KID to be added/updated
**********************************************************************/

DRM_API DRM_RESULT DRM_CALL DRM_SNC_DeleteKID(
    __in       DRM_SYNC_CONTEXT *f_pcontextSYN,
    __in const DRM_KID          *f_pkid );



extern const DRM_CONST_STRING* const g_apdstrActions [1];


EXIT_PK_NAMESPACE;

#endif /* __DRM_SYNC_STORE__ */
