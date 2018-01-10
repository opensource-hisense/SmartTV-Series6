/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRMDEVICEREVOCATION_H__
#define __DRMDEVICEREVOCATION_H__

#include <oemcryptoctx.h>
#include <drmrevocationstore.h>

ENTER_PK_NAMESPACE;

DRM_API DRM_NO_INLINE DRM_BOOL DRM_CALL DRM_DEVICEREVOCATION_IsDeviceRevocationSupported(DRM_VOID) DRM_NO_INLINE_ATTRIBUTE;
DRM_API DRM_BOOL DRM_CALL DRM_DEVICEREVOCATION_IsDeviceRevocationUnsupported(DRM_VOID);

/******************************************************************************
**
** Function :   DRM_RVK_UpdateRevocationListDecoded
**
** Synopsis :   updates the revocation list in the secure store
**
** Arguments :
** [f_pcontextCrypto]      --
** [f_pcontextRev]         -- revocation store context
** [f_pbRevocationList]    -- input buffer for exclusion list
** [f_cbRevocationList]    -- buffer size
** [f_pdstrRevocationList] -- the new DCRL
** [f_pGUID]               -- DRM_GUID used to store this list
** [f_pfUpdated]           -- Optional flag indicates whether the CRL was
**                            updated in the HDS or not.
** Returns :
**
** Notes :
**
******************************************************************************/
PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_PARAM_25004, "Crypto contexts can not be const and f_pContextRev is modified.  PREFAST is wrong.")
DRM_API DRM_NO_INLINE DRM_RESULT DRM_RVK_UpdateRevocationListDecoded(
    __in                                   DRM_CRYPTO_CONTEXT          *f_pcontextCrypto,
    __in                                   DRM_REVOCATIONSTORE_CONTEXT *f_pContextRev,
    __in_ecount(f_cbRevocationList)        DRM_BYTE                    *f_pbRevocationList,
    __in                                   DRM_DWORD                    f_cbRevocationList,
    __in                             const DRM_BYTE                    *f_pbRevocationBuffer,
    __in                                   DRM_DWORD                    f_cbRevocationBuffer,
    __in                             const DRM_GUID                    *f_pGUID,
    __in                             const PUBKEY                      *f_ppubkey,
    __out_opt                              DRM_BOOL                    *f_pfUpdated ) DRM_NO_INLINE_ATTRIBUTE;
PREFAST_POP

PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_PARAM_25004, "Crypto contexts can not be const and f_pContextRev is modified.  PREFAST is wrong.")
PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_COUNT_REQUIRED_FOR_WRITABLE_BUFFER, "f_rgchBase length defined by f_pdasstrRevocationList")
DRM_API DRM_RESULT DRM_RVK_UpdateRevocationList(
    __in                                                                                    DRM_CRYPTO_CONTEXT          *f_pcontextCrypto,
    __in                                                                                    DRM_REVOCATIONSTORE_CONTEXT *f_pContextRev,
    __inout_ecount( f_pdasstrRevocationList->m_ich + f_pdasstrRevocationList->m_cch )       DRM_CHAR                    *f_rgchBase,
    __in                                                                              const DRM_SUBSTRING               *f_pdasstrRevocationList,
    __in_bcount( f_cbRevocationBuffer )                                               const DRM_BYTE                    *f_pbRevocationBuffer,
    __in                                                                                    DRM_DWORD                    f_cbRevocationBuffer,
    __in                                                                              const DRM_GUID                    *f_pGUID,
    __in                                                                              const PUBKEY                      *f_ppubkey );
PREFAST_POP
PREFAST_POP

DRM_API DRM_RESULT DRM_CALL DRM_RVK_GetDeviceRevocationList(
    __in                                           DRM_CRYPTO_CONTEXT          *f_pcontextCRYP,
    __in                                           DRM_REVOCATIONSTORE_CONTEXT *f_pContextRev,
    __out_bcount_opt( *f_pcbRevocationData ) const DRM_BYTE                    *f_pbRevocationData,
    __inout                                        DRM_DWORD                   *f_pcbRevocationData,
    __out                                          DRM_DWORD                   *f_pidSerial ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_RESULT DRM_CALL DRM_RVK_CheckDeviceRevocation(
    __in  const DRM_CONST_STRING *f_pdstrDevCert,
    __in  const DRM_CONST_STRING *f_pdstrXMLExclusion,
    __out       DRM_BOOL         *f_pfExcluded );

DRM_API DRM_RESULT DRM_CALL DRM_DEVICEREVOCATION_IsDeviceRevoked(
    __in                      const DRM_CONST_STRING *f_pdstrDeviceCert,
    __in_bcount(f_ccbCRLSize) const DRM_BYTE         *f_pbCRLData,
    __in                      const DRM_DWORD         f_ccbCRLSize );

EXIT_PK_NAMESPACE;

#endif /*__DRMDEVICEREVOCATION_H__ */

