/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRMERR_H__
#define __DRMERR_H__

#include <drmtypes.h>
#include <drmdebug.h>
#include <drmresults.h>
#include <drmpragmas.h> /* Required to ChkDR( constant ); */

#if DBG

ENTER_PK_NAMESPACE;
    extern void (*g_pfDebugAnalyzeDR)(unsigned long);
EXIT_PK_NAMESPACE;

#define SetDbgAnalyzeFunction(pfn) g_pfDebugAnalyzeDR = pfn;

#define ExamineDRValue(_drval_) do {                                \
        if( g_pfDebugAnalyzeDR != NULL )                            \
        {                                                           \
            (*g_pfDebugAnalyzeDR)((unsigned long)(_drval_));        \
        }                                                           \
    } while(FALSE)

#else  /* DBG */

#define SetDbgAnalyzeFunction(pfn)
#define ExamineDRValue(_drval_)

#endif  /* DBG */

#if defined (__GNUC__)

/* If using the GNU compiler use __builtin_expect to improve branch predictions */
#define DRM_LIKELY( expr ) __builtin_expect(!!(expr),1)
#define DRM_UNLIKELY( expr ) __builtin_expect(!!(expr),0)

#else  /* __GNUC__ */

#define DRM_LIKELY( expr )    (expr)
#define DRM_UNLIKELY( expr )  (expr)

#endif  /* __GNUC__ */

#if DBG
#define ChkDR(expr) do {            \
            dr = (expr);            \
            ExamineDRValue(dr);     \
            if( DRM_FAILED( dr ) )  \
            {                       \
                if (dr == DRM_E_NOTIMPL) \
                   TRACE( ( "PANIC: NOTIMPL: %s %d %lx\n", __FILE__, __LINE__, dr) ); \
                goto ErrorExit;     \
            }                       \
        } while(FALSE)
#else // DBG
#define ChkDR(expr) do {            \
            dr = (expr);            \
            ExamineDRValue(dr);     \
            if( DRM_FAILED( dr ) )  \
            {                       \
                goto ErrorExit;     \
            }                       \
        } while(FALSE)
#endif

#define ChkMem(expr) do {                                                                       \
            if( DRM_UNLIKELY( NULL == (expr) ) )                                                \
            {                                                                                   \
                TRACE( ( "Allocation failure at %s : %d.\n%s\n", __FILE__, __LINE__, #expr ) );   \
                dr = DRM_E_OUTOFMEMORY;                                                         \
                ExamineDRValue(dr);                                                             \
                goto ErrorExit;                                                                 \
            }                                                                                   \
        } while(FALSE)

#define ChkArg(expr) do {                                                                       \
            if( DRM_UNLIKELY( !(expr) ) )                                                       \
            {                                                                                   \
                TRACE( ("Invalid argument at %s : %d.\n%s\n", __FILE__, __LINE__, #expr) );     \
                dr = DRM_E_INVALIDARG;                                                          \
                ExamineDRValue(dr);                                                             \
                goto ErrorExit;                                                                 \
            }                                                                                   \
        } while(FALSE)

#define ChkPtr(expr) do {                                                                       \
            if( DRM_UNLIKELY( NULL == (expr) ) )                                                \
            {                                                                                   \
                TRACE( ("NULL pointer at %s : %d.\n%s\n", __FILE__, __LINE__, #expr) );         \
                dr = DRM_E_POINTER;                                                             \
                ExamineDRValue(dr);                                                             \
                goto ErrorExit;                                                                 \
            }                                                                                   \
        } while(FALSE)

#define ChkDRMString(s) do {                                                                    \
            if( !(s) || (s)->pwszString == NULL || (s)->cchString == 0 )                        \
            {                                                                                   \
                TRACE( ("Invalid argument at %s : %d.\n%s\n", __FILE__, __LINE__, #s) );        \
                dr = DRM_E_INVALIDARG;                                                          \
                ExamineDRValue(dr);                                                             \
                goto ErrorExit;                                                                 \
            }                                                                                   \
        } while(FALSE)

#define ChkDRMANSIString(s) do {                                                                \
            if( !(s) || (s)->pszString == NULL || (s)->cchString == 0 )                         \
            {                                                                                   \
                TRACE( ("Invalid argument at %s : %d.\n%s\n", __FILE__, __LINE__, #s) );        \
                dr = DRM_E_INVALIDARG;                                                          \
                ExamineDRValue(dr);                                                             \
                goto ErrorExit;                                                                 \
            }                                                                                   \
        } while(FALSE)

#define ChkBOOL(fExpr,err) do {         \
            if( !(fExpr) )              \
            {                           \
                dr = (err);             \
                ExamineDRValue(dr);     \
                goto ErrorExit;         \
            }                           \
        } while(FALSE)

#define ChkFAIL(fExpr) ChkBOOL(fExpr,DRM_E_FAIL)

#define ChkDRContinue(exp) do {         \
            dr=(exp);                   \
            ExamineDRValue(dr);         \
            if( DRM_FAILED( dr ) )      \
            {                           \
                continue;               \
            }                           \
        } while(FALSE)

#define ChkOverflow(a,b) do {                       \
            if( a < b )                             \
            {                                       \
                ChkDR(DRM_E_ARITHMETIC_OVERFLOW);   \
            }                                       \
        } while(FALSE)

#define ChkOverflowUI64(a,b) do {                   \
            if( DRM_UI64Les( a, b ) )               \
            {                                       \
                ChkDR(DRM_E_ARITHMETIC_OVERFLOW);   \
            }                                       \
        } while(FALSE)

#define ChkOverflowI64(a,b) do {                    \
            if( DRM_I64Les( a, b ) )                \
            {                                       \
                ChkDR(DRM_E_ARITHMETIC_OVERFLOW);   \
            }                                       \
        } while(FALSE)

#define ChkBoundsLT( index, arrSize ) do {              \
            if( index >= arrSize )                      \
            {                                           \
                ChkDR( DRM_E_BUFFER_BOUNDS_EXCEEDED );  \
            }                                           \
        } while(FALSE)

#define ChkDRMap( expr, drOriginal, drMapped ) do {     \
            dr = ( expr );                              \
            ExamineDRValue(dr);                         \
            if( dr == ( drOriginal ) )                  \
            {                                           \
                dr = ( drMapped );                      \
                ExamineDRValue(dr);                     \
            }                                           \
            if( DRM_FAILED( dr ) )                      \
            {                                           \
                goto ErrorExit;                         \
            }                                           \
        } while(FALSE)

#define MapDR( drOriginal, drMapped ) do {                                                                          \
            TRACE( ("Error code 0x%X mapped at %s : %d. to 0x%X \n", drOriginal,  __FILE__, __LINE__, drMapped) );  \
            drOriginal = ( drMapped );                                                                              \
        } while(FALSE)

#define AssertChkArg(expr) do {     \
        DRM_BOOL _f = (expr);       \
        DRMASSERT( _f );            \
        ChkArg( _f );               \
    } while(FALSE)

#define AssertChkFeature(expr) do {                                                                         \
        DRM_BOOL _f = (expr);                                                                               \
        if( DRM_UNLIKELY( !_f ) )                                                                           \
        {                                                                                                   \
            TRACE( ( "Incompatible Feature Set Detected at %s : %d.\n%s\n", __FILE__, __LINE__, #expr ) );  \
            DRMASSERT( FALSE );                                                                             \
            ChkDR( DRM_E_BCERT_INVALID_FEATURE );                                                           \
        }                                                                                                   \
    } while(FALSE)

#define DRM_REQUIRE_BUFFER_TOO_SMALL( drRet )   do {   \
        if( drRet != DRM_E_BUFFERTOOSMALL )            \
        {                                              \
            ChkDR( drRet );                            \
            DRMASSERT( FALSE );                        \
            ChkDR( DRM_E_LOGICERR );                   \
        }                                              \
    } while( FALSE )

#endif /* __DRMERR_H__ */

