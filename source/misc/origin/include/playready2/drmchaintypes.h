/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRM_CHAINTYPES_H__
#define __DRM_CHAINTYPES_H__

#include <drmtypes.h>
#include <drmlicevaltypes.h>
#include <drmlicstore.h>

ENTER_PK_NAMESPACE;

#define DRM_MAX_COPY_OPL_DATA_SIZE (1024*4)
#define DRM_MAX_PLAY_OPL_DATA_SIZE (128)

typedef DRM_RESULT (DRM_CALL *pfnCheckDeviceRevocation)(DRM_LICEVAL_CONTEXT* pLicEvalContext, DRM_VOID *pv );

#define DRM_POLICY_FLAG_ONLINE_DISABLED              0x00000001
#define DRM_POLICY_FLAG_METERING_DISABLED_ENTERPRISE 0x00000002

typedef struct __tagCOPY_OPL_CHAIN
{
    DRM_BYTE     rgbCopyOPLBuffer[__CB_DECL(DRM_MAX_COPY_OPL_DATA_SIZE)];
    DRM_COPY_OPL oplCopy;
} COPY_OPL_CHAIN;

typedef struct __tagPLAY_OPL_CHAIN
{
    DRM_BYTE         rgbPlayOPLBuffer[__CB_DECL(DRM_MAX_PLAY_OPL_DATA_SIZE)];
    DRM_PLAY_OPL_EX2 oplPlay;
} PLAY_OPL_CHAIN;


typedef struct _FFLICENSE
{
    /* __in    */ DRM_LICSTORE_CONTEXT              *rgpLicStoreCurrent[DRM_MAX_LICENSE_CHAIN_DEPTH]; /* Context to an Open license store for each license in the chain */
    /* __in    */ DRM_LICSTORE_CONTEXT              *rgpLicStores[DRM_LICSTORE_MAX_STORES]; /* Array of contexts to Open license stores (for enumeration) */
    /* __in    */ DRM_LICSTORE_CONTEXT              *pLicStorePRND; /* Non-NULL if PRND store is included in Open license stores */
    /* __in    */ DRM_LICSTORE_CONTEXT              *pLicStoreNST;  /* Non-NULL if NST store is included in Open license stores */
    /* __in    */ DRM_LICSTORE_CONTEXT              *pLicStoreEST;  /* Non-NULL if EST store is included in Open license stores */
    /* __in    */ DRM_DWORD                          cLicStores; /* Count of elements in pLicStores */
    /* __inout */ DRM_LICSTOREENUM_MULTIPLE_CONTEXT *pLicStoreEnum; /* Enumerators for all depths, [0] should be initialized */
    /* __inout */ DRM_SECSTORE_CONTEXT              *pSecStoreLicense;
    /* __in    */ DRM_LICEVAL_CONTEXT               *pLicEval;
    /* __in    */ DRM_V1Header                      *pV1Header;
    /* __out   */ DRM_BINDING_INFO                  *pBindingInfo;     /* This should point to an array of DRM_MAX_LICENSE_CHAIN_DEPTH binding infos. */
    /* __out   */ DRM_XMR_LICENSE                   *pLicenseXMR;
    /* __in    */ DRM_BOOL                          *fSkipAESContent;
    /* __in    */ DRM_STACK_ALLOCATOR_CONTEXT       *pstack;
    /* __in    */ DRM_BYTE                          *pbBuffer;     /* Working buffer */
    /* __in    */ DRM_DWORD                          cbBuffer;
    /* __in    */ DRM_DWORD                          dwChainDepth; /* The current depth of the chain.  If we are looking for the first license this is 0 */
    /* __in    */ DRM_DWORD                          dwPolicyFlags; /* bitmask of policy flags */
    /* __in    */ DRM_BYTE                           rgbRevocationPassword [__CB_DECL(DRM_SHA1_DIGEST_LEN)];
    /*         */ DRM_BYTE                           rgbLicensePassword    [__CB_DECL(DRM_SHA1_DIGEST_LEN)];
    /* __out   */ DRM_BOOL                           fSecStoreOpen         [DRM_MAX_LICENSE_CHAIN_DEPTH]; /* On function exit the caller should close the stores if they are open */
    /* __out   */ DRM_BOOL                           rgfLicenseFromEST     [DRM_MAX_LICENSE_CHAIN_DEPTH];
    /* __out   */ DRM_BOOL                           rgfLicenseFromPRND    [DRM_MAX_LICENSE_CHAIN_DEPTH];
    /* __out   */ DRM_BOOL                           rgfDeleteLicense      [DRM_MAX_LICENSE_CHAIN_DEPTH];
    /* __out   */ DRM_KID                            rgkid                 [DRM_MAX_LICENSE_CHAIN_DEPTH];
    /* __out   */ DRM_LID                            rglid                 [DRM_MAX_LICENSE_CHAIN_DEPTH];
    /* __out   */ DRM_DST_SLOT_HINT                  rgslotHint            [DRM_MAX_LICENSE_CHAIN_DEPTH];
    /* __out   */ DRM_MID                            rgmid                 [DRM_MAX_LICENSE_CHAIN_DEPTH];
    /* __out   */ DRM_BOOL                           rgfHasMetering        [DRM_MAX_LICENSE_CHAIN_DEPTH]; /* On function exit the caller should close the stores if they are open */

    /* __out   */ COPY_OPL_CHAIN                     rgCopyOpl             [DRM_MAX_LICENSE_CHAIN_DEPTH];
    /* __out   */ DRM_BOOL                           rgfCopyOplValid       [DRM_MAX_LICENSE_CHAIN_DEPTH];
    /* __out   */ PLAY_OPL_CHAIN                     rgPlayOpl             [DRM_MAX_LICENSE_CHAIN_DEPTH];
    /* __out   */ DRM_BOOL                           rgfPlayOplValid       [DRM_MAX_LICENSE_CHAIN_DEPTH];
    /* __out   */ DRM_INCLUSION_LIST_CALLBACK_STRUCT inclusionListCallback;

    /* __out   */ DRM_DWORD                          dwMinimumRequiredAppSec;
    /* __in    */ DRM_BOOL                           fCanBind;
    /* __out   */ DRM_DWORD                          dwSourceid;
    /* __out   */ DRM_DWORD                          dwLicRevInfoVer;
    /* __out   */ DRM_BOOL                           fBlockNDT;    /* TRUE on output if the license should be blocked from NDT */

    /*
    ** We use this boolean to cache whether the root license MUST
    **  be domain bound due to a leaf license requiring it.
    ** See comments regarding the equivalent flag in drmliceval.h
    **  for more information.
    */
    /* __out   */ DRM_BOOL                          fDomainBoundRootRequired;

    /* __out   */ DRM_UINT64                        ui64RealTimeExpiration;

} DRM_FFLICENSE;

EXIT_PK_NAMESPACE;

#endif  /* __DRM_CHAINTYPES_H__ */

