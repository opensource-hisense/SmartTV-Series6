/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/
#ifndef __BIGPRIV_H
#define __BIGPRIV_H 1
/*
      File bigpriv.h.   Version 20 September, 2002

      Declarations accessible to bignum library but invisible to application.
      Also see fieldpriv.h
*/

#include "bignum.h"


ENTER_PK_NAMESPACE;

#if defined (DRM_MSC_VER)

    #pragma warning(disable: 4146 4514)  // TBD
         /* 4146 -- unary minus operator applied
            to unsigned type, result still unsigned.
            4514 -- unreferenced inline function
          */
#endif



/*
     Some routines allow the caller to supply temps, but
     accept a NULL argument to say "Allocate them yourself!".
     possible_digit_allocate assists in doing the allocate
     if the caller passed NULL.
*/

typedef struct digit_tempinfo_t {
    digit_t *address;       // Address supplied by user.
                            // Updated to specify address
                            // to use for temporaries.
    DRM_DWORD nelmt;         // Number of digit_t elements needed
    DRM_BOOL  need_to_free;  // Should be set FALSE by application.
                            // Changed to TRUE if a free is required.
} digit_tempinfo_t;

DRM_API DRM_BOOL DRM_CALL possible_digit_allocate(
    digit_tempinfo_t *tempinfo,
    struct bigctx_t  *f_pBigCtx);

DRM_API DRM_BOOL DRM_CALL modmul_choices1(mp_modulus_t*, DRM_LONG*);

DRM_API DRM_BOOL DRM_CALL modmul_from_right_default(
    __in      const digit_t      *a,
    __in      const digit_t      *b,
    __out           digit_t      *c,
    __in      const mp_modulus_t *pmodulo,
    __inout         digit_t      *temps );

DRM_API DRM_BOOL DRM_CALL modmul_from_right_default_modulo8(
    __in     const digit_t      *a,
    __in     const digit_t      *b,
    __out          digit_t      *c,
    __in     const mp_modulus_t *pmodulo,
    __inout        digit_t      *temps );

EXIT_PK_NAMESPACE;


#endif  //  __BIGPRIV_H
