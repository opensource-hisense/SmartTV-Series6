/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRMBCERTPARSERTYPES_H__
#define __DRMBCERTPARSERTYPES_H__

#include <drmtypes.h>
#include <drmbcert.h>
#include <drmblackboxtypes.h>

ENTER_PK_NAMESPACE;

/*
** Minimal length of a certificate chain in bytes - 20
*/
#define DRM_MIN_CERT_CHAIN_LEN ( SIZEOF( DRM_DWORD )   /* Header Constant */ \
                               + SIZEOF( DRM_DWORD )   /* Version */ \
                               + SIZEOF( DRM_DWORD )   /* Length */ \
                               + SIZEOF( DRM_DWORD )   /* Flags */ \
                               + SIZEOF( DRM_DWORD ) ) /* No of certificate entries: zero for minimal cert chain */

/*
** Defines for verification of object lengths in object headers
*/
#define DRM_BCERT_SIGNATURE_OBJECT_LEN ( SIZEOF( DRM_BCERT_OBJECT_HEADER )   /* Object header */ \
                                        + SIZEOF( DRM_DWORD )      /* Signature type and length */ \
                                        + SIZEOF( SIGNATURE_P256 ) /* Signature data */ \
                                        + SIZEOF( DRM_DWORD )      /* Issuer key length */ \
                                        + SIZEOF( PUBKEY_P256 ) )  /* Issuer key data */

#define DRM_BCERT_BASIC_INFO_OBJECT_LEN ( SIZEOF( DRM_BCERT_OBJECT_HEADER )  /* Object header */ \
                                        + DRM_BCERT_CERT_ID_LENGTH      /* Certificate ID */ \
                                        + SIZEOF( DRM_DWORD )           /* Security level */ \
                                        + SIZEOF( DRM_DWORD )           /* Certificate Flags */ \
                                        + SIZEOF( DRM_DWORD )           /* Type */ \
                                        + SHA256_DIGEST_SIZE_IN_BYTES   /* Digest Value */ \
                                        + SIZEOF( DRM_DWORD )           /* Expiration Date */ \
                                        + DRM_BCERT_CLIENT_ID_LENGTH )  /* Client ID */

#define DRM_BCERT_DEVICE_INFO_OBJECT_LEN ( SIZEOF( DRM_BCERT_OBJECT_HEADER ) /* Object header */ \
                                        + SIZEOF( DRM_DWORD )         /* Max License Size */ \
                                        + SIZEOF( DRM_DWORD )         /* Max Header Size */ \
                                        + SIZEOF( DRM_DWORD ) )       /* Max License Chain Depth */

#define DRM_BCERT_FEATURES_OBJECT_MIN_LEN ( SIZEOF( DRM_BCERT_OBJECT_HEADER ) /* Object header */ \
                                          + SIZEOF( DRM_DWORD ) )   /* Number of features: zero for minimal feature info */

#define DRM_BCERT_KEY_OBJECT_MIN_LEN ( SIZEOF( DRM_BCERT_OBJECT_HEADER ) /* Object header */ \
                                     + SIZEOF( DRM_WORD )                /* Type */ \
                                     + SIZEOF( DRM_WORD )                /* Length */ \
                                     + SIZEOF( DRM_DWORD )               /* Flags */ \
                                     + ECC_P256_POINT_SIZE_IN_BYTES      /* Value */ \
                                     + SIZEOF( DRM_DWORD )               /* Number of Entries */ \
                                     + SIZEOF( DRM_DWORD ) )             /* One entry */

/*
** Minimal length of a certificate:
** Cert header, Basic Info, Feature Info with zero features,
** Key Info and Signature Info.
*/
#define DRM_MIN_CERTIFICATE_LEN ( SIZEOF( DRM_BCERT_HEADER )         \
                                + SIZEOF( DRM_BCERT_BASIC_INFO )     \
                                + DRM_BCERT_FEATURES_OBJECT_MIN_LEN  \
                                + DRM_BCERT_KEY_OBJECT_MIN_LEN       \
                                + DRM_BCERT_SIGNATURE_OBJECT_LEN )


/*
** Minimal information to keep after a single certificate is parsed,
** which is needed verify the whole certificate chain.
*/
typedef struct __tagDRM_BCertMinimalData {
    DRM_BCERT_HEADER             oCertHeader;
    DRM_BCERT_BASIC_INFO         oBasicInfo;
    DRM_BCERT_PUBKEY             oIssuerKey;
    DRM_BCERT_FEATURE_INFO       oFeatureInfo;
    DRM_BCERT_KEY_INFO           oKeyInfo;
    DRM_BCERT_SIGNATURE_INFO     oSignatureInfo;
    DRM_BCERT_SECURITY_VERSION   oSecurityVersion;
    DRM_BCERT_SECURITY_VERSION   oSecurityVersion2;
} DRM_BCERT_MINIMALDATA;

/*
** Parsing error presentation, used in validation context structure.
*/
typedef struct {
    /*
    ** Number of the cert in the chain, zero-based with leaf cert as 0
    */
    DRM_DWORD   cCertNumber;
    /*
    ** Error code
    */
    DRM_RESULT  dwResult;
} DRM_BCERT_VERIFICATIONRESULT;

#define DRM_MAX_VERIFICATIONRESULTS 10

/*
** Validation context: structure that controls certificate parser behavior.
** On exit it may contain a list of parsing errors.
*/
typedef struct {
    /*
    ** [in] The latest expiration time of the cert chain - if 0 then don't verify it
    */
    DRMFILETIME        ftExpirationTime;
    /*
    ** [in] Pointer to a public key of the cert chain root - if NULL then skip this verification
    */
    const PUBKEY_P256  *pRootPubKey;
    /*
    ** [in] Expected leaf certificate type - if DRM_BCERT_CERTTYPE_UNKNOWN then don't verify
    */
    DRM_DWORD          dwType;
    /*
    ** [in] Context for crypto operations
    */
    DRM_CRYPTO_CONTEXT *pCryptoCtx;
    /*
    ** [in] Blackbox context for certificate caching
    */
    DRM_BB_CONTEXT *pBlackboxCtx;
    /*
    ** [in] Secure store context for certificate caching
    */
    DRM_SECSTORE_CONTEXT *pSecStoreCtx;
    /*
    ** [in] Datastore context for certificate caching
    */
    DRM_DST *pDSTCtx;
    /*
    ** [in] Set into TRUE if parser should verify cert signatures up the chain
    */
    DRM_BOOL           fVerifyCertSignatures;
    /*
    ** [in] Set into FALSE if parser should ignore absense of extended data and don't verify signature over it
    */
    DRM_BOOL           fDontFailOnMissingExtData;
    /*
    ** [in] Array of key usages that must be found in a leaf certificate,
    **      otherwise error out with DRM_E_BCERT_REQUIRED_KEYUSAGE_MISSING
    */
    DRM_DWORD          rgdwRequiredKeyUsages[DRM_BCERT_MAX_KEY_USAGES];
    /*
    ** [in] Actual number of elements in rgdwRequiredKeyUsages
    */
    DRM_DWORD          cRequiredKeyUsages;
    /*
    ** [in] If set into TRUE then parser will store non-fatal parser errors in array, keep parsing
    **      and return DRM_E_BCERT_VERIFICATION_ERRORS unless this is overriden by a fatal error
    **      (i.e. error after which the cert parsing cannot continue, for instance, length overflow)
    **      If set into FALSE then parsing stops immediately after any error.
    ** By default this field is FALSE.
    */
    DRM_BOOL           fCollectErrorsInArrayAndContinue;
    /*
    ** [out] Array to store and return non-fatal verification errors.
    */
    DRM_BCERT_VERIFICATIONRESULT rgoResults[ DRM_MAX_VERIFICATIONRESULTS ];
    /*
    ** [out] Actual number of members in rgoResults array, should be <= DRM_MAX_VERIFICATIONRESULTS
    */
    DRM_DWORD                    cResults;
    /*
    ** [out] Number of a currently parsed certificate, zero-based with leaf cert as 0
    */
    DRM_DWORD                    cCurrentCert;
    /*
    ** [out] Offsets of each certificate in the chain that have been parsed.
    */
    DRM_DWORD                    rgdwCertificateOffsets[DRM_BCERT_MAX_CERTS_PER_CHAIN];
    /*
    ** [out] The expiration of the earliest expiring certificate in the chain, i.e. when the entire chain expires.
    */
    DRM_DWORD                    dwCertificateChainExpiration;
} DRM_BCERT_VERIFICATIONCONTEXT;

#define DRM_BCert_GetLeafSecurityLevel(secLevel, chain) \
    NETWORKBYTES_TO_DWORD( (secLevel), (chain), SIZEOF( DRM_BCERT_CHAIN_HEADER )  \
                                              + SIZEOF( DRM_BCERT_HEADER )        \
                                              + SIZEOF( DRM_BCERT_OBJECT_HEADER ) \
                                              + SIZEOF( DRM_BCERT_CERT_ID ) );


#define BCERT_KEYUSAGE_PARENT_ISSUERS_MASK                          \
    ( BCERT_KEYUSAGE_BIT( DRM_BCERT_KEYUSAGE_ISSUER_INDIV )         \
    | BCERT_KEYUSAGE_BIT( DRM_BCERT_KEYUSAGE_ISSUER_DEVICE )        \
    | BCERT_KEYUSAGE_BIT( DRM_BCERT_KEYUSAGE_ISSUER_LINK )          \
    | BCERT_KEYUSAGE_BIT( DRM_BCERT_KEYUSAGE_ISSUER_DOMAIN )        \
    | BCERT_KEYUSAGE_BIT( DRM_BCERT_KEYUSAGE_ISSUER_SILVERLIGHT )   \
    | BCERT_KEYUSAGE_BIT( DRM_BCERT_KEYUSAGE_ISSUER_APPLICATION )   \
    | BCERT_KEYUSAGE_BIT( DRM_BCERT_KEYUSAGE_ISSUER_CRL )           \
    | BCERT_KEYUSAGE_BIT( DRM_BCERT_KEYUSAGE_ISSUER_SIGN_KEYFILE )  \
    | BCERT_KEYUSAGE_BIT( DRM_BCERT_KEYUSAGE_ISSUER_METERING )      \
    | BCERT_KEYUSAGE_BIT( DRM_BCERT_KEYUSAGE_ISSUER_SIGN_LICENSE ) )

#define DRM_BCERT_CHKVERIFICATIONERR( pVerificationCtx, fCondition, dwErr )                                         \
do {                                                                                                                \
    if ( !(fCondition) )                                                                                            \
    {                                                                                                               \
        if ( pVerificationCtx->fCollectErrorsInArrayAndContinue == FALSE                                            \
            || pVerificationCtx->cResults >= DRM_MAX_VERIFICATIONRESULTS )                                          \
        {                                                                                                           \
            TRACE( ( "CERT ERROR %s : %d\n", __FILE__, __LINE__ ) ); \
            ChkDR(dwErr);                                                                                           \
        }                                                                                                           \
        else                                                                                                        \
        {                                                                                                           \
            pVerificationCtx->rgoResults[pVerificationCtx->cResults].cCertNumber = pVerificationCtx->cCurrentCert;  \
            pVerificationCtx->rgoResults[pVerificationCtx->cResults++].dwResult = (dwErr);                          \
        }                                                                                                           \
    }                                                                                                               \
} while(FALSE)

EXIT_PK_NAMESPACE;

#endif /* __DRMBCERTPARSERTYPES_H__ */

