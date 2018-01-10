/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/


#ifndef __DRM_EMBEDDEDSTORE_H__
#define __DRM_EMBEDDEDSTORE_H__

#include <drmdatastore.h>

ENTER_PK_NAMESPACE;

PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_PARAM, "Parameters must match generic drmdatastore.h interface")

/*
** Embedded store header constants
*/
#define DRM_EST_HEADER_CONST     "EST" /* Constant which must begin the EST buffer. */
#define DRM_EST_HEADER_CONST_LEN 4     /* Length of DRM_EST_HEADER_CONST in bytes. */
#define DRM_EST_MINIMUM_VERSION  1     /* Lowest valid version for the embedded store format */
#define DRM_EST_CURRENT_VERSION  1     /* Current version of the embedded store format. */

/*
** EmbeddedLicenseStore Header Format
**
** Field                         | Type
** --------------------------------------
** Header Constants              | DWORD
** Store Version                 | WORD
** Minimum Compatibility Version | WORD
** Store Size                    | DWORD
** License Slots                 | Data
*/
#define DRM_EST_HEADER_LEN       ( DRM_EST_HEADER_CONST_LEN + 2 * SIZEOF( DRM_WORD ) + SIZEOF( DRM_DWORD ) )

/*
** Embedded store slot constants
*/

/*
** EmbeddedLicenseSlot Header Format
**
** Field                         | Type
** --------------------------------------
** Slot Size                     | DWORD
** Key ID                        | DRM_GUID
** License ID                    | DRM_GUID
** License Priority              | DWORD                Priority is the first DWORD of the license data
** License Data                  | Byte array
*/
#define DRM_EST_SLOTHEADER_LEN  ( SIZEOF( DRM_DWORD ) + 2 * SIZEOF( DRM_DST_KEY ) )

DRM_API DRM_RESULT DRM_CALL DRM_EST_InitializeDST( __out DRM_DST *f_pDst );

DRM_API DRM_RESULT DRM_CALL DRM_EST_Init ( __inout DRM_DST_CONTEXT *f_pContextDST );

DRM_API DRM_RESULT DRM_CALL DRM_EST_Uninit ( __inout DRM_DST_CONTEXT *f_pContextDST );

DRM_API DRM_RESULT DRM_CALL DRM_EST_CreateStore(
    __in_opt                           DRM_VOID          *f_pbOEMContext,
    __in_bcount( f_cbStoreData ) const DRM_BYTE          *f_pbStoreData,
    __in                               DRM_DWORD          f_cbStoreData,
    __in                         const DRM_DWORD          f_dwBlockSize,
    __in                               DRM_DST_BLKNUMTYPE f_eBlNumType,
    __in                               DRM_BOOL           f_fTruncateExist,
    __in                         const DRM_DWORD          f_dwInitSizeInKB,
    __inout                            DRM_DST_CONTEXT   *f_pContextDST );

DRM_API DRM_RESULT DRM_CALL DRM_EST_OpenStore (
    __in_opt                     DRM_VOID        *f_pOEMContext,
    __in_bcount( f_cbStoreData ) DRM_BYTE        *f_pbStoreData,
    __in                         DRM_DWORD        f_cbStoreData,
    __in                         DRM_DWORD        f_dwGrowBySizeinKB,
    __inout                      DRM_DST_CONTEXT *f_pContextDST );

DRM_API DRM_RESULT DRM_CALL DRM_EST_CloseStore ( __inout DRM_DST_CONTEXT *f_pContextDST );

DRM_API DRM_RESULT DRM_CALL DRM_EST_CommitStore ( __inout DRM_DST_CONTEXT *f_pContextDST );

DRM_API DRM_RESULT DRM_CALL DRM_EST_CleanupStore (
    __inout       DRM_DST_CONTEXT *f_pContextDST,
    __in          DRM_BOOL         f_fWait );

DRM_API DRM_RESULT DRM_CALL DRM_EST_OpenNamespace (
    __inout        DRM_DST_CONTEXT           *f_pContextDST,
    __in    const  DRM_DST_NAMESPACE         *f_pNamespace,
    __in           DRM_DST_OPENMODE           f_eOpenMode,
    __in           DRM_WORD                   f_wMaxNumChildren,
    __in           DRM_DWORD                  f_dwExpectedSlotSize,
    __out          DRM_DST_NAMESPACE_CONTEXT *f_pContextNS );

DRM_API DRM_RESULT DRM_CALL DRM_EST_DeleteNamespace(
    __inout    DRM_DST_CONTEXT   *f_pContextDST,
    __inout    DRM_DST_NAMESPACE *f_pNS,
    __in       DRM_BOOL           f_fWait );

DRM_API DRM_RESULT DRM_CALL DRM_EST_CloseNamespace (
    __inout    DRM_DST_NAMESPACE_CONTEXT  *f_pContextNS );

DRM_API DRM_RESULT DRM_CALL DRM_EST_CommitNamespace (
    __inout    DRM_DST_NAMESPACE_CONTEXT  *f_pContextNS );

DRM_API DRM_RESULT DRM_CALL DRM_EST_MakeSlotHint (
    __in    DRM_DST_SLOT_CONTEXT  *f_pContextSlot,
    __out   DRM_DST_SLOT_HINT     *f_pSlotHint );

DRM_API DRM_RESULT DRM_CALL DRM_EST_OpenSlot (
    __in       DRM_DST_NAMESPACE_CONTEXT *f_pContextNS,
    __in       DRM_DWORD                  f_dwMode,
    __in const DRM_DST_KEY               *f_pKey1,
    __in const DRM_DST_KEY               *f_pKey2,
    __in_opt   DRM_DST_SLOT_HINT         *f_pSlotHint,
    __inout    DRM_DWORD                 *f_pcbSlotSize,
    __out      DRM_DST_SLOT_CONTEXT      *f_pContextSlot );

DRM_API DRM_RESULT DRM_CALL DRM_EST_CloseSlot (
    __inout  DRM_DST_SLOT_CONTEXT  *f_pContextSlot );

DRM_API DRM_RESULT DRM_CALL DRM_EST_DeleteSlot (
    __in       DRM_DST_NAMESPACE_CONTEXT *f_pContextNS,
    __in const DRM_DST_KEY               *f_pKey1,
    __in const DRM_DST_KEY               *f_pKey2,
    __in_opt   DRM_DST_SLOT_HINT         *f_pSlotHint,
    __in       DRM_BOOL                   f_fWait );

DRM_API DRM_RESULT DRM_CALL DRM_EST_InitSlotEnum (
    __in           DRM_DST_NAMESPACE_CONTEXT *f_pContextNS,
    __in_opt const DRM_DST_KEY               *f_pKey1,
    __in           DRM_DST_LOCKMODE           f_eLockMode,
    __out          DRM_DST_ENUM_CONTEXT      *f_pContextEnum );

DRM_API DRM_RESULT DRM_CALL DRM_EST_SlotEnumNext (
    __inout    DRM_DST_ENUM_CONTEXT  *f_pContextEnum,
    __out      DRM_DST_SLOT_CONTEXT  *f_pContextSlot,
    __out_opt  DRM_DST_KEY           *f_pKey1,
    __out_opt  DRM_DST_KEY           *f_pKey2,
    __out_opt  DRM_DWORD             *f_pcbSize );

DRM_API DRM_RESULT DRM_CALL DRM_EST_SlotEnumReloadCurrent (
    __inout    DRM_DST_ENUM_CONTEXT  *f_pContextEnum,
    __out      DRM_DST_SLOT_CONTEXT  *f_pContextSlot,
    __out_opt  DRM_DST_KEY           *f_pKey1,
    __out_opt  DRM_DST_KEY           *f_pKey2,
    __out_opt  DRM_DWORD             *f_pcbSize );

DRM_API DRM_RESULT DRM_CALL DRM_EST_SlotEnumDeleteCurrent (
    __inout   DRM_DST_ENUM_CONTEXT  *f_pContextEnum,
    __inout   DRM_DST_SLOT_CONTEXT  *f_pContextSlot );

DRM_API DRM_RESULT DRM_CALL DRM_EST_BlockScanDelete (
    __inout                DRM_DST_NAMESPACE_CONTEXT  *f_pContextNS,
    __in_ecount( f_cKey1 ) DRM_DST_KEY                *f_rgKey1,
    __in                   DRM_DWORD                   f_cKey1,
    __in                   DRM_DST_KEY                *f_pKey2,
    __in                   DRM_BOOL                    f_fWait );

DRM_API DRM_RESULT DRM_CALL DRM_EST_SlotResize (
    __inout  DRM_DST_SLOT_CONTEXT  *f_pContextSlot,
    __in     DRM_DWORD              f_cbSize );

DRM_API DRM_RESULT DRM_CALL DRM_EST_SlotSeek (
    __inout   DRM_DST_SLOT_CONTEXT  *f_pContextSlot,
    __in      DRM_LONG               f_lOffset,
    __in      DRM_DST_SEEKMODE       f_eSeekMode,
    __out_opt DRM_DWORD             *f_pdwSeekPointer );

DRM_API DRM_RESULT DRM_CALL DRM_EST_SlotRead (
    __inout                  DRM_DST_SLOT_CONTEXT  *f_pContextSlot,
    __in                     DRM_DWORD              f_cbData,
    __out_bcount( f_cbData ) DRM_BYTE              *f_pbData,
    __out_opt                DRM_DWORD             *f_pcbRead );

DRM_API DRM_RESULT DRM_CALL DRM_EST_SlotWrite (
    __inout                       DRM_DST_SLOT_CONTEXT  *f_pContextSlot,
    __in                          DRM_DWORD              f_cbData,
    __in_bcount( f_cbData ) const DRM_BYTE              *f_pbData,
    __out_opt                     DRM_DWORD             *f_pcbWritten );

DRM_API DRM_RESULT DRM_CALL DRM_EST_SlotReadPtr(
    __inout                           DRM_DST_SLOT_CONTEXT  *f_pContextSlot,
    __deref_out_bcount( *f_pcbData )  DRM_BYTE             **f_ppbData,
    __out                             DRM_DWORD             *f_pcbData );

PREFAST_POP /* Parameters must match generic drmdatastore.h interface */

EXIT_PK_NAMESPACE;

#endif  /* __DRM_EMBEDDEDSTORE_H__ */
