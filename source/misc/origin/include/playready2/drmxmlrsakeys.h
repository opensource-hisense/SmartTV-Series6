/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRMXMLRSAKEYS_H
#define __DRMXMLRSAKEYS_H

#include <drmcommon.h>
#include <drmxmlparser.h>
#include <drmxmlbuildera.h>
#include <oemrsa.h>

ENTER_PK_NAMESPACE;

DRM_API DRM_RESULT DRM_CALL DRM_XML_RSA_WritePublicKeyNodeA(
   __inout        _XMBContextA                  *f_pXMLCtxA,
   __in_opt const DRM_ANSI_CONST_STRING         *f_pdastrWrapperTag,
   __in     const DRM_RSA_PUBLIC_KEY_2048BIT    *f_pKeyRSAPublic );

DRM_API DRM_RESULT DRM_CALL DRM_XML_RSA_WritePublicKeyNode(
   __inout        _XMBContext                *f_pXMLCtx,
   __in_opt const DRM_CONST_STRING           *f_pdastrWrapperTag,
   __in     const DRM_RSA_PUBLIC_KEY_2048BIT *f_pKeyRSAPublic );

DRM_API DRM_RESULT DRM_CALL DRM_XML_RSA_ParseBase64PublicKey(
   __in    const DRM_CONST_STRING           *f_dstrPubKeyModulus,
   __in    const DRM_CONST_STRING           *f_dstrPubKeyExponent,
   __inout       DRM_RSA_PUBLIC_KEY_2048BIT *f_pKeyRSAPublic );

DRM_API DRM_RESULT DRM_CALL DRM_XML_RSA_ParseBase64PublicKeyA(
    __in    const DRM_ANSI_CONST_STRING         *f_dastrPubKeyModulus,
    __in    const DRM_SUBSTRING                 *f_dasstrPubKeyModulus,
    __in    const DRM_ANSI_CONST_STRING         *f_dastrPubKeyExponent,
    __in    const DRM_SUBSTRING                 *f_dasstrPubKeyExponent,
    __inout       DRM_RSA_PUBLIC_KEY_2048BIT    *f_pKeyRSAPublic );

DRM_API DRM_RESULT DRM_CALL DRM_XML_RSA_WritePrivateKeyNode(
   __inout        _XMBContext                 *f_pXMLCtx,
   __in_opt const DRM_CONST_STRING            *f_pdstrWrapperTag,
   __in     const DRM_RSA_PRIVATE_KEY_2048BIT *f_pKeyRSAPrivate );

DRM_API DRM_RESULT DRM_CALL DRM_XML_RSA_ParseBase64PrivateKey(
    __in    const DRM_CONST_STRING            *f_dstrPrivKeyPrime0,
    __in    const DRM_CONST_STRING            *f_dstrPrivKeyPrime1,
    __in    const DRM_CONST_STRING            *f_dstrPrivKeyCRTExponent0,
    __in    const DRM_CONST_STRING            *f_dstrPrivKeyCRTExponent1,
    __in    const DRM_CONST_STRING            *f_dstrPrivKeyIQMP,
    __inout       DRM_RSA_PRIVATE_KEY_2048BIT *f_pKeyRSAPrivate );

EXIT_PK_NAMESPACE;

#endif /* __DRMXMLRSAKEYS_H__ */

