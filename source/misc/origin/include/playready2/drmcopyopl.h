/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRM_COPYOPL__
#define __DRM_COPYOPL__

#include <drmviewrights.h>

ENTER_PK_NAMESPACE;

DRM_API DRM_BOOL DRM_CALL DRM_COPYOPL_IsCopyOplSupported(DRM_VOID);
DRM_API DRM_BOOL DRM_CALL DRM_COPYOPL_IsCopyOplUnsupported(DRM_VOID);

DRM_API DRM_RESULT DRM_CALL DRM_COPYOPL_ASD_ExamineOutputLevels(
    __in  const DRM_VIEW_RIGHTS_CONTEXT *f_pcontextLQ,
    __in  const DRM_COPY_OPL            *f_pOutputLevels,
    __out       DRM_DWORD               *f_pdwResult );

DRM_API DRM_RESULT DRM_CALL DRM_COPYOPL_ASD_ExamineOutputLevelsXMR(
    __in  DRM_VIEW_RIGHTS_CONTEXT *f_pcontextLQ,
    __out DRM_DWORD               *f_pdwResult );

DRM_API DRM_RESULT DRM_CALL DRM_COPYOPL_ProcessCopyOutputLevelData(
    __in    const DRM_CONST_STRING             *f_pdstrRestrictions,
    __inout       DRM_COPY_OPL                 *f_pCopyOPL,
    __in          DRM_STACK_ALLOCATOR_CONTEXT  *f_pstack );

DRM_API DRM_RESULT DRM_CALL DRM_COPYOPL_ProcessCopyOutputLevelDataXMR(
    __in    const DRM_XMR_COPY_RIGHTS          *f_pxmrCopyRights,
    __inout       DRM_COPY_OPL                 *f_pCopyOPL,
    __in    const DRM_STACK_ALLOCATOR_CONTEXT  *f_pstack );

EXIT_PK_NAMESPACE;

#endif /* __DRM_COPYOPL__ */

