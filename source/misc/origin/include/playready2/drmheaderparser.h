/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/


#ifndef __DRMHEADERPARSER_H__
#define __DRMHEADERPARSER_H__

#include <drmtypes.h>
#include <oemcryptoctx.h>
#include <drmpragmas.h>

ENTER_PK_NAMESPACE;

#define DRM_HEADER_MAX_SIZE_IN_BYTES 5120

typedef enum
{
    DRM_HEADER_ATTRIB_VERSION            = 1,
    DRM_HEADER_ATTRIB_KID                = 2,
    DRM_HEADER_ATTRIB_LAINFO             = 3,
    DRM_HEADER_ATTRIB_CHECKSUM           = 4,
    DRM_HEADER_ATTRIB_SECURITYVERSION    = 5,
    DRM_HEADER_ATTRIB_OTHER              = 6,
    DRM_HEADER_ATTRIB_LICENSE_ACQ_V4_URL = 7,
    DRM_HEADER_ATTRIB_LICENSE_UI_URL     = 8,
    DRM_HEADER_ATTRIB_DOMAIN_SERVICE_ID  = 9,
    DRM_HEADER_ATTRIB_DECRYPTOR_SETUP    = 10,
    DRM_HEADER_ATTRIB_ALGID              = 11,
} eDRM_HEADER_ATTRIBUTES;

typedef enum
{
    DRM_HEADER_VERSION_UNKNOWN           = 0,
    DRM_HEADER_VERSION_2                 = 1,
    DRM_HEADER_VERSION_2_4               = 3,
    DRM_HEADER_VERSION_4                 = 2,
    DRM_HEADER_VERSION_4_1               = 4,
} eDRM_HEADER_VERSION;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_HDR_GetHeaderVersion(
    __in const DRM_CONST_STRING     *f_pdstrContentHeader,
    __out      eDRM_HEADER_VERSION  *f_peVersion );

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_HDR_GetAttribute(
    __in     const DRM_CONST_STRING       *pdstrContentHeader,
    __in_opt const DRM_CONST_STRING       *pdstrAttrName,
    __in           eDRM_HEADER_ATTRIBUTES  eAttribute,
    __out          DRM_CONST_STRING       *pdstrValue,
    __in           DRM_WCHAR               chXPathSeparator);

DRM_API DRM_RESULT DRM_CALL DRM_HDR_GetUplink(
    __in const DRM_CONST_STRING *pdstrContentHeader,
    __in       DRM_DWORD         dwUplinkNumber,
    __out      DRM_CONST_STRING *pdstrKid );

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_HDR_Verify(
    __in     const DRM_CONST_STRING   *pdstrContentHeader,
    __in_opt const DRM_CONST_STRING   *pdstrPubKey,
    __in_opt       DRM_CRYPTO_CONTEXT *pContext,
    __out          DRM_LONG           *plResult );

EXIT_PK_NAMESPACE;

#endif /* __DRMHEADERPARSER_H__ */

