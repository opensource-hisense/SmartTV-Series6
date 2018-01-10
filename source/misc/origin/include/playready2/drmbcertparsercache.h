/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRMBCERTPARSERCACHE_H__
#define __DRMBCERTPARSERCACHE_H__

#include <drmtypes.h>
#include <drmbcert.h>
#include <drmpragmas.h>

ENTER_PK_NAMESPACE;

typedef enum
{
    DRM_BINARY_DEVICE_CERT_KEY_SIGN         = 0,
    DRM_BINARY_DEVICE_CERT_KEY_ENCRYPT      = 1,
    DRM_BINARY_DEVICE_CERT_KEY_PRND_ENCRYPT = 2,
} eDRM_BINARY_DEVICE_CERT_KEYUSAGE;

typedef struct
{
    PUBKEY_P256       PublicKey;
DRM_OBFUS_PTR_TOP
    OEM_CRYPTO_HANDLE hPublicKey;
DRM_OBFUS_PTR_BTM
} DRM_PUBLIC_KEY_CONTEXT;

typedef struct
{
    DRM_PUBLIC_KEY_CONTEXT PublicKeyContext;
    DRM_BYTE               rgbPrivateKey[ __CB_DECL( SIZEOF( PRIVKEY_P256 ) ) ];
} DRM_BINARY_DEVICE_CERT_KEYPAIR;

typedef struct
{
    DRM_BCERT_CLIENT_ID             DeviceSerialNumber;
    DRM_DWORD                       dwGroupSecurityLevel;
    DRM_DWORD                       dwFeatureFlags;
    DRM_BINARY_DEVICE_CERT_KEYPAIR  DeviceKeySign;
    DRM_BINARY_DEVICE_CERT_KEYPAIR  DeviceKeyEncrypt;
    DRM_BOOL                        fDeviceKeyPrndEncryptSet;
DRM_OBFUS_FILL_BYTES(4)
    DRM_BINARY_DEVICE_CERT_KEYPAIR  DeviceKeyPrndEncrypt;
} DRM_BINARY_DEVICE_CERT_CACHED_VALUES;



EXIT_PK_NAMESPACE;

#endif /* __DRMBCERTPARSERCACHE_H__ */

