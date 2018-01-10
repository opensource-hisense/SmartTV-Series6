/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/


#ifndef __DRMREVOCATION_H__
#define __DRMREVOCATION_H__

#include <drmliceval.h>
#include <drmrevocationstore.h>
#include <drmrevocationtypes.h>
#include <oemparsers.h>

ENTER_PK_NAMESPACE;

#define MAX_REVOCATION_LIST_SIZE      ( 30 * 1024 )
#define MAX_REVOCATION_EXPIRE_TIME    ( 90 * 24 * 60 * 60 ) /* 90 days */

DRM_API DRM_NO_INLINE DRM_BOOL DRM_CALL DRM_REVOCATION_IsRevocationSupported(DRM_VOID) DRM_NO_INLINE_ATTRIBUTE;
DRM_API DRM_BOOL DRM_CALL DRM_REVOCATION_IsV1RIVSupported(DRM_VOID);
DRM_API DRM_BOOL DRM_CALL DRM_REVOCATION_AreAppAndDeviceRevocationSupported(DRM_VOID);
DRM_API DRM_BOOL DRM_CALL DRM_REVOCATION_AreAppAndWmdrmnetRevocationSupported(DRM_VOID);
DRM_API DRM_BOOL DRM_CALL DRM_REVOCATION_AreDeviceAndWmdrmnetRevocationSupported(DRM_VOID);
DRM_API DRM_BOOL DRM_CALL DRM_REVOCATION_AreAppAndDeviceAndWmdrmnetRevocationSupported(DRM_VOID);

#define DRM_ALL_REVOCATIONS NULL
DRM_API DRM_RESULT DRM_CALL DRM_RVK_GetCurrentRevocationInfo(
    __in                                 DRM_REVOCATIONSTORE_CONTEXT *f_pContextRev,
    __in                           const DRM_GUID                    *f_pguidRevocationType,
    __out_bcount_opt(*f_pcbBuffer)       DRM_BYTE                    *f_pbBuffer,
    __inout                              DRM_DWORD                   *f_pcbBuffer,
    __out                                DRM_RLVI                    *f_pRLVI,
    __in                                 DRM_CRYPTO_CONTEXT          *f_pCryptoCtx ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_RESULT DRM_CALL DRM_RVK_ProcessRevocationInfo (
    __in                              DRM_CRYPTO_CONTEXT          *f_pContextCrypto,
    __in                              DRM_REVOCATIONSTORE_CONTEXT *f_pContextRev,
    __in                              DRM_ANSI_CONST_STRING       *f_pdastrLicenseResponse,
    __in_ecount(f_cbRevocationBuffer) DRM_BYTE                    *f_pbRevocationBuffer,
    __in                              DRM_DWORD                    f_cbRevocationBuffer,
    __in                              APPCERT                     *f_pAppcert,
    __inout                           DRM_REVLIST_ID_VALUES       *f_pRevList );

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_RVK_ProcessRevocationInfoXML(
    __in                                      DRM_CRYPTO_CONTEXT          *f_pContextCrypto,
    __in                                      DRM_REVOCATIONSTORE_CONTEXT *f_pContextRev,
    __in_ecount(f_cchRevocationInfoXML) const DRM_CHAR                    *f_pchRevocationInfoXML,
    __in                                      DRM_DWORD                    f_cchRevocationInfoXML,
    __in_ecount(f_cbRevocationBuffer)         DRM_BYTE                    *f_pbRevocationBuffer,
    __in                                      DRM_DWORD                    f_cbRevocationBuffer,
    __out_opt                                 DRM_BOOL                    *f_pfUpdated ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_RESULT DRM_CALL DRM_RVK_UpdateRevocationVersionsCache(
    __inout                            DRM_REVOCATIONSTORE_CONTEXT *f_pContextRev,
    __in                               DRM_CRYPTO_CONTEXT          *f_pContextCrypto,
    __inout                            DRM_REVLIST_ID_VALUES       *f_pRevListIDs,
    __out_bcount(f_cbRevocationBuffer) DRM_BYTE                    *f_pbRevocationBuffer,
    __in                               DRM_DWORD                    f_cbRevocationBuffer,
    __out_opt                          DRM_BOOL                    *f_pfUpdated ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_RESULT DRM_CALL DRM_RVK_VerifyRevInfoSafe(
    __in                               DRM_CRYPTO_CONTEXT          *f_pContextCrypto,
    __in                               DRM_REVOCATIONSTORE_CONTEXT *f_pContextRev,
    __in const                         DRM_GUID                    *f_pguidRevocationType,
    __inout_bcount(f_cbRevocationInfo) DRM_BYTE                    *f_pbRevocationInfo,
    __in                               DRM_DWORD                    f_cbRevocationInfo,
    __in_bcount(f_cbRevocationBuffer)  DRM_BYTE                    *f_pbRevocationBuffer,
    __in                               DRM_DWORD                    f_cbRevocationBuffer,
    __inout_opt                        DRM_REVLIST_ID_VALUES       *f_pRevList,
    __out                              DRM_RLVI                    *f_pnewRLVI,
    __out                              DRM_BOOL                    *f_pfRIV2,
    __out                              DRM_BOOL                    *f_pfVerified ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_RESULT DRM_CALL DRM_RVK_StoreRevInfo(
    __in                              DRM_CRYPTO_CONTEXT          *f_pContextCrypto,
    __in                              DRM_REVOCATIONSTORE_CONTEXT *f_pContextRev,
    __in                              const DRM_GUID              *f_pguidRevocationType,
    __in_ecount(f_cbRevocationInfo)   DRM_BYTE                    *f_pbRevocationInfo,
    __in                              DRM_DWORD                    f_cbRevocationInfo,
    __in_ecount(f_cbRevocationBuffer) DRM_BYTE                    *f_pbRevocationBuffer,
    __in                              DRM_DWORD                    f_cbRevocationBuffer,
    __inout_opt                       DRM_REVLIST_ID_VALUES       *f_pRevList,
    __out_opt                         DRM_BOOL                    *f_pfWasStored ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_RESULT DRM_RVK_StoreRevocationLists(
    __in                              DRM_CRYPTO_CONTEXT          *f_pContextCrypto,
    __in                              DRM_REVOCATIONSTORE_CONTEXT *f_pContextRev,
    __in                              DRM_DWORD                    f_cRevocationLists,
    __in_ecount(f_cRevocationLists)   DRM_RVK_LIST                *f_pRevocationLists,
    __in                              APPCERT                     *f_pAppcert,
    __in_ecount(f_cbRevocationBuffer) DRM_BYTE                    *f_pbRevocationBuffer,
    __in                              DRM_DWORD                    f_cbRevocationBuffer,
    __inout_ecount(1)                 DRM_REVLIST_ID_VALUES       *f_pRevList );

DRM_API DRM_RESULT DRM_CALL DRM_RVK_VerifyRevocationInfo(
    __in_bcount( f_cbRevInfo ) DRM_BYTE           *f_pbRevInfo,
    __in                       DRM_DWORD           f_cbRevInfo,
    __out                      DRM_RLVI           *f_pRLVI,
    __in                       DRM_CRYPTO_CONTEXT *f_pCryptoCtx,
    __in_opt                   DRM_BB_CONTEXT     *f_pcontextBBX,
    __in_opt                   DRM_SECSTORE_CONTEXT *f_pcontextSST,
    __in_opt                   DRM_DST            *f_pDatastore ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_BOOL DRM_RVK_IsWrappedCRL(
    __in const DRM_CONST_STRING *f_pdstrRevocationList );

DRM_API DRM_RESULT DRM_CALL DRM_RVK_VerifyRevocationList(
    __in_opt DRM_REVOCATIONSTORE_CONTEXT *f_pContextRev,
    __in     DRM_CRYPTO_CONTEXT          *f_pcontextCRYP,
    __in     DRM_CONST_STRING            *f_pdstrList,
    __in const PUBKEY                    *f_ppubkey,
    __out    DRM_DWORD                   *f_pidSerial ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_RVK_GetSSTRevocationList(
    __in                           const DRM_GUID                    *f_pGUID,
    __in                                 DRM_CRYPTO_CONTEXT          *f_pcontextCRYP,
    __in                                 DRM_REVOCATIONSTORE_CONTEXT *f_pContextRev,
    __in                           const PUBKEY                      *f_ppubkey,
    __out_bcount_opt(*f_pcbBuffer) const DRM_BYTE                    *f_pbBuffer,
    __inout                              DRM_DWORD                   *f_pcbBuffer,
    __out                                DRM_DWORD                   *f_pidSerial ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_RESULT DRM_CALL DRM_RVK_VerifySigningCert(
    __in                          const DRM_ANSI_CONST_STRING       *f_pdastrResponse,
    __in                          const DRM_SUBSTRING               *f_pdasstrResponse,
    __in                          const DRM_ANSI_CONST_STRING       *f_pdastrCertNodePath,
    __in_bcount( f_cbBcertBuffer )      DRM_BYTE                    *f_pbBCertBuffer,
    __in                                DRM_DWORD                    f_cbBcertBuffer,
    __in_bcount( f_cbRevocationBuffer ) DRM_BYTE                    *f_pbRevocationBuffer,
    __in                                DRM_DWORD                    f_cbRevocationBuffer,
    __in                                DRM_BB_CONTEXT              *f_pBBXContext,
    __in                                DRM_SECSTORE_CONTEXT        *f_pSecStoreGlobalContext,
    __in                                DRM_DST                     *f_pDatastore,
    __in                                DRM_REVOCATIONSTORE_CONTEXT *f_pRevStoreContext );

#define DRM_APP_REVOCATION_VERSION_NONE    0xFFFFFFFF

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_RVK_GetCRL(
    __in                                DRM_CRYPTO_CONTEXT           *f_pContextCrypto,
    __in                                DRM_REVOCATIONSTORE_CONTEXT  *f_pContextRev,
    __in                          const DRM_GUID                     *f_pguidRevocationType,
    __out_bcount_opt( *f_pcbCRL )       DRM_BYTE                     *f_pbCRL,
    __inout                             DRM_DWORD                    *f_pcbCRL,
    __out_opt                           DRM_DWORD                    *f_pdwCRLVersion ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_RESULT DRM_CALL DRM_RVK_SetCRL(
    __in                                      DRM_CRYPTO_CONTEXT           *f_pContextCrypto,
    __in                                      DRM_REVOCATIONSTORE_CONTEXT  *f_pContextRev,
    __in                                const DRM_GUID                     *f_pguidRevocationType,
    __in_bcount( f_cbCRL )                    DRM_BYTE                     *f_pbCRL,
    __in                                      DRM_DWORD                     f_cbCRL,
    __in_bcount( f_cbRevocationBuffer )       DRM_BYTE                     *f_pbRevocationBuffer,
    __in                                      DRM_DWORD                     f_cbRevocationBuffer,
    __out                                     DRM_BOOL                     *f_pfUpdated ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_RVK_CheckRevInfoForExpiration(
    __in                                DRM_CRYPTO_CONTEXT           *f_pContextCrypto,
    __in                                DRM_REVOCATIONSTORE_CONTEXT  *f_pContextRev,
    __in                          const DRM_GUID                     *f_pguidRevocationType,
    __in_opt                      const DRM_ID                       *f_pidSession,
    __out_bcount_opt( *f_pcbRevInfo )   DRM_BYTE                     *f_pbRevInfo,
    __inout                             DRM_DWORD                    *f_pcbRevInfo ) DRM_NO_INLINE_ATTRIBUTE;


EXIT_PK_NAMESPACE;

#endif /* __DRMREVOCATION_H__ */

