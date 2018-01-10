/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRMPROFILE_H__
#define __DRMPROFILE_H__

#include <drmprofileconstants.h>
#include <drmprofiletypes.h>

/* OEM function to retrieve global profile context. */
#include <oemprofile.h>

ENTER_PK_NAMESPACE;

#if DRM_SUPPORT_PROFILING

    extern DRM_DWORD Perf_String_Data( DRM_CONST_STRING * pdstrIn );

    extern DRM_DWORD Perf_Binary_Data( DRM_BYTE * pbIn, DRM_DWORD dwSize );

    extern DRM_RESULT Perf_Log_Profile( PERF_SCOPE_CONTEXT * pScopeContext, DRM_DWORD nScopeLevel );

    extern DRM_RESULT Perf_Enter_Scope( PERF_SCOPE_CONTEXT * pScopeContext );

    extern DRM_RESULT Perf_Leave_Scope( PERF_SCOPE_CONTEXT * pScopeContext );

    extern DRM_RESULT Perf_Enter_Agg_Scope( PERF_AGG_SCOPE_CONTEXT ** ppAggScopeContext, DRM_DWORD dwScopeID );

    extern DRM_RESULT Perf_Leave_Agg_Scope( PERF_AGG_SCOPE_CONTEXT * pAggScopeContext, DRM_DWORD dwDuration );

    extern DRM_RESULT Perf_Start_Profiling( DRM_VOID *pOEMContext, DRM_CONST_STRING *dstrPerfFileName );

    extern DRM_RESULT Perf_Stop_Profiling();

    extern DRM_RESULT Perf_Init_ProfileStack();

    /* Macro definitions. */

    /* Returns the performance counter's currrent count in microseconds. */
    static DRM_UINT64 PERF_MICROSECONDS_PER_SECOND = DRM_UI64LITERAL( 0,1000000 );
    #define PERF_CURRENT_MICROSECOND_COUNT  \
        ( DRM_UI64Low32( DRM_UI64Div( DRM_UI64Mul( Oem_Clock_QueryPerformanceCounter( NULL ), PERF_MICROSECONDS_PER_SECOND ), Oem_Clock_QueryPerformanceFrequency( NULL ) ) ) )

    /* Macros used for normal scope sampling. */
    #define PERF_SCOPE_DETAIL_LEVEL_X( DetailLevel)         ScopeContext.m_nDetailLevel = ( DetailLevel );

    #define PERF_SCOPE_FEATURE_SET_X( FeatureSet)           ScopeContext.m_nFeatureSet = ( FeatureSet );

    #define PERF_ENTER_SCOPE_X( ModuleID, FuncID, BlockID ) { \
                                                            PERF_SCOPE_CONTEXT ScopeContext = { 0 }; \
                                                            ScopeContext.m_dwScopeID = PERF_SCOPE_ID( ( ModuleID ), ( FuncID ), ( BlockID ) ); \
                                                            ScopeContext.m_nDetailLevel = 1; \
                                                            ScopeContext.m_nFeatureSet = 0; \
                                                            ScopeContext.m_eTraceLevel = TRACE_FATAL; \
                                                            Perf_Enter_Scope(&ScopeContext); \
                                                            DRM_TRACE_ENTER_SCOPE( TRACE_DEFAULT_ROBUST, ScopeContext.m_dwScopeID );

    #define PERF_LEAVE_SCOPE_X                              Perf_Leave_Scope( &ScopeContext );  \
                                                            DRM_TRACE_LEAVE_SCOPE( TRACE_DEFAULT_ROBUST, ScopeContext.m_dwScopeID, dr ); \
                                                            }

    #define PERF_ENTER_SCOPE( ModuleID, FuncID )            PERF_ENTER_SCOPE_X( ModuleID, FuncID, 1 )

    #define PERF_LEAVE_SCOPE                                PERF_LEAVE_SCOPE_X;

    /* Macros used for aggregated scope sampling. */
    #define PERF_AGG_SCOPE_DETAIL_LEVEL_X( DetailLevel )    pAggScopeContext->m_nDetailLevel = ( DetailLevel );

    #define PERF_AGG_SCOPE_FEATURE_SET_X( FeatureSet )      pAggScopeContext->m_nFeatureSet = ( FeatureSet );

    #define PERF_ENTER_AGG_SCOPE_X( ModuleID, FuncID, BlockID ) { \
                                                            static PERF_AGG_SCOPE_CONTEXT * pAggScopeContext = NULL; \
                                                            DRM_DWORD dwPerfAggEnterTick = PERF_CURRENT_MICROSECOND_COUNT; \
                                                            Perf_Enter_Agg_Scope( &pAggScopeContext, PERF_SCOPE_ID( ( ModuleID ), ( FuncID ), ( BlockID ) ) );

    #define PERF_LEAVE_AGG_SCOPE_X                          dwPerfAggEnterTick = PERF_CURRENT_MICROSECOND_COUNT - dwPerfAggEnterTick; \
                                                            Perf_Leave_Agg_Scope( pAggScopeContext, dwPerfAggEnterTick ); \
                                                            }

    #define PERF_ENTER_AGG_SCOPE( ModuleID, FuncID )        PERF_ENTER_AGG_SCOPE_X( ModuleID, FuncID, 1 )

    #define PERF_LEAVE_AGG_SCOPE                            PERF_LEAVE_AGG_SCOPE_X;

    /* Below are macros that are used externally by the code to be profiled. */

    /* Macros used for global context setup. */
    #define DRM_PROFILING_GLOBAL_DETAIL_LEVEL( DetailLevel )    \
                                                            Oem_Profiling_GetProfileContext()->m_nDetailLevel = ( DetailLevel );

    #define DRM_PROFILING_GLOBAL_FEATURE_SET( FeatureSet )  Oem_Profiling_GetProfileContext()->m_nFeatureSet = ( FeatureSet );

    #define DRM_PROFILING_STRING_HASH( pstrIn )             ( Perf_String_Data( ( DRM_CONST_STRING * )pstrIn ) )

    #define DRM_PROFILING_BINARY_HASH( pbIn, dwSize )       ( Perf_Binary_Data( pbIn, dwSize ) )

    #if PROFILE_USER_DATA

        #define DRM_PROFILING_USER_DATA_1( UserData )       ScopeContext.m_dwUserData1 = ( UserData );

        #define DRM_PROFILING_USER_DATA_2( UserData )       ScopeContext.m_dwUserData2 = ( UserData );

    #else

        #define DRM_PROFILING_USER_DATA_1( UserData )

        #define DRM_PROFILING_USER_DATA_2( UserData )

    #endif  /* PROFILE_USER_DATA */

    /* Define generic macros used in the source code. */
    #if PROFILE_USE_SCOPE

        #define DRM_PROFILING_DETAIL_LEVEL( DetailLevel )   PERF_SCOPE_DETAIL_LEVEL_X( DetailLevel )

        #define DRM_PROFILING_FEATURE_SET( FeatureSet )     PERF_SCOPE_FEATURE_SET_X( FeatureSet )

        #define DRM_PROFILING_ENTER_SCOPE_X                 PERF_ENTER_SCOPE_X

        #define DRM_PROFILING_LEAVE_SCOPE_X                 PERF_LEAVE_SCOPE_X

        #define DRM_PROFILING_ENTER_SCOPE                   PERF_ENTER_SCOPE

        #define DRM_PROFILING_LEAVE_SCOPE                   PERF_LEAVE_SCOPE

    #endif  /* PROFILE_USE_SCOPE */

    #if PROFILE_USE_AGG_SCOPE

        #define DRM_PROFILING_DETAIL_LEVEL( DetailLevel )   PERF_AGG_SCOPE_DETAIL_LEVEL_X(DetailLevel)

        #define DRM_PROFILING_FEATURE_SET( FeatureSet )     PERF_AGG_SCOPE_FEATURE_SET_X(FeatureSet)

        #define DRM_PROFILING_ENTER_SCOPE_X                 PERF_ENTER_AGG_SCOPE_X

        #define DRM_PROFILING_LEAVE_SCOPE_X                 PERF_LEAVE_AGG_SCOPE_X

        #define DRM_PROFILING_ENTER_SCOPE                   PERF_ENTER_AGG_SCOPE

        #define DRM_PROFILING_LEAVE_SCOPE                   PERF_LEAVE_AGG_SCOPE

    #endif  /* PROFILE_USE_AGG_SCOPE */

    #define DRM_Start_Profiling( x, y ) Perf_Start_Profiling( x, y )

    #define DRM_Stop_Profiling()        Perf_Stop_Profiling()

    #define DRM_Init_ProfileStack()     Perf_Init_ProfileStack()

#else   /* DRM_SUPPORT_PROFILING */

    #define DRM_PROFILING_USER_DATA_1( UserData )

    #define DRM_PROFILING_USER_DATA_2( UserData )

    #define DRM_PROFILING_DETAIL_LEVEL( DetailLevel )

    #define DRM_PROFILING_FEATURE_SET( FeatureSet )

    #define DRM_PROFILING_ENTER_SCOPE_X( ModuleID, FuncID, BlockID )

    #define DRM_PROFILING_LEAVE_SCOPE_X()

    #if DRM_SUPPORT_TRACING

        typedef struct _trace_scope_context
        {
            /* Scope ID. */
            DRM_DWORD m_dwScopeID;

            /* Trace level of the current scope. */
            eTraceLevel m_eTraceLevel;

            /* Current component ID. */
            DRM_DWORD m_dwComponent;

        } TRACE_SCOPE_CONTEXT;

        #define DRM_PROFILING_ENTER_SCOPE( ModuleID, FuncID )       { \
                                                                    TRACE_SCOPE_CONTEXT ScopeContext = { 0 }; \
                                                                    ScopeContext.m_dwScopeID = PERF_SCOPE_ID( ( ModuleID ), ( FuncID ), 1 ); \
                                                                    ScopeContext.m_eTraceLevel = TRACE_FATAL; \
                                                                    DRM_TRACE_ENTER_SCOPE( TRACE_DEFAULT_ROBUST, ScopeContext.m_dwScopeID );

        #define DRM_PROFILING_LEAVE_SCOPE                           DRM_TRACE_LEAVE_SCOPE( TRACE_DEFAULT_ROBUST, ScopeContext.m_dwScopeID, dr ); }

    #else

        #define DRM_PROFILING_ENTER_SCOPE( ModuleID, FuncID )

        #define DRM_PROFILING_LEAVE_SCOPE

    #endif  /* DRM_SUPPORT_TRACING */

    #define DRM_PROFILING_GLOBAL_DETAIL_LEVEL( DetailLevel )

    #define DRM_PROFILING_GLOBAL_FEATURE_SET( FeatureSet )

    #define DRM_PROFILING_STRING_HASH( pstrIn )

    #define DRM_PROFILING_BINARY_HASH( pstrIn )

    #define DRM_Start_Profiling( x, y ) DRM_SUCCESS

    #define DRM_Stop_Profiling()        DRM_SUCCESS

    #define DRM_Init_ProfileStack()     DRM_SUCCESS

#endif /* DRM_SUPPORT_PROFILING */

EXIT_PK_NAMESPACE;

#endif    /* __DRMPROFILE_H__ */

