/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __OEMRSACOMMON_H__
#define __OEMRSACOMMON_H__

#include <byteorder.h>

ENTER_PK_NAMESPACE;

/*
** Supported key lengths
*/
typedef enum __tageDRM_RSA_SUPPORTED_KEY_LENGTHS_2048BIT
{
    eDRM_RSA_KEY_LENGTH_UNKNOWN_2048BIT  = 0,
    eDRM_RSA_KEY_LENGTH_1024_2048BIT     = 1024,
    eDRM_RSA_KEY_LENGTH_2048_2048BIT     = 2048,
} DRM_RSA_SUPPORTED_KEY_LENGTHS_2048BIT;

/* Value cannot from enum because it used to define DRM_RSA_CB_PRIME_MAX_2048BIT that used for SAL annotations */
#define eDRM_RSA_MAXIMUM_KEY_LENGTH_2048BIT               2048

#define IS_VALID_DRM_RSA_KEY_LENGTH_2048BIT( keyLength )  ( ( eDRM_RSA_KEY_LENGTH_1024_2048BIT == ( keyLength ) )   \
                                                         || ( eDRM_RSA_KEY_LENGTH_2048_2048BIT == ( keyLength ) ) )

/*
** Primes are either 1024 or 2048 bits (128 or 256 bytes) each
*/
#define DRM_RSA_CB_PRIME( keyLength )           ( (DRM_WORD)( ( keyLength ) / BITS_PER_STANDARD_BYTE ) )
#define DRM_RSA_CB_PRIME_MAX_2048BIT            DRM_RSA_CB_PRIME( eDRM_RSA_MAXIMUM_KEY_LENGTH_2048BIT )
#define DRM_RSA_B64ENC_PRIME_MAX                344 /* CCH_BASE64_EQUIV(DRM_RSA_CB_PRIME_MAX_2048BIT) */

/*
** Modulus is 128/256 bytes or 1024/2048 bits
*/
#define DRM_RSA_CB_MODULUS( keyLength )         DRM_RSA_CB_PRIME( keyLength )
#define DRM_RSA_CB_MODULUS_MAX_2048BIT          DRM_RSA_CB_MODULUS( eDRM_RSA_MAXIMUM_KEY_LENGTH_2048BIT )

#define DRM_RSA_CBITS_MODULUS( keyLength )      ( (DRM_WORD)( DRM_RSA_CB_MODULUS( keyLength ) * BITS_PER_STANDARD_BYTE ) )
#define DRM_RSA_CBITS_MODULUS_MAX_2048BIT       DRM_RSA_CBITS_MODULUS( eDRM_RSA_MAXIMUM_KEY_LENGTH_2048BIT )

/*
** RSA ciphertext length is the same as the prime length
*/
#define DRM_RSA_CB_CIPHERTEXT( keyLength )      DRM_RSA_CB_MODULUS( keyLength )
#define DRM_RSA_CB_CIPHERTEXT_MAX_2048BIT       DRM_RSA_CB_CIPHERTEXT( eDRM_RSA_MAXIMUM_KEY_LENGTH_2048BIT )

/*
** Public and private exponent sizes
*/
#define DRM_RSA_CB_PUBEXP                       4
#define DRM_RSA_CB_PRIVEXP( keyLength )         DRM_RSA_CB_MODULUS( keyLength )
#define DRM_RSA_CB_PRIVEXP_MAX_2048BIT          DRM_RSA_CB_PRIVEXP( eDRM_RSA_MAXIMUM_KEY_LENGTH_2048BIT )

/*
** For regular encryption (not large encryption) the plaintext must be smaller than the modulus
*/
#define DRM_RSA_CB_MAX_PLAINTEXT( keyLength )   ( (DRM_WORD)( ( DRM_RSA_CB_MODULUS( keyLength ) - ( 2 * DRM_SHA1_DIGEST_LEN + 2 ) ) ) )
#define DRM_RSA_CB_MAX_PLAINTEXT_MAX_2048BIT    DRM_RSA_CB_MAX_PLAINTEXT( eDRM_RSA_MAXIMUM_KEY_LENGTH_2048BIT )

/******************************************************************************
**
** RSA 4096BIT (512BYTE) support
**
******************************************************************************/

typedef enum __tageDRM_RSA_SUPPORTED_KEY_LENGTHS_4096BIT
{
    eDRM_RSA_KEY_LENGTH_UNKNOWN_4096BIT = 0,
    eDRM_RSA_KEY_LENGTH_1024_4096BIT = 1024,
    eDRM_RSA_KEY_LENGTH_2048_4096BIT = 2048,
    eDRM_RSA_KEY_LENGTH_4096_4096BIT = 4096,
} DRM_RSA_SUPPORTED_KEY_LENGTHS_4096BIT;

#define eDRM_RSA_MAXIMUM_KEY_LENGTH_4096BIT               4096

#define IS_VALID_DRM_RSA_KEY_LENGTH_4096BIT( keyLength )  ( ( eDRM_RSA_KEY_LENGTH_1024_4096BIT == ( keyLength ) )   \
                                                         || ( eDRM_RSA_KEY_LENGTH_2048_4096BIT == ( keyLength ) )   \
                                                         || ( eDRM_RSA_KEY_LENGTH_4096_4096BIT == ( keyLength ) ) )

#define DRM_RSA_CB_PRIME_MAX_4096BIT            DRM_RSA_CB_PRIME( eDRM_RSA_MAXIMUM_KEY_LENGTH_4096BIT )
#define DRM_RSA_CB_MODULUS_MAX_4096BIT          DRM_RSA_CB_MODULUS( eDRM_RSA_MAXIMUM_KEY_LENGTH_4096BIT )
#define DRM_RSA_CBITS_MODULUS_MAX_4096BIT       DRM_RSA_CBITS_MODULUS( eDRM_RSA_MAXIMUM_KEY_LENGTH_4096BIT )
#define DRM_RSA_CB_CIPHERTEXT_MAX_4096BIT       DRM_RSA_CB_CIPHERTEXT( eDRM_RSA_MAXIMUM_KEY_LENGTH_4096BIT )
#define DRM_RSA_CB_PRIVEXP_MAX_4096BIT          DRM_RSA_CB_PRIVEXP( eDRM_RSA_MAXIMUM_KEY_LENGTH_4096BIT )
#define DRM_RSA_CB_MAX_PLAINTEXT_MAX_4096BIT    DRM_RSA_CB_MAX_PLAINTEXT( eDRM_RSA_MAXIMUM_KEY_LENGTH_4096BIT )

EXIT_PK_NAMESPACE;

#endif /* __OEMRSACOMMON_H__ */

