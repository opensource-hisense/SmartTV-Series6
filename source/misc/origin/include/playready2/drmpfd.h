/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRMPFD_H__
#define __DRMPFD_H__

#include <drmpfdmanager.h>

ENTER_PK_NAMESPACE;

DRM_RESULT _PfdDrmManagerFreeContentSession(
    __inout    PFDMGR_CONTEXT_INTERNAL *f_pContext,
    __in const DRM_DWORD                f_dwSessionId
);

DRM_RESULT _PfdDrmManagerFreeAllContentSessions(
    __inout    PFDMGR_CONTEXT_INTERNAL *f_pContext
);

DRM_RESULT _PfdDrmManagerGetSession(
    __inout const PFDMGR_CONTEXT_INTERNAL                  *f_pContext,
    __in    const DRM_DWORD                                 f_dwSessionId,
    __out         PFDMGR_CONTENT_SESSION_CONTEXT_INTERNAL **f_pContentSession );

EXIT_PK_NAMESPACE;

#endif  /* __DRMPFD_H__ */
