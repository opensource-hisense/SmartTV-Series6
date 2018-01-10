/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/


#ifndef __DRM_DATASTORE_H__
#define __DRM_DATASTORE_H__

#include <drmdatastoretypes.h>
#include <drmdatastorecommon.h>
#include <drmembeddedstore_impl.h>
#include <drmhds_impl.h>
#include <drmpragmas.h>

ENTER_PK_NAMESPACE;

/*
** ----------------------------------------------------------------------------
** API function definitions to be used for data store interface calls
** ----------------------------------------------------------------------------
*/

/*
** ----------------------------------------------------------------------------
** Methods applied to whole data store
** ----------------------------------------------------------------------------
*/

DRM_API DRM_RESULT DRM_CALL DRM_DST_Init(
    __in                          DRM_DST_IMPLEMENTATION_TYPE       f_eImplementationType,
    __in_bcount( f_cbDSTContext ) DRM_DST_CONTEXT                  *f_pDSTContext,
    __in                          DRM_DWORD                         f_cbDSTContext,
    __out                         DRM_DST                          *f_pDST );

DRM_API DRM_RESULT DRM_CALL DRM_DST_Uninit( __inout DRM_DST *f_pDST );

DRM_API DRM_RESULT DRM_CALL DRM_DST_CreateStore(
    __in_opt                           DRM_VOID          *f_pbOEMContext,
    __in_bcount( f_cbStoreData ) const DRM_BYTE          *f_pbStoreData,
    __in                               DRM_DWORD          f_cbStoreData,
    __in                         const DRM_DWORD          f_dwBlockSize,
    __in                               DRM_DST_BLKNUMTYPE f_eBlNumType,
    __in                               DRM_BOOL           f_fTruncateExist,
    __in                         const DRM_DWORD          f_dwInitSizeInKB,
    __inout                            DRM_DST            *f_pDST );

DRM_API DRM_RESULT DRM_CALL DRM_DST_OpenStore(
    __in_opt                     DRM_VOID   *f_pOEMContext,
    __in_bcount( f_cbStoreData ) DRM_BYTE   *f_pbStoreData,
    __in                         DRM_DWORD   f_cbStoreData,
    __in                         DRM_DWORD   f_dwGrowBySizeinKB,
    __inout                      DRM_DST    *f_pDST );

DRM_API DRM_RESULT DRM_CALL DRM_DST_CloseStore( __inout DRM_DST *f_pDST );

DRM_API DRM_RESULT DRM_CALL DRM_DST_CommitStore( __inout DRM_DST *f_pDST );

DRM_API DRM_RESULT DRM_CALL DRM_DST_CleanupStore(
    __inout DRM_DST   *f_pDST,
    __in    DRM_BOOL   f_fWait );


/*
** ----------------------------------------------------------------------------
** Methods applied to namespaces within the data store.
** ----------------------------------------------------------------------------
*/

DRM_API DRM_RESULT DRM_CALL DRM_DST_OpenNamespace(
    __inout        DRM_DST                   *f_pDST,
    __in    const  DRM_DST_NAMESPACE         *f_pNamespace,
    __in           DRM_DST_OPENMODE           f_eOpenMode,
    __in           DRM_WORD                   f_wMaxNumChildren,
    __in           DRM_DWORD                  f_dwExpectedSlotSize,
    __out          DRM_DST_NAMESPACE_CONTEXT *f_pContextNS );

DRM_API DRM_RESULT DRM_CALL DRM_DST_DeleteNamespace(
    __inout    DRM_DST           *f_pDST,
    __inout    DRM_DST_NAMESPACE *f_pNS,
    __in       DRM_BOOL           f_fWait );

DRM_API DRM_RESULT DRM_CALL DRM_DST_CloseNamespace(
    __inout const DRM_DST                    *f_pDST,
    __inout       DRM_DST_NAMESPACE_CONTEXT  *f_pContextNS ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_RESULT DRM_CALL DRM_DST_CommitNamespace(
    __inout const DRM_DST                    *f_pDST,
    __inout       DRM_DST_NAMESPACE_CONTEXT  *f_pContextNS );


/*
** ----------------------------------------------------------------------------
** Methods to navigate, create, delete, open and close DST dataslots
** ----------------------------------------------------------------------------
*/

DRM_API DRM_RESULT DRM_CALL DRM_DST_MakeSlotHint(
    __inout const DRM_DST               *f_pDST,
    __in          DRM_DST_SLOT_CONTEXT  *f_pContextSlot,
    __out         DRM_DST_SLOT_HINT     *f_pSlotHint ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_RESULT DRM_CALL DRM_DST_OpenSlot(
    __inout  const DRM_DST                   *f_pDST,
    __in           DRM_DST_NAMESPACE_CONTEXT *f_pContextNS,
    __in           DRM_DWORD                  f_dwMode,
    __in     const DRM_DST_KEY               *f_pKey1,
    __in     const DRM_DST_KEY               *f_pKey2,
    __in_opt       DRM_DST_SLOT_HINT         *f_pSlotHint,
    __inout        DRM_DWORD                 *f_pcbSlotSize,
    __out          DRM_DST_SLOT_CONTEXT      *f_pContextSlot ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_RESULT DRM_CALL DRM_DST_CloseSlot(
    __inout const DRM_DST               *f_pDST,
    __inout       DRM_DST_SLOT_CONTEXT  *f_pContextSlot ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_RESULT DRM_CALL DRM_DST_DeleteSlot(
    __inout  const DRM_DST                   *f_pDST,
    __in           DRM_DST_NAMESPACE_CONTEXT *f_pContextNS,
    __in     const DRM_DST_KEY               *f_pKey1,
    __in     const DRM_DST_KEY               *f_pKey2,
    __in_opt       DRM_DST_SLOT_HINT         *f_pSlotHint,
    __in           DRM_BOOL                   f_fWait ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_RESULT DRM_CALL DRM_DST_InitSlotEnum(
    __inout  const DRM_DST                   *f_pDST,
    __in           DRM_DST_NAMESPACE_CONTEXT *f_pContextNS,
    __in_opt const DRM_DST_KEY               *f_pKey1,
    __in           DRM_DST_LOCKMODE           f_eLockMode,
    __out          DRM_DST_ENUM_CONTEXT      *f_pContextEnum ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_RESULT DRM_CALL DRM_DST_SlotEnumNext(
    __inout   const DRM_DST               *f_pDST,
    __inout         DRM_DST_ENUM_CONTEXT  *f_pContextEnum,
    __out           DRM_DST_SLOT_CONTEXT  *f_pContextSlot,
    __out_opt       DRM_DST_KEY           *f_pKey1,
    __out_opt       DRM_DST_KEY           *f_pKey2,
    __out_opt       DRM_DWORD             *f_pcbSize ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_RESULT DRM_CALL DRM_DST_SlotEnumReloadCurrent(
    __inout   const DRM_DST               *f_pDST,
    __inout         DRM_DST_ENUM_CONTEXT  *f_pContextEnum,
    __out           DRM_DST_SLOT_CONTEXT  *f_pContextSlot,
    __out_opt       DRM_DST_KEY           *f_pKey1,
    __out_opt       DRM_DST_KEY           *f_pKey2,
    __out_opt       DRM_DWORD             *f_pcbSize ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_RESULT DRM_CALL DRM_DST_SlotEnumDeleteCurrent(
    __inout const DRM_DST               *f_pDST,
    __inout       DRM_DST_ENUM_CONTEXT  *f_pContextEnum,
    __inout       DRM_DST_SLOT_CONTEXT  *f_pContextSlot ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_RESULT DRM_CALL DRM_DST_BlockScanDelete(
    __inout                const DRM_DST                    *f_pDST,
    __inout                      DRM_DST_NAMESPACE_CONTEXT  *f_pContextNS,
    __in_ecount( f_cKey1 )       DRM_DST_KEY                *f_rgKey1,
    __in                         DRM_DWORD                   f_cKey1,
    __in                         DRM_DST_KEY                *f_pKey2,
    __in                         DRM_BOOL                    f_fWait ) DRM_NO_INLINE_ATTRIBUTE;


/*
** ----------------------------------------------------------------------------
** Methods to read, write and seek within a dataslot
** ----------------------------------------------------------------------------
*/

DRM_API DRM_RESULT DRM_CALL DRM_DST_SlotResize(
    __inout const DRM_DST               *f_pDST,
    __inout       DRM_DST_SLOT_CONTEXT  *f_pContextSlot,
    __in          DRM_DWORD              f_cbSize ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_RESULT DRM_CALL DRM_DST_SlotSeek(
    __inout   const DRM_DST               *f_pDST,
    __inout         DRM_DST_SLOT_CONTEXT  *f_pContextSlot,
    __in            DRM_LONG               f_lOffset,
    __in            DRM_DST_SEEKMODE       f_eSeekMode,
    __out_opt       DRM_DWORD             *f_pdwSeekPointer ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_RESULT DRM_CALL DRM_DST_SlotRead(
    __inout                  const DRM_DST               *f_pDST,
    __inout                        DRM_DST_SLOT_CONTEXT  *f_pContextSlot,
    __in                           DRM_DWORD              f_cbData,
    __out_bcount( f_cbData )       DRM_BYTE              *f_pbData,
    __out_opt                      DRM_DWORD             *f_pcbRead ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_RESULT DRM_CALL DRM_DST_SlotWrite(
    __inout                 const DRM_DST               *f_pDST,
    __inout                       DRM_DST_SLOT_CONTEXT  *f_pContextSlot,
    __in                          DRM_DWORD              f_cbData,
    __in_bcount( f_cbData ) const DRM_BYTE              *f_pbData,
    __out_opt                     DRM_DWORD             *f_pcbWritten ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_RESULT DRM_CALL DRM_DST_SlotReadPtr(
    __inout                     const DRM_DST               *f_pDST,
    __inout                           DRM_DST_SLOT_CONTEXT  *f_pContextSlot,
    __deref_out_bcount( *f_pcbData )  DRM_BYTE             **f_ppbData,
    __out                             DRM_DWORD             *f_pcbData );

EXIT_PK_NAMESPACE;

#endif  /* __DRM_DATASTORE_H__ */

