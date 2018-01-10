/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRMCERTPARSER_H__
#define __DRMCERTPARSER_H__

#include <drmbase64.h>
#include <drmrevocation.h>
#include <drmcert.h>
#include <drmpragmas.h>

ENTER_PK_NAMESPACE;

enum DRM_CERTIFICATE_TYPE
{
    certtypeUnknown = -1,
    certtypeRoot    =  0,
    certtypeCertAuthority,
    certtypeBlackBox,
    certtypeBlackBoxVersion,
    certtypeMachine,
    certtypeIndivBox,
    certtypeExport,
    certtypeExportIncl,
    certtypeDevice,
    certtypeSampleProtection
};

DRM_API DRM_RESULT DRM_CALL DRM_WCP_GetCertificateType(
    __in    const DRM_CHAR             *f_pszBase,
    __in    const DRM_SUBSTRING        *f_pdasstrCert,
    __out   enum  DRM_CERTIFICATE_TYPE *f_pcerttype );

DRM_API DRM_RESULT DRM_CALL DRM_WCP_GetAttribute(
    __in                           const DRM_CHAR                 *f_pszBase,
    __in                           const DRM_SUBSTRING            *f_pdasstrCert,
    __in                                 DRM_WMDRM_CERT_ATTRIBUTE  f_attribute,
    __out_ecount_opt(*f_pcEntries)       DRM_SUBSTRING             f_rgdasstrValue [],
    __inout                              DRM_DWORD                *f_pcEntries );

DRM_API DRM_RESULT DRM_CALL DRM_WCP_GetKeyUsage(
    __in  const DRM_CHAR      *f_pszBase,
    __in  const DRM_SUBSTRING *f_pdasstrCert,
    __out       DRM_DWORD     *f_pdwUsage );

DRM_API DRM_RESULT DRM_CALL DRM_WCP_GetFeatures(
    __in  const DRM_CHAR              *f_pszBase,
    __in  const DRM_SUBSTRING         *f_pdasstrCert,
    __out       DRM_DWORD             *f_pfFeatures );

DRM_API DRM_RESULT DRM_CALL DRM_WCP_GetSecurityLevel(
    __in  const DRM_CHAR      *f_pszBase,
    __in  const DRM_SUBSTRING *f_pdasstrCert,
    __out       DRM_DWORD     *f_pdwSecurityLevel );

DRM_API DRM_RESULT DRM_CALL DRM_WCP_GetPublicKey(
    __in                            const DRM_CHAR              *f_pszBase,
    __in                            const DRM_SUBSTRING         *f_pdasstrCert,
    __out_ecount_opt(*f_pcbModulus)       DRM_BYTE              *f_pbModulus,
    __out                                 DRM_DWORD             *f_pcbModulus );

DRM_API DRM_RESULT DRM_CALL DRM_WCP_GetHardwareID(
    __in                              const DRM_CHAR      *f_pszBase,
    __in                              const DRM_SUBSTRING *f_pdasstrCert,
    __out_ecount(DRM_SHA1_DIGEST_LEN)       DRM_BYTE       f_rgbHardwareID[DRM_SHA1_DIGEST_LEN] );

DRM_API DRM_RESULT DRM_CALL DRM_WCP_GetSignatureDigest(
    __in                              const DRM_CHAR                *f_pszBase,
    __in                              const DRM_SUBSTRING           *f_pdasstrCert,
    __out_ecount(DRM_SHA1_DIGEST_LEN)       DRM_BYTE                 f_rgbDigest[DRM_SHA1_DIGEST_LEN] );

DRM_API DRM_RESULT DRM_CALL DRM_WCP_GetManufacturerNodes(
    __in                           const DRM_CHAR      *f_pszBase,
    __in                           const DRM_SUBSTRING *f_pdasstrCertificate,
    __out_opt                            DRM_SUBSTRING *f_pdasstrNamespace,
    __out_ecount(*f_pcEntries)           DRM_SUBSTRING  f_rgdastrTag        [],
    __out_ecount_opt(*f_pcEntries)       DRM_SUBSTRING  f_rgdasstrAttrLabel [],
    __out_ecount_opt(*f_pcEntries)       DRM_SUBSTRING  f_rgdasstrAttrValue [],
    __out_ecount(*f_pcEntries)           DRM_SUBSTRING  f_rgdasstrValue     [],
    __out                                DRM_DWORD     *f_pcEntries );

#define DRM_WCP_VERIFY_CERT_SIGNATURE     0x00000001
#define DRM_WCP_VERIFY_CERT_REQUIRED_TAGS 0x00000002
#define DRM_WCP_VERIFY_CERT_METHODS       0x00000004
#define DRM_WCP_VERIFY_CERT_ALL      (DRM_WCP_VERIFY_CERT_SIGNATURE|DRM_WCP_VERIFY_CERT_REQUIRED_TAGS|DRM_WCP_VERIFY_CERT_METHODS)

DRM_API DRM_RESULT DRM_CALL DRM_WCP_VerifyCertificate(
    __in                                  const DRM_CHAR            *f_pszBase,
    __in                                  const DRM_SUBSTRING       *f_pdasstrCert,
    __in                                        DRM_DWORD            f_fVerify,
    __in_ecount_opt(f_cRevocationEntries) const WMDRMNET_CRL_ENTRY  *f_pRevocationEntries,
    __in                                        DRM_DWORD            f_cRevocationEntries,
    __out                                       DRM_SUBSTRING       *f_pdasstrPublicRSA,
    __in                                        DRM_CRYPTO_CONTEXT  *f_pCryptoCtx );

DRM_API DRM_RESULT DRM_CALL DRM_WCP_VerifyCertificateCollection(
    __in                                  const DRM_CHAR              *f_pszBase,
    __in                                  const DRM_SUBSTRING         *f_pdasstrCollection,
    __in_opt                              const DRM_ANSI_CONST_STRING *f_pdastrRootPubKey,
    __in_ecount_opt(f_cRevocationEntries) const WMDRMNET_CRL_ENTRY    *f_pRevocationEntries,
    __in                                        DRM_DWORD              f_cRevocationEntries,
    __out_opt                                   DRM_SUBSTRING         *f_pdasstrLeafCertificate,
    __out_opt                                   DRM_SUBSTRING         *f_pdasstrPubkeyMachine,
    __in                                        DRM_CRYPTO_CONTEXT    *f_pCryptoCtx );

DRM_API DRM_RESULT DRM_CALL DRM_WCP_ReadPubKeyModulus(
    __in                    const DRM_CHAR      *f_rgchB64,
    __in                    const DRM_SUBSTRING *f_pdasstrB64,
    __out_ecount(*f_pcbMod)       DRM_BYTE      *f_pbMod,
    __out                         DRM_DWORD     *f_pcbMod );

DRM_API DRM_RESULT DRM_CALL DRM_WCP_VerifyDigitalSignature(
    __in                                  const DRM_CHAR             *f_pszBase,
    __in                                  const DRM_SUBSTRING        *f_pdasstrDataInclusive,
    __in                                  const DRM_SUBSTRING        *f_pdasstrSignatureInclusive,
    __in                                  const DRM_BOOL              f_fWMDRMNET,
    __in_ecount_opt(f_cRevocationEntries) const WMDRMNET_CRL_ENTRY   *f_pRevocationEntries,
    __in                                        DRM_DWORD             f_cRevocationEntries,
    __in                                        DRM_CRYPTO_CONTEXT   *f_pCryptoCtx );

EXIT_PK_NAMESPACE;

#endif /* __DRMCERTPARSER_H__ */
