/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/


#ifndef __DRM_LA_H__
#define __DRM_LA_H__

#include <drmliceval.h>

ENTER_PK_NAMESPACE;

DRM_API DRM_RESULT DRM_CALL DRM_LA_EvaluateLicense(
    __in   DRM_LICEVAL_CONTEXT *f_pcontextLEVL,
    __in   DRM_DST             *f_pDatastore );

EXIT_PK_NAMESPACE;

#endif  /* __DRM_LA_H__ */

