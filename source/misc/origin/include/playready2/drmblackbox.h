/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRMBLACKBOX_H__
#define __DRMBLACKBOX_H__

#include <drmblackboxtypes.h>
#include <drmpragmas.h>
#include <drmlicense.h>
#include <drmdevcert.h>
#include <oemcipher.h>
#include <oemeccp256.h>
#include <oemhalbasic.h>
#include <drmxmr.h>
#include <byteorder.h>
#include <drmdomainstoretypes.h>
#include <drmkeyfile.h>
#include <drmbcertparsercache.h>

#ifdef PLAYREADY2TEE
#include <tee.h>
#endif

ENTER_PK_NAMESPACE;

/*
** Functions defining whether legacy (WMDRM) crypto keys and algorithms are supported
*/
DRM_API DRM_NO_INLINE DRM_BOOL DRM_CALL DRM_BBX_IsLegacyCryptoSupported(DRM_VOID) DRM_NO_INLINE_ATTRIBUTE;
DRM_API DRM_NO_INLINE DRM_BOOL DRM_CALL DRM_BBX_IsLegacyCryptoUnsupported(DRM_VOID) DRM_NO_INLINE_ATTRIBUTE;

/*
** Functions defining whether Symmetric License Keys (SLKs) are supported
*/
DRM_API DRM_NO_INLINE DRM_BOOL DRM_CALL DRM_BBX_IsSlkCryptoSupported(DRM_VOID) DRM_NO_INLINE_ATTRIBUTE;
DRM_API DRM_NO_INLINE DRM_BOOL DRM_CALL DRM_BBX_IsSlkCryptoUnsupported(DRM_VOID) DRM_NO_INLINE_ATTRIBUTE;

/*
** Functions defining whether OEM HAL device certificate validation is supported
*/
DRM_API DRM_NO_INLINE DRM_BOOL DRM_CALL DRM_BBX_IsHalDevCertValidationSupported(DRM_VOID) DRM_NO_INLINE_ATTRIBUTE;
DRM_API DRM_NO_INLINE DRM_BOOL DRM_CALL DRM_BBX_IsHalDevCertValidationUnsupported(DRM_VOID) DRM_NO_INLINE_ATTRIBUTE;

/*
** Function defining whether crypto handle caching in black box HAL is supported.
*/
DRM_API DRM_NO_INLINE DRM_BOOL DRM_CALL DRM_BBX_IsHandleCachingSupported(DRM_VOID) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_RESULT DRM_CALL DRM_BBX_Initialize(
    __in_opt             DRM_VOID           *f_pOEMContext,
    __inout_ecount( 1 )  DRM_BB_CONTEXT     *f_pcontextBBX );

DRM_API DRM_RESULT DRM_CALL DRM_BBX_TestDeviceKeyPair(
    __inout_ecount( 1 )  DRM_BB_CONTEXT     *f_pcontextBBX );

DRM_API DRM_RESULT DRM_CALL DRM_BBX_GetClientId(
    __out_ecount( 1 )    CLIENTID          *f_pClientId,
    __inout_ecount( 1 )  DRM_BB_CONTEXT    *f_pcontextBBX );

DRM_API DRM_RESULT DRM_CALL DRM_BBX_Shutdown(
    __inout_ecount( 1 )  DRM_BB_CONTEXT     *f_pcontextBBX );

DRM_API DRM_BB_KEYHANDLE_CALLBACKS* DRM_CALL DRM_BBX_GetKeyHandleCallbacks(
    __inout_ecount( 1 )  DRM_BB_CONTEXT *f_pcontextBBX );

DRM_API DRM_BOOL DRM_CALL DRM_BBX_CanBind(
    __in_ecount( f_dwChainLength ) const DRM_BINDING_INFO *f_pBindingInfo,
    __in                                 DRM_DWORD         f_dwChainLength,
    __inout_ecount( 1 )                  DRM_BB_CONTEXT   *f_pcontextBBX,
    __out_opt                            DRM_RESULT       *f_pDr );

PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_PARAM_25004, "Prefast Noise: DRM_BB_CONTEXT should never be const");
DRM_API DRM_RESULT DRM_CALL DRM_BBX_HashValue(
    __in_bcount( f_cbValue )  const     DRM_BYTE       *f_pbValue,
    __in                                DRM_DWORD       f_cbValue,
    __in_bcount( DRM_SHA1_DIGEST_LEN )  DRM_BYTE        f_rgbHashValue[DRM_SHA1_DIGEST_LEN],
    __inout_ecount( 1 )                 DRM_BB_CONTEXT *f_pcontextBBX );
PREFAST_POP /* __WARNING_NONCONST_PARAM_25004 */

DRM_API DRM_BOOL DRM_CALL DRM_BBX_DecryptLicense(
    __inout_bcount( f_cbEncryptedLicense )   DRM_BYTE       *f_pbEncryptedLicense,
    __in                                     DRM_DWORD       f_cbEncryptedLicense,
    __out_bcount_opt( f_cbEncryptedLicense - DRM_ECC160_CIPHERTEXT_LEN )
                                             DRM_BYTE       *f_pbLicense,
    __inout_ecount( 1 )                      DRM_BB_CONTEXT *f_pcontextBBX,
    __in_opt                           const PUBKEY         *f_pPubKey  );

DRM_API DRM_RESULT DRM_CALL DRM_BBX_CipherKeySetup(
    __in_ecount( f_dwChainLength ) const DRM_BINDING_INFO    *f_pBindingInfo,
    __in                                 DRM_DWORD            f_dwChainLength,
    __out_ecount( 1 )                    DRM_CIPHER_CONTEXT  *f_pCipherContext,
    __inout_ecount( 1 )                  DRM_BB_CONTEXT      *f_pcontextBBX );

PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_PARAM_25004, "Prefast Noise: DRM_CIPHER_CONTEXT* should not be const.");
DRM_API DRM_RESULT DRM_CALL DRM_BBX_CPHR_InitDecrypt(
    __inout_ecount( 1 )                                                DRM_CIPHER_CONTEXT *f_pCipherContext,
    __in_bcount_opt( MIN(DRM_CPHR_CB_FOR_INITDECRYPT,f_cbData) ) const DRM_BYTE           *f_pbLast15,
    __in                                                               DRM_DWORD           f_cbData );
PREFAST_POP /* __WARNING_NONCONST_PARAM_25004 */

PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_PARAM_25004, "Prefast Noise: DRM_AES_COUNTER_MODE_CONTEXT* and DRM_CIPHER_CONTEXT* should not be const.");
DRM_API DRM_RESULT DRM_CALL DRM_BBX_CPHR_Decrypt(
    __in_ecount( 1 )            DRM_CIPHER_CONTEXT           *f_pCipherContext,
    __inout_opt                 DRM_AES_COUNTER_MODE_CONTEXT *f_pCtrContext,
    __in                        DRM_DWORD                     f_cbData,
    __inout_bcount( f_cbData )  DRM_BYTE                     *f_pbData );

DRM_API DRM_RESULT DRM_CALL DRM_BBX_CPHR_DecryptOpaque(
    __in_ecount( 1 )            DRM_CIPHER_CONTEXT           *f_pCipherContext,
    __inout                     DRM_AES_COUNTER_MODE_CONTEXT *f_pCtrContext,
    __in                        OEM_OPAQUE_BUFFER_HANDLE      f_hInBuf,
    __in                        OEM_OPAQUE_BUFFER_HANDLE      f_hOutBuf,
    __in                        DRM_DWORD                     f_cbData );
PREFAST_POP /* __WARNING_NONCONST_PARAM_25004 */

DRM_API DRM_VOID DRM_CALL DRM_BBX_CPHR_Uninitialize(
    __inout_ecount(1) DRM_CIPHER_CONTEXT *f_pContext );

DRM_API DRM_RESULT DRM_CALL DRM_BBX_CPHR_Duplicate(
    __inout_ecount(1) DRM_CIPHER_CONTEXT *f_pContext,
    __out_ecount(1)   DRM_CIPHER_CONTEXT *f_pDuplicateContext );

DRM_API DRM_RESULT DRM_CALL DRM_BBX_CPHR_InitWithKeyHandle(
    __inout_ecount( 1 )                DRM_BB_CONTEXT        *f_pcontextBBX,
    __out_ecount(1)                    DRM_CIPHER_CONTEXT    *f_pContext,
    __in                               DRM_SUPPORTED_CIPHERS  f_eCipherType,
    __in                               OEM_CRYPTO_HANDLE      f_hContKey );

DRM_API DRM_RESULT DRM_CALL DRM_BBX_SignData(
    __inout_ecount( 1 )                      DRM_BB_CONTEXT *f_pcontextBBX,
    __in_bcount( f_cbData )  const           DRM_BYTE       *f_pbData,
    __in                                     DRM_DWORD       f_cbData,
    __in                                     DRM_DWORD       f_ePrivKeyType,
    __out_bcount( DRM_ECC160_SIGNATURE_LEN ) DRM_BYTE        f_rgbSignature[DRM_ECC160_SIGNATURE_LEN] );

DRM_API DRM_RESULT DRM_CALL DRM_BBX_SymmetricSign(
    __inout_ecount( 1 )                    DRM_BB_CONTEXT *f_pcontextBBX,
    __in_bcount( f_cbData )  const         DRM_BYTE       *f_pbData,
    __in                                   DRM_DWORD       f_cbData,
    __in_bcount_opt( f_cbExtraData ) const DRM_BYTE       *f_pbExtraData,
    __in                                   DRM_DWORD       f_cbExtraData,
    __out_bcount( DRM_SHA1_DIGEST_LEN )    DRM_BYTE        f_rgbSymSig[DRM_SHA1_DIGEST_LEN] );

DRM_API DRM_RESULT DRM_CALL DRM_BBX_SymmetricVerify(
    __inout_ecount( 1 )                      DRM_BB_CONTEXT *f_pcontextBBX,
    __in_opt                           const PUBKEY         *f_pPubKey,
    __in_bcount( f_cbData )            const DRM_BYTE       *f_pbData,
    __in                                     DRM_DWORD       f_cbData,
    __in_bcount_opt( f_cbExtraData )   const DRM_BYTE       *f_pbExtraData,
    __in                                     DRM_DWORD       f_cbExtraData,
    __in_opt                           const DRM_SLK        *f_pslk,
    __in_bcount( DRM_SHA1_DIGEST_LEN ) const DRM_BYTE        f_rgbSymSig[DRM_SHA1_DIGEST_LEN] );

DRM_API DRM_RESULT DRM_CALL DRM_BBX_AsymmetricToSymmetricKeyXML(
    __inout_ecount( 1 )      DRM_BB_CONTEXT       *f_pcontextBBX,
    __inout_ecount_opt( 1 )  DRM_BINDING_INFO     *f_pbindinfo,
    __out_ecount( 1 )        DRM_DWORD            *f_pcbSymmKey );

DRM_API DRM_RESULT DRM_CALL DRM_BBX_AsymmetricToSymmetricKeyXMR(
    __inout_ecount( 1 )               DRM_BB_CONTEXT                *f_pcontextBBX,
    __inout_ecount_opt( 1 )           DRM_BINDING_INFO              *f_pbindinfo,
    __inout_bcount( f_cbLicense )     DRM_BYTE                      *f_pbLicense,
    __in                              DRM_DWORD                      f_cbLicense,
    __inout_ecount( 1 )               DRM_DWORD                     *f_pcbLicenseUsed,
    __inout_ecount( 1 )               DRM_STACK_ALLOCATOR_CONTEXT   *f_pStack,
    __out_ecount( 1 )                 DRM_DWORD                     *f_pcbSymmKey );

DRM_API DRM_RESULT DRM_CALL DRM_BBX_RebindSymmetricKeyXML(
    __inout         DRM_BB_CONTEXT       *f_pcontextBBX,
    __in      const DRM_SLK              *f_pslk,
    __inout         DRM_XML_BINDING_INFO *f_pXmlBindInfo,
    __in            DRM_DWORD             f_cbSymmKey );

DRM_API DRM_RESULT DRM_CALL DRM_BBX_RebindSymmetricKeyXMR(
    __inout         DRM_BB_CONTEXT       *f_pcontextBBX,
    __in      const DRM_SLK              *f_pslk,
    __inout         DRM_XMR_LICENSE      *f_pXmrLicense );

DRM_API DRM_RESULT DRM_CALL DRM_BBX_RebindSLK(
    __inout_ecount( 1 )             DRM_BB_CONTEXT *f_pcontextBBX,
    __in_bcount( f_cbEncSLK ) const DRM_BYTE       *f_pbEncSLK,
    __in                            DRM_DWORD       f_cbEncSLK,
    __out_ecount( 1 )               DRM_SLK        *f_pslk );

DRM_API DRM_RESULT DRM_CALL DRM_BBX_StoreDomainPrivateKeys(
    __inout_ecount( 1 )         DRM_BB_CONTEXT *f_poBBXContext,
    __inout_ecount( 1 )         DRM_DOMAINSTORE_CONTEXT *f_poDomainStoreContext,
    __inout_bcount( f_cbData )  DRM_BYTE *f_pbData,
    __in                        DRM_DWORD f_cbData,
    __inout_ecount( 1 )         DRM_DOMAIN_ID *f_poDomainID,
    __in_ecount( 1 )      const PUBKEY_P256 *f_poECC256PubKey,
    __in_ecount( 1 )            DRM_ANSI_STRING *f_pdastrCertificate );

DRM_API DRM_RESULT DRM_CALL DRM_BBX_Legacy_SymmetricCipher(
    __in                                DRM_BOOL  f_fEncrypt,
    __in_bcount_opt( f_cbKey )   const  DRM_BYTE *f_pbKey,
    __in                                DRM_DWORD f_cbKey,
    __in_bcount( f_cbData )             DRM_BYTE *f_pbDataIn,
    __out_bcount_opt( f_cbData )        DRM_BYTE *f_pbDataOut,
    __in                                DRM_DWORD f_cbData );

DRM_API DRM_RESULT DRM_CALL DRM_BBX_ECC256_Decrypt(
    __inout_ecount( 1 )                DRM_BB_CONTEXT    *f_poBBXContext,
    __in_bcount( f_cbData )      const DRM_BYTE          *f_pbData,
    __in                               DRM_DWORD          f_cbData,
    __inout_ecount( 1 )          const PUBKEY_P256       *f_poECC256PubKey,
    __out_ecount( 1 )                  OEM_CRYPTO_HANDLE *f_phKeyPair );

DRM_API DRM_RESULT DRM_CALL DRM_BBX_ECC256_Sign(
    __inout_ecount( 1 )                                DRM_BB_CONTEXT *f_poBBXContext,
    __inout_bcount( f_cbData )                         const DRM_BYTE *f_pbData,
    __in                                               DRM_DWORD       f_cbData,
    __inout_ecount( 1 )                                PUBKEY_P256    *f_poECC256PubKey,
    __out_bcount( ECDSA_P256_SIGNATURE_SIZE_IN_BYTES ) DRM_BYTE        f_rgbECC256Signature[ECDSA_P256_SIGNATURE_SIZE_IN_BYTES] );

DRM_API DRM_RESULT DRM_CALL DRM_BBX_SignWithCertKeys(
    __in_ecount( 1 )                DRM_BB_CONTEXT      *f_pBbxContext,
    __in                            DRM_DEVICE_KEY_TYPE  f_eKeyType,
    __in                            OEM_CRYPTO_HANDLE    f_hPrivKey,  
    __in                            DRM_DWORD            f_cbData,
    __in_bcount( f_cbData ) const   DRM_BYTE            *f_pbData,
    __inout_ecount( 1 )             DRM_DWORD           *f_pcbSignature,
    __out_bcount( *f_pcbSignature ) DRM_BYTE            *f_pbSignature);
	
#ifdef PLAYREADY2TEE
DRM_API DRM_RESULT DRM_CALL DRM_BBX_GetSecureStop(
    __inout_ecount( 1 )         DRM_BB_CONTEXT *f_poBBXContext,
    __in_bcount( 16 )           DRM_BYTE       *f_pbSessionID,   
    __inout_bcount( f_cbData )  DRM_BYTE       *f_pbData,
    __inout_ecount( 1 )         DRM_DWORD      *f_cbData,
    __out                       TEE_SIGNATURE  *f_sig);
#endif

DRM_API DRM_RESULT DRM_CALL DRM_BBX_GenerateECCKeyPair(
    __inout                             DRM_BB_CONTEXT    *f_pBbxContext,
    __in                                OEM_HAL_KEY_TYPE   f_eKeyType,
    __inout_ecount( 1 )                 DRM_DWORD         *f_pcbPublicKey,
    __out_bcount( *f_pcbPublicKey )     DRM_BYTE          *f_pbPublicKey,
    __out_ecount( 1 )                   OEM_CRYPTO_HANDLE *f_phKeyPair );

DRM_API DRM_RESULT DRM_CALL DRM_BBX_Legacy_GenerateECCKeyPair(
    __inout                             DRM_CRYPTO_CONTEXT                 *f_pcontextCRYP,
    __in                                DRM_PKCRYPTO_SUPPORTED_ALGORITHMS   f_eAlgorithm,
    __inout_ecount( 1 )                 DRM_DWORD                          *f_pcbPublicKey,
    __out_bcount( *f_pcbPublicKey )     DRM_BYTE                           *f_pbPublicKey,
    __inout_ecount( 1 )                 DRM_DWORD                          *f_pcbPrivateKey,
    __out_bcount( *f_pcbPrivateKey )    DRM_BYTE                           *f_pbPrivateKey);

DRM_API DRM_RESULT DRM_CALL DRM_BBX_KF_EncryptKey (
    __inout           DRM_BB_CONTEXT    *f_pBbxContext,
    __in              OEM_CRYPTO_HANDLE  f_hKey,
    __out_ecount( 1 ) DRM_ENCRYPTED_KEY *f_pEncryptedKey );

DRM_API DRM_RESULT DRM_CALL DRM_BBX_KF_Legacy_DecryptKey(
    __in_opt                                       DRM_VOID             *f_pOEMContext,
    __in                                     const DRM_ENCRYPTED_KEY    *f_pEncryptedKey,
    __in                                           DRM_DEVICE_KEY_TYPE   f_eKeyType,
    __inout_bcount_opt( *f_pcbDecryptedKey )       DRM_BYTE             *f_pbDecryptedKey,
    __inout                                        DRM_DWORD            *f_pcbDecryptedKey );

DRM_API DRM_RESULT DRM_CALL DRM_BBX_KF_Legacy_EncryptKey (
    __in_opt                        DRM_VOID                  *f_pOEMContext,
    __in_bcount(f_cbClearKey) const DRM_BYTE                  *f_pbClearKey,
    __in                            DRM_DWORD                  f_cbClearKey,
    __in                            DRM_DEVICE_KEY_TYPE        f_eKeyType,
    __out                           DRM_ENCRYPTED_KEY         *f_pEncryptedKey );

DRM_API DRM_RESULT DRM_CALL DRM_BBX_KF_CalculateOmac (
    __in_opt    DRM_VOID    *f_pOEMContext,
    __inout     DRM_GUID    *f_pguidAESDecryptionKeyID,
    __in        DRM_BOOL     f_fUseCurrentKey,
    __in_bcount(f_cbData) const DRM_BYTE *f_pbData,
    __in        DRM_DWORD    f_cbData,
    __inout_bcount(DRM_AES_BLOCKLEN) DRM_BYTE f_rgbSignatureBuffer[DRM_AES_BLOCKLEN]
);

/*
** Note that this API must be called in the context of the keyfile context already open
** and locked for writing.
*/

DRM_API DRM_RESULT DRM_CALL DRM_BBX_SetupSecureStoreKey(
    __inout_ecount( 1 ) DRM_BB_CONTEXT *f_pBlackBoxContext,
    __in_opt            DRM_VOID       *f_pOEMContext );

PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_PARAM_25004, "Prefast Noise: asks for different parameters to be constant because of empty stub functions.");
DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_BBX_PRND_Tx_GenerateAESKeyPairAndECCEncrypt(
    __inout_ecount( 1 )                               DRM_BB_CONTEXT                  *f_poBBXContext,
    __in                                              DRM_BBX_KEY_PAIR_TYPE            f_eKeyPairType,
    __in_opt                                    const DRM_PUBLIC_KEY_CONTEXT          *f_poECC256PubKeyTarget,
    __in_ecount_opt( f_cbCertificateTarget )    const DRM_BYTE                        *f_pbCertificateTarget,
    __in                                              DRM_DWORD                        f_cbCertificateTarget,
    __in_ecount_opt( f_cbCertificateTargetCRL ) const DRM_BYTE                        *f_pbCertificateTargetCRL,
    __in                                              DRM_DWORD                        f_cbCertificateTargetCRL,
    __in_ecount_opt( f_cbRevInfo )              const DRM_BYTE                        *f_pbRevInfo,
    __in                                              DRM_DWORD                        f_cbRevInfo,
    __in                                              DRM_DWORD                        f_dwRequestedSecurityLevel,
    __out_ecount( 1 )                                 CIPHERTEXT_P256                 *f_poEncryptedAESKeyPair,
    __out_ecount( 1 )                                 OEM_CRYPTO_HANDLE               *f_phandleAESKeyPair ) DRM_NO_INLINE_ATTRIBUTE;

PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_BUFFER_PARAM_25033, "Out params can't be const");
DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_BBX_PRND_Tx_GenerateAESKeyPairAndAESECBEncrypt(
    __inout_ecount( 1 )                               DRM_BB_CONTEXT                  *f_poBBXContext,
    __in                                              DRM_BBX_KEY_PAIR_TYPE            f_eKeyPairType,
    __in_ecount( 1 )                            const OEM_CRYPTO_HANDLE                f_handleAESRootEncryptionKey,
    __in                                              DRM_DWORD                        f_dwRequestedSecurityLevel,
    __out_ecount( DRM_AES_BLOCKLEN * 2 )              DRM_BYTE                         f_rgbEncryptedAESKeyPair[DRM_AES_BLOCKLEN * 2],
    __out_ecount( 1 )                                 OEM_CRYPTO_HANDLE               *f_phandleAESKeyPair ) DRM_NO_INLINE_ATTRIBUTE;
PREFAST_POP /* __WARNING_NONCONST_PARAM_25033 */

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_BBX_PRND_Tx_GenerateAESGenericKey(
    __inout_ecount( 1 )                               DRM_BB_CONTEXT                  *f_poBBXContext,
    __in                                              OEM_HAL_KEY_TYPE                 f_eKeyType,
    __out_ecount( 1 )                                 OEM_CRYPTO_HANDLE               *f_phandleAESGenericKey ) DRM_NO_INLINE_ATTRIBUTE;

PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_BUFFER_PARAM_25033, "Out params can't be const");
PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_PARAM_25004, "Prefast Noise: temporarily disable while two keys passed in");
DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_BBX_PRND_Tx_EncryptAESKeyPairWithAESECBUsingGenericKey(
    __inout_ecount( 1 )                               DRM_BB_CONTEXT                  *f_poBBXContext,
    __in_ecount( 1 )                            const OEM_CRYPTO_HANDLE                f_handleAESGenericKey,
    __in_ecount( 1 )                            const OEM_CRYPTO_HANDLE                f_handleAESKeyPair,
    __out_ecount( DRM_AES_BLOCKLEN * 2 )              DRM_BYTE                         f_rgbEncryptedAESKeyPair[DRM_AES_BLOCKLEN * 2] ) DRM_NO_INLINE_ATTRIBUTE;
PREFAST_POP /* __WARNING_NONCONST_PARAM_25004 */
PREFAST_POP /* __WARNING_NONCONST_PARAM_25033 */

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_BBX_PRND_Tx_DecryptAESKeyPairWithAESECBUsingGenericKey(
    __inout_ecount( 1 )                               DRM_BB_CONTEXT                  *f_poBBXContext,
    __in_ecount( 1 )                            const OEM_CRYPTO_HANDLE                f_handleAESGenericKey,
    __in_ecount( DRM_AES_BLOCKLEN * 2 )         const DRM_BYTE                         f_rgbEncryptedAESKeyPair[DRM_AES_BLOCKLEN * 2],
    __out_ecount( 1 )                                 OEM_CRYPTO_HANDLE               *f_phandleAESKeyPair ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_BBX_PRND_Tx_RebindLicenseKeysToNewECCKey(
    __inout_ecount( 1 )                               DRM_BB_CONTEXT                  *f_poBBXContext,
    __in_ecount( 1 )                            const DRM_BINDING_INFO                *f_pRootmostLicenseBindingInfo,
    __in                                        const DRM_PUBLIC_KEY_CONTEXT          *f_poECC256PubKeyTarget,
    __in_ecount_opt( f_cbCertificateTarget )    const DRM_BYTE                        *f_pbCertificateTarget,
    __in                                              DRM_DWORD                        f_cbCertificateTarget,
    __in_ecount_opt( f_cbCertificateTargetCRL ) const DRM_BYTE                        *f_pbCertificateTargetCRL,
    __in                                              DRM_DWORD                        f_cbCertificateTargetCRL,
    __in_ecount_opt( f_cbRevInfo )              const DRM_BYTE                        *f_pbRevInfo,
    __in                                              DRM_DWORD                        f_cbRevInfo,
    __out_ecount( 1 )                                 OEM_CRYPTO_HANDLE               *f_phandleAESIntegrityKey,
    __out_ecount( 1 )                                 CIPHERTEXT_P256                 *f_poEncryptedAESKeyPair ) DRM_NO_INLINE_ATTRIBUTE;

PREFAST_POP /* __WARNING_NONCONST_PARAM_25004 */

PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_BUFFER_PARAM_25033, "Out params can't be const");
PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_PARAM_25004, "Prefast Noise: DRM_BB_CONTEXT should never be const");
DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_BBX_PRND_Tx_EncryptClearContentWithAESCTR(
    __inout_ecount( 1 )                               DRM_BB_CONTEXT                  *f_poBBXContext,
    __in_ecount( 1 )                            const OEM_CRYPTO_HANDLE                f_handleAESContentEncryptionKey,
    __inout_ecount( 1 )                               OEM_ENCRYPTION_HANDLE           *f_phandleEncryption,
    __out                                             DRM_UINT64                      *f_pqwInitializationVector,
    __out_ecount_opt(1)                               OEM_HAL_SAMPLE_METADATA         *f_pMetadata,
    __in_opt                                          OEM_OPAQUE_BUFFER_HANDLE         f_hInBuf,
    __in_opt                                          OEM_OPAQUE_BUFFER_HANDLE         f_hOutBuf,
    __inout_bcount_opt( f_cbData )                    DRM_BYTE                        *f_pbData,
    __in                                              DRM_DWORD                        f_cbData ) DRM_NO_INLINE_ATTRIBUTE;
PREFAST_POP /* __WARNING_NONCONST_PARAM_25004 */
PREFAST_POP /* __WARNING_NONCONST_PARAM_25033 */

PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_PARAM_25004, "Prefast Noise: DRM_BB_CONTEXT should never be const");
DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_BBX_PRND_Rx_SignWithAESOMAC(
    __inout_ecount( 1 )                               DRM_BB_CONTEXT                  *f_poBBXContext,
    __in_ecount( 1 )                                  OEM_CRYPTO_HANDLE                f_handleAESIntegrityKey,
    __in_bcount( f_cbData )                     const DRM_BYTE                        *f_pbData,
    __in                                              DRM_DWORD                        f_cbData,
    __out_ecount( DRM_AES_BLOCKLEN )                  DRM_BYTE                         f_rgbSignature[DRM_AES_BLOCKLEN] ) DRM_NO_INLINE_ATTRIBUTE;
PREFAST_POP /* __WARNING_NONCONST_PARAM_25004 */

PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_BUFFER_PARAM_25033, "Out params can't be const");
PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_PARAM_25004, "Prefast Noise: DRM_BB_CONTEXT should never be const");
DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_BBX_PRND_Tx_SignWithAESOMAC(
    __inout_ecount( 1 )                               DRM_BB_CONTEXT                  *f_poBBXContext,
    __in_ecount( 1 )                                  OEM_CRYPTO_HANDLE                f_handleAESIntegrityKey,
    __in_bcount( f_cbData )                     const DRM_BYTE                        *f_pbData,
    __in                                              DRM_DWORD                        f_cbData,
    __out_ecount( DRM_AES_BLOCKLEN )                  DRM_BYTE                         f_rgbSignature[DRM_AES_BLOCKLEN] ) DRM_NO_INLINE_ATTRIBUTE;
PREFAST_POP /* __WARNING_NONCONST_PARAM_25004 */
PREFAST_POP /* __WARNING_NONCONST_PARAM_25033 */

PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_BUFFER_PARAM_25033, "Out params can't be const");
PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_PARAM_25004, "Prefast Noise: DRM_BB_CONTEXT should never be const");
DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_BBX_PRND_Tx_CalculateChecksum(
    __inout_ecount( 1 )                               DRM_BB_CONTEXT                  *f_poBBXContext,
    __in_ecount( 1 )                            const OEM_CRYPTO_HANDLE                f_handleAESContentEncryptionKey,
    __in                                        const DRM_KID                         *f_pKID,
    __out_ecount( DRM_AES_CK_CHECKSUM_LENGTH )        DRM_BYTE                         f_rgbChecksum[ DRM_AES_CK_CHECKSUM_LENGTH ] ) DRM_NO_INLINE_ATTRIBUTE;
PREFAST_POP /* __WARNING_NONCONST_PARAM_25004 */
PREFAST_POP /* __WARNING_NONCONST_PARAM_25033 */

PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_PARAM_25004, "Prefast Noise: DRM_BB_CONTEXT should never be const");
DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_BBX_PRND_Rx_VerifySignatureWithAESOMAC(
    __inout_ecount( 1 )                               DRM_BB_CONTEXT                  *f_poBBXContext,
    __in_ecount( 1 )                            const OEM_CRYPTO_HANDLE                f_handleAESIntegrityKey,
    __in_bcount( f_cbData )                     const DRM_BYTE                        *f_pbData,
    __in                                              DRM_DWORD                        f_cbData,
    __in_ecount( DRM_AES_BLOCKLEN )             const DRM_BYTE                         f_rgbSignature[DRM_AES_BLOCKLEN] ) DRM_NO_INLINE_ATTRIBUTE;
PREFAST_POP /* __WARNING_NONCONST_PARAM_25004 */
PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_PARAM_25004, "Prefast Noise: DRM_BB_CONTEXT should never be const");
DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_BBX_PRND_Tx_VerifySignatureWithAESOMAC(
    __inout_ecount( 1 )                               DRM_BB_CONTEXT                  *f_poBBXContext,
    __in_ecount( 1 )                            const OEM_CRYPTO_HANDLE                f_handleAESIntegrityKey,
    __in_bcount( f_cbData )                     const DRM_BYTE                        *f_pbData,
    __in                                              DRM_DWORD                        f_cbData,
    __in_ecount( DRM_AES_BLOCKLEN )             const DRM_BYTE                         f_rgbSignature[DRM_AES_BLOCKLEN] ) DRM_NO_INLINE_ATTRIBUTE;
PREFAST_POP /* __WARNING_NONCONST_PARAM_25004 */

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_BBX_PRND_Rx_ECCDecryptAESKeyPair(
    __inout_ecount( 1 )                               DRM_BB_CONTEXT                  *f_poBBXContext,
    __in                                              DRM_BBX_KEY_PAIR_TYPE            f_eKeyPairType,
    __in_ecount( 1 )                            const CIPHERTEXT_P256                 *f_poEncryptedAESKeyPair,
    __out_ecount( 1 )                                 OEM_CRYPTO_HANDLE               *f_phandleAESKeyPair ) DRM_NO_INLINE_ATTRIBUTE;

PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_PARAM_25004, "Prefast Noise: DRM_BB_CONTEXT should never be const");
DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_BBX_PRND_Rx_EncryptNonceWithAESECB(
    __inout_ecount( 1 )                               DRM_BB_CONTEXT                  *f_poBBXContext,
    __in_ecount( 1 )                            const OEM_CRYPTO_HANDLE                f_handleAESMessageEncryptionKey,
    __inout_ecount( 1 )                               DRM_ID                          *f_pNonce ) DRM_NO_INLINE_ATTRIBUTE;
PREFAST_POP /* __WARNING_NONCONST_PARAM_25004 */
PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_PARAM_25004, "Prefast Noise: DRM_BB_CONTEXT should never be const");
DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_BBX_PRND_Tx_EncryptNonceWithAESECB(
    __inout_ecount( 1 )                               DRM_BB_CONTEXT                  *f_poBBXContext,
    __in_ecount( 1 )                            const OEM_CRYPTO_HANDLE                f_handleAESMessageEncryptionKey,
    __inout_ecount( 1 )                               DRM_ID                          *f_pNonce ) DRM_NO_INLINE_ATTRIBUTE;
PREFAST_POP /* __WARNING_NONCONST_PARAM_25004 */

DRM_API DRM_VOID DRM_CALL DRM_BBX_SafeReleaseKey(
    __inout_ecount( 1 ) DRM_BB_CONTEXT    *f_pBbxContext,
    __inout_ecount( 1 ) OEM_CRYPTO_HANDLE *f_phKey );

DRM_API DRM_VOID DRM_CALL DRM_BBX_SafeDestroySampleEncryptionContext(
    __inout_ecount( 1 ) OEM_ENCRYPTION_HANDLE *f_phEncryptionContext );

DRM_API DRM_RESULT DRM_CALL DRM_BBX_GetPreloadedKey( 
    __inout_ecount( 1 )    DRM_BB_CONTEXT    *f_pBbxContext,
    __in                   OEM_HAL_KEY_TYPE   f_eType,
    __in_ecount( 1 ) const DRM_GUID          *f_pguidKeyId,
    __out_ecount( 1 )      OEM_CRYPTO_HANDLE *f_phKey );

DRM_API DRM_RESULT DRM_CALL DRM_BBX_UnwrapKey(
    __inout                                 DRM_BB_CONTEXT     *f_pBbxContext,
    __in                                    OEM_HAL_KEY_TYPE    f_eKeyType,
    __in                                    OEM_CRYPTO_HANDLE   f_hWrappingKey,
    __in_bcount( f_cbWrappedKeyData ) const DRM_BYTE           *f_pbWrappedKeyData,
    __in                                    DRM_DWORD           f_cbWrappedKeyData,
    __in_bcount( f_cbParameterData )  const DRM_BYTE           *f_pbParameterData,
    __in                                    DRM_DWORD           f_cbParameterData,
    __in_bcount( f_cbCacheKey )       const DRM_BYTE           *f_pbCacheKey,
    __in                              const DRM_DWORD           f_cbCacheKey,
    __out_ecount( 1 )                       OEM_CRYPTO_HANDLE  *f_phKey);

PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_PARAM_25004, "Prefast Noise: DRM_BB_CONTEXT should never be const");
DRM_API DRM_RESULT DRM_CALL DRM_BBX_InitPublicKeyContext(
    __inout_ecount(1) DRM_BB_CONTEXT       *f_pBbxContext,
    __out_ecount(1) DRM_PUBLIC_KEY_CONTEXT *f_pKeyContext );
PREFAST_POP /* __WARNING_NONCONST_PARAM_25004 */

PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_PARAM_25004, "Prefast Noise: DRM_BB_CONTEXT should never be const");
DRM_API DRM_VOID DRM_CALL DRM_BBX_CleanupPublicKeyContext(
    __inout_ecount(1) DRM_BB_CONTEXT       *f_pBbxContext,
    __out_ecount(1) DRM_PUBLIC_KEY_CONTEXT *f_pKeyContext );
PREFAST_POP /* __WARNING_NONCONST_PARAM_25004 */

DRM_API DRM_RESULT DRM_CALL DRM_BBX_TransferPublicKeyContext(
    __inout_ecount(1) DRM_BB_CONTEXT         *f_pBbxContext,
    __out_ecount(1)   DRM_PUBLIC_KEY_CONTEXT *f_pDestinationKeyContext,
    __inout_ecount(1) DRM_PUBLIC_KEY_CONTEXT *f_pSourceKeyContext );

DRM_API DRM_RESULT DRM_CALL DRM_BBX_DuplicatePublicKeyContext(
    __inout_ecount(1) DRM_BB_CONTEXT         *f_pBbxContext,
    __out_ecount(1)   DRM_PUBLIC_KEY_CONTEXT *f_pDestinationKeyContext,
    __inout_ecount(1) DRM_PUBLIC_KEY_CONTEXT *f_pSourceKeyContext );


EXIT_PK_NAMESPACE;

#endif /* __DRMBLACKBOX_H__ */

