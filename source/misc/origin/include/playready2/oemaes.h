/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

/*
**  oemaes.h
**
**  Contains structures and function definitions implemented in oemaes.c
**
*/

#ifndef __OEMAES_H__
#define __OEMAES_H__

#include <oemaeskey.h>
#include <oemaesimpl.h>
#include <oemaescommon.h>
#include <oemaesmulti.h>

ENTER_PK_NAMESPACE;

DRM_API DRM_RESULT DRM_CALL Oem_Aes_ZeroKey(
    __inout_ecount( 1 )                      DRM_AES_KEY  *f_pKey );

DRM_API DRM_RESULT DRM_CALL Oem_Aes_SetKey(
    __in_bcount( DRM_AES_KEYSIZE_128 ) const DRM_BYTE      f_rgbKey[__CB_DECL( DRM_AES_KEYSIZE_128 )],
    __inout_ecount( 1 )                      DRM_AES_KEY  *f_pAesKey );

DRM_API DRM_RESULT DRM_CALL Oem_Aes_EncryptOne(
    __in_ecount( 1 )                   const DRM_AES_KEY  *f_pKey,
    __inout_bcount( DRM_AES_BLOCKLEN )       DRM_BYTE      f_rgbData[__CB_DECL( DRM_AES_BLOCKLEN )] );

DRM_API DRM_RESULT DRM_CALL Oem_Aes_DecryptOne(
    __in_ecount( 1 )                   const DRM_AES_KEY  *f_pKey,
    __inout_bcount( DRM_AES_BLOCKLEN )       DRM_BYTE      f_rgbData[__CB_DECL( DRM_AES_BLOCKLEN )] ) DRM_NO_INLINE_ATTRIBUTE;

EXIT_PK_NAMESPACE;

#endif /* __OEMAES_H__ */
