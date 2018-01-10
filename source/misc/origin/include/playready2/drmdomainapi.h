/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRM_DOMAIN_API_H
#define __DRM_DOMAIN_API_H

#include <drmdomainimp.h>
#include <drmmanagertypes.h>

ENTER_PK_NAMESPACE;

DRM_API DRM_NO_INLINE DRM_BOOL DRM_CALL DRM_DOMAIN_IsDomainSupported(DRM_VOID) DRM_NO_INLINE_ATTRIBUTE;
DRM_API DRM_BOOL DRM_CALL DRM_DOMAIN_IsDomainUnsupported(DRM_VOID);

EXIT_PK_NAMESPACE;

#endif /* __DRM_DOMAIN_API_H */

