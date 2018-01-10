/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __OEMRSA_H__
#define __OEMRSA_H__

#include <drmtypes.h>
#include <oemrsaimpl.h>
#include <oemrsacommon.h>
#include <drmlicense.h>

ENTER_PK_NAMESPACE;

#define BITS_TO_BYTES( nb ) ( ( ( nb ) + BITS_PER_STANDARD_BYTE - 1 ) / BITS_PER_STANDARD_BYTE )
#define BYTES_TO_BITS( nb ) ( ( nb ) * BITS_PER_STANDARD_BYTE )

extern DRM_EXPORT_VAR const DRM_BYTE rgbDRM_RSA_DEFAULT_PUBEXP[__CB_DECL( DRM_RSA_CB_PUBEXP )];

#define DRM_RSA_DEFAULT_PUBEXP_DWORD 65537

/*
** Sizes of internal RSA key structures:
*/
#define DRM_RSA_CB_PUBKEY_2048BIT   SIZEOF( INTERNAL_DRM_RSA_PUBLIC_KEY_2048BIT )
#define DRM_RSA_CB_PRIVKEY_2048BIT  SIZEOF( INTERNAL_DRM_RSA_PRIVATE_KEY_2048BIT )

/*
** RSA public key
**
** The actual contents of the structure are opaque.
** The opaque data is represented as a byte array below.
** Do not access the array or assume the size of this structure.
*/
typedef struct __tagDRM_RSA_PUBLIC_KEY_2048BIT
{
    DRM_BYTE rgbOpaque[__CB_DECL( DRM_RSA_CB_PUBKEY_2048BIT )];
} DRM_RSA_PUBLIC_KEY_2048BIT;

/*
** RSA private key
**
** The actual contents of the structure are opaque.
** The opaque data is represented as a byte array below.
** Do not access the array or assume the size of this structure.
*/
typedef struct __tagDRM_RSA_PRIVATE_KEY_2048BIT
{
    DRM_BYTE rgbOpaque[__CB_DECL( DRM_RSA_CB_PRIVKEY_2048BIT )];
} DRM_RSA_PRIVATE_KEY_2048BIT;

/*
** Key management functions:
*/
DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL OEM_RSA_GetPublicKeyLength_2048BIT(
    __in const DRM_RSA_PUBLIC_KEY_2048BIT            *f_pPublicKey,
    __out      DRM_RSA_SUPPORTED_KEY_LENGTHS_2048BIT *f_peKeyLength
    ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL OEM_RSA_GetPrivateKeyLength_2048BIT(
    __in const DRM_RSA_PRIVATE_KEY_2048BIT           *f_pPrivateKey,
    __out      DRM_RSA_SUPPORTED_KEY_LENGTHS_2048BIT *f_peKeyLength
    ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL OEM_RSA_GetKeyLengthFromModulusLength_2048BIT(
    __in const DRM_DWORD                              f_cbModulus,
    __out      DRM_RSA_SUPPORTED_KEY_LENGTHS_2048BIT *f_peKeyLength
    ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL OEM_RSA_ParsePublicKey_2048BIT(
    __in const                        DRM_RSA_PUBLIC_KEY_2048BIT            *f_pPublicKey,
    __out_opt                         DRM_RSA_SUPPORTED_KEY_LENGTHS_2048BIT *f_peKeyLength,
    __inout_opt                       DRM_DWORD                             *f_pcbPubExp,
    __out_ecount_opt( *f_pcbPubExp )  DRM_BYTE                              *f_pbPubExp,
    __inout_opt                       DRM_DWORD                             *f_pcbModulus,
    __out_ecount_opt( *f_pcbModulus ) DRM_BYTE                              *f_pbModulus
    ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL OEM_RSA_ParsePrivateKey_2048BIT(
    __in                              const DRM_RSA_PRIVATE_KEY_2048BIT           *f_pPrivateKey,
    __out_opt                               DRM_RSA_SUPPORTED_KEY_LENGTHS_2048BIT *f_peKeyLength,
    __inout_opt                             DRM_DWORD                             *f_pcbPrivExp,
    __out_ecount_opt( *f_pcbPrivExp ) const DRM_BYTE                              *f_pbPrivExp,
    __inout_opt                             DRM_DWORD                             *f_pcbPrimes,
    __out_ecount_opt( *f_pcbPrimes )        DRM_BYTE                              *f_pbPrime0,
    __out_ecount_opt( *f_pcbPrimes )        DRM_BYTE                              *f_pbPrime1 ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL OEM_RSA_SetPublicKey_2048BIT(
    __in const                       DRM_RSA_SUPPORTED_KEY_LENGTHS_2048BIT  f_eKeyLength,
    __in const                       DRM_DWORD                              f_cbPubExp,
    __in_ecount( f_cbPubExp ) const  DRM_BYTE                              *f_pbPubExp,
    __in const                       DRM_DWORD                              f_cbModulus,
    __in_ecount( f_cbModulus ) const DRM_BYTE                              *f_pbModulus,
    __out                            DRM_RSA_PUBLIC_KEY_2048BIT            *f_pPublicKey
    ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL OEM_RSA_SetPrivateKey_2048BIT(
    __in const                       DRM_RSA_SUPPORTED_KEY_LENGTHS_2048BIT  f_eKeyLength,
    __in const                       DRM_DWORD                              f_cbPrivExp,
    __in_ecount( f_cbPrivExp ) const DRM_BYTE                              *f_pbPrivExp,
    __in const                       DRM_DWORD                              f_cbPrimes,
    __in_ecount( f_cbPrimes ) const  DRM_BYTE                              *f_pbPrime0,
    __in_ecount( f_cbPrimes ) const  DRM_BYTE                              *f_pbPrime1,
    __out                            DRM_RSA_PRIVATE_KEY_2048BIT           *f_pPrivateKey,
    __inout                          DRM_CRYPTO_CONTEXT                    *f_pCryptoCtx
    ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL OEM_RSA_ZeroPublicKey_2048BIT(
    __in       DRM_RSA_PUBLIC_KEY_2048BIT            *f_pPublicKey
    ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_RESULT DRM_CALL OEM_RSA_ZeroPrivateKey_2048BIT(
    __in       DRM_RSA_PRIVATE_KEY_2048BIT           *f_pPrivateKey
    );

/*
** Encryption and decryption functions
*/
DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL OEM_RSA_Encrypt_2048BIT(
    __in const                      DRM_RSA_PUBLIC_KEY_2048BIT *f_pPublicKey,
    __in const                      DRM_DWORD                   f_cbDataIn,
    __in_ecount( f_cbDataIn ) const DRM_BYTE                   *f_pbDataIn,
    __out_ecount( f_cbDataIn )      DRM_BYTE                   *f_pbDataOut,
    __in                            DRM_CRYPTO_CONTEXT         *f_pCryptoCtx
    ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL OEM_RSA_Decrypt_2048BIT(
    __in const                      DRM_RSA_PRIVATE_KEY_2048BIT *f_pPrivateKey,
    __in const                      DRM_DWORD                    f_cbDataIn,
    __in_ecount( f_cbDataIn ) const DRM_BYTE                    *f_pbDataIn,
    __out_ecount( f_cbDataIn )      DRM_BYTE                    *f_pbDataOut,
    __in                            DRM_CRYPTO_CONTEXT          *f_pCryptoCtx
    ) DRM_NO_INLINE_ATTRIBUTE;

/*
** Key generation
*/
DRM_API DRM_RESULT DRM_CALL OEM_RSA_GenerateKeyPair_2048BIT(
    __in const      DRM_RSA_SUPPORTED_KEY_LENGTHS_2048BIT  f_eKeyLength,
    __out_ecount(1) DRM_RSA_PRIVATE_KEY_2048BIT           *f_pPrivateKey,
    __out_ecount(1) DRM_RSA_PUBLIC_KEY_2048BIT            *f_pPublicKey,
    __inout         DRM_CRYPTO_CONTEXT                    *f_pCryptoCtx
    );

/******************************************************************************
**
** RSA 4096BIT (512BYTE) support
**
******************************************************************************/

#define DRM_RSA_CB_PUBKEY_4096BIT   SIZEOF( INTERNAL_DRM_RSA_PUBLIC_KEY_4096BIT )
#define DRM_RSA_CB_PRIVKEY_4096BIT  SIZEOF( INTERNAL_DRM_RSA_PRIVATE_KEY_4096BIT )

typedef struct __tagDRM_RSA_PUBLIC_KEY_4096BIT
{
    DRM_BYTE rgbOpaque[__CB_DECL( DRM_RSA_CB_PUBKEY_4096BIT )];
} DRM_RSA_PUBLIC_KEY_4096BIT;

typedef struct __tagDRM_RSA_PRIVATE_KEY_4096BIT
{
    DRM_BYTE rgbOpaque[__CB_DECL( DRM_RSA_CB_PRIVKEY_4096BIT )];
} DRM_RSA_PRIVATE_KEY_4096BIT;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL OEM_RSA_GetPublicKeyLength_4096BIT(
    __in const DRM_RSA_PUBLIC_KEY_4096BIT            *f_pPublicKey,
    __out      DRM_RSA_SUPPORTED_KEY_LENGTHS_4096BIT *f_peKeyLength
    ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL OEM_RSA_GetPrivateKeyLength_4096BIT(
    __in const DRM_RSA_PRIVATE_KEY_4096BIT           *f_pPrivateKey,
    __out      DRM_RSA_SUPPORTED_KEY_LENGTHS_4096BIT *f_peKeyLength
    ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL OEM_RSA_GetKeyLengthFromModulusLength_4096BIT(
    __in const DRM_DWORD                              f_cbModulus,
    __out      DRM_RSA_SUPPORTED_KEY_LENGTHS_4096BIT *f_peKeyLength
    ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL OEM_RSA_ParsePublicKey_4096BIT(
    __in const                        DRM_RSA_PUBLIC_KEY_4096BIT            *f_pPublicKey,
    __out_opt                         DRM_RSA_SUPPORTED_KEY_LENGTHS_4096BIT *f_peKeyLength,
    __inout_opt                       DRM_DWORD                             *f_pcbPubExp,
    __out_ecount_opt( *f_pcbPubExp )  DRM_BYTE                              *f_pbPubExp,
    __inout_opt                       DRM_DWORD                             *f_pcbModulus,
    __out_ecount_opt( *f_pcbModulus ) DRM_BYTE                              *f_pbModulus
    ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_RESULT DRM_CALL OEM_RSA_ParsePrivateKey_4096BIT(
    __in const                              DRM_RSA_PRIVATE_KEY_4096BIT           *f_pPrivateKey,
    __out_opt                               DRM_RSA_SUPPORTED_KEY_LENGTHS_4096BIT *f_peKeyLength,
    __inout_opt                             DRM_DWORD                             *f_pcbPrivExp,
    __out_ecount_opt( *f_pcbPrivExp ) const DRM_BYTE                              *f_pbPrivExp,
    __inout_opt                             DRM_DWORD                             *f_pcbPrimes,
    __out_ecount_opt( *f_pcbPrimes )        DRM_BYTE                              *f_pbPrime0,
    __out_ecount_opt( *f_pcbPrimes )        DRM_BYTE                              *f_pbPrime1
    );

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL OEM_RSA_SetPublicKey_4096BIT(
    __in const                       DRM_RSA_SUPPORTED_KEY_LENGTHS_4096BIT  f_eKeyLength,
    __in const                       DRM_DWORD                              f_cbPubExp,
    __in_ecount( f_cbPubExp ) const  DRM_BYTE                              *f_pbPubExp,
    __in const                       DRM_DWORD                              f_cbModulus,
    __in_ecount( f_cbModulus ) const DRM_BYTE                              *f_pbModulus,
    __out                            DRM_RSA_PUBLIC_KEY_4096BIT            *f_pPublicKey
    ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL OEM_RSA_SetPrivateKey_4096BIT(
    __in const                       DRM_RSA_SUPPORTED_KEY_LENGTHS_4096BIT  f_eKeyLength,
    __in const                       DRM_DWORD                              f_cbPrivExp,
    __in_ecount( f_cbPrivExp ) const DRM_BYTE                              *f_pbPrivExp,
    __in const                       DRM_DWORD                              f_cbPrimes,
    __in_ecount( f_cbPrimes ) const  DRM_BYTE                              *f_pbPrime0,
    __in_ecount( f_cbPrimes ) const  DRM_BYTE                              *f_pbPrime1,
    __out                            DRM_RSA_PRIVATE_KEY_4096BIT           *f_pPrivateKey,
    __inout                          DRM_CRYPTO_CONTEXT                    *f_pCryptoCtx
    ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL OEM_RSA_ZeroPublicKey_4096BIT(
    __in       DRM_RSA_PUBLIC_KEY_4096BIT            *f_pPublicKey
    ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_RESULT DRM_CALL OEM_RSA_ZeroPrivateKey_4096BIT(
    __in       DRM_RSA_PRIVATE_KEY_4096BIT           *f_pPrivateKey
    );

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL OEM_RSA_Encrypt_4096BIT(
    __in const                      DRM_RSA_PUBLIC_KEY_4096BIT *f_pPublicKey,
    __in const                      DRM_DWORD                   f_cbDataIn,
    __in_ecount( f_cbDataIn ) const DRM_BYTE                   *f_pbDataIn,
    __out_ecount( f_cbDataIn )      DRM_BYTE                   *f_pbDataOut,
    __in                            DRM_CRYPTO_CONTEXT         *f_pCryptoCtx
    ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL OEM_RSA_Decrypt_4096BIT(
    __in const                      DRM_RSA_PRIVATE_KEY_4096BIT *f_pPrivateKey,
    __in const                      DRM_DWORD                    f_cbDataIn,
    __in_ecount( f_cbDataIn ) const DRM_BYTE                    *f_pbDataIn,
    __out_ecount( f_cbDataIn )      DRM_BYTE                    *f_pbDataOut,
    __in                            DRM_CRYPTO_CONTEXT          *f_pCryptoCtx
    ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_RESULT DRM_CALL OEM_RSA_GenerateKeyPair_4096BIT(
    __in const      DRM_RSA_SUPPORTED_KEY_LENGTHS_4096BIT  f_eKeyLength,
    __out_ecount(1) DRM_RSA_PRIVATE_KEY_4096BIT           *f_pPrivateKey,
    __out_ecount(1) DRM_RSA_PUBLIC_KEY_4096BIT            *f_pPublicKey,
    __inout         DRM_CRYPTO_CONTEXT                    *f_pCryptoCtx
    );

EXIT_PK_NAMESPACE;

#endif /* __OEMRSA_H__ */

