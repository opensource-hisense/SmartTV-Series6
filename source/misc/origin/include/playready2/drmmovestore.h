/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRM_MOVE_STORE_H
#define __DRM_MOVE_STORE_H

#include <drmdatastore.h>

ENTER_PK_NAMESPACE;

/* The context of the move store. */
typedef struct _tagMoveStoreContextPrivate
{
    /* Pointer to the underlying DST. */
    DRM_DST *m_poDST;

    /* The underlying DST namespace context. */
    DRM_DST_NAMESPACE_CONTEXT m_oDSTNameSpaceContext;

    /* The underlying DST slot context. */
    DRM_DST_SLOT_CONTEXT m_oDSTSlotContext;

    /* Flag indicating whether the context has been initialized. */
    DRM_BOOL m_fInited;
} DRM_MOVESTORE_CONTEXT_PRIVATE;

/* The context of the move store in the form of a BLOB. */
typedef struct __tagDRM_MOVESTORE_CONTEXT
{
    DRM_BYTE rgbOpaqueData [ __CB_DECL( SIZEOF( DRM_MOVESTORE_CONTEXT_PRIVATE ) ) ];
} DRM_MOVESTORE_CONTEXT;

#define DRM_MOVST_MOVE_INDEX_NUMBER MAX_UNSIGNED_VALUE( DRM_DWORD )

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_MOVST_OpenStore(
    __in  DRM_DST               *f_pDatastore,
    __out DRM_MOVESTORE_CONTEXT *f_poMoveStoreContext ) DRM_NO_INLINE_ATTRIBUTE;


DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_MOVST_CloseStore(
    __in DRM_MOVESTORE_CONTEXT *f_poMoveStoreContext ) DRM_NO_INLINE_ATTRIBUTE;

/*
**  Extract a move page or a move list index from the store.
**  Move pages are 0 indexed and the move list index is referenced by DRM_MOVST_MOVE_INDEX_NUMBER
*/

#define DRM_MOVE_PAGE_INDEX 0
#define DRM_MOVE_PAGE_N( n ) (n)

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_MOVST_UpdateMovePage(
    __in                          DRM_MOVESTORE_CONTEXT *f_poMoveStoreContext,
    __in                          DRM_DWORD              f_iPage,
    __in_bcount( f_cbPage ) const DRM_BYTE              *f_pbPage,
    __in                          DRM_DWORD              f_cbPage ) DRM_NO_INLINE_ATTRIBUTE;


DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_MOVST_GetMovePage(
    __in                           DRM_MOVESTORE_CONTEXT *f_poMoveStoreContext,
    __in                           DRM_DWORD              f_iPage,
    __out_bcount_opt( *f_pcbPage ) DRM_BYTE              *f_pbPage,
    __inout                        DRM_DWORD             *f_pcbPage ) DRM_NO_INLINE_ATTRIBUTE;

EXIT_PK_NAMESPACE;

#endif /* __DRM_MOVE_STORE_H */

