/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/


#ifndef __DRMNDCERTBUILDER_H__
#define __DRMNDCERTBUILDER_H__


#include <drmbase64.h>
#include <drmxmlrsakeys.h>
#include <oemrsa.h>
#include <drmcert.h>
#include <drmcertparser.h>

#define DRM_CDS_USE_SIGNATURE_PARAMETER 0x00000001

#define CB_SIGNATURE_RSA( keyLength )   DRM_RSA_CB_MODULUS( keyLength )
#define CCH_SIGNATURE_RSA( keyLength )  CCH_BASE64_EQUIV( CB_SIGNATURE_RSA( keyLength ) )

ENTER_PK_NAMESPACE;

DRM_API DRM_RESULT DRM_CALL DRM_ND_CB_CreateCertificateInit(
  __inout            _XMBContextA          *f_pXMLContextA,
  __in     enum DRM_CERTIFICATE_TYPE        f_eCertType,
  __in    const DRM_RSA_PUBLIC_KEY_2048BIT *f_pKeyPublic,
  __in    const DRM_CRYPTO_CONTEXT         *f_pCryptoCtx  );

DRM_API DRM_RESULT DRM_CALL DRM_ND_CB_CreateCertificateAddTemplateData(
  __inout       _XMBContextA               *f_pXMLContextA,
  __in    const DRM_ANSI_CONST_STRING      *f_pdastrTemplate );

DRM_API DRM_RESULT DRM_CALL DRM_ND_CB_CreateCertificateSignAndClose(
  __inout       _XMBContextA                  *f_pXMLContextA,
  __in    const DRM_ANSI_CONST_STRING         *f_pdastrRSAPubKeyModulusB64,
  __in    const DRM_ANSI_CONST_STRING         *f_pdastrRSAPubKeyExponentB64,
  __in    const DRM_RSA_PRIVATE_KEY_2048BIT   *f_pRSAPrivKey,
  __in          DRM_CRYPTO_CONTEXT            *f_pCryptoCtx  );

DRM_API DRM_RESULT DRM_CALL DRM_ND_CB_CreateCertificate(
  __inout       _XMBContextA                *f_pXMLContextA,
  __in     enum DRM_CERTIFICATE_TYPE         f_eCertType,
  __in    const DRM_RSA_PUBLIC_KEY_2048BIT  *f_pKeyPublic,
  __in    const DRM_ANSI_CONST_STRING       *f_pdastrRSAPubKeyModulusB64,
  __in    const DRM_ANSI_CONST_STRING       *f_pdastrRSAPubKeyExponentB64,
  __in    const DRM_RSA_PRIVATE_KEY_2048BIT *f_pRSAPrivKey,
  __in    const DRM_ANSI_CONST_STRING       *f_pdastrTemplate,
  __in          DRM_CRYPTO_CONTEXT          *f_pCryptoCtx );

DRM_API DRM_RESULT DRM_CALL DRM_ND_CB_AddAttribute(
  __inout                             _XMBContextA             *f_pXMLContext,
  __in                                DRM_WMDRM_CERT_ATTRIBUTE  f_eCertAttribute,
  __in_ecount(f_cEntries)       const DRM_ANSI_CONST_STRING    *f_rgpdastrValue[],
  __in                                DRM_DWORD                 f_cEntries );

DRM_API DRM_RESULT DRM_CALL DRM_ND_CB_AddManufacturerNodes(
    __inout                           _XMBContextA           *f_pXMLContext,
    __in_opt                    const DRM_ANSI_CONST_STRING  *f_pdastrNamespace,
    __in_ecount(f_cEntries)     const DRM_ANSI_CONST_STRING **f_rgpdastrTag,
    __in_ecount_opt(f_cEntries) const DRM_ANSI_CONST_STRING **f_rgpdastrAttrLabel,
    __in_ecount_opt(f_cEntries) const DRM_ANSI_CONST_STRING **f_rgpdastrAttrValue,
    __in_ecount(f_cEntries)     const DRM_ANSI_CONST_STRING **f_rgpdastrValue,
    __in                        const DRM_DWORD               f_cEntries );

DRM_API DRM_RESULT DRM_CALL DRM_ND_CB_SignCertificate(
    __inout       _XMBContextA                  *f_pXMLContext,
    __in          DRM_BOOL                       f_fWMDRMNET,
    __in    const DRM_ANSI_CONST_STRING         *f_pdastrRSAPubKeyModulusB64,
    __in    const DRM_ANSI_CONST_STRING         *f_pdastrRSAPubKeyExponentB64,
    __in    const DRM_RSA_PRIVATE_KEY_2048BIT   *f_pRSAPrivKey,
    __in          DRM_CRYPTO_CONTEXT            *f_pCryptoCtx  );

DRM_API DRM_RESULT DRM_CALL DRM_ND_CB_CreateDigitalSignature(
    __inout                           _XMBContextA                  *f_pXMLContext,
    __in                        const DRM_ANSI_CONST_STRING         *f_pdastrRSAPubKeyModulusB64,
    __in                        const DRM_ANSI_CONST_STRING         *f_pdastrRSAPubKeyExponentB64,
    __in                        const DRM_RSA_PRIVATE_KEY_2048BIT   *f_pRSAPrivKey,
    __in                        const DRM_DWORD                      f_cchSHA,
    __in_ecount( f_cchSHA )     const DRM_CHAR                      *f_pchSHA,
    __in                        const DRM_DWORD                      f_cchRSA,
    __in_ecount_opt( f_cchRSA ) const DRM_CHAR                      *f_pchRSA,
    __in                              DRM_DWORD                      f_dwSignType,
    __in                              DRM_DWORD                      f_dwFlags,
    __in                              DRM_CRYPTO_CONTEXT            *f_pCryptoCtx );

DRM_API DRM_RESULT DRM_CALL DRM_ND_CB_CreateCertificateFile(
    __inout        _XMBContextA                *f_pXMLContext,
    __in     enum  DRM_CERTIFICATE_TYPE         f_oCertType,
    __in     const DRM_RSA_PUBLIC_KEY_2048BIT  *f_pKeyPublic,
    __in     const DRM_ANSI_CONST_STRING       *f_pdastrRSAPubKeyModulusB64,
    __in     const DRM_ANSI_CONST_STRING       *f_pdastrRSAPubKeyExponentB64,
    __in     const DRM_RSA_PRIVATE_KEY_2048BIT *f_pRSAPrivKey,
    __in     const DRM_ANSI_CONST_STRING       *f_pdastrTemplate,
    __in_opt const DRM_ANSI_CONST_STRING       *f_pdastrCerts,
    __in           DRM_CRYPTO_CONTEXT          *f_pCryptoCtx );

EXIT_PK_NAMESPACE;

#endif /* __DRMNDCERTBUILDER_H__ */
