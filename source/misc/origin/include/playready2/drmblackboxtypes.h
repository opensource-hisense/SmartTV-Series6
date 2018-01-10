/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRMBLACKBOXTYPES_H__
#define __DRMBLACKBOXTYPES_H__

#include <drmxmr.h>
#include <drmlicense.h>
#include <drmdomainstoretypes.h>
#include <drmbcertparsercache.h>
#include <drmdevcerttypes.h>
#include <drmkeyfiletypes.h>

#include <oemcommon.h>
#include <oemhalbasic.h>
#include <oemeccp256.h>
#include <oemcryptoctx.h>

ENTER_PK_NAMESPACE;

/*
** Defines minimum register size of each key type that a black box requires in order to function correctly.
*/
#define OEM_BB_KEYMAP_MIN_REQUIRED_SIZE_ECC_P256_CONTENT_ENCRYPT                   5
#define OEM_BB_KEYMAP_MIN_REQUIRED_SIZE_ECC_P256_DOMAIN_ENCRYPT                    5
#define OEM_BB_KEYMAP_MIN_REQUIRED_SIZE_ECC_P256_MESSAGE_ENCRYPT                   5
#define OEM_BB_KEYMAP_MIN_REQUIRED_SIZE_ECC_P256_SIGN                              5
#define OEM_BB_KEYMAP_MIN_REQUIRED_SIZE_ECC_P256_PUBLIC                            5
#define OEM_BB_KEYMAP_MIN_REQUIRED_SIZE_ECC_P256_MODEL_SIGN                        5
#define OEM_BB_KEYMAP_MIN_REQUIRED_SIZE_AES_ECB_ROOT                               5
#define OEM_BB_KEYMAP_MIN_REQUIRED_SIZE_AES_CTR_CONTENT                            100    /* Enough for agressive key-rotation pre-buffering. */
#define OEM_BB_KEYMAP_MIN_REQUIRED_SIZE_AES_ECB_MESSAGE_ENCRYPT                    5
#define OEM_BB_KEYMAP_MIN_REQUIRED_SIZE_AES_ECB_DOMAIN_PROTECT                     5
#define OEM_BB_KEYMAP_MIN_REQUIRED_SIZE_AES_OMAC1_SECURE_STORE                     5
#define OEM_BB_KEYMAP_MIN_REQUIRED_SIZE_AES_KEYFILE                                5
#define OEM_BB_KEYMAP_MIN_REQUIRED_SIZE_AES_GENERIC_KEY_CONTENT                    5
#define OEM_BB_KEYMAP_MIN_REQUIRED_SIZE_AES_GENERIC_KEY_ROOT                       5
#define OEM_BB_KEYMAP_MIN_REQUIRED_SIZE_AES_ECB_NEW_LICENSE_ROOT                   5
#define OEM_BB_KEYMAP_MIN_REQUIRED_SIZE_AES_CTR_NEW_LICENSE_CONTENT                100    /* Enough for agressive key-rotation pre-buffering. */
#define OEM_BB_KEYMAP_MIN_REQUIRED_SIZE_LEGACY                                     5
#define OEM_BB_KEYMAP_MIN_REQUIRED_SIZE_SLK                                        5

/*
** Defines how many register entries can be cached per each key type.
*/
#define OEM_BB_KEYMAP_CACHE_HEADROOM_SIZE_ECC_P256_CONTENT_ENCRYPT                 5
#define OEM_BB_KEYMAP_CACHE_HEADROOM_SIZE_ECC_P256_DOMAIN_ENCRYPT                  5
#define OEM_BB_KEYMAP_CACHE_HEADROOM_SIZE_ECC_P256_MESSAGE_ENCRYPT                 5
#define OEM_BB_KEYMAP_CACHE_HEADROOM_SIZE_ECC_P256_SIGN                            5
#define OEM_BB_KEYMAP_CACHE_HEADROOM_SIZE_ECC_P256_PUBLIC                          5
#define OEM_BB_KEYMAP_CACHE_HEADROOM_SIZE_ECC_P256_MODEL_SIGN                      5
#define OEM_BB_KEYMAP_CACHE_HEADROOM_SIZE_AES_ECB_ROOT                             5
#define OEM_BB_KEYMAP_CACHE_HEADROOM_SIZE_AES_CTR_CONTENT                          5
#define OEM_BB_KEYMAP_CACHE_HEADROOM_SIZE_AES_ECB_MESSAGE_ENCRYPT                  5
#define OEM_BB_KEYMAP_CACHE_HEADROOM_SIZE_AES_ECB_DOMAIN_PROTECT                   5
#define OEM_BB_KEYMAP_CACHE_HEADROOM_SIZE_AES_OMAC1_SECURE_STORE                   5
#define OEM_BB_KEYMAP_CACHE_HEADROOM_SIZE_AES_KEYFILE                              5
#define OEM_BB_KEYMAP_CACHE_HEADROOM_SIZE_AES_GENERIC_KEY_CONTENT                  5
#define OEM_BB_KEYMAP_CACHE_HEADROOM_SIZE_AES_GENERIC_KEY_ROOT                     5
#define OEM_BB_KEYMAP_CACHE_HEADROOM_SIZE_AES_ECB_NEW_LICENSE_ROOT                 5
#define OEM_BB_KEYMAP_CACHE_HEADROOM_SIZE_AES_CTR_NEW_LICENSE_CONTENT              5
#define OEM_BB_KEYMAP_CACHE_HEADROOM_SIZE_LEGACY                                   5
#define OEM_BB_KEYMAP_CACHE_HEADROOM_SIZE_SLK                                      5

/*
** Defines total key register size per key type.
*/
#define OEM_BB_KEYMAP_SIZE_ECC_P256_CONTENT_ENCRYPT     ( OEM_BB_KEYMAP_MIN_REQUIRED_SIZE_ECC_P256_CONTENT_ENCRYPT      + OEM_BB_KEYMAP_CACHE_HEADROOM_SIZE_ECC_P256_CONTENT_ENCRYPT )
#define OEM_BB_KEYMAP_SIZE_ECC_P256_DOMAIN_ENCRYPT      ( OEM_BB_KEYMAP_MIN_REQUIRED_SIZE_ECC_P256_DOMAIN_ENCRYPT       + OEM_BB_KEYMAP_CACHE_HEADROOM_SIZE_ECC_P256_DOMAIN_ENCRYPT )
#define OEM_BB_KEYMAP_SIZE_ECC_P256_MESSAGE_ENCRYPT     ( OEM_BB_KEYMAP_MIN_REQUIRED_SIZE_ECC_P256_MESSAGE_ENCRYPT      + OEM_BB_KEYMAP_CACHE_HEADROOM_SIZE_ECC_P256_MESSAGE_ENCRYPT )
#define OEM_BB_KEYMAP_SIZE_ECC_P256_SIGN                ( OEM_BB_KEYMAP_MIN_REQUIRED_SIZE_ECC_P256_SIGN                 + OEM_BB_KEYMAP_CACHE_HEADROOM_SIZE_ECC_P256_SIGN )
#define OEM_BB_KEYMAP_SIZE_ECC_P256_PUBLIC              ( OEM_BB_KEYMAP_MIN_REQUIRED_SIZE_ECC_P256_PUBLIC               + OEM_BB_KEYMAP_CACHE_HEADROOM_SIZE_ECC_P256_PUBLIC )
#define OEM_BB_KEYMAP_SIZE_ECC_P256_MODEL_SIGN          ( OEM_BB_KEYMAP_MIN_REQUIRED_SIZE_ECC_P256_MODEL_SIGN           + OEM_BB_KEYMAP_CACHE_HEADROOM_SIZE_ECC_P256_MODEL_SIGN )
#define OEM_BB_KEYMAP_SIZE_AES_ECB_ROOT                 ( OEM_BB_KEYMAP_MIN_REQUIRED_SIZE_AES_ECB_ROOT                  + OEM_BB_KEYMAP_CACHE_HEADROOM_SIZE_AES_ECB_ROOT )
#define OEM_BB_KEYMAP_SIZE_AES_CTR_CONTENT              ( OEM_BB_KEYMAP_MIN_REQUIRED_SIZE_AES_CTR_CONTENT               + OEM_BB_KEYMAP_CACHE_HEADROOM_SIZE_AES_CTR_CONTENT )
#define OEM_BB_KEYMAP_SIZE_AES_ECB_MESSAGE_ENCRYPT      ( OEM_BB_KEYMAP_MIN_REQUIRED_SIZE_AES_ECB_MESSAGE_ENCRYPT       + OEM_BB_KEYMAP_CACHE_HEADROOM_SIZE_AES_ECB_MESSAGE_ENCRYPT )
#define OEM_BB_KEYMAP_SIZE_AES_ECB_DOMAIN_PROTECT       ( OEM_BB_KEYMAP_MIN_REQUIRED_SIZE_AES_ECB_DOMAIN_PROTECT        + OEM_BB_KEYMAP_CACHE_HEADROOM_SIZE_AES_ECB_DOMAIN_PROTECT )
#define OEM_BB_KEYMAP_SIZE_AES_OMAC1_SECURE_STORE       ( OEM_BB_KEYMAP_MIN_REQUIRED_SIZE_AES_OMAC1_SECURE_STORE        + OEM_BB_KEYMAP_CACHE_HEADROOM_SIZE_AES_OMAC1_SECURE_STORE )
#define OEM_BB_KEYMAP_SIZE_AES_KEYFILE                  ( OEM_BB_KEYMAP_MIN_REQUIRED_SIZE_AES_KEYFILE                   + OEM_BB_KEYMAP_CACHE_HEADROOM_SIZE_AES_KEYFILE )
#define OEM_BB_KEYMAP_SIZE_AES_GENERIC_KEY_CONTENT      ( OEM_BB_KEYMAP_MIN_REQUIRED_SIZE_AES_GENERIC_KEY_CONTENT       + OEM_BB_KEYMAP_CACHE_HEADROOM_SIZE_AES_GENERIC_KEY_CONTENT )
#define OEM_BB_KEYMAP_SIZE_AES_GENERIC_KEY_ROOT         ( OEM_BB_KEYMAP_MIN_REQUIRED_SIZE_AES_GENERIC_KEY_ROOT          + OEM_BB_KEYMAP_CACHE_HEADROOM_SIZE_AES_GENERIC_KEY_ROOT )
#define OEM_BB_KEYMAP_SIZE_AES_ECB_NEW_LICENSE_ROOT     ( OEM_BB_KEYMAP_MIN_REQUIRED_SIZE_AES_ECB_NEW_LICENSE_ROOT      + OEM_BB_KEYMAP_CACHE_HEADROOM_SIZE_AES_ECB_NEW_LICENSE_ROOT )
#define OEM_BB_KEYMAP_SIZE_AES_CTR_NEW_LICENSE_CONTENT  ( OEM_BB_KEYMAP_MIN_REQUIRED_SIZE_AES_CTR_NEW_LICENSE_CONTENT   + OEM_BB_KEYMAP_CACHE_HEADROOM_SIZE_AES_CTR_NEW_LICENSE_CONTENT )
#define OEM_BB_KEYMAP_SIZE_LEGACY                       ( OEM_BB_KEYMAP_MIN_REQUIRED_SIZE_LEGACY                        + OEM_BB_KEYMAP_CACHE_HEADROOM_SIZE_LEGACY )
#define OEM_BB_KEYMAP_SIZE_SLK                          ( OEM_BB_KEYMAP_MIN_REQUIRED_SIZE_SLK                           + OEM_BB_KEYMAP_CACHE_HEADROOM_SIZE_SLK )

/*
** Defines preloaded key register size per key type.
*/
#define OEM_BB_PRELOAD_LOOKUP_SIZE_ECC_P256_PUBLIC                                 1
#define OEM_BB_PRELOAD_LOOKUP_SIZE_ECC_P256_MODEL_SIGN                             1
#define OEM_BB_PRELOAD_LOOKUP_SIZE_AES_KEYFILE                                     5

typedef enum
{
    eDRM_BB_KEY_REGISTER_STATE_UNALLOCATED = 0, /* No Register has been allocated from the HAL         */
    eDRM_BB_KEY_REGISTER_STATE_PRELOADED   = 1, /* The register contains a preloaded key               */
    eDRM_BB_KEY_REGISTER_STATE_UNASSIGNED  = 2, /* A Register has been allocated but is not in use     */
    eDRM_BB_KEY_REGISTER_STATE_IN_USE      = 3, /* The register is in use                              */
} DRM_BB_KEY_REGISTER_STATE;

#define DRM_BB_MAX_CACHE_KEY_SIZE_IN_BYTES      (ECC_P256_CIPHERTEXT_SIZE_IN_BYTES)

#define DRM_BB_KEY_REGISTER_ENTRY_INDEX_INVALID (-1)

typedef DRM_OBFUS_FIXED_ALIGN struct __tagDRM_BB_KEY_REGISTER_ENTRY
{
    OEM_HAL_KEY_TYPE           eType;
    DRM_BB_KEY_REGISTER_STATE  eState;
    OEM_HAL_KEY_REGISTER_INDEX indexKeyRegister;
    DRM_LONG                   indexPreloadedTable;
    DRM_DWORD                  dwRefCount;
    DRM_BYTE                   pbCacheKey[ DRM_BB_MAX_CACHE_KEY_SIZE_IN_BYTES ]; /* Key used for cache lookup */
    DRM_DWORD                  cbCacheKey;                                       /* Size of pbCacheLookupKey in bytes */
    DRM_DWORD                  dwUnwrapTimestamp;                                /* Timestamp of the last _Hal_UnwrapKey call  */
} DRM_BB_KEY_REGISTER_ENTRY;


typedef DRM_OBFUS_FIXED_ALIGN struct __tagDRM_BB_KEY_REGISTER_TABLE
{
    DRM_LONG                   cEntries;
DRM_OBFUS_FILL_BYTES(4)
DRM_OBFUS_PTR_TOP
    DRM_BB_KEY_REGISTER_ENTRY *pEntries;
DRM_OBFUS_PTR_BTM
    DRM_LONG                   cPreloadedIds;
DRM_OBFUS_FILL_BYTES(4)
DRM_OBFUS_PTR_TOP
    DRM_GUID                  *pPreloadedIds;
DRM_OBFUS_PTR_BTM
} DRM_BB_KEY_REGISTER_TABLE;


typedef DRM_OBFUS_FIXED_ALIGN struct __tagDRM_BB_KEY_HANDLE_STATE
{
    DRM_BB_KEY_REGISTER_ENTRY rgKeyMapEccP256ContentEncrypt[OEM_BB_KEYMAP_SIZE_ECC_P256_CONTENT_ENCRYPT];
    DRM_BB_KEY_REGISTER_ENTRY rgKeyMapEccP256DomainEncrypt[OEM_BB_KEYMAP_SIZE_ECC_P256_CONTENT_ENCRYPT];
    DRM_BB_KEY_REGISTER_ENTRY rgKeyMapEccP256MessageEncrypt[OEM_BB_KEYMAP_SIZE_ECC_P256_MESSAGE_ENCRYPT];
    DRM_BB_KEY_REGISTER_ENTRY rgKeyMapEccP256Sign[OEM_BB_KEYMAP_SIZE_ECC_P256_SIGN];
    DRM_BB_KEY_REGISTER_ENTRY rgKeyMapEccP256Public[OEM_BB_KEYMAP_SIZE_ECC_P256_PUBLIC];
    DRM_BB_KEY_REGISTER_ENTRY rgKeyMapEccP256ModelSign[OEM_BB_KEYMAP_SIZE_ECC_P256_MODEL_SIGN];
    DRM_BB_KEY_REGISTER_ENTRY rgKeyMapAesEcbRoot[OEM_BB_KEYMAP_SIZE_AES_ECB_ROOT];
    DRM_BB_KEY_REGISTER_ENTRY rgKeyMapAesCtrContent[OEM_BB_KEYMAP_SIZE_AES_CTR_CONTENT];
    DRM_BB_KEY_REGISTER_ENTRY rgKeyMapAesEcbMessageEncrypt[OEM_BB_KEYMAP_SIZE_AES_ECB_MESSAGE_ENCRYPT];
    DRM_BB_KEY_REGISTER_ENTRY rgKeyMapAesEcbDomainProtect[OEM_BB_KEYMAP_SIZE_AES_ECB_DOMAIN_PROTECT];
    DRM_BB_KEY_REGISTER_ENTRY rgKeyMapAesOmac1SecureStore[OEM_BB_KEYMAP_SIZE_AES_OMAC1_SECURE_STORE];
    DRM_BB_KEY_REGISTER_ENTRY rgKeyMapAesKeyFile[OEM_BB_KEYMAP_SIZE_AES_KEYFILE];
    DRM_BB_KEY_REGISTER_ENTRY rgKeyMapAesGenericKeyContent[OEM_BB_KEYMAP_SIZE_AES_GENERIC_KEY_CONTENT];
    DRM_BB_KEY_REGISTER_ENTRY rgKeyMapAesGenericKeyRoot[OEM_BB_KEYMAP_SIZE_AES_GENERIC_KEY_ROOT];
    DRM_BB_KEY_REGISTER_ENTRY rgKeyMapAesEcbNewLicenseRoot[OEM_BB_KEYMAP_SIZE_AES_ECB_NEW_LICENSE_ROOT];
    DRM_BB_KEY_REGISTER_ENTRY rgKeyMapAesCtrNewLicenseContent[OEM_BB_KEYMAP_SIZE_AES_CTR_NEW_LICENSE_CONTENT];
    DRM_BB_KEY_REGISTER_ENTRY rgKeyMapLegacy[OEM_BB_KEYMAP_SIZE_LEGACY];
    DRM_BB_KEY_REGISTER_ENTRY rgKeyMapSlk[OEM_BB_KEYMAP_SIZE_SLK];

    DRM_GUID rgPreloadLookupMapEccP256Public[OEM_BB_PRELOAD_LOOKUP_SIZE_ECC_P256_PUBLIC];
    DRM_GUID rgPreloadLookupMapEccP256ModelSign[OEM_BB_PRELOAD_LOOKUP_SIZE_ECC_P256_MODEL_SIGN];
    DRM_GUID rgPreloadLookupMapAesKeyFile[OEM_BB_PRELOAD_LOOKUP_SIZE_AES_KEYFILE];

    DRM_OBFUS_FILL_BYTES(4)

    DRM_BB_KEY_REGISTER_TABLE rgKeyMapTables[ OEM_HAL_KEY_TYPE_NUM_VALID_TYPES ];
} DRM_BB_KEY_HANDLE_STATE;



#define DRM_PK_BUFFER_MAX  DRM_ECC160_PLAINTEXT_LEN
#define DRM_MAX_DRMOLDKEYS 20
#define DRMKEYPAIRSIZE    ( SIZEOF( PUBKEY ) + SIZEOF( PRIVKEY ) )

typedef DRM_OBFUS_FIXED_ALIGN struct __tagDRM_CLIENT_INFO
{
    DRM_ANSI_STRING m_dastrClientVersion;
} DRM_CLIENT_INFO;

#define BBX_OPAQUE_DATA_SIZE 128

typedef DRM_OBFUS_FIXED_ALIGN struct __tagDRM_BB_REV_INFO_DATA
{
    DRM_DWORD  dwRevInfoSequenceNumber;
    DRM_DWORD  dwCRLVersion;
} DRM_BB_REV_INFO_DATA;


typedef DRM_OBFUS_FIXED_ALIGN struct __tagDRM_BB_CONTEXT
{
    /* Make sure the crypto context is the first member in this struct */
    DRM_CRYPTO_CONTEXT                   CryptoContext;
    DRM_DEVICE_CERTIFICATE_CACHED_VALUES cachedCertValues;
DRM_OBFUS_PTR_TOP
    DRM_DOMAINSTORE_CONTEXT             *pDomainStoreContext; /* Used for domain-bound licenses */
DRM_OBFUS_PTR_BTM
    DRM_BINARY_DEVICE_CERT_CACHED_VALUES cachedBCertValues;

DRM_OBFUS_PTR_TOP
    DRM_VOID                            *pOEMContext;
DRM_OBFUS_PTR_BTM
    DRM_BOOL                             fInited;

DRM_OBFUS_FILL_BYTES(4)

DRM_OBFUS_PTR_TOP
    DRM_KEYFILE_CONTEXT                  *pKeyFileContext;
DRM_OBFUS_PTR_BTM

    DRM_BYTE                              rgbOpaqueData[BBX_OPAQUE_DATA_SIZE];

DRM_OBFUS_PTR_TOP
    DRM_CLIENT_INFO                      *pClientInfo;
DRM_OBFUS_PTR_BTM

    DRM_BB_KEY_HANDLE_STATE               keyHandleState;
    DRM_BB_REV_INFO_DATA                  seenRevInfoVersions;
DRM_OBFUS_PTR_TOP
    DRM_VOID                             *prgOpaqueKeyMap;
DRM_OBFUS_PTR_BTM
DRM_OBFUS_PTR_TOP
    DRM_VOID                             *prgOpaqueCallbackTable;
DRM_OBFUS_PTR_BTM
} DRM_BB_CONTEXT;


typedef enum _BB_SUPPORTED_ALGORITHMS
{
    eMSDRM_PK  = 1,  /* The key is encrypted with a ECC public key */
    eMSDRM_CK  = 2,  /* This is a chained license key algorithm. ( DES/AES encrypted ) */
    eMSDRM_SYM = 3   /* The license is symmetrically bound.  This means that is was actually rebound to a symmetric key once is was stored on the device */
} BB_SUPPORTED_ALGORITHMS;

/*
** Contains checksum data
*/
typedef DRM_OBFUS_FIXED_ALIGN struct __tagDRM_BB_CHECKSUM_CONTEXT
{
    DRM_BOOL   m_fIgnoreChecksum;
    DRM_BYTE   m_rgbChecksumData[DRM_MAX_CHECKSUM];
    DRM_DWORD  m_cbChecksum;  /* Should be 20 bytes for normal checksum, 24 bytes for V1 header checksum */
    DRM_KID    m_KID;
DRM_OBFUS_PTR_TOP
    DRM_BYTE  *m_pbV1KID;     /* If not NULL then use the old V1 checksum algorithm */
DRM_OBFUS_PTR_BTM
} DRM_BB_CHECKSUM_CONTEXT;

/*
** Contains binding information for XML licenses
*/
typedef DRM_DWORD_ALIGN struct __tagDRM_XML_BINDING_INFO
{
    DRM_BYTE                 m_rgbContentKey[DRM_ECC160_CIPHERTEXT_LEN];
    DRM_BYTE                 m_rgbSignature[DRM_ECC160_SIGNATURE_LEN];
    PUBKEY                   m_oPublKey;
    PUBKEY                   m_oLsPublKey;
    DRM_DWORD                m_dwAlgorithm;
    DRM_BOOL                 m_fCKSigVerified;
} DRM_XML_BINDING_INFO;

typedef DRM_OBFUS_FIXED_ALIGN struct __tagDRM_XMR_BINDING_INFO
{
DRM_OBFUS_PTR_TOP
    DRM_XMR_CONTENT_KEY            *m_pxmrContentKey;
DRM_OBFUS_PTR_BTM
DRM_OBFUS_PTR_TOP
    DRM_XMR_OPTIMIZED_CONTENT_KEY  *m_pxmrOptimizedContentKey; /* Pointer to symmetrically optimized version of content key */
DRM_OBFUS_PTR_BTM
DRM_OBFUS_PTR_TOP
    DRM_XMR_DEVICE_KEY             *m_pxmrDeviceKey;
DRM_OBFUS_PTR_BTM
DRM_OBFUS_PTR_TOP
    DRM_XMR_ECC_DEVICE_KEY         *m_pxmrDeviceEccKey;
DRM_OBFUS_PTR_BTM
DRM_OBFUS_PTR_TOP
    DRM_XMR_SIGNATURE              *m_pxmrSignature;
DRM_OBFUS_PTR_BTM
DRM_OBFUS_PTR_TOP
    DRM_XMR_DOMAIN_ID              *m_pxmrDomainID;
DRM_OBFUS_PTR_BTM
DRM_OBFUS_PTR_TOP
    DRM_XMR_LICENSE                *m_pxmrLicense;    /* An HMAC signature of this license will be calculated and compared to m_pbSignature */
DRM_OBFUS_PTR_BTM
} DRM_XMR_BINDING_INFO;

typedef DRM_OBFUS_FIXED_ALIGN struct __tagDRM_BINDING_INFO
{
    DRM_BB_CHECKSUM_CONTEXT m_oChecksum;   /* Contains Checksum data */
    DRM_BOOL                m_fXMRLicense; /* Specifies XMR or XML license type */

DRM_OBFUS_FILL_BYTES(4)
    union
    {
        DRM_XMR_BINDING_INFO m_XMR;
        DRM_XML_BINDING_INFO m_XML;
    } m_BindingInfo;
} DRM_BINDING_INFO;


/*
** Contains the info required to verify and unwrap a license below the OEM HAL
*/
typedef DRM_OBFUS_FIXED_ALIGN struct __tagDRM_XMR_UNWRAP_INFO
{
DRM_OBFUS_PTR_TOP
    const DRM_BYTE                *pbXMRLic;
DRM_OBFUS_PTR_BTM
    DRM_DWORD                      cbXMRLic;
    const DRM_BB_CHECKSUM_CONTEXT *poChecksum;
} DRM_XMR_UNWRAP_INFO;


/*
** Is different from PC client's version set into 1
*/
#define DOMAIN_KEY_RECORD_VERSION 2

typedef struct _tagDRM_BB_DOMAIN_KEY_RECORD {
    /* domain private key record format version */
    DRM_DWORD dwVersion;
    /* domain private key encrypted with one of the device private keys from the keyfile */
    PRIVKEY_P256 oDomainPrivKeyEncrypted;
    /* public key matching private key used to encrypt oDomainPrivKeyEncrypted */
    PUBKEY_P256  oDevicePubKey;
} DRM_BB_DOMAIN_KEY_RECORD;


/*
** Some blackbox implementations require key handle callbacks to implement key handle functionality.
** If this is the case a pointer to the following functions and function table is used to provide the callbacks
*/
typedef DRM_RESULT ( *PF_INITIALIZE_HANDLE_CACHING )(
    __inout_ecount( 1 )             DRM_BB_CONTEXT                       *f_pBbxContext,
    __inout_ecount( 1 )             DRM_BINARY_DEVICE_CERT_CACHED_VALUES *f_pCache,
    __in_bcount(f_cbCertData) const DRM_BYTE                             *f_pbCertData,
    __in                      const DRM_DWORD                             f_cbCertData,
    __in                            DRM_DWORD                             f_dwChainLength,
    __in                            DRM_DWORD                             f_bOffset,
    __out_ecount( 1 )               OEM_CRYPTO_HANDLE                    *f_phCertChainPubKey );


typedef DRM_RESULT ( *PF_UNWRAP_PUBLIC_KEY_HANDLE )(
    __inout_ecount( 1 )                     DRM_BB_CONTEXT         *f_pBbxContext,
    __in                                    OEM_CRYPTO_HANDLE       f_hWrappingKey,
    __in_bcount( f_cbWrappedKeyData ) const DRM_BYTE               *f_pbCertificate,
    __in                                    DRM_DWORD               f_cbCertificate,
    __in                                    DRM_DWORD               f_iKeyInCert,
    __out_ecount( 1 )                       DRM_PUBLIC_KEY_CONTEXT *f_pKeyContext );


typedef DRM_VOID ( *PF_COMPLETE_HANDLE_CACHING )(
    __inout_ecount_opt( 1 )         DRM_BB_CONTEXT                       *f_pBbxContext,
    __inout_ecount_opt( 1 )         DRM_BINARY_DEVICE_CERT_CACHED_VALUES *f_pCache,
    __in                            DRM_RESULT                            f_drCachingResult,
    __inout_ecount_opt( 1 )         OEM_CRYPTO_HANDLE                    *f_phCertChainPubKey );


typedef DRM_VOID ( *PF_CLEANUP_HANDLE_CACHE )(
    __inout_ecount_opt( 1 )         DRM_BB_CONTEXT                       *f_pBbxContext,
    __inout_ecount_opt( 1 )         DRM_BINARY_DEVICE_CERT_CACHED_VALUES *f_pCache );


typedef DRM_OBFUS_FIXED_ALIGN struct __tagDRM_BB_KEYHANDLE_CALLBACKS
{
DRM_OBFUS_PTR_TOP
    PF_INITIALIZE_HANDLE_CACHING pfInitializeCaching;
DRM_OBFUS_PTR_BTM
DRM_OBFUS_PTR_TOP
    PF_UNWRAP_PUBLIC_KEY_HANDLE  pfUnwrapPublicKeyHandle;
DRM_OBFUS_PTR_BTM
DRM_OBFUS_PTR_TOP
    PF_COMPLETE_HANDLE_CACHING   pfCompleteCaching;
DRM_OBFUS_PTR_BTM
DRM_OBFUS_PTR_TOP
    PF_CLEANUP_HANDLE_CACHE      pfCleanupCache;
DRM_OBFUS_PTR_BTM
} DRM_BB_KEYHANDLE_CALLBACKS;


typedef enum
{
    eBBX_PRIVKEY_MACHINE               = 1,
    eBBX_PRIVKEY_RESTORELICENSESIGNER  = 2,
    eBBX_PRIVKEY_TRANSFERLICENSESIGNER = 3
} eBBX_SIGNING_KEY_TYPES;

#define SYMMETRIC_ENCRYPT TRUE
#define SYMMETRIC_DECRYPT FALSE

/*
** Note that this API must be called in the context of the keyfile context already open
** and locked for writing.
*/

typedef enum
{
    DRM_BBX_KEY_PAIR_TYPE_MIMK = 1,
    DRM_BBX_KEY_PAIR_TYPE_CICK = 2,
    DRM_BBX_KEY_PAIR_TYPE_RIRK = 3,
} DRM_BBX_KEY_PAIR_TYPE;

EXIT_PK_NAMESPACE;

#endif /* __DRMBLACKBOXTYPES_H__ */

