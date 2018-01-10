/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/


#ifndef __OEMECCP160_H__
#define __OEMECCP160_H__

#include <oemcryptoctx.h>
#include <ecurve.h>
#include <mprand.h>

ENTER_PK_NAMESPACE;

DRM_API DRM_VOID DRM_CALL OEM_ECC_ZeroPublicKey_P160(
    __inout        PUBKEY     *f_pPubkey );

DRM_API DRM_VOID DRM_CALL OEM_ECC_ZeroPrivateKey_P160(
    __inout        PRIVKEY    *f_pPrivkey );

/*********************************************************************
**
**  Function:  OEM_ECC_GenKeyPair_P160
**
**  Synopsis:  Generate a matched public and private key pair
**
**  Arguments:
**     [f_pContext] -- Pointer to context the size of DRM_PKCRYPTO_CONTEXT_BUFFER_SIZE
**     [f_ppubkey]  -- New public key
**     [f_pprivkey] -- New private key
**
*********************************************************************/
DRM_API DRM_RESULT DRM_CALL OEM_ECC_GenKeyPair_P160(
    __in  DRM_VOID *f_pContext,
    __out PUBKEY   *f_ppubkey,
    __out PRIVKEY  *f_pprivkey );

/*********************************************************************
**
**  Function:  OEM_ECC_Encrypt_P160
**
**  Synopsis:  Encrypt a block of data with a given public key.
**
**  Arguments:
**     [f_pContext] -- Pointer to context the size of DRM_PKCRYPTO_CONTEXT_BUFFER_SIZE
**     [f_ppubkey]  -- Public key to encrypt with
**     [f_rgbIn]    -- Data to be encrypted
**     [f_rgbOut]   -- Buffer to hold the encrypted data value.
**
**  Notes:  Data is not encrpyted in place.  It is put in the rgbOut buffer.
*********************************************************************/
DRM_API DRM_RESULT DRM_CALL OEM_ECC_Encrypt_P160(
    __in                                            DRM_VOID *f_pContext,
    __in                                      const PUBKEY   *f_ppubkey,
    __in_bcount( DRM_ECC160_PLAINTEXT_LEN )   const DRM_BYTE  f_rgbIn[__CB_DECL(DRM_ECC160_PLAINTEXT_LEN)],
    __out_bcount( DRM_ECC160_CIPHERTEXT_LEN )       DRM_BYTE  f_rgbOut[__CB_DECL(DRM_ECC160_CIPHERTEXT_LEN)] );


/*********************************************************************
**
**  Function:  OEM_ECC_Decrypt_P160
**
**  Synopsis:
**
**  Arguments:
**     [f_pContext] -- Pointer to context the size of DRM_PKCRYPTO_CONTEXT_BUFFER_SIZE
**     [f_pprivkey] -- Private key to decrypt with
**     [f_rgbIn]    -- Encrypted bytes that are to be decrypted
**     [f_rgbOut]   -- Clear text result
**
**  Notes:  Data is not decrpyted in place.  It is put in the rgbOut buffer.
**
*********************************************************************/
DRM_API DRM_RESULT DRM_CALL OEM_ECC_Decrypt_P160(
    __in                                           DRM_VOID *f_pContext,
    __in                                     const PRIVKEY  *f_pprivkey,
    __in_bcount( DRM_ECC160_CIPHERTEXT_LEN ) const DRM_BYTE  f_rgbIn [__CB_DECL(DRM_ECC160_CIPHERTEXT_LEN)],
    __out_bcount( DRM_ECC160_PLAINTEXT_LEN )       DRM_BYTE  f_rgbOut[__CB_DECL(DRM_ECC160_PLAINTEXT_LEN) ] );


/*********************************************************************
**
**  Function:  OEM_ECC_Sign_P160
**
**  Synopsis:  Generate a digital signature with a private key
**
**  Arguments:
**     [f_pContext]     -- Pointer to context the size of DRM_PKCRYPTO_CONTEXT_BUFFER_SIZE
**     [f_privkey]      -- Private key to create a signature with
**     [f_pbData]       -- Array of bytes to create a signature over
**     [f_cbData]       -- Length of pbBuffer in bytes
**     [f_rgbSignature] -- Buffer to hold result signature
*********************************************************************/
DRM_API DRM_RESULT DRM_CALL OEM_ECC_Sign_P160(
    __in                                           DRM_VOID  *f_pContext,
    __in                                     const PRIVKEY   *f_privkey,
    __out_bcount( f_cbData )                 const DRM_BYTE  *f_pbData,
    __in                                           DRM_DWORD  f_cbData,
    __out_bcount( DRM_ECC160_SIGNATURE_LEN )       DRM_BYTE   f_rgbSignature[ __CB_DECL(DRM_ECC160_SIGNATURE_LEN) ] );

/*********************************************************************
**
**  Function:  OEM_ECC_Verify_P160
**
**  Synopsis:  Verify a digital signature created by OEM_ECC_Sign_P160.
**
**  Arguments:
**     [f_pContext]     -- Pointer to context the size of DRM_PKCRYPTO_CONTEXT_BUFFER_SIZE
**     [f_ppubkey]      -- Pubkey to check the signature with
**     [f_pbData]       -- Data buffer that the signature was created over
**     [f_cbData]       -- Length of pbBuffer in bytes
**     [f_rgbSignature] -- The signature to verify
**
**  Returns:  TRUE if the signature verified correctly.  FALSE is it didn't
**
*********************************************************************/
DRM_API DRM_BOOL DRM_CALL OEM_ECC_Verify_P160(
    __in                                          DRM_VOID  *f_pContext,
    __in                                    const PUBKEY    *f_ppubkey,
    __in_bcount( f_cbData )                 const DRM_BYTE  *f_pbData,
    __in                                          DRM_DWORD  f_cbData,
    __in_bcount( DRM_ECC160_SIGNATURE_LEN ) const DRM_BYTE   f_rgbSignature[__CB_DECL(DRM_ECC160_SIGNATURE_LEN)] ) DRM_NO_INLINE_ATTRIBUTE;

/*********************************************************************
**
**  Function:  OEM_ECC_ThreadUnSafePKInit, OEM_ECC_ThreadSafeInit
**
**  Synopsis:  Initializes DRMBIGNUM_CONTEXT_STRUCT
**
**  Arguments:
**     [f_pContext]     -- Pointer to context the size of DRM_PKCRYPTO_CONTEXT_BUFFER_SIZE

**  Returns:  DRM_SUCCESS if context is initialized.
**
*********************************************************************/

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL OEM_ECC_ThreadUnSafePKInit(
    __inout  DRM_VOID* f_pContext,
    __in_opt DRM_VOID* f_pOEMContext ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_VOID DRM_CALL DRM_RSA_PKInitSize(
    __inout DRM_VOID *f_pContext,
    __in    DRM_DWORD f_dwSize ) DRM_NO_INLINE_ATTRIBUTE;


/* Although thread safeness is mentioned here, it is not enough: bignum also has to be made thread safe to use these functions since bignum context is used within them. */

#if DRM_THREAD_SAFE
#define OEM_ECC_PKInit( pContext, pOEMContext  ) OEM_ECC_ThreadSafeInit( pContext, pOEMContext )
#else
#define OEM_ECC_PKInit( pContext, pOEMContext  ) OEM_ECC_ThreadUnSafePKInit( pContext, pOEMContext  )
#endif

/* Zeroes out bignum stack, not thread safe */
DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL OEM_ECC_InitializeBignumStack( DRM_VOID* f_pContext ) DRM_NO_INLINE_ATTRIBUTE;

#define TABLE_SPACING 4
#define TABLE_LAST 60
#define PK_DATA_HEAP_SIZE 250

typedef struct {
    digit_t q[LNGQ];
    digit_t a[LNGQ];
    digit_t b[LNGQ];
    digit_t r[LNGQ];         /* order of curve */
    DRM_DWORD   lngr;        /* Length of r (digits) */

    digit_t g[2*LNGQ];
    digit_t TABLE[ 2 * LNGQ * (TABLE_LAST+1) ];

    mp_modulus_t   qmodulus;
    ecurve_t       ecurve;
    field_desc_t   fdesc;
    reciprocal_1_t rrecip;             /* For division by r */

    DRM_STACK_ALLOCATOR_CONTEXT pkdHeap;
    DRM_BYTE rgbHeap[__CB_DECL(PK_DATA_HEAP_SIZE)];
} PK_DATA;

typedef struct __DRMBIGNUM_CONTEXT_STRUCT
{
    DRM_STACK_ALLOCATOR_CONTEXT oHeap;
    DRM_BYTE  rgbHeap[__CB_DECL(DRM_PKCRYPTO_CONTEXT_BUFFER_INTERNAL_SIZE)];
    PK_DATA   pkData;
    DRM_DWORD fInited;
    DRM_VOID *pOEMContext;
} DRMBIGNUM_CONTEXT_STRUCT;


EXIT_PK_NAMESPACE;

#endif /* __OEMECCP160_H__ */

