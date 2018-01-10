/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/


#ifndef __DRMDEBUG_H__
#define __DRMDEBUG_H__

#include <oemdebug.h>

ENTER_PK_NAMESPACE;

/*************************************************************************
*
*   debug printf macro
*   Sample calling seq:
*
*   TRACE(("My name is %s", "DRM"));
*
*   Note the double parenthesis.
*************************************************************************/
#if DBG

    #undef TRACE

    #ifdef __cplusplus_cli
        // If building under a C++/CLI flag ignore all TRACE statements
        #define TRACE(x)
    #else
        #define TRACE(x) do { Oem_Debug_Trace("TRACE at %s(%d): ", __FILE__, __LINE__); Oem_Debug_Trace x; Oem_Debug_Trace("\r\n"); } while( FALSE )
    #endif

    #undef TRACE_IF_FAILED
    #define TRACE_IF_FAILED(x) do { if ( DRM_FAILED( dr ) ){ TRACE(x); } } while ( FALSE )

#else  // DBG

    #ifndef TRACE
    #define TRACE(x)
    #endif

    #ifndef TRACE_IF_FAILED
    #define TRACE_IF_FAILED(x)
    #endif

#endif  // DBG


/*
** Compile-time asserts cause PREfast warnings regarding the comparison of two constants.
** So, enable this macro only when the PREfast tool is not analyzing the code.
*/
#ifndef _PREFAST_
    #define DRMSIZEASSERT(x,y)  \
        {switch(0){case ((x)==(y)?0:(y)):case (y):;}} \
        {switch(0){case ((y)==(x)?0:(x)):case (x):;}}
#else
    #define DRMSIZEASSERT(x,y)
#endif


#define ENSURE_MEMBERS_ADJACENT(struc,member1,member2)  ((DRM_OFFSET_OF(struc,member1)+(DRM_DWORD)(SIZEOF(((struc *)0)->member1))) == DRM_OFFSET_OF(struc,member2))

#if DBG
    #undef DRMASSERT
    /* Call the global assert handler function. */

    #ifdef __cplusplus_cli
        /* Don't include strings in C++/CLI code */
        #define DRMASSERT(x) Oem_Debug_Assert((x), NULL, NULL, __LINE__)
    #else
        #define DRMASSERT(x) Oem_Debug_Assert((x), #x, __FILE__, __LINE__)
    #endif

#else
    #ifndef DRMASSERT
        #define DRMASSERT( x )
    #endif
    #ifndef DRMCASSERT
        #define DRMCASSERT( x )
    #endif
#endif

EXIT_PK_NAMESPACE;

#endif  /* __DRMDEBUG_H__ */

