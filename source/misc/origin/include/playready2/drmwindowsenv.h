/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRM_WINDOWS_ENV_H__
#define __DRM_WINDOWS_ENV_H__

#include <drmcompiler.h>

/*
# Abstract:
#
# This file contains compiler directives for disabling certain Windows CE
# compiler-time warnings and allow the PK environment to be compiled under
# elevated warning level
#
*/

#if defined (DRM_MSC_VER)

#if defined (WINCE)
#pragma warning( push )
#pragma warning(disable:4115) /* 'type' : named type definition in parentheses */
#pragma warning(disable:4201) /* nonstandard extension used : nameless struct/union */
#pragma warning(disable:4214) /* nonstandard extension used : bit field types other than int */
#endif

#include <windows.h>

#ifndef ChkWR
#define ChkWR(expr) {                                           \
            if (!(expr))                                        \
            {                                                   \
                dr = (HRESULT)GetLastError();                   \
                dr = HRESULT_FROM_WIN32((unsigned long)dr);     \
                ExamineDRValue(dr);                             \
                goto ErrorExit;                                 \
            }                                                   \
        }
#endif

#if defined (WINCE)
#pragma warning( pop )
#endif

#endif /* DRM_MSC_VER */

#endif /* __DRM_WINDOWS_ENV_H__ */




