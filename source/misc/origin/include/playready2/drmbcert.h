/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRMBCERT_H__
#define __DRMBCERT_H__

#include <drmtypes.h>
#include <oemshahash.h>
#include <oemeccp256.h>

ENTER_PK_NAMESPACE;

#define BYTES_PER_DWORD      SIZEOF( DRM_DWORD )
#define PAD_AMOUNT(x)        ( ( (x) > 0 ) ? ( ( BYTES_PER_DWORD - ( (x) % BYTES_PER_DWORD ) ) % BYTES_PER_DWORD ) : 0 )

#define DRM_BCERT_OBJFLAG_EMPTY              0x0000
#define DRM_BCERT_OBJFLAG_MUST_UNDERSTAND    0x0001
#define DRM_BCERT_OBJFLAG_CONTAINER_OBJ      0x0002

#define DRM_BCERT_OBJTYPE_BASIC              0x0001
#define DRM_BCERT_OBJTYPE_DOMAIN             0x0002
#define DRM_BCERT_OBJTYPE_PC                 0x0003
#define DRM_BCERT_OBJTYPE_DEVICE             0x0004
#define DRM_BCERT_OBJTYPE_FEATURE            0x0005
#define DRM_BCERT_OBJTYPE_KEY                0x0006
#define DRM_BCERT_OBJTYPE_MANUFACTURER       0x0007
#define DRM_BCERT_OBJTYPE_SIGNATURE          0x0008
#define DRM_BCERT_OBJTYPE_SILVERLIGHT        0x0009
#define DRM_BCERT_OBJTYPE_METERING           0x000a
#define DRM_BCERT_OBJTYPE_EXTDATASIGNKEY     0x000b
#define DRM_BCERT_OBJTYPE_EXTDATACONTAINER   0x000c
#define DRM_BCERT_OBJTYPE_EXTDATASIGNATURE   0x000d
#define DRM_BCERT_OBJTYPE_EXTDATA_HWID       0x000e
#define DRM_BCERT_OBJTYPE_SERVER             0x000f
#define DRM_BCERT_OBJTYPE_SECURITY_VERSION   0x0010
#define DRM_BCERT_OBJTYPE_SECURITY_VERSION_2 0x0011

#define DRM_BCERT_OBJTYPE_MAX_VALUE          0x0011

typedef struct _tagDrmBCertObjectHeader
{
    DRM_WORD    wFlags;       /* bit field */
    DRM_WORD    wType;
    DRM_DWORD   cbLength;
} DRM_BCERT_OBJECT_HEADER;


#define DRM_BCERT_MAX_CERTS_PER_CHAIN   6


/* ------------------------------------------------------------------------- */
/*  CERTIFICATE HEADER  */

#define DRM_BCERT_HEADER_TAG     0x43455254  /* "CERT" */
#define DRM_BCERT_VERSION        0x00000001

typedef struct _tagDrmBCertHeader
{
    DRM_DWORD              dwHeaderTag;
    DRM_DWORD              dwVersion;
    DRM_DWORD              cbCertificate;
    DRM_DWORD              cbCertificateSigned;
} DRM_BCERT_HEADER;


/* ------------------------------------------------------------------------- */
/*  BASIC INFO  */


#define DRM_BCERT_CERT_ID_LENGTH  16  /* 128 bits */
typedef struct _tagDrmBCertCertId
{
    DRM_BYTE    rgb[ __CB_DECL( DRM_BCERT_CERT_ID_LENGTH ) ];
} DRM_BCERT_CERT_ID;

#define DRM_BCERT_SECURITYLEVEL_150    150  /* for testing */
#define DRM_BCERT_SECURITYLEVEL_2000   2000

#define DRM_BCERT_FLAGS_EMPTY             0x00000000 /* default */
#define DRM_BCERT_FLAGS_EXTDATA_PRESENT   0x00000001 /* presence of extended data */

#define DRM_BCERT_CERTTYPE_UNKNOWN           0x00000000
#define DRM_BCERT_CERTTYPE_PC                0x00000001
#define DRM_BCERT_CERTTYPE_DEVICE            0x00000002
#define DRM_BCERT_CERTTYPE_DOMAIN            0x00000003
#define DRM_BCERT_CERTTYPE_ISSUER            0x00000004
#define DRM_BCERT_CERTTYPE_CRL_SIGNER        0x00000005
#define DRM_BCERT_CERTTYPE_SERVICE           0x00000006
#define DRM_BCERT_CERTTYPE_SILVERLIGHT       0x00000007
#define DRM_BCERT_CERTTYPE_APPLICATION       0x00000008
#define DRM_BCERT_CERTTYPE_METERING          0x00000009
#define DRM_BCERT_CERTTYPE_KEYFILESIGNER     0x0000000a
#define DRM_BCERT_CERTTYPE_SERVER            0x0000000b
#define DRM_BCERT_CERTTYPE_LICENSESIGNER     0x0000000c

#define DRM_BCERT_CERTTYPE_MAX_VALUE         0x0000000c

#define DRM_BCERT_DEFAULT_EXPIRATION_DATE  0xFFFFFFFF

#define DRM_BCERT_CLIENT_ID_LENGTH  16  /* 128 bits */
typedef struct _tagDrmBCertClientId
{
    DRM_BYTE    rgb[ __CB_DECL( DRM_BCERT_CLIENT_ID_LENGTH ) ];
} DRM_BCERT_CLIENT_ID;

typedef struct _tagDrmBCertBasicInfo
{
    DRM_BCERT_OBJECT_HEADER  Header;
    DRM_BCERT_CERT_ID        CertificateID;
    DRM_DWORD                dwSecurityLevel;
    DRM_DWORD                dwFlags;           /* bit field */
    DRM_DWORD                dwType;
    DRM_SHA256_Digest        DigestValue;       /* hash of the public key value */
    DRM_DWORD                dwExpirationDate;
    DRM_BCERT_CLIENT_ID      ClientID;
} DRM_BCERT_BASIC_INFO;


/* ------------------------------------------------------------------------- */
/*  DOMAIN INFO  */


#define DRM_BCERT_ACCOUNT_ID_LENGTH  SIZEOF(DRM_GUID)  /* 128 bits */
typedef struct _tagDrmBCertAccountId
{
    DRM_BYTE    rgb[ __CB_DECL( DRM_BCERT_ACCOUNT_ID_LENGTH ) ];
} DRM_BCERT_ACCOUNT_ID;

#define DRM_BCERT_SERVICE_ID_LENGTH  16  /* 128 bits */
typedef struct _tagDrmBCertServiceId
{
    DRM_BYTE    rgb[ __CB_DECL( DRM_BCERT_SERVICE_ID_LENGTH ) ];
} DRM_BCERT_SERVICE_ID;

#define DRM_BCERT_MAX_DOMAIN_URL_LENGTH  4096
typedef struct _tagDrmBCertDomainURL
{
    DRM_DWORD   cb;  /* URL length */
    DRM_BYTE    rgb[ __CB_DECL( DRM_BCERT_MAX_DOMAIN_URL_LENGTH ) ];
} DRM_BCERT_DOMAIN_URL;

typedef struct _tagDrmBCertDomainInfo
{
    DRM_BCERT_OBJECT_HEADER  Header;
    DRM_BCERT_SERVICE_ID     ServiceID;
    DRM_BCERT_ACCOUNT_ID     AccountID;
    DRM_DWORD                dwRevision;  /* a timestamp */
    DRM_BCERT_DOMAIN_URL     DomainURL;
} DRM_BCERT_DOMAIN_INFO;


/* ------------------------------------------------------------------------- */
/*  PC INFO  */


typedef struct _tagDrmBCertPCInfo
{
    DRM_BCERT_OBJECT_HEADER  Header;
    DRM_DWORD                dwSecurityVersion;  /* A.B.C.D */
} DRM_BCERT_PC_INFO;

/* ------------------------------------------------------------------------- */
/*  SILVERLIGHT INFO  */


typedef struct
{
    DRM_BCERT_OBJECT_HEADER  Header;
    DRM_DWORD                dwSecurityVersion;  /* A.B.C.D */
    DRM_DWORD                dwPlatformIdentifier;
} DRM_BCERT_SILVERLIGHT_INFO;

/*  Platform Identifiers for the SilverLight INFO structure, v2/v3 (not v4) */
#define DRM_BCERT_SILVERLIGHT_PLATFORM_WINDOWS_X86  0
#define DRM_BCERT_SILVERLIGHT_PLATFORM_WINDOWS_X64  1
#define DRM_BCERT_SILVERLIGHT_PLATFORM_OSX_PPC      2
#define DRM_BCERT_SILVERLIGHT_PLATFORM_OSX_X86      3
#define DRM_BCERT_SILVERLIGHT_PLATFORM_OSX_X64      4
#define DRM_BCERT_SILVERLIGHT_PLATFORM_MAX          4

/* ------------------------------------------------------------------------- */
/*  DEVICE INFO  */


#define DRM_BCERT_MAX_LICENSE_SIZE         10240  /* 10K */
#define DRM_BCERT_MAX_HEADER_SIZE          15360  /* 15K */
#define DRM_BCERT_MAX_LICENSE_CHAIN_DEPTH      2

typedef struct _tagDrmBCertDeviceInfo
{
    DRM_BCERT_OBJECT_HEADER  Header;
    DRM_DWORD                cbMaxLicense;
    DRM_DWORD                cbMaxHeader;
    DRM_DWORD                dwMaxChainDepth;
} DRM_BCERT_DEVICE_INFO;


/* ------------------------------------------------------------------------- */
/*  METERING INFO  */

#define DRM_BCERT_METERING_ID_LENGTH  SIZEOF(DRM_GUID)  /* 128 bits */
typedef struct _tagDrmBCertMeteringId
{
    DRM_BYTE    rgb[ __CB_DECL( DRM_BCERT_METERING_ID_LENGTH ) ];
} DRM_BCERT_METERING_ID;

#define DRM_BCERT_MAX_METERING_URL_LENGTH  4096
typedef struct _tagDrmBCertMeteringURL
{
    DRM_DWORD   cb;  /* URL length */
    DRM_BYTE    rgb[ __CB_DECL( DRM_BCERT_MAX_METERING_URL_LENGTH ) ];
} DRM_BCERT_METERING_URL;

typedef struct
{
    DRM_BCERT_OBJECT_HEADER  Header;
    DRM_BCERT_METERING_ID    MeteringID;
    DRM_BCERT_METERING_URL   MeteringURL;
} DRM_BCERT_METERING_INFO;

/* ------------------------------------------------------------------------- */
/*  SERVER INFO  */


typedef struct _tagDrmBCertServerInfo
{
    DRM_BCERT_OBJECT_HEADER  Header;
    DRM_DWORD                dwWarningDays;  /* number of days before expiry to start warning */
} DRM_BCERT_SERVER_INFO;

/* ------------------------------------------------------------------------- */
/*  SECURITY VERSION */


#define DRM_BCERT_SECURITY_VERSION_PLATFORM_WINDOWS      0x0
#define DRM_BCERT_SECURITY_VERSION_PLATFORM_OSX          0x1
#define DRM_BCERT_SECURITY_VERSION_PLATFORM_WINDOWS_ARM  0x2

#define DRM_BCERT_SECURITY_VERSION_PLATFORM_WM_7         0x5

#define DRM_BCERT_SECURITY_VERSION_PLATFORM_IOS_ARM      0x6
#define DRM_BCERT_SECURITY_VERSION_PLATFORM_XBOX_PPC     0x7
#define DRM_BCERT_SECURITY_VERSION_PLATFORM_WP8_ARM      0x8
#define DRM_BCERT_SECURITY_VERSION_PLATFORM_WP8_X86      0x9



typedef struct _tagDrmBcertSecurityVersion
{
    DRM_BCERT_OBJECT_HEADER  Header;
    DRM_DWORD                dwSecurityVersion;  /* A.B.C.D */
    DRM_DWORD                dwPlatformIdentifier;
} DRM_BCERT_SECURITY_VERSION;


/* ------------------------------------------------------------------------- */
/*  FEATURE INFO  */

#define DRM_BCERT_MAX_FEATURES 32    /* array size with room to grow */

#define DRM_BCERT_FEATURE_TRANSMITTER             0x00000001
#define DRM_BCERT_FEATURE_RECEIVER                0x00000002
#define DRM_BCERT_FEATURE_SHARED_CERTIFICATE      0x00000003
#define DRM_BCERT_FEATURE_SECURE_CLOCK            0x00000004
#define DRM_BCERT_FEATURE_ANTIROLLBACK_CLOCK      0x00000005
/*
** The next three feature flags should not be explicitly set in the certs
** because for any cert their values are already known
** (i.e. every device must support metering, license sync and symmetric optimization)
** These features will stay deprecated as long as they are not optional.
*/
#define DRM_BCERT_FEATURE_RESERVED_METERING       0x00000006
#define DRM_BCERT_FEATURE_RESERVED_LICSYNC        0x00000007
#define DRM_BCERT_FEATURE_RESERVED_SYMOPT         0x00000008
#define DRM_BCERT_FEATURE_SUPPORTS_CRLS           0x00000009

/*
** Server features
*/
#define DRM_BCERT_FEATURE_SERVER_BASIC_EDITION    0x0000000A
#define DRM_BCERT_FEATURE_SERVER_STANDARD_EDITION 0x0000000B
#define DRM_BCERT_FEATURE_SERVER_PREMIUM_EDITION  0x0000000C

#define DRM_BCERT_FEATURE_MAX_VALUE               0x0000000C


#define BCERT_FEATURE_BIT(dwFeature)     (1 << ((dwFeature)-1))


typedef struct _tagDrmBCertFeatureInfo
{
    DRM_BCERT_OBJECT_HEADER  Header;
    DRM_DWORD                dwNumFeatureEntries;  /* this can be zero */
    DRM_DWORD                rgdwFeatureSet[ DRM_BCERT_MAX_FEATURES ];
} DRM_BCERT_FEATURE_INFO;


/* ------------------------------------------------------------------------- */
/*  KEY INFO  */


/* List of supported key types. (currently just one) */
#define DRM_BCERT_KEYTYPE_ECC256   0x0001

#define DRM_BCERT_KEYUSAGE_UNKNOWN                          0x00000000
#define DRM_BCERT_KEYUSAGE_SIGN                             0x00000001
#define DRM_BCERT_KEYUSAGE_ENCRYPT_KEY                      0x00000002
#define DRM_BCERT_KEYUSAGE_SIGN_CRL                         0x00000003
#define DRM_BCERT_KEYUSAGE_ISSUER_ALL                       0x00000004
#define DRM_BCERT_KEYUSAGE_ISSUER_INDIV                     0x00000005
#define DRM_BCERT_KEYUSAGE_ISSUER_DEVICE                    0x00000006
#define DRM_BCERT_KEYUSAGE_ISSUER_LINK                      0x00000007
#define DRM_BCERT_KEYUSAGE_ISSUER_DOMAIN                    0x00000008
#define DRM_BCERT_KEYUSAGE_ISSUER_SILVERLIGHT               0x00000009
#define DRM_BCERT_KEYUSAGE_ISSUER_APPLICATION               0x0000000a
#define DRM_BCERT_KEYUSAGE_ISSUER_CRL                       0x0000000b
#define DRM_BCERT_KEYUSAGE_ISSUER_METERING                  0x0000000c
#define DRM_BCERT_KEYUSAGE_ISSUER_SIGN_KEYFILE              0x0000000d
#define DRM_BCERT_KEYUSAGE_SIGN_KEYFILE                     0x0000000e
#define DRM_BCERT_KEYUSAGE_ISSUER_SERVER                    0x0000000f
#define DRM_BCERT_KEYUSAGE_ENCRYPTKEY_SAMPLE_PROTECTION     0x00000010
#define DRM_BCERT_KEYUSAGE_RESERVED2                        0x00000011
#define DRM_BCERT_KEYUSAGE_ISSUER_SIGN_LICENSE              0x00000012
#define DRM_BCERT_KEYUSAGE_SIGN_LICENSE                     0x00000013
#define DRM_BCERT_KEYUSAGE_SIGN_RESPONSE                    0x00000014
#define DRM_BCERT_KEYUSAGE_PRND_ENCRYPT_KEY                 0x00000015

#define DRM_BCERT_KEYUSAGE_MAX_VALUE                        0x00000015

/*
** DRM_BCERT_MAX_KEY_USAGES has to be larger than DRM_BCERT_KEYUSAGE_MAX_VALUE.
** DRM_BCERT_MAX_KEY_USAGES should not exceed 32 since a bitmap based on DRM_DWORD
** is currently used to represent key usage set.
*/
#define DRM_BCERT_MAX_KEY_USAGES                22

#define BCERT_KEYUSAGE_BIT(dwKeyUsage)          (1 << ((dwKeyUsage)-1))

/*
** The following byte value should be equal to the largest public key length supported
*/
#define DRM_BCERT_MAX_PUBKEY_VALUE_LENGTH     SIZEOF( PUBKEY_P256 )

#define DRM_BCERT_PUBKEY    PUBKEY_P256

typedef struct _tagDrmBCertCertKey
{
    DRM_WORD                 wType;
    DRM_WORD                 wLength;           /* in bits */
    DRM_DWORD                dwFlags;           /* bit field; should be ignored */
DRM_OBFUS_PTR_TOP
    DRM_BCERT_PUBKEY        *pValue;            /* pointer to the public key in the cert buffer */
DRM_OBFUS_PTR_BTM
    DRM_DWORD                dwUsageSet;        /* key usage set */
DRM_OBFUS_FILL_BYTES(4)
} DRM_BCERT_CERTKEY;


typedef struct _tagDrmBCertKeyInfo
{
    DRM_BCERT_OBJECT_HEADER  Header;
    DRM_DWORD                dwNumKeys;                             /* actual number of items in array, > 0 */
DRM_OBFUS_FILL_BYTES(4)
    DRM_BCERT_CERTKEY        rgoKeys[ DRM_BCERT_MAX_KEY_USAGES ];   /* array of public keys, up to number of various key usages */
}  DRM_BCERT_KEY_INFO;


/* ------------------------------------------------------------------------- */
/*  MANUFACTURER INFO  */


#define DRM_BCERT_MAX_MANUFACTURER_STRING_LENGTH  128   /* bytes */
typedef struct _tagDrmBCertManufacturerString
{
    DRM_DWORD   cb;
    DRM_BYTE    rgb[ __CB_DECL( DRM_BCERT_MAX_MANUFACTURER_STRING_LENGTH ) ];
} DRM_BCERT_MANUFACTURER_STRING;

typedef struct _tagDrmBCertManufacturerStrings
{
    DRM_BCERT_MANUFACTURER_STRING  ManufacturerName;
    DRM_BCERT_MANUFACTURER_STRING  ModelName;
    DRM_BCERT_MANUFACTURER_STRING  ModelNumber;
} DRM_BCERT_MANUFACTURER_STRINGS;

typedef struct _tagDrmBCertManufacturerInfo
{
    DRM_BCERT_OBJECT_HEADER          Header;
    DRM_DWORD                        dwFlags; /* bit field; should be ignored */
    DRM_BCERT_MANUFACTURER_STRINGS   ManufacturerStrings;
} DRM_BCERT_MANUFACTURER_INFO;


/* ------------------------------------------------------------------------- */
/*  EXTENDED DATA SIGNATURE KEY INFO */


typedef struct _tagDrmBCertExtDataSignKeyInfo
{
    DRM_BCERT_OBJECT_HEADER     Header;
    DRM_WORD                    wType;
    DRM_WORD                    wLength;           /* in bits */
    DRM_DWORD                   dwFlags;           /* bit field; should be ignored */
DRM_OBFUS_PTR_TOP
    DRM_BCERT_PUBKEY           *pValue;            /* pointer to the public key in the cert buffer */
DRM_OBFUS_PTR_BTM
} DRM_BCERT_EXTDATA_SIGNKEY_INFO;


/* ------------------------------------------------------------------------- */
/*  SIGNATURE INFO  */


#define DRM_BCERT_SIGNATURE_TYPE_P256         0x0001    /* ECDSA-P-256-SHA-256 */

/*
** The following byte value should be equal to the largest signature length supported
*/
#define DRM_BCERT_MAX_SIGNATURE_DATA_LENGTH   SIZEOF( SIGNATURE_P256 )

typedef struct _tagDrmBCertSignatureData
{
    DRM_WORD    cb;     /* bytes */
DRM_OBFUS_FILL_BYTES(4)
DRM_OBFUS_PTR_TOP
    DRM_BYTE   *pValue;  /* pointer to the signature in the cert buffer */
DRM_OBFUS_PTR_BTM
} DRM_BCERT_SIGNATURE_DATA;

typedef struct _tagDrmBCertSignatureInfo
{
    DRM_BCERT_OBJECT_HEADER         Header;
    DRM_WORD                        wSignatureType;
DRM_OBFUS_FILL_BYTES(4)
    DRM_BCERT_SIGNATURE_DATA        SignatureData;
    DRM_DWORD                       dwIssuerKeyLength;
DRM_OBFUS_FILL_BYTES(4)
DRM_OBFUS_PTR_TOP
    DRM_BCERT_PUBKEY               *pIssuerKey;          /* = public key in next cert */
DRM_OBFUS_PTR_BTM
} DRM_BCERT_SIGNATURE_INFO;


/* ------------------------------------------------------------------------- */
/*  EXTENDED DATA RECORD */


typedef struct _tagBCertExtDataRecord
{
    DRM_BCERT_OBJECT_HEADER     Header;
    DRM_DWORD                   dwDataLength;
DRM_OBFUS_FILL_BYTES(4)
DRM_OBFUS_PTR_TOP
    DRM_BYTE                    *pbData;    /* this is a pointer, not a buffer */
DRM_OBFUS_PTR_BTM
} DRM_BCERT_EXTDATA_RECORD;

/* ------------------------------------------------------------------------- */
/*  EXTENDED DATA SIGNATURE */


typedef struct _tagDrmBCertExtDataSignature
{
    DRM_BCERT_OBJECT_HEADER     Header;
    DRM_WORD                    wSignatureType;
DRM_OBFUS_FILL_BYTES(4)
    DRM_BCERT_SIGNATURE_DATA    SignatureData;
} DRM_BCERT_EXTDATA_SIGNATURE;


/* ------------------------------------------------------------------------- */
/*  EXTENDED DATA CONTAINER */


#define DRM_BCERT_MAX_EXTDATA_RECORDS           1

typedef struct _tagBCertExtDataContainer
{
    DRM_BCERT_OBJECT_HEADER     Header;
    DRM_DWORD                   cbRecordsCount;
DRM_OBFUS_FILL_BYTES(4)
    DRM_BCERT_EXTDATA_RECORD    Records[DRM_BCERT_MAX_EXTDATA_RECORDS];
    DRM_BCERT_EXTDATA_SIGNATURE Signature;
} DRM_BCERT_EXTDATA_CONTAINER;


/* ------------------------------------------------------------------------- */
/*  CERTIFICATE STRUCTURE (for reference) */


typedef struct _tagDrmBCertCertificate
{
    DRM_BCERT_HEADER              Header;
    DRM_BCERT_BASIC_INFO          BasicInfo;

    union _tagBCertType
    {
        DRM_BCERT_DOMAIN_INFO       DomainInfo;
        DRM_BCERT_PC_INFO           PCInfo;
        DRM_BCERT_DEVICE_INFO       DeviceInfo;
        DRM_BCERT_SILVERLIGHT_INFO  SilverLightInfo;
        DRM_BCERT_METERING_INFO     MeteringInfo;
        DRM_BCERT_SERVER_INFO       ServerInfo;
    } Type; /* optional */

    DRM_BCERT_SECURITY_VERSION      SecurityVersion;   /* optional */
    DRM_BCERT_SECURITY_VERSION      SecurityVersion2;  /* optional */

    DRM_BCERT_FEATURE_INFO        FeatureInfo;
DRM_OBFUS_FILL_BYTES(4)
    DRM_BCERT_KEY_INFO            KeyInfo;
    DRM_BCERT_MANUFACTURER_INFO   ManufacturerInfo;  /* optional */

    DRM_BCERT_EXTDATA_SIGNKEY_INFO ExtDataSignatureInfo;
    /* New elements defined post-v1 go here */

    DRM_BCERT_SIGNATURE_INFO      SignatureInfo;

    DRM_BCERT_EXTDATA_CONTAINER   ExtDataContainer;
} DRM_BCERT_CERTIFICATE;


/* ------------------------------------------------------------------------- */
/*  CHAIN HEADER  */


#define DRM_BCERT_CHAIN_HEADER_TAG     0x43484149  /* "CHAI" */
#define DRM_BCERT_CHAIN_VERSION        0x00000001

typedef struct _tagDrmBCertChainHeader
{
    DRM_DWORD              dwHeaderTag; /* = DRM_BCERT_CHAIN_HEADER_ID */
    DRM_DWORD              dwVersion;   /* = DRM_BCERT_CHAIN_VERSION   */
    DRM_DWORD              cbChain;
    DRM_DWORD              dwFlags;     /* bit field; should be ignored */
    DRM_DWORD              cCerts;
} DRM_BCERT_CHAIN_HEADER;

#define SIZEOF_CHAIN_HEADER        SIZEOF( DRM_BCERT_CHAIN_HEADER )

/*
** The following two offsets are relative to the beginning of the certificate chain
*/
#define DRM_BCERT_CHAIN_SIZE_OFFSET     ( 2 * SIZEOF( DRM_DWORD ) )
#define DRM_BCERT_CHAIN_COUNT_OFFSET    ( 4 * SIZEOF( DRM_DWORD ) )



/* ------------------------------------------------------------------------- */

EXIT_PK_NAMESPACE;

#endif /* __DRMBCERT_H__ */

