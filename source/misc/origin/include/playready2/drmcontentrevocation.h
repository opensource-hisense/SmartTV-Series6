/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRM_CONTENTREVOCATION__
#define __DRM_CONTENTREVOCATION__

#include <oemcryptoctx.h>
#include <drmliceval.h>

ENTER_PK_NAMESPACE;

DRM_API DRM_NO_INLINE DRM_BOOL DRM_CALL DRM_CONTENTREVOCATION_IsContentRevocationSupported(DRM_VOID) DRM_NO_INLINE_ATTRIBUTE;
DRM_API DRM_BOOL DRM_CALL DRM_CONTENTREVOCATION_IsContentRevocationUnsupported(DRM_VOID);

DRM_API DRM_RESULT DRM_CALL DRM_CONTENTREVOCATION_LIC_VerifyContentRevocation(
    __in      const DRM_CONST_STRING   *pdstrContentRevocation,
    __out_opt       DRM_CONST_STRING   *pdstrLSPubKey,
    __out_opt       DRM_DWORD          *pdwSequenceNumber,
    __out_opt       DRM_CONST_STRING   *pdstrContentOwnerPubKey,
    __out_opt       DRM_CONST_STRING   *pdstrCondition,
    __in            DRM_CRYPTO_CONTEXT *pcontextCrypto );

DRM_API DRM_RESULT DRM_CALL DRM_CONTENTREVOCATION_LIC_GetContentRevocation(
    __in const DRM_CONST_STRING   *pdstrLicense,
    __in       DRM_DWORD           dwSequenceNumber,
    __out      DRM_DWORD          *pdwSequenceNumber,
    __out      DRM_CONST_STRING   *pdstrContentRevocation,
    __out      DRM_CONST_STRING   *pdstrContentOwnerPubKey,
    __out_opt  DRM_CONST_STRING   *pdstrCondition,
    __in       DRM_CRYPTO_CONTEXT *pcontextCrypto );

DRM_API DRM_RESULT DRM_CALL DRM_CONTENTREVOCATION_LEVL_SetOrUpdateContentRevocation(
    __inout       DRM_LICEVAL_CONTEXT *f_pContextLicEval,
    __in    const DRM_DST             *f_pDatastore );

DRM_API DRM_BOOL DRM_CALL DRM_CONTENTREVOCATION_LEVL_IsLicenseRevoked(
    __in const DRM_LICEVAL_CONTEXT *f_pContextLicEval,
    __in const DRM_DST             *f_pDatastore );

DRM_API DRM_RESULT DRM_CALL DRM_CONTENTREVOCATION_LEVL_VerifyHeaderSignature(
    __inout        DRM_LICEVAL_CONTEXT          *f_pContextLicEval,
    __in           eDRM_LICEVAL_OPERATION_STATE  f_eOperationState,
    __in     const DRM_CONST_STRING             *f_pdstrKID,
    __in           DRM_CONST_STRING             *f_pdstrLIData );

EXIT_PK_NAMESPACE;

#endif /* __DRM_CONTENTREVOCATION__ */

