/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRMNAMESPACE_H__
#define __DRMNAMESPACE_H__

#include <drmfeatures.h>

/*
# Abstract:
#
# This file contains compiler directives for disabling certain compiler-time warnings
# and allow the PK environment to be compiled under elevated warning level
#
#
*/

/*
** Set namespace, USE_PK_NAMESPACES is defined in build profile
*/
#ifdef __cplusplus

#if USE_PK_NAMESPACES
/*
**  Place PK functions in a specific namespace
*/
#define ENTER_EXTERN_C_NAMESPACE extern "C" {
#define EXIT_EXTERN_C_NAMESPACE }
#define ENTER_PK_NAMESPACE namespace PK {
#define EXIT_PK_NAMESPACE };
#define USING_PK_NAMESPACE using namespace PK;
#define ENTER_PK_NAMESPACE_CODE namespace PK {
#define EXIT_PK_NAMESPACE_CODE };
#else /* USE_PK_NAMESPACES */
/*
**  Make PK functions appear as simple C functions
*/
#define ENTER_EXTERN_C_NAMESPACE extern "C" {
#define EXIT_EXTERN_C_NAMESPACE }
#define ENTER_PK_NAMESPACE extern "C" {
#define EXIT_PK_NAMESPACE }
#define USING_PK_NAMESPACE
#define ENTER_PK_NAMESPACE_CODE extern "C" {
#define EXIT_PK_NAMESPACE_CODE }
#endif /* USE_PK_NAMESPACES */

#if DRM_INCLUDE_PK_NAMESPACE_USING_STATEMENT
namespace PK {} /* Make sure namespace is defined before using statement */
using namespace PK;
#endif /* DRM_INCLUDE_PK_NAMESPACE_USING_STATEMENT */

#else /* __cplusplus */

/*
**  Building as C - no need to change prototypes
*/
#define ENTER_EXTERN_C_NAMESPACE
#define EXIT_EXTERN_C_NAMESPACE
#define ENTER_PK_NAMESPACE
#define EXIT_PK_NAMESPACE
#define USING_PK_NAMESPACE
#define ENTER_PK_NAMESPACE_CODE
#define EXIT_PK_NAMESPACE_CODE

#endif /* __cplusplus */

#endif  /* __DRMNAMESPACE_H__ */

