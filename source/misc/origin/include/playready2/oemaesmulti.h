/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/


#ifndef __OEMAESMULTI_H__
#define __OEMAESMULTI_H__

#include <oemaeskey.h>

ENTER_PK_NAMESPACE;

DRM_API DRM_RESULT DRM_CALL Oem_Aes_CtrProcessData(
    __in_ecount( 1 )            const DRM_AES_KEY                  *f_pKey,
    __inout_bcount( f_cbData )        DRM_BYTE                     *f_pbData,
    __in                              DRM_DWORD                     f_cbData,
    __inout_ecount( 1 )               DRM_AES_COUNTER_MODE_CONTEXT *f_pCtrContext );

DRM_API DRM_RESULT DRM_CALL Oem_Aes_CbcEncryptData(
    __in_ecount( 1 )                const DRM_AES_KEY *f_pKey,
    __inout_bcount( f_cbData )            DRM_BYTE    *f_pbData,
    __in                                  DRM_DWORD    f_cbData,
    __in_bcount( DRM_AES_BLOCKLEN ) const DRM_BYTE     f_rgbIV[__CB_DECL( DRM_AES_BLOCKLEN )] );

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL Oem_Aes_CbcDecryptData(
    __in_ecount( 1 )                const DRM_AES_KEY *f_pKey,
    __inout_bcount( f_cbData )            DRM_BYTE    *f_pbData,
    __in                                  DRM_DWORD    f_cbData,
    __in_bcount( DRM_AES_BLOCKLEN ) const DRM_BYTE     f_rgbIV[__CB_DECL( DRM_AES_BLOCKLEN )] ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_RESULT DRM_CALL Oem_Aes_EcbEncryptData(
    __in_ecount( 1 )                const DRM_AES_KEY *f_pKey,
    __inout_bcount( f_cbData )            DRM_BYTE    *f_pbData,
    __in                                  DRM_DWORD    f_cbData );

DRM_API DRM_RESULT DRM_CALL Oem_Aes_EcbDecryptData(
    __in_ecount( 1 )                const DRM_AES_KEY *f_pKey,
    __inout_bcount( f_cbData )            DRM_BYTE    *f_pbData,
    __in                                  DRM_DWORD    f_cbData );

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL Oem_Omac1_Sign(
    __in_ecount( 1 )                       const DRM_AES_KEY *f_pKey,
    __in_bcount( f_ibData + f_cbData )     const DRM_BYTE    *f_pbData,
    __in                                   DRM_DWORD    f_ibData,
    __in                                   DRM_DWORD    f_cbData,
    __out_bcount( DRM_AES_BLOCKLEN )       DRM_BYTE     f_rgbTag[__CB_DECL( DRM_AES_BLOCKLEN )] ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_RESULT DRM_CALL Oem_Omac1_Verify(
    __in_ecount( 1 )                const DRM_AES_KEY *f_pKey,
    __in_bcount(f_ibData+f_cbData)  const DRM_BYTE    *f_pbData,
    __in                                  DRM_DWORD    f_ibData,
    __in                                  DRM_DWORD    f_cbData,
    __in_bcount(f_ibSignature+DRM_AES_BLOCKLEN) const DRM_BYTE *f_pbSignature,
    __in                                  DRM_DWORD    f_ibSignature );

EXIT_PK_NAMESPACE;

#endif /* __OEMAESMULTI_H__ */

