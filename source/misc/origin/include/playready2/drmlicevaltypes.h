/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRMLICEVALTYPES_H__
#define __DRMLICEVALTYPES_H__

#include <drmrevocationstore.h>
#include <drmsyncstorecontext.h>
#include <drmmetercertstore.h>
#include <drmwmdrmtypes.h>
#include <drmlicense.h>

ENTER_PK_NAMESPACE;

#define DRM_MAX_ACTIONS 10

/*
** Flags for use with SetLicense method
*/
enum
{
    LICEVAL_VERIFY_CERT_WITH_EXPIRYCHECK    = 1,
    LICEVAL_VERIFY_CERT_WITHOUT_EXPIRYCHECK = 2,
    LICEVAL_VERIFY_SIGNATURE                = 4,
    LICEVAL_VERIFY_IGNORE_VERIFICATION      = 8,
    LICEVAL_IGNORE_SECURESTORE_ENTRY        = 16,
};

#define LICEVAL_STORE_CHECK_SETTINGS ( LICEVAL_VERIFY_CERT_WITH_EXPIRYCHECK | LICEVAL_VERIFY_SIGNATURE )
#define LICEVAL_OPEN_CHECK_SETTINGS  ( LICEVAL_VERIFY_CERT_WITHOUT_EXPIRYCHECK | LICEVAL_VERIFY_SIGNATURE )

typedef struct __tagDRM_APPCERT_INFO
{
    DRM_DWORD appSec;
    DRM_DWORD appcd_subject;
} DRM_APPCERT_INFO;

typedef enum
{
    LICEVAL_NOREFERENECE                 = 0,
    LICEVAL_MACHINEDATETIMEREFERENCED    = 1,
    LICEVAL_GRACEPERIODREFERENCED        = 2
} eDRM_LICEVAL_TIMEBASED_STATE;

typedef enum
{
    eDRM_LIC_CACHED_ATTRIB_KID           = 0,
    eDRM_LIC_CACHED_ATTRIB_LID           = 1,
    eDRM_LIC_CACHED_ATTRIB_CONTENTPUBKEY = 2,
    eDRM_LIC_CACHED_ATTRIB_METERING_ID   = 3,
    eDRM_LIC_CACHED_ATTRIB_CHAINEDKID    = 4,
    eDRM_LIC_CACHED_ATTRIB_LAST          = 5
} eDRM_LIC_CACHED_ATTRIBS;

typedef struct tagDRM_CACHED_EVENT
{
    DRM_CONST_STRING  dstrType;
    DRM_CONST_STRING  dstrAction;
    DRM_CONST_STRING  dstrCondition;
    DRM_CONST_STRING  dstrRestriction;
} DRM_CACHED_EVENT;

/*
**  Current revocation list values should be placed in this struct and passed to CompleteChain so licenses can be compared against these
**  values.
*/
typedef struct __tagDRM_REVLIST_ID_VALUES
{
    DRM_BOOL   fUpdatedRevocationList;
    DRM_DWORD  wmdrmapp;
    DRM_DWORD  playreadyapp;
    DRM_DWORD  device;
    DRM_DWORD  wmdrmnet;
    DRM_DWORD  runtime;
    DRM_DWORD  riv;
    DRM_DWORD  riv2;
} DRM_REVLIST_ID_VALUES;

typedef struct __tagDRM_LICEVAL_CONTEXT
{
    DRM_BB_CONTEXT              *pcontextBBX;
    APPCERT                      appcert;
    DRM_WMDRM_EXPR_EVAL_CONTEXT  contextEXPR;
    DRM_CONST_STRING             dstrContentHeader;
    DRM_CONST_STRING             dstrContentLicense;
    DRM_CONST_STRING             dstrBBVer;
    DRM_CONST_STRING             dstrDRMVer;
    DRM_CONST_STRING             dstrDRMKVer;
    DRM_SECSTORE_CONTEXT        *pcontextSSTLicense;
    DRM_SECSTORE_CONTEXT        *pcontextSSTGlobal;
    DRM_SECSTORE_CONTEXT        *pcontextSSTRevocation;
    DRM_APPCERT_INFO             certinfoSDK;
    DRM_BOOL                     fAppInfoValid;
    DRM_APPCERT_INFO             certinfoApp;
    DRM_BOOL                     fLegacyAppInfoValid;
    DRM_APPCERT_INFO             certinfoAppLegacy;
    DRM_DWORD                    dwChainDepth;
    DRM_BOOL                     fDeviceRegistered;      /* TRUE if the device is registered */
    DRM_LID                      LID;
    DRM_KID                      KID;
    DRM_BOOL                     fGlobalSecStoreWritable;
    DRM_LONG                     lReasonForFail;
    DRM_CONST_STRING             wszDRMKParam;           /* This is an OUT string.  After a license is evaluated this will point to a version string if SAP is required */
    DRM_DWORD                    dwFlags;                /* Default as this LICEVAL_OPEN_CHECK_SETTINGS */
    DRM_BOOL                     fReserved;              /* Must be initialized to 0 */
    DRM_BOOL                     fSSecureTimeDataLoaded; /* Indicates whether we've already attempted to load the proceeding values */
    DRM_BOOL                     fSecureTimeDataValid;   /* Is secure time data valid. Must be initialized to 0 */
    DRM_BOOL                     fInGracePeriod;         /* Is in Grace period */
    DRM_UINT64                   u64GPStartTime;         /*Grace period duration*/
    DRM_DST                     *pDatastore;
    DRM_BOOL                     fIgnoreTimeBoundLicense;
    eDRM_LICEVAL_TIMEBASED_STATE eTimeBasedState;
    DRM_BYTE                    *pbRevocationBuffer;     /* User gives a point to work in.  This is actually going to be used for revocation from the secure store */
    DRM_DWORD                    cbRevocationBuffer;     /* Size of the user supplied pointer */
    DRM_REVLIST_ID_VALUES        idCRLsCurrent;
    DRM_REVOCATIONSTORE_CONTEXT *pContextRev;
    DRM_BOOL                     fDeleteLicense;
    DRM_BOOL                     fUseCachedAttribs;
    DRM_CONST_STRING             rgdstrCachedAttribs[ eDRM_LIC_CACHED_ATTRIB_LAST ];
    DRM_CACHED_EVENT             rgCachedEvents[ DRM_MAX_ACTIONS ];
    DRM_DWORD                    cCachedEvents;
    DRM_SYNC_CONTEXT             *pcontextSync;
    DRM_METERCERT_CONTEXT        *pcontextMeterCert;
    DRM_XMR_LICENSE              *plicenseXMR;
    DRM_BOOL                      fLicenseIsXMR;
    DRM_BOOL                      fIsReadOnlyMode;
    DRM_DWORD                     rgdwAllowedSourceIDs[XMR_SOURCEID_MAXCOUNT];
    DRM_DWORD                     cAllowedSourceIDs;
    DRM_BOOL                      fAllowAllSourceIDs;
    DRM_BOOL                      fLicenseFromHDS;
    DRM_BOOL                      fLicenseFromPRND;

    /*
    ** OUT: When evaluating the Copy right, if the license is domain bound without
    **  an explicit copy right, but is not bound to any of the domains given
    **  (or no domains were given), the evaluation will fail because copy isn't allowed,
    **  but fCopyDestDomainAccountIDRequired will be set to TRUE and the associated data
    **  will indicate to the caller which domain the copy destination must join
    **  in order for the copy to be allowed.
    */
    DRM_BOOL                      fCopyDestDomainAccountIDRequired;
    DRM_GUID                      guidCopyDestDomainAccountIDRequired;
    DRM_DWORD                     dwCopyDestDomainRevisionRequired;

    /*
    ** OUT: When evaluating the Copy right, if the license is a LEAF license,
    **  and the license does not have the Copy right, then evaluation will
    **  still succeed and this value will get set to TRUE.
    ** It is then the caller's responsibility to validate that this license
    **  chains up to a valid domain-bound root license before allowing Copy
    **  to succeed.
    ** This applies to the Copy right by itself as well as the Copy right
    **  with either the Copy To PC or Copy To Device action qualifier.
    ** This does NOT apply to the Copy right with any other action qualifier.
    */
    DRM_BOOL                      fDomainBoundRootRequired;

    DRM_BOOL                      fMoveListCheckRequired;

    DRM_UINT64                    ui64RealTimeExpiration;
} DRM_LICEVAL_CONTEXT;

typedef enum
{
    DRM_LICENSE_EVAL_SELECT               = 1,
    DRM_LICENSE_EVAL_DELETE               = 2,
    DRM_LICENSE_EVAL_STORE                = 3,
    DRM_LICENSE_EVAL_REPORTCLOCK_ROLLBACK = 4, /* Only use DRM_LICENSE_EVAL_DONE_WITH_OPERATION for clock rollback. */
    DRM_LICENSE_EVAL_ACTION               = 5  /* With ACTION you must provide an action string */
} eDRM_LICEVAL_OPERATIONS;

typedef enum
{
    DRM_LICENSE_EVAL_CAN_DO_OPERATION    = 1,
    DRM_LICENSE_EVAL_DONE_WITH_OPERATION = 2
} eDRM_LICEVAL_OPERATION_STATE;

EXIT_PK_NAMESPACE;

#endif /* __DRMLICEVALTYPES_H__ */

