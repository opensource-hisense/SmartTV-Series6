/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRM_METERING__
#define __DRM_METERING__

#include <drmtypes.h>

ENTER_PK_NAMESPACE;

DRM_API DRM_BOOL DRM_CALL DRM_METERING_IsMeteringSupported(DRM_VOID);
DRM_API DRM_BOOL DRM_CALL DRM_METERING_IsMeteringUnsupported(DRM_VOID);

EXIT_PK_NAMESPACE;

#endif /* __DRM_METERING__ */

