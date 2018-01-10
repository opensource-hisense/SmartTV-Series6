/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRMSECURECLOCKCONSTANTS_H__
#define __DRMSECURECLOCKCONSTANTS_H__

#include <drmtypes.h>
#include <oemcryptoctx.h>

ENTER_PK_NAMESPACE;

    extern const DRM_CONST_STRING       g_dstrTagError;
    extern const DRM_CONST_STRING       g_dstrExprVarInGracePeriod;
    extern const DRM_CONST_STRING       g_dstrExprVarGpStartTime;
    extern const DRM_CONST_STRING       g_dstrStatus;
    extern const DRM_CONST_STRING       g_dstrTagGmtTime;
    extern const DRM_CONST_STRING       g_dstrTagRefreshDate;
    extern const DRM_CONST_STRING       g_dstrTagDRMReqRoot;

    extern const DRM_CONST_STRING       g_dstrDefaultPlayReadySecureClockServerUrl;

    extern const PUBKEY  g_pubkeyDefaultPlayReadySecureClockServer;

EXIT_PK_NAMESPACE;

#endif /* __DRMSECURECLOCKCONSTANTS_H__ */

