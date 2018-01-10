/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/


#ifndef __DRM_DATASTORETYPES_H__
#define __DRM_DATASTORETYPES_H__

#include <drmembeddedstore_impl.h>
#include <drmhds_impl.h>

ENTER_PK_NAMESPACE;

/*
** Enumeration of the currently supported DST implementations
*/
typedef enum
{
    eDRM_DST_NONE,
    eDRM_DST_HDS,
    eDRM_DST_EMBEDDED
} DRM_DST_IMPLEMENTATION_TYPE;

/*
** Context sizes which depend on the supported, underlying implementations:
*/
#define DRM_DST_CONTEXT_LEN            MAX( DRM_HDS_CONTEXT_LEN,           DRM_EST_CONTEXT_LEN )
#define DRM_DST_NAMESPACE_CONTEXT_LEN  MAX( DRM_HDS_NAMESPACE_CONTEXT_LEN, DRM_EST_NAMESPACE_CONTEXT_LEN )
#define DRM_DST_NAMESPACE_LEN          MAX( DRM_HDS_NSNAME_SIZE,           DRM_EST_NAMESPACE_LEN )
#define DRM_DST_SLOT_CONTEXT_LEN       MAX( DRM_HDS_SLOT_CONTEXT_LEN,      DRM_EST_SLOT_CONTEXT_LEN )
#define DRM_DST_ENUM_CONTEXT_LEN       MAX( DRM_HDS_ENUM_CONTEXT_LEN,      DRM_EST_ENUM_CONTEXT_LEN )
#define DRM_DST_SLOT_HINT_LEN          MAX( DRM_HDS_SLOT_HINT_LEN,         DRM_EST_SLOT_HINT_LEN )

/*
** Context containing information about a data store.
** This is a maximum size across all implementations.
*/
typedef struct __tagDRM_DST_CONTEXT
{
    DRM_BYTE rgbOpaqueData[DRM_DST_CONTEXT_LEN]; /* Opaque, implementation-specific data */
} DRM_DST_CONTEXT;

/*
** Namespace identification data.
*/
typedef struct __tagDRM_DST_NAMESPACE
{
    DRM_BYTE rgbOpaqueData[DRM_DST_NAMESPACE_LEN];/* Opaque, implementation-specific data */
} DRM_DST_NAMESPACE;

/*
** Context containing information about a namespace within a data store.
*/
typedef struct __tagDRM_DST_NAMESPACE_CONTEXT
{
    DRM_BYTE rgbOpaqueData[DRM_DST_NAMESPACE_CONTEXT_LEN]; /* Opaque, implementation-specific data */
} DRM_DST_NAMESPACE_CONTEXT;

/*
** Context containing information about a data slot within a namespace.
*/
typedef struct __tagDRM_DST_SLOT_CONTEXT
{
    DRM_BYTE rgbOpaqueData[DRM_DST_SLOT_CONTEXT_LEN]; /* Opaque, implementation-specific data */
} DRM_DST_SLOT_CONTEXT;

/*
** Context containing information about a slot enumeration context.
*/
typedef struct __tagDRM_DST_ENUM_CONTEXT
{
    DRM_BYTE rgbOpaqueData[DRM_DST_ENUM_CONTEXT_LEN]; /* Opaque, implementation-specific data */
} DRM_DST_ENUM_CONTEXT;

/*
** Context containing data used to find a slot quickly.
*/
typedef struct __tagDRM_DST_SLOT_HINT
{
    DRM_BYTE rgbOpaqueData[DRM_DST_SLOT_HINT_LEN]; /* Opaque, implementation-specific data */
} DRM_DST_SLOT_HINT;


/*
** ----------------------------------------------------------------------------
** Function typedefs
** ----------------------------------------------------------------------------
*/

typedef DRM_API DRM_RESULT ( DRM_CALL *DRM_DST_INIT ) ( __inout DRM_DST_CONTEXT *f_pContextDST );

typedef DRM_API DRM_RESULT ( DRM_CALL *DRM_DST_UNINIT ) ( __inout DRM_DST_CONTEXT *f_pContextDST );

typedef DRM_API DRM_RESULT ( DRM_CALL *DRM_DST_CREATESTORE ) (
    __in_opt                           DRM_VOID          *f_pbOEMContext,
    __in_bcount( f_cbStoreData ) const DRM_BYTE          *f_pbStoreData,
    __in                               DRM_DWORD          f_cbStoreData,
    __in                         const DRM_DWORD          f_dwBlockSize,
    __in                               DRM_DST_BLKNUMTYPE f_eBlNumType,
    __in                               DRM_BOOL           f_fTruncateExist,
    __in                         const DRM_DWORD          f_dwInitSizeInKB,
    __inout                            DRM_DST_CONTEXT   *f_pContextDST );

typedef DRM_API DRM_RESULT ( DRM_CALL *DRM_DST_OPENSTORE ) (
    __in_opt                     DRM_VOID        *f_pOEMContext,
    __in_bcount( f_cbStoreData ) DRM_BYTE        *f_pbStoreData,
    __in                         DRM_DWORD        f_cbStoreData,
    __in                         DRM_DWORD        f_dwGrowBySizeinKB,
    __inout                      DRM_DST_CONTEXT *f_pContextDST );

typedef DRM_API DRM_RESULT ( DRM_CALL *DRM_DST_CLOSESTORE )( __inout DRM_DST_CONTEXT *f_pContextDST );

typedef DRM_API DRM_RESULT ( DRM_CALL *DRM_DST_COMMITSTORE )( __inout DRM_DST_CONTEXT *f_pContextDST );

typedef DRM_API DRM_RESULT ( DRM_CALL *DRM_DST_CLEANUPSTORE )(
    __inout DRM_DST_CONTEXT *f_pContextDST,
    __in    DRM_BOOL         f_fWait );

typedef DRM_API DRM_RESULT ( DRM_CALL *DRM_DST_OPENNAMESPACE )(
    __inout        DRM_DST_CONTEXT           *f_pContextDST,
    __in    const  DRM_DST_NAMESPACE         *f_pNamespace,
    __in           DRM_DST_OPENMODE           f_eOpenMode,
    __in           DRM_WORD                   f_wMaxNumChildren,
    __in           DRM_DWORD                  f_dwExpectedSlotSize,
    __out          DRM_DST_NAMESPACE_CONTEXT *f_pContextNS );

typedef DRM_API DRM_RESULT ( DRM_CALL *DRM_DST_DELETENAMESPACE )(
    __inout    DRM_DST_CONTEXT   *f_pContextDST,
    __inout    DRM_DST_NAMESPACE *f_pNS,
    __in       DRM_BOOL           f_fWait );

typedef DRM_API DRM_RESULT ( DRM_CALL *DRM_DST_CLOSENAMESPACE )(
    __inout    DRM_DST_NAMESPACE_CONTEXT  *f_pContextNS );

typedef DRM_API DRM_RESULT ( DRM_CALL *DRM_DST_COMMITNAMESPACE )(
    __inout    DRM_DST_NAMESPACE_CONTEXT  *f_pContextNS );

typedef DRM_API DRM_RESULT ( DRM_CALL *DRM_DST_MAKESLOTHINT )(
    __in    DRM_DST_SLOT_CONTEXT  *f_pContextSlot,
    __out   DRM_DST_SLOT_HINT     *f_pSlotHint );

typedef DRM_API DRM_RESULT ( DRM_CALL *DRM_DST_OPENSLOT )(
    __in       DRM_DST_NAMESPACE_CONTEXT *f_pContextNS,
    __in       DRM_DWORD                  f_dwMode,
    __in const DRM_DST_KEY               *f_pKey1,
    __in const DRM_DST_KEY               *f_pKey2,
    __in_opt   DRM_DST_SLOT_HINT         *f_pSlotHint,
    __inout    DRM_DWORD                 *f_pcbSlotSize,
    __out      DRM_DST_SLOT_CONTEXT      *f_pContextSlot );

typedef DRM_API DRM_RESULT ( DRM_CALL *DRM_DST_CLOSESLOT )(
    __inout  DRM_DST_SLOT_CONTEXT  *f_pContextSlot );

typedef DRM_API DRM_RESULT ( DRM_CALL *DRM_DST_DELETESLOT )(
    __in       DRM_DST_NAMESPACE_CONTEXT *f_pContextNS,
    __in const DRM_DST_KEY               *f_pKey1,
    __in const DRM_DST_KEY               *f_pKey2,
    __in_opt   DRM_DST_SLOT_HINT         *f_pSlotHint,
    __in       DRM_BOOL                   f_fWait );

typedef DRM_API DRM_RESULT ( DRM_CALL *DRM_DST_INITSLOTENUM )(
    __in           DRM_DST_NAMESPACE_CONTEXT *f_pContextNS,
    __in_opt const DRM_DST_KEY               *f_pKey1,
    __in           DRM_DST_LOCKMODE           f_eLockMode,
    __out          DRM_DST_ENUM_CONTEXT      *f_pContextEnum );

typedef DRM_API DRM_RESULT ( DRM_CALL *DRM_DST_SLOTENUMNEXT )(
    __inout    DRM_DST_ENUM_CONTEXT  *f_pContextEnum,
    __out      DRM_DST_SLOT_CONTEXT  *f_pContextSlot,
    __out_opt  DRM_DST_KEY           *f_pKey1,
    __out_opt  DRM_DST_KEY           *f_pKey2,
    __out_opt  DRM_DWORD             *f_pcbSize );

typedef DRM_API DRM_RESULT ( DRM_CALL *DRM_DST_SLOTENUMRELOADCURRENT )(
    __inout    DRM_DST_ENUM_CONTEXT  *f_pContextEnum,
    __out      DRM_DST_SLOT_CONTEXT  *f_pContextSlot,
    __out_opt  DRM_DST_KEY           *f_pKey1,
    __out_opt  DRM_DST_KEY           *f_pKey2,
    __out_opt  DRM_DWORD             *f_pcbSize );

typedef DRM_API DRM_RESULT ( DRM_CALL *DRM_DST_SLOTENUMDELETECURRENT )(
    __inout   DRM_DST_ENUM_CONTEXT  *f_pContextEnum,
    __inout   DRM_DST_SLOT_CONTEXT  *f_pContextSlot );

typedef DRM_API DRM_RESULT ( DRM_CALL *DRM_DST_BLOCKSCANDELETE )(
    __inout                DRM_DST_NAMESPACE_CONTEXT  *f_pContextNS,
    __in_ecount( f_cKey1 ) DRM_DST_KEY                *f_rgKey1,
    __in                   DRM_DWORD                   f_cKey1,
    __in                   DRM_DST_KEY                *f_pKey2,
    __in                   DRM_BOOL                    f_fWait );

typedef DRM_API DRM_RESULT ( DRM_CALL *DRM_DST_SLOTRESIZE )(
    __inout  DRM_DST_SLOT_CONTEXT  *f_pContextSlot,
    __in     DRM_DWORD              f_cbSize );

typedef DRM_API DRM_RESULT ( DRM_CALL *DRM_DST_SLOTSEEK )(
    __inout   DRM_DST_SLOT_CONTEXT  *f_pContextSlot,
    __in      DRM_LONG               f_lOffset,
    __in      DRM_DST_SEEKMODE       f_eSeekMode,
    __out_opt DRM_DWORD             *f_pdwSeekPointer );

typedef DRM_API DRM_RESULT ( DRM_CALL *DRM_DST_SLOTREAD )(
    __inout                  DRM_DST_SLOT_CONTEXT  *f_pContextSlot,
    __in                     DRM_DWORD              f_cbData,
    __out_bcount( f_cbData ) DRM_BYTE              *f_pbData,
    __out_opt                DRM_DWORD             *f_pcbRead );

typedef DRM_API DRM_RESULT ( DRM_CALL *DRM_DST_SLOTWRITE )(
    __inout                       DRM_DST_SLOT_CONTEXT  *f_pContextSlot,
    __in                          DRM_DWORD              f_cbData,
    __in_bcount( f_cbData ) const DRM_BYTE              *f_pbData,
    __out_opt                     DRM_DWORD             *f_pcbWritten );

typedef DRM_API DRM_RESULT ( DRM_CALL *DRM_DST_SLOTREADPTR )(
    __inout                           DRM_DST_SLOT_CONTEXT  *f_pContextSlot,
    __deref_out_bcount( *f_pcbData )  DRM_BYTE             **f_ppbData,
    __out                             DRM_DWORD             *f_pcbData );


/*
** Meta-structure which contains the function pointers used to access
** data store implementations
*/
typedef struct __tag_DRM_DST_INTERFACE
{
    /*
    ** Methods applied to whole data store
    */
    DRM_DST_INIT         pfnInit;        /* Pointer to a data store init function */
    DRM_DST_UNINIT       pfnUninit;      /* Pointer to a data store uninit function */
    DRM_DST_CREATESTORE  pfnCreateStore; /* Pointer to a data store creation function */
    DRM_DST_OPENSTORE    pfnOpenStore;   /* Pointer to a data store opem function */
    DRM_DST_CLOSESTORE   pfnCloseStore;  /* Pointer to a data store close function */
    DRM_DST_COMMITSTORE  pfnCommitStore; /* Pointer to a data store commit function */
    DRM_DST_CLEANUPSTORE pfnCleanupStore;/* Pointer to a data store cleanup function */

    /*
    ** Methods used to open and manage namespaces within a data store.
    */
    DRM_DST_OPENNAMESPACE   pfnOpenNamespace;   /* Pointer to a namespace open function */
    DRM_DST_DELETENAMESPACE pfnDeleteNamespace; /* Pointer to a namespace deletion function */
    DRM_DST_CLOSENAMESPACE  pfnCloseNamespace;  /* Pointer to a namespace close function */
    DRM_DST_COMMITNAMESPACE pfnCommitNamespace; /* Pointer to a namespace commit function */

    /*
    ** Methods to navigate, create, delete, open and close DST dataslots
    */
    DRM_DST_MAKESLOTHINT          pfnMakeSlotHint;          /* Pointer to a slot hint function */
    DRM_DST_OPENSLOT              pfnOpenSlot;              /* Pointer to an open slot function */
    DRM_DST_CLOSESLOT             pfnCloseSlot;             /* Pointer to a close slot function */
    DRM_DST_DELETESLOT            pfnDeleteSlot;            /* Pointer to a slot deletion function */
    DRM_DST_INITSLOTENUM          pfnInitSlotEnum;          /* Pointer to an init slot enum function */
    DRM_DST_SLOTENUMNEXT          pfnSlotEnumNext;          /* Pointer to a slot enum next function */
    DRM_DST_SLOTENUMRELOADCURRENT pfnSlotEnumReloadCurrent; /* Pointer to a slot enum reload current function */
    DRM_DST_SLOTENUMDELETECURRENT pfnSlotEnumDeleteCurrent; /* Pointer to a slot enum delete current function */
    DRM_DST_BLOCKSCANDELETE       pfnBlockScanDelete;       /* Pointer to a block scan delete function */

    /*
    ** Functions to read, write and seek within a dataslot
    */
    DRM_DST_SLOTRESIZE  pfnSlotResize;  /* Pointer to a slot resize function. */
    DRM_DST_SLOTSEEK    pfnSlotSeek;    /* Pointer to a slot seek function. */
    DRM_DST_SLOTREAD    pfnSlotRead;    /* Pointer to a slot read function. */
    DRM_DST_SLOTWRITE   pfnSlotWrite;   /* Pointer to a slot write function. */
    DRM_DST_SLOTREADPTR pfnSlotReadPtr; /* Pointer to a slod read pointer function. Valid only for memory-backed stores. */
} DRM_DST_INTERFACE;

/*
** Context containing information about a data store.
*/
typedef struct __tagDRM_DST
{
    DRM_DST_IMPLEMENTATION_TYPE       eImplementationType;  /* Specifies the implementation type */
    DRM_DST_INTERFACE                 oDataStoreInterface;  /* Contains the function table for an implementation */
    DRM_DST_CONTEXT                  *poContextDST;         /* Contains the internal data store context */
} DRM_DST;

EXIT_PK_NAMESPACE;

#endif  /* __DRM_DATASTORETYPES_H__ */

