/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRM_STACK_ALLOCATORTYPES__
#define __DRM_STACK_ALLOCATORTYPES__

#include <drmtypes.h>

ENTER_PK_NAMESPACE;

#define DRM_STK_REQUIRED(cbData) \
    (   (cbData) \
    +   SIZEOF(DRM_DWORD) \
    +   ( ((cbData) % SIZEOF(DRM_DWORD_PTR) == 0) ? (0) : (SIZEOF(DRM_DWORD_PTR) - ((cbData) % SIZEOF(DRM_DWORD_PTR))) ) )

typedef DRM_OBFUS_FIXED_ALIGN struct __tagDRM_STACK_ALLOCATOR_CONTEXT
{
    DRM_DWORD nStackTop;    /* position of stack top */
    DRM_DWORD cbStack;      /* size of stack */
DRM_OBFUS_PTR_TOP
    DRM_BYTE *pbStack;      /* stack buffer */
DRM_OBFUS_PTR_BTM
    DRM_BOOL  fWasPreAlloc; /* used to signal that we PreAlloc, and Alloc shouldn't fill mem with 0xaa */
DRM_OBFUS_FILL_BYTES(4)
} DRM_STACK_ALLOCATOR_CONTEXT;

EXIT_PK_NAMESPACE;

#endif /* __DRM_STACK_ALLOCATORTYPES__ */

