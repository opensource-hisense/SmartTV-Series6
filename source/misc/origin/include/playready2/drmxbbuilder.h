/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRM_XB_BUILDER_H__
#define __DRM_XB_BUILDER_H__ 1

#include <drmxb.h>
#include <drmstkalloc.h>

ENTER_PK_NAMESPACE;

typedef struct __tagDRM_XB_BUILDER_NODE
{
    DRM_WORD     wType;
    DRM_DWORD    cbLength;
    /*
    ** This can either be an object or a linked list of
    ** builder nodes depending on whether this is a
    ** leaf node or not
    */
    const DRM_VOID *pvObject;
} DRM_XB_BUILDER_NODE;

typedef struct __tagDRM_XB_BUILDER_LISTNODE
{
    DRM_XB_BUILDER_NODE                  Node;
    struct __tagDRM_XB_BUILDER_LISTNODE *pNext;
} DRM_XB_BUILDER_LISTNODE;


typedef struct __tagDRM_XB_BUILDER_CONTEXT_INTERNAL
{
    DRM_DWORD                                 dwVersion;

    /*  In case of nodes which can have duplicates, the array below will hold the
    **  pointer to the last node of that type. In those cases, it is just used
    **  to keep track of the types of nodes added
    */
    DRM_XB_BUILDER_NODE                    **rgpObjectNodes;
    DRM_XB_BUILDER_LISTNODE                 *pUnknownObjects;
    DRM_STACK_ALLOCATOR_CONTEXT              contextStack;
    const DRM_XB_FORMAT_DESCRIPTION         *pformat;

#if DRM_OBFUS_NEED_PADDING
    DRM_VOID *m_rgpvWM7Padding[4];
#endif /* DRM_OBFUS_NEED_PADDING */
} DRM_XB_BUILDER_CONTEXT_INTERNAL;

#define DRM_XB_BUILDER_CONTEXT_BUFFER_SIZE SIZEOF( DRM_XB_BUILDER_CONTEXT_INTERNAL )

typedef struct __tagDRM_XB_BUILDER_CONTEXT
{
    /*
    ** This data is Opaque.  Do not set any value in it.
    */
    DRM_BYTE rgbOpaqueBuffer[__CB_DECL( DRM_XB_BUILDER_CONTEXT_BUFFER_SIZE )];
} DRM_XB_BUILDER_CONTEXT;

DRM_API DRM_RESULT DRM_CALL DRM_XB_StartFormat(
    __inout_bcount( f_cbStack ) DRM_BYTE                  *f_pbStack,
    __in                        DRM_DWORD                  f_cbStack,
    __in                        DRM_DWORD                  f_dwVersion,
    __inout_ecount( 1 )         DRM_XB_BUILDER_CONTEXT    *f_pcontextBuilder,
    __in                  const DRM_XB_FORMAT_DESCRIPTION *f_pformat );

DRM_API DRM_RESULT DRM_CALL DRM_XB_FinishFormat(
    __in_ecount( 1 ) const              DRM_XB_BUILDER_CONTEXT *f_pcontextBuilder,
    __inout_bcount_opt( *f_pcbLicense ) DRM_BYTE                *f_pbLicense,
    __inout_ecount( 1 )                 DRM_DWORD               *f_pcbLicense );

DRM_API DRM_RESULT DRM_CALL DRM_XB_AddEntry(
    __inout_ecount( 1 )    DRM_XB_BUILDER_CONTEXT    *f_contextBuilder,
    __in                   DRM_WORD                   f_wObjectType,
    __in_ecount( 1 ) const DRM_VOID                  *f_pvObject );

EXIT_PK_NAMESPACE;

#endif  /* __DRM_XB_BUILDER_H__ */

