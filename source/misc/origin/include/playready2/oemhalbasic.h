/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __OEMHALBASIC_H__
#define __OEMHALBASIC_H__

#include <drmpragmas.h>
#include <drmsal.h>
#include <drmtypes.h>
#include <drmpragmas.h>

ENTER_PK_NAMESPACE;

/*
**
** OEM HAL Types and Enumerations
**
*/

/*
** Opaque hash handle representing a multi-step hash operation. 
*/
typedef DRM_VOID* OEM_HASH_HANDLE;
#define OEM_HASH_HANDLE_INVALID ((OEM_HASH_HANDLE)0)

/*
** The following type is used to represent a handle to a sample encryption context.
** The sample encryption context itself is opaque to the caller.
*/
typedef DRM_VOID* OEM_ENCRYPTION_HANDLE;
#define OEM_ENCRYPTION_HANDLE_INVALID ((OEM_ENCRYPTION_HANDLE)0)


/*
** The following type is used to select a key register.
*/
typedef DRM_LONG OEM_HAL_KEY_REGISTER_INDEX;
#define OEM_HAL_KEY_REGISTER_INDEX_INVALID (-1)

#define OEM_HAL_MAX_PRELOADED_KEYS 10

/*
** The following type is used to represent a handle to a secure buffer.
*/
typedef DRM_VOID* OEM_OPAQUE_BUFFER_HANDLE;
#define OEM_OPAQUE_BUFFER_HANDLE_INVALID ((OEM_OPAQUE_BUFFER_HANDLE)0)


/*
** Sample encryption modes.
**
** OEM_HAL_SAMPLE_ENCRYPTION_MODE_PASSTHRU          : No encryption occurs, the content is returned in the clear.
** OEM_HAL_SAMPLE_ENCRYPTION_MODE_FULL              : The entire sample is encrypted, with no subsamples defined.
** OEM_HAL_SAMPLE_ENCRYPTION_MODE_SUBSAMPLE_CENC    : The sample is composed of subsamples, each being a NAL. 
**      The subsample starts with the fixed length NAL header, which is left in the clear, the remainder of the 
**      sub-sample being encrypted. The actual number of bytes left clear is a matter of local policy, with a 
**      fixed length of 5 being typical.
** OEM_HAL_SAMPLE_ENCRYPTION_MODE_SUBSAMPLE_CFF:    The sample is composed of subsamples, each a NAL. If the
**      NAL is less than 112 bytes then the entire NAL is left unencrypted. Otherwise the first 96 to 111 bytes of
**      each NAL is left in the clear. The exact size of the unencrypted part is chosen such that the remainder of
**      the sub-sample, which is encrypted, is a multiple of 16 bytes.
**
*/
typedef enum
{
    OEM_HAL_SAMPLE_ENCRYPTION_MODE_PASSTHRU       = 0,
    OEM_HAL_SAMPLE_ENCRYPTION_MODE_FULL           = 1,
    OEM_HAL_SAMPLE_ENCRYPTION_MODE_SUBSAMPLE_CENC = 2,
    OEM_HAL_SAMPLE_ENCRYPTION_MODE_SUBSAMPLE_CFF  = 3
} OEM_HAL_SAMPLE_ENCRYPTION_MODE;


typedef struct _OEM_HAL_SUBSAMPLE
{
    DRM_DWORD dwClearLength;
    DRM_DWORD dwEncryptedLength;
} OEM_HAL_SUBSAMPLE;


#define MAX_SUB_SAMPLES 100

typedef struct _OEM_HAL_SAMPLE_METADATA
{
    OEM_HAL_SAMPLE_ENCRYPTION_MODE mode;
    DRM_UINT64                     qwInitializationVector;
    DRM_DWORD                      cSubSamples;
    OEM_HAL_SUBSAMPLE              rgSubSamples[MAX_SUB_SAMPLES];
} OEM_HAL_SAMPLE_METADATA;

/*
** OEM_HAL_HASH_TYPE_SHA1   : The SHA-1 hash algorithm.
**      not required to be implemented for this version of the PK.
** OEM_HAL_HASH_TYPE_SHA256 : The SHA-256 hash algorithm - 
*/
typedef enum
{
    OEM_HAL_HASH_TYPE_SHA1   = 0,
    OEM_HAL_HASH_TYPE_SHA256 = 1,
} OEM_HAL_HASH_TYPE;

/*
** OEM_HAL_SIGNATURE_SCHEME_RSASSA_PKCS1_v1_5: 
**   The RSASSA-PKCS1 v1.5 signature scheme with appendix - not required for this version.
** OEM_HAL_SIGNATURE_SCHEME_RSASSA_PSS: 
**   The RSASSA-PSS signature scheme with appendix - not required for this version.
** OEM_HAL_SIGNATURE_SCHEME_ECDSA_P256: 
**   The public-key signature/verification algorithm used in PlayReady DRM. 
*/
typedef enum
{
    OEM_HAL_SIGNATURE_SCHEME_RSASSA_PKCS1_v1_5 = 0,
    OEM_HAL_SIGNATURE_SCHEME_RSASSA_PSS        = 1,
    OEM_HAL_SIGNATURE_SCHEME_ECDSA_P256        = 2
} OEM_HAL_SIGNATURE_SCHEME;

/*
** SLK encryption type: SLK keys can be encrypted by the device private key in two different ways:
**  Asymmetrically - where a padded SLK key is encrypted as a single ECC256 crypto block
**  Symmetrically  - where the SLK key is AES encrypted using an AES key derived from the 
**  ECC256 device private key
**
** OEM_HAL_SLK_ENCRYPTION_TYPE_ASYMMETRIC       : a padded SLK key is encrypted as a single ECC256 crypto block.
** OEM_HAL_SLK_ENCRYPTION_TYPE_DERIVED_SYMMETRIC: the SLK key is AES encrypted using an AES key derived from the ECC256 device private key.
*/
typedef enum
{
    OEM_HAL_SLK_ENCRYPTION_TYPE_INVALID           = 0,
    OEM_HAL_SLK_ENCRYPTION_TYPE_ASYMMETRIC        = 1,
    OEM_HAL_SLK_ENCRYPTION_TYPE_DERIVED_SYMMETRIC = 2,
} OEM_HAL_SLK_ENCRYPTION_TYPE;

typedef enum
{
    eOEM_HAL_PUBKEY_NOT_VERIFIED = 0,
    eOEM_HAL_PUBKEY_VERIFIED     = 1,
    eOEM_HAL_PUBKEY_REVOKED      = 2
} OEM_HAL_PUBKEY_VERIFICATION_STATE;

#define DRM_AES_KEYSIZE_128_X2 32

EXIT_PK_NAMESPACE;

#endif /* __OEMHALBASIC_H__ */

