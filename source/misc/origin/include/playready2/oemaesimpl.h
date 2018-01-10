/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

/*
**  oemaesimpl.h
**
**  Contains AES secret key and key table definitions used in the oem aes implementation, and
**  to create an opaque aes key structure in oemaes.h
**
*/

#ifndef __OEMAESIMPL_H__
#define __OEMAESIMPL_H__

#include <drmerr.h>
#include <oemaescommon.h>

ENTER_PK_NAMESPACE;

/*
** AES Key Table structures
*/
typedef struct
{
    DRM_DWORD   keytabenc[DRM_AES_ROUNDS_128+1][4];
    DRM_DWORD   keytabdec[DRM_AES_ROUNDS_128+1][4];
} DRM_AESTable_128;

#define DRM_AESTable          DRM_AESTable_128
#define DRM_AES_TABLESIZE     SIZEOF( DRM_AESTable )

/*
** Internal AES secret key
*/
typedef struct
{
    DRM_AESTable   AESTable;
    DRM_BYTE   rgbKey[__CB_DECL( DRM_AES_KEYSIZE_128 )];
} INTERNAL_DRM_AES_KEY;

#define DRM_AES_KEYSTRUCTSIZE  SIZEOF( INTERNAL_DRM_AES_KEY )


EXIT_PK_NAMESPACE;

#endif /* __OEMAESIMPL_H__ */
