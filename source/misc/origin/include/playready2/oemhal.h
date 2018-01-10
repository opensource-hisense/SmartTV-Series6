/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

/******************************************************************************
**
** This file declares the interface between the DRM blackbox and the secure crypto core.
** If the device supports a secure crypto core:
**      This file should define the interface between the unsecure core
**      (where the rest of DRM code runs) and the secure crypto core.
**      OEMs will need to create whatever OEM-hardware-specific layering is
**      required for this interface to become that boundary.
** If the device does not support a secure crypto core:
**      OEMs should not need to change this file in any way (except to get it to compile properly).
**
*******************************************************************************
*/

#ifndef __OEMHAL_H__
#define __OEMHAL_H__

#include <oemhalbasic.h>
#include <oemcommon.h>
#include <oemcryptoctx.h>

ENTER_PK_NAMESPACE;

DRM_API DRM_NO_INLINE DRM_BOOL DRM_CALL OEM_HAL_IsHalDevCertValidationSupported(DRM_VOID) DRM_NO_INLINE_ATTRIBUTE;
DRM_API DRM_NO_INLINE DRM_BOOL DRM_CALL OEM_HAL_IsHalDevCertValidationUnsupported(DRM_VOID) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_RESULT DRM_CALL Oem_Hal_AllocateRegister(
    __in              OEM_HAL_KEY_TYPE            f_eKeyType,
    __out_ecount( 1 ) OEM_HAL_KEY_REGISTER_INDEX *f_pKeyRegisterIndex );

DRM_API DRM_RESULT DRM_CALL Oem_Hal_FreeRegister(
    __in OEM_HAL_KEY_TYPE           f_eKeyType,
    __in OEM_HAL_KEY_REGISTER_INDEX f_keyRegisterIndex );

DRM_API DRM_RESULT DRM_CALL Oem_Hal_RegisterCount(
    __in            OEM_HAL_KEY_TYPE     f_eKeyType,
    __out_ecount(1) DRM_DWORD           *f_pdwTotalRegisters,
    __out_ecount(1) DRM_DWORD           *f_pdwAllocatedRegisters );

DRM_API DRM_RESULT DRM_CALL Oem_Hal_GetPreloadedIndex(
    __in                           DRM_VOID                   *f_pOEMContext,
    __in                           OEM_HAL_KEY_TYPE            f_eKeyType,
    __in_bcount( f_cbKeyId ) const DRM_BYTE                   *f_pbKeyId,
    __in                           DRM_DWORD                   f_cbKeyId,
    __out_ecount( 1 )              OEM_HAL_KEY_REGISTER_INDEX *f_pIndexKey );

DRM_API DRM_RESULT DRM_CALL Oem_Hal_Initialize();

DRM_API DRM_RESULT DRM_CALL Oem_Hal_Deinitialize();

DRM_API DRM_RESULT DRM_CALL Oem_Hal_VerifyMessageSignature(
    __in_bcount( f_cbMessage )   const DRM_BYTE                  *f_pbMessage,
    __in                               DRM_DWORD                  f_cbMessage,
    __in_bcount( f_cbSignature ) const DRM_BYTE                  *f_pbSignature,
    __in                               DRM_DWORD                  f_cbSignature,
    __in                               OEM_HAL_HASH_TYPE          f_eHashType,
    __in                               OEM_HAL_SIGNATURE_SCHEME   f_eSignatureScheme,
    __in                               OEM_HAL_KEY_REGISTER_INDEX f_indexIntegrityKey );

DRM_API DRM_RESULT DRM_CALL Oem_Hal_SignWithPrivateKey(
    __in                                DRM_VOID                  *f_pOEMContext,
    __inout_ecount_opt( 1 )             DRM_CRYPTO_CONTEXT        *f_pCryptoContext,
    __in_bcount( f_cbMessage )    const DRM_BYTE                  *f_pbMessage,
    __in                                DRM_DWORD                  f_cbMessage,
    __out_bcount_opt( *f_pcbSignature ) DRM_BYTE                  *f_pbSignature,
    __inout                             DRM_DWORD                 *f_pcbSignature,
    __in                                OEM_HAL_HASH_TYPE          f_eHashType,
    __in                                OEM_HAL_SIGNATURE_SCHEME   f_eSignatureScheme,
    __in                                OEM_HAL_KEY_TYPE           f_eKeyType,
    __in                                OEM_HAL_KEY_REGISTER_INDEX f_indexIntegrityKey );

DRM_API DRM_RESULT DRM_CALL Oem_Hal_VerifyOMAC1Signature(
    __in_bcount( f_cbData )      const DRM_BYTE                   *f_pbData,
    __in                               DRM_DWORD                   f_cbData,
    __in_bcount( f_cbSignature ) const DRM_BYTE                   *f_pbSignature,
    __in                               DRM_DWORD                   f_cbSignature,
    __in                               OEM_HAL_KEY_TYPE            f_eKeyType,
    __in                               OEM_HAL_KEY_REGISTER_INDEX  f_indexKey );

DRM_API DRM_RESULT DRM_CALL Oem_Hal_CreateOMAC1Signature(
    __in_bcount( f_cbData )        const DRM_BYTE                   *f_pbData,
    __in                                 DRM_DWORD                   f_cbData,
    __out_bcount_opt( *f_pcbSignature )  DRM_BYTE                   *f_pbSignature,
    __inout                              DRM_DWORD                  *f_pcbSignature,
    __in                                 OEM_HAL_KEY_TYPE            f_eKeyType,
    __in                                 OEM_HAL_KEY_REGISTER_INDEX  f_indexKey );

DRM_API DRM_RESULT DRM_CALL Oem_Hal_EncryptDataBlock(
    __in_bcount( f_cbData )             const DRM_BYTE                   *f_pbBlock,
    __in                                      DRM_DWORD                   f_cbBlock,
    __out_bcount_opt( *f_pcbEncryptedBlock )  DRM_BYTE                   *f_pbEncryptedBlock,
    __inout                                   DRM_DWORD                  *f_pcbEncryptedBlock,
    __in                                      OEM_HAL_KEY_TYPE            f_eKeyType,
    __in                                      OEM_HAL_KEY_REGISTER_INDEX  f_indexMessageEncryptKey );

DRM_API DRM_BOOL DRM_CALL Oem_Hal_IsDevelopmentPlatform();

DRM_API DRM_RESULT DRM_CALL Oem_Hal_UnwrapKey(
    __inout_ecount_opt( 1 )                    DRM_CRYPTO_CONTEXT         *f_pCryptoContext,
    __in                                       OEM_HAL_KEY_TYPE            f_eKeyType,
    __in                                       OEM_HAL_KEY_REGISTER_INDEX  f_indexKey,
    __in                                       OEM_HAL_KEY_TYPE            f_eWrappingKeyType,
    __in                                       OEM_HAL_KEY_REGISTER_INDEX  f_indexWrappingKey,
    __in_bcount( f_cbWrappedKeyData )    const DRM_BYTE                   *f_pbWrappedKeyData,
    __in                                       DRM_DWORD                   f_cbWrappedKeyData,
    __in_bcount_opt( f_cbParameterData ) const DRM_BYTE                   *f_pbParameterData,
    __in                                       DRM_DWORD                   f_cbParameterData );

DRM_API DRM_RESULT DRM_CALL Oem_Hal_WrapKey(
    __in                                 DRM_VOID                   *f_pOEMContext,
    __inout_ecount_opt( 1 )              DRM_CRYPTO_CONTEXT         *f_pCryptoContext,
    __in                                 OEM_HAL_KEY_TYPE            f_eKeyType,
    __in                                 OEM_HAL_KEY_REGISTER_INDEX  f_indexKey,
    __in                                 OEM_HAL_KEY_TYPE            f_eWrappingKeyType,
    __in                                 OEM_HAL_KEY_REGISTER_INDEX  f_indexWrappingKey,
    __out_bcount_opt( *f_pcbWrappedKey ) DRM_BYTE                   *f_pbWrappedKey,
    __inout_ecount(1)                    DRM_DWORD                  *f_pcbWrappedKey );

DRM_API DRM_RESULT DRM_CALL Oem_Hal_GenerateKey(
    __in                    DRM_VOID                  *f_pOEMContext,
    __inout_ecount_opt( 1 ) DRM_CRYPTO_CONTEXT        *f_pCryptoContext,
    __in                    OEM_HAL_KEY_TYPE           f_eKeyType,
    __in                    OEM_HAL_KEY_REGISTER_INDEX f_indexKey,
    __in                    DRM_DWORD                  f_dwRequestedSecurityLevel );

DRM_API DRM_RESULT DRM_CALL Oem_Hal_DecryptContent(
    __inout_bcount( f_cbData ) DRM_BYTE                   *f_pbData,
    __in                       DRM_DWORD                   f_cbData,
    __in                       OEM_HAL_KEY_TYPE            f_eKeyType,
    __in                       OEM_HAL_KEY_REGISTER_INDEX  f_indexContentKey,
    __in                       DRM_UINT64                  f_qwInitializationVector,
    __in                       DRM_UINT64                  f_qwSampleByteOffset );

DRM_API DRM_RESULT DRM_CALL Oem_Hal_DecryptContentOpaque(
    __in                       OEM_OPAQUE_BUFFER_HANDLE    f_hInBuf,
    __in                       OEM_OPAQUE_BUFFER_HANDLE    f_hOutBuf,
    __in                       DRM_DWORD                   f_cbData,
    __in                       OEM_HAL_KEY_TYPE            f_eKeyType,
    __in                       OEM_HAL_KEY_REGISTER_INDEX  f_indexContentKey,
    __in                       DRM_UINT64                  f_qwInitializationVector,
    __in                       DRM_UINT64                  f_qwSampleByteOffset );

DRM_API DRM_RESULT DRM_CALL Oem_Hal_CreateSampleEncryptionContext(
    __in            OEM_HAL_KEY_TYPE                f_eKeyType,
    __in            OEM_HAL_KEY_REGISTER_INDEX      f_indexKey,
    __in            OEM_HAL_SAMPLE_ENCRYPTION_MODE  f_eSampleEncryptionMode,
    __out_ecount(1) OEM_ENCRYPTION_HANDLE          *f_phEncryptionContext );

DRM_API DRM_RESULT DRM_CALL Oem_Hal_EncryptSampleData(
    __in                           DRM_VOID                 *f_pOEMContext,
    __in                           OEM_ENCRYPTION_HANDLE     f_hEncryptionContext,
    __out_ecount_opt(1)            DRM_UINT64               *f_pqwInitializationVector,
    __out_ecount_opt(1)            OEM_HAL_SAMPLE_METADATA  *f_pMetadata,
    __in_opt                       OEM_OPAQUE_BUFFER_HANDLE  f_hInBuf,
    __in_opt                       OEM_OPAQUE_BUFFER_HANDLE  f_hOutBuf,
    __in                           DRM_DWORD                 f_cbData,
    __inout_bcount_opt( f_cbData ) DRM_BYTE                 *f_pbData );

DRM_API DRM_RESULT DRM_CALL Oem_Hal_QuerySampleMetadata(
    __in            OEM_ENCRYPTION_HANDLE    f_hEncryptionContext,
    __out_ecount(1) OEM_HAL_SAMPLE_METADATA *f_pMetadata );

DRM_API DRM_RESULT DRM_CALL Oem_Hal_DestroySampleEncryptionContext(
    __in OEM_ENCRYPTION_HANDLE f_hEncryptionContext );

DRM_API DRM_RESULT DRM_CALL Oem_Hal_LoadPlayReadyRevocationInfo(
    __inout_ecount_opt( 1 )                 DRM_CRYPTO_CONTEXT         *f_pCryptoContext,
    __in_bcount( f_cbRevocationInfo ) const DRM_BYTE                   *f_pbRevocationInfo,
    __in                                    DRM_DWORD                   f_cbRevocationInfo,
    __in                                    OEM_HAL_KEY_REGISTER_INDEX  f_indexSigningKey );

DRM_API DRM_RESULT DRM_CALL Oem_Hal_LoadPlayReadyCrl(
    __inout_ecount_opt( 1 )      DRM_CRYPTO_CONTEXT         *f_pCryptoContext,
    __in_bcount( f_cbCRL ) const DRM_BYTE                   *f_pbCRL,
    __in                         DRM_DWORD                   f_cbCRL,
    __in                         OEM_HAL_KEY_REGISTER_INDEX  f_indexSigningKey );

EXIT_PK_NAMESPACE;

#endif /* __OEMHAL_H__ */

