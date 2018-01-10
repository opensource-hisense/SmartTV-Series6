/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRMCOMPILER_H__
#define __DRMCOMPILER_H__

#include <drmfeatures.h>

/*
** +-----------------------------------+
** | PREFAST WARNING HANDLERS          |
** +-----------------------------------+
*/
#if defined(_PREFAST_)
#define PREFAST_PUSH_DISABLE_EXPLAINED(warning, explanation) \
    __pragma(prefast(push))\
    __pragma(prefast(disable:warning,explanation))
#define PREFAST_POP __pragma(prefast(pop))
#else /* defined(_PREFAST_) */
#define PREFAST_PUSH_DISABLE_EXPLAINED(warning, explanation)
#define PREFAST_POP
#endif /* defined(_PREFAST_) */

/*
** +-----------------------------------+
** | PRAGMA WARNING MACROS             |
** +-----------------------------------+
*/
#if !defined(__PRAGMA_WARNING_MACROS__)
#define __PRAGMA_WARNING_MACROS__ (1)
#if __GNUC__
#define PRAGMA_INTRINSIC(func)
#define PRAGMA_WARNING_DEFAULT(warningnum)
#define PRAGMA_WARNING_DISABLE(warningnum)
#define PRAGMA_WARNING_PUSH
#define PRAGMA_WARNING_POP
#else /* __GNUC__ */
#define PRAGMA_INTRINSIC(func) __pragma(intrinsic(func))
#define PRAGMA_WARNING_DEFAULT(warningnum) __pragma(warning(default:warningnum))
#define PRAGMA_WARNING_DISABLE(warningnum) __pragma(warning(disable:warningnum))
#define PRAGMA_WARNING_PUSH __pragma(warning(push))
#define PRAGMA_WARNING_POP __pragma(warning(pop))
#endif /* __GNUC__ */
#endif /* __PRAGMA_WARNING_MACROS__ */

/*
** +----------------------------------------+
** | 64-BIT TARGET ARCHITECTURE DEFINITIONS |
** +----------------------------------------+
*/
#if defined(_WIN64)
#define DRM_64BIT_TARGET         1
#elif defined(_MAC64)
#define DRM_64BIT_TARGET         1
#else
/*
** Assume the target is a 32-bit architecture.
** If the target is 64-bit, DRM_64BIT_TARGET should be set to 1.
*/
#endif

/*
** Some customers have codebases that set _MSC_VER when using 3rd
** party compilers in order to leverage Microsoft headers.
*/
#if defined(_MSC_VER) && ( _MSC_VER >= 1300 )
#define DRM_MSC_VER _MSC_VER
#endif /* defined(_MSC_VER) && ( _MSC_VER >= 1300 ) */

/*
** +-------------------------------------+
** | MICROSOFT COMPILER SPECIFIC PRAGMAS |
** +-------------------------------------+
*/
#if defined (DRM_MSC_VER) && !defined (__GNUC__)
#define PRAGMA_STRICT_GS_PUSH_ON    __pragma(strict_gs_check(push, on))
#define PRAGMA_STRICT_GS_POP        __pragma(strict_gs_check(pop))
#if DBG
#define PRAGMA_DBG_OPTIMIZATION_OFF __pragma(optimize("",off))
#define PRAGMA_DBG_OPTIMIZATION_ON  __pragma(optimize("",on))
#else   /* DBG */
#define PRAGMA_DBG_OPTIMIZATION_OFF
#define PRAGMA_DBG_OPTIMIZATION_ON
#endif  /* DBG */
#else /* defined (DRM_MSC_VER) && !defined (__GNUC__) */
#define PRAGMA_STRICT_GS_PUSH_ON
#define PRAGMA_STRICT_GS_POP
#define PRAGMA_DBG_OPTIMIZATION_OFF
#define PRAGMA_DBG_OPTIMIZATION_ON
#endif /* defined (DRM_MSC_VER) && !defined (__GNUC__) */

/*
** +-----------------------------------+
** | COMPILATION QUALIFIER DEFINITIONS |
** +-----------------------------------+
*/

/* ====================== Microsoft specific qualifiers ======================= */
/* ============================================================================ */
#if defined (DRM_MSC_VER)

#define DRM_CCALL      __cdecl
#define DRM_STDCALL    __stdcall
#define DRM_FASTCALL   __fastcall

#define DRM_DLLEXPORT  __declspec(dllexport)
#define DRM_DLLIMPORT  __declspec(dllimport)
#define DRM_ALIGN_4    __declspec(align(4))
#define DRM_ALIGN_8    __declspec(align(8))
#define DRM_PACKED

/*
** Microsoft linkers require that extern const data be marked with __declspec(selectany) for it to be discarded
** when not used.  If this tag is not present the data will be linked into final binaries regardless of it being necessary
** or not.
*/
#define DRM_DISCARDABLE __declspec(selectany)

/* ========================= GNU specific qualifiers ========================== */
/* ============================================================================ */
#elif defined (__GNUC__)

#define DRM_CCALL      __attribute__((cdecl))
#define DRM_STDCALL    __attribute__((stdcall))
#define DRM_FASTCALL   __attribute__((fastcall))

#define DRM_DLLEXPORT  __attribute__((dllexport))
#define DRM_DLLIMPORT  __attribute__((dllimport))
#define DRM_ALIGN_4    __attribute__((aligned(4)))
#define DRM_ALIGN_8    __attribute__((aligned(8)))
#define DRM_PACKED     __attribute__((__packed__))


/*
**  Set to nothing as there is no comparable setting
*/
#define DRM_DISCARDABLE

/* ======================== Default (empty) qualifiers ======================== */
/* ============================================================================ */
#else

#define DRM_CCALL
#define DRM_STDCALL
#define DRM_FASTCALL

#define DRM_DLLEXPORT
#define DRM_DLLIMPORT
#define DRM_ALIGN_4
#define DRM_ALIGN_8
#define DRM_DISCARDABLE
#define DRM_PACKED


#endif


#if !DRM_SUPPORT_FORCE_ALIGN
#undef DRM_ALIGN_4
#define DRM_ALIGN_4
#undef DRM_ALIGN_8
#define DRM_ALIGN_8
#endif /* !DRM_SUPPORT_FORCE_ALIGN */

/*
** +-----------------------------------+
** |   COMPILATION BEHAVIOR SETTINGS   |
** +-----------------------------------+
*/

/* ============================ Microsoft Compiler ============================ */
/* ============================================================================ */
#if defined (DRM_MSC_VER)

/* ------------------------------ MS ANSI build ------------------------------- */
/* ---------------------------------------------------------------------------- */
/* when compiling as ANSI, parameter-passing specifications aren't allowed      */
#if defined (__STDC__)
#define SIXTEEN_BIT_ADDRESSING 0
#define DRM_CALL
#define DRMINLINE
#define DRMFORCEINLINE
#define DRM_EXTERN_INLINE
#define DRM_EXPORTED_INLINE
#define DRM_INLINING_SUPPORTED 0
#define DRM_DWORD_ALIGN
#define DRM_NO_INLINE

/* ---------------------------- MS non-ANSI build ----------------------------- */
/* ---------------------------------------------------------------------------- */
#else

/* ----------------- Building the PK DLL ----------------- */
/* Set the macros to export the APIs and global variables  */
#if DRM_EXPORT_APIS_TO_DLL
#define DRM_API         DRM_DLLEXPORT
#define DRM_EXPORT_VAR  DRM_DLLEXPORT
#endif

/* ------------ Building the Test Executables ------------ */
/* Set the macro to import the global variables            */
#if DRM_TEST_LINK_TO_DRMAPI_DLL
#define DRM_EXPORT_VAR  DRM_DLLIMPORT
#endif

#define SIXTEEN_BIT_ADDRESSING  0
#define DRM_CALL                DRM_CCALL
#define DRMINLINE               _inline
#define DRMFORCEINLINE          __forceinline
#define DRM_EXTERN_INLINE       extern DRMINLINE
#define DRM_EXPORTED_INLINE     DRMINLINE
#define DRM_INLINING_SUPPORTED  0
#define DRM_DWORD_ALIGN         DRM_ALIGN_4
#define DRM_NO_INLINE           __declspec(noinline)

#endif

#define DRM_NO_INLINE_ATTRIBUTE
#define DRM_ALWAYS_INLINE_ATTRIBUTE

/* =============================== GNU Compiler =============================== */
/* ============================================================================ */
#elif defined (__GNUC__)
#define DRM_EXTERN_INLINE       extern
#define DRM_EXPORTED_INLINE

#define SIXTEEN_BIT_ADDRESSING  0
#define DRM_CALL
#if DRM_BUILD_PROFILE == DRM_BUILD_PROFILE_IOS
#define DRMINLINE               inline
#define DRMFORCEINLINE          inline __attribute__((always_inline))
#else
#define DRMINLINE               inline
#define DRMFORCEINLINE          inline
#endif /* DRM_BUILD_PROFILE == DRM_BUILD_PROFILE_IOS */
#define DRM_INLINING_SUPPORTED  0
#define DRM_DWORD_ALIGN         DRM_ALIGN_4
#define DRM_NO_INLINE
#define DRM_NO_INLINE_ATTRIBUTE __attribute__((noinline))
#define DRM_ALWAYS_INLINE_ATTRIBUTE

/* ============================= Unknown Compiler ============================= */
/* ============================================================================ */
#else
#error Unknown compiler - please supply appropriate definitions for the above
#endif

#if SIXTEEN_BIT_ADDRESSING
#error The PlayReady Porting Kit no longer supports architectures without 8-bit addressing
#endif

/*
** Currently, creating a DLL is only supported on Microsoft compiler non-ANSI builds,
** so ensure that the following DLL specific macros are empty if not set above.
*/
#ifndef DRM_API
#define DRM_API
#endif

#ifndef DRM_EXPORT_VAR
#define DRM_EXPORT_VAR
#endif


/*
** +-----------------------------------+
** |     LITTLE ENDIAN / BIG ENDIAN    |
** +-----------------------------------+
*/
#if !defined(TARGET_LITTLE_ENDIAN) || !defined(TARGET_SUPPORTS_UNALIGNED_DWORD_POINTERS)
#if defined(_M_IX86)       /* Microsoft X86 compiler detected   */
#ifndef TARGET_LITTLE_ENDIAN
#define TARGET_LITTLE_ENDIAN                        1
#endif  /* TARGET_LITTLE_ENDIAN */
#ifndef TARGET_SUPPORTS_UNALIGNED_DWORD_POINTERS
#define TARGET_SUPPORTS_UNALIGNED_DWORD_POINTERS    1
#endif  /* TARGET_SUPPORTS_UNALIGNED_DWORD_POINTERS */
#elif defined( _M_AMD64 )  /* Microsoft AMD64 compiler detected */
#ifndef TARGET_LITTLE_ENDIAN
#define TARGET_LITTLE_ENDIAN                        1
#endif  /* TARGET_LITTLE_ENDIAN */
#ifndef TARGET_SUPPORTS_UNALIGNED_DWORD_POINTERS
#define TARGET_SUPPORTS_UNALIGNED_DWORD_POINTERS    1
#endif  /* TARGET_SUPPORTS_UNALIGNED_DWORD_POINTERS */
#elif defined( _M_IA64 )   /* Microsoft IA64 compiler detected  */
#ifndef TARGET_LITTLE_ENDIAN
#define TARGET_LITTLE_ENDIAN                        1
#endif  /* TARGET_LITTLE_ENDIAN */
#ifndef TARGET_SUPPORTS_UNALIGNED_DWORD_POINTERS
#define TARGET_SUPPORTS_UNALIGNED_DWORD_POINTERS    1
#endif  /* TARGET_SUPPORTS_UNALIGNED_DWORD_POINTERS */
#elif defined( _XBOX )     /* Microsoft XBOX compiler detected  */
#ifndef TARGET_LITTLE_ENDIAN
#define TARGET_LITTLE_ENDIAN                        0
#endif  /* TARGET_LITTLE_ENDIAN */
#ifndef TARGET_SUPPORTS_UNALIGNED_DWORD_POINTERS
#define TARGET_SUPPORTS_UNALIGNED_DWORD_POINTERS    1
#endif  /* TARGET_SUPPORTS_UNALIGNED_DWORD_POINTERS */
#elif defined( _M_PPC )     /* Microsoft XBOX/PPC compiler detected  */
#ifndef TARGET_LITTLE_ENDIAN
#define TARGET_LITTLE_ENDIAN                        0
#endif  /* TARGET_LITTLE_ENDIAN */
#ifndef TARGET_SUPPORTS_UNALIGNED_DWORD_POINTERS
#define TARGET_SUPPORTS_UNALIGNED_DWORD_POINTERS    1
#endif  /* TARGET_SUPPORTS_UNALIGNED_DWORD_POINTERS */
#elif defined( ARM )
#ifndef TARGET_LITTLE_ENDIAN
#define TARGET_LITTLE_ENDIAN                        1
#endif  /* TARGET_LITTLE_ENDIAN */
#ifndef TARGET_SUPPORTS_UNALIGNED_DWORD_POINTERS
#define TARGET_SUPPORTS_UNALIGNED_DWORD_POINTERS    0
#endif  /* TARGET_SUPPORTS_UNALIGNED_DWORD_POINTERS */
#else
#error Unknown target - you will need to define TARGET_LITTLE_ENDIAN to 0 or 1 and TARGET_SUPPORTS_UNALIGNED_DWORD_POINTERS to 0 or 1.
#endif
#endif  /* !defined(TARGET_LITTLE_ENDIAN) || !defined(TARGET_SUPPORTS_UNALIGNED_DWORD_POINTERS) */


/*
** +-----------------------------------+
** |    BASIC TYPE/SIZE DEFINITIONS    |
** +-----------------------------------+
*/

/*
** In General,
** DRM_CHAR* is used for null terminated ANSI strings
** DRM_BYTE* is used for just plain byte buffer, w/o any termination
*/

/*
** Wide character is special type in C++ - wchar_t,
** while for "C" compilation it is just unsigned short.
** So 2 different types for C and C++.
*/

/* ======================== Microsoft compiler sizes ========================== */
/* ============================================================================ */
#if defined (DRM_MSC_VER)
                                                   /* 8-bit addressing    16 bit addressing*/
typedef unsigned __int8         DRM_BYTE;               /* 1 byte              1 byte */
typedef __int8                  DRM_CHAR;               /* 1 byte              1 byte */
typedef unsigned __int16        DRM_WORD;               /* 2 bytes             1 byte */
typedef __int16                 DRM_SHORT;              /* 2 bytes             1 byte */
typedef unsigned __int16        DRM_WCHAR;              /* 2 bytes             1 byte */
typedef __int32                 DRM_BOOL;               /* 4 bytes             2 bytes */
typedef unsigned long           DRM_DWORD;              /* 4 bytes             2 bytes */
typedef unsigned __int32        DRM_WCHAR32;            /* 4 bytes             2 bytes */
typedef long                    DRM_LONG;               /* 4 bytes             2 bytes */

#if DRM_BUILD_PROFILE == DRM_BUILD_PROFILE_XBOX
#ifdef __cplusplus
typedef __wchar_t               DRM_WCHAR_NATIVE;       /* 2 bytes             1 byte */
#else /* __cplusplus */
typedef unsigned __int16        DRM_WCHAR_NATIVE;       /* 2 bytes             1 byte */
#endif /* __cplusplus */
#else /* DRM_BUILD_PROFILE == DRM_BUILD_PROFILE_XBOX */
typedef unsigned __int16        DRM_WCHAR_NATIVE;       /* 2 bytes             1 byte */
#endif /* DRM_BUILD_PROFILE == DRM_BUILD_PROFILE_XBOX */

/* =========================== GNU compiler sizes ============================= */
/* ============================================================================ */
#elif defined (__GNUC__)

    #include <stdint.h>
                                                       /* 8-bit addressing    16 bit addressing*/
    typedef uint8_t                 DRM_BYTE;               /* 1 byte              1 byte */
    typedef char                    DRM_CHAR;               /* 1 byte              1 byte */
    typedef uint16_t                DRM_WORD;               /* 2 bytes             1 byte */
    typedef int16_t                 DRM_SHORT;              /* 2 bytes             1 byte */

/* DRM_WCHAR needs to be a 2 bytes in size.  Opt for wchar_t if it is the right size,
   otherwise use uint16_t
*/
//#if __WCHAR_MAX__ == 0xFFFF
//	typedef wchar_t                 DRM_WCHAR;              /* 2 bytes             1 byte */
//#else
    typedef uint16_t                DRM_WCHAR;              /* 2 bytes             1 byte */
//#endif

    typedef int32_t                 DRM_BOOL;               /* 4 bytes             2 bytes */
    typedef uint32_t                DRM_DWORD;              /* 4 bytes             2 bytes */
    typedef uint32_t                DRM_WCHAR32;            /* 4 bytes             2 bytes */
#if DRM_64BIT_TARGET
    typedef int32_t                 DRM_LONG;               /* 4 bytes             2 bytes */
#else
    typedef long                    DRM_LONG;               /* 4 bytes             2 bytes */
#endif

    #ifdef __cplusplus
    typedef wchar_t                 DRM_WCHAR_NATIVE;      /* 2 bytes             1 byte */
    #else
    typedef uint16_t                DRM_WCHAR_NATIVE;      /* 2 bytes             1 byte */
    #endif

    #define  vsprintf_s    vsnprintf

/* ============================== Default sizes =============================== */
/* ============================================================================ */
#else

                                                   /* 8-bit addressing    16 bit addressing*/
typedef unsigned char           DRM_BYTE;               /* 1 byte              1 byte */
typedef char                    DRM_CHAR;               /* 1 byte              1 byte */
typedef unsigned short          DRM_WORD;               /* 2 bytes             1 byte */
typedef short                   DRM_SHORT;              /* 2 bytes             1 byte */
typedef unsigned short          DRM_WCHAR;              /* 2 bytes             1 byte */
typedef int                     DRM_BOOL;               /* 1 bytes             1 bytes */
typedef unsigned long           DRM_DWORD;              /* 4 bytes             2 bytes */
typedef unsigned int            DRM_WCHAR32;            /* 4 bytes             2 bytes */
typedef long                    DRM_LONG;               /* 4 bytes             2 bytes */

#ifdef __cplusplus
typedef wchar_t                 DRM_WCHAR_NATIVE;      /* 2 bytes             1 byte */
#else
typedef unsigned short          DRM_WCHAR_NATIVE;      /* 2 bytes             1 byte */
#endif

#endif


/*
** +-----------------------------------+
** | MACRO DEFINITIONS                 |
** +-----------------------------------+
*/

#define DRM_OFFSET_OF(struc,member)   (DRM_DWORD_PTR)&(((struc *)0)->member)

/*
** DRM_SIZEOF_MEMBER uses the DRM_OFFSET_OF trick to reference a member of a struct for use in SIZEOF because sizeof(struct foo.bar) doesn't "just work"
** without an explicit instance of foo
*/
#define DRM_SIZEOF_MEMBER(struc,member) SIZEOF((((struc *)0)->member))
#define DRM_SIZEOF_MEMBER_DEREF(struc,member) SIZEOF(*((((struc *)0)->member)))


/* ====================== Microsoft specific qualifiers ======================= */
/* ============================================================================ */
#if defined (DRM_MSC_VER)

/*
** Compile-time asserts cause PREfast warnings regarding the comparison of two constants.
** So, enable this macro only when the PREfast tool is not analyzing the code.
*/
#ifndef _PREFAST_

    /* Definition of the compile time assert. */
    #define DRMCASSERT( x ) switch(0){case 0:case (x):;}

    /* Assertion of the alignment of a member field within a structure. */
    #define DRMALIGNASSERT( struc, member ) DRMCASSERT( ( DRM_OFFSET_OF( struc, member ) ) % SIZEOF( DRM_WCHAR ) == 0 )

    /* Assertion of adjacency of two member fields within the same structure. */
    #define DRMADJASSERT( struc, member1, member2 ) DRMCASSERT( ENSURE_MEMBERS_ADJACENT( struc, member1, member2 ) )

#else
    /* Definition of the compile time assert. */
    #define DRMCASSERT( x )

    /* Assertion of the alignment of a member field within a structure. */
    #define DRMALIGNASSERT( struc, member ) DRMASSERT( ( DRM_OFFSET_OF( struc, member ) ) % SIZEOF( DRM_WCHAR ) == 0 )

    /* Assertion of adjacency of two member fields within the same structure. */
    #define DRMADJASSERT( struc, member1, member2 ) DRMASSERT( ENSURE_MEMBERS_ADJACENT( struc, member1, member2 ) )

#endif

#else

/* Definition of the compile time assert. */
#define DRMCASSERT( x ) switch(0){case 0:case (x):;}

/* Assertion of the alignment of a member field within a structure. */
#define DRMALIGNASSERT( struc, member ) DRMASSERT( ( DRM_OFFSET_OF( struc, member ) ) % SIZEOF( DRM_WCHAR ) == 0 )

/* Assertion of adjacency of two member fields within the same structure. */
#define DRMADJASSERT( struc, member1, member2 ) DRMASSERT( ENSURE_MEMBERS_ADJACENT( struc, member1, member2 ) )

#endif

/*
** This option enables specific struct alignment on some Microsoft internal builds.
** Should not be used.
*/
#define DRM_OBFUS_FIXED_ALIGN
#ifndef DRM_USE_OBFUS_STRUCT_ALIGN

#define DRM_OBFUS_FILL_BYTES(x)
#define DRM_OBFUS_PTR_TOP
#define DRM_OBFUS_PTR_BTM
#define DRM_OBFUS_FIXED_ALIGN
#define DRM_OBFUS_INIT_PTR_TOP
#define DRM_OBFUS_INIT_PTR_BTM
#define DRM_OBFUS_INIT_FILL
#define DRM_OBFUS_PTR_WRAP_SIZE 0

#endif

#define DRM_ALWAYS_INLINE DRMFORCEINLINE

#if DBG
#define DRM_FRE_INLINE              DRM_NO_INLINE
#define DRM_FRE_INLINE_ATTRIBUTE    DRM_NO_INLINE_ATTRIBUTE
#else  /* DBG */
#define DRM_FRE_INLINE              DRM_ALWAYS_INLINE
#define DRM_FRE_INLINE_ATTRIBUTE    DRM_ALWAYS_INLINE_ATTRIBUTE
#endif /* DBG */

#endif   /* __DRMCOMPILER_H__ */

