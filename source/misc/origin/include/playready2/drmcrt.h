/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRMCRT_H__
#define __DRMCRT_H__

#include <drmstrsafe.h>
#include <oemcommon.h>

ENTER_PK_NAMESPACE;
DRM_API DRM_BOOL DRM_CALL DRM_CRT_IsCRTSupported(DRM_VOID);
DRM_API DRM_BOOL DRM_CALL DRM_CRT_IsCRTUnsupported(DRM_VOID);
EXIT_PK_NAMESPACE;

ENTER_PK_NAMESPACE;

/* String CRT functions */

DRM_API DRM_BOOL  DRM_CALL DRMCRT_iswspace  (DRM_WCHAR wch);
DRM_API DRM_BOOL  DRM_CALL DRMCRT_iswxdigit (DRM_WCHAR wch);
DRM_API DRM_BOOL  DRM_CALL DRMCRT_iswdigit  (DRM_WCHAR wch);
DRM_API DRM_BOOL  DRM_CALL DRMCRT_iswalpha  (DRM_WCHAR wch);
DRM_API DRM_WCHAR DRM_CALL DRMCRT_towlower  (DRM_WCHAR wch);

DRM_API DRM_BOOL  DRM_CALL DRMCRT_isdigit   (DRM_CHAR ch);

#if DRM_BUILD_PROFILE == DRM_BUILD_PROFILE_WP8 || DRM_BUILD_PROFILE == DRM_BUILD_PROFILE_XBOX || DRM_BUILD_PROFILE == DRM_BUILD_PROFILE_IOS

#ifndef DRM_BUILDING_CRTIMPLREAL_C
#ifdef DRMCRT_memcpy
#undef DRMCRT_memcpy
#endif
#ifdef DRMCRT_memset
#undef DRMCRT_memset
#endif
#ifdef DRMCRT_memcmp
#undef DRMCRT_memcmp
#endif

#if defined(DRM_MSC_VER) || defined(__GNUC__)
DRMFORCEINLINE int DRM_CALL DRMCRT_LocalMemcmp(
    __in_bcount( f_cbCount ) const  DRM_VOID  *f_pLHS,
    __in_bcount( f_cbCount ) const  DRM_VOID  *f_pRHS,
    __in                            DRM_DWORD  f_cbCount ) DRM_ALWAYS_INLINE_ATTRIBUTE;

DRMFORCEINLINE int DRM_CALL DRMCRT_LocalMemcmp(
    __in_bcount( f_cbCount ) const  DRM_VOID  *f_pLHS,
    __in_bcount( f_cbCount ) const  DRM_VOID  *f_pRHS,
    __in                            DRM_DWORD  f_cbCount )
{
    /* Without volatile, some compilers can figure out this is an implementation of a memcmp */
    volatile const char * pRHS = (const char *) f_pRHS;
    const char * pLHS = (const char *) f_pLHS;
    while (f_cbCount--)
    {
        if(*pLHS < *pRHS)
        {
            return -1;
        }
        else if(*pLHS > *pRHS)
        {
            return 1;
        }
        pLHS++;
        pRHS++;
    }
    return 0;
}

#else   /* defined(DRM_MSC_VER) || defined(__GNUC__) */
#error "Unexpected Error: In the profile currently being compiled, either DRM_MSC_VER or __GNUC__ *should* be defined."
#endif  /* defined(DRM_MSC_VER) || defined(__GNUC__) */

#define DRMCRT_memcpy OEM_SECURE_MEMCPY
#define DRMCRT_memset OEM_SECURE_MEMSET
#define DRMCRT_memcmp DRMCRT_LocalMemcmp

#endif  /* DRM_BUILDING_CRTIMPLREAL_C */

#else /* DRM_BUILD_PROFILE == DRM_BUILD_PROFILE_WP8 || DRM_BUILD_PROFILE == DRM_BUILD_PROFILE_XBOX || DRM_BUILD_PROFILE == DRM_BUILD_PROFILE_IOS */

DRM_API DRM_LONG DRM_CALL DRMCRT_memcmp(
    __in_bcount( count ) const DRM_VOID   *src1,
    __in_bcount( count ) const DRM_VOID   *src2,
    __in                       DRM_SIZE_T  count );

DRM_API DRM_VOID DRM_CALL DRMCRT_memset(
    __out_bcount( count ) DRM_VOID   *dst,
    __in                  DRM_DWORD   b,
    __in                  DRM_SIZE_T  count );

DRM_API DRM_VOID DRM_CALL DRMCRT_memcpy(
    __out_bcount( count )       DRM_VOID   *dst,
    __in_bcount( count )  const DRM_VOID   *src,
    __in                        DRM_SIZE_T  count );

#endif /* DRM_BUILD_PROFILE == DRM_BUILD_PROFILE_WP8 || DRM_BUILD_PROFILE == DRM_BUILD_PROFILE_XBOX || DRM_BUILD_PROFILE == DRM_BUILD_PROFILE_IOS*/

DRM_API DRM_VOID * DRM_CALL DRMCRT_memmove(
    __out_bcount( count )       DRM_VOID  *dst,
    __in_bcount( count )  const DRM_VOID  *src,
    __in                        DRM_SIZE_T count );

DRM_API DRM_LONG DRM_CALL DRMCRT_wcsncmp(
    __in_ecount( count ) const DRM_WCHAR  *first,
    __in_ecount( count ) const DRM_WCHAR  *last,
    __in                       DRM_SIZE_T  count );

DRM_API DRM_LONG DRM_CALL DRMCRT_wcsnicmp(
    __in_ecount( count ) const DRM_WCHAR    *first,
    __in_ecount( count ) const DRM_WCHAR    *last,
    __in                       DRM_SIZE_T    count );

DRM_API DRM_LONG DRM_CALL DRMCRT_wcsicmp(
    __in_z const DRM_WCHAR *first,
    __in_z const DRM_WCHAR *last );

DRM_API DRM_SIZE_T DRM_CALL DRMCRT_wcslen(
    __in_z const DRM_WCHAR *wsz );

DRM_API DRM_SIZE_T DRM_CALL DRMCRT_strlen(
    __in_z const DRM_CHAR *sz );

DRM_API DRM_LONG DRM_CALL DRMCRT_strncmp(
    __in_ecount( count ) const DRM_CHAR   *first,
    __in_ecount( count ) const DRM_CHAR   *last,
    __in                       DRM_SIZE_T  count );

DRM_API DRM_LONG DRM_CALL DRMCRT_abs( DRM_LONG number );

/**********************************************************************
**
** Set of DRM specific functions that complement C run time.
*
***********************************************************************/

DRM_API DRM_RESULT DRM_CALL DRMCRT_AtoDWORD(
    __in_ecount( f_cchStringInput ) const DRM_CHAR  *f_pszStringInput,
    __in                                  DRM_DWORD  f_cchStringInput,
    __in                                  DRM_DWORD  f_base,
    __out                                 DRM_DWORD *f_pdwValue );

DRM_API DRM_RESULT DRM_CALL DRMCRT_WtoDWORD(
    __in_ecount( f_cchStringInput ) const DRM_WCHAR *pwszStringInput,
    __in                                  DRM_DWORD  f_cchStringInput,
    __in                                  DRM_DWORD  f_base,
    __out                                 DRM_DWORD *f_pdwValue,
    __out_opt                             DRM_DWORD *f_pcchValue );

DRM_API DRM_RESULT DRM_CALL DRMCRT_strntol(
    __in_ecount( cchStringInput ) const DRM_CHAR *pszStringInput,
    __in                                DRM_DWORD  cchStringInput,
    __out                               DRM_LONG  *plValue );

DRM_API DRM_RESULT DRM_CALL DRMCRT_wcsntol(
    __in_ecount( cchStringInput ) const DRM_WCHAR *pwszStringInput,
    __in                                DRM_DWORD  cchStringInput,
    __out                               DRM_LONG  *plValue );


DRM_API DRM_CHAR* DRM_CALL DRMCRT_strnstr(
   __in_ecount( cchMaxStr )       const DRM_CHAR  *pszStr,
   __in                                 DRM_DWORD  cchMaxStr,
   __in_ecount( cchMaxStrSearch ) const DRM_CHAR  *pszStrSearch,
   __in                                 DRM_DWORD  cchMaxStrSearch );

DRM_API DRM_WCHAR* DRM_CALL DRMCRT_wcsnstr(
   __in_ecount( cchMaxStr )       const DRM_WCHAR *pwszStr,
   __in                                 DRM_DWORD  cchMaxStr,
   __in_ecount( cchMaxStrSearch ) const DRM_WCHAR *pwszStrSearch,
   __in                                 DRM_DWORD  cchMaxStrSearch );

EXIT_PK_NAMESPACE;

#if !defined( min )
    #define min( a, b ) ( (a) < (b) ? (a) : (b) )
#endif

#if !defined( max )
    #define max( a, b ) ( (a) < (b) ? (b) : (a) )
#endif

#endif /* __DRMCRT_H__ */
