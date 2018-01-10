/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRM_SYNC_STORE_CONTEXT__
#define __DRM_SYNC_STORE_CONTEXT__

#include <drmtypes.h>
#include <drmdatastore.h>

ENTER_PK_NAMESPACE;

typedef struct _tagSyncContext
{
    DRM_DST_SLOT_CONTEXT      contextDSTSlot;
    DRM_DST_NAMESPACE_CONTEXT contextNameSpace;
    DRM_DST                  *pDatastore;
    DRM_BOOL                  fInited;
} DRM_SYNC_CONTEXT_PRIVATE;

typedef struct _tagSyncListEntry
{
    DRM_BOOL fIsValid;
    DRM_KID  kid;
} SyncListEntry;

typedef struct _tagSyncEnumContext
{
    DRM_SYNC_CONTEXT_PRIVATE *pcontextSync;
    DRM_DST_ENUM_CONTEXT      contextDSTEnum;
    DRM_DST_SLOT_CONTEXT      contextDSTSlot;
    DRM_BOOL                  fInited,
                              fAny;
    SyncListEntry             itemSync;
} DRM_SYNC_ENUM_CONTEXT_PRIVATE;

/* opaque versions of contexts, corresponding to those actually declared in drmsyncstore.c */

typedef struct __tagDRM_SYNC_CONTEXT
{
    DRM_BYTE rgbOpaqueData [__CB_DECL(SIZEOF(DRM_SYNC_CONTEXT_PRIVATE))];
} DRM_SYNC_CONTEXT;

typedef struct __tagDRM_SYNC_ENUM_CONTEXT
{
    DRM_BYTE rgbOpaqueData [__CB_DECL(SIZEOF(DRM_SYNC_ENUM_CONTEXT_PRIVATE))];
} DRM_SYNC_ENUM_CONTEXT;


EXIT_PK_NAMESPACE;

#endif /* __DRM_SYNC_STORE_CONTEXT__ */
