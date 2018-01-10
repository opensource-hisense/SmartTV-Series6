/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRMSETFEATURES_H__
#define __DRMSETFEATURES_H__

#ifdef __cplusplus
extern "C" {
#endif

/*
** Sample OEM profiles - OEMs can make variants of these profiles and give them names here.
*/
#define DRM_BUILD_PROFILE_OEM                  10
#define DRM_BUILD_PROFILE_OEMPLAYONLY          11

/*
** MS internal only (No value in OEM modification): Other profiles
** -----------------------------------------------
** MIN and MAX TEST profiles - This range of values is used internally for testing
*/
#define DRM_BUILD_PROFILE_PK                     1
#define DRM_BUILD_PROFILE_PC                    21
#define DRM_BUILD_PROFILE_WP8                   22
#define DRM_BUILD_PROFILE_PK_TEST_MIN          100
#define DRM_BUILD_PROFILE_PK_TEST_MAX          199
#define DRM_BUILD_PROFILE_WM7                  500
#define DRM_BUILD_PROFILE_XBOX                 600
#define DRM_BUILD_PROFILE_IOS                  700
#define DRM_BUILD_PROFILE_RMSDK                800
#define DRM_BUILD_PROFILE_LINUX                900
#define DRM_BUILD_PROFILE_PRND_TX_1            950
#define DRM_BUILD_PROFILE_MPR                 1000

/*
** Ensure the build profile is properly set.
*/
#ifndef DRM_BUILD_PROFILE
    #ifndef __BUILDMACHINE__
        #error "DRM_BUILD_PROFILE must be set to one of the above values either by the build environment or here."
        /* Example: #define DRM_BUILD_PROFILE DRM_BUILD_PROFILE_PK */
    #else
        /* MS internal only (No value in OEM modification): MS builds (detected via __BUILDMACHINE__) default to PC profile */
        #define DRM_BUILD_PROFILE DRM_BUILD_PROFILE_PC
    #endif
#endif

/*
** Pick correct compilation options based on a build profile.
*/
#if DRM_BUILD_PROFILE == DRM_BUILD_PROFILE_OEM  ||  DRM_BUILD_PROFILE == DRM_BUILD_PROFILE_OEMPLAYONLY

/*
** If building inside the provided nmake build system:
** Do nothing.
** If building outside the provided nmake build system:
** Uncommment one of the #includes below.
** Modify the corresponding header for your specific OEM implementation.
*/

/* #include <drmbuild_oem.h> */
/* #include <drmbuild_oemplayonly.h> */

/*
** MS internal only (No value in OEM modification): #elif sections below
*/
#elif DRM_BUILD_PROFILE == DRM_BUILD_PROFILE_IOS
#include <drmbuild_ios.h>
#include <drmobfusdefs.h>
#elif DRM_BUILD_PROFILE == DRM_BUILD_PROFILE_PK
/* Do nothing */
#elif DRM_BUILD_PROFILE == DRM_BUILD_PROFILE_RMSDK
/* Do nothing */
#elif DRM_BUILD_PROFILE == DRM_BUILD_PROFILE_PC
#if __MACINTOSH__
#include <drmbuild_pc.h>
#else  /* __MACINTOSH__ */
/* #include <banned.h> */
#endif /* __MACINTOSH__ */
#elif DRM_BUILD_PROFILE == DRM_BUILD_PROFILE_WP8
/* Do nothing */
#elif DRM_BUILD_PROFILE == DRM_BUILD_PROFILE_WM7
#include <drmobfusdefs.h>
#elif DRM_BUILD_PROFILE == DRM_BUILD_PROFILE_XBOX
#include <drmobfusdefs.h>
#elif DRM_BUILD_PROFILE >= DRM_BUILD_PROFILE_PK_TEST_MIN && DRM_BUILD_PROFILE <= DRM_BUILD_PROFILE_PK_TEST_MAX
/* Do nothing */
#elif DRM_BUILD_PROFILE == DRM_BUILD_PROFILE_MPR
#include <drmobfusdefs.h>
#elif DRM_BUILD_PROFILE == DRM_BUILD_PROFILE_LINUX
#include <drmbuild_linux.h>
#elif DRM_BUILD_PROFILE == DRM_BUILD_PROFILE_PRND_TX_1
#include <drmbuild_linux.h>
#else
#error "Invalid value of DRM_BUILD_PROFILE in drmfeatures.h"
#endif

/*
#------------------------------------------------------------------------------
# DRM_SUPPORT_PROFILING
# Set this flag to '1' to enable profiling functionality
# Profiling macros compile to gather performance data and write to a binary
# file named perf.dat or perfagg.dat. The file can be used by external tools
# for further analysis.
# Profiling must be activated by a runtime call of DRM_Start_Profiling(),
# and it can also be turned off at runtime by calling DRM_Stop_Profiling().
# To minimize overhead introduced by the profiling, samples collected during
# profiling are buffered first and flushed to a file when the buffer becomes full.
# The file drmprofile.h defines several contstants to modify the behavior of
# the profiling.
#
# If this flag is '0', the profiling macros compile to nothing.
#
# An application must still link to drmprofilingreal.lib in order for
# profiling functions to be enabled.  Otherwise, the profiling macros
# compile to function calls that themselves do nothing.
#
# There are no top level APIs directly affected by this flag.
#
#------------------------------------------------------------------------------
*/
#ifndef DRM_SUPPORT_PROFILING
#define DRM_SUPPORT_PROFILING           0
#endif

/*
#------------------------------------------------------------------------------
# DRM_EXPORT_APIS_TO_DLL
# MS internal only (No value in OEM modification):
# Set this flag to '1' to mark DRM_API functions to be exported from a DLL.
#------------------------------------------------------------------------------
*/
#ifndef DRM_EXPORT_APIS_TO_DLL
#define DRM_EXPORT_APIS_TO_DLL          0
#endif
/*
#------------------------------------------------------------------------------
# DRM_TEST_LINK_TO_DRMAPI_DLL
# MS internal only (No value in OEM modification):
# Set this flag to '1' to allow test code executables to link with a DLL.
#------------------------------------------------------------------------------
*/
#ifndef DRM_TEST_LINK_TO_DRMAPI_DLL
#define DRM_TEST_LINK_TO_DRMAPI_DLL     0
#endif

/*
#------------------------------------------------------------------------------
# DRM_MAX_LICENSE_CHAIN_DEPTH
# MS internal only (No value in OEM modification):
# Total number of licenses in a chain support by this DRM implementation
# Must be set to 2.
#------------------------------------------------------------------------------
*/
#ifndef DRM_MAX_LICENSE_CHAIN_DEPTH
#define DRM_MAX_LICENSE_CHAIN_DEPTH   2
#endif

/*
#------------------------------------------------------------------------------
# DRM_SUPPORT_KEYFILE
# MS internal only (No value in OEM modification):
# Set this flag to '1' to include the support of Key files.
# Must be set to 1.
#------------------------------------------------------------------------------
*/
#ifndef DRM_SUPPORT_KEYFILE
#define DRM_SUPPORT_KEYFILE  1
#endif

/*
#------------------------------------------------------------------------------
# DRM_NO_OBFUS
# MS internal only (No value in OEM modification):
# Set this flag to '1' to disable using obfuscated group private key BLOB.
#------------------------------------------------------------------------------
*/
#ifndef DRM_NO_OBFUS
#define DRM_NO_OBFUS 1
#endif

/*
#------------------------------------------------------------------------------
# MS internal only (No value in OEM modification):
# These flags must be defined by a profile.
# If building inside the provided nmake build system,
# they will be set by the included .mk files.
# If building outside the provided nmake build system,
# they should be set inside the following #if block above:
# #if DRM_BUILD_PROFILE == DRM_BUILD_PROFILE_OEM
# Refer to comments in that #if block (above).
#------------------------------------------------------------------------------
*/
#ifndef DRM_SUPPORT_ASSEMBLY
#error DRM_SUPPORT_ASSEMBLY must be defined by your profile
#endif

#ifndef DRM_SUPPORT_REACTIVATION
#error DRM_SUPPORT_REACTIVATION must be defined by your profile
#endif

#ifndef DRM_SUPPORT_DATASTORE_PREALLOC
#error DRM_SUPPORT_DATASTORE_PREALLOC must be defined by your profile
#endif

#ifndef DRM_SUPPORT_DEVICE_SIGNING_KEY
#error DRM_SUPPORT_DEVICE_SIGNING_KEY must be defined by your profile
#endif

#ifndef DRM_SUPPORT_ECCPROFILING
#error DRM_SUPPORT_ECCPROFILING must be defined by your profile
#endif

#ifndef DRM_SUPPORT_EMBEDDED_CERTS
#error DRM_SUPPORT_EMBEDDED_CERTS must be defined by your profile
#endif

#ifndef DRM_SUPPORT_FORCE_ALIGN
#error DRM_SUPPORT_FORCE_ALIGN must be defined by your profile
#endif

#ifndef DRM_SUPPORT_INLINEDWORDCPY
#error DRM_SUPPORT_INLINEDWORDCPY must be defined by your profile
#endif

#ifndef DRM_SUPPORT_LOCKING
#error DRM_SUPPORT_LOCKING must be defined by your profile
#endif

#ifndef DRM_SUPPORT_MULTI_THREADING
#error DRM_SUPPORT_MULTI_THREADING must be defined by your profile
#endif

#ifndef DRM_SUPPORT_NATIVE_64BIT_TYPES
#error DRM_SUPPORT_NATIVE_64BIT_TYPES must be defined by your profile
#endif

#ifndef DRM_SUPPORT_NONVAULTSIGNING
#error DRM_SUPPORT_NONVAULTSIGNING must be defined by your profile
#endif

#ifndef DRM_SUPPORT_PRECOMPUTE_GTABLE
#error DRM_SUPPORT_PRECOMPUTE_GTABLE must be defined by your profile
#endif

#ifndef DRM_SUPPORT_PRIVATE_KEY_CACHE
#error DRM_SUPPORT_PRIVATE_KEY_CACHE must be defined by your profile
#endif

#ifndef DRM_SUPPORT_SECUREOEMHAL
#error DRM_SUPPORT_SECUREOEMHAL must be defined by your profile
#endif

#ifndef DRM_SUPPORT_SECUREOEMHAL_PLAY_ONLY
#error DRM_SUPPORT_SECUREOEMHAL_PLAY_ONLY must be defined by your profile
#endif

#ifndef DRM_SUPPORT_TRACING
#error DRM_SUPPORT_TRACING must be defined by your profile
#endif

#ifndef DRM_USE_IOCTL_HAL_GET_DEVICE_INFO
#error DRM_USE_IOCTL_HAL_GET_DEVICE_INFO must be defined by your profile
#endif

#ifndef _DATASTORE_WRITE_THRU
#error _DATASTORE_WRITE_THRU must be defined by your profile
#endif

#ifndef _ADDLICENSE_WRITE_THRU
#error _ADDLICENSE_WRITE_THRU must be defined by your profile
#endif

#ifndef DRM_HDS_COPY_BUFFER_SIZE
#error DRM_HDS_COPY_BUFFER_SIZE must be defined by your profile
#endif

#ifndef DRM_TEST_SUPPORT_NET_IO
#error DRM_TEST_SUPPORT_NET_IO must be defined by your profile
#endif

#ifndef DRM_TEST_SUPPORT_ACTIVATION
#error DRM_TEST_SUPPORT_ACTIVATION must be defined by your profile
#endif

#ifndef USE_PK_NAMESPACES
#error USE_PK_NAMESPACES must be defined by your profile
#endif

#ifndef DRM_INCLUDE_PK_NAMESPACE_USING_STATEMENT
#error DRM_INCLUDE_PK_NAMESPACE_USING_STATEMENT must be defined by your profile
#endif

#ifndef DRM_KEYFILE_VERSION
#error DRM_KEYFILE_VERSION must be defined by your profile
#endif

/*
** MS internal only (No value in OEM modification):
**
** To enforce feature value for ALL profiles add the following pragma and then define a feature:
**
** #pragma warning(disable:4005)
** #define DRM_SUPPORT_SOMEFEATURE 1
*/

#ifdef __cplusplus
}
#endif

#endif  /* __DRMSETFEATURES_H__ */



