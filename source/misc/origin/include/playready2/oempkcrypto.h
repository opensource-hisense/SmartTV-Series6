/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/


#ifndef __OEMPKCRYPTO_H__
#define __OEMPKCRYPTO_H__

#include <drmtypes.h>
#include <oemrsacommon.h>

ENTER_PK_NAMESPACE;

/*
** Enum: Supported asymmetric crypto algorithms for sign/verify and encrypt/decrypt
*/
typedef enum __tagDRM_PKCRYPTO_SUPPORTED_ALGORITHMS
{
    eDRM_ECC_P160  = 1,
    eDRM_ECC_P256  = 2,
    eDRM_RSA       = 3
} DRM_PKCRYPTO_SUPPORTED_ALGORITHMS;


DRM_API DRM_RESULT DRM_CALL DRM_PK_GenKeyPair(
    __in_opt                            DRM_VOID                             *f_pContext,
    __in                                DRM_PKCRYPTO_SUPPORTED_ALGORITHMS     f_eAlgorithm,
    __in                                DRM_RSA_SUPPORTED_KEY_LENGTHS_2048BIT f_eRSAKeyLength,
    __inout_ecount( 1 )                 DRM_DWORD                            *f_pcbPublicKey,
    __out_bcount( *f_pcbPublicKey )     DRM_BYTE                             *f_pbPublicKey,
    __inout_ecount( 1 )                 DRM_DWORD                            *f_pcbPrivateKey,
    __out_bcount( *f_pcbPrivateKey )    DRM_BYTE                             *f_pbPrivateKey );


DRM_API DRM_RESULT DRM_CALL DRM_PK_Encrypt(
    __in_opt                            DRM_VOID                           *f_pOEMContext,
    __in_opt                            DRM_VOID                           *f_pContext,
    __in                                DRM_PKCRYPTO_SUPPORTED_ALGORITHMS   f_eAlgorithm,
    __in                                DRM_DWORD                           f_cbPublicKey,
    __in_bcount( f_cbPublicKey )  const DRM_BYTE                           *f_pbPublicKey,
    __in                                DRM_DWORD                           f_cbPlainText,
    __in_bcount( f_cbPlainText )  const DRM_BYTE                           *f_pbPlainText,
    __inout_ecount( 1 )                 DRM_DWORD                          *f_pcbCipherText,
    __out_bcount( *f_pcbCipherText )    DRM_BYTE                           *f_pbCipherText );


DRM_API DRM_RESULT DRM_CALL DRM_PK_Decrypt(
    __in_opt                            DRM_VOID                           *f_pContext,
    __in                                DRM_PKCRYPTO_SUPPORTED_ALGORITHMS   f_eAlgorithm,
    __in                                DRM_DWORD                           f_cbPrivateKey,
    __in_bcount( f_cbPrivateKey ) const DRM_BYTE                           *f_pbPrivateKey,
    __in                                DRM_DWORD                           f_cbCipherText,
    __in_bcount( f_cbCipherText ) const DRM_BYTE                           *f_pbCipherText,
    __inout_ecount( 1 )                 DRM_DWORD                          *f_pcbPlainText,
    __out_bcount( *f_pcbPlainText )     DRM_BYTE                           *f_pbPlainText );


DRM_API DRM_RESULT DRM_CALL DRM_PK_Sign(
    __in_opt                            DRM_VOID                           *f_pContext,
    __in                                DRM_PKCRYPTO_SUPPORTED_ALGORITHMS   f_eAlgorithm,
    __in                                DRM_DWORD                           f_cbPrivateKey,
    __in_bcount( f_cbPrivateKey ) const DRM_BYTE                           *f_pbPrivateKey,
    __in                                DRM_DWORD                           f_cbData,
    __in_bcount( f_cbData )       const DRM_BYTE                           *f_pbData,
    __inout_ecount( 1 )                 DRM_DWORD                          *f_pcbSignature,
    __out_bcount( *f_pcbSignature )     DRM_BYTE                           *f_pbSignature );


DRM_API DRM_RESULT DRM_CALL DRM_PK_Verify(
    __in_opt                            DRM_VOID                           *f_pContext,
    __in                                DRM_PKCRYPTO_SUPPORTED_ALGORITHMS   f_eAlgorithm,
    __in                                DRM_DWORD                           f_cbPublicKey,
    __in_bcount( f_cbPublicKey )  const DRM_BYTE                           *f_pbPublicKey,
    __in                                DRM_DWORD                           f_cbData,
    __in_bcount( f_cbData )       const DRM_BYTE                           *f_pbData,
    __in                                DRM_DWORD                           f_cbSignature,
    __in_bcount( f_cbSignature )  const DRM_BYTE                           *f_pbSignature ) DRM_NO_INLINE_ATTRIBUTE;


EXIT_PK_NAMESPACE;

#endif /* __OEMPKCRYPTO_H__ */

