/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __OEMPARSERS_H__
#define __OEMPARSERS_H__

#include <drmbcrltypes.h>
#include <drmrevocationtypes.h>
#include <drmbcertparsertypes.h>
#include <drmutftypes.h>

ENTER_PK_NAMESPACE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_UTF8_ReadCodePoint8(
    __in     const DRM_CHAR          *f_pchSource,
    __inout        DRM_STRING_WINDOW *f_pdstrwSource,
    __out          DRM_CODE_POINT    *f_pcp );

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_UTF8_VerifyBytes(
    __in_bcount( f_cbData ) const DRM_BYTE  *f_pbData,
    __in                    const DRM_DWORD  f_cbData,
    __in                    const DRM_DWORD  f_iMin,
    __in                    const DRM_DWORD  f_iMax );

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_RVK_FindEntryInRevInfo(
    __in                     const DRM_RLVI    *f_prlvi,
    __in_bcount(f_cbRevInfo) const DRM_BYTE    *f_pbRevInfo,
    __in                           DRM_DWORD    f_cbRevInfo,
    __in                     const DRM_GUID    *f_pguidEntry,
    __out                          DRM_DWORD   *f_pdwVersion ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_RVK_ParseRevocationInfoHeader(
    __in_bcount( f_cbRevInfo ) const DRM_BYTE           *f_pbRevInfo,
    __in                             DRM_DWORD           f_cbRevInfo,
    __out                            DRM_RLVI           *f_pRLVI,
    __inout                          DRM_DWORD          *f_pidxRevInfo ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_RESULT DRM_CALL DRM_RVK_ParseRevocationInfo(
    __in_bcount( f_cbRevInfo ) const DRM_BYTE           *f_pbRevInfo,
    __in                             DRM_DWORD           f_cbRevInfo,
    __out                            DRM_RLVI           *f_pRLVI,
    __out_ecount_opt(1)              DRM_DWORD          *f_pcbSignedBytes ) DRM_NO_INLINE_ATTRIBUTE;

/*********************************************************************
**
**  Parses the unsigned portion of Playready/Silverlight CRL from
**  binary to data structure.
**
**  NOTE: The parser does not make copies of the DRM_RevocationEntry
**        data, it just points to them in the f_pbCrlData buffer so
**        you cannot free the f_pbCrlData and still have a valid f_poCrl
**        data structure.
**
*********************************************************************/

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_BCrl_ParseUnsignedCrl(
    __in_bcount(f_cbCrlData) const DRM_BYTE       *f_pbCrlData,
    __in                     const DRM_DWORD       f_cbCrlData,
    __out                    DRM_DWORD            *f_pcbSignedMessageLength,
    __out                    DRM_BCRL             *f_poCrl ) DRM_NO_INLINE_ATTRIBUTE;

/*********************************************************************
**
**  Parses the entire Playready/Silverlight CRL from
**  binary to data structure.
**
**  NOTE: The parser does not make copies of the DRM_RevocationEntry
**        data, it just points to them in the f_pbCrlData buffer so
**        you cannot free the f_pbCrlData and still have a valid f_poCrl
**        data structure.
**
*********************************************************************/

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_BCrl_ParseSignedCrl(
    __in_bcount(f_cbCrlData) const DRM_BYTE        *f_pbCrlData,
    __in                     const DRM_DWORD        f_cbCrlData,
    __out_ecount_opt(1)            DRM_DWORD       *f_pcbSignedMessageLength,
    __out                          DRM_BCRL_Signed *f_poCrl ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_BCert_InitVerificationContext(
    __in_opt                        const DRMFILETIME                   *f_pftExpirationTime,
    __in_opt                        const PUBKEY_P256                   *f_pRootPubKey,
    __in                            const DRM_DWORD                      f_dwCertType,
    __in_opt                              DRM_CRYPTO_CONTEXT            *f_pCryptoCtx,
    __in                                  DRM_BOOL                       f_fVerifyCertSignatures,
    __in                                  DRM_BOOL                       f_fDontFailOnMissingExtData,
    __in_ecount_opt(f_NumKeyUsages) const DRM_DWORD                     *f_pKeyUsages,
    __in                                  DRM_DWORD                      f_NumKeyUsages,
    __in                                  DRM_BOOL                       f_fCollectErrs,
    __in_opt                              DRM_BB_CONTEXT                *f_pcontextBBX,
    __in_opt                              DRM_SECSTORE_CONTEXT          *f_pcontextSST,
    __in_opt                              DRM_DST                       *f_pDatastore,
    __inout                               DRM_BCERT_VERIFICATIONCONTEXT *f_pVerificationContext );

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_BCert_ParseRawCertificate(
    __in_bcount(f_cbCertData) const DRM_BYTE                *f_pbCertData,
    __in                      const DRM_DWORD               f_cbCertData,
    __inout_ecount(1)         DRM_DWORD                     *f_pbOffset,
    __inout_ecount_opt(1)     DRM_BCERT_CERTIFICATE         *f_poCertificate,
    __inout_ecount_opt(1)     DRM_BCERT_MINIMALDATA         *f_poMinCertData,
    __inout_ecount(1)         DRM_BCERT_VERIFICATIONCONTEXT *f_pVerificationContext );

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_BCert_parseManufacturerInfo(
    __in_bcount(f_cbCertData) const DRM_BYTE                *f_pbCertData,
    __in                      const DRM_DWORD               f_cbCertData,
    __inout_ecount(1)         DRM_DWORD                     *f_pbOffset,
    __inout_ecount_opt(1)     DRM_BCERT_MANUFACTURER_INFO   *f_poManufacturerInfo,
    __inout_ecount(1)         DRM_BCERT_VERIFICATIONCONTEXT *f_pVerificationContext );

DRM_API DRM_RESULT DRM_CALL DRM_BCert_GetCertificate(
    __in_bcount(f_cbCertData) const DRM_BYTE        *f_pbCertData,
    __in                      const DRM_DWORD       f_cbCertData,
    __inout_ecount(1)         DRM_DWORD             *f_pbOffset,
    __inout_ecount_opt(1)     DRM_BCERT_CERTIFICATE *f_poCertificate,
    __in                      const DRM_DWORD        f_dwRequiredCertType );

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_BCert_VerifyChildUsage(
    __in const DRM_DWORD f_dwChildKeyUsageMask,
    __in const DRM_DWORD f_dwParentKeyUsageMask );

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_BCert_getObjectHeader(
    __in_bcount(f_cbCertData) const DRM_BYTE          *f_pbCertData,
    __in                      const DRM_DWORD         f_cbCertData,
    __inout_ecount(1)         DRM_DWORD               *f_pbOffset,
    __inout_ecount(1)         DRM_BCERT_OBJECT_HEADER *f_poHeader );

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_BCert_parseCertHeader(
    __in_bcount(f_cbCertData) const DRM_BYTE   *f_pbCertData,
    __in                      const DRM_DWORD   f_cbCertData,
    __inout_ecount(1)         DRM_DWORD        *f_pbOffset,
    __inout_ecount(1)         DRM_BCERT_HEADER *f_poCertHeader,
    __inout_ecount(1)         DRM_BCERT_VERIFICATIONCONTEXT *f_pVerificationContext );

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_BCert_parseSecurityVersion(
    __in_bcount(f_cbCertData) const DRM_BYTE                *f_pbCertData,
    __in                      const DRM_DWORD                f_cbCertData,
    __inout_ecount(1)         DRM_DWORD                     *f_pbOffset,
    __inout_ecount_opt(1)     DRM_BCERT_SECURITY_VERSION    *f_poSecurityVersion,
    __inout_ecount_opt(1)     DRM_BCERT_SECURITY_VERSION    *f_poSecurityVersion2,
    __inout_ecount(1)         DRM_BCERT_VERIFICATIONCONTEXT *f_pVerificationContext );

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_BCert_parseSignatureInfo(
    __in_bcount(f_cbCertData) const DRM_BYTE                 *f_pbCertData,
    __in                      const DRM_DWORD                f_cbCertData,
    __inout_ecount(1)         DRM_DWORD                      *f_pbOffset,
    __inout_ecount(1)         DRM_BCERT_SIGNATURE_INFO       *f_poSignatureInfo,
    __inout_ecount(1)         DRM_BCERT_VERIFICATIONCONTEXT  *f_pVerificationContext );

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_BCert_parseKeyInfo(
    __in_bcount(f_cbCertData) const DRM_BYTE                *f_pbCertData,
    __in                      const DRM_DWORD               f_cbCertData,
    __inout_ecount(1)         DRM_DWORD                     *f_pbOffset,
    __in const                DRM_DWORD                     f_dwCertType,
    __inout_ecount(1)         DRM_BCERT_KEY_INFO            *f_poKeyInfo,
    __inout_ecount(1)         DRM_BCERT_VERIFICATIONCONTEXT *f_pVerificationContext );

EXIT_PK_NAMESPACE;

#endif /* __OEMPARSERS_H__ */

