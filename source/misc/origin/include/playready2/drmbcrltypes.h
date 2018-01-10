/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRMBCRLTYPES_H__
#define __DRMBCRLTYPES_H__

#include <drmrevocationtypes.h>
#include <oemeccp256.h>

ENTER_PK_NAMESPACE;

#define PLAYREADY_DRM_BCRL_SIGNATURE_TYPE 1

typedef DRM_BYTE DRM_CrlIdentifier[16];

typedef struct __tagDRM_BCRL
{
    DRM_CrlIdentifier    Identifier;
    DRM_DWORD            dwVersion;
    DRM_DWORD            cRevocationEntries;
    DRM_RevocationEntry *Entries;
} DRM_BCRL;

/*
** The following byte value should be equal to the largest signature length supported
*/
#define DRM_BCRL_MAX_SIGNATURE_DATA_LENGTH   SIZEOF( SIGNATURE_P256 )

typedef struct _tagDrmBCrlSignatureData
{
    DRM_BYTE    type;
    DRM_WORD    cb;
    DRM_BYTE    rgb[ __CB_DECL( DRM_BCRL_MAX_SIGNATURE_DATA_LENGTH ) ];
} DRM_BCRL_SIGNATURE_DATA;

typedef struct __tagDRM_BCRL_Signed
{
    DRM_BCRL                 Crl;
    DRM_BCRL_SIGNATURE_DATA  Signature;
    DRM_BYTE                *pbCertificateChain;
    DRM_DWORD                cbCertificateChain;
} DRM_BCRL_Signed;

EXIT_PK_NAMESPACE;

#endif /* __DRMBCRLTYPES_H__ */


