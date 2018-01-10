/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __OEMCOMMONMEM_H__
#define __OEMCOMMONMEM_H__

#include <drmtypes.h>

ENTER_PK_NAMESPACE;

#undef OEM_SECURE_ZERO_MEMORY

/* OEM special implementation functions (oemimpl.c). */
#if defined(DRM_MSC_VER) || defined(__GNUC__)

DRMFORCEINLINE DRM_VOID * DRM_CALL DRMCRT_ScrubMemory(
    __out_bcount( f_cbCount ) DRM_VOID  *f_ptr,
    __in DRM_DWORD  f_cbCount  ) ;

#if 0
DRMFORCEINLINE DRM_VOID * DRM_CALL DRMCRT_ScrubMemory(
    __out_bcount( f_cbCount ) DRM_VOID  *f_ptr,
    __in DRM_DWORD  f_cbCount  )
{
    /*
    ** Casting the pointer to volatile makes MS and GNU compilers act
    ** as if another thread can see and access the buffer. This
    ** prevents the compiler from reordering or optimizing away
    ** the writes.
    */

    volatile char *vptr = (volatile char *)f_ptr;

    while (f_cbCount)
    {
        *vptr = 0;
        vptr++;
        f_cbCount--;
    }

    return f_ptr;
}
#endif

#define OEM_SECURE_ZERO_MEMORY DRMCRT_ScrubMemory

#endif /* defined(DRM_MSC_VER) || defined(__GNUC__) */

/*
** OEM_MANDATORY:
** For all devices, this macro MUST be implemented by the OEM.
*/
#ifndef OEM_SECURE_ZERO_MEMORY
#error "Please provide implementation for OEM_SECURE_ZERO_MEMORY macro.\
 OEM_SECURE_ZERO_MEMORY is called to scrub memory on critical pieces of data before freeing buffers or exiting local scope.\
 Using of memset function on these buffers is not sufficient, since compiler\
 may optimize out zeroing of buffers that are not used afterwards.\
 Please verify the implementation will not be optimized out by your compiler.\
 Consult the documentation for your compiler to see how this can be done. \
 The Microsoft supplied example is only guaranteed to work on Microsoft compilers. "

#endif /* ifndef OEM_SECURE_ZERO_MEMORY */

#undef OEM_SECURE_MEMCPY
#undef OEM_SECURE_MEMCPY_IDX
#undef OEM_SECURE_MEMSET
#undef OEM_SECURE_ARE_EQUAL
#undef OEM_SECURE_DWORDCPY
#undef OEM_SECURE_DIGITTCPY

#if defined(DRM_MSC_VER) || defined(__GNUC__)

DRMFORCEINLINE DRM_VOID * DRM_CALL DRMCRT_LocalMemcpy(
    __out_bcount_full( f_cbCount )  DRM_VOID  *f_pOut,
    __in_bcount( f_cbCount ) const  DRM_VOID  *f_pIn,
    __in                            DRM_DWORD  f_cbCount ) DRM_ALWAYS_INLINE_ATTRIBUTE;

#if 0
DRMFORCEINLINE DRM_VOID * DRM_CALL DRMCRT_LocalMemcpy(
    __out_bcount_full( f_cbCount )  DRM_VOID  *f_pOut,
    __in_bcount( f_cbCount ) const  DRM_VOID  *f_pIn,
    __in                            DRM_DWORD  f_cbCount )
{
    /* w/o volatile some compilers can figure out this is an
       implementation of a memcpy */
    volatile const char * pIn = (const char *) f_pIn;
    char * pOut = (char *) f_pOut;
    while (f_cbCount--)
    {
        *pOut++ = *pIn++;
    }
    return f_pOut;
}
#endif

DRMFORCEINLINE DRM_VOID * DRM_CALL DRMCRT_LocalMemset(
    __out_bcount_full( f_cbCount )  DRM_VOID  *f_pOut,
    __in                            DRM_BYTE   f_cbValue,
    __in                            DRM_DWORD  f_cbCount ) DRM_ALWAYS_INLINE_ATTRIBUTE;

#if 0
DRMFORCEINLINE DRM_VOID * DRM_CALL DRMCRT_LocalMemset(
    __out_bcount_full( f_cbCount )  DRM_VOID  *f_pOut,
    __in                            DRM_BYTE   f_cbValue,
    __in                            DRM_DWORD  f_cbCount )
{
    /* w/o volatile some compilers can figure out this is an
       implementation of a memset */
    volatile unsigned char * pOut = (unsigned char *) f_pOut;
    while (f_cbCount--)
    {
        *pOut++ = f_cbValue;
    }
    return f_pOut;
}
#endif

DRMFORCEINLINE DRM_VOID * DRM_CALL DRMCRT_LocalDWORDSetZero(
    __out_bcount_full( f_cdwCount ) DRM_DWORD  *f_pdwOut,
    __in                            DRM_DWORD   f_cdwCount ) DRM_ALWAYS_INLINE_ATTRIBUTE;

#if 0
DRMFORCEINLINE DRM_VOID * DRM_CALL DRMCRT_LocalDWORDSetZero(
    __out_bcount_full( f_cdwCount ) DRM_DWORD  *f_pdwOut,
    __in                            DRM_DWORD   f_cdwCount )
{
    /* w/o volatile some compilers can figure out this is an
       implementation of a memset */
    volatile DRM_DWORD * pdwOut = f_pdwOut;
    while (f_cdwCount--)
    {
        *pdwOut++ = 0;
    }
    return f_pdwOut;
}
#endif

DRMFORCEINLINE DRM_BOOL DRM_CALL DRMCRT_LocalAreEqual(
    __in_bcount( f_cbCount ) const  DRM_VOID  *f_pLHS,
    __in_bcount( f_cbCount ) const  DRM_VOID  *f_pRHS,
    __in                            DRM_DWORD  f_cbCount ) DRM_ALWAYS_INLINE_ATTRIBUTE;

#if 0
DRMFORCEINLINE DRM_BOOL DRM_CALL DRMCRT_LocalAreEqual(
    __in_bcount( f_cbCount ) const  DRM_VOID  *f_pLHS,
    __in_bcount( f_cbCount ) const  DRM_VOID  *f_pRHS,
    __in                            DRM_DWORD  f_cbCount )
{
    /*
    ** Without volatile, some compilers can figure out this is an
    ** implementation of a memcmp-similar function or can
    ** optimize out checks which we don't want.
    */
    volatile DRM_DWORD dwResult = 0;

#if TARGET_SUPPORTS_UNALIGNED_DWORD_POINTERS

    /* Optimize: When unaligned pointers are allowed, compare in DRM_DWORD-sized groups. */
    volatile const DRM_DWORD *pLHS = (const DRM_DWORD*) f_pLHS;
    volatile const DRM_DWORD *pRHS = (const DRM_DWORD*) f_pRHS;

    while( f_cbCount >= SIZEOF(DRM_DWORD) )
    {
        dwResult |= (*pLHS ^ *pRHS);
        pLHS++;
        pRHS++;
        f_cbCount -= SIZEOF(DRM_DWORD);
    }

#else   /* TARGET_SUPPORTS_UNALIGNED_DWORD_POINTERS */

    volatile const DRM_BYTE *pLHS = (const DRM_BYTE*) f_pLHS;
    volatile const DRM_BYTE *pRHS = (const DRM_BYTE*) f_pRHS;

#endif  /* TARGET_SUPPORTS_UNALIGNED_DWORD_POINTERS */

    while( f_cbCount-- )
    {
        volatile const DRM_BYTE bLHS = ((const DRM_BYTE*)pLHS)[f_cbCount];
        volatile const DRM_BYTE bRHS = ((const DRM_BYTE*)pRHS)[f_cbCount];
        dwResult |= (DRM_DWORD)( bLHS ^ bRHS );
    }

    return ( dwResult == 0 );
}
#endif

#if DRM_SUPPORT_INLINEDWORDCPY

DRMFORCEINLINE DRM_VOID * DRM_CALL DRMCRT_LocalDWORDcpy(
    __out_ecount_full( f_cdwCount )  DRM_DWORD  *f_pdwOut,
    __in_ecount( f_cdwCount ) const  DRM_DWORD  *f_pdwIn,
    __in                             DRM_DWORD  f_cdwCount ) DRM_ALWAYS_INLINE_ATTRIBUTE;

#if 0
DRMFORCEINLINE DRM_VOID * DRM_CALL DRMCRT_LocalDWORDcpy(
    __out_ecount_full( f_cdwCount )  DRM_DWORD  *f_pdwOut,
    __in_ecount( f_cdwCount ) const  DRM_DWORD  *f_pdwIn,
    __in                             DRM_DWORD  f_cdwCount )
{
    /* w/o volatile some compilers can figure out this is an
       implementation of a memcpy */
    volatile const DRM_DWORD * pdwIn = (const DRM_DWORD *) f_pdwIn;
    DRM_DWORD * pdwOut = (DRM_DWORD *) f_pdwOut;
    while (f_cdwCount--)
    {
        *pdwOut++ = *pdwIn++;
    }
    return pdwOut;
}
#endif

#define OEM_SECURE_DWORDCPY(out, in, ecount) DRMCRT_LocalDWORDcpy((DRM_DWORD*)(out), (const DRM_DWORD*)(in), (ecount))
#else   /* DRM_SUPPORT_INLINEDWORDCPY */
#define OEM_SECURE_DWORDCPY(out, in, ecount) OEM_SECURE_MEMCPY((out), (in), (ecount)*SIZEOF(DRM_DWORD))
#endif  /* DRM_SUPPORT_INLINEDWORDCPY */

#if DWORDS_PER_DIGIT == 1
#define OEM_SECURE_DIGITTCPY OEM_SECURE_DWORDCPY
#define OEM_SECURE_DIGITZEROMEMORY DRMCRT_LocalDWORDSetZero
#endif  /* DWORDS_PER_DIGIT == 1 */

#define OEM_SECURE_MEMCPY DRMCRT_LocalMemcpy

#define OEM_SECURE_MEMCPY_IDX(dest, dest_offset, source, source_offset, count) OEM_SECURE_MEMCPY((char*)(dest)+(dest_offset), (const char*)(source)+(source_offset), (count))

#define OEM_SECURE_MEMSET DRMCRT_LocalMemset

#define OEM_SECURE_ARE_EQUAL DRMCRT_LocalAreEqual

#endif /* defined(DRM_MSC_VER) || defined(__GNUC__) */

/*
** OEM_MANDATORY:
** For all devices, these macros MUST be implemented by the OEM.
*/
#if !defined(OEM_SECURE_MEMCPY) || !defined(OEM_SECURE_MEMCPY_IDX) || !defined(OEM_SECURE_DWORDCPY) || !defined(OEM_SECURE_DIGITTCPY) || !defined(OEM_SECURE_DIGITZEROMEMORY)

#error "Please provide implementation for OEM_SECURE_* macros.\
 OEM_SECURE_* is used for copying or setting bytes where calls to CRT implementation of \
 mem* functions cannot be used."

#endif /* !defined(OEM_SECURE_MEMCPY) || !defined(OEM_SECURE_MEMCPY_IDX) || !defined(OEM_SECURE_DWORDCPY) || !defined(OEM_SECURE_DIGITTCPY) || !defined(OEM_SECURE_DIGITZEROMEMORY) */

EXIT_PK_NAMESPACE;

#endif /* __OEMCOMMONMEM_H__ */

