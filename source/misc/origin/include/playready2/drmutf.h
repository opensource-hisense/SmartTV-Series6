/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRM_UTF_H
#define __DRM_UTF_H

#include <drmtypes.h>
#include <oemparsers.h>

ENTER_PK_NAMESPACE;

/* Test for little endian UTF-16 BOM (byte order mask) */
#define IS_LITTLE_ENDIAN_UTF16_BOM(_pbData_) ( GET_BYTE( _pbData_, 0 ) == 0xFFUL && GET_BYTE( _pbData_, 1 ) == 0xFEUL )

/* Test for big endian UTF-16 BOM (byte order mask) */
#define IS_BIG_ENDIAN_UTF16_BOM(_pbData_) ( GET_BYTE( _pbData_, 0 ) == 0xFEUL && GET_BYTE( _pbData_, 1 ) == 0xFFUL )

DRM_API DRM_RESULT DRM_CALL DRM_STR_UTF32toUTF16(
    __in_ecount( f_cchSource )          const DRM_WCHAR32 *f_pw32szSource,
    __in                                const DRM_DWORD    f_cchSource,
    __out_ecount_z_opt( *f_pcchTarget )       DRM_WCHAR   *f_pwszTarget,
    __inout                                   DRM_DWORD   *f_pcchTarget );

DRM_API DRM_RESULT DRM_CALL DRM_STR_UTF32toDSTR(
    __in_ecount( f_cchSource ) const DRM_WCHAR32 *f_pw32szSource,
    __in                       const DRM_DWORD    f_cchSource,
    __inout                          DRM_STRING  *f_pdstrTarget );

DRM_API DRM_RESULT DRM_CALL DRM_STR_UTF16toUTF32(
    __in_ecount( f_cchSource )          const DRM_WCHAR   *f_pwszSource,
    __in                                const DRM_DWORD    f_cchSource,
    __out_ecount_z_opt( *f_pcchTarget )       DRM_WCHAR32 *f_pw32szTarget,
    __inout                                   DRM_DWORD   *f_pcchTarget );

DRM_API DRM_RESULT DRM_CALL DRM_STR_DSTRtoUTF32(
    __in                              const DRM_STRING  *f_pdstrSource,
    __out_ecount_opt( *f_pcchTarget )       DRM_WCHAR32 *f_pw32szTarget,
    __inout                                 DRM_DWORD   *f_pcchTarget );

DRM_API DRM_RESULT DRM_CALL DRM_STR_UTF16toUTF8(
    __in_ecount( f_cchSource )          const DRM_WCHAR *f_pwszSource,
    __in                                const DRM_DWORD  f_cchSource,
    __out_ecount_z_opt( *f_pcchTarget )       DRM_CHAR  *f_pchTarget,
    __in                                const DRM_DWORD  f_ichTarget,
    __inout                                   DRM_DWORD *f_pcchTarget );

DRM_API DRM_RESULT DRM_CALL DRM_STR_DSTRtoUTF8_ByWindow(
    __in                                                  const DRM_STRING        *f_pdstrSource,
    __out_ecount_opt( f_pdstrwTarget->m_ichMaxExclusive )       DRM_CHAR          *f_pchTarget,
    __inout                                                     DRM_STRING_WINDOW *f_pdstrwTarget );

DRM_API DRM_RESULT DRM_CALL DRM_STR_DSTRtoUTF8(
    __in                              const DRM_STRING *f_pdstrSource,
    __out_ecount_opt( *f_pcchTarget )       DRM_CHAR   *f_pchTarget,
    __inout                                 DRM_DWORD  *f_pcchTarget );

DRM_API DRM_RESULT DRM_CALL DRM_STR_UTF8toUTF16(
    __in_ecount( f_ichSource + f_cchSource ) const DRM_CHAR  *f_pchSource,
    __in                                     const DRM_DWORD  f_ichSource,
    __in                                     const DRM_DWORD  f_cchSource,
    __out_ecount_z_opt( *f_pcchTarget )            DRM_WCHAR *f_pchTarget,
    __inout                                        DRM_DWORD *f_pcchTarget );

DRM_API DRM_RESULT DRM_CALL DRM_STR_UTF8toDSTR_ByWindow(
    __in_ecount( f_pdstrwSource->m_ichMaxExclusive ) const DRM_CHAR          *f_pchSource,
    __in                                             const DRM_STRING_WINDOW *f_pdstrwSource,
    __inout                                                DRM_STRING        *f_pdstrTarget );

DRM_API DRM_RESULT DRM_CALL DRM_STR_UTF8toDSTR(
    __in_ecount( f_cchSource ) const DRM_CHAR   *f_pchSource,
    __in                       const DRM_DWORD   f_cchSource,
    __inout                          DRM_STRING *f_pdstrTarget );

DRM_API DRM_RESULT DRM_CALL DRM_STR_ASCII_SUBSTRtoDSTR(
    __in_ecount( f_pdasstr->m_ich + f_pdasstr->m_cch ) const DRM_CHAR      *f_pchSource,
    __in                                               const DRM_SUBSTRING *f_pdasstr,
    __inout                                                  DRM_STRING    *f_pdstrTarget );

DRM_API DRM_RESULT DRM_CALL DRM_STR_ASCIItoDSTR(
    __in_ecount( f_cchSource ) const DRM_CHAR   *f_pchSource,
    __in                       const DRM_DWORD   f_cchSource,
    __inout                          DRM_STRING *f_pdstrTarget );

DRM_API DRM_RESULT DRM_CALL DRM_STR_UTF16toASCII(
    __in_ecount(f_cchSource)    const DRM_WCHAR *f_pwszSource,
    __in                        const DRM_DWORD  f_cchSource,
    __inout_ecount(f_cchTarget)       DRM_CHAR  *f_pszTarget,
    __in                        const DRM_DWORD  f_cchTarget );

EXIT_PK_NAMESPACE;

#endif /* __DRM_UTF_H */

