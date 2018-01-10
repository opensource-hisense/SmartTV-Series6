/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRMBCRL_H__
#define __DRMBCRL_H__

#include <drmbcrltypes.h>
#include <oemcryptoctx.h>
#include <oemeccp256.h>
#include <oemparsers.h>
#include <drmblackbox.h>
#include <drmrevocationtypes.h>

ENTER_PK_NAMESPACE;

/*********************************************************************
**
**  Used to validate the signature on instances of a PlayReady
**  Binary CRL or RevInfoV2, both of which use the same type of
**  certificate chain and signature structure.
**
*********************************************************************/

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_BCrl_VerifySignature(
    __in_bcount(f_cbSignedBytes)      const DRM_BYTE               *f_pbSignedBytes,
    __in                                    DRM_DWORD               f_cbSignedBytes,
    __in_bcount(f_cbSignature)              DRM_BYTE               *f_pbSignature,
    __in                                    DRM_DWORD               f_cbSignature,
    __in_bcount(f_cbCertificateChain) const DRM_BYTE               *f_pbCertificateChain,
    __in                                    DRM_DWORD               f_cbCertificateChain,
    __in_ecount(1)                    const PUBKEY_P256            *f_pRootPubkey,
    __in                                    DRM_CRYPTO_CONTEXT     *f_pCryptoCtx,
    __in_opt                                DRM_BB_CONTEXT         *f_pcontextBBX,
    __in_opt                                DRM_SECSTORE_CONTEXT   *f_pcontextSST,
    __in_opt                                DRM_DST                *f_pDatastore );

/*********************************************************************
**
**  Parses Playready/Silverlight CRL from binary to data structure.
**  Verifies signature and certificate chain.
**
**  NOTE: The parser does not make copies of the DRM_RevocationEntry
**        data, it just points to them in the f_pbCrlData buffer so
**        you cannot free the f_pbCrlData and still have a valid f_poCrl
**        data structure.
**
*********************************************************************/

DRM_API DRM_RESULT DRM_CALL DRM_BCrl_ParseCrl(
 __in_bcount(f_cbCrlData) const DRM_BYTE *f_pbCrlData,
 __in                     const DRM_DWORD f_cbCrlData,
 __out                    DRM_BCRL_Signed *f_poCrl,
 __in_ecount(1)           const PUBKEY_P256  *f_pRootPubkey,
 __inout                  DRM_CRYPTO_CONTEXT *f_pCryptoCtx,
 __in_opt                 DRM_BB_CONTEXT     *f_pcontextBBX,
 __in_opt                 DRM_SECSTORE_CONTEXT *f_pcontextSST,
 __in_opt                 DRM_DST            *f_pDatastore
) DRM_NO_INLINE_ATTRIBUTE;

/*********************************************************************
**
**  Checks to see if the given certificate is in the given CRL file.
**  Internally the API uses the DRM_BCrl_ParseCrl method to parse
**  and verify the CRL.  Then it walks through the entries in the CRL
**  to see if the given certificate is revoked.  The API returns
**  DRM_E_CERTIFICATE_REVOKED if any certificate in the chain is revoked.
**
*********************************************************************/

PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_PARAM_25004, "Prefast Noise: DRM_CRYPTO_CONTEXT* should not be const.")
DRM_API DRM_RESULT DRM_CALL DRM_BCrl_CheckIfPlayReadyCertRevoked
(
    __in_bcount(f_cbPlayReadyCert)const DRM_BYTE            *f_pbPlayReadyCert,
    __in                                DRM_DWORD           f_cbPlayReadyCert,
    __in_bcount(f_cbPlayReadyCRL) const DRM_BYTE           *f_pbPlayReadyCRL,
    __in                                DRM_DWORD           f_cbPlayReadyCRL,
    __out_opt                           DRM_SHA256_Digest  *f_pRevokedCertDigest,
    __out_opt                           DRM_DWORD          *f_pdwPlayReadyCRLVer,
    __inout                             DRM_CRYPTO_CONTEXT *f_pCryptoCtx,
    __in_opt                            DRM_BB_CONTEXT     *f_pcontextBBX,
    __in_opt                            DRM_SECSTORE_CONTEXT   *f_pcontextSST,
    __in_opt                            DRM_DST            *f_pDatastore
);
PREFAST_POP /* __WARNING_NONCONST_PARAM_25004 */

EXIT_PK_NAMESPACE;

#endif /* __DRMBCRL_H__ */


