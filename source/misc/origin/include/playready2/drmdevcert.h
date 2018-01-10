/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRMDEVCERTPARSER_H__
#define __DRMDEVCERTPARSER_H__

#include <drmbcert.h>
#include <oemeccp256.h>
#include <drmkeyfile.h>

#include <drmdevcerttypes.h>

ENTER_PK_NAMESPACE;

DRM_API DRM_RESULT DRM_CALL DRM_DCP_GetAttribute(
    __in_opt  DRM_DEVICE_CERT_PARSER_CACHE *f_poParserCache,
    __in      const DRM_CONST_STRING       *f_pdstrDevCert,
    __in      eDRM_DEVCERT_ATTRIBUTES       f_eAttribute,
    __out_opt DRM_CONST_STRING             *f_pdstrNode,
    __out_opt DRM_CONST_STRING             *f_pdstrValue );

DRM_API DRM_RESULT DRM_CALL DRM_DCP_StartCertParserCache(
    __in     const DRM_CONST_STRING             *f_pdstrDevCert,
    __in_opt const DRM_KEYFILE_CONTEXT          *f_poKeyFileContext,
    __out          DRM_DEVICE_CERT_PARSER_CACHE *f_poParserCache );

DRM_API DRM_RESULT DRM_CALL DRM_DCP_StopCertParserCache(
    __in_opt DRM_KEYFILE_CONTEXT          *f_poKeyFileContext,
    __in     DRM_DEVICE_CERT_PARSER_CACHE *f_poParserCache );

DRM_API DRM_RESULT DRM_CALL DRM_DCP_VerifyDeviceCert(
    __in_opt   DRM_DEVICE_CERT_PARSER_CACHE *f_poParserCache,
    __in const DRM_CONST_STRING             *f_pdstrDevCert,
    __in       DRM_DWORD                     f_dwVerifyFlags,
    __in_opt   DRM_KEYFILE_CONTEXT          *f_poKeyFileContext,
    __in       DRM_CRYPTO_CONTEXT           *f_pcontextCRYP );

DRM_API DRM_RESULT DRM_CALL DRM_DCP_LoadPropertiesCache(
    __in_opt       DRM_DEVICE_CERT_PARSER_CACHE          *f_poParserCache,
    __in     const DRM_CONST_STRING                      *f_pdstrDevCert,
    __in_opt       DRM_KEYFILE_CONTEXT                   *f_poKeyFileContext,
    __in     const DRM_CRYPTO_CONTEXT                    *f_poCryptoContext,
    __out          DRM_DEVICE_CERTIFICATE_CACHED_VALUES  *f_pcacheDevCert );

EXIT_PK_NAMESPACE;

#endif /* __DRMDEVCERTPARSER_H__ */

