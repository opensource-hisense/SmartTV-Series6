/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRM_REMOVAL_DATE_STORE__
#define __DRM_REMOVAL_DATE_STORE__

#include <drmremovaldatestorecontext.h>

ENTER_PK_NAMESPACE;

DRM_API DRM_RESULT DRM_CALL DRM_RDS_OpenStore(
    __inout_ecount( 1 )   DRM_DST                  *f_pDatastore,
    __out_ecount( 1 )     DRM_REMOVAL_DATE_CONTEXT *f_pcontextRemovalDateOut);

DRM_API DRM_RESULT DRM_CALL DRM_RDS_CloseStore(
    __inout_ecount( 1 )   DRM_REMOVAL_DATE_CONTEXT *f_pcontextRemovalDateIn);

DRM_API DRM_RESULT DRM_CALL DRM_RDS_DeleteLicenseEntry(
    __inout_ecount( 1 )        DRM_DST             *f_pDatastore,
    __in_ecount( 1 )     const DRM_KID             *f_pKID,
    __in_ecount_opt( 1 ) const DRM_LID             *f_pLID );

DRM_API DRM_RESULT DRM_CALL DRM_RDS_Delete(
    __inout_ecount( 1 )        DRM_REMOVAL_DATE_CONTEXT *f_pcontextRemovalDate,
    __in                       DRM_DWORD                 f_dwRemovalDate,
    __in_ecount( 1 )     const DRM_KID                  *f_pKID,
    __in_ecount_opt( 1 )       DRM_DST_SLOT_HINT        *f_pslotHint );

DRM_API DRM_RESULT DRM_CALL DRM_RDS_EnumDeleteCurrent (
    __inout_ecount( 1 )   DRM_REMOVAL_DATE_ENUM    *f_pcontextRemovalDateEnum );

DRM_API DRM_RESULT DRM_CALL DRM_RDS_InitEnum   (
    __inout_ecount( 1 )   DRM_REMOVAL_DATE_CONTEXT *f_pcontextRemovalDate,
    __in                  DRM_DST_LOCKMODE          f_eLockMode,
    __out_ecount( 1 )     DRM_REMOVAL_DATE_ENUM    *f_pcontextRemovalDateEnum );

DRM_API DRM_RESULT DRM_CALL DRM_RDS_EnumNext   (
    __inout_ecount( 1 )   DRM_REMOVAL_DATE_ENUM    *f_pcontextRemovalDateEnum,
    __out_ecount( 1 )     DRM_DWORD                *f_pdwRemovalDate,
    __out_ecount( 1 )     DRM_KID                  *f_pKID,
    __out_ecount_opt( 1 ) DRM_DST_SLOT_HINT        *f_pslotHint,
    __out_ecount_opt( 1 ) DRM_DWORD                *f_pcLicenses );

DRM_API DRM_RESULT DRM_CALL DRM_RDS_AddRemovalDate(
    __inout_ecount( 1 )        DRM_DST                    *f_pDatastore,
    __in_ecount_opt( 1 )       DRM_DST_NAMESPACE_CONTEXT  *f_pDstNamespaceContext,
    __in                       DRM_DWORD                   f_dwRemovalDate,
    __in_ecount( 1 )     const DRM_KID                    *f_pKID,
    __in_ecount( 1 )     const DRM_LID                    *f_pLID,
    __in_ecount_opt( 1 )       DRM_DST_SLOT_HINT          *f_pSlotHint );

DRM_API DRM_RESULT DRM_CALL DRM_RDS_GetRemovalDateEntry   (
   __inout_ecount( 1 )            DRM_REMOVAL_DATE_CONTEXT *f_pcontextRemovalDate,
   __in                           DRM_DWORD                 f_dwRemovalDate,
   __in_ecount( 1 )         const DRM_KID                  *f_pKID,
   __in_ecount_opt( 1 )           DRM_DST_SLOT_HINT        *f_pslotHint,
   __inout_ecount( 1 )            DRM_DWORD                *f_pcbData,
   __out_bcount(*f_pcbData)       DRM_BYTE                 *f_pbData,
   __out_ecount( 1 )              DRM_DWORD                *f_pcEntries );

DRM_API DRM_RESULT DRM_CALL DRM_RDS_GetLicenseCount(
    __inout_ecount( 1 )         DRM_DST                  *f_pDatastore,
    __in_ecount_opt( 1 ) const  DRM_DWORD                *f_pdwRemovalDate,
    __out_ecount( 1 )           DRM_DWORD                *f_pcLicenses );

EXIT_PK_NAMESPACE;

#endif /* __DRM_REMOVAL_DATE_STORE__ */
