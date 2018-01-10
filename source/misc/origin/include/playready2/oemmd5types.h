/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __OEMMD5TYPES_H__
#define __OEMMD5TYPES_H__ 1

#include <drmtypes.h>

ENTER_PK_NAMESPACE;

#define MD5DIGESTLEN 16

typedef struct __tagDRM_MD5_CTX {
    DRM_DWORD awaiting_data[16];
                             /* Data awaiting full 512-bit block.       */
                             /* Length (nbit_total[0] % 512) bits.      */
                             /* Unused part of buffer (at end) is zero. */
    DRM_DWORD partial_hash[4];
                             /* Hash through last full block            */
    DRM_DWORD nbit_total[2];
                             /* Total length of message so far          */
                             /* (bits, mod 2^64)                        */
    DRM_BYTE digest[__CB_DECL(MD5DIGESTLEN)];
                             /* Actual digest after MD5Final completes  */
} DRM_MD5_CTX;

EXIT_PK_NAMESPACE;

#endif /* __OEMMD5TYPES_H__ */

