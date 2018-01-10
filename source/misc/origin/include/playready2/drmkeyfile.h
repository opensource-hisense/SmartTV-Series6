/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef _DRMKEYFILE_H_
#define _DRMKEYFILE_H_

#include <drmkeyfiletypes.h>
#include <drmkeyfileformat.h>
#include <drmstkalloc.h>
#include <drmdevcertcache.h>
#include <oemcommon.h>

ENTER_PK_NAMESPACE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_KF_Initialize(
    __in_opt       DRM_VOID                    *f_pOEMContext,
    __out          DRM_KEYFILE_CONTEXT         *f_pKeyFile ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_KF_Uninitialize(
    __inout   DRM_KEYFILE_CONTEXT           *f_pKeyFile ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_KF_Open(
    __inout  DRM_KEYFILE_CONTEXT *f_pKeyFile,
    __in     DRM_DWORD            f_fCreateIfNotExists,
    __in     DRM_DWORD            f_dwAccessMode ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_KF_LoadFromMemory(
    __in_ecount(f_cbKeyFile)   const DRM_BYTE            *f_pbKeyFile,
    __in                             DRM_DWORD            f_cbKeyFile,
    __inout                          DRM_KEYFILE_CONTEXT *f_pKeyFile ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_KF_LoadFromFile(
    __inout   DRM_KEYFILE_CONTEXT        *f_pKeyFile,
    __in      DRM_BOOL                    f_fValidateSignature ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_KF_StoreToFile(
    __inout   DRM_KEYFILE_CONTEXT           *f_pKeyFile ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_KF_Close(
    __in   DRM_KEYFILE_CONTEXT   *f_pKeyFile ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_KEYFILE_CERT_TYPE DRM_CALL MapApiCertTypeToFormatCertType( __in DRM_KF_CERT_TYPE f_eCertType ) DRM_NO_INLINE_ATTRIBUTE;

PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_PARAM_25004, "Prefast Noise: DRM_KEYFILE_CONTEXT* should not be const.")
DRM_API DRM_RESULT DRM_CALL DRM_KF_GetCertificate(
    __in                            DRM_KEYFILE_CONTEXT   *f_pKeyFile,
    __in                            DRM_KF_CERT_TYPE       f_eCertType,
    __out_ecount(*f_pcbCertData)    DRM_BYTE             **f_ppbCertData,
    __out_ecount(1)                 DRM_DWORD             *f_pcbCertData );
PREFAST_POP /* __WARNING_NONCONST_PARAM_25004 */

DRM_API DRM_RESULT DRM_CALL DRM_KF_SetCertificate(
    __in                            DRM_KEYFILE_CONTEXT   *f_pKeyFile,
    __in                            DRM_KF_CERT_TYPE       f_eCertType,
    __in_bcount(f_cbCertData) const DRM_BYTE              *f_pbCertData,
    __in                            DRM_DWORD              f_cbCertData );

DRM_API DRM_NO_INLINE DRM_KEYFILE_ASYMMETRIC_KEY_TYPE DRM_CALL MapApiKeyTypeToFormatKeyType( __in DRM_KF_KEY_TYPE f_eKeyType ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_KF_GetPrivateKey(
    __in                        const DRM_KEYFILE_CONTEXT   *f_pKeyFile,
    __in                              DRM_KF_KEY_TYPE        f_eKeyType,
    __in_bcount_opt(f_cbPubKey) const DRM_BYTE              *f_pbPubKey,
    __in                              DRM_DWORD              f_cbPubKey,
    __out_ecount(1)                   DRM_ENCRYPTED_KEY     *f_pKey ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_RESULT DRM_CALL DRM_KF_SetPrivateKey(
    __in                              DRM_KEYFILE_CONTEXT   *f_pKeyFile,
    __in                              DRM_KF_KEY_TYPE        f_eKeyType,
    __in_bcount_opt(f_cbPubKey) const DRM_BYTE              *f_pbPubKey,
    __in                              DRM_DWORD              f_cbPubKey,
    __in                              DRM_ENCRYPTED_KEY     *f_pKey );

DRM_API DRM_RESULT DRM_CALL DRM_KF_SetCertParserCache(
    __in  DRM_KEYFILE_CONTEXT          *f_pKeyFile,
    __in  DRM_DEVICE_CERT_PARSER_CACHE *f_pCertParserCache );

EXIT_PK_NAMESPACE;

#endif /* _DRMKEYFILE_H_ */

