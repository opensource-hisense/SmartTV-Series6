/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

/*
**  oemaescommon.h
**
**  Contains common definitions used by OEM AES implementations as well as
**  AES API functions.
**
*/


#ifndef __OEMAESCOMMON_H__
#define __OEMAESCOMMON_H__

#include <drmtypes.h>
#include <drmpragmas.h>

ENTER_PK_NAMESPACE;

/*
** AES Key Sizes
*/
#define DRM_AES_KEYSIZE_128   16   /* Size ( in bytes ) of a 128 bit key */
#define DRM_AES_KEYSIZE_192   24   /* Size ( in bytes ) of a 192 bit key */
#define DRM_AES_KEYSIZE_256   32   /* Size ( in bytes ) of a 256 bit key */
#define DRM_AES_MAXKEYSIZE  DRM_AES_KEYSIZE_256

/*
** Round counts corresponding to key sizes
*/
#define DRM_AES_ROUNDS_128    10
#define DRM_AES_ROUNDS_192    12
#define DRM_AES_ROUNDS_256    14
#define DRM_AES_MAXROUNDS   DRM_AES_ROUNDS_256

#define DRM_AES_BLOCKLEN    DRM_AES_KEYSIZE_128 /* Size ( in bytes ) of a single encrypted/decrypted block */
#define DRM_AES_ROUNDS      DRM_AES_ROUNDS_128

/*
** Supported cipher modes for AES encryption/decryption
*/
typedef enum
{
    eDRM_AES_CTR_MODE  = 1,
    eDRM_AES_ECB_MODE  = 2,
    eDRM_AES_CBC_MODE  = 3
} DRM_AES_SUPPORTED_MODES;

typedef struct
{
    DRM_UINT64  qwInitializationVector;
    DRM_UINT64  qwBlockOffset;
    DRM_BYTE    bByteOffset;  /* Byte offset within the current block */
} DRM_AES_COUNTER_MODE_CONTEXT;

EXIT_PK_NAMESPACE;

#endif /* __OEMAESCOMMON_H__ */

