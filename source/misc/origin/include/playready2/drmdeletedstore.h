/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRM_DELETEDSTORE__
#define __DRM_DELETEDSTORE__

#include <drmdatastore.h>

ENTER_PK_NAMESPACE;

DRM_API DRM_NO_INLINE DRM_BOOL DRM_CALL DRM_DELETEDSTORE_IsDeletedStoreSupported(DRM_VOID) DRM_NO_INLINE_ATTRIBUTE;
DRM_API DRM_BOOL DRM_CALL DRM_DELETEDSTORE_IsDeletedStoreUnsupported(DRM_VOID);

DRM_API DRM_RESULT DRM_CALL DRM_DELETEDSTORE_UpdateRecentExpired(
    __in       DRM_DST            *pDatastore,
    __in const DRM_KID            *pKID ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_RESULT DRM_CALL DRM_DELETEDSTORE_CheckRecentExpired(
    __in                  DRM_VOID                *f_pcontextOEM,
    __in                  DRM_DST                 *f_pDatastore,
    __in            const DRM_KID                 *f_pKID,               /* kid to query */
    __out_ecount(1)       DRM_BOOL                *f_pfRecentExpired );  /* query result */

EXIT_PK_NAMESPACE;

#endif /* __DRM_DELETEDSTORE__ */

