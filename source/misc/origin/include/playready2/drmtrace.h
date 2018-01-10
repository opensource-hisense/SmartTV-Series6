/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRMTRACE_H__
#define __DRMTRACE_H__

#include <drmtypes.h>
#include <drmpragmas.h>

ENTER_PK_NAMESPACE;

/*
** Maximum number of components that can be defined.
** DRM_TRACE_COMPONENT_ID macro is used to assign a component
** ID (DWORD) to a scope.
*/
#define MAX_TRACE_COMPONENT     256

/* Enumeration of the various trace level. */
typedef enum
{
    TRACE_NONE     = 0,
    TRACE_FATAL    = 1,
    TRACE_CRITICAL = 2,
    TRACE_WARNING  = 3,
    TRACE_INFO     = 4,
    TRACE_VERBOSE  = 5
} eTraceLevel;

/* Enumeration of the various robustness level. */
typedef enum
{
    TRACE_NON_ROBUST  = 0,
    TRACE_ROBUST      = 1,
    TRACE_MOST_ROBUST = 2
} eTraceRobustLevel;

#define TRACE_DEFAULT_ROBUST    TRACE_NON_ROBUST

/*
** Predefined event type for scope.
*/
typedef enum
{
    TRACE_DEFAULT_EVENT = 0,
    TRACE_ENTER_SCOPE   = 1,
    TRACE_LEAVE_SCOPE   = 2
    /* OEM may define customized events starting with value 4. */
} eTraceScopeEventType;

/* Enumeration of the various trace channels. */
typedef enum
{
    TRACE_CONSOLE_CHANNEL = 0x01,
    TRACE_FILE_CHANNEL    = 0x02,
    /* OEM may define customized channels starting with mask 0x04. */
} eTraceChannelType;

#if DRM_SUPPORT_TRACING

/* Global trace context data structure. */
typedef struct __tagTRACE_GLOBAL_CONTEXT
{
    /* Current global trace level. */
    eTraceLevel m_eTraceLevel;

    /* Default component trace levels. */
    eTraceLevel m_rgeComponentTraceLevels[ MAX_TRACE_COMPONENT ];

    /*
    ** Init flag to indicate whether the
    ** data structure has been initialized.
    */
    DRM_BOOL m_fInit;

    /*
    ** OEM data field to allow OEM to store its
    ** specific information (such as a trace log
    ** file pointer).
    */
    DRM_VOID *m_pvOEMData;

    /*
    ** Flag indicating whether is currently in
    ** Oem_Trace_Enter/LeaveScope() API. This flag
    ** is used to prevent recursive entering
    ** of Oem_Trace_Enter/LeaveScope().
    */
    DRM_BOOL m_fEnterScope;

    /*
    ** Flag indicating whether is currently in
    ** Oem_Trace_Start API. This flag
    ** is used to prevent recursive entering
    ** of Oem_Trace_Start.
    */
    DRM_BOOL m_fStartTrace;

    /* Bit mask of trace channel. */
    DRM_DWORD m_dwChannelMask;

} DRM_TRACE_GLOBAL_CONTEXT;

EXIT_PK_NAMESPACE;

#include <oemtrace.h>

ENTER_PK_NAMESPACE;

DRM_API DRM_TRACE_GLOBAL_CONTEXT * DRM_CALL Oem_Trace_GetGlobalContext( DRM_VOID );

/** OEM MUST provide its own mapping of the following DRM_TRACE macros in oemtrace.h. */

/*
** #define DRM_TRACE_ID( trace_id )
** Note: DRM_TRACE_ID macro is used to handle all trace_id's in a single location e.g if
**       the OEM layer would like to ignore (and hence not define) the trace ID's then
**       this macro can be used to define all such trace_id's to say 0.  If OEM layer is
**       going to use the trace_id's, then it must define the values for the trace_ids.
**
** #define DRM_TRACE( szFormat )
** Note: DRM_TRACE macro is used to trace an arbitrary format string with arbitrary number
**       of parameters. The length of the result string is only limited by OEM's specific
**       implementation. All information must be enclosed by a pair of parenthesis. For example,
**       DRM_TRACE( ( "%s %d.", "Hello World", 123 ) ).
**       DRM_TRACE must be used within a scope that has already been defined by the
**       the DRM_PROFILING_ENTER_SCOPE and DRM_PROFILING_LEAVE_SCOPE macros.
**
** #define DRM_TRACE_NO_SCOPE( szFormat )
** Note: DRM_TRACE_NO_SCOPE is almost identical to DRM_TRACE, with the only difference that
**       DRM_TRACE_NO_SCOPE can be used anywhere whether a scope has been defined or not.
**       Traces originated from DRM_TRACE_NO_SCOPE cannot be filtered since they are not
**       associated with either a specific scope or a specific component.
**       The TRACE macro is translated into DRM_TRACE_NO_SCOPE.
**
** #define DRM_TRACE_ID0( eRobust, dwID, dwParam0 )
** #define DRM_TRACE_ID1( eRobust, dwID, dwParam0, dwParam1 )
** #define DRM_TRACE_ID2( eRobust, dwID, dwParam0, dwParam1, dwParam2 )
** #define DRM_TRACE_ID3( eRobust, dwID, dwParam0, dwParam1, dwParam2, dwParam3 )
** Note: DRM_TRACE_IDX macros are used to trace a predefined format string specified by a
**       format string ID. The format string takes zero or more DWORD parameters.
**       If OEM wants to use format strings with more than three parameters, it can add more
**       macro definitions to the DRM_TRACE_IDX macro group.
**
** #define DRM_TRACE_ENTER_SCOPE( eRobust, dwScopeID )
** #define DRM_TRACE_LEAVE_SCOPE( eRobust, dwScopeID, dr )
** Note: The enter/leave scope trace maros are implicitly called by DRM_PROFILING_ENTER_SCOPE
**       and DRM_PROFILING_LEAVE_SCOPE macros. Generally user should not deal with these two
**       macros directly. It is recommended to set the filter level of enter/leave scope trace
**       at a higher trace level (e.g. equal to or above TRACE_INFO ) to avoid unnecessary
**       details.
**
** #define DRM_TRACE_STATUS_CODE( eRobust, dwEventID, dr )
** Note: The status trace macro is used to trace a status code associated with a specific
**       event ID. The exact meaning of an event ID is defined by the user.
**
** #define DRM_TRACE_START( pOEMContext, pdstrFilename )
** #define DRM_TRACE_STOP()
** Note: The start/stop trace macros are defined by OEM to start/stop the tracing machanism.
**       For example, OEM can open a trace log file when DRM_TRACE_START is called, and close
**       the trace log file when DRM_TRACE_STOP is called.
*/

/* The following macros are shared by all OEM tracing implementations. */

/*
** Set the global trace level to a certain level will filter out all traces from
** scopes that have scope tracel level higher than the global trace level.
*/
#define DRM_GLOBAL_TRACE_LEVEL( Level ) \
                                    Oem_Trace_GetGlobalContext()->m_eTraceLevel = ( Level );

/*
** Set the global component trace level to a certain level will filter out all traces from
** components that have component trace level higher than the global component trace level.
*/
#define DRM_GLOBAL_COMPONENT_TRACE_LEVEL( ID, Level ) \
                                    if ( ID >=0 && ID < MAX_TRACE_COMPONENT ) \
                                    { \
                                        Oem_Trace_GetGlobalContext()->m_rgeComponentTraceLevels[ ID ] = ( Level ); \
                                    }

/*
** Define the current scope trace level. The current scope must have already been defined
** by the DRM_PROFILING_ENTER_SCOPE and DRM_PROFILING_LEAVE_SCOPE macros.
*/
#define DRM_TRACE_LEVEL( Level )    ScopeContext.m_eTraceLevel = ( Level );

/*
** Associate the current scope with a component ID. By default all scopes belongs to component 0.
** Each scope can only be associated with one component at one time. The current scope must have
** already been defined by the DRM_PROFILING_ENTER_SCOPE and DRM_PROFILING_LEAVE_SCOPE macros.
*/
#define DRM_TRACE_COMPONENT_ID( ID ) \
                                    ScopeContext.m_dwComponent = ( ID );

/*
** Internal macro that is used to determine whether the trace from the current scope should be filtered.
** The trace from the current scope should be filtered if both of the following conditions are met:
** 1. The current scope has a scope tracel level that is higher than the global trace level.
** 2. The current scope has a component trace level that is higher than the global component trace level.
*/
#define _DRM_TRACE_IF_NOT_FILTERED   if ( Oem_Trace_GetGlobalContext()->m_eTraceLevel >= ScopeContext.m_eTraceLevel || \
                                          Oem_Trace_GetGlobalContext()->m_rgeComponentTraceLevels[ ScopeContext.m_dwComponent ] >= ScopeContext.m_eTraceLevel )

/* Turn on a specific trace channel. By default only console channel ( TRACE_CONSOLE_CHANNEL ) is turned on. */
#define DRM_TRACE_CHANNEL_ON( Channel ) \
                                    Oem_Trace_GetGlobalContext()->m_dwChannelMask |= ( ( Channel ) );

/* Turn off a specific trace channel. */
#define DRM_TRACE_CHANNEL_OFF( Channel ) \
                                    Oem_Trace_GetGlobalContext()->m_dwChannelMask &= ( ~( Channel ) );

#else

/* Define all trace macros to nothing is DRM_SUPPORT_TRACING is 0. */
#define DRM_TRACE_ID( trace_id )
#define DRM_TRACE( szFormat )
#define DRM_TRACE_NO_SCOPE( szFormat )
#define DRM_TRACE_ID0( eRobust, dwID, dwParam0 )
#define DRM_TRACE_ID1( eRobust, dwID, dwParam0, dwParam1 )
#define DRM_TRACE_ID2( eRobust, dwID, dwParam0, dwParam1, dwParam2 )
#define DRM_TRACE_ID3( eRobust, dwID, dwParam0, dwParam1, dwParam2, dwParam3 )
#define DRM_TRACE_ENTER_SCOPE( eRobust, dwScopeID )
#define DRM_TRACE_LEAVE_SCOPE( eRobust, dwScopeID, dr )
#define DRM_TRACE_STATUS_CODE( eRobust, dwEventID, dr )
#define DRM_TRACE_START( pOEMContext, pdstrFilename )
#define DRM_TRACE_STOP()

#define DRM_GLOBAL_TRACE_LEVEL( Level )
#define DRM_GLOBAL_COMPONENT_TRACE_LEVEL( ID, Level )
#define DRM_TRACE_LEVEL( Level )
#define DRM_TRACE_COMPONENT_ID( ID )
#define DRM_TRACE_IF_NOT_FILTERED
#define DRM_TRACE_CHANNEL_ON( Channel )
#define DRM_TRACE_CHANNEL_OFF( Channel )

#endif  /* DRM_SUPPORT_TRACING */

EXIT_PK_NAMESPACE;

#endif  /* __DRMTRACE_H__ */

