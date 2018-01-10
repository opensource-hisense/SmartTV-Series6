/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRMAPPREVOCATION_H__
#define __DRMAPPREVOCATION_H__

#include <drmliceval.h>
#include <drmrevocationtypes.h>

ENTER_PK_NAMESPACE;

DRM_API DRM_BOOL DRM_CALL DRM_APPREVOCATION_IsAppRevocationSupported(DRM_VOID);
DRM_API DRM_BOOL DRM_CALL DRM_APPREVOCATION_IsAppRevocationUnsupported(DRM_VOID);

DRM_API DRM_RESULT DRM_CALL DRM_RVK_GetCurrentAppRevocationList(
    __in                            DRM_REVOCATIONSTORE_CONTEXT *f_pContextRev,
    __in_bcount_opt( *f_pcbBuffer ) DRM_BYTE                    *f_pbBuffer,
    __inout                         DRM_DWORD                   *f_pcbBuffer,
    __out                           DRM_DWORD                   *f_pidCRLApp ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_RESULT DRM_CALL DRM_RVK_PerformAppRevocationCheck(
    __in                                      DRM_CRYPTO_CONTEXT          *f_pContextCrypto,
    __in                                      DRM_REVOCATIONSTORE_CONTEXT *f_pContextRev,
    __in                                const DRM_CONST_STRING            *f_pdstrContentLicense,
    __in                                      APPCERT                     *f_pAppCert,
    __in_bcount( f_cbRevocationBuffer )       DRM_BYTE                    *f_pbRevocationBuffer,
    __in                                      DRM_DWORD                    f_cbRevocationBuffer,
    __inout                                   DRM_REVLIST_ID_VALUES       *f_pRevListIDs );

DRM_API DRM_RESULT DRM_CALL DRM_RVK_CheckAppCertForRevocation(
    __in_bcount( f_cbAppCRL ) DRM_BYTE  *f_pbAppCRL,
    __in                      DRM_DWORD  f_cbAppCRL,
    __in                      APPCERT   *f_pappcert );

DRM_API DRM_RESULT DRM_CALL DRM_RVK_UpdateAppRevocationListA(
    __in                                                                                 DRM_CRYPTO_CONTEXT          *f_pcontextCRY,
    __in                                                                                 DRM_REVOCATIONSTORE_CONTEXT *f_pContextRev,
    __in_bcount( f_cbBuffer )                                                            DRM_BYTE                    *f_pbBuffer,
    __in                                                                                 DRM_DWORD                    f_cbBuffer,
    __in_ecount( f_pdasstrRevocationList->m_ich + f_pdasstrRevocationList->m_cch ) const DRM_CHAR                    *f_rgchBase,
    __in                                                                           const DRM_SUBSTRING               *f_pdasstrRevocationList,
    __in                                                                                 APPCERT                     *f_pappcert,
    __in                                                                                 DRM_DWORD                    f_idCRLAppCurrent,
    __out_opt                                                                            DRM_BOOL                    *f_pfUpdatedAppRevocationList );

DRM_API DRM_RESULT DRM_CALL DRM_RVK_UpdateAppRevocationListW(
    __in                      DRM_CRYPTO_CONTEXT          *f_pcontextCRY,
    __in                      DRM_REVOCATIONSTORE_CONTEXT *f_pContextRev,
    __in_bcount( f_cbBuffer ) DRM_BYTE                    *f_pbBuffer,
    __in                      DRM_DWORD                    f_cbBuffer,
    __in                      DRM_CONST_STRING            *f_pdstrRevocationList,
    __in_opt                  APPCERT                     *f_pappcert,
    __in                      DRM_DWORD                    f_idCRLAppCurrent,
    __out                     DRM_BOOL                    *f_pfUpdatedAppRevocationList,
    __out_opt                 DRM_DWORD                   *f_pdwVersion ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_RESULT DRM_NO_INLINE DRM_CALL DRM_RVK_UpdateAppRevocationListDecoded(
    __in                              DRM_CRYPTO_CONTEXT            *f_pcontextCRY,
    __in                              DRM_REVOCATIONSTORE_CONTEXT   *f_pContextRev,
    __in_bcount( f_cbRevocationList ) DRM_BYTE                      *f_pbRevocationList,
    __in                              DRM_DWORD                      f_cbRevocationList,
    __in_opt                          APPCERT                       *f_pappcert,
    __in                              DRM_DWORD                      f_idCRLAppCurrent,
    __out_opt                         DRM_BOOL                      *f_pfUpdatedAppRevocationList,
    __out_opt                         DRM_DWORD                     *f_pdwVersion ) DRM_NO_INLINE_ATTRIBUTE;

EXIT_PK_NAMESPACE;

#endif /*__DRMAPPREVOCATION_H__ */

