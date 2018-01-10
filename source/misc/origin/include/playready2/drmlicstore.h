/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/


#ifndef __DRM_LICSTORE_H__
#define __DRM_LICSTORE_H__

#include <drmdatastore.h>

ENTER_PK_NAMESPACE;

/*
** License store context size
*/
#define MAX_PRILIC_LIST     10

typedef enum _tageDRM_LICENSE_STORE_TYPE
{
    eDRM_LICENSE_STORE_XML  = 1,
    eDRM_LICENSE_STORE_XMR  = 2,
    eDRM_LICENSE_STORE_TEMP = 3    // Added for the PC client
} eDRM_LICENSE_STORE_TYPE;

/*
** License store context stucture.
** This contains the DST namespace context it is using and
** the local stack info for internal use
*/
typedef struct _tagDRM_LICSTORE_CONTEXT
{
    DRM_DST_SLOT_CONTEXT       SlotContext;
    DRM_DST_NAMESPACE_CONTEXT  DstNamespaceContext;
    DRM_DST                   *pDatastore;
    DRM_BOOL                   fInited;
    eDRM_LICENSE_STORE_TYPE    eType;
} DRM_LICSTORE_CONTEXT;

/*
** License store modes
*/
typedef enum _tageDRM_LICENSE_STORE_MODE
{
    /*
    ** no license found
    */
    eDRM_LICENSE_STORE_MODE_NONE                = 0,
    /*
    ** a local list of license's KID and LID is loaded for query
    */
    eDRM_LICENSE_STORE_MODE_PRIORITIZED         = 1,
    /*
    ** enum for licenses matching given KID
    */
    eDRM_LICENSE_STORE_MODE_FILTERED            = 2,
    /*
    ** enum all licenses
    */
    eDRM_LICENSE_STORE_MODE_NATURAL             = 3,
    /*
    ** enum licenses matching KID after eDRM_LICENSE_STORE_MODE_PRIORITIZED exhausted
    */
    eDRM_LICENSE_STORE_MODE_POST_PRIORITIZED    = 4 ,
    /*
    ** enum licenses in reverse priority order
    */
    eDRM_LICENSE_STORE_MODE_REVERSE_PRIORITIZED = 5
} eDRM_LICENSE_STORE_MODE;

/*
** Prioritized license
*/
typedef struct _tagDRM_PRIORITIZED_LICENSE
{
    DRM_DWORD         dwPriority;   /* the higher the value, the higher the priority */
    DRM_LID           LID;
    DRM_BOOL          fDelete;
    DRM_DST_SLOT_HINT slotHint;
} DRM_PRIORITIZED_LICENSE;

/*
** Prioritized license list
*/
typedef struct _tagDRM_PRIORITIZED_LICENSE_LIST
{
    DRM_KID                 KID;
    DRM_DWORD               iNextLicense;
    DRM_DWORD               cLicenses; /* # of license slot used in the array */
    DRM_PRIORITIZED_LICENSE rgPrioritizedList[MAX_PRILIC_LIST + 1]; /* one extra for working buffer */
} DRM_PRIORITIZED_LICENSE_LIST;

/*
** Non-prioritized license
*/
typedef struct _tagDRM_NONPRIORITIZED_LICENSE
{
    DRM_BOOL  fCurrIsValid;
    DRM_KID   CurrKID;
    DRM_LID   CurrLID;
} DRM_NONPRIORITIZED_LICENSE;

/*
** All license list struct for DRM_LICSTOREENUM_CONTEXT
*/
typedef struct _tag_DRM_LICSTOREENUM_LICENSE_LIST
{
    DRM_PRIORITIZED_LICENSE_LIST  Prioritized;
    DRM_NONPRIORITIZED_LICENSE    NonPrioritized;
} DRM_LICSTOREENUM_LICENSE_LIST;

/*
** License Store enumeration context
*/
typedef struct _tag_DRM_LICSTOREENUM_CONTEXT
{
    DRM_LICSTORE_CONTEXT    *pLicContext;
    DRM_DST_ENUM_CONTEXT     DstEnumContext;
    DRM_DST_SLOT_CONTEXT     SlotContext;
    DRM_BOOL                 fInited;
    eDRM_LICENSE_STORE_MODE  eMode;
    DRM_LICSTOREENUM_LICENSE_LIST List; 
} DRM_LICSTOREENUM_CONTEXT;

/*
** The maximum number of stores for multiple enumeration
*/
#define DRM_LICSTORE_MAX_STORES 4

/*
** License Store enumeration context for enumeration
** over multiple stores
*/
typedef struct _tag_DRM_LICSTOREENUM_MULTIPLE_CONTEXT
{
    DRM_LICSTOREENUM_CONTEXT   rgLicContexts[DRM_LICSTORE_MAX_STORES];
    DRM_DWORD                  cLicContexts;

    DRM_BOOL                   fInited;
    eDRM_LICENSE_STORE_MODE    eMode;

    DRM_LICSTOREENUM_CONTEXT  *pCurEnum; /* Pointer to the enumeration context for the next license */

} DRM_LICSTOREENUM_MULTIPLE_CONTEXT;


/*
** API Functions
*/

DRM_API DRM_RESULT DRM_CALL DRM_LST_Open(
    __out DRM_LICSTORE_CONTEXT    *f_pLicContext,
    __in  DRM_DST                 *f_pDatastore,
    __in  eDRM_LICENSE_STORE_TYPE  f_eLicenseStoreType );

DRM_API DRM_RESULT DRM_CALL DRM_LST_Close(
    __in DRM_LICSTORE_CONTEXT *f_pLicContext );

DRM_API DRM_RESULT DRM_CALL DRM_LST_AddLicense(
    __inout                          DRM_LICSTORE_CONTEXT *f_pLicContext,
    __in                             DRM_DWORD             f_cbLicense,
    __in_bcount( f_cbLicense )       DRM_BYTE             *f_pbLicense,
    __in_opt                   const DRM_KID              *f_pKID,
    __in_opt                   const DRM_LID              *f_pLID,
    __in                             DRM_DWORD             f_dwPriority );

DRM_API DRM_RESULT DRM_CALL DRM_LST_GetLicense(
    __in                                    DRM_LICSTORE_CONTEXT *f_pLicContext,
    __in                              const DRM_KID              *f_pKID,
    __in                              const DRM_LID              *f_pLID,
    __in_opt                                DRM_DST_SLOT_HINT    *f_pSlotHint,
    __out_bcount_opt( *f_pcbLicense )       DRM_BYTE             *f_pbLicense,
    __inout                                 DRM_DWORD            *f_pcbLicense );

DRM_API DRM_RESULT DRM_CALL DRM_LST_GetLicensePtr(
    __in                                    DRM_LICSTORE_CONTEXT *f_pLicContext,
    __in                              const DRM_KID              *f_pKID,
    __in                              const DRM_LID              *f_pLID,
    __in_opt                                DRM_DST_SLOT_HINT    *f_pSlotHint,
    __deref_out_bcount( *f_pcbLicense )     DRM_BYTE            **f_ppbLicense,
    __out                                   DRM_DWORD            *f_pcbLicense,
    __out_opt                               DRM_DWORD            *f_pdwPriority );

DRM_API DRM_RESULT DRM_CALL DRM_LST_DeleteLicense(
    __inout        DRM_LICSTORE_CONTEXT *f_pLicContext,
    __in     const DRM_KID              *f_pKID,
    __in     const DRM_LID              *f_pLID,
    __in_opt       DRM_DST_SLOT_HINT    *f_pSlotHint );

DRM_API DRM_RESULT DRM_CALL DRM_LST_UpdateLicense(
    __inout                          DRM_LICSTORE_CONTEXT     *f_pLicContext,
    __in                             DRM_DWORD                 f_cbLicense,
    __in_bcount( f_cbLicense ) const DRM_BYTE                 *f_pbLicense,
    __in                       const DRM_KID                  *f_pKID,
    __in                       const DRM_LID                  *f_pLID,
    __in                             DRM_DWORD                 f_dwPriority,
    __in_opt                         DRM_DST_SLOT_HINT        *f_pSlotHint );

DRM_API DRM_RESULT DRM_CALL DRM_LST_DeleteLicenseAndSaveDate(
    __inout        DRM_LICSTORE_CONTEXT *f_pLicContext,
    __in     const DRM_KID              *f_pKID,
    __in     const DRM_LID              *f_pLID,
    __in_opt       DRM_DST_SLOT_HINT    *f_pSlotHint,
    __in           DRM_BOOL              f_fSaveDate );

DRM_API DRM_RESULT DRM_CALL DRM_LST_InitEnum(
    __in            DRM_LICSTORE_CONTEXT     *f_pLicContext,
    __in_opt  const DRM_KID                  *f_pKID,
    __in            DRM_BOOL                  f_fPrioritized,
    __out           DRM_LICSTOREENUM_CONTEXT *f_pLicEnumContext );

DRM_API DRM_RESULT DRM_CALL DRM_LST_InitReverseEnum(
    __in        DRM_LICSTORE_CONTEXT     *f_pLicContext,
    __in  const DRM_KID                  *f_pKID,
    __out       DRM_LICSTOREENUM_CONTEXT *f_pLicEnumContext );

DRM_API DRM_RESULT DRM_CALL DRM_LST_EnumNext(
    __in      DRM_LICSTOREENUM_CONTEXT *f_pLicEnumContext,
    __out_opt DRM_KID                 *f_pKID,
    __out     DRM_LID                 *f_pLID,
    __out_opt DRM_DST_SLOT_HINT       *f_pSlotHint,
    __out_opt DRM_DWORD               *f_pcbLicense );

DRM_API DRM_RESULT DRM_CALL DRM_LST_EnumDelete( __in DRM_LICSTOREENUM_CONTEXT *f_pLicEnumContext );

DRM_API DRM_RESULT DRM_CALL DRM_LST_EnumDeleteAndSaveDate(
    __in DRM_LICSTOREENUM_CONTEXT *f_pLicEnumContext,
    __in DRM_BOOL                  f_fSaveDate );

DRM_API DRM_RESULT DRM_CALL DRM_LST_LicCount(
    __in    DRM_LICSTOREENUM_CONTEXT *f_pLicEnumContext,
    __out   DRM_DWORD                *f_pcLicenses );

DRM_API DRM_RESULT DRM_CALL DRM_LST_InitEnumMultiple(
    __in_ecount( f_cLicContexts )       DRM_LICSTORE_CONTEXT              *f_prgbLicContexts[],
    __in                                DRM_DWORD                          f_cLicContexts,
    __in_opt                      const DRM_KID                           *f_pKID,
    __in                                DRM_BOOL                           f_fPrioritized,
    __out                               DRM_LICSTOREENUM_MULTIPLE_CONTEXT *f_pLicEnumContext );

DRM_API DRM_RESULT DRM_CALL DRM_LST_EnumNextMultiple(
    __in       DRM_LICSTOREENUM_MULTIPLE_CONTEXT *f_pLicEnumContext,
    __out_opt  DRM_KID                           *f_pKID,
    __out_opt  DRM_LID                           *f_pLID,
    __out_opt  DRM_LICSTORE_CONTEXT             **f_ppLicStore,
    __out_opt  DRM_DST_SLOT_HINT                 *f_pSlotHint,
    __out_opt  DRM_DWORD                         *f_pcbLicense );

DRM_API DRM_RESULT DRM_CALL DRM_LST_EnumDeleteMultiple( __in DRM_LICSTOREENUM_MULTIPLE_CONTEXT *f_pLicEnumContext );

/**********************************************************************
**
** Function :   pfnStoreCleanupProgress
**
** Synopsis :   Callback function to report progress during License
**              store cleanup
**
** Arguments :
**      [f_pvCallerData]       : Opaque context data provided to DRM_LST_Clean
**      [f_cLicensesProcessed] : Count of licenses processed
**      [f_cTotalLicenses]     : Count of total licenses in the store
**
** Returns :
**      DRM_SUCCESS
**          Success
**
**********************************************************************/
typedef DRM_RESULT ( DRM_CALL *pfnStoreCleanupProgress )(
    __in  const DRM_VOID    *f_pvCallerData,
    __in        DRM_DWORD    f_cLicensesProcessed,
    __in        DRM_DWORD    f_cTotalLicenses );

DRM_API DRM_RESULT DRM_CALL DRM_LST_Clean(
    __in                        DRM_BYTE                  *f_pContextLEVL,
    __in_bcount( SIZEOF( DRM_LICSTORE_CONTEXT ) )
                                DRM_BYTE                  *f_pContextLSTXML,
    __in_bcount( SIZEOF( DRM_LICSTORE_CONTEXT ) )
                                DRM_BYTE                  *f_pContextLSTXMR,
    __in                        DRM_LICSTOREENUM_CONTEXT  *f_pLicStoreEnumContext,
    __in                        DRM_DWORD                  f_dwFlags,
    __in_bcount(f_cbBuffer )    DRM_BYTE                  *f_pbBuffer,
    __in                        DRM_DWORD                  f_cbBuffer,
    __in_opt              const DRM_VOID                  *f_pvCallerData,
    __in                        DRM_DWORD                  f_dwCallbackInterval,
    __in_opt                    pfnStoreCleanupProgress    f_pfnCallback,
    __in                        DRM_DST                   *f_pDatastore );

EXIT_PK_NAMESPACE;

#endif  /* __DRM_LICSTORE_H__ */


