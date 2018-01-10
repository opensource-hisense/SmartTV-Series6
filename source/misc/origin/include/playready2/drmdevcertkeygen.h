/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRMDEVCERTKEYGEN_H__
#define __DRMDEVCERTKEYGEN_H__

#include <drmtypes.h>
#include <drmkeyfile.h>
#include <oemcryptoctx.h>
#include <drmblackbox.h>

ENTER_PK_NAMESPACE;

DRM_API DRM_NO_INLINE DRM_BOOL DRM_CALL DRM_DDC_IsDevCertKeyGenSupported(DRM_VOID) DRM_NO_INLINE_ATTRIBUTE;
DRM_API DRM_NO_INLINE DRM_BOOL DRM_CALL DRM_DDC_IsDevCertKeyGenUnsupported(DRM_VOID) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_RESULT DRM_CALL DRM_DDC_SetXMLDeviceCertificateAndKey(
    __in           DRM_BB_CONTEXT      *f_pBlackBoxContext,
    __in           DRM_KEYFILE_CONTEXT *f_poKeyFileContext,
    __inout        DRM_STRING          *f_pdstrWMDRMCertStr );

DRM_API DRM_RESULT DRM_CALL DRM_DDC_CreateXMLDeviceCertificateAndKey(
    __in_opt       DRM_VOID                         *f_pOEMContext,
    __in           DRM_KEYFILE_CONTEXT              *f_poKeyFileContext,
    __in           DRM_DEVICE_CERT_PARSER_CACHE     *f_poParserCache,
    __in           DRM_BB_CONTEXT                   *f_pBlackBoxContext,
    __inout        DRM_STRING                       *f_pdstrWMDRMCertStr );

DRM_API DRM_RESULT DRM_CALL DRM_DDC_SetBinaryDeviceCertificateAndKey(
    __in_opt                               DRM_VOID             *f_pOEMContext,
    __in                                   DRM_KEYFILE_CONTEXT  *f_poKeyFileContext,
    __out_bcount(*f_pcbBinaryDevCertChain) DRM_BYTE             *f_pBinaryDevCertChain,
    __inout                                DRM_DWORD            *f_pcbBinaryDevCertChain,
    __inout                                DRM_BB_CONTEXT       *f_pBlackBoxContext );

DRM_API DRM_RESULT DRM_CALL DRM_DDC_CreateBinaryDeviceCertificateAndKey(
    __in_opt                               DRM_VOID             *f_pOEMContext,
    __in                                   DRM_KEYFILE_CONTEXT  *f_poKeyFileContext,
    __out_bcount(*f_pcbBinaryDevCertChain) DRM_BYTE             *f_pBinaryDevCertChain,
    __inout                                DRM_DWORD            *f_pcbBinaryDevCertChain,
    __in                                   DRM_BB_CONTEXT       *f_pBlackBoxContext );

DRM_API DRM_RESULT DRM_CALL DRM_DDC_CreateSecureStoreKeyAndSaveKeyFile(
    __in_opt            DRM_VOID       *f_pOEMContext,
    __inout_ecount( 1 ) DRM_BB_CONTEXT *f_pBlackBoxContext );

EXIT_PK_NAMESPACE;

#define SIGNING_KEY_IDX         0
#define ENCRYPTION_KEY_IDX      1
#define PRND_ENCRYPTION_KEY_IDX 2


#endif /* __DRMDEVCERTKEYGEN_H__ */

