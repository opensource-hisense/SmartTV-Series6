/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __CMDLNPARS_H__
#define __CMDLNPARS_H__

#include <drmtypes.h>

#define DRM_CMD_MAX_ARGUMENTS 15

#ifdef __cplusplus
extern "C" {
#endif

DRM_LONG DRM_CALL DRM_Main(
    __in                    DRM_LONG argc,
    __in_ecount_opt( argc ) DRM_WCHAR** argv );

/* calvin add below */
typedef DRM_LONG (*pfWMain)(DRM_LONG argc, DRM_WCHAR *argv[]);
DRM_LONG main_wrapper(DRM_LONG argc, DRM_CHAR **argv, pfWMain wmain );


#ifdef __cplusplus
}
#endif

ENTER_PK_NAMESPACE;

DRM_LONG DRM_CALL DRM_CMD_ConvertToArgvArgc(
    __inout __nullterminated                  const DRM_WCHAR *lpCmdLine,
    __out_ecount_opt( DRM_CMD_MAX_ARGUMENTS )       DRM_WCHAR *argv[DRM_CMD_MAX_ARGUMENTS] );

DRM_BOOL DRM_CALL DRM_CMD_ParseCmdLine(
    __in_opt            const DRM_WCHAR        *pwszArgument,
    __out_ecount_opt(1)       DRM_WCHAR        *pwchOptionChar,
    __out_opt                 DRM_CONST_STRING *f_pdstrParam,
    __out_opt                 DRM_CONST_STRING *f_pdstrExtra );

DRM_BOOL DRM_CALL DRM_CMD_ParseCmdLineMultiChar(
    __in      const DRM_WCHAR        *pwszArgument,
    __out           DRM_CONST_STRING *pwszOptionStr,
    __out_opt       DRM_CONST_STRING *f_pdstrParam,
    __out_opt       DRM_CONST_STRING *f_pdstrExtra );

DRM_RESULT DRM_CALL DRM_CMD_TryProcessDefaultOption(
    __in const DRM_WCHAR  *f_wszArgument );

EXIT_PK_NAMESPACE;

#endif /* __CMDLNPARS_H__ */
