/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRM_XMR_H__
#define __DRM_XMR_H__

#include <drmoutputleveltypes.h>
#include <oemaescommon.h>

ENTER_PK_NAMESPACE;

#define XMR_RID_OFFSET           ( SIZEOF( DRM_DWORD ) * 2 )
#define XMR_HEADER_LENGTH        ( XMR_RID_OFFSET + SIZEOF( DRM_ID ) )
#define XMR_BASE_OBJECT_LENGTH   ( SIZEOF( DRM_WORD ) * 2  + SIZEOF( DRM_DWORD ) )
#define XMR_MAXIMUM_OBJECT_DEPTH  5

/*
** constants, enums and data types
*/
#define XMR_MAGIC_CONSTANT        0x584D5200 /* 'XMR\0' */

#define XMR_UNLIMITED             MAX_UNSIGNED_TYPE( DRM_DWORD )

#define XMR_AES_OMAC_SIGNATURE_LENGTH     16

enum XMR_VERSION
{
    XMR_VERSION_INVALID  = 0x0000,
    XMR_VERSION_1        = 0x0001,
    XMR_VERSION_2        = 0x0002,
    XMR_VERSION_3        = 0x0003,

    XMR_VERSION_MAX      = XMR_VERSION_3,
};

enum XMR_OBJECT_FLAGS
{
    XMR_FLAGS_NONE                  = 0x0000,
    XMR_FLAGS_MUST_UNDERSTAND       = 0x0001,
    XMR_FLAGS_CONTAINER             = 0x0002,
    XMR_FLAGS_ALLOW_EXTERNAL_PARSE  = 0x0004,
    XMR_FLAGS_BEST_EFFORT           = 0x0008,
    XMR_FLAGS_HAS_SECURE_STATE      = 0x0010
};

enum XMR_SETTINGS_FLAGS
{
    XMR_SETTINGS_FLAG_CANNOT_PERSIST    = 0x0001
};

/*
** Symmetric encryption types used for content encryption
*/
enum XMR_SYMMETRIC_ENCRYPTION_TYPE
{
    XMR_SYMMETRIC_ENCRYPTION_TYPE_INVALID      = 0x0000,
    XMR_SYMMETRIC_ENCRYPTION_TYPE_AES_128_CTR  = 0x0001,
    XMR_SYMMETRIC_ENCRYPTION_TYPE_RC4_CIPHER   = 0x0002,
    XMR_SYMMETRIC_ENCRYPTION_TYPE_AES_128_ECB  = 0x0003,
    XMR_SYMMETRIC_ENCRYPTION_TYPE_COCKTAIL     = 0x0004
};

/*
** Asymmetric encryption types used for encrypting the content key
*/
enum XMR_ASYMMETRIC_ENCRYPTION_TYPE
{
    XMR_ASYMMETRIC_ENCRYPTION_TYPE_INVALID          = 0x0000,
    XMR_ASYMMETRIC_ENCRYPTION_TYPE_RSA_1024         = 0x0001,
    XMR_ASYMMETRIC_ENCRYPTION_TYPE_CHAINED_LICENSE  = 0x0002,
    XMR_ASYMMETRIC_ENCRYPTION_TYPE_ECC_256          = 0x0003,
    XMR_ASYMMETRIC_ENCRYPTION_TYPE_ECC_256_WITH_KZ  = 0x0004
};

/*
** Symmetric encryption types used for encrypting the content key (optimized)
*/
enum XMR_SYMMETRIC_KEY_ENCRYPTION_TYPE
{
    XMR_SYMMETRIC_KEY_ENCRYPTION_TYPE_INVALID          = 0x0000,
    XMR_SYMMETRIC_KEY_ENCRYPTION_TYPE_AES_128_ECB      = 0x0001,
    XMR_SYMMETRIC_KEY_ENCRYPTION_TYPE_AES_128_ECB_SLK  = 0x0002
};

enum XMR_ECC_CURVE_TYPE
{
    XMR_ECC_CURVE_TYPE_INVALID                = 0x0000,
    XMR_ECC_CURVE_TYPE_P256                   = 0x0001
};

enum XMR_SIGNATURE_TYPE
{
    XMR_SIGNATURE_TYPE_INVALID                = 0x0000,
    XMR_SIGNATURE_TYPE_AES_128_OMAC           = 0x0001,
    XMR_SIGNATURE_TYPE_SHA_256_HMAC           = 0x0002
};

enum XMR_GLOBAL_RIGHTS_SETTINGS
{
    XMR_RIGHTS_CANNOT_PERSIST                 = 0x001,
    XMR_RIGHTS_ALLOW_BACKUP_RESTORE           = 0x004,
    XMR_RIGHTS_COLLABORATIVE_PLAY             = 0x008,
    XMR_RIGHTS_BASE_LICENSE                   = 0x010,
                                             /* 0x020 was previously used by THUMBNAIL right in Vista/Polaris and shouldn't be used */
    XMR_RIGHTS_CANNOT_BIND_LICENSE            = 0x040,
    XMR_RIGHTS_TEMP_STORE_ONLY                = 0x080,
};

enum XMR_EXTENSIBLE_RESTRICTON_STATE
{
    XMR_EXTENSIBLE_RESTRICTON_STATE_COUNT      = 0x02,
    XMR_EXTENSIBLE_RESTRICTON_STATE_DATE       = 0x03,
    XMR_EXTENSIBLE_RESTRICTON_STATE_BYTEARRAY  = 0x04,
};

enum XMR_EMBEDDING_BEHAVIOR
{
    XMR_EMBEDDING_BEHAVIOR_INVALID = 0x00,
    XMR_EMBEDDING_BEHAVIOR_IGNORE  = 0x01,
    XMR_EMBEDDING_BEHAVIOR_COPY    = 0x02,
    XMR_EMBEDDING_BEHAVIOR_MOVE    = 0x03
};

enum XMR_UPLINK_CHECKSUM_TYPE
{
    XMR_UPLINK_CHECKSUM_TYPE_XMRV1      = 0x00,
    XMR_UPLINK_CHECKSUM_TYPE_AESOMAC1   = 0x01,
};

enum XMR_OBJECT_TYPE
{
    XMR_OBJECT_TYPE_INVALID                                            = 0x0000,
    XMR_OBJECT_TYPE_OUTER_CONTAINER                                    = 0x0001,
    XMR_OBJECT_TYPE_GLOBAL_POLICY_CONTAINER                            = 0x0002,
    XMR_OBJECT_TYPE_MINIMUM_ENVIRONMENT_OBJECT                         = 0x0003,
    XMR_OBJECT_TYPE_PLAYBACK_POLICY_CONTAINER                          = 0x0004,
    XMR_OBJECT_TYPE_OUTPUT_PROTECTION_OBJECT                           = 0x0005,
    XMR_OBJECT_TYPE_UPLINK_KID_OBJECT                                  = 0x0006,
    XMR_OBJECT_TYPE_EXPLICIT_ANALOG_VIDEO_OUTPUT_PROTECTION_CONTAINER  = 0x0007,
    XMR_OBJECT_TYPE_ANALOG_VIDEO_OUTPUT_CONFIGURATION_OBJECT           = 0x0008,
    XMR_OBJECT_TYPE_KEY_MATERIAL_CONTAINER                             = 0x0009,
    XMR_OBJECT_TYPE_CONTENT_KEY_OBJECT                                 = 0x000A,
    XMR_OBJECT_TYPE_SIGNATURE_OBJECT                                   = 0x000B,
    XMR_OBJECT_TYPE_SERIAL_NUMBER_OBJECT                               = 0x000C,
    XMR_OBJECT_TYPE_SETTINGS_OBJECT                                    = 0x000D,
    XMR_OBJECT_TYPE_COPY_POLICY_CONTAINER                              = 0x000E,
    XMR_OBJECT_TYPE_ALLOW_PLAYLISTBURN_POLICY_CONTAINER                = 0x000F,
    XMR_OBJECT_TYPE_INCLUSION_LIST_OBJECT                              = 0x0010,
    XMR_OBJECT_TYPE_PRIORITY_OBJECT                                    = 0x0011,
    XMR_OBJECT_TYPE_EXPIRATION_OBJECT                                  = 0x0012,
    XMR_OBJECT_TYPE_ISSUEDATE_OBJECT                                   = 0x0013,
    XMR_OBJECT_TYPE_EXPIRATION_AFTER_FIRSTUSE_OBJECT                   = 0x0014,
    XMR_OBJECT_TYPE_EXPIRATION_AFTER_FIRSTSTORE_OBJECT                 = 0x0015,
    XMR_OBJECT_TYPE_METERING_OBJECT                                    = 0x0016,
    XMR_OBJECT_TYPE_PLAYCOUNT_OBJECT                                   = 0x0017,
    XMR_OBJECT_TYPE_GRACE_PERIOD_OBJECT                                = 0x001A,
    XMR_OBJECT_TYPE_COPYCOUNT_OBJECT                                   = 0x001B,
    XMR_OBJECT_TYPE_COPY_PROTECTION_OBJECT                             = 0x001C,
    XMR_OBJECT_TYPE_PLAYLISTBURN_COUNT_OBJECT                          = 0x001F,
    XMR_OBJECT_TYPE_REVOCATION_INFORMATION_VERSION_OBJECT              = 0x0020,
    XMR_OBJECT_TYPE_RSA_DEVICE_KEY_OBJECT                              = 0x0021,
    XMR_OBJECT_TYPE_SOURCEID_OBJECT                                    = 0x0022,
    XMR_OBJECT_TYPE_REVOCATION_CONTAINER                               = 0x0025,
    XMR_OBJECT_TYPE_RSA_LICENSE_GRANTER_KEY_OBJECT                     = 0x0026,
    XMR_OBJECT_TYPE_USERID_OBJECT                                      = 0x0027,
    XMR_OBJECT_TYPE_RESTRICTED_SOURCEID_OBJECT                         = 0x0028,
    XMR_OBJECT_TYPE_DOMAIN_ID_OBJECT                                   = 0x0029,
    XMR_OBJECT_TYPE_ECC_DEVICE_KEY_OBJECT                              = 0x002A,
    XMR_OBJECT_TYPE_GENERATION_NUMBER_OBJECT                           = 0x002B,
    XMR_OBJECT_TYPE_POLICY_METADATA_OBJECT                             = 0x002C,
    XMR_OBJECT_TYPE_OPTIMIZED_CONTENT_KEY_OBJECT                       = 0x002D,
    XMR_OBJECT_TYPE_EXPLICIT_DIGITAL_AUDIO_OUTPUT_PROTECTION_CONTAINER = 0x002E,
    XMR_OBJECT_TYPE_RINGTONE_POLICY_CONTAINER                          = 0x002F,
    XMR_OBJECT_TYPE_EXPIRATION_AFTER_FIRSTPLAY_OBJECT                  = 0x0030,
    XMR_OBJECT_TYPE_DIGITAL_AUDIO_OUTPUT_CONFIGURATION_OBJECT          = 0x0031,
    XMR_OBJECT_TYPE_REVOCATION_INFORMATION_VERSION_2_OBJECT            = 0x0032,
    XMR_OBJECT_TYPE_EMBEDDING_BEHAVIOR_OBJECT                          = 0x0033,
    XMR_OBJECT_TYPE_SECURITY_LEVEL                                     = 0x0034,
    XMR_OBJECT_TYPE_COPY_TO_PC_CONTAINER                               = 0x0035,
    XMR_OBJECT_TYPE_PLAY_ENABLER_CONTAINER                             = 0x0036,
    XMR_OBJECT_TYPE_MOVE_ENABLER_OBJECT                                = 0x0037,
    XMR_OBJECT_TYPE_COPY_ENABLER_CONTAINER                             = 0x0038,
    XMR_OBJECT_TYPE_PLAY_ENABLER_OBJECT                                = 0x0039,
    XMR_OBJECT_TYPE_COPY_ENABLER_OBJECT                                = 0x003A,
    XMR_OBJECT_TYPE_UPLINK_KID_2_OBJECT                                = 0x003B,
    XMR_OBJECT_TYPE_COPY_POLICY_2_CONTAINER                            = 0x003C,
    XMR_OBJECT_TYPE_COPYCOUNT_2_OBJECT                                 = 0x003D,
    XMR_OBJECT_TYPE_RINGTONE_ENABLER_OBJECT                            = 0x003E,
    XMR_OBJECT_TYPE_EXECUTE_POLICY_CONTAINER                           = 0x003F,
    XMR_OBJECT_TYPE_EXECUTE_POLICY_OBJECT                              = 0x0040,
    XMR_OBJECT_TYPE_READ_POLICY_CONTAINER                              = 0x0041,
    XMR_OBJECT_TYPE_EXTENSIBLE_POLICY_RESERVED_42                      = 0x0042,
    XMR_OBJECT_TYPE_EXTENSIBLE_POLICY_RESERVED_43                      = 0x0043,
    XMR_OBJECT_TYPE_EXTENSIBLE_POLICY_RESERVED_44                      = 0x0044,
    XMR_OBJECT_TYPE_EXTENSIBLE_POLICY_RESERVED_45                      = 0x0045,
    XMR_OBJECT_TYPE_EXTENSIBLE_POLICY_RESERVED_46                      = 0x0046,
    XMR_OBJECT_TYPE_EXTENSIBLE_POLICY_RESERVED_47                      = 0x0047,
    XMR_OBJECT_TYPE_EXTENSIBLE_POLICY_RESERVED_48                      = 0x0048,
    XMR_OBJECT_TYPE_EXTENSIBLE_POLICY_RESERVED_49                      = 0x0049,
    XMR_OBJECT_TYPE_EXTENSIBLE_POLICY_RESERVED_4A                      = 0x004A,
    XMR_OBJECT_TYPE_EXTENSIBLE_POLICY_RESERVED_4B                      = 0x004B,
    XMR_OBJECT_TYPE_EXTENSIBLE_POLICY_RESERVED_4C                      = 0x004C,
    XMR_OBJECT_TYPE_EXTENSIBLE_POLICY_RESERVED_4D                      = 0x004D,
    XMR_OBJECT_TYPE_EXTENSIBLE_POLICY_RESERVED_4E                      = 0x004E,
    XMR_OBJECT_TYPE_EXTENSIBLE_POLICY_RESERVED_4F                      = 0x004F,
    XMR_OBJECT_TYPE_REMOVAL_DATE_OBJECT                                = 0x0050,
    XMR_OBJECT_TYPE_AUX_KEY_OBJECT                                     = 0x0051,
    XMR_OBJECT_TYPE_UPLINKX_OBJECT                                     = 0x0052,
    XMR_OBJECT_TYPE_INVALID_RESERVED_53                                = 0x0053,    /* Deprecated: 0x0053 was documented in PlayReady 2.0 CHM for Content Boundary Identification Object */
    XMR_OBJECT_TYPE_APPLICATION_ID_LIST                                = 0x0054,
    XMR_OBJECT_TYPE_REAL_TIME_EXPIRATION                               = 0x0055,
    XMR_OBJECT_TYPE_ND_TX_AUTH_CONTAINER                               = 0x0056,
    XMR_OBJECT_TYPE_ND_TX_AUTH_OBJECT                                  = 0x0057,
    XMR_OBJECT_TYPE_MAXIMUM_DEFINED                                    = 0x0057
};

typedef struct
{
    DRM_BOOL                fIsContainer;
    DRM_WORD                wParent;
    DRM_WORD                wFlags;
} XMR_COMMON_INTERNAL_DEFINES;

extern const DRM_EXPORT_VAR XMR_COMMON_INTERNAL_DEFINES g_xmrCommonDefines[XMR_OBJECT_TYPE_MAXIMUM_DEFINED+1];


#define XMR_RIGHTS_COPY_FROM_V1 19



typedef struct __tagDRM_XMR_WORD
{
    DRM_BOOL fValid;
    DRM_WORD wValue;
} DRM_XMR_WORD;

typedef struct __tagDRM_XMR_DWORD
{
    DRM_BOOL  fValid;
    DRM_DWORD dwValue;
} DRM_XMR_DWORD;

typedef DRM_OBFUS_FIXED_ALIGN struct __tagDRM_XMR_GUID
{
    DRM_BOOL  fValid;
DRM_OBFUS_FILL_BYTES(4)
DRM_OBFUS_PTR_TOP
    DRM_BYTE  *pguidBuffer;
DRM_OBFUS_PTR_BTM
    DRM_DWORD  iGuid;
DRM_OBFUS_FILL_BYTES(4)
} DRM_XMR_GUID;

typedef DRM_OBFUS_FIXED_ALIGN struct __tagDRM_XMR_GUIDLIST
{
    DRM_BOOL   fValid;
    DRM_DWORD  cGUIDs;
DRM_OBFUS_PTR_TOP
    DRM_BYTE  *pguidBuffer;
DRM_OBFUS_PTR_BTM
    DRM_DWORD  iGuids;
DRM_OBFUS_FILL_BYTES(4)
} DRM_XMR_GUIDLIST;

typedef DRM_OBFUS_FIXED_ALIGN struct __tagDRM_XMR_BYTEARRAY
{
    DRM_BOOL   fValid;
    DRM_DWORD  cbData;
DRM_OBFUS_PTR_TOP
    DRM_BYTE  *pbDataBuffer;
DRM_OBFUS_PTR_BTM
    DRM_DWORD  iData;
DRM_OBFUS_FILL_BYTES(4)
} DRM_XMR_BYTEARRAY;

typedef struct __tagDRM_XMR_EMPTY
{
    DRM_BOOL  fValid;
} DRM_XMR_EMPTY;

typedef struct __tagDRM_XMR_DWORD_VERSIONED
{
    DRM_BOOL  fValid;
    DRM_DWORD dwVersion;    /* Only used for validation purposes during parsing, sometimes used when building V1 XMR licenses to decide which object type to use (defaults to the V1 object) */
    DRM_DWORD dwValue;
} DRM_XMR_DWORD_VERSIONED;


/*
** Structures for Global requirements container
*/
typedef struct __tagDRM_XMR_MINIMUM_ENVIRONMENT
{
    DRM_BOOL    fValid;
    DRM_DWORD   dwVersion;   /* Only used for validation purposes during parsing */
    DRM_WORD    wMinimumSecurityLevel;
    DRM_DWORD   dwMinimumAppRevocationListVersion;
    DRM_DWORD   dwMinimumDeviceRevocationListVersion;
} DRM_XMR_MINIMUM_ENVIRONMENT;


typedef DRM_XMR_BYTEARRAY           DRM_XMR_SERIAL_NUMBER;
typedef DRM_XMR_WORD                DRM_XMR_RIGHTS;
typedef DRM_XMR_DWORD_VERSIONED     DRM_XMR_REVOCATION_INFORMATION_VERSION;
typedef DRM_XMR_DWORD               DRM_XMR_PRIORITY;
typedef DRM_XMR_DWORD               DRM_XMR_SOURCEID;
typedef DRM_XMR_EMPTY               DRM_XMR_RESTRICTED_SOURCEID;
typedef DRM_XMR_EMPTY               DRM_XMR_REAL_TIME_EXPIRATION;
typedef DRM_XMR_WORD                DRM_XMR_EMBEDDING_BEHAVIOR;
typedef DRM_XMR_DWORD               DRM_XMR_MOVE_ENABLER;

enum  XMR_SOURCEID
{
    XMR_SOURCEID_NONE          = 0,
    XMR_SOURCEID_MACROVISION   = 1,
    XMR_SOURCEID_CGMSA         = 2,
    XMR_SOURCEID_WSS           = 3,
    XMR_SOURCEID_DIGITAL_CABLE = 4,
    XMR_SOURCEID_ATSC          = 5,
    XMR_SOURCEID_PDRM          = 260,
    XMR_SOURCEID_LEGACY_DVR    = 261,
    XMR_SOURCEID_V1            = 262,
};

#define XMR_SOURCEID_MAXCOUNT   100

typedef struct __tagDRM_XMR_EXPIRATION
{
    DRM_BOOL    fValid;
    DRM_DWORD   dwBeginDate;
    DRM_DWORD   dwEndDate;
} DRM_XMR_EXPIRATION;


typedef DRM_XMR_DWORD           DRM_XMR_ISSUEDATE;
typedef DRM_XMR_DWORD           DRM_XMR_GRACE_PERIOD;
typedef DRM_XMR_GUID            DRM_XMR_METERING;
typedef DRM_XMR_DWORD_VERSIONED DRM_XMR_EXPIRATION_AFTER_FIRSTUSE; /* dwVersion == 2 means this represents expiration after first play, it represents expiration after first use otherwise */
typedef DRM_XMR_DWORD           DRM_XMR_EXPIRATION_AFTER_FIRSTSTORE;
typedef DRM_XMR_GUIDLIST        DRM_XMR_INCLUSION_LIST;

typedef DRM_OBFUS_FIXED_ALIGN struct __tagDRM_XMR_UNKNOWN_OBJECT
{
    DRM_BOOL                            fValid;
    DRM_WORD                            wType;
    DRM_WORD                            wFlags;
DRM_OBFUS_PTR_TOP
    DRM_BYTE                           *pbBuffer;
DRM_OBFUS_PTR_BTM
    DRM_DWORD                           ibData;
    DRM_DWORD                           cbData;
DRM_OBFUS_PTR_TOP
    struct __tagDRM_XMR_UNKNOWN_OBJECT *pNext; /* Linked list */
DRM_OBFUS_PTR_BTM
} DRM_XMR_UNKNOWN_OBJECT;

typedef DRM_OBFUS_FIXED_ALIGN struct __tagDRM_XMR_UNKNOWN_CONTAINER
{
    DRM_BOOL                                         fValid;
    DRM_WORD                                         wType;
    DRM_WORD                                         wFlags;
DRM_OBFUS_PTR_TOP
    DRM_XMR_UNKNOWN_OBJECT                           *pObject;
DRM_OBFUS_PTR_BTM
DRM_OBFUS_PTR_TOP
    struct __tagDRM_XMR_UNKNOWN_CONTAINER            *pUnkChildcontainer;/* Linked list */
DRM_OBFUS_PTR_BTM
DRM_OBFUS_PTR_TOP
    struct __tagDRM_XMR_UNKNOWN_CONTAINER            *pNext; /* Linked list */
DRM_OBFUS_PTR_BTM
} DRM_XMR_UNKNOWN_CONTAINER;

typedef DRM_OBFUS_FIXED_ALIGN struct __tagDRM_XMR_ND_TX_AUTH_OBJECT
{
    DRM_BOOL                            fValid;
    DRM_WORD                            wVersion;
DRM_OBFUS_PTR_TOP
    DRM_BYTE                           *pbBufferClient;
DRM_OBFUS_PTR_BTM
    DRM_DWORD                           ibDataClient;
    DRM_DWORD                           cbDataClient;
DRM_OBFUS_PTR_TOP
    DRM_BYTE                           *pbBufferService;
DRM_OBFUS_PTR_BTM
    DRM_DWORD                           ibDataService;
    DRM_DWORD                           cbDataService;
DRM_OBFUS_PTR_TOP
    struct __tagDRM_XMR_ND_TX_AUTH_OBJECT *pNext; /* Linked list */
DRM_OBFUS_PTR_BTM
} DRM_XMR_ND_TX_AUTH_OBJECT;

typedef DRM_OBFUS_FIXED_ALIGN struct __tagDRM_XMR_ND_TX_AUTH_CONTAINER
{
    DRM_BOOL                                         fValid;
DRM_OBFUS_FILL_BYTES(4)
DRM_OBFUS_PTR_TOP
    struct __tagDRM_XMR_ND_TX_AUTH_OBJECT            *pAuthObject; /* Linked list */
DRM_OBFUS_PTR_BTM
} DRM_XMR_ND_TX_AUTH_CONTAINER;

typedef DRM_XMR_DWORD DRM_XMR_GENERATION_NUMBER;

typedef DRM_OBFUS_FIXED_ALIGN struct __tagDRM_XMR_DOMAIN_ID
{
    DRM_BOOL    fValid;
DRM_OBFUS_FILL_BYTES(4)
DRM_OBFUS_PTR_TOP
    DRM_BYTE   *pbAccountID;
DRM_OBFUS_PTR_BTM
    DRM_DWORD   ibAccountID;
    DRM_DWORD   cbAccountID;
    DRM_DWORD   dwRevision;
DRM_OBFUS_FILL_BYTES(4)
} DRM_XMR_DOMAIN_ID;

typedef DRM_OBFUS_FIXED_ALIGN struct __tagDRM_XMR_POLICY_METADATA_OBJECT
{
    DRM_BOOL     fValid;
DRM_OBFUS_FILL_BYTES(4)
DRM_OBFUS_PTR_TOP
    DRM_BYTE    *pMetadataTypeGuidBuffer;
DRM_OBFUS_PTR_BTM
    DRM_DWORD    iMetadataTypeGuid;
    DRM_DWORD    cbPolicyData;
DRM_OBFUS_PTR_TOP
    DRM_BYTE    *pbPolicyDataBuffer;
DRM_OBFUS_PTR_BTM
    DRM_DWORD    iPolicyData;
DRM_OBFUS_FILL_BYTES(4)
} DRM_XMR_POLICY_METADATA_OBJECT;

typedef DRM_OBFUS_FIXED_ALIGN struct __tagDRM_XMR_POLICY_METADATA_LIST
{
    DRM_XMR_POLICY_METADATA_OBJECT            MetadataObject;
DRM_OBFUS_PTR_TOP
    struct __tagDRM_XMR_POLICY_METADATA_LIST *pNext;
DRM_OBFUS_PTR_BTM
} DRM_XMR_POLICY_METADATA_LIST;

typedef DRM_OBFUS_FIXED_ALIGN struct __tagDRM_XMR_POLICY_METADATA
{
    DRM_BOOL                      fValid;
    DRM_DWORD                     cPolicyMetadataObjects;
DRM_OBFUS_PTR_TOP
    DRM_XMR_POLICY_METADATA_LIST *plistPolicyMetadataObjects;
DRM_OBFUS_PTR_BTM
} DRM_XMR_POLICY_METADATA;

typedef DRM_OBFUS_FIXED_ALIGN struct __tagDRM_XMR_REMOVAL_DATE
{
    DRM_BOOL    fValid;
    DRM_DWORD   dwRemovalDate;
} DRM_XMR_REMOVAL_DATE;

typedef DRM_OBFUS_FIXED_ALIGN struct __tagDRM_XMR_GLOBAL_REQUIREMENTS
{
    DRM_BOOL                                 fValid;
    DRM_XMR_MINIMUM_ENVIRONMENT              MinimumEnvironment;
    DRM_XMR_SERIAL_NUMBER                    SerialNumber;
    DRM_XMR_RIGHTS                           Rights;
    DRM_XMR_PRIORITY                         Priority;
    DRM_XMR_SOURCEID                         SourceID;
    DRM_XMR_RESTRICTED_SOURCEID              RestrictedSourceID;
    DRM_XMR_EXPIRATION                       Expiration;
    DRM_XMR_REAL_TIME_EXPIRATION             RealTimeExpiration;
    DRM_XMR_ISSUEDATE                        IssueDate;
    DRM_XMR_GRACE_PERIOD                     GracePeriod;
DRM_OBFUS_FILL_BYTES(4)
    DRM_XMR_METERING                         Metering;
    DRM_XMR_EXPIRATION_AFTER_FIRSTUSE        ExpirationAfterUse;
    DRM_XMR_EXPIRATION_AFTER_FIRSTSTORE      ExpirationAfterStore;
DRM_OBFUS_FILL_BYTES(4)
    DRM_XMR_INCLUSION_LIST                   InclusionList;
    DRM_XMR_REVOCATION_INFORMATION_VERSION   RevocationInformationVersion;
DRM_OBFUS_FILL_BYTES(4)
    DRM_XMR_DOMAIN_ID                        DomainID;
    DRM_XMR_EMBEDDING_BEHAVIOR               EmbeddingBehavior;
DRM_OBFUS_PTR_TOP
    DRM_XMR_UNKNOWN_OBJECT                  *pUnknownObjects;
DRM_OBFUS_PTR_BTM
    DRM_XMR_POLICY_METADATA                  PolicyMetadata;
    DRM_XMR_REMOVAL_DATE                     RemovalDate;
} DRM_XMR_GLOBAL_REQUIREMENTS;

/*
**  Structures for playback policies container
*/
typedef DRM_XMR_DWORD DRM_XMR_PLAYCOUNT;

typedef struct __tagDRM_XMR_MINIMUM_OUTPUT_PROTECTION_LEVELS
{
    DRM_BOOL fValid;
    DRM_WORD wCompressedDigitalVideo;
    DRM_WORD wUncompressedDigitalVideo;
    DRM_WORD wAnalogVideo;
    DRM_WORD wCompressedDigitalAudio;
    DRM_WORD wUncompressedDigitalAudio;
    DRM_DWORD        cbRawData;
DRM_OBFUS_FILL_BYTES(4)
DRM_OBFUS_PTR_TOP
    const DRM_BYTE  *pbRawData;
DRM_OBFUS_PTR_BTM
    DRM_DWORD        iRawData;
DRM_OBFUS_FILL_BYTES(4)
} DRM_XMR_MINIMUM_OUTPUT_PROTECTION_LEVELS;

typedef struct __tagDRM_XMR_OUTPUT_CONFIGURATION
{
    DRM_BOOL     fValid;
    DRM_BYTE    *pguidBuffer;
    DRM_DWORD    iGuid;
    DRM_DWORD    cbConfigData;
    DRM_BYTE    *pbConfigDataBuffer;
    DRM_DWORD    iConfigData;
} DRM_XMR_OUTPUT_CONFIGURATION;
typedef DRM_XMR_OUTPUT_CONFIGURATION DRM_XMR_VIDEO_OUTPUT_CONFIGURATION;
typedef DRM_XMR_OUTPUT_CONFIGURATION DRM_XMR_AUDIO_OUTPUT_CONFIGURATION;

typedef struct __tagDRM_XMR_OUTPUT_CONFIGURATION_LIST
{
    DRM_XMR_OUTPUT_CONFIGURATION                   Config;
    struct __tagDRM_XMR_OUTPUT_CONFIGURATION_LIST *pNext;
} DRM_XMR_OUTPUT_CONFIGURATION_LIST;
typedef DRM_XMR_OUTPUT_CONFIGURATION_LIST DRM_XMR_VIDEO_OUTPUT_CONFIGURATION_LIST;
typedef DRM_XMR_OUTPUT_CONFIGURATION_LIST DRM_XMR_AUDIO_OUTPUT_CONFIGURATION_LIST;

typedef DRM_OBFUS_FIXED_ALIGN struct __tagDRM_XMR_EXPLICIT_OUTPUT_PROTECTION
{
    DRM_BOOL         fValid;
    DRM_DWORD        cOutputProtectionIDs;
    DRM_DWORD        cbRawData;
DRM_OBFUS_FILL_BYTES(4)
DRM_OBFUS_PTR_TOP
    const DRM_BYTE  *pbRawData;
DRM_OBFUS_PTR_BTM
    DRM_DWORD        iRawData;
DRM_OBFUS_FILL_BYTES(4)
DRM_OBFUS_PTR_TOP
    DRM_XMR_OUTPUT_CONFIGURATION_LIST *plistOutputConfiguration;
DRM_OBFUS_PTR_BTM
} DRM_XMR_EXPLICIT_OUTPUT_PROTECTION;
typedef DRM_XMR_EXPLICIT_OUTPUT_PROTECTION DRM_XMR_EXPLICIT_ANALOG_VIDEO_PROTECTION;
typedef DRM_XMR_EXPLICIT_OUTPUT_PROTECTION DRM_XMR_EXPLICIT_DIGITAL_AUDIO_PROTECTION;

typedef DRM_OBFUS_FIXED_ALIGN struct __tagDRM_XMR_PLAYBACK_RIGHTS
{
    DRM_BOOL                                   fValid;
    DRM_XMR_PLAYCOUNT                          PlayCount;
DRM_OBFUS_FILL_BYTES(4)
    DRM_XMR_MINIMUM_OUTPUT_PROTECTION_LEVELS   opl;
DRM_OBFUS_FILL_BYTES(8)
    DRM_XMR_EXPLICIT_ANALOG_VIDEO_PROTECTION   containerExplicitAnalogVideoProtection;
    DRM_XMR_EXPLICIT_DIGITAL_AUDIO_PROTECTION  containerExplicitDigitalAudioProtection;
DRM_OBFUS_PTR_TOP
    DRM_XMR_UNKNOWN_OBJECT                    *pUnknownObjects;
DRM_OBFUS_PTR_BTM
    DRM_XMR_UNKNOWN_CONTAINER                  UnknownContainer;
} DRM_XMR_PLAYBACK_RIGHTS;

typedef struct __tagDRM_XMR_COPY_TO_PC
{
    DRM_BOOL                                   fValid;
} DRM_XMR_COPY_TO_PC;

/*
**  Maximum allowable CopyCount
*/
#define XMR_MAX_COPY_COUNT 249

/*
**  Structures for copy policies container
*/
typedef DRM_XMR_DWORD_VERSIONED     DRM_XMR_COPY_COUNT;
typedef DRM_XMR_WORD                DRM_XMR_COPY_PROTECTION_LEVEL;
typedef DRM_OBFUS_FIXED_ALIGN struct __tagDRM_XMR_COPY_RIGHTS
{
    DRM_BOOL                        fValid;
    DRM_DWORD                       dwVersion;      /* Used for validation purposes during parsing, used when building V1 XMR licenses to decide which object type to use (defaults to XMR_OBJECT_TYPE_COPY_POLICY_2_CONTAINER) */
    DRM_XMR_COPY_COUNT              CopyCount;      /* Object type for DRM_XMR_COPY_COUNT will be determined based on object type for DRM_XMR_COPY_RIGHTS */
    DRM_XMR_COPY_PROTECTION_LEVEL   CopyProtectionLevel;
    DRM_XMR_MOVE_ENABLER            MoveEnabler;
DRM_OBFUS_FILL_BYTES(4)
DRM_OBFUS_PTR_TOP
    DRM_XMR_UNKNOWN_OBJECT         *pUnknownObjects;
DRM_OBFUS_PTR_BTM
    DRM_XMR_UNKNOWN_CONTAINER       UnknownContainer;
} DRM_XMR_COPY_RIGHTS;

/*
**  Structures for playlistburn policies container
*/
typedef struct __tagDRM_XMR_PLAYLIST_BURN_RESTRICTIONS
{
    DRM_BOOL    fValid;
    DRM_DWORD   dwMaxPlaylistBurnCount;
    DRM_DWORD   dwPlaylistBurnTrackCount;
} DRM_XMR_PLAYLIST_BURN_RESTRICTIONS;

typedef DRM_OBFUS_FIXED_ALIGN struct __tagDRM_XMR_PLAYLIST_BURN_RIGHTS
{
    DRM_BOOL                           fValid;
    DRM_XMR_PLAYLIST_BURN_RESTRICTIONS Restrictions;
DRM_OBFUS_PTR_TOP
    DRM_XMR_UNKNOWN_OBJECT            *pUnknownObjects;
DRM_OBFUS_PTR_BTM
} DRM_XMR_PLAYLIST_BURN_RIGHTS;


/*
** Structures for Revocation container
*/
typedef DRM_OBFUS_FIXED_ALIGN struct __tagDRM_XMR_RSA_PUBKEY
{
    DRM_BOOL    fValid;
    DRM_DWORD   dwExponent;
    DRM_WORD    cbModulus;
DRM_OBFUS_FILL_BYTES(4)
DRM_OBFUS_PTR_TOP
    DRM_BYTE   *pbModulusBuffer;
DRM_OBFUS_PTR_BTM
    DRM_DWORD   iModulus;
DRM_OBFUS_FILL_BYTES(4)
} DRM_XMR_RSA_PUBKEY;

typedef DRM_XMR_RSA_PUBKEY DRM_XMR_RSA_LICENSE_GRANTER_KEY;

typedef DRM_OBFUS_FIXED_ALIGN struct __tagDRM_XMR_USERID
{
    DRM_BOOL     fValid;
    DRM_DWORD    cbUserID;
DRM_OBFUS_PTR_TOP
    DRM_BYTE    *pbUserID;
DRM_OBFUS_PTR_BTM
    DRM_DWORD    iUserID;
DRM_OBFUS_FILL_BYTES(4)
} DRM_XMR_USERID;

typedef DRM_OBFUS_FIXED_ALIGN struct __tagDRM_XMR_REVOCATION
{
    DRM_BOOL                        fValid;
DRM_OBFUS_FILL_BYTES(4)
    DRM_XMR_RSA_LICENSE_GRANTER_KEY RsaLicenseGranterKey;
    DRM_XMR_USERID                  UserID;
} DRM_XMR_REVOCATION;

/*
**  Structures for Key Material container
*/
typedef DRM_OBFUS_FIXED_ALIGN struct __tagDRM_XMR_CONTENT_KEY
{
    DRM_BOOL     fValid;
DRM_OBFUS_FILL_BYTES(4)
DRM_OBFUS_PTR_TOP
    DRM_BYTE    *pbguidKeyID;
DRM_OBFUS_PTR_BTM
    DRM_DWORD    iguidKeyID;
    DRM_WORD     wSymmetricCipherType;
    DRM_WORD     wKeyEncryptionCipherType;
    DRM_WORD     cbEncryptedKey;
DRM_OBFUS_FILL_BYTES(4)
DRM_OBFUS_PTR_TOP
    DRM_BYTE    *pbEncryptedKeyBuffer;
DRM_OBFUS_PTR_BTM
    DRM_DWORD    iEncryptedKey;
DRM_OBFUS_FILL_BYTES(4)
} DRM_XMR_CONTENT_KEY;

typedef DRM_OBFUS_FIXED_ALIGN struct __tagDRM_XMR_OPTIMIZED_CONTENT_KEY
{
    DRM_BOOL     fValid;
    DRM_WORD     wKeyEncryptionCipherType;
    DRM_WORD     cbEncryptedKey;
DRM_OBFUS_PTR_TOP
    DRM_BYTE    *pbEncryptedKeyBuffer;
DRM_OBFUS_PTR_BTM
    DRM_DWORD    iEncryptedKey;
DRM_OBFUS_FILL_BYTES(4)
} DRM_XMR_OPTIMIZED_CONTENT_KEY;

PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_POOR_DATAALIGNMENT, "Structure sequence is maintained to keep related structure members logically co-located.")
typedef DRM_OBFUS_FIXED_ALIGN struct __tagDRM_XMR_ECC_DEVICE_KEY
{
    DRM_BOOL    fValid;
    DRM_WORD    wEccCurveType;
    DRM_DWORD   iKeyData;
    DRM_WORD    cbKeyData;
DRM_OBFUS_PTR_TOP
    DRM_BYTE   *pbKeyData;
DRM_OBFUS_PTR_BTM
} DRM_XMR_ECC_DEVICE_KEY;
PREFAST_POP

typedef DRM_XMR_RSA_PUBKEY DRM_XMR_DEVICE_KEY;


PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_POOR_DATAALIGNMENT, "Structure sequence is maintained to keep related structure members logically co-located.")
typedef DRM_OBFUS_FIXED_ALIGN struct __tagDRM_XMR_UPLINK_KID
{
    DRM_BOOL     fValid;
    DRM_DWORD    dwVersion;    /* Only used for validation purposes during parsing */
DRM_OBFUS_PTR_TOP
    DRM_BYTE    *pbguidUplinkKID;
DRM_OBFUS_PTR_BTM
    DRM_DWORD    iguidUplinkKID;
    DRM_WORD     cbChainedCheckSum;
DRM_OBFUS_PTR_TOP
    DRM_BYTE    *pbChainedCheckSumBuffer;
DRM_OBFUS_PTR_BTM
    DRM_DWORD    iChainedCheckSum;
    DRM_WORD     wChecksumType;
} DRM_XMR_UPLINK_KID;
PREFAST_POP

typedef DRM_OBFUS_FIXED_ALIGN struct __tagDRM_XMR_AUX_KEY_ENTRY
{
    DRM_DWORD dwLocation;
    DRM_BYTE  rgbKey[DRM_AES_KEYSIZE_128];
} DRM_XMR_AUX_KEY_ENTRY;

typedef DRM_OBFUS_FIXED_ALIGN struct __tagDRM_XMR_AUX_KEY
{
    DRM_BOOL   fValid;
    DRM_WORD   cEntries;
DRM_OBFUS_PTR_TOP
    DRM_XMR_AUX_KEY_ENTRY *pEntries;
DRM_OBFUS_PTR_BTM
} DRM_XMR_AUX_KEY;

PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_POOR_DATAALIGNMENT, "Structure sequence is maintained to keep related structure members logically co-located.")
typedef DRM_OBFUS_FIXED_ALIGN struct __tagDRM_XMR_UPLINKX
{
    DRM_BOOL     fValid;
DRM_OBFUS_FILL_BYTES(4)
DRM_OBFUS_PTR_TOP
    DRM_BYTE    *pbguidUplinkKID;
DRM_OBFUS_PTR_BTM
    DRM_DWORD    iguidUplinkKID;
    DRM_WORD     cbCheckSum;
DRM_OBFUS_PTR_TOP
    DRM_BYTE    *pbCheckSumBuffer;
DRM_OBFUS_PTR_BTM
    DRM_DWORD    iCheckSum;
    DRM_WORD     cEntries;
DRM_OBFUS_PTR_TOP
    DRM_DWORD   *pdwLocation;
DRM_OBFUS_PTR_BTM
DRM_OBFUS_PTR_TOP
    DRM_BYTE    *pbKey;
DRM_OBFUS_PTR_BTM
} DRM_XMR_UPLINKX;
PREFAST_POP

typedef DRM_OBFUS_FIXED_ALIGN struct __tagDRM_XMR_KEY_MATERIAL
{
    DRM_BOOL                        fValid;
DRM_OBFUS_FILL_BYTES(4)
    DRM_XMR_CONTENT_KEY             ContentKey;
    DRM_XMR_OPTIMIZED_CONTENT_KEY   OptimizedContentKey;
    DRM_XMR_DEVICE_KEY              DeviceKey;
    DRM_XMR_ECC_DEVICE_KEY          ECCKey;
    DRM_XMR_UPLINK_KID              UplinkKid;
    DRM_XMR_AUX_KEY                 AuxKey;
    DRM_XMR_UPLINKX                 UplinkX;
} DRM_XMR_KEY_MATERIAL;

/*
**  The signature object will be used by caller only during parsing. The
**  builder ignores any data that is passed in this object. It instead populates
**  it itself.
*/
PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_POOR_DATAALIGNMENT, "Structure sequence is maintained to keep related structure members logically co-located.")
typedef DRM_OBFUS_FIXED_ALIGN struct __tagDRM_XMR_SIGNATURE
{
    DRM_BOOL    fValid;
    DRM_WORD    wType;
DRM_OBFUS_PTR_TOP
    DRM_BYTE   *pbSignatureBuffer;
DRM_OBFUS_PTR_BTM
    DRM_DWORD   iSignature;
    DRM_WORD    cbSignature;
} DRM_XMR_SIGNATURE;
PREFAST_POP

typedef DRM_OBFUS_FIXED_ALIGN struct __tagDRM_XMR_OUTER_CONTAINER
{
    DRM_BOOL                        fValid;
DRM_OBFUS_FILL_BYTES(4)
    DRM_XMR_GLOBAL_REQUIREMENTS     containerGlobalPolicies;
    DRM_XMR_PLAYBACK_RIGHTS         containerPlaybackPolicies;
    DRM_XMR_COPY_RIGHTS             containerCopyPolicies;
    DRM_XMR_COPY_TO_PC              containerCopyToPCPolicies;
DRM_OBFUS_FILL_BYTES(4)
    DRM_XMR_PLAYLIST_BURN_RIGHTS    containerPlaylistBurnPolicies;
    DRM_XMR_GENERATION_NUMBER       generationNumber;
    DRM_XMR_UNKNOWN_CONTAINER       containerUnknown;
    DRM_XMR_REVOCATION              containerRevocation;
    DRM_XMR_KEY_MATERIAL            containerKeys;
    DRM_XMR_ND_TX_AUTH_CONTAINER    containerNDTxAuth;
    DRM_XMR_SIGNATURE               signature;
} DRM_XMR_OUTER_CONTAINER;

typedef DRM_OBFUS_FIXED_ALIGN struct __tagDRM_XMR_LICENSE
{
DRM_OBFUS_PTR_TOP
    DRM_BYTE                   *pbRightsIdBuffer;
DRM_OBFUS_PTR_BTM
    DRM_DWORD                   iRightsId;
    DRM_DWORD                   dwVersion;
DRM_OBFUS_PTR_TOP
    DRM_BYTE                   *pbSignedDataBuffer;
DRM_OBFUS_PTR_BTM
    DRM_DWORD                   iSignedData;
    DRM_DWORD                   cbSignedData;
    DRM_XMR_OUTER_CONTAINER     containerOuter;
DRM_OBFUS_PTR_TOP
    DRM_BYTE                    *pbXMRLic;
DRM_OBFUS_PTR_BTM
    DRM_DWORD                   cbXMRLic;
DRM_OBFUS_FILL_BYTES(4)
} DRM_XMR_LICENSE;

/*
** License evaluation macros
*/
#define XMR_IS_RID_VALID( plicenseXMR )                                          \
    ( ( plicenseXMR )->containerOuter.fValid                                     \
   && NULL != ( plicenseXMR )->pbRightsIdBuffer )                                \

#define XMR_IS_METERING_VALID( plicenseXMR )                                     \
    ( ( plicenseXMR )->containerOuter.fValid                                     \
   && ( plicenseXMR )->containerOuter.containerGlobalPolicies.fValid             \
   && ( plicenseXMR )->containerOuter.containerGlobalPolicies.Metering.fValid )

#define XMR_IS_KEY_MATERIAL_VALID( plicenseXMR )                                 \
    ( ( plicenseXMR )->containerOuter.fValid                                     \
   && ( plicenseXMR )->containerOuter.containerKeys.fValid )                     \

#define XMR_IS_UPLINK_KID_VALID( plicenseXMR )                                   \
    ( ( plicenseXMR )->containerOuter.fValid                                     \
   && ( plicenseXMR )->containerOuter.containerKeys.fValid                       \
   && ( plicenseXMR )->containerOuter.containerKeys.UplinkKid.fValid )

#define XMR_IS_PRIORITY_VALID( plicenseXMR )                                     \
    ( ( plicenseXMR )->containerOuter.fValid                                     \
   && ( plicenseXMR )->containerOuter.containerGlobalPolicies.fValid             \
   && ( plicenseXMR )->containerOuter.containerGlobalPolicies.Priority.fValid )

#define XMR_IS_SOURCEID_VALID( plicenseXMR )                                     \
    ( ( plicenseXMR )->containerOuter.fValid                                     \
   && ( plicenseXMR )->containerOuter.containerGlobalPolicies.fValid             \
   && ( plicenseXMR )->containerOuter.containerGlobalPolicies.SourceID.fValid )

#define XMR_IS_RESTRICTED_SOURCEID_VALID( plicenseXMR )                          \
    ( ( plicenseXMR )->containerOuter.fValid                                     \
    && ( plicenseXMR )->containerOuter.containerGlobalPolicies.fValid            \
    && ( plicenseXMR )->containerOuter.containerGlobalPolicies.RestrictedSourceID.fValid )

#define XMR_IS_REVOCATION_INFORMATION_VERSION_VALID( plicenseXMR )               \
    ( ( plicenseXMR )->containerOuter.fValid                                     \
   && ( plicenseXMR )->containerOuter.containerGlobalPolicies.fValid             \
   && ( plicenseXMR )->containerOuter.containerGlobalPolicies.RevocationInformationVersion.fValid )

#define XMR_IS_GLOBAL_POLICIES_VALID( plicenseXMR )                              \
    ( ( plicenseXMR )->containerOuter.fValid                                     \
   && ( plicenseXMR )->containerOuter.containerGlobalPolicies.fValid )

#define XMR_IS_EXPIRATION_VALID( plicenseXMR )                                   \
    ( ( plicenseXMR )->containerOuter.fValid                                     \
   && ( plicenseXMR )->containerOuter.containerGlobalPolicies.fValid             \
   && ( plicenseXMR )->containerOuter.containerGlobalPolicies.Expiration.fValid )

#define XMR_IS_ISSUEDATE_VALID( plicenseXMR )                                    \
    ( ( plicenseXMR )->containerOuter.fValid                                     \
   && ( plicenseXMR )->containerOuter.containerGlobalPolicies.fValid             \
   && ( plicenseXMR )->containerOuter.containerGlobalPolicies.IssueDate.fValid )

#define XMR_IS_GRACE_PERIOD_VALID( plicenseXMR )                                 \
    ( ( plicenseXMR )->containerOuter.fValid                                     \
   && ( plicenseXMR )->containerOuter.containerGlobalPolicies.fValid             \
   && ( plicenseXMR )->containerOuter.containerGlobalPolicies.GracePeriod.fValid )

#define XMR_IS_EXPIRATION_AFTER_FIRST_USE_VALID( plicenseXMR )                   \
    ( ( plicenseXMR )->containerOuter.fValid                                     \
   && ( plicenseXMR )->containerOuter.containerGlobalPolicies.fValid             \
   && ( plicenseXMR )->containerOuter.containerGlobalPolicies.ExpirationAfterUse.fValid )

#define XMR_IS_EXPIRATION_AFTER_STORE_VALID( plicenseXMR )                       \
    ( ( plicenseXMR )->containerOuter.fValid                                     \
   && ( plicenseXMR )->containerOuter.containerGlobalPolicies.fValid             \
   && ( plicenseXMR )->containerOuter.containerGlobalPolicies.ExpirationAfterStore.fValid )

#define XMR_IS_MINIMUM_ENVIRONMENT_VALID( plicenseXMR )                          \
    ( ( plicenseXMR )->containerOuter.fValid                                     \
   && ( plicenseXMR )->containerOuter.containerGlobalPolicies.fValid             \
   && ( plicenseXMR )->containerOuter.containerGlobalPolicies.MinimumEnvironment.fValid )

#define XMR_IS_SECURITY_LEVEL_VALID( plicenseXMR )                               \
    ( ( plicenseXMR )->containerOuter.fValid                                     \
   && ( plicenseXMR )->containerOuter.containerGlobalPolicies.fValid             \
   && ( plicenseXMR )->containerOuter.containerGlobalPolicies.MinimumEnvironment.fValid )

#define XMR_IS_OPL_VALID( plicenseXMR  )                                         \
    ( (plicenseXMR)->containerOuter.fValid                                       \
   && (plicenseXMR)->containerOuter.containerPlaybackPolicies.fValid             \
   && (plicenseXMR)->containerOuter.containerPlaybackPolicies.opl.fValid)        \

#define XMR_IS_EXPLICITANALOGVIDEOPROTECTION_VALID( plicenseXMR  )               \
    ( (plicenseXMR)->containerOuter.fValid                                       \
   && (plicenseXMR)->containerOuter.containerPlaybackPolicies.fValid             \
   && (plicenseXMR)->containerOuter.containerPlaybackPolicies.containerExplicitAnalogVideoProtection.fValid)

#define XMR_IS_EXPLICITDIGITALAUDIOPROTECTION_VALID( plicenseXMR  )              \
    ( (plicenseXMR)->containerOuter.fValid                                       \
   && (plicenseXMR)->containerOuter.containerPlaybackPolicies.fValid             \
   && (plicenseXMR)->containerOuter.containerPlaybackPolicies.containerExplicitDigitalAudioProtection.fValid)

#define XMR_IS_POLICYMETADATA_VALID( plicenseXMR )                               \
    ( ( plicenseXMR )->containerOuter.fValid                                     \
   && ( plicenseXMR )->containerOuter.containerGlobalPolicies.fValid             \
   && ( plicenseXMR )->containerOuter.containerGlobalPolicies.PolicyMetadata.fValid )

#define XMR_IS_INCLUSIONLIST_VALID( plicenseXMR )                                \
    ( ( plicenseXMR )->containerOuter.fValid                                     \
   && ( plicenseXMR )->containerOuter.containerGlobalPolicies.fValid             \
   && ( plicenseXMR )->containerOuter.containerGlobalPolicies.InclusionList.fValid )

#define XMR_IS_PLAYLISTBURN_VALID( plicenseXMR )                                 \
    ( ( plicenseXMR )->containerOuter.fValid                                     \
   && ( plicenseXMR )->containerOuter.containerPlaylistBurnPolicies.fValid )     \

#define XMR_IS_PLAYLISTBURN_RESTRICTIONS_VALID( plicenseXMR )                    \
    ( ( plicenseXMR )->containerOuter.fValid                                     \
   && ( plicenseXMR )->containerOuter.containerPlaylistBurnPolicies.fValid       \
   && ( plicenseXMR )->containerOuter.containerPlaylistBurnPolicies.Restrictions.fValid )

#define XMR_IS_PLAY_VALID( plicenseXMR )                                         \
    ( ( plicenseXMR )->containerOuter.fValid                                     \
   && ( plicenseXMR )->containerOuter.containerPlaybackPolicies.fValid )         \

#define XMR_IS_PLAYCOUNT_VALID( plicenseXMR )                                    \
    ( ( plicenseXMR )->containerOuter.fValid                                     \
   && ( plicenseXMR )->containerOuter.containerPlaybackPolicies.fValid           \
   && ( plicenseXMR )->containerOuter.containerPlaybackPolicies.PlayCount.fValid )

#define XMR_IS_COPY_TO_PC_VALID( plicenseXMR )                                   \
    ( ( plicenseXMR )->containerOuter.fValid                                     \
   && ( plicenseXMR )->containerOuter.containerCopyToPCPolicies.fValid )

#define XMR_IS_COPY_VALID( plicenseXMR )                                         \
    ( ( plicenseXMR )->containerOuter.fValid                                     \
   && ( plicenseXMR )->containerOuter.containerCopyPolicies.fValid )

#define XMR_IS_COPYCOUNT_VALID( plicenseXMR )                                    \
    ( ( plicenseXMR )->containerOuter.fValid                                     \
   && ( plicenseXMR )->containerOuter.containerCopyPolicies.fValid               \
   && ( plicenseXMR )->containerOuter.containerCopyPolicies.CopyCount.fValid )

#define XMR_IS_MOVEENABLER_VALID( plicenseXMR )                                  \
    ( ( plicenseXMR )->containerOuter.fValid                                     \
   && ( plicenseXMR )->containerOuter.containerCopyPolicies.fValid               \
   && ( plicenseXMR )->containerOuter.containerCopyPolicies.MoveEnabler.fValid )

#define XMR_IS_COPYPROTECTIONLEVEL_VALID( plicenseXMR )                          \
    ( ( plicenseXMR )->containerOuter.fValid                                     \
   && ( plicenseXMR )->containerOuter.containerCopyPolicies.fValid               \
   && ( plicenseXMR )->containerOuter.containerCopyPolicies.CopyProtectionLevel.fValid )

#define XMR_IS_REVOCATION_VALID( plicenseXMR )                                   \
    ( ( plicenseXMR )->containerOuter.fValid                                     \
   && ( plicenseXMR )->containerOuter.containerRevocation.fValid )               \

#define XMR_IS_RSA_LICENSE_GRANTER_KEY_VALID( plicenseXMR )                      \
    ( (plicenseXMR)->containerOuter.fValid                                       \
   && (plicenseXMR)->containerOuter.containerRevocation.fValid                   \
   && (plicenseXMR)->containerOuter.containerRevocation.RsaLicenseGranterKey.fValid )

#define XMR_IS_USERID_VALID( plicenseXMR )                                       \
    ( ( plicenseXMR )->containerOuter.fValid                                     \
   && ( plicenseXMR )->containerOuter.containerRevocation.fValid                 \
   && ( plicenseXMR )->containerOuter.containerRevocation.UserID.fValid )

#define XMR_IS_SIGNATURE_VALID( plicenseXMR )                                    \
    ( ( plicenseXMR )->containerOuter.fValid                                     \
   && ( plicenseXMR )->containerOuter.signature.fValid )

#define XMR_IS_CONTENT_KEY_VALID( plicenseXMR )                                  \
    ( ( plicenseXMR )->containerOuter.fValid                                     \
   && ( plicenseXMR )->containerOuter.containerKeys.fValid                       \
   && ( plicenseXMR )->containerOuter.containerKeys.ContentKey.fValid )

#define XMR_IS_OPTIMIZED_CONTENT_KEY_VALID( plicenseXMR )                        \
    ( ( plicenseXMR )->containerOuter.fValid                                     \
   && ( plicenseXMR )->containerOuter.containerKeys.fValid                       \
   && ( plicenseXMR )->containerOuter.containerKeys.OptimizedContentKey.fValid )

#define XMR_IS_DEVICE_KEY_VALID( plicenseXMR )                                   \
    ( (plicenseXMR)->containerOuter.fValid                                       \
   && (plicenseXMR)->containerOuter.containerKeys.fValid                         \
   && (plicenseXMR)->containerOuter.containerKeys.DeviceKey.fValid )             \

#define XMR_IS_ECC_DEVICE_KEY_VALID( plicenseXMR )                               \
    ( (plicenseXMR)->containerOuter.fValid                                       \
   && (plicenseXMR)->containerOuter.containerKeys.fValid                         \
   && (plicenseXMR)->containerOuter.containerKeys.ECCKey.fValid )                \

#define XMR_IS_RIGHTS_VALID( plicenseXMR )                                       \
    ( ( plicenseXMR )->containerOuter.fValid                                     \
   && ( plicenseXMR )->containerOuter.containerGlobalPolicies.fValid             \
   && ( plicenseXMR )->containerOuter.containerGlobalPolicies.Rights.fValid )

#define XMR_IS_CANNOT_PERSIST_LICENSE( plicenseXMR )                             \
    ( XMR_IS_RIGHTS_VALID( ( plicenseXMR ) )                                     \
   && ( XMR_RIGHTS_CANNOT_PERSIST == ( ( plicenseXMR )->containerOuter.containerGlobalPolicies.Rights.wValue & XMR_RIGHTS_CANNOT_PERSIST ) ) )

#define XMR_IS_DOMAIN_ID_VALID( plicenseXMR )                                    \
    ( (plicenseXMR)->containerOuter.fValid                                       \
   && (plicenseXMR)->containerOuter.containerGlobalPolicies.fValid               \
   && (plicenseXMR)->containerOuter.containerGlobalPolicies.DomainID.fValid )

#define XMR_IS_SERIAL_NUMBER_RESTRICTION_VALID( plicenseXMR  )                         \
    ( (plicenseXMR)->containerOuter.fValid                                             \
   && (plicenseXMR)->containerOuter.containerGlobalPolicies.fValid                     \
   && (plicenseXMR)->containerOuter.containerGlobalPolicies.SerialNumber.fValid)       \

#define XMR_IS_EMBEDDING_BEHAVIOR_VALID( plicenseXMR  )                                \
    ( (plicenseXMR)->containerOuter.fValid                                             \
   && (plicenseXMR)->containerOuter.containerGlobalPolicies.fValid                     \
   && (plicenseXMR)->containerOuter.containerGlobalPolicies.EmbeddingBehavior.fValid)  \

#define XMR_IS_GENERATION_NUMBER_VALID( plicenseXMR )           \
    ( (plicenseXMR)->containerOuter.fValid                      \
   && (plicenseXMR)->containerOuter.generationNumber.fValid )   \

#define XMR_IS_UNKNOWN_CONTAINER_VALID( plicenseXMR )           \
    ( (plicenseXMR)->containerOuter.fValid                      \
   && (plicenseXMR)->containerOuter.containerUnknown.fValid )   \

#define XMR_IS_REMOVAL_DATE_VALID( plicenseXMR )                                   \
    ( ( plicenseXMR )->containerOuter.fValid                                       \
   && ( plicenseXMR )->containerOuter.containerGlobalPolicies.fValid               \
   && ( plicenseXMR )->containerOuter.containerGlobalPolicies.RemovalDate.fValid )

/*
**
**  'Create Thumbnail Image' is an implied right which uses "Play"
**  action to verify if it is allowed or not.
**  Restrictions are:
**    -  license must have unlimited play count
**    -  license must not have any time based restrictions:
**          - Expiration (END) date, Expiration after First Use, Expiration after First Storage
**          - Note that Expiration (BEGIN) date is OK to have
**
*/
#define XMR_IS_THUMBNAIL_VALID( plicenseXMR )                                                                   \
    ( XMR_IS_PLAY_VALID( plicenseXMR )                                                                          \
   && ( !XMR_IS_PLAYCOUNT_VALID( plicenseXMR )                                                                  \
     || ( XMR_IS_PLAYCOUNT_VALID( plicenseXMR )                                                                 \
       && ( ( plicenseXMR )->containerOuter.containerPlaybackPolicies.PlayCount.dwValue == XMR_UNLIMITED ) ) )  \
   && ( !XMR_IS_EXPIRATION_VALID( plicenseXMR )                                                                 \
     || ( ( plicenseXMR )->containerOuter.containerGlobalPolicies.Expiration.dwEndDate == XMR_UNLIMITED ) )     \
   && !XMR_IS_EXPIRATION_AFTER_STORE_VALID( plicenseXMR )                                                       \
   && !XMR_IS_EXPIRATION_AFTER_FIRST_USE_VALID( plicenseXMR ) )

/*
** Check if license should be disabled on clock rollback
*/
#define XMR_HAS_TIME_BASED_RESTRICTIONS( plicenseXMR )                                                          \
    ( ( plicenseXMR )->containerOuter.fValid                                                                    \
   && ( plicenseXMR )->containerOuter.containerGlobalPolicies.fValid                                            \
   && ( ( plicenseXMR )->containerOuter.containerGlobalPolicies.Expiration.fValid                               \
     || ( plicenseXMR )->containerOuter.containerGlobalPolicies.ExpirationAfterUse.fValid                       \
     || ( plicenseXMR )->containerOuter.containerGlobalPolicies.ExpirationAfterStore.fValid ) )

#define XMR_IS_EXPIRATION_DATE_VALID( plicenseXMR )                                                             \
    ( ( plicenseXMR )->containerOuter.containerGlobalPolicies.Expiration.dwBeginDate          != 0              \
   || ( plicenseXMR )->containerOuter.containerGlobalPolicies.Expiration.dwEndDate != XMR_UNLIMITED             \
   || ( plicenseXMR )->containerOuter.containerGlobalPolicies.ExpirationAfterStore.dwValue    != 0              \
   || ( plicenseXMR )->containerOuter.containerGlobalPolicies.ExpirationAfterUse.dwValue      != 0 )

#define XMR_IS_AUX_KEY_VALID( plicenseXMR )                                                                     \
    ( ( plicenseXMR )->containerOuter.fValid                                                                    \
   && ( plicenseXMR )->containerOuter.containerKeys.fValid                                                      \
   && ( plicenseXMR )->containerOuter.containerKeys.AuxKey.fValid )

#define XMR_IS_UPLINKX_VALID( plicenseXMR )                                                                     \
    ( ( plicenseXMR )->containerOuter.fValid                                                                    \
   && ( plicenseXMR )->containerOuter.containerKeys.fValid                                                      \
   && ( plicenseXMR )->containerOuter.containerKeys.UplinkX.fValid )

#define XMR_IS_REAL_TIME_EXPIRATION_VALID( plicenseXMR )                                                        \
    ( ( plicenseXMR )->containerOuter.fValid                                                                    \
   && ( plicenseXMR )->containerOuter.containerGlobalPolicies.fValid                                            \
   && ( plicenseXMR )->containerOuter.containerGlobalPolicies.RealTimeExpiration.fValid )

/*
** There is a finite set of objects which get allocated using
** DRM_STK_Alloc in the XMR parser which can potentially be larger
** than the original raw binary license data they contain.
**
** The smallest size of an XMR object is XMR_BASE_OBJECT_LENGTH.
**
** Therefore, the worst-case license, which contains nothing but
** instances of the highest-bloat object which needs to be allocated
** using DRM_STK_Alloc, will require this many bytes:
**  DRM_XMR_COMPUTED_MAX_UNPACK_ALLOC_FACTOR * sizeof(raw XMR license)
**
** In effect, that constant equals:
**  (Space needed for the Highest-Bloat object)
**    / (Smallest size that object could be in the raw XMR license)
**
** However, DRM_XMR_MAX_UNPACK_ALLOC_FACTOR is what should primarily
** be used by callers of DRM_XMR_UnpackLicense because that will
** ensure consistent allocation behavior on on architectures.
** Note: Inside DRM_XMR_UnpackLicense, there is a compile-time assert
** to validate that:
**     DRM_XMR_MAX_UNPACK_ALLOC_FACTOR
**  >= DRM_XMR_COMPUTED_MAX_UNPACK_ALLOC_FACTOR
**
** Therefore, callers of DRM_XMR_UnpackLicense that don't want
** to worry about potentially running out of space should ensure
** that f_pStack contains at least this many bytes:
**  (DRM_XMR_MAX_UNPACK_ALLOC_FACTOR * f_cbLicense)
**
** Additional notes about DRM_XMR_COMPUTED_MAX_UNPACK_ALLOC_FACTOR:
**  The extra "+ ( SIZEOF(DRM_DWORD_PTR) - 1 )" is due to the
**   fact that the memory allocation may need to be aligned.
**  The extra "+ 1" is due to the fact that the division will
**   round down.
*/

#define DRM_XMR_COMPUTED_MAX_UNPACK_ALLOC_FACTOR                                        \
    ( ( ( MAX(                                                                          \
              MAX(                                                                      \
                  MAX( SIZEOF(DRM_XMR_UNKNOWN_CONTAINER),                               \
                       SIZEOF(DRM_XMR_UNKNOWN_OBJECT) ),                                \
                  MAX( SIZEOF(DRM_XMR_VIDEO_OUTPUT_CONFIGURATION_LIST),                 \
                       SIZEOF(DRM_XMR_AUDIO_OUTPUT_CONFIGURATION_LIST) ) ),             \
              SIZEOF( DRM_XMR_POLICY_METADATA_LIST ) )                                  \
        + ( SIZEOF(DRM_DWORD_PTR) - 1 ) )                                               \
    / XMR_BASE_OBJECT_LENGTH ) + 1 )

#define DRM_XMR_MAX_UNPACK_ALLOC_FACTOR 7

EXIT_PK_NAMESPACE;

#endif  /* __DRM_XMR_H__ */

