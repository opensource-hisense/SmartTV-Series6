/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRM_VIEWRIGHTS_H__
#define __DRM_VIEWRIGHTS_H__

#include <drmoutputleveltypes.h>
#include <drmchaintypes.h>

ENTER_PK_NAMESPACE;

DRM_API DRM_BOOL DRM_CALL DRM_VIEWRIGHTS_IsViewRightsSupported(DRM_VOID);
DRM_API DRM_BOOL DRM_CALL DRM_VIEWRIGHTS_IsViewRightsUnsupported(DRM_VOID);

/* We need: */
/* 1.  Content header KID */
/* 2.  Blackbox context */
/* 3.  Secure store open to global state */
/* 4.  Secure store context not open yet */
/* 5.  License store context ( we enum here ) */
/* 6.  License eval context */
#define DRM_MAX_RIGHTS_SUPPORTED 9

/* support up to 2 different KIDs for uplink root license for leaf license of the same KID */
#define DRM_MAX_CHAIN_ROOTVARIANCE_SUPPORT   2


#if !DRM_LICENSE_STATE_TYPES_DEFINED
#define DRM_LICENSE_STATE_TYPES_DEFINED 1

#define DRM_ASD_VAGUE       0x1
#define DRM_ASD_OPL         0x2
#define DRM_ASD_SAP         0x4
#define DRM_ASD_MU_EXT_REST 0x8 /* Has must understand extensible restrictions */

/* Enum and structure for license properties queries */
typedef enum DRM_LICENSE_STATE_CATEGORY
{
    DRM_LICENSE_STATE_NORIGHT = 0,
    DRM_LICENSE_STATE_UNLIM,
    DRM_LICENSE_STATE_COUNT,
    DRM_LICENSE_STATE_FROM,
    DRM_LICENSE_STATE_UNTIL,
    DRM_LICENSE_STATE_FROM_UNTIL,
    DRM_LICENSE_STATE_COUNT_FROM,
    DRM_LICENSE_STATE_COUNT_UNTIL,
    DRM_LICENSE_STATE_COUNT_FROM_UNTIL,
    DRM_LICENSE_STATE_EXPIRATION_AFTER_FIRSTUSE,
    DRM_LICENSE_STATE_FORCE_SYNC,
    DRM_LICENSE_STATE_NOT_FOUND,
    DRM_LICENSE_STATE_ENTRY_MARKED_FOR_DELETION
} DRM_LICENSE_STATE_CATEGORY;

typedef struct _DRM_LICENSE_STATE_DATA
{
    DRM_DWORD   dwStreamId;      /* 0 -> All streams, != 0 -> A particular stream. */
    DRM_DWORD   dwCategory;      /* Indicates the category of string to be displayed. */
    DRM_DWORD   dwNumCounts;     /* Number of items supplied in dwCount. */
    DRM_DWORD   dwCount  [4];    /* Up to 4 counts. */
    DRM_DWORD   dwNumDates;      /* Number of items supplied in dwDate. */
    DRMFILETIME datetime [4];    /* Up to 4 dates. */
    DRM_DWORD   dwVague;         /* 0 -> certain, 1 -> atleast.  (There could be more */
                                 /*               licenses. Aggregation not possible.) */
} DRM_LICENSE_STATE_DATA;
#endif /* DRM_LICENSE_STATE_TYPES_DEFINED */


/***************************************************************************/
/* Internal structures and data */
typedef enum _LicenseCategory
{
    LIC_TYPE_IGNORE = 0,
    LIC_TYPE_EXPIRY,
    LIC_TYPE_COUNTED_EXPIRY,
    LIC_TYPE_EXPIRATION_AFTER_FIRST_USE
} LicenseCategory;


typedef struct LicenseInfo
{
    LicenseCategory         dwCategory;     /* License Category. DIVX, counted etc.   */
    DRM_DWORD               dwStartCount;   /* How many counts were given originally. */
    DRM_DWORD               dwCount;        /* How many counts are left.              */
    DRM_DWORD               dwHours;        /* How many days are left. For expiration after first use licenses that are never used so far. */
    DRMFILETIME             begDate;        /* License valid only after this date.    */
    DRMFILETIME             endDate;        /* License not valid after this date.     */
    DRM_BOOL                fHasOPLs;       /* True if OPLs were seen in the license  */
    DRM_BOOL                fRequiresSAP;   /* True if the license requires SAP       */
    DRM_BOOL                fHasMUExtensibleRestrictions; /* True if the license has extensible restrictions that are marked as "must understand" */
} LicenseInfo;


typedef DRM_DWORD DRM_LICQUERY_RESULT_BITS;
#define DRM_LICQUERY_NOT_ENABLED                        0x00000001
#define DRM_LICQUERY_NOT_ENABLED_NO_LICENSE             0x00000002
#define DRM_LICQUERY_NOT_ENABLED_NO_RIGHT               0x00000004
#define DRM_LICQUERY_NOT_ENABLED_EXHAUSTED              0x00000008
#define DRM_LICQUERY_NOT_ENABLED_EXPIRED                0x00000010
#define DRM_LICQUERY_NOT_ENABLED_NOT_STARTED            0x00000020
#define DRM_LICQUERY_NOT_ENABLED_APPSEC_TOO_LOW         0x00000040
#define DRM_LICQUERY_NOT_ENABLED_REQ_INDIV              0x00000080
#define DRM_LICQUERY_NOT_ENABLED_COPY_OPL_TOO_LOW       0x00000100
#define DRM_LICQUERY_NOT_ENABLED_COPY_OPL_EXCLUDED      0x00000200
#define DRM_LICQUERY_NOT_ENABLED_NO_CLOCK_SUPPORT       0x00000400
#define DRM_LICQUERY_NOT_ENABLED_NO_METERING_SUPPORT    0x00000800
#define DRM_LICQUERY_NOT_ENABLED_CHAIN_DEPTH_TOO_HIGH   0x00001000
#define DRM_LICQUERY_NOT_ENABLED_NO_UPLINK              0x00002000
#define DRM_LICQUERY_SATISFIED                          0x10000000

typedef struct _DRM_CANDO_QUERY_CACHE
{
    DRM_LID   cachedLID;
    DRM_KID   parentKID;
    DRM_DWORD dwResult[DRM_MAX_RIGHTS_SUPPORTED];
    DRM_DWORD dwUplinkVector;
    LicenseInfo licInfo[DRM_MAX_RIGHTS_SUPPORTED];
} DRM_CANDO_QUERY_CACHE;


typedef struct __tagDRM_STATE_DATA_STACK
{
    DRM_LICENSE_STATE_DATA    rgStatePri[DRM_MAX_RIGHTS_SUPPORTED]; /* Caller shouldn't touch these */
    DRM_KID                   rgkidRoot  [DRM_MAX_CHAIN_ROOTVARIANCE_SUPPORT];
    DRM_LICENSE_STATE_DATA    rgRootState[DRM_MAX_CHAIN_ROOTVARIANCE_SUPPORT][DRM_MAX_RIGHTS_SUPPORTED]; /* Caller shouldn't touch these */
    DRM_LICENSE_STATE_DATA    rgLeafState[DRM_MAX_CHAIN_ROOTVARIANCE_SUPPORT][DRM_MAX_RIGHTS_SUPPORTED]; /* Caller shouldn't touch these */
} DRM_STATE_DATA_STACK;


typedef struct __tagDRM_VIEW_RIGHTS_CONTEXT
{
/*PUBLIC */
    DRM_KID                      KID;              /* Pointer to a DRM_KID_LENGTH byte buffer with the KID we are looking for */
    DRM_BB_CONTEXT              *pBBContext;       /* Pointer to a Blackbox context structure */
    DRM_SECSTORE_CONTEXT        *pbGlobalSecStore; /* Pointer to a secure store opened to the global key */
    DRM_SECSTORE_CONTEXT        *pbLIDSecStore;    /* Pointer to open secure store -- not opened to a specific key yet. */
    DRM_LICSTORE_CONTEXT        *pbLicenseStoreXML;/* Pointer to an open license store context */
    DRM_LICSTORE_CONTEXT        *pbLicenseStoreXMR;/* Pointer to an open license store context */
    DRM_LICSTOREENUM_CONTEXT    *rgpLicQueryContext[DRM_MAX_LICENSE_CHAIN_DEPTH]; /* Pointer to memory for a DRM_LICSTOREENUM_CONTEXT.  Should not be intialized!!!  Just need the memory */
    DRM_LICEVAL_CONTEXT         *pLicEval;         /* Pointer to a liceval context */
    DRM_BYTE                    *pbBuffer;         /* User gives a sandbox buffer to work in */
    DRM_DWORD                    cbBuffer;         /* Size of sandbox buffer.  If it is too small we will fail.  Don't know how big because licenses can be variable length */

    DRM_DEVICE_CERTIFICATE_CACHED_VALUES  cacheDevCert;
    DRM_BOOL                     fIsWMDRMPDDevice;
    DRM_DWORD                    dwDeviceCopyOPL;
    DRM_GUID                     deviceGUID;
    DRM_LONG                     lDeviceAppSec;
    DRM_BOOL                     fDeviceSupportMetering;
    DRM_BOOL                     fDeviceSupportClock;
    DRM_BOOL                     fDeviceHasSerialNum;
    DRM_BOOL                     fPCSupportMetering;
    DRM_DWORD                    dwLicChainDepth;
    COPY_OPL_CHAIN               copyOPL;

/* private */
    DRM_STACK_ALLOCATOR_CONTEXT  stack;                 /* local stack allocator */
    DRM_BYTE                    *pbCurrentLicenseBuff;  /* pointer to XML lic buffer allocated from local stack */
    DRM_BOOL                     fCurrentLicenseIsXML;  /* TRUE if current lic is XML */
    DRM_LICSTORE_CONTEXT        *pActiveLicStore;       /* set at run time:  pbLicenseStoreXML or pbLicenseStoreXMR */
    DRM_XMR_LICENSE              licXMR;                /* XMR license structure */
    DRM_DWORD                    iCurrSlot;
    DRM_DWORD                    cCacheSlots;
    DRM_CANDO_QUERY_CACHE       *rgCacheSlots;
    DRM_STATE_DATA_STACK         rgStack[DRM_MAX_LICENSE_CHAIN_DEPTH];
    LicenseInfo                  rgLicInfo[DRM_MAX_RIGHTS_SUPPORTED]; /* Caller shouldn't touch these */
} DRM_VIEW_RIGHTS_CONTEXT;


#define DRM_ASD_AGGREGATE_ROOT_LICENSES            0
#define DRM_ASD_AGGREGATE_SIMPLE_AND_LEAF_LICENSES 1

DRM_API DRM_RESULT DRM_CALL DRM_VIEWRIGHTS_GetLicenseAggregateData(
    __in_ecount( f_cActionsQueried)  const DRM_CONST_STRING*  const f_rgpdstrAction[], /* Array of DRM_CONST_STRING pointers */
    __out_opt                              DRM_LICENSE_STATE_DATA   f_rgStateData[],   /* array of DRM_LICENSE_STATE_DATAs */
    __in                                   DRM_DWORD                f_cActionsQueried,
    __inout_opt                            DRM_VIEW_RIGHTS_CONTEXT *f_pcontextLQ,
    __inout                                DRM_DST                 *f_pDatastore,
    __in                                   DRM_BOOL                 f_fDeleteExpiredLicenses,
    __in                                   DRM_DWORD                f_dwAggregationType,
    __in_opt                               DRMPFNPOLICYCALLBACK     f_pfnPolicyCallback,
    __in_opt                         const DRM_VOID                *f_pv);


DRM_API DRM_RESULT DRM_CALL DRM_VIEWRIGHTS_IsAllowed(
    __in    const DRM_CONST_STRING        *pdstrAction,
    __inout       DRM_VIEW_RIGHTS_CONTEXT *pContext,
    __inout       DRM_DST                 *f_pDatastore );

DRM_API DRM_RESULT DRM_CALL DRM_VIEWRIGHTS_InitCanDoQuery(
    __in       DRM_CRYPTO_CONTEXT       *f_pDrmCrypto,
    __in       DRM_LICSTORE_CONTEXT     *f_pbLicenseStoreXML,
    __in       DRM_LICSTORE_CONTEXT     *f_pbLicenseStoreXMR,
    __in_ecount( DRM_MAX_LICENSE_CHAIN_DEPTH)  DRM_LICSTOREENUM_CONTEXT *f_rgpLicQueryContext[DRM_MAX_LICENSE_CHAIN_DEPTH],
    __in       DRM_LICEVAL_CONTEXT      *f_pLicEval,
    __in       DRM_BYTE                 *f_pbBuffer,
    __in       DRM_DWORD                 f_cbBuffer,
    __in       DRM_LONG                  f_lDeviceAppSec,
    __in       DRM_BOOL                  f_fDeviceHasSerialNum,
    __in       DRM_DWORD                 f_dwDeviceCopyOPL,
    __in const DRM_GUID                 *f_pDeviceGUID,
    __in const DRM_CONST_STRING         *f_pdstrDevCert,
    __in       DRM_DWORD                 f_cCacheSlots,     /* must be >= 1 */
    __in       DRM_CANDO_QUERY_CACHE    *f_pCacheSlots,
    __out      DRM_VIEW_RIGHTS_CONTEXT  *f_pLicQueryCtx);


DRM_API DRM_RESULT DRM_CALL DRM_VIEWRIGHTS_CandoQuery(
    __in                              const DRM_KID                 *f_pKID,
    __in                                    DRM_DWORD                f_cActionsQueried,
    __in_ecount( f_cActionsQueried )  const DRM_CONST_STRING        *f_rgpdstrAction[],
    __inout                                 DRM_VIEW_RIGHTS_CONTEXT *f_pcontextLQ,
    __inout                                 DRM_DST                 *f_pDatastore,
    __in                                    DRM_BOOL                 f_fDeleteExpiredLicenses,
    __out_ecount( f_cActionsQueried )       DRM_DWORD                f_rgResults[]);

EXIT_PK_NAMESPACE;

#endif /* __DRM_VIEWRIGHTS_H__ */

