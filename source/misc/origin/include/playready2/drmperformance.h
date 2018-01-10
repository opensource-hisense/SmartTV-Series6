/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRM_PERFORMANCE__
#define __DRM_PERFORMANCE__

#include <drmtypes.h>
#include <drmpragmas.h>

ENTER_PK_NAMESPACE;

typedef enum
{
    eDRM_PERF_LogTag_Enter      = 0,
    eDRM_PERF_LogTag_Exit       = 1,
    eDRM_PERF_LogTag_Separator  = 2
} eDRM_PERF_LogTag;

typedef enum
{
    eDRM_PERF_LogFunction_Drm_Initialize                        = 0,
    eDRM_PERF_LogFunction_Drm_Reader_Bind                       = 1,
    eDRM_PERF_LogFunction_Drm_Reader_Commit                     = 2,
    eDRM_PERF_LogFunction_Drm_Reader_InitDecrypt                = 3,
    eDRM_PERF_LogFunction_Drm_Reader_Decrypt                    = 4,
    eDRM_PERF_LogFunction_Drm_StoreMgmt_CleanupStore            = 5,
    eDRM_PERF_LogFunction_Drm_ACT_GenerateChallengeInternal     = 6,
    eDRM_PERF_LogFunction_Drm_ACT_ProcessWSDLResponseInternal   = 7,
    eDRM_PERF_LogFunction__EvaluateRealTimeExpiration           = 8,
    eDRM_PERF_LogFunction_Oem_Aes_CtrProcessData                = 9,
} eDRM_PERF_LogFunction;

DRM_API DRM_RESULT DRM_CALL DRM_PERF_AllocateLogBuffer(
    __in const DRM_DWORD  f_dwNumberOfEntries );

DRM_API DRM_VOID DRM_CALL DRM_PERF_FreeLogBuffer();

DRM_API DRM_RESULT DRM_CALL DRM_PERF_DumpLogBuffer(
    __in_z const DRM_CHAR  *f_pszFilename );

DRM_API DRM_RESULT DRM_CALL DRM_PERF_On();

DRM_API DRM_VOID DRM_CALL DRM_PERF_Off();

DRM_API DRM_VOID DRM_CALL DRM_PERF_LogMicrosecondCount(
    __in   const      eDRM_PERF_LogTag      f_eLogTag,
    __in   const      eDRM_PERF_LogFunction f_eLogFunction );

DRM_API DRM_RESULT DRM_CALL DRM_PERF_LogSeparator();

EXIT_PK_NAMESPACE;

#endif  /* __DRM_PERFORMANCE__ */

