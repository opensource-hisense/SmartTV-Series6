/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRMSTRSAFE_H__
#define __DRMSTRSAFE_H__

#include <drmtypes.h>

#ifdef __cplusplus
extern "C"
{
#endif

ENTER_PK_NAMESPACE;

#define DRM_STRSAFE_MAX_CCH 2147483647


#define DRM_MAX_CCH_BASE2_DWORD_STRING      32
#define DRM_MAX_CCH_BASE2_WORD_STRING       16
#define DRM_MAX_CCH_BASE2_BYTE_STRING       8

#define DRM_MAX_CCH_BASE10_DWORD_STRING     10
#define DRM_MAX_CCH_BASE10_WORD_STRING      5
#define DRM_MAX_CCH_BASE10_BYTE_STRING      3

#define DRM_MAX_CCH_BASE16_DWORD_STRING     8
#define DRM_MAX_CCH_BASE16_WORD_STRING      4
#define DRM_MAX_CCH_BASE16_BYTE_STRING      2


DRM_API DRM_RESULT DRM_CALL DRM_STR_StringCchLengthW(
    __in_z const DRM_WCHAR *f_pwsz,
    __in         DRM_DWORD  f_cchMax,
    __out_opt    DRM_DWORD *f_pcchLength );

DRM_API DRM_RESULT DRM_CALL DRM_STR_StringCchLengthA(
    __in_z              const DRM_CHAR  *f_psz,
    __in                      DRM_DWORD  f_cchMax,
    __out_opt                 DRM_DWORD *f_pcchLength);


DRM_API DRM_RESULT DRM_CALL DRM_STR_StringCchCopyNW(
    __out_ecount_z(f_cchDest)     DRM_WCHAR  *f_pwszDest,
    __in                          DRM_DWORD   f_cchDest,
    __in_ecount( f_cchSrc ) const DRM_WCHAR  *f_pwszSrc,
    __in                          DRM_DWORD   f_cchSrc );

DRM_API DRM_RESULT DRM_CALL DRM_STR_StringCchCopyNA(
    __out_ecount_z(f_cchDest)      DRM_CHAR  *f_pszDest,
    __in                           DRM_DWORD  f_cchDest,
    __in_ecount(f_cchToCopy) const DRM_CHAR  *f_pszSrc,
    __in                           DRM_DWORD  f_cchToCopy);

DRM_API DRM_RESULT DRM_CALL DRM_STR_StringCchCopyW(
    __out_ecount_z(f_cchDest) DRM_WCHAR  *f_pwszDest,
    __in                      DRM_DWORD   f_cchDest,
    __in_z              const DRM_WCHAR  *f_pwszSrc );

DRM_API DRM_RESULT DRM_CALL DRM_STR_StringCchCopyA(
    __out_ecount_z(f_cchDest) DRM_CHAR *f_pszDest,
    __in                      DRM_DWORD f_cchDest,
    __in_z              const DRM_CHAR *f_pszSrc);

DRM_API DRM_RESULT DRM_CALL DRM_STR_StringCchCatW
(   __out_ecount_z(f_cchDest) DRM_WCHAR *f_pwszDest,
    __in                      DRM_DWORD  f_cchDest,
    __in_z              const DRM_WCHAR *pwszSrc );

DRM_API DRM_RESULT DRM_CALL DRM_STR_StringCchCatA
(   __out_ecount_z(f_cchDest) DRM_CHAR  *f_pszDest,
    __in                      DRM_DWORD  f_cchDest,
    __in_z              const DRM_CHAR *pszSrc );

DRM_API DRM_RESULT DRM_CALL DRM_STR_StringCchCatNW
(   __out_ecount_z(f_cchDest)        DRM_WCHAR *f_pwszDest,
    __in                             DRM_DWORD  f_cchDest,
    __in_ecount(f_cchToAppend) const DRM_WCHAR *f_pwszSrc,
    __in                             DRM_DWORD  f_cchToAppend );

DRM_API DRM_RESULT DRM_CALL DRM_STR_StringCchCatNA
(   __out_ecount_z(f_cchDest)        DRM_CHAR     *f_pszDest,
    __in                             DRM_DWORD     f_cchDest,
    __in_ecount(f_cchToAppend) const DRM_CHAR     *f_pszSrc,
    __in                             DRM_DWORD     f_cchToAppend );

DRM_API DRM_RESULT DRM_CALL DRM_STR_StringCchPrintfW_1
(   __out_ecount_z(f_cchDest) DRM_WCHAR       *f_pwszDest,
    __in                      DRM_DWORD        f_cchDest,
    __in __format_string      DRM_WCHAR const *f_pwszFormat,
    __in                      DRM_DWORD        f_dwValue );

DRM_API DRM_RESULT DRM_CALL DRM_STR_StringCchPrintfExW_1
(   __out_ecount_z(f_cchDest)                DRM_WCHAR *f_pwszDest,
    __in                                     DRM_DWORD  f_cchDest,
    __deref_opt_out_ecount(*f_pcchRemaining) DRM_WCHAR**f_ppwszDestEnd,
    __out_opt                                DRM_DWORD *f_pcchRemaining,
    __in                                     DRM_DWORD  f_dwFlags,
    __in_z __format_string             const DRM_WCHAR *f_pwszFormat,
    __in                                     DRM_DWORD  f_dwValue );

DRM_API DRM_RESULT DRM_CALL DRM_STR_DstrCat(
    __inout    DRM_STRING       *f_pdstrTarget,
    __in const DRM_CONST_STRING *f_pdstrAdd,
    __in const DRM_DWORD         f_cchTargetMax );

DRM_API DRM_RESULT DRM_CALL DRM_STR_StringCchToLower(
    __inout_ecount_nz(f_cchToLower) DRM_WCHAR *f_prgwchToLower,
    __in                            DRM_DWORD  f_cchToLower );

DRM_API DRM_RESULT DRM_CALL DRM_STR_DstrToLower(
    __inout    DRM_STRING       *f_pdstrToLower );

EXIT_PK_NAMESPACE;

#ifdef __cplusplus
}
#endif


#endif /* __DRMSTRSAFE_H__ */

