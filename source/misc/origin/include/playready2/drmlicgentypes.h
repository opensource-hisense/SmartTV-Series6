/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRMLICGENTYPES_H_
#define __DRMLICGENTYPES_H_ 1

#include <oemaescommon.h>
#include <oemeccp256.h>

ENTER_PK_NAMESPACE;

typedef DRM_VOID *DRM_LICENSE_HANDLE;
#define DRM_LICENSE_HANDLE_INVALID   ((DRM_LICENSE_HANDLE)NULL)

#define DRM_MAX_LOCAL_LICENSE_EXPLICIT_OUTPUT_PROTECTIONS            10
#define DRM_MAX_LOCAL_LICENSE_EXPLICIT_OUTPUT_PROTECTION_CONFIG_DATA 16
#define DRM_MAX_LOCAL_LICENSE_PLAY_ENABLERS                          10
#define DRM_MAX_LOCAL_LICENSE_CACHE_TIME_IN_SECONDS                  18000   /* 5 hours */

#define DRM_LOCAL_LICENSE_MINIMUM_PROTECTION_LEVEL                   0

#define DRM_LOCAL_LICENSE_EXPIRATION_MIN_BEGIN_DATE                  0
#define DRM_LOCAL_LICENSE_INFINITE_EXPIRATION                        MAX_UNSIGNED_TYPE( DRM_DWORD )

typedef enum
{
    eDRM_LOCAL_LICENSE_LOCAL_BOUND_SIMPLE,
    eDRM_LOCAL_LICENSE_LOCAL_BOUND_ROOT,
    eDRM_LOCAL_LICENSE_LEAF,
    eDRM_LOCAL_LICENSE_REMOTE_BOUND_SIMPLE,
    eDRM_LOCAL_LICENSE_REMOTE_BOUND_ROOT
} DRM_LOCAL_LICENSE_TYPE;

typedef enum
{
    eDRM_LOCAL_LICENSE_XMR_STORE,
    eDRM_LOCAL_LICENSE_PRND_SESSION_STORE
} DRM_LOCAL_LICENSE_STORE;

typedef struct __tagDRM_LOCAL_LICENSE_EXPIRATION
{
    DRM_BOOL                                      fValid;
    DRM_DWORD                                     dwBeginDate;
    DRM_DWORD                                     dwEndDate;
} DRM_LOCAL_LICENSE_EXPIRATION;

typedef struct __tagDRM_LOCAL_LICENSE_EXPIRATION_AFTER_FIRST_PLAY
{
    DRM_BOOL                                      fValid;
    DRM_DWORD                                     dwValue;
} DRM_LOCAL_LICENSE_EXPIRATION_AFTER_FIRST_PLAY;

typedef struct __tagDRM_LOCAL_LICENSE_SOURCE_ID
{
    DRM_BOOL                                      fValid;
    DRM_DWORD                                     dwSourceId;
    DRM_BOOL                                      fRestrictedSourceId;
} DRM_LOCAL_LICENSE_SOURCE_ID;

typedef struct __tagDRM_LOCAL_LICENSE_EXPLICIT_OUTPUT_PROTECTION
{
    DRM_GUID                                      oProtectionId;
    DRM_WORD                                      cbConfigData;
    DRM_BYTE                                      rgbConfigData[ DRM_MAX_LOCAL_LICENSE_EXPLICIT_OUTPUT_PROTECTION_CONFIG_DATA];
} DRM_LOCAL_LICENSE_EXPLICIT_OUTPUT_PROTECTION;

typedef struct __tagDRM_LOCAL_LICENSE_POLICY_DESCRIPTOR
{
    DRM_WORD                                      wSecurityLevel;
    DRM_BOOL                                      fCannotPersist;
    DRM_LOCAL_LICENSE_EXPIRATION                  oExpiration;
    DRM_LOCAL_LICENSE_EXPIRATION_AFTER_FIRST_PLAY oExpirationAfterFirstPlay;
    DRM_BOOL                                      fRealTimeExpiration;
    DRM_LOCAL_LICENSE_SOURCE_ID                   oSourceId;
    DRM_WORD                                      wCompressedDigitalVideo;
    DRM_WORD                                      wUncompressedDigitalVideo;
    DRM_WORD                                      wAnalogVideo;
    DRM_WORD                                      wCompressedDigitalAudio;
    DRM_WORD                                      wUncompressedDigitalAudio;
    DRM_WORD                                      cExplicitAnalogVideoOutputProtections;
    DRM_LOCAL_LICENSE_EXPLICIT_OUTPUT_PROTECTION  rgoExplicitAnalogVideoOutputProtections[ DRM_MAX_LOCAL_LICENSE_EXPLICIT_OUTPUT_PROTECTIONS ];
    DRM_WORD                                      cExplicitDigitalAudioOoutputProtections;
    DRM_LOCAL_LICENSE_EXPLICIT_OUTPUT_PROTECTION  rgoExplicitDigitalAudioOutputProtections[ DRM_MAX_LOCAL_LICENSE_EXPLICIT_OUTPUT_PROTECTIONS ];
    DRM_WORD                                      cPlayEnablers;
    DRM_GUID                                      rgoPlayEnablers[ DRM_MAX_LOCAL_LICENSE_PLAY_ENABLERS ];
} DRM_LOCAL_LICENSE_POLICY_DESCRIPTOR;


typedef struct __tagDRM_LOCAL_LICENSE_KEY_CACHE
{
    struct __tagDRM_LOCAL_LICENSE_KEY_CACHE *poNextLicenseCache;

    DRM_KID                                  kid;
    DRM_BOOL                                 fRoot;
    DRM_BYTE                                 rgbEncryptedAESKeyPair[DRM_AES_BLOCKLEN * 2];
    DRM_BYTE                                 rgbCICKEncryptedWithPubkey[ECC_P256_CIPHERTEXT_SIZE_IN_BYTES]; /* used on root/simple license */
    DRM_BYTE                                 rgbCICKEncryptedWithROOTAESECBKey[DRM_AES_BLOCKLEN * 2];       /* used on leaf license */
    DRMFILETIME                              ftAccessTime;
} DRM_LOCAL_LICENSE_KEY_CACHE;

typedef struct __tagDRM_LOCAL_LICENSE_CONTEXT
{
    OEM_CRYPTO_HANDLE                hAESGenericKeyContent;                       /* Determined on licgen */
    OEM_CRYPTO_HANDLE                hAESGenericKeyRoot;                          /* Determined on licgen */
    DRM_LOCAL_LICENSE_KEY_CACHE     *poLicenseKeyCache;
} DRM_LOCAL_LICENSE_CONTEXT;

EXIT_PK_NAMESPACE;

#endif /* __DRMLICGENTYPES_H_ */

