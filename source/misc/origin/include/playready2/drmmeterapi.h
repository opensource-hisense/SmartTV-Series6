/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRM_METER_API_H
#define __DRM_METER_API_H

#include <drmmetering.h>
#include <drmmanager.h>

ENTER_PK_NAMESPACE;

DRM_API DRM_RESULT DRM_CALL DRM_METERING_UpdateData(
    __in                        DRM_APP_CONTEXT   *f_poAppContext,
    __in                  const DRM_CONST_STRING **f_ppdstrActions,
    __in                        DRM_DWORD          f_cActions );


EXIT_PK_NAMESPACE;

#endif /* __DRM_METER_API_H */
