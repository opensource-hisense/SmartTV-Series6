/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/


#ifndef __DRMREVOCATIONTYPES_H__
#define __DRMREVOCATIONTYPES_H__

#include <oemsha1.h>
#include <drmtypes.h>
#include <drmrevocationenum.h>

ENTER_PK_NAMESPACE;

typedef struct __tagDRM_RLVI_RECORD
{
    DRM_GUID   listID;
    DRM_UINT64 qwVersion;
} DRM_RLVI_RECORD;

typedef struct __tagDRM_RLVI_HEAD
{
    DRM_DWORD   dwID;
    DRM_DWORD   cbSignedBytes;
    DRM_BYTE    bFormatVersion;
    DRM_BYTE    bReserved[3];
    DRM_DWORD   dwRIV;
    DRMFILETIME ftIssuedTime;
    DRM_DWORD   dwRecordCount;
} DRM_RLVI_HEAD;

typedef struct __tagDRM_RLVI_SIGNATURE
{
    DRM_BYTE  bSignatureType;
    DRM_DWORD ibSignature;
    DRM_DWORD cbSignature;
} DRM_RLVI_SIGNATURE;

typedef struct __tagDRM_RLVI_CERTCHAIN
{
    DRM_DWORD  cbCertChain;
    DRM_DWORD  ibCertChain;
} DRM_RLVI_CERTCHAIN;

typedef struct __tagDRM_RLVI
{
    DRM_RLVI_HEAD       head;
    DRM_DWORD           ibEntries;    /* Byte offset to the entries in the revocation info */
    DRM_RLVI_SIGNATURE  signature;
    DRM_RLVI_CERTCHAIN  certchain;
} DRM_RLVI;

typedef struct
{    DRM_GUID guidRevocationList;
    DRM_BYTE *pbRevocationList;
    DRM_DWORD cbRevocationList;
} DRM_RVK_LIST;

#define RLVI_MAGIC_NUM_V1   ((DRM_DWORD) 0x524C5649) /* 'RLVI' */
#define RLVI_MAGIC_NUM_V2   ((DRM_DWORD) 0x524C5632) /* 'RLV2' */

#define RLVI_FORMAT_VERSION_V1 ((DRM_BYTE) 1)
#define RLVI_FORMAT_VERSION_V2 ((DRM_BYTE) 2)
#define RLVI_SIGNATURE_TYPE_1 ((DRM_BYTE) 1)
#define RLVI_SIGNATURE_SIZE_1 ((DRM_DWORD) 128)
#define RLVI_SIGNATURE_TYPE_2 ((DRM_BYTE) 2)
#define RLVI_SIGNATURE_SIZE_2 ((DRM_DWORD) 256)

#define DRM_NO_PREVIOUS_CRL 0xFFFFFFFF

/*
** CRL defines
*/
#define WMDRMNET_CRL_ENTRY_SIZE                     DRM_SHA1_DIGEST_LEN
#define WMDRMNET_CRL_SIGNATURE_TYPE_RSA_SHA1        2
#define WMDRMNET_CRL_SIGNATURE_LEN_RSA_SHA1         128

typedef struct
{
    DRM_BYTE val[ __CB_DECL( WMDRMNET_CRL_ENTRY_SIZE ) ];

} WMDRMNET_CRL_ENTRY;

typedef DRM_BYTE DRM_RevocationEntry[32];

EXIT_PK_NAMESPACE;

#endif /* __DRMREVOCATIONTYPES_H__ */
