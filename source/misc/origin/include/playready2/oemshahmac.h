/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __OEMSHAHMAC_H__
#define __OEMSHAHMAC_H__

#include <oemshahash.h>

ENTER_PK_NAMESPACE;

typedef struct __tagDRM_HMAC_CONTEXT
{
    DRM_BOOL        fInitialized;
DRM_OBFUS_FILL_BYTES(4)
    DRM_SHA_CONTEXT shaContext;
    DRM_BYTE        shaDigest[__CB_DECL( DRM_SHA_DIGEST_LEN_MAX )];
    DRM_BYTE        rgbBuffer[__CB_DECL( DRM_SHA_BLOCK_SIZE_MAX )];
} DRM_HMAC_CONTEXT;

#define DRM_HMAC_CONTEXT_DEFAULT { FALSE, DRM_SHA_CONTEXT_DEFAULT, { 0 }, { 0 } }

DRM_API DRM_RESULT DRM_CALL DRM_HMAC_Init(
    __inout_ecount( 1 )          DRM_HMAC_CONTEXT              *f_pContextHMAC,
    __in                         eDRM_SHA_SUPPORTED_ALGORITHMS  f_eShaAlgorithm,
    __in_bcount( f_cbKey ) const DRM_BYTE                      *f_pbKey,
    __in                         DRM_DWORD                      f_cbKey );

DRM_API DRM_RESULT DRM_CALL DRM_HMAC_Update(
    __inout_ecount( 1 )           DRM_HMAC_CONTEXT  *f_pContextHMAC,
    __in_bcount( f_cbData ) const DRM_BYTE          *f_pbData,
    __in                          DRM_DWORD          f_cbData );

DRM_API DRM_RESULT DRM_CALL DRM_HMAC_Finalize(
    __inout_ecount( 1 )           DRM_HMAC_CONTEXT  *f_pContextHMAC,
    __out_bcount( f_cbKeyedHash ) DRM_BYTE          *f_pbKeyedHash,
    __in                          DRM_DWORD          f_cbKeyedHash );

PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_COUNT_REQUIRED_FOR_WRITABLE_BUFFER, "f_pbKeyedHash length defined by f_cbKeyedHash and f_ibKeyedHash" )
DRM_API DRM_RESULT DRM_CALL DRM_HMAC_FinalizeOffset(
    __inout_ecount( 1 )                             DRM_HMAC_CONTEXT  *f_pContextHMAC,
    __out_bcount( f_cbKeyedHash + f_ibKeyedHash )   DRM_BYTE          *f_pbKeyedHash,
    __in                                            DRM_DWORD          f_ibKeyedHash,
    __in                                            DRM_DWORD          f_cbKeyedHash );
PREFAST_POP

DRM_API DRM_RESULT DRM_CALL DRM_HMAC_CreateMAC(
    __in                                      eDRM_SHA_SUPPORTED_ALGORITHMS  f_eAlgorithm,
    __in_bcount( f_cbKey )              const DRM_BYTE                      *f_pbKey,
    __in                                      DRM_DWORD                      f_cbKey,
    __in_bcount( f_cbData + f_ibData )  const DRM_BYTE                      *f_pbData,
    __in                                      DRM_DWORD                      f_ibData,
    __in                                      DRM_DWORD                      f_cbData,
    __out_bcount( f_cbMAC + f_ibMAC )         DRM_BYTE                      *f_pbMAC,
    __in                                      DRM_DWORD                      f_ibMAC,
    __in                                      DRM_DWORD                      f_cbMAC );

DRM_API DRM_RESULT DRM_CALL DRM_HMAC_VerifyMAC(
    __in                                      eDRM_SHA_SUPPORTED_ALGORITHMS  f_eAlgorithm,
    __in_bcount( f_cbKey )              const DRM_BYTE                      *f_pbKey,
    __in                                      DRM_DWORD                      f_cbKey,
    __in_bcount( f_cbData + f_ibData )  const DRM_BYTE                      *f_pbData,
    __in                                      DRM_DWORD                      f_ibData,
    __in                                      DRM_DWORD                      f_cbData,
    __in_bcount( f_cbMAC + f_ibMAC )    const DRM_BYTE                      *f_pbMAC,
    __in                                      DRM_DWORD                      f_ibMAC,
    __in                                      DRM_DWORD                      f_cbMAC );

EXIT_PK_NAMESPACE;

#endif /* __OEMSHAHMAC_H__ */

