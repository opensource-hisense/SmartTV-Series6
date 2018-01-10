/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/


#ifndef __DRM_HDS_H__
#define __DRM_HDS_H__

#include <drmdatastorecommon.h>
#include <drmdatastore.h>

PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_PARAM_25004, "Parameters must match generic drmdatastore.h interface")

ENTER_PK_NAMESPACE;
DRM_API DRM_BOOL DRM_CALL DRM_HDS_IsHDSSupported(DRM_VOID);
DRM_API DRM_BOOL DRM_CALL DRM_HDS_IsHDSUnsupported(DRM_VOID);

typedef struct __tagDRM_HDS_CONTEXT
{
    DRM_BYTE rgbOpaqueData[__CB_DECL( DRM_HDS_CONTEXT_LEN )];
} DRM_HDS_CONTEXT;

/*
** API Functions
*/

/*
** ----------------------------------------------------------------------------
** Methods applied to whole hashed file store
** ----------------------------------------------------------------------------
*/

/**********************************************************************
** Function:    DRM_HDS_Init
** Synopsis:    Init HDS Context
** Arguments:   [f_pContextDST] --
** Returns:     DRM_SUCCESS on success
** Notes:       The function MUST be called in the main thread BEFORE
**              any of the child thread(s) starting sharing the same
**              context. If this function is called after the child
**              thread(s) started, the result is undefined.
***********************************************************************/
DRM_API DRM_RESULT DRM_CALL DRM_HDS_Init( __inout DRM_DST_CONTEXT *f_pContextDST );


/**********************************************************************
** Function:    DRM_HDS_Uninit
** Synopsis:    Uninit HDS Context
** Arguments:   [f_pContextDST] --
** Returns:     DRM_SUCCESS on success
** Notes:       This function MUST be called in the main thread AFTER
**              any of the child thread(s) sharing the same context
**              stopped. If this function is called before the child
**              thread(s) stopped, the result is undefined.
***********************************************************************/
DRM_API DRM_RESULT DRM_CALL DRM_HDS_Uninit( __inout DRM_DST_CONTEXT *f_pContextDST );


/**********************************************************************
** Function:    DRM_HDS_CreateStore
** Synopsis:    Create DRM data store file
** Arguments:   [] --
** Returns:     DRM_SUCCESS on success
** Notes:
***********************************************************************/
DRM_API DRM_RESULT DRM_CALL DRM_HDS_CreateStore(
    __in_opt                           DRM_VOID          *f_pvOEMContext,
    __in_bcount( f_cbStoreData ) const DRM_BYTE          *f_pbStoreData,
    __in                               DRM_DWORD          f_cbStoreData,
    __in                         const DRM_DWORD          f_dwBlockSize,
    __in                               DRM_DST_BLKNUMTYPE f_eBlNumType,
    __in                               DRM_BOOL           f_fTruncateExist,
    __in                         const DRM_DWORD          f_dwInitSizeInKB,
    __out                              DRM_DST_CONTEXT   *f_pContextDST );


/**********************************************************************
** Function:    DRM_HDS_OpenStore
** Synopsis:    Initialize the data store
** Arguments:   [] --
** Returns:     DRM_SUCCESS on success
** Notes:
***********************************************************************/
PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_BUFFER_PARAM, "Parameters must match generic drmdatastore.h interface")
DRM_API DRM_RESULT DRM_CALL DRM_HDS_OpenStore(
    __in_opt                     DRM_VOID        *f_pOEMContext,
    __in_bcount( f_cbStoreData ) DRM_BYTE        *f_pbStoreData,
    __in                         DRM_DWORD        f_cbStoreData,
    __in                         DRM_DWORD        f_dwGrowBySizeinKB,
    __out                        DRM_DST_CONTEXT *f_pContextDST );
PREFAST_POP


/**********************************************************************
** Function:    DRM_HDS_CloseStore
** Synopsis:    Close the license store.  This will also Commit before close
** Arguments:   [f_pContextDST] --
** Returns:     DRM_SUCCESS on success
** Notes:
***********************************************************************/
DRM_API DRM_RESULT DRM_CALL DRM_HDS_CloseStore( __inout DRM_DST_CONTEXT *f_pContextDST );

/**********************************************************************
** Function:    DRM_HDS_CommitStore
** Synopsis:    flush unwritten data to disk
** Arguments:   [f_pContextDST] --
** Returns:     DRM_SUCCESS on success
** Notes:
***********************************************************************/
DRM_API DRM_RESULT DRM_CALL DRM_HDS_CommitStore( __inout DRM_DST_CONTEXT *f_pContextDST );


/**********************************************************************
** Function:    DRM_HDS_CleanupStore
** Synopsis:    clean up empty blocks and hidden slot in store
** Arguments:   [f_pContextDST] --
** Returns:     DRM_SUCCESS on success
** Notes:
***********************************************************************/
DRM_API DRM_RESULT DRM_CALL DRM_HDS_CleanupStore(
    __inout DRM_DST_CONTEXT *f_pContextDST,
    __in    DRM_BOOL         f_fWait );

#define DRM_HDS_OPEN_NAMESPACE_DEFAULT_EXPECTED_SLOT_SIZE 1000
DRM_API DRM_RESULT DRM_CALL DRM_HDS_OpenNamespace(
    __inout                            DRM_DST_CONTEXT           *f_pContextDST,
    __in    const                      DRM_DST_NAMESPACE         *f_pNamespace,
    __in                               DRM_DST_OPENMODE           f_eOpenMode,
    __in                               DRM_WORD                   f_wMaxNumChildren,
    __in                               DRM_DWORD                  f_dwExpectedSlotSize,
    __out                              DRM_DST_NAMESPACE_CONTEXT *f_pContextNS );

/* remove the entire namespace tree and its nodes in the data store */
DRM_API DRM_RESULT DRM_CALL DRM_HDS_DeleteNamespace(
    __inout    DRM_DST_CONTEXT   *f_pContextDST,
    __inout    DRM_DST_NAMESPACE *f_pNS,
    __in       DRM_BOOL           f_fWait );

/* start using the specified namespace, any subsequent calls will be based on this namespace */
DRM_API DRM_RESULT DRM_CALL DRM_HDS_CloseNamespace(
    __inout    DRM_DST_NAMESPACE_CONTEXT  *f_pContextNS );  /* Namespace context returned from DRM_HDS_OpenNamespace */


DRM_API DRM_RESULT DRM_CALL DRM_HDS_CommitNamespace( __inout    DRM_DST_NAMESPACE_CONTEXT  *f_pContextNS );

/*
** ----------------------------------------------------------------------------
** Methods to navigate, create, delete, open and close HDS dataslots
** ----------------------------------------------------------------------------
*/

/* Initialize a slot hint based on the slot context passed */
PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_PARAM, "Parameters must match generic drmdatastore.h interface")
DRM_API DRM_RESULT DRM_CALL DRM_HDS_MakeSlotHint(
    __in    DRM_DST_SLOT_CONTEXT  *f_pContextSlot,
    __out   DRM_DST_SLOT_HINT     *f_pSlotHint );
PREFAST_POP

/* Create or open dataslot using given key1 and key2 */
PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_BUFFER_PARAM_25033, "Out params can't be const")
DRM_API DRM_RESULT DRM_CALL DRM_HDS_OpenSlot(
    __in       DRM_DST_NAMESPACE_CONTEXT *f_pContextNS,/* Namespace context returned from DRM_HDS_OpenNamespace */
    __in       DRM_DWORD                  f_dwMode,
    __in const DRM_DST_KEY               *f_pHashKey,
    __in const DRM_DST_KEY               *f_pUniqueKey,
    __in_opt   DRM_DST_SLOT_HINT         *f_pSlotHint,
    __inout    DRM_DWORD                 *f_pcbSlotSize,/* current dataslot size */
    __out      DRM_DST_SLOT_CONTEXT      *f_pContextSlot );/* user given Dataslot context buffer */
PREFAST_POP

/* Close an opened dataslot */
DRM_API DRM_RESULT DRM_CALL DRM_HDS_CloseSlot( __inout  DRM_DST_SLOT_CONTEXT  *f_pContextSlot );

/* delete the slot immediately */
DRM_API DRM_RESULT DRM_CALL DRM_HDS_DeleteSlot(
    __in       DRM_DST_NAMESPACE_CONTEXT *f_pContextNS,
    __in const DRM_DST_KEY               *f_pHashKey,
    __in const DRM_DST_KEY               *f_pUniqueKey,
    __in_opt   DRM_DST_SLOT_HINT         *f_pSlotHint,
    __in       DRM_BOOL                   f_fWait );


/**********************************************************************
** Function:    DRM_HDS_InitSlotEnum
** Synopsis:
** Arguments:   [f_pContextNS]   -- Namespace context init'd by DRM_HDS_OpenNamespace()
**              [f_pHashKey]     -- Hashkey, if given to query, if not, enum all will be performed
**              [f_eLockMode]    -- Flag specifing how to lock the slot
**              [f_pContextEnum] -- returned Enum context
** Returns:     DRM_SUCCESS on success
** Notes:       This is 2 functions in one. If f_pHashKey is given, only the slots
**              with the same hashkey will be enum'ed. if pHashKey is NULL, all
**              slots within the namespace will be enum'ed.
***********************************************************************/
DRM_API DRM_RESULT DRM_CALL DRM_HDS_InitSlotEnum(
    __in           DRM_DST_NAMESPACE_CONTEXT *f_pContextNS,
    __in_opt const DRM_DST_KEY               *f_pHashKey,
    __in           DRM_DST_LOCKMODE           f_eLockMode,
    __out          DRM_DST_ENUM_CONTEXT      *f_pContextEnum );


/**********************************************************************
** Function:    DRM_HDS_SlotEnumNext
** Synopsis:    Get the next slot in the enumeration
** Arguments:   [f_pcontextEnum] -- Enum Context init'd by DRM_HDS_InitSlotEnum()
**              [f_pContextSlot] -- Slot Context of the current slot
**              [f_pHashKey] -- Hashkey of the current slot
**              [f_pUniqueKey] -- Uniquekey of the current slot
**              [f_pcbSlot] -- size of the current slot
** Returns:     DRM_SUCCESS on success
** Notes:
***********************************************************************/
PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_BUFFER_PARAM_25033, "Out params can't be const")
DRM_API DRM_RESULT DRM_CALL DRM_HDS_SlotEnumNext(
    __inout    DRM_DST_ENUM_CONTEXT  *f_pContextEnum,/* setup by DRM_HDS_InitSlotEnum() */
    __out      DRM_DST_SLOT_CONTEXT  *f_pContextSlot,/* user given Dataslot context buffer */
    __out_opt  DRM_DST_KEY           *f_pHashKey,    /* optional parameter */
    __out_opt  DRM_DST_KEY           *f_pUniqueKey,  /* optional parameter */
    __out_opt  DRM_DWORD             *f_pcbSlot );   /* current dataslot size, optional parameter */
PREFAST_POP

/**********************************************************************
** Function:    DRM_HDS_SlotEnumReloadCurrent
** Synopsis:    Load the current slot in the enumeration
** Arguments:   [f_pContextEnum] -- Enum Context init'd by DRM_HDS_InitSlotEnum()
**              [f_pContextSlot] -- Slot Context of the current slot
**              [f_pHashKey] -- Hashkey of the current slot
**              [f_pUniqueKey] -- Uniquekey of the current slot
**              [f_pcbSlot] -- size of the current slot
** Returns:     DRM_SUCCESS on success
** Notes:
***********************************************************************/
PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_BUFFER_PARAM_25033, "Out params can't be const")
DRM_API DRM_RESULT DRM_CALL DRM_HDS_SlotEnumReloadCurrent(
    __inout    DRM_DST_ENUM_CONTEXT  *f_pContextEnum,       /* setup by DRM_HDS_InitSlotEnum() */
    __out      DRM_DST_SLOT_CONTEXT  *f_pContextSlot,       /* user given Dataslot context buffer */
    __out_opt  DRM_DST_KEY           *f_pHashKey,           /* optional parameter */
    __out_opt  DRM_DST_KEY           *f_pUniqueKey,         /* optional parameter */
    __out_opt  DRM_DWORD             *f_pcbSlot );          /* current dataslot size, optional parameter */
PREFAST_POP

/**********************************************************************
** Function:    DRM_HDS_SlotEnumDeleteCurrent
** Synopsis:    Delete the current enumerated slot
** Arguments:   [f_pcontextEnum] -- Enum Context init'd by DRM_HDS_InitSlotEnum()
**              [f_pcontextSlot] -- Slot Context of the current slot
** Returns:     DRM_SUCCESS on success
** Notes:       The enumeration must be init'ed with EXCLUSIVE right.
***********************************************************************/
DRM_API DRM_RESULT DRM_CALL DRM_HDS_SlotEnumDeleteCurrent(
    __inout   DRM_DST_ENUM_CONTEXT  *f_pContextEnum,
    __inout   DRM_DST_SLOT_CONTEXT  *f_pContextSlot );


/* Block Scan API: rapid deletion of multiple slots */

PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_PARAM, "Parameters must match generic drmdatastore.h interface")
DRM_API DRM_RESULT DRM_CALL DRM_HDS_BlockScanDelete(
    __inout                          DRM_DST_NAMESPACE_CONTEXT  *f_pContextNS,
    __in_ecount( f_cKeysHash )       DRM_DST_KEY                *f_rgKeyHash,
    __in                             DRM_DWORD                   f_cKeysHash,
    __in                             DRM_DST_KEY                *f_pkeyUnique,
    __in                             DRM_BOOL                    f_fWait );
PREFAST_POP

/*
** ----------------------------------------------------------------------------
** Methods to read, write and seek within a dataslot
** ----------------------------------------------------------------------------
*/

/**********************************************************************
** Function:    DRM_HDS_SlotResize
** Synopsis:    resize an opened dataslot
** Arguments:   [f_pContextSlot] -- An open slot context
**              [f_cbSize]       -- New size of the slot
** Returns:     DRM_SUCCESS on success
** Notes:
** Possible cases:
**
***********************************************************************/
DRM_API DRM_RESULT DRM_CALL DRM_HDS_SlotResize(
    __inout  DRM_DST_SLOT_CONTEXT  *f_pContextSlot,
    __in     DRM_DWORD              f_cbSize );

PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_BUFFER_PARAM_25033, "Out params can't be const")
DRM_API DRM_RESULT DRM_CALL DRM_HDS_SlotSeek(
    __inout   DRM_DST_SLOT_CONTEXT  *f_pContextSlot,
    __in      DRM_LONG               f_lOffset,
    __in      DRM_DST_SEEKMODE       f_eOrigin,
    __out_opt DRM_DWORD             *f_pdwSeekPointer );/* optional parameter, can be NULL */
PREFAST_POP

PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_BUFFER_PARAM_25033, "Out params can't be const")
DRM_API DRM_RESULT DRM_CALL DRM_HDS_SlotRead(
    __inout                  DRM_DST_SLOT_CONTEXT  *f_pContextSlot,
    __in                     DRM_DWORD              f_cbData,
    __out_bcount( f_cbData ) DRM_BYTE              *f_pbData,
    __out_opt                DRM_DWORD             *f_pcbRead );
PREFAST_POP

PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_BUFFER_PARAM_25033, "Out params can't be const")
DRM_API DRM_RESULT DRM_CALL DRM_HDS_SlotWrite(
    __inout                       DRM_DST_SLOT_CONTEXT  *f_pContextSlot,
    __in                          DRM_DWORD              f_cbData,
    __in_bcount( f_cbData ) const DRM_BYTE              *f_pbData,
    __out_opt                     DRM_DWORD             *f_pcbWritten );
PREFAST_POP

PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_BUFFER_PARAM_25033, "Out params can't be const")
DRM_API DRM_RESULT DRM_CALL DRM_HDS_SlotReadPtr(
    __inout                           DRM_DST_SLOT_CONTEXT  *f_pContextSlot,
    __deref_out_bcount( *f_pcbData )  DRM_BYTE             **f_ppbData,
    __out                             DRM_DWORD             *f_pcbData );
PREFAST_POP

DRM_API DRM_RESULT DRM_CALL DRM_HDS_InitializeDST( __out DRM_DST *f_pDst );

EXIT_PK_NAMESPACE;

PREFAST_POP /* Parameters must match generic drmdatastore.h interface */

#endif  /* __DRM_HDS_H__ */

