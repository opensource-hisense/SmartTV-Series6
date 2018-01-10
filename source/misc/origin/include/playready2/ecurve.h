/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/
#ifndef ECURVE_H
#define ECURVE_H 1
#include <bignum.h>
#include <field.h>
#include <bigpriv.h>

ENTER_PK_NAMESPACE;

/*
  
             This file (ecurve.h) has definitions for
         elliptic curve operations.


             Over a field GF(q), where q > 3 is prime,
         an elliptic curve is all points (x, y) in GF(q) x GF(q)
         satisfying the Weierstrass equation
  
                  y^2 = x^3 + ax + b,          (4a^3 + 27 b^2 != 0)
  
         plus a point at infinity.  The points form an abelian group
         under a well-known addition rule.
  
             Over GF(2^m), the curve is instead
  
                   y^2 + xy = x^3 + ax^2 + b   (b != 0)

         Fields a and b of the struct should have length
         elng = fdesc->elng.
         generator should have length 2*elng or be NULL.
         gorder, the order of generator, should be have length
         elng+1 or be NULL.

         Field deallocate is the address to pass to free
         (unless it is NULL) when the curve becomes inactive.

   Points are usually in affine form, with only x and y.
   When b <> 0,  the point at infinity has x = y = 0.
   When b = 0, the point at infinity has x = 0 and y = 1.
   fdesc.elng digit_t words are used for each of x and y,
   with no gap between them.
*/
Future_Struct(ecurve_t);

typedef DRM_BOOL DRM_CALL ec_exponentiation_t(const digit_t *, const digit_t *, const DRM_DWORD,
                                        digit_t *, const struct ecurve_t*,
                                        struct bigctx_t *f_pBigCtx);


typedef struct ecurve_t {
             const field_desc_t     *fdesc;
             digit_t           *a;
             digit_t           *b;
             digit_t        *generator;  /* Generator of cyclic group */
                                            /* (affine form, x and y) */
             digit_t           *gorder;     /* Order of cyclic group */
             digit_t           *deallocate;
             ec_exponentiation_t *fexpon;   /* Special exponentiation code */
                                            /* Used for Koblitz curves */
             DRM_BOOL               free_field; /* Flag telling ec_free to call */
                                            /* Kfree.  For system use only. */
             DRM_BOOL               biszero;    /* Is b == 0? */
             DRM_DWORD           ndigtemps;  /* Number of digit_t temporaries */
                                            /* needed by EC */
                                            /* addition/subtraction routines: */
                                            /* */
                                            /*     ecaffine_addition */
                                            /*     ecaffine_addition_subtraction */
                                            /*     ecaffine_on_curve */
                                            /*     ecaffine_PPQ */
                                            /*     ecaffine_random */
                                            /* */
                                            /* Includes enough for a */
                                            /* multiplication or inversion */
                                            /* (or Kmuladd, etc.) */
                                            /* in the base field. */
             DRM_DWORD           lnggorder;  /* Number of significant words */
                                            /* in *gorder, if not NULL. */
             reciprocal_1_t     grecip;     /* Reciprocal for gorder */
} ecurve_t;

/*
** This number (MAX_ECTEMPS) was 5, but has been increased to 8
** because we have gone from 160bit to 256 bit encryption
** and this assumes that the minimum size of digit_t/digit_t
** types is a 32 bit type
**
** Maximum number of field temporaries needed
** by any EC addition/subtraction/doubling routine,
** including
**
**     ecaffine_addition,
**     ecaffine_addition_subtraction
**     ecaffine_on_curve
**     ecaffine_PPQ
**     ecaffine_random
*/
#define MAX_ECTEMPS 8

DRM_API DRM_BOOL DRM_CALL ecaffine_addition
      (const digit_t *, const digit_t *, digit_t *,
       const DRM_LONG, const struct ecurve_t*, digit_t *, struct bigctx_t *f_pBigCtx);

DRM_API DRM_BOOL DRM_CALL ecaffine_addition_subtraction
      (const digit_t *, const digit_t *, digit_t *,
       digit_t *, const struct ecurve_t*, digit_t *, struct bigctx_t *f_pBigCtx);

DRM_API DRM_BOOL DRM_CALL ecaffine_exponentiation
          (
              const digit_t    *P0,
              const digit_t     exponent[],
              const DRM_DWORD   lng_exponent,
                    digit_t    *Presult,
              const ecurve_t   *E,
              struct bigctx_t  *f_pBigCtx
           );

DRM_API DRM_BOOL DRM_CALL ecaffine_is_infinite(const digit_t *, const struct ecurve_t*, struct bigctx_t *f_pBigCtx);

DRM_API DRM_BOOL DRM_CALL ecaffine_multiply_pm1
          (const digit_t *, digit_t *, const DRM_LONG, const struct ecurve_t*, struct bigctx_t *f_pBigCtx);

DRM_API DRM_BOOL DRM_CALL ecaffine_negate(const digit_t *, digit_t *,
                                   const struct ecurve_t*, struct bigctx_t *f_pBigCtx);

DRM_API DRM_BOOL DRM_CALL ecaffine_on_curve(const digit_t *, const struct ecurve_t*,
                                     const DRM_CHAR*, digit_t *, struct bigctx_t *f_pBigCtx);

DRM_API DRM_BOOL DRM_CALL ecaffine_PPQ(const digit_t *, const digit_t *,
                                digit_t *, const DRM_LONG,
                                const struct ecurve_t*, digit_t *, struct bigctx_t *f_pBigCtx);

DRM_API DRM_BOOL DRM_CALL ecaffine_random(digit_t *, const struct ecurve_t*,
                                   digit_t *, struct bigctx_t *f_pBigCtx);

DRM_API DRM_BOOL DRM_CALL ecaffine_set_infinite(digit_t *,
                                         const struct ecurve_t*, struct bigctx_t *f_pBigCtx);

DRM_API DRM_BOOL DRM_CALL ec_initialize(const digit_t *, const digit_t *,
                                const field_desc_t*, struct ecurve_t*, struct bigctx_t *f_pBigCtx, struct bigctx_t*);

DRM_API DRM_BOOL DRM_CALL ec_free(struct ecurve_t*, struct bigctx_t *f_pBigCtx);     /* IN/OUT */

DRM_API DRM_EXTERN_INLINE DRM_BOOL DRM_CALL ecaffine_exponentiation_tabular(
                 const digit_t *Pbase_powers,
                 const DRM_DWORD    table_spacing,
                 const DRM_DWORD    table_last,
                 const digit_t     exponent[],
                 const DRM_DWORD    lexpon,
                 digit_t  *result,
                 const ecurve_t   *ecurve,
                 struct bigctx_t *f_pBigCtx);

DRM_API DRM_BOOL DRM_CALL ecaffine_table_construction(
         const digit_t      *p0,
         const DRM_DWORD     table_spacing,
         const DRM_DWORD     table_last,
               digit_t      *table,
         const ecurve_t     *ecurve,
         struct bigctx_t    *f_pBigCtx);

DRM_BOOL DRM_CALL ecaffine_to_ecproj5(const digit_t *, digit_t *,
                                const struct ecurve_t*, digit_t *, struct bigctx_t *f_pBigCtx);

DRM_BOOL DRM_CALL ecproj5_add_ecproj5(const digit_t *, const digit_t *,
                                       digit_t *, const struct ecurve_t*,
                                       digit_t *, struct bigctx_t *f_pBigCtx);

DRM_BOOL DRM_CALL ecproj5_to_ecaffine(const digit_t *, digit_t *,
                                const struct ecurve_t*, digit_t *, struct bigctx_t *f_pBigCtx);

EXIT_PK_NAMESPACE;

#endif /* ECURVE_H */
