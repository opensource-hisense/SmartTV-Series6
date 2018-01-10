/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/


#ifndef __DRMLICENSE_H__
#define __DRMLICENSE_H__

#include <drmtypes.h>
#include <oemcryptoctx.h>

ENTER_PK_NAMESPACE;

#define DRM_MAX_LICENSESIZE           36864                        /* 36 * 1024 == 36K max license size */
#define MAX_DEVICE_CERT_SIZE          36864                        /* 36 * 1024 == 36K max device cert size */
#define MAX_DEVICE_CERT_TEMPLATE_SIZE ( ( MAX_DEVICE_CERT_SIZE * 6 ) / 10 )/* 60% of max devcert */

/* Constant indicating the number of times SHA has to be used to get the hash of key. */
/* This hash is used to check whether the key is good or bad. */
/* CHECKSUM_LENGTH indicates the number of bytes in final hash value to use as CHECKSUM. */
#define SHA_ITERATIONS      5
#define CHECKSUM_LENGTH     7
#define DRM_AES_CK_CHECKSUM_LENGTH 8
#define APPSEC_LEN   4
#define RIGHTS_LEN   4

#define LEGACY_KID_B64ENC_LEN   24
#define DRM_MAX_CHECKSUM        MAX( MAX( CHECKSUM_LENGTH, LEGACY_KID_B64ENC_LEN ), DRM_AES_CK_CHECKSUM_LENGTH )

typedef struct {
    PKV pk;
    DRM_BYTE appSec [__CB_DECL(APPSEC_LEN)];
    DRM_BYTE subject[__CB_DECL(SUBJ_LEN)];
} APPCERTDATA;

typedef struct {
    DRM_BYTE appcertVersion[__CB_DECL(VERSION_LEN)];
    DRM_BYTE datalen       [__CB_DECL(INT_LEN)];
    DRM_BYTE sign          [__CB_DECL(DRM_ECC160_SIGNATURE_LEN)];
    APPCERTDATA appcd;
} APPCERT;

typedef struct __tagCLIENTID
{
    DRM_BYTE version[__CB_DECL(VERSION_LEN)];
    DRM_BYTE randNum[__CB_DECL(DRM_ECC160_CIPHERTEXT_LEN)];
    PKCERT pk;
} CLIENTID;

typedef struct __tagDRM_V1Header
{
    DRM_BYTE  *pbKeyID;
    DRM_DWORD  cbKeyID;
    DRM_BYTE  *pbSecretData;
    DRM_DWORD  cbSecretData;
    DRM_BYTE  *pbURL;
    DRM_DWORD  cbURL;
    DRM_BYTE   bBuffer[1];
} DRM_V1Header;

EXIT_PK_NAMESPACE;

#endif /* __DRMLICENSE_H__ */

