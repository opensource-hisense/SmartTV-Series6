/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef DBLINT_H
#define DBLINT_H 1

#include <drmtypes.h>

#if defined(_M_IX86) || defined(_M_AMD64)

#ifdef __cplusplus
extern "C"
#endif
unsigned __int64 __emulu(
   unsigned int a,
   unsigned int b
);

#pragma intrinsic(__emulu)

#endif

ENTER_PK_NAMESPACE;

/*
        File: dblint.h.  Supplement to bignum.h.  Version 10 December, 2002.

        This file has declarations related to double-precision integers,
        such as typedefs, constants, and primitive operations.

        The DRM_UINT64 type is unsigned and holds twice as many bits
        as a digit_t datum.  If (DRM_SUPPORT_NATIVE_64BIT_TYPES = 1), then use the type
        already in the language.  Otherwise (DRM_SUPPORT_NATIVE_64BIT_TYPES = 0)
        construct one of our own, using a struct with two digit_t fields.

        Let u, u1, u2 have type digit_t and
        d, d1, d2 have type DRM_UINT64.
        The following primitives are defined,
        whether we use the built-in type or our own type:

                DPRODUU(u1, u2) -- Product of u1 and u2, as a DRM_UINT64.
                HPRODUU(u1, u2) -- Most significant half of product
                                   of u1 and u2, as a digit_t.
*/

#if DRM_SUPPORT_NATIVE_64BIT_TYPES

#if defined (DRM_MSC_VER)
#if DRM_INLINING_SUPPORTED

/*
    Note: it seems that for Arm platform this should be moved to just (DWORD)u1*(DWORD)u2.
            DRM_UI64(u1) * DRM_UI64(u2) on x86&x64 produces a [slow]  __allmul call.
            which can be very miserable for mod_exp and other functions which use lots of this.
*/
static DRMFORCEINLINE DRM_UINT64 DRM_CALL DPRODUU(const digit_t u1, const digit_t u2)
{
#if defined(_M_IX86) || defined(_M_AMD64)
    return __emulu(u1, u2);
#else
    return DRM_UI64(u1) * DRM_UI64(u2);
#endif

}
#else /* DRM_INLINING_SUPPORTED */
#define DPRODUU(u1, u2) (DRM_UI64(u1) * DRM_UI64(u2))
#endif /* DRM_INLINING_SUPPORTED */

#else /* DRM_MSC_VER */

#define DPRODUU(u1, u2) (DRM_UI64(u1) * DRM_UI64(u2))

#endif /* DRM_MSC_VER */

#define MULTIPLY_ADD1(d1, d2, d3) \
        DRM_UI64Add(DPRODUU(d1, d2), DRM_UI64(d3))
           /* d1*d2 + d3 */

#define MULTIPLY_ADD2(d1, d2, d3, d4) \
        DRM_UI64Add(DRM_UI64Add(DPRODUU(d1, d2), DRM_UI64(d3)), \
                   DRM_UI64(d4))
          /* d1*d2 + d3 + d4 */

#define HPRODUU(u1, u2) DRM_UI64High32(DRM_UI64Mul(DRM_UI64((u1)), DRM_UI64((u2))))

#else  /* DRM_SUPPORT_NATIVE_64BIT_TYPES */

/* No native support for 64-bit types */

#if defined( _M_AMD64_ )
    #pragma intrinsic(__umulh)
    #define HPRODUU(u1, u2) __umulh(u1, u2)
#else
    #define HPRODUU(u1, u2) DRM_UI64High32(DRM_UI64Mul(DRM_UI64((u1)), DRM_UI64((u2))))
#endif

#if !DRM_INLINING_SUPPORTED

DRM_API DRM_UINT64 DRM_CALL DPRODUU(const digit_t, const digit_t);
DRM_API DRM_UINT64 DRM_CALL MULTIPLY_ADD1(const digit_t, const digit_t, const digit_t);
DRM_API DRM_UINT64 DRM_CALL MULTIPLY_ADD2(const digit_t, const digit_t,
                                            const digit_t, const digit_t);


#else /* !DRM_INLINING_SUPPORTED */

DRMINLINE DRM_UINT64 DRM_CALL DPRODUU(const digit_t u1, const digit_t u2)
/*
        Multiply two single-precision operands,
        return double precision product.
        This will normally be replaced by an assembly language routine.
        unless the top half of the product (HPRODUU) is available in C.
*/
{
    return DRM_UI64Mul( DRM_UI64( u1 ), DRM_UI64( u2 ) );
}   /* end DPRODUU */



/*
    The MULTIPLY_ADD1. MULTIPLY_ADD2
    functions take single-length (digit_t) operands and
    return double-length (DRM_UINT64) results.
    Overflow is impossible.
*/


DRMINLINE DRM_UINT64 DRM_CALL MULTIPLY_ADD1(const digit_t d1, const digit_t d2,
                                                 const digit_t d3)
{
    return DRM_UI64Add( DRM_UI64Mul( DRM_UI64(d1), DRM_UI64(d2) ), DRM_UI64(d3) );
} /* MULTIPLY_ADD1 */


DRMINLINE DRM_UINT64 DRM_CALL MULTIPLY_ADD2(const digit_t d1, const digit_t d2,
                                                 const digit_t d3, const digit_t d4)
{
    return DRM_UI64Add( DRM_UI64Add( DRM_UI64Mul( DRM_UI64(d1), DRM_UI64(d2) ), DRM_UI64(d3) ), DRM_UI64(d4) );
} /* MULTIPLY_ADD2 */

#endif /* !DRM_INLINING_SUPPORTED */

#endif /* DRM_SUPPORT_NATIVE_64BIT_TYPES */

EXIT_PK_NAMESPACE;

#endif /* DBLINT_H */

