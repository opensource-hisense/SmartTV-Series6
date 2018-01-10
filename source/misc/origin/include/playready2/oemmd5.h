/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __OEMMD5_H__
#define __OEMMD5_H__ 1

#include <drmerr.h>
#include <oemmd5types.h>

ENTER_PK_NAMESPACE;

DRM_API DRM_VOID DRM_CALL DRM_MD5_Init(
    __inout DRM_MD5_CTX *f_contextMD5 );

DRM_API DRM_VOID DRM_CALL DRM_MD5_Update(
    __inout                     DRM_MD5_CTX *f_contextMD5,
    __in_bcount(f_cbData) const DRM_VOID    *f_rgbData,
    __in                        DRM_DWORD    f_cbData );

DRM_API DRM_VOID DRM_CALL DRM_MD5_Final(
    __inout DRM_MD5_CTX *f_contextMD5 );

EXIT_PK_NAMESPACE;

#endif /* __OEMMD5_H__ */

