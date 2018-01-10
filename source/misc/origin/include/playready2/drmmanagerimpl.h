/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRMMANAGERIMPL_H__
#define __DRMMANAGERIMPL_H__

#include <drmmanagertypes.h>

ENTER_PK_NAMESPACE;

DRM_API DRM_VOID DRM_CALL _FreeDrmAppInternalContexts(
    __in DRM_APP_CONTEXT_INTERNAL *f_poAppContext );

DRM_API DRM_RESULT DRM_CALL _SetupLicEvalObjectToShare(
    __in DRM_APP_CONTEXT_INTERNAL *f_poAppContextInternal );

DRM_API DRM_BOOL DRM_CALL _BlockTimeBoundLicenses(
    __in const DRM_APP_CONTEXT_INTERNAL *f_poAppContextInternal );

EXIT_PK_NAMESPACE;

#endif /* __DRMMANAGERIMPL_H__ */

