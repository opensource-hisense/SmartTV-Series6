/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRMREVOCATIONCONSTANTS_H__
#define __DRMREVOCATIONCONSTANTS_H__

#include <drmtypes.h>

ENTER_PK_NAMESPACE;

    extern const DRM_ANSI_CONST_STRING  g_dastrTagRevocation;
    extern const DRM_ANSI_CONST_STRING  g_dastrAppRevocation;
    extern const DRM_ANSI_CONST_STRING  g_dastrTagRevocationInfo;
    extern const DRM_ANSI_CONST_STRING  g_dastrDeviceRevocation;
    extern const DRM_ANSI_CONST_STRING  g_dastrWMDRMNET_Revocation;

    extern const DRM_ANSI_CONST_STRING  g_dastrRevocationGuidWMDRMNET;
    extern const DRM_ANSI_CONST_STRING  g_dastrRevocationGuidDevice;
    extern const DRM_ANSI_CONST_STRING  g_dastrRevocationGuidApp;

    extern const DRM_LID                g_lidRevocationInfo;
    extern const DRM_LID                g_lidRevocationInfo2;
    extern const DRM_LID                g_lidDeviceRevocation;
    extern const DRM_LID                g_lidWMDRMNET_Revocation;
    extern const DRM_LID                g_lidAppRevocation;
    extern const DRM_LID                g_lidPRRTRevocation;
    extern const DRM_LID                g_lidPRAppRevocation;

EXIT_PK_NAMESPACE;

#endif /* __DRMREVOCATIONCONSTANTS_H__ */

