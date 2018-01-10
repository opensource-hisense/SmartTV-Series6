/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/
#ifndef BIGDECLS_H
#define BIGDECLS_H 1

ENTER_PK_NAMESPACE;

/*
** The assembly versions of these calls were hardcoded to use stdcall calling
** DRM_API    convention. For the C implementation we will use DRM_CALL as it is standard
** throughout the porting kits.
*/
#if defined(_M_IX86) && DRM_SUPPORT_ASSEMBLY

extern DRM_BOOL __stdcall mp_mul22s(const digit_t[4], digit_t *, digit_t *,
                             const DRM_DWORD, sdigit_t[2]);

extern DRM_BOOL __stdcall mp_mul22u(const digit_t[4], digit_t *, digit_t *,
                             const DRM_DWORD,  digit_t[2] );

extern DRM_VOID __stdcall multiply_low(const digit_t *, const digit_t *, digit_t *, const DRM_DWORD );

#else

DRM_API DRM_BOOL DRM_CALL mp_mul22s(
 __in_ecount(4)        const digit_t mat[4],       /* IN  (2 x 2 matrix of scalars) */
 __inout_ecount(lvec)  digit_t  vec1[],            /* INOUT */
 __inout_ecount(lvec)  digit_t  vec2[],            /* INOUT */
 __in                  const DRM_DWORD lvec,       /* IN */
 __out_ecount(2)       sdigit_t carrys[2] );        /* OUT  (array of 2 scalars) */

DRM_API DRM_BOOL DRM_CALL mp_mul22u(
   __in_ecount(4)       const digit_t mat[4],       /* IN  (2 x 2 matrix of scalars) */
   __inout_ecount(lvec) digit_t  vec1[],            /* INOUT */
   __inout_ecount(lvec) digit_t  vec2[],            /* INOUT */
   __in const           DRM_DWORD lvec,             /* IN */
   __out_ecount(2)      digit_t  carrys[2] );      /* OUT  (array of 2 scalars) */

DRM_API DRM_VOID DRM_CALL multiply_low(const digit_t *, const digit_t *, digit_t *, const DRM_DWORD );

#endif

EXIT_PK_NAMESPACE;

#endif /* BIGDECLS_H */