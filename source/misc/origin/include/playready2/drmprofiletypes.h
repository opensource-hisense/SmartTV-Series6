/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRMPROFILETYPES_H__
#define __DRMPROFILETYPES_H__

#include <drmtypes.h>
#include <drmtrace.h>
#include <drmbytemanip.h>
#include <oemcommon.h>

ENTER_PK_NAMESPACE;

/* Maxmimum size of cached sample buffer in bytes, should be a multiple of 16 bytes. */
#define MAX_PROFILE_BUFFER_SIZE     92160

/*
** Scope ID is made up of three components: Module ID (12 bits), Function ID (12 bits) and Block ID (7 bits)
** This Macro has been moved out from conditional compilation so that perftool can access it without turning
** ON profiling.
*/
#define PERF_SCOPE_ID( ModuleID, FuncID, BlockID )  ( ( ( ( ModuleID ) & 0x0fff ) << 19 ) + ( ( ( FuncID ) & 0x0fff ) << 7 ) + ( ( BlockID ) & 0x007f ) )

#if DRM_SUPPORT_PROFILING

    /* Flag to indicate whether to enable user data logging. */
    /* User data logging is not supported under aggregated scope sampling. */
    #define PROFILE_USER_DATA       0

    /* PROFILE_USE_SCOPE is defined to use normal scope sampling mechanism. */
    #define PROFILE_USE_SCOPE       1

    /* PROFILE_USE_AGG_SCOPE is defined to use aggregated scope sampling mechanism. */
    #define PROFILE_USE_AGG_SCOPE   0

    /* PROFILE_STACK_SIZE should be turned on to get the max. stack utilization by DRM APIs. */
    #define PROFILE_STACK_SIZE      0

    /* Note: One and only one of the above two definitions can be 1. */
    #if ( PROFILE_USE_SCOPE && PROFILE_USE_AGG_SCOPE ) || ( !PROFILE_USE_SCOPE && !PROFILE_USE_AGG_SCOPE )
        #error One and only one of PROFILE_USE_SCOPE and PROFILE_USE_AGG_SCOPE can be 1.
    #endif

    #if ( PROFILE_USER_DATA && !PROFILE_USE_SCOPE )
        #error User data logging is supported only under normal scope sampling.
    #endif

    #if ( PROFILE_USER_DATA && PROFILE_USE_AGG_SCOPE )
        #error User data logging is not supported under aggregated scope sampling.
    #endif

    /* Maximum levels of nested scope calls. */
    #define MAX_PROFILE_SCOPE_LEVEL     512

    /* Maximum number of aggregated scopes. */
    #define MAX_PROFILE_AGG_SCOPES      1024

    /*
    ** PERF_AGG_SCOPE_CONTEXT is used to store aggregated information of a scope.
    ** All PERF_AGG_SCOPE_CONTEXT structures are stored in global memory and
    ** are persisted at the end of profiling.
    */
    typedef struct _perf_scope_agg_context
    {
        /* Define detail level of logging for this scope. 0: do not check detail level. */
        DRM_DWORD m_nDetailLevel;

        /* Define feature set this scope belongs to. 0: do not check feature set. */
        DRM_DWORD m_nFeatureSet;

        /* Scope ID. */
        DRM_DWORD m_dwScopeID;

        /* Aggregated duration of the scope. */
        DRM_DWORD m_dwDuration;

        /* Total call count of the scope. */
        DRM_DWORD m_dwCallCount;

    } PERF_AGG_SCOPE_CONTEXT;

    /* PERF_GLOBAL_CONTEXT is the global context of the profiling machanism. */
    typedef struct _perf_global_context
    {
        /* Scope stack. */
        DRM_DWORD m_dwScopeID[ MAX_PROFILE_SCOPE_LEVEL ];

        /* Point to top of the scope stack. */
        DRM_DWORD m_nCurrScope;

        /* Logging scopes with detail level < this value.  */
        DRM_DWORD m_nDetailLevel;

        /* Logging scopes within a specific group of feature sets. */
        DRM_DWORD m_nFeatureSet;

        /* Next PER_AGG_SCOPE_CONTEXT slot number to be assigned. */
        DRM_DWORD m_nCurrAggScope;

        /* File handle for normal scope samples. */
        OEM_FILEHDL m_fp;

        /* File handle for aggregated scope samples. */
        OEM_FILEHDL m_fpAgg;

        /* Buffer to cache normal scope samples to minimize I/O. */
        DRM_BYTE m_bBuffer[ MAX_PROFILE_BUFFER_SIZE ];

        /* Next m_bBuffer slot to be assigned. */
        DRM_DWORD m_dwBufferIndex;

        /* Global aggregated scope context. */
        PERF_AGG_SCOPE_CONTEXT m_AggScopes[ MAX_PROFILE_AGG_SCOPES ];

        /* Flag indicating whether the profiling machanism is enable or not. */
        DRM_BOOL m_bRunning;

        /* Flag to prevent recursive profiling. */
        DRM_BOOL m_bInProfile;

        /* Time spent in writing profiling logs to the disk. */
        DRM_DWORD m_dwLogWriteDuration;

        #if PROFILE_USER_DATA
            /* File handle for user data logging. */
            OEM_FILEHDL * m_fpUserData;

            /* Buffer to cache user data to minimize I/O. */
            DRM_BYTE m_bBufferUserData[ MAX_PROFILE_BUFFER_SIZE ];

            /* Next m_bBufferUserData slot to be assigned. */
            DRM_DWORD m_dwBufferUserDataIndex;
        #endif

        #if PROFILE_STACK_SIZE
            /* File handle for logging stack size data. */
            OEM_FILEHDL  m_fpStackSize;

            /* Max stack usage deteted so far for current PK API (scopelevel = 2). */
            DRM_DWORD m_dwMaxStackSize;

            /* Stack base - relative to this stack size will be calculated. */
            DRM_DWORD_PTR m_dwStackBase;

            /* Scope ID of the PK API leading to max stack usage. */
            DRM_DWORD m_dwMaxStackSizeScopeID;

            /* Max stack usage over all the PK APIs involved in a specific scenario. */
            DRM_DWORD m_dwMaxStackSizeinScenario;
        #endif

    } PERF_GLOBAL_CONTEXT;

    typedef struct _perf_scope_context
    {
        /* Define detail level of logging for this scope. 0: do not check detail level. */
        DRM_DWORD m_nDetailLevel;

        /* Define feature set this scope belongs to. 0: do not check feature set. */
        DRM_DWORD m_nFeatureSet;

        /* Scope ID. */
        DRM_DWORD m_dwScopeID;

        /* Parent scope ID. */
        DRM_DWORD m_dwParentScopeID;

        /* Duration of the scope. */
        DRM_DWORD m_dwDuration;

        #if PROFILE_USER_DATA
            /* Custom user data per context. */
            DRM_DWORD m_dwUserData1;

            DRM_DWORD m_dwUserData2;

            /* More user data can be defined afterwards. */
        #endif

        /*
        ** Trace level of the current scope.
        ** If both profiling and tracing are enabled, the
        ** scope level tracing control will stay in the
        ** perf scope context.
        **/
        eTraceLevel m_eTraceLevel;

        /* Current component ID. */
        DRM_DWORD m_dwComponent;

    } PERF_SCOPE_CONTEXT;

#endif /* DRM_SUPPORT_PROFILING */

EXIT_PK_NAMESPACE;

#endif    /* __DRMPROFILETYPES_H__ */

