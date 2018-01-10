/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRM_REMOVAL_DATE_STORE_CONTEXT__
#define __DRM_REMOVAL_DATE_STORE_CONTEXT__

#include <drmtypes.h>
#include <drmdatastore.h>

ENTER_PK_NAMESPACE;

typedef struct _tagRemovalDateContext
{
    DRM_DST_SLOT_CONTEXT      contextDSTSlot;
    DRM_DST_NAMESPACE_CONTEXT contextNameSpace;
    DRM_DST                  *pDatastore;
    DRM_BOOL                  fInited;
} DRM_REMOVAL_DATE_CONTEXT_PRIVATE;


typedef struct _tagRemovalDateEnumContext
{
    DRM_REMOVAL_DATE_CONTEXT_PRIVATE *pcontextRemovalDate;
    DRM_DST_ENUM_CONTEXT              contextDSTEnum;
    DRM_DST_SLOT_CONTEXT              contextDSTSlot;
    DRM_BOOL                          fInited;
    DRM_BOOL                          fAny;
    DRM_BOOL                          fSkipEnumNext;
} DRM_REMOVAL_DATE_ENUM_PRIVATE;

typedef struct _tagDrmRemovalDateEntry
{
    DRM_LID           lid;
    DRM_DST_SLOT_HINT slotHint;
} DRM_REMOVAL_DATE_ENTRY;

/* opaque versions of contexts, corresponding to those actually declared in drmremvoaldatestore.c */

typedef struct __tagDRM_REMOVAL_DATE_CONTEXT
{
    DRM_BYTE rgbOpaqueData [__CB_DECL(SIZEOF(DRM_REMOVAL_DATE_CONTEXT_PRIVATE))];
} DRM_REMOVAL_DATE_CONTEXT;

typedef struct __tagDRM_REMOVAL_DATE_ENUM
{
    DRM_BYTE rgbOpaqueData [__CB_DECL(SIZEOF(DRM_REMOVAL_DATE_ENUM_PRIVATE))];
} DRM_REMOVAL_DATE_ENUM;

EXIT_PK_NAMESPACE;

#endif /* __DRM_REMOVAL_DATE_STORE_CONTEXT__ */
