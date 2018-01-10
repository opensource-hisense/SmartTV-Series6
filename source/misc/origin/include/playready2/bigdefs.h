/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef BIGDEFS_H              /* If not previously #included */
#define BIGDEFS_H 1

/*
**       File bigdefs.h     Version 10 February 2004
**
**       This file declared the fundamental types and constants used
**       within the bignum code.
**
**           digit_t
**           sdigit_t
**
**        used within the bignum code and headers.
**        We also declare the most fundamental routines for operating on these.
**
**        If you need to perform arithmetic, not just copy data, see bignum.h .
*/

#include <drmerr.h>
#include <oemcommonmem.h>
#include <drmbytemanip.h>

ENTER_PK_NAMESPACE;

/*
      Occasionally a struct name is used before the struct itself is
      declared.  The Future_Struct macro avoids a warning message
      with Visual C .NET (2002).
*/
#define Future_Struct(strname) struct strname

#define MP_SIGNIFICANT_BIT_COUNT_DRMBIGNUM_IMPL() do {                  \
        DRM_DWORD lng_sig = 0;                                          \
        lng_sig = significant_digit_count( a, lnga );                   \
        if( lng_sig == 0 )                                              \
        {                                                               \
            return 0;                                                   \
        }                                                               \
        else                                                            \
        {                                                               \
           return    ( (lng_sig - 1) * RADIX_BITS )                     \
                   + significant_bit_count(a[lng_sig-1]);               \
        }                                                               \
    } while( FALSE )


#define SIGNIFICANT_BIT_COUNT_DRMBIGNUM_IMPL() do {                                                 \
        digit_t dadj = d | 1;                                                                       \
        DRM_DWORD width = RADIX_BITS;                                                               \
        DRM_DWORD width_adj;                                                                        \
        while( dadj < ( DIGIT_ONE << ( RADIX_BITS - 5 ) ) )                                         \
        {                                                                                           \
            width -= 5;                                                                             \
            dadj <<= 5;                                                                             \
        }                                                                                           \
        dadj >>= ( RADIX_BITS - 4 );     /* From 0 to 15 */                                         \
        width_adj = ((DRM_DWORD)0000000011112234 >> dadj) >> (2*dadj);                              \
                         /* Shift by 3*dadj, to index into array of octal digits */                 \
        return width - (width_adj & 7);   /* Subtract 5 - significant_bit_count(2*dadj + 1) */      \
    } while( FALSE )


#define MP_EXTEND_DRMBIGNUM_IMPL() do {                                                             \
        if( lngb >= lnga )                                                                          \
        {                                                                                           \
            OEM_SECURE_DIGITTCPY( b, a, ( lnga ) );                                                 \
            OEM_SECURE_ZERO_MEMORY( b + lnga, ( lngb - lnga ) * SIZEOF( digit_t ) );                \
        }                                                                                           \
        else                                                                                        \
        {                                                                                           \
            OEM_SECURE_DIGITTCPY( b, a, ( lngb ) );                                                 \
        }                                                                                           \
    } while( FALSE )


#define MP_GETBIT_DRMBIGNUM_IMPL() do {                                                             \
        return digit_getbit( a[ibit/RADIX_BITS], ibit % RADIX_BITS );                               \
    } while( FALSE )

#define MP_SETBIT_DRMBIGNUM_IMPL() do {                                                             \
        const DRM_DWORD j       = ibit / RADIX_BITS;                                                \
        const DRM_DWORD ishift  = ibit % RADIX_BITS;                                                \
        const digit_t mask1 = (DIGIT_ONE &  new_value) << ishift;                                   \
        const digit_t mask2 = (DIGIT_ONE & ~new_value) << ishift;                                   \
        if( j < lnga )                                                                              \
        {                                                                                           \
            a[j] = (a[j] & ~mask2) | mask1;                                                         \
        }                                                                                           \
    } while( FALSE )


#define SIGNIFICANT_DIGIT_COUNT_DRMBIGNUM_IMPL() do {       \
        DRM_DWORD i = lng;                                  \
        while( i != 0 && a[i-1] == 0 ) i--;                 \
        return i;                                           \
    } while( FALSE )


#if DWORDS_PER_DIGIT == 1
#define DIGITS_TO_DWORDS_DRMBIGNUM_IMPL() do { OEM_SECURE_DIGITTCPY( pbyte, pdigit, lng_dwords ); return TRUE; } while( FALSE )
#define DWORDS_TO_DIGITS_DRMBIGNUM_IMPL() do { OEM_SECURE_DIGITTCPY( pdigit, (digit_t*)pdword, lng_dwords ); return TRUE; } while( FALSE )
#elif DWORDS_PER_DIGIT == 2
#define DIGITS_TO_DWORDS_DRMBIGNUM_IMPL() do {                                                      \
        const DRM_DWORD lng_half = lng_dwords >> 1;                                                 \
        DRM_DWORD i;                                                                                \
                                                                                                    \
        if (IS_ODD(lng_dwords))                                                                     \
        {                                                                                           \
            OEM_SECURE_DIGITTCPY(pbyte+(lng_dwords-1)*SIZEOF(DRM_DWORD), pdigit[lng_half], 1);      \
        }                                                                                           \
        for (i = 0; i != lng_half; i++)                                                             \
        {                                                                                           \
            const digit_t dig = pdigit[i];                                                          \
            DRM_DWORD dwTmp = (DRM_DWORD)(dig >> DWORD_BITS);                                       \
                                                                                                    \
            OEM_SECURE_DIGITTCPY(pbyte+2*i*SIZEOF(DRM_DWORD), &dig, 1);                             \
            OEM_SECURE_DIGITTCPY(pbyte+(2*i+1)*SIZEOF(DRM_DWORD), &dwTmp, 1);                       \
        }                                                                                           \
        return TRUE;                                                                                \
    } while( FALSE )


#define DWORDS_TO_DIGITS_DRMBIGNUM_IMPL() do {                                                      \
        const DRM_DWORD lng_half = lng_dwords >> 1;                                                 \
        DRM_DWORD i;                                                                                \
                                                                                                    \
        if (IS_ODD(lng_dwords))                                                                     \
        {                                                                                           \
            pdigit[lng_half] = (digit_t)pdword[lng_dwords - 1];  /* Zero fill */                    \
        }                                                                                           \
        for (i = 0; i != lng_half; i++)                                                             \
        {                                                                                           \
            pdigit[i] =    ((digit_t)pdword[2*i+1] << DWORD_BITS)                                   \
                         |  (digit_t)pdword[2*i];                                                   \
        }                                                                                           \
        return TRUE;                                                                                \
    } while( FALSE )


#else /* DWORDS_PER_DIGIT */
#error "Unexpected DWORDS_PER_DIGIT"
#endif /* DWORDS_PER_DIGIT */


#if !DRM_INLINING_SUPPORTED

DRM_API DRM_DWORD DRM_CALL significant_bit_count( const digit_t d );

DRM_API DRM_DWORD DRM_CALL mp_significant_bit_count( const digit_t a[], const DRM_DWORD lnga );

DRM_API DRM_BOOL DRM_CALL digits_to_dwords(
    __in_ecount(lng_dwords)                                      const digit_t   pdigit[],
    __inout_ecount_full(lng_dwords*SIZEOF( digit_t )/DWORDS_PER_DIGIT) DRM_BYTE  pbyte[],
    __in                                                         const DRM_DWORD lng_dwords );

DRM_API DRM_BOOL DRM_CALL dwords_to_digits(
                               const DRM_DWORD   pdword[],
    __inout_ecount(lng_dwords)       digit_t     pdigit[],
                               const DRM_DWORD   lng_dwords );

DRM_API DRM_VOID DRM_CALL mp_extend(
    __in_ecount(lnga)    const digit_t   a[],
                         const DRM_DWORD lnga,
    __inout_ecount(lngb)       digit_t   b[],
                         const DRM_DWORD lngb );

DRM_API digit_t DRM_CALL mp_getbit( const digit_t a[], const DRM_DWORD ibit );

DRM_API DRM_VOID DRM_CALL mp_setbit(
    __inout_ecount(lnga)       digit_t      a[],
                         const DRM_DWORD    lnga,
                         const DRM_DWORD    ibit,
                         const digit_t      new_value );

DRM_API DRM_DWORD DRM_CALL significant_digit_count(
    __in_ecount(lng) const digit_t   a[],
    __in             const DRM_DWORD lng );

#else  /* !DRM_INLINING_SUPPORTED */

static DRMFORCEINLINE DRM_VOID DRM_CALL mp_extend(
    __in_ecount(lnga)    const digit_t   a[],
                         const DRM_DWORD lnga,
    __inout_ecount(lngb)       digit_t   b[],
                         const DRM_DWORD lngb )
/*
        Copy a to b, while changing its length from
        lnga to lngb (zero fill).  Require lngb >= lnga.
*/
{
    MP_EXTEND_DRMBIGNUM_IMPL();
}  /* mp_extend */
/****************************************************************************/
static DRMFORCEINLINE digit_t DRM_CALL mp_getbit( const digit_t a[], const DRM_DWORD ibit )
                /* Extract bit of multiple precision number */
{
    MP_GETBIT_DRMBIGNUM_IMPL();
}
/****************************************************************************/
static DRMFORCEINLINE DRM_VOID DRM_CALL mp_setbit(
    __inout_ecount(lnga)       digit_t      a[],
                         const DRM_DWORD    lnga,
                         const DRM_DWORD    ibit,
                         const digit_t      new_value )
/*
        Set a bit to 0 or 1,
        when the number is viewed as a bit array.
*/
{
    MP_SETBIT_DRMBIGNUM_IMPL();
} /* end mp_setbit */
/****************************************************************************/
static DRMFORCEINLINE DRM_DWORD DRM_CALL significant_digit_count(
    __in_ecount(lng) const digit_t   a[],
    __in             const DRM_DWORD lng )
/*
        Return the number of significant digits in a.
        Function value is zero precisely when a == 0.
*/
{
    SIGNIFICANT_DIGIT_COUNT_DRMBIGNUM_IMPL();
}  /* significant_digit_count */
/****************************************************************************/
PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_COUNT_REQUIRED_FOR_WRITABLE_BUFFER, "pbyte length defined by lng_dwords")
static DRMFORCEINLINE DRM_BOOL DRM_CALL digits_to_dwords(
    __in_ecount(lng_dwords)                                      const digit_t   pdigit[],
    __inout_ecount_full(lng_dwords*SIZEOF( digit_t )/DWORDS_PER_DIGIT) DRM_BYTE  pbyte[],
    __in                                                         const DRM_DWORD lng_dwords )
{
    DIGITS_TO_DWORDS_DRMBIGNUM_IMPL();
}  /* digits_to_dwords */
PREFAST_POP
/****************************************************************************/
static DRMFORCEINLINE DRM_BOOL DRM_CALL dwords_to_digits(
                               const DRM_DWORD   pdword[],
    __inout_ecount(lng_dwords)       digit_t     pdigit[],
                               const DRM_DWORD   lng_dwords )
{
    DWORDS_TO_DIGITS_DRMBIGNUM_IMPL();
}  /* dwords_to_digits */

#undef significant_bit_count    /* In case a macro version existed */
static DRMFORCEINLINE DRM_DWORD DRM_CALL significant_bit_count (const digit_t d )
/*
        Compute the number of significant bits in d.
        This is one more than the truncated base 2 logarithm of d.
        significant_bit_count(0)  is undefined.

        For example, significant_bit_count(d) = 8 for 128 <= d <= 255.

        On platforms which have a Count Leading Zeroes or
        similar instruction, UNIFORM_SIGNIFICANT_BIT_COUNT
        should be 1, with special code used.
        For other platforms, use this algorithm.
        The algorithm performs best when the argument is large,
        a feature used by the GCD routines.
*/
{
    SIGNIFICANT_BIT_COUNT_DRMBIGNUM_IMPL();
} /* significant_bit_count */

static DRMFORCEINLINE DRM_DWORD DRM_CALL mp_significant_bit_count( const digit_t a[], const DRM_DWORD lnga )
/*
        Return the number of significant bits in a, which
        is one more than the truncated base 2 logarithm of a.
        Return 0 if a == 0.
*/
{
    MP_SIGNIFICANT_BIT_COUNT_DRMBIGNUM_IMPL();
}


/****************************************************************************/
#endif /* !DRM_INLINING_SUPPORTED */

/*
        The application should define the
        following three malloc-like functions.
        Sample definitions appear in bigalloc.h.
*/

DRM_API DRM_VOID* DRM_CALL bignum_alloc(__in const DRM_DWORD cblen, __in struct bigctx_t *f_pBigCtx);
DRM_API DRM_VOID  DRM_CALL bignum_free(DRM_VOID *pvMem, struct bigctx_t *f_pBigCtx);
DRM_API DRM_VOID* DRM_CALL bignum_alloc_align(__in const DRM_DWORD cblen,
                                              __in const DRM_DWORD cbAlign,
                                              __in struct bigctx_t *f_pBigCtx,
                                              __out DRM_VOID **ppbBufferRaw);

EXIT_PK_NAMESPACE;

#endif /* BIGDEFS_H */

