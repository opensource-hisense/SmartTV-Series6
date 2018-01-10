/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

/*      File mprand.h */

#ifndef _MPRAND_H
#define _MPRAND_H

#include "bignum.h"

ENTER_PK_NAMESPACE;

DRM_API DRM_NO_INLINE DRM_BOOL DRM_CALL random_bytes(
    DRM_BYTE* byte_array,
    const DRM_DWORD nbyte,
    struct bigctx_t *f_pBigCtx );
         // Procedure to be supplied by application.


DRM_API DRM_BOOL DRM_CALL random_digits(digit_t dtArray[],
                                      const DRM_DWORD lng,
                                      struct bigctx_t *f_pBigCtx);


// Following are extern on all platforms

DRM_API DRM_NO_INLINE DRM_BOOL DRM_CALL random_digit_interval
        (const digit_t  dlow,
         const digit_t  dhigh,
         digit_t  *pdout,
         struct bigctx_t *f_pBigCtx);
          /* Generate random digit_t or DRM_DWORD in specified closed interval. */

DRM_API DRM_BOOL DRM_CALL random_mod        (const digit_t *, digit_t *,
                                          const DRM_DWORD, struct bigctx_t *f_pBigCtx);

/*
** Checked stublib expects the function name to be new_random_mod_nonzero
** Temporary fix.
*/
#define random_mod_nonzero new_random_mod_nonzero
DRM_API DRM_BOOL DRM_CALL random_mod_nonzero(const digit_t *, digit_t *,
                                          const DRM_DWORD, struct bigctx_t *f_pBigCtx);
                        // Generate random value modulo another value.
                        // random_mod_nonzero generates a nonzero value.

EXIT_PK_NAMESPACE;

#endif   // _MPRAND_H
