/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRM_CALLBACKTYPES_H__
#define __DRM_CALLBACKTYPES_H__

#include <drmerr.h>
#include <drmoutputleveltypes.h>
#include <drmxmr.h>

ENTER_PK_NAMESPACE;

typedef enum
{
    DRM_PLAY_OPL_CALLBACK                       = 0x1,  /* DRM_PLAY_OPL_EX2                         */
    DRM_COPY_OPL_CALLBACK                       = 0x2,  /* DRM_COPY_OPL                             */
    DRM_INCLUSION_LIST_CALLBACK                 = 0x3,  /* DRM_INCLUSION_LIST_CALLBACK_STRUCT       */
    DRM_EXTENDED_RESTRICTION_CONDITION_CALLBACK = 0x4,  /* DRM_EXTENDED_RESTRICTION_CALLBACK_STRUCT */
    DRM_EXTENDED_RESTRICTION_ACTION_CALLBACK    = 0x5,  /* DRM_EXTENDED_RESTRICTION_CALLBACK_STRUCT */
    DRM_EXTENDED_RESTRICTION_QUERY_CALLBACK     = 0x6,  /* DRM_EXTENDED_RESTRICTION_CALLBACK_STRUCT */
    DRM_SECURE_STATE_TOKEN_RESOLVE_CALLBACK     = 0x7,  /* DRM_SECURE_STATE_TOKEN_RESOLVE_DATA      */
    DRM_RESTRICTED_SOURCEID_CALLBACK            = 0x8,  /* DRM_RESTRICTED_SOURCEID_CALLBACK_STRUCT  */
} DRM_POLICY_CALLBACK_TYPE;

typedef DRM_RESULT (DRM_CALL* DRMPFNPOLICYCALLBACK)(
    __in const DRM_VOID                 *f_pvCallbackData,
    __in       DRM_POLICY_CALLBACK_TYPE  f_dwCallbackType,
    __in const DRM_VOID                 *f_pv );

/*
**  When recieving this struct via a callback you can determine which GUIDs in the list are usabale by checking the
**  rgfInclusionListValid[dwChainDepth] array to see which ones are TRUE.  Those that are true means that
**  rgInclusionList[x] is usable where rgfInclusionListValid[x][dwChainDepth] is TRUE.
*/

typedef struct __tagDRM_INCLUSION_LIST_CALLBACK_STRUCT
{
    DRM_GUID  rgInclusionList       [DRM_MAX_INCLUSION_GUIDS];
    DRM_BOOL  rgfInclusionListValid [DRM_MAX_INCLUSION_GUIDS][DRM_MAX_LICENSE_CHAIN_DEPTH];
    DRM_DWORD dwChainDepth;
} DRM_INCLUSION_LIST_CALLBACK_STRUCT;


typedef struct
{
    DRM_WORD                             wRightID;
    DRM_XMR_UNKNOWN_OBJECT              *pRestriction;
    DRM_XMR_LICENSE                     *pXMRLicense;
    DRM_VOID                            *pContextSST;   /*DRM_SECSTORE_CONTEXT*/
} DRM_EXTENDED_RESTRICTION_CALLBACK_STRUCT;

typedef struct
{
    DRM_DWORD dwSourceID; /* global requirement, no need to pass right ID */
} DRM_RESTRICTED_SOURCEID_CALLBACK_STRUCT;


EXIT_PK_NAMESPACE;

#endif /* __DRMCALLBACKTYPES_H__ */
