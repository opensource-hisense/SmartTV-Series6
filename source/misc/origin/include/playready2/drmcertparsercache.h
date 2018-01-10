/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRM_CERTPARSERCACHE__
#define __DRM_CERTPARSERCACHE__

#include <drmtypes.h>
#include <drmdevcertcache.h>
#include <drmkeyfile.h>

ENTER_PK_NAMESPACE;

DRM_API DRM_BOOL DRM_CALL DRM_CERTPARSERCACHE_IsCertParserCacheSupported(DRM_VOID);
DRM_API DRM_BOOL DRM_CALL DRM_CERTPARSERCACHE_IsCertParserCacheUnsupported(DRM_VOID);

DRM_API DRM_RESULT DRM_CALL DRM_CERTPARSERCACHE_PackCertParserEntry(
    __in  DRM_WORD                            f_iAttrib,
    __in_bcount( f_cbPacked )
          DRM_BYTE                           *f_pbPacked,
    __in  DRM_DWORD                           f_cbPacked,
    __out DRM_DEVICE_CERT_PARSER_CACHE_ENTRY *f_poEntry );

DRM_API DRM_RESULT DRM_CALL DRM_CERTPARSERCACHE_UnpackCertParserEntry(
    __in  DRM_WORD                            f_iAttrib,
    __in_bcount( f_cbPacked )
          const DRM_BYTE                     *f_pbPacked,
    __in  DRM_DWORD                           f_cbPacked,
    __out DRM_DEVICE_CERT_PARSER_CACHE_ENTRY *f_poEntry );

DRM_API DRM_RESULT DRM_CALL DRM_CERTPARSERCACHE_DCP_StartCertParserCache(
    __in     const DRM_CONST_STRING             *f_pdstrDevCert,
    __in_opt const DRM_KEYFILE_CONTEXT          *f_poKeyFileContext,
    __out          DRM_DEVICE_CERT_PARSER_CACHE *f_poParserCache );

DRM_API DRM_RESULT DRM_CALL DRM_CERTPARSERCACHE_DCP_StopCertParserCache(
    __in_opt DRM_KEYFILE_CONTEXT          *f_poKeyFileContext,
    __in     DRM_DEVICE_CERT_PARSER_CACHE *f_poParserCache );

EXIT_PK_NAMESPACE;

#endif /* __DRM_CERTPARSERCACHE__ */

