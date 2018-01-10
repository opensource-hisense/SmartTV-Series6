/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifdef __DRMLASTINCLUDE_H__
#error drmlastinclude.h should be included in each source file as the last include only.
#endif

#define __DRMLASTINCLUDE_H__

#if DRM_BUILD_PROFILE == DRM_BUILD_PROFILE_IOS
#include <drmobfusdefslast.h>
#elif DRM_BUILD_PROFILE == DRM_BUILD_PROFILE_XBOX
#include <drmobfusdefslast.h>
#endif
