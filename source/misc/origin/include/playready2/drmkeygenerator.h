/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRMKEYGEN_H__
#define __DRMKEYGEN_H__

#include <drmnamespace.h>   /* defining proper namespace (if used) */
#include <oemcipher.h>

ENTER_PK_NAMESPACE;

#define DRM_KEYSEED_BASE64_LEN  40
#define DRM_KEYSEED_BINARY_LEN  CB_BASE64_DECODE(DRM_KEYSEED_BASE64_LEN)


/**************
  NOTE:  All Keygen functions include a NULL termination character
  in the character count and the string on function return
**************/

/**********************************************************************
** Function:    DRM_KG_GenerateKeyseed
** Synopsis:    Generate pseudo random keyseed
** Arguments:   [pwszKeyseed] -- Pointer of Unicode string to receive the keyseed
**              [pchKeyseed] -- size in chars of pwszKeyseed
** Returns:     DRM_SUCCESS on success
** Notes:
***********************************************************************
*/
DRM_API DRM_RESULT DRM_CALL DRM_KG_GenerateKeyseed(
    __in_opt                           DRM_VOID  *f_pOEMContext,
    __out_ecount_opt( *f_pcchKeyseed ) DRM_WCHAR *f_pwszKeyseed,
    __inout                            DRM_DWORD *f_pcchKeyseed );

/**********************************************************************
** Function:    DRM_KG_GenerateKeyID
** Synopsis:    Generate pseudo random Key ID
** Arguments:   [pwszKeyseed] -- Pointer of Unicode string to receive the keyseed
**              [pchKeyseed] -- size in chars of pwszKeyseed
** Returns:     DRM_SUCCESS on success
** Notes:
***********************************************************************
*/
DRM_API DRM_RESULT DRM_CALL DRM_KG_GenerateKeyID(
    __in_opt                         DRM_VOID  *f_pOEMContext,
    __out_ecount_opt( *f_pcchKeyID ) DRM_WCHAR *f_pwszKeyID,           /* base64 encoded string */
    __inout                          DRM_DWORD *f_pcchKeyID );


/*******************************************************************************
** Function:   DRM_KG_GenerateContentKeyB64
** Parameters:
**      [in] pbKeySeed:    A byte array representing seed.
**      [in] cbKeySeed:    The length of the pbKeySeed field
**      [in] pbKId:        The key id (KID). Normally, this is base-64 encoded guid.
**      [in] cbKId:        The length of the pbKId field.
**      [out] pwszContentKey: base64
**      [in] pcchContentKey:
** Purpose:
**      To generate the key for a given kid based on a license key seed of length up to 20 bytes.
********************************************************************************/
DRM_API DRM_RESULT DRM_CALL DRM_KG_GenerateContentKeyB64(
    __in_ecount( f_cchKeySeed )            const DRM_WCHAR             *f_pwszKeySeed,          /* base64 encoded string */
    __in                                         DRM_DWORD              f_cchKeySeed,
    __in_ecount( f_cchKeyID )              const DRM_WCHAR             *f_pwszKeyID,            /* base64 encoded string */
    __in                                         DRM_DWORD              f_cchKeyID,
    __in                                         DRM_SUPPORTED_CIPHERS  f_eCipherType,
    __in                                         DRM_DWORD              f_cbContentKey,
    __out_ecount_opt(*f_pcchContentKey)          DRM_WCHAR             *f_pwszContentKey,
    __in                                         DRM_DWORD             *f_pcchContentKey,
    __out_bcount_opt( f_cbScratchKeySeed )       DRM_BYTE              *f_pbScratchKeySeed,
    __in                                         DRM_DWORD              f_cbScratchKeySeed );



DRM_NO_INLINE DRM_API DRM_RESULT DRM_CALL DRM_KG_GenerateContentKeyBinary(
    __in_bcount( f_cbKeySeed )             const DRM_BYTE  *f_pbKeySeed,
    __in                                         DRM_DWORD  f_cbKeySeed,
    __in                                   const DRM_KID   *f_pKID,
    __in                                         DRM_SUPPORTED_CIPHERS f_eCipherType,
    __out_bcount(f_cbContentKey)                 DRM_BYTE  *f_pbContentKey,
    __in                                         DRM_DWORD  f_cbContentKey,
    __out_bcount_opt( f_cbScratchKeySeed )       DRM_BYTE  *f_pbScratchKeySeed,
    __in                                         DRM_DWORD  f_cbScratchKeySeed ) DRM_NO_INLINE_ATTRIBUTE;





/*******************************************************************************
** Function:    DRM_KG_GenerateSigningKeys
** Synopsis:    Generate signing key pair. Generated key pair will be base64 encoded
** Arguments:   [pCrypto] -- pointer to PKCrypto context
**              [pwszPrivKey] -- pointer to unicode string to receive the generated priv key
**              [pcchPrivKey] -- length in char of pwszPrivKey
**              [pwszPubKey] -- pointer to unicode string to receive the generated pub key
**              [pcchPubKey] -- length in char of pwszPubkey
** Returns:     DRM_SUCCESS on success
** Notes:
********************************************************************************/
DRM_API DRM_RESULT DRM_CALL DRM_KG_GenerateSigningKeys(
    __in                               DRM_CRYPTO_CONTEXT *f_pCrypto,
    __out_ecount_opt( *f_pcchPrivKey ) DRM_WCHAR          *f_pwszPrivKey,  /* base64 encoded string */
    __inout                            DRM_DWORD          *f_pcchPrivKey,
    __out_ecount_opt( *f_pcchPubKey )  DRM_WCHAR          *f_pwszPubKey,   /* base64 encoded string */
    __inout                            DRM_DWORD          *f_pcchPubKey );

EXIT_PK_NAMESPACE;

#endif /*__DRMKEYGEN_H__ */

