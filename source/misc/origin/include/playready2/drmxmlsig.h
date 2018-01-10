/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRM_XML_SIG_H
#define __DRM_XML_SIG_H

#include <drmxmlbuildera.h>
#include <oemeccp256.h>
#include <drmblackbox.h>

ENTER_PK_NAMESPACE;

/*
** An AES key combo. The first 16 bytes forms an 128 bits initialization vector.
** The second 16 bytes forms a random 128 bits AES key.
*/
#define DRM_XML_AES_KEY_SIZE  ( DRM_AES_KEYSIZE_128 * 2 )

/*
***************************************************************************
**                        XML Key info
***************************************************************************
*/

/*
** The enumeration define type of RSA public key to be used.
*/
typedef enum
{
    /*
    ** Invalid Key info: not initialized or not consistent
    */
    DRM_XML_KEYINFO_INVALID,

    /*
    ** Key info that contains a public key only
    */
    DRM_XML_KEYINFO_SIMPLE,

    /*
    ** Key info that contains symmetric key
    ** encrypted with a public key;
    ** XML presentation will have <EncryptedKey> tag
    */
    DRM_XML_KEYINFO_ENCRYPTED

} DRM_XML_KEYINFO_TYPE;

/*
** The enumeration define type of RSA public key to be used.
*/
typedef enum
{
    /* Invalid key.  */
    DRM_XML_ECC256_INVALID_KEY,

    /*
    ** Full ECC-256 public key.
    */
    DRM_XML_ECC256_PUBLIC_KEY_DATA,

    /*
    ** ID of a pre-shared ECC-256 Public key:
    ** It means the ECC-256 public key in the <KeyInfo> segment
    ** only contains a key ID. Parties that see the key ID
    ** should understand the actual ECC-256 public key represented
    ** by the key ID.
    */
    DRM_XML_ECC256_SERVER_PUBLIC_KEY_ID,

    DRM_XML_ECC256_CLIENT_PUBLIC_KEY_ID,

    DRM_XML_ECC256_METERING_PUBLIC_KEY_ID
} DRM_XML_ECC256_KEY_FORMAT;

/*
** Union used to store either a clear or an ECC-256 encrypted AES key.
** Assumes the size of the ciphered version is equal or bigger
** than the size clear version (plus the IV). In other words, the size of
** the ciphered version determines the size of the union.
*/
typedef union
{
    /* A clear AES key combo. */
    struct
    {
        /* Randomly generated IV */
        DRM_BYTE m_rgbIV[ __CB_DECL( DRM_AES_KEYSIZE_128 )];

        /* AES key, padded with random bytes */
        DRM_BYTE m_rgbPaddedAESKey[ __CB_DECL( DRM_XML_AES_KEY_SIZE )];
    } m_oClearAESKey;

    /* An ECC-256 encrypted AES key BLOB */
    DRM_BYTE m_rgbCipherAESKey[ __CB_DECL( ECC_P256_CIPHERTEXT_SIZE_IN_BYTES ) ];
} _AES_KEY;

/*
** Structure to contain information of a key in the <KeyInfo> XML segment.
*/
typedef struct
{
    /*
    ** KeyInfo type, can be simple or complex
    ** i.e. with another key encrypted inside
    */
    DRM_XML_KEYINFO_TYPE m_eKeyInfoType;

    /* AES key */
    _AES_KEY m_oAESKey;

    /*
    ** The format of the ECC-256 public key that is used to encrypt the AES key.
    ** If the values is DRM_XML_ECC256_PUBLIC_KEY_ID, a pre-shared ECC-256 public key
    ** will be used to decrypte the AES key.
    ** If the valus is DRM_XML_ECC-256_PUBLIC_KEY_DATA, a full ECC-256 public key
    ** stored in m_oECC256PubKey will be used to decrypt the AES key.
    */
    DRM_XML_ECC256_KEY_FORMAT m_eKeyFormat;

    /*
    ** If m_eKeyFormat is DRM_XML_ECC256_PUBLIC_KEY_DATA, m_oECC256PubKey
    ** contains a full ECC-256 public key used to decrypt the AES key, otherwise
    ** this field is not used.
    */
    PUBKEY_P256 m_oECC256PubKey;
} DRM_XML_KEY;

#define EMPTY_XML_KEY { DRM_XML_KEYINFO_INVALID, { 0 }, DRM_XML_ECC256_INVALID_KEY, { 0 } }


/*
***************************************************************************
**                        KeyInfo
***************************************************************************
*/
DRM_API DRM_RESULT DRM_CALL DRM_XMLSIG_GetSimpleECC256KeyInfoNodeCharCount(
    __in  const DRM_XML_ECC256_KEY_FORMAT f_eECC256KeyFormat,
    __out       DRM_DWORD                *f_pcchSize );

DRM_API DRM_RESULT DRM_CALL DRM_XMLSIG_BuildSimpleECC256KeyInfoNode(
    __inout       _XMBContextA             *f_poXMLContextA,
    __in    const PUBKEY_P256              *f_poECC256PubKey,
    __in    const DRM_XML_ECC256_KEY_FORMAT f_eECC256KeyFormat );

DRM_API DRM_RESULT DRM_CALL DRM_XMLSIG_ExtractSimpleECC256Key(
    __in_ecount( f_pdasstrXML->m_ich + f_pdasstrXML->m_cch ) const DRM_CHAR      *f_pszBase,
    __in                                                     const DRM_SUBSTRING *f_pdasstrXML,
    __out                                                          PUBKEY_P256   *f_poECC256PubKey );

DRM_API DRM_RESULT DRM_CALL DRM_XMLSIG_GetEncryptedKeyInfoNodeCharCount(
    __in    const DRM_XML_KEY *f_poXMLKey,
    __inout       DRM_DWORD   *f_pcchSize );

DRM_API DRM_RESULT DRM_CALL DRM_XMLSIG_BuildEncryptedKeyInfoNode(
    __inout       _XMBContextA *f_poXMLContextA,
    __in    const DRM_XML_KEY  *f_poXMLKey );

/*
***************************************************************************
**                        XML Signature
***************************************************************************
*/
DRM_API DRM_RESULT DRM_CALL DRM_XMLSIG_GetSignatureNodeCharCount(
    __inout DRM_DWORD *f_pcchSize );

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_XMLSIG_BuildECC256PublicKeyInfoNode(
    __inout       _XMBContextA *f_poXMLContextA,
    __in    const PUBKEY_P256  *f_poECC256PubKey );

DRM_API DRM_RESULT DRM_CALL DRM_XMLSIG_BuildSignatureNode(
    __inout       _XMBContextA   *f_poXMLContextA,
    __inout       DRM_BB_CONTEXT *f_poBBXContext,
    __in_ecount( f_pdasstrData->m_ich + f_pdasstrData->m_cch )
            const DRM_CHAR       *f_pszBase,
    __in    const DRM_SUBSTRING  *f_pdasstrData );

DRM_API DRM_RESULT DRM_CALL DRM_XMLSIG_VerifySignature(
    __in_ecount(f_pdasstrData->m_ich+f_pdasstrData->m_cch)           const DRM_CHAR             *f_pszDataBase,
    __in                                                             const DRM_SUBSTRING        *f_pdasstrData,
    __in_ecount(f_pdasstrSignature->m_ich+f_pdasstrSignature->m_cch) const DRM_CHAR             *f_pszSignatureBase,
    __in                                                             const DRM_SUBSTRING        *f_pdasstrSignature,
    __in                                                             const PUBKEY_P256          *f_poECC256PubKey,
    __inout                                                                DRM_CRYPTO_CONTEXT   *f_pCryptoCtx ) DRM_NO_INLINE_ATTRIBUTE;

/*
***************************************************************************
**                        XML Encryption
***************************************************************************
*/
DRM_API DRM_RESULT DRM_CALL DRM_XMLSIG_GetEncryptedDataNodeCharCount(
    __in    const DRM_XML_KEY *f_poXMLKey,
    __in    const DRM_DWORD    f_cbData,
    __out         DRM_DWORD   *f_pcchSize );

DRM_API DRM_RESULT DRM_CALL DRM_XMLSIG_BuildEncryptedDataNode(
    __inout       _XMBContextA  *f_poXMLContextA,
    __in    const DRM_XML_KEY   *f_poXMLKey,
    __in    const DRM_DWORD      f_cbData,
    __out         DRM_SUBSTRING *f_pdasstrEncryptedData );

PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_COUNT_REQUIRED_FOR_WRITABLE_BUFFER, "f_pszBase length defined by f_pdasstrXML")
PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_COUNT_REQUIRED_FOR_WRITABLE_BUFFER_25057, "f_pszBase length defined by f_pdasstrXML")
DRM_API  DRM_RESULT DRM_CALL DRM_XMLSIG_ExtractCipherData(
    __inout_ecount(f_pdasstrXML->m_ich+f_pdasstrXML->m_cch)       DRM_CHAR       *f_pszBase,
    __in                                                    const DRM_SUBSTRING  *f_pdasstrXML,
    __deref_out_bcount( *f_pcbCipherData )                        DRM_BYTE      **f_ppbCipherData,
    __out                                                         DRM_DWORD      *f_pcbCipherData,
    __out_opt                                                     DRM_SUBSTRING  *f_pdasstrCipherData );
PREFAST_POP
PREFAST_POP


EXIT_PK_NAMESPACE;

#endif /* __DRM_XML_SIG_H */
