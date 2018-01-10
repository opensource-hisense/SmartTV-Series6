/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRMDEVCERTCACHE_H__
#define __DRMDEVCERTCACHE_H__

#include <drmtypes.h>
#include <drmpragmas.h>
#include <oemsha1.h>

ENTER_PK_NAMESPACE;

typedef enum
{
    DRM_DEVCERT_SERIALNUMBER = 1,       /* CERTIFICATE type="DEVICE"/DATA/UNIQUEID */
    DRM_DEVCERT_DEVICEPUBKEY,           /* CERTIFICATE type="DEVICE"/DATA/PUBLICKEY */
    DRM_DEVCERT_DEVICEPRIVKEY,          /* CERTIFICATE type="DEVICE"/DATA/PRIVATEKEY */
    DRM_DEVCERT_DEVICEDATANODE,         /* CERTIFICATE type="DEVICE"/DATA */
    DRM_DEVCERT_DEVICESIGNATURE,        /* CERTIFICATE type="DEVICE"/MSDRM_SIGNATURE_VALUE */
    DRM_DEVCERT_COMPATIBILITYVERSION,   /* FALLBACK/SECURITYVERSION */
    DRM_DEVCERT_COMPATIBILITYCERT,      /* FALLBACK/CERTIFICATE */
    DRM_DEVCERT_SECURECLOCK,            /* CERTIFICATE type="GROUP"/DATA/FEATURE/CLOCK */
    DRM_DEVCERT_SECURECLOCKURL,         /* CERTIFICATE type="GROUP"/DATA/FEATURE/SECURECLOCK/URL */
    DRM_DEVCERT_SECURECLOCKPUBKEY,      /* CERTIFICATE type="GROUP"/DATA/FEATURE/SECURECLOCK/PUBLICKEY */
    DRM_DEVCERT_METERING,               /* CERTIFICATE type="GROUP"/DATA/FEATURE/METERING */
    DRM_DEVCERT_LICENSEACQUISITIONMODE, /* CERTIFICATE type="GROUP"/DATA/FEATURE/LICENSE_ACQ */
    DRM_DEVCERT_LICENSESYNCMODE,        /* CERTIFICATE type="GROUP"/DATA/FEATURE/LICENSE_SYNC */
    DRM_DEVCERT_SYMMETRICOPTIMIZATIONS, /* CERTIFICATE type="GROUP"/DATA/FEATURE/SYMMETRIC_OPT */
    DRM_DEVCERT_ENCRYPTION,             /* CERTIFICATE type="GROUP"/DATA/FEATURE/ENCRYPTION */
    DRM_DEVCERT_MAXCHAINDEPTH,          /* CERTIFICATE type="GROUP"/DATA/LIMITS/MAXCHAINDEPTH */
    DRM_DEVCERT_MAXLICENSESIZE,         /* CERTIFICATE type="GROUP"/DATA/LIMITS/MAXLICENSESIZE */
    DRM_DEVCERT_MAXHEADERSIZE,          /* CERTIFICATE type="GROUP"/DATA/LIMITS/MAXHEADERSIZE */
    DRM_DEVCERT_GROUPSECURITYLEVEL,     /* CERTIFICATE type="GROUP"/DATA/SECURITYLEVEL */
    DRM_DEVCERT_GROUPCERTPUBKEY,        /* CERTIFICATE type="GROUP"/DATA/PUBLICKEY */
    DRM_DEVCERT_GROUPCERTDATANODE,      /* CERTIFICATE type="GROUP"/DATA */
    DRM_DEVCERT_GROUPCERTSIGNATURE,     /* CERTIFICATE type="GROUP"/MSDRM_SIGNATURE_VALUE */
    DRM_DEVCERT_DACSECURITYLEVEL,       /* CERTIFICATE type="AUTHORIZATION"/DATA/SECURITYLEVEL */
    DRM_DEVCERT_SUBJECTID,              /* CERTIFICATE type="AUTHORIZATION"/DATA/AUTH_ID */
    DRM_DEVCERT_DACPUBKEY,              /* CERTIFICATE type="AUTHORIZATION"/DATA/PUBLICKEY */
    DRM_DEVCERT_DACDATANODE,            /* CERTIFICATE type="AUTHORIZATION"/DATA */
    DRM_DEVCERT_DACSIGNATURE,           /* CERTIFICATE type="AUTHORIZATION"/MSDRM_SIGNATURE_VALUE */
    DRM_DEVCERT_DACROOTPUBKEY,          /* CERTIFICATE type="AUTHORIZATION_ROOT"/DATA/PUBLICKEY */
    DRM_DEVCERT_AUTHROOTDATANODE,       /* CERTIFICATE type="AUTHORIZATION_ROOT"/DATA */
    DRM_DEVCERT_AUTHROOTSIGNATURE,      /* CERTIFICATE type="AUTHORIZATION_ROOT"/MSDRM_SIGNATURE_VALUE */
    DRM_DEVCERT_SUPPORT_REVOCATION,     /* CERTIFICATE type="GROUP"/DATA/FEATURE/SUPPORT_REVOCATION */
    DRM_DEVCERT_ATTRIB_OTHER,
    DRM_DEVCERT_SUPPORTCRL,             /* CERTIFICATE type="GROUP"/DATA/FEATURE/SUPPORT_REVOCATION */
#if DRM_SUPPORT_DEVICE_SIGNING_KEY
    DRM_DEVCERT_DEVICESIGNINGCERTIFICATE,  /* SIGNING/CERTIFICATE */
#endif
    DRM_DEVCERT_DEVICEMODELNAME,        /* CERTIFICATE type="DEVICE"/DATA/NAME */
    DRM_DEVCERT_GROUPSECURITYVERSIONNUM,/* CERTIFICATE type="GROUP"/DATA/SECURITYVERSION/NUMBER */
    DRM_DEVCERT_GROUPPLATFORMID,        /* CERTIFICATE type="GROUP"/DATA/SECURITYVERSION/PLATFORM_ID */
    DRM_DEVCERT_MAXATTRIBUTES
} eDRM_DEVCERT_ATTRIBUTES;

/* Current version of the cert parser cache. */
#define DRM_CERT_PARSER_CACHE_VERSION_1     0x01

/* The maximum character count of a device cert that can use the cert cache. */
#define DRM_MAX_CCH_DEVICE_CERT_FOR_CACHE   8192

/*
** Data structure of an device cert parser cache entry.
** The reason to use DRM_WORD rather than DRM_DWORD to store the string
** position/length is to save memory consumption of the cache since
** device certificate should be within the value range of DRM_WORD.
*/
typedef struct
{
    /* Flag indicating whether the values of this entry are useable. */
    DRM_WORD m_fValid;

    /* The starting position of the node substring. */
    DRM_WORD m_iNodeStart;

    /* The length of the node substring. */
    DRM_WORD m_iNodeLength;

    /* The starting position of the value substring. */
    DRM_WORD m_iValueStart;

    /* The length of the value substring. */
    DRM_WORD m_iValueLength;
} DRM_DEVICE_CERT_PARSER_CACHE_ENTRY;

/* Count of DRM_BYTEs to store a single cert parser entry. */
#define DRM_CB_CERT_PARSER_ENTRY    ( 5 * SIZEOF( DRM_WORD ) )

/* Total count of DRM_BYTEs to store all cert parser entries. */
#define DRM_CB_CERT_PARSER_ENTRIES  ( DRM_DEVCERT_MAXATTRIBUTES * DRM_CB_CERT_PARSER_ENTRY )

/* Data structure of the device cert parser cache. */
typedef struct
{
    /* Flag indicating whether the cache is being used. */
    DRM_BOOL m_fUsed;

    /* Flag indicating whether the cache has been updated. */
    DRM_BOOL m_fUpdated;

    /* SHA-1 hash of the device cert. */
    DRM_BYTE m_rgbSHAHash[ __CB_DECL( DRM_SHA1_DIGEST_LEN ) ];

    /* Byte array to store the packed device cert cache entries. */
    DRM_BYTE m_rgbPacked[ DRM_CB_CERT_PARSER_ENTRIES ];
} DRM_DEVICE_CERT_PARSER_CACHE;

EXIT_PK_NAMESPACE;

#endif /* __DRMDEVCERTCACHE_H__ */

