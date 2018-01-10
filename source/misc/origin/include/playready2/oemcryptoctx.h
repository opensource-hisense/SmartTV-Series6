/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/


#ifndef __OEMCRYPTOCTX_H__
#define __OEMCRYPTOCTX_H__

#include <drmstkalloc.h>

ENTER_PK_NAMESPACE;

/* The following sizes are in BYTEs */
#define DRM_ECC160_PUBLIC_KEY_LEN   40
#define DRM_ECC160_PRIVATE_KEY_LEN  20
#define DRM_ECC160_PLAINTEXT_LEN    16
#define DRM_ECC160_CIPHERTEXT_LEN   80
#define DRM_ECC160_SIGNATURE_LEN    40
#define DRM_ECC160_SIGNATURE_B64LEN 56 /* CCH_BASE64_EQUIV_SAL(DRM_ECC160_SIGNATURE_LEN) */

#define PKSYMM_ALG_TYPE_RC4        1

/*
** The largest single allocation in the crypto code is in mod_exp
** which allocates up to this many bytes: (1 << MAX_BUCKET_WIDTH) * (max digits) * sizeof(digit)
** MAX_BUCKET_WIDTH from modexp.c is 6, so (1 << MAX_BUCKET_WIDTH) == 0x40
** Meanwhile, max digits is 0x80 used by 4096-bit-RSA.
** So the largest single allocation is 0x40 * 0x80 * 4 == 0x8000 bytes.
** This allocation dwarfs all the other buffer allocations that might be
** used in conjunction with it by a factor of more than 0x10, and no
** codepath that doesn't use mod_exp comes anywhere close to using this
** large a buffer. Therefore, set the size to 0x8800:
** 0x8000 for that one allocation and an additional
** 0x0800 for all other allocations on that codepath.
*/
#define DRM_PKCRYPTO_CONTEXT_BUFFER_INTERNAL_SIZE 0x8800

/* This is size for PK_DATA structure defined in oemeccp160.h.
   This size of structure on x86 is 3036.
   use 3100 to allow larger size for different architecture.
*/
#define DRM_PK_DATA_SIZE                          3200

#define LNGQDW 5
#define LNGQ DWORDS_TO_DIGITS(LNGQDW)
#define QBITS (LNGQDW * DWORD_BITS)

/*
** Defines the buffer size for DRMBIGNUM_CONTEXT_STRUCT defined in oemeccp160.h
*/
#define DRM_PKCRYPTO_CONTEXT_BUFFER_SIZE  ( DRM_PKCRYPTO_CONTEXT_BUFFER_INTERNAL_SIZE + SIZEOF( DRM_STACK_ALLOCATOR_CONTEXT ) + DRM_PK_DATA_SIZE + SIZEOF( DRM_DWORD ) + SIZEOF(DRM_VOID*) + DRM_OBFUS_PTR_WRAP_SIZE )

typedef DRM_DWORD_ALIGN struct __tagPUBKEY
{
    DRM_BYTE y[ __CB_DECL(DRM_ECC160_PUBLIC_KEY_LEN) ];
} PUBKEY;

typedef DRM_DWORD_ALIGN struct __tagPRIVKEY
{
    DRM_BYTE x[ __CB_DECL(DRM_ECC160_PRIVATE_KEY_LEN) ];
} PRIVKEY;

typedef struct {
    PUBKEY pk;
    DRM_BYTE version[__CB_DECL(VERSION_LEN)];
} PKV;

typedef struct {
    PKV pk;  /* pk.version indicates the pubkey needed to verify. */
    DRM_BYTE sign[__CB_DECL(DRM_ECC160_SIGNATURE_LEN)];
} PKCERT;

#if !DRM_SUPPORT_FORCE_ALIGN
#if defined (DRM_MSC_VER)
#pragma pack(push)
#pragma pack(1)
#endif /* #if defined (DRM_MSC_VER) */
#endif /* #if !DRM_SUPPORT_FORCE_ALIGN */

#define ISSUER_LEN           4
#define SUBJ_LEN             4
#define DATE_LEN             4
#define SER_NUM_LEN          4
#define INT_LEN              4

typedef struct CERTDATAtag{
    PUBKEY pk;
    DRM_BYTE expiryDate  [__CB_DECL(DATE_LEN)];
    DRM_BYTE serialNumber[__CB_DECL(SER_NUM_LEN)];
    DRM_BYTE issuer      [__CB_DECL(ISSUER_LEN)];
    DRM_BYTE subject     [__CB_DECL(SUBJ_LEN)];
} CERTDATA, *PCERTDATA;

typedef struct CERTtag{
    DRM_BYTE certVersion[__CB_DECL(VERSION_LEN)];
    DRM_BYTE datalen    [__CB_DECL(INT_LEN)];
    DRM_BYTE sign       [__CB_DECL(DRM_ECC160_SIGNATURE_LEN)];
    CERTDATA cd;
} CERT, *PCERT;

#if !DRM_SUPPORT_FORCE_ALIGN
#if defined (DRM_MSC_VER)
#pragma pack(pop)
#endif /* #if defined (DRM_MSC_VER) */
#endif /* #if !DRM_SUPPORT_FORCE_ALIGN */

typedef DRM_OBFUS_FIXED_ALIGN struct __tagDRM_CRYPTO_CONTEXT
{
    DRM_BYTE rgbCryptoContext[__CB_DECL(DRM_PKCRYPTO_CONTEXT_BUFFER_SIZE)];   /* size of the buffer pkcrypto code needs. Note this may have alignment problems. */
    PUBKEY   pubKey;  /* 40 BYTES */
    PUBKEY   pubKey2; /* 40 BYTES */
    union  _tagcert
    {
        CERT     cert;    /* 108 bytes */
        PKCERT   pkcert;  /* 84 bytes  */
    } union_cert;
    DRM_BYTE signature[__CB_DECL(DRM_ECC160_SIGNATURE_LEN)];   /* 40 BYTES     */
DRM_OBFUS_FILL_BYTES(4)
} DRM_CRYPTO_CONTEXT;

EXIT_PK_NAMESPACE;

#endif /* __OEMCRYPTOCTX_H__ */

