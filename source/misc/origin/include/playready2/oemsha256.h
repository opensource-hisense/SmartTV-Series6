/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __OEMSHA256_H__
#define __OEMSHA256_H__ 1

#include <drmtypes.h>

ENTER_PK_NAMESPACE;

/*
** Sha-256 defines
*/

#define SHA256_DIGEST_SIZE_IN_BYTES  32
#define SHA256_STATE_SIZE_IN_BYTES   256
#define SHA256_STATE_SIZE_IN_DWORDS  8
#define SHA256_STATE_SIZE_IN_INT64S  4
#define SHA256_BLOCK_SIZE_IN_BYTES   64
#define SHA256_BLOCK_SIZE_IN_DWORDS  16
#define SHA256_NUM_ITERATIONS        64
#define SHA256_NUM_FRONT_ITERATIONS  16

/*
** Structs
*/
typedef struct __tagSHA256_CTX
{
    union
    {
#if DRM_64BIT_TARGET
        DRM_UINT64 m_rgu64State64[ SHA256_STATE_SIZE_IN_INT64S ]; /* force alignment */
#endif
        DRM_DWORD  m_rgdwState[ SHA256_STATE_SIZE_IN_DWORDS ];   /* state (ABCDEFGH) */
    } m_rgUnion; /* end union */

    DRM_DWORD m_rgdwCount[ 2 ]; /* number of bytes, msb first */
    DRM_DWORD m_rgdwBuffer[SHA256_BLOCK_SIZE_IN_DWORDS]; /* input buffer */
} DRM_SHA256_Context;

typedef struct __tagSHA256_Digest
{
    DRM_BYTE m_rgbDigest[ __CB_DECL( SHA256_DIGEST_SIZE_IN_BYTES ) ];
} DRM_SHA256_Digest;


/*
** Function Prototypes
*/

DRM_API DRM_RESULT DRM_CALL DRM_SHA256_Init(
    __in_ecount( 1 ) DRM_SHA256_Context *f_pShaContext );

DRM_API DRM_RESULT DRM_CALL DRM_SHA256_Update(
    __inout_ecount( 1 )             DRM_SHA256_Context *f_pShaContext,
    __in_ecount( f_cbBuffer ) const DRM_BYTE            f_rgbBuffer[],
    __in                            DRM_DWORD           f_cbBuffer );

DRM_API DRM_RESULT DRM_CALL DRM_SHA256_UpdateOffset(
    __inout_ecount( 1 )                                DRM_SHA256_Context *f_pShaContext,
    __in_ecount( f_cbBuffer + f_ibBufferOffset ) const DRM_BYTE            f_rgbBuffer[],
    __in                                               DRM_DWORD           f_cbBuffer,
    __in                                               DRM_DWORD           f_ibBufferOffset );

DRM_API DRM_RESULT DRM_CALL DRM_SHA256_Finalize(
    __inout_ecount( 1 ) DRM_SHA256_Context *f_pContext,
    __inout_ecount( 1 ) DRM_SHA256_Digest  *f_pDigest );

EXIT_PK_NAMESPACE;

#endif /* #ifndef __OEMSHA256_H__ */

