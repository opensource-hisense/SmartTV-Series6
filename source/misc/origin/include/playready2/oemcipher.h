/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/


#ifndef __OEMCIPHER_H__
#define __OEMCIPHER_H__


#include <drmerr.h>
#include <oemsha1.h>
#include <oemdes.h>
#include <oemrc4.h>
#include <oemcbc.h>
#include <oemaes.h>
#include <oemcommon.h>
#include <drmtypes.h>

ENTER_PK_NAMESPACE;

#ifndef DRMCIPHERKEYLEN_RC4
#define DRMCIPHERKEYLEN_RC4        7
#endif

/*
** Legacy PDRM content acquired through ILA will
** contain a 6-byte Cocktail content key. This is
** only valid for XMR licenses.
*/
#ifndef DRMCIPHERKEYLEN_RC4_PDRM
#define DRMCIPHERKEYLEN_RC4_PDRM   6
#endif

#ifndef DRMCIPHERKEYLEN_MAX
#define DRMCIPHERKEYLEN_MAX MAX( DRM_AES_MAXKEYSIZE, DRMCIPHERKEYLEN_RC4 )
#endif

typedef enum _DRM_SUPPORTED_CIPHERS
{
    eDRM_CIPHER_INVALID     = 0,
    eDRM_RC4_CIPHER         = 1,
    eDRM_AES_COUNTER_CIPHER = 2,
    eDRM_DES_CIPHER         = 3   /* Used only for chaining in legacy XML licenses */
} DRM_SUPPORTED_CIPHERS;

typedef struct __tagDRM_RC4_CIPHER_CONTEXT
{
    DRM_BYTE      shaOut [__CB_DECL( DRM_SHA1_DIGEST_LEN )];
    DRM_DWORD     desS1  [2];
    DRM_DWORD     desS2  [2];
    DESTable      destable;
    DRM_CBCKey    mackey;
    DRM_CBCKey    invmackey;
    RC4_KEYSTRUCT rc4ks;
    DRM_CBCState  cbcstate;
    DRM_DWORD     rc4key[2];
    DRM_DWORD     rguiLast8[2];
    DRM_DWORD     cbPacket;
    DRM_DWORD     iPacket;
    DRM_BOOL      fDecryptInited;
} DRM_RC4_CIPHER_CONTEXT;

typedef struct __tagDRM_AES_CIPHER_CONTEXT
{
    DRM_BYTE          rgbContentKey[__CB_DECL( DRM_AES_MAXKEYSIZE )];
    DRM_AES_KEY       aesKey;
DRM_OBFUS_PTR_TOP
    OEM_CRYPTO_HANDLE hAesKey;
#ifdef PLAYREADY2TEE
    DRM_BOOL secureStopUpdated;
#endif
DRM_OBFUS_PTR_BTM
} DRM_AES_CIPHER_CONTEXT;

#define DRM_OPAQUE_CIPHER_CONTEXT_SIZE 176

typedef struct __tagDRM_OPAQUE_CIPHER_CONTEXT
{
    DRM_BYTE      rgbContentKey[__CB_DECL( DRM_OPAQUE_CIPHER_CONTEXT_SIZE )];
} DRM_OPAQUE_CIPHER_CONTEXT;

typedef struct __tagDRM_CIPHER_CONTEXT
{
    DRM_SUPPORTED_CIPHERS eCipherType;
    DRM_BOOL              fInited;
    DRM_DWORD             cbContentKey;
DRM_OBFUS_FILL_BYTES(4)
    DRM_UINT64            ui64RealTimeExpiration;
    DRM_UINT64            ui64cbProcessed;
DRM_OBFUS_PTR_TOP
    DRM_VOID             *pOEMContext;
DRM_OBFUS_PTR_BTM
DRM_OBFUS_PTR_TOP
    DRM_VOID             *pOpaqueBbx;
DRM_OBFUS_PTR_BTM
    union _tagcipher
    {
        DRM_RC4_CIPHER_CONTEXT    cipherRC4;
        DRM_AES_CIPHER_CONTEXT    cipherAES;
        DRM_OPAQUE_CIPHER_CONTEXT cipherOPAQUE;
    } cipher;
} DRM_CIPHER_CONTEXT;

#define DRM_CPHR_CB_FOR_INITDECRYPT 15


DRM_API DRM_RESULT DRM_CALL DRM_CPHR_Init(
    __out_ecount( 1 )                              DRM_CIPHER_CONTEXT           *f_pContext,
    __in                                           DRM_SUPPORTED_CIPHERS         f_eCipherType,
    __in                                           DRM_DWORD                     f_cbContKey,
    __in_bcount( f_cbContKey )               const DRM_BYTE                     *f_pbContKey );


DRM_API DRM_RESULT DRM_CALL DRM_CPHR_InitWithKeyHandle(
    __inout_ecount( 1 )                            DRM_VOID                     *f_pOpaqueBBX,
    __out_ecount( 1 )                              DRM_CIPHER_CONTEXT           *f_pContext,
    __in                                           DRM_SUPPORTED_CIPHERS         f_eCipherType,
    __in                                           OEM_CRYPTO_HANDLE             f_hContKey );


DRM_API DRM_RESULT DRM_CALL DRM_CPHR_InitDecrypt(
    __inout_ecount( 1 )                                                DRM_CIPHER_CONTEXT *f_pContext,
    __in_bcount_opt( MIN(DRM_CPHR_CB_FOR_INITDECRYPT,f_cbData) ) const DRM_BYTE           *f_pbLast15,
    __in                                                               DRM_DWORD           f_cbData );


DRM_API DRM_RESULT DRM_CALL DRM_CPHR_Decrypt(
    __inout_ecount( 1 )                            DRM_CIPHER_CONTEXT           *f_pContext,
    __inout_opt                                    DRM_AES_COUNTER_MODE_CONTEXT *f_pCtrContext,
    __in                                           DRM_DWORD                     f_cbData,
    __inout_bcount( f_cbData )                     DRM_BYTE                     *f_pbData );


DRM_API DRM_RESULT DRM_CALL DRM_CPHR_Encrypt(
    __inout_ecount( 1 )                            DRM_CIPHER_CONTEXT           *f_pContext,
    __inout_opt                                    DRM_AES_COUNTER_MODE_CONTEXT *f_pCtrContext,
    __in                                           DRM_DWORD                     f_cbData,
    __inout_bcount( f_cbData )                     DRM_BYTE                     *f_pbData );

EXIT_PK_NAMESPACE;

#endif /* __OEMCIPHER_H__ */

