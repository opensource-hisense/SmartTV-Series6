/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef _DRMMOVEFORMAT_H_
#define _DRMMOVEFORMAT_H_ 1

#include <drmxbbuilder.h>
#include <oemcryptoctx.h>

ENTER_PK_NAMESPACE;

enum MOVE_PAGE_ENTRY_TYPES
{
    MP_ENTRY_TYPE_BASIC_INFORMATION    = XB_OBJECT_GLOBAL_HEADER+1,
    MP_ENTRY_TYPE_LID_LIST,
    MP_ENTRY_TYPE_MAX_DEFINED
};

typedef DRM_XB_GUIDLIST MOVE_LID_LIST;

typedef struct __tagMOVE_PAGE_BASIC_INFORMATION
{
    DRM_BOOL  fValid;
    DRM_DWORD dwSerialNumber;
    DRM_DWORD dwPageNumber;
} MOVE_PAGE_BASIC_INFORMATION;

typedef struct __tagDRM_MOVE_PAGE
{
    DRM_BOOL                    fValid;
    MOVE_PAGE_BASIC_INFORMATION BasicInformation;
    MOVE_LID_LIST               LidList;
} DRM_MOVE_PAGE;

enum MOVE_INDEX_ENTRY_TYPES
{
    MI_ENTRY_TYPE_BASIC_INFORMATION    = XB_OBJECT_GLOBAL_HEADER+1,
    MI_ENTRY_TYPE_PAGE_DESCRIPTOR,
    MI_ENTRY_TYPE_PAGE_LIST,
    MI_ENTRY_TYPE_SIGNATURE,
    MI_ENTRY_TYPE_MAX_DEFINED
};


typedef struct __tagMOVE_INDEX_BASIC_INFORMATION
{
    DRM_BOOL           fValid;
    DRM_DWORD          dwSerialNumber;
    DRM_XB_BYTEARRAY   xbbaClientId;
} MOVE_INDEX_BASIC_INFORMATION;

typedef struct __tagDRM_MOVE_PAGE_DESCRIPTOR
{
    DRM_BOOL           fValid;
    struct __tagDRM_MOVE_PAGE_DESCRIPTOR *pNext;

    DRM_DWORD          dwSerialNumber;
    DRM_DWORD          dwPageNumber;
    DRM_DWORD          dwPageHashType;
    DRM_XB_BYTEARRAY   xbbaHash;
} DRM_MOVE_PAGE_DESCRIPTOR;

typedef struct __tagDRM_MOVE_PAGE_LIST
{
    DRM_BOOL                  fValid;
    DRM_MOVE_PAGE_DESCRIPTOR *pHead;
} DRM_MOVE_PAGE_LIST;

typedef struct __tagDRM_MOVE_INDEX_SIGNATURE
{
    DRM_BOOL                  fValid;
    DRM_WORD                  wSignatureType;
    DRM_XB_BYTEARRAY          xbbaSignature;
    DRM_XB_BYTEARRAY          xbbaValidaingPubKey;
} DRM_MOVE_INDEX_SIGNATURE;

typedef struct __tagDRM_MOVE_INDEX
{
    DRM_BOOL                     fValid;
    MOVE_INDEX_BASIC_INFORMATION BasicInformation;
    DRM_MOVE_PAGE_LIST           PageList;
    DRM_MOVE_INDEX_SIGNATURE     Signature;
} DRM_MOVE_INDEX;


/* Use DRM_MOV_Page_Start to begin the building of a move page.  Add object to the move page using
   DRM_XB_AddObject */
DRM_API DRM_RESULT DRM_CALL DRM_MOV_Page_Start(
    __inout_bcount( f_cbStack ) DRM_BYTE                *f_pbStack,
    __in                        DRM_DWORD                f_cbStack,
    __inout_ecount( 1 )         DRM_XB_BUILDER_CONTEXT  *f_pcontextBuilder );

DRM_API DRM_RESULT DRM_CALL DRM_MOV_Page_Finish(
    __inout_ecount( 1 )            const DRM_XB_BUILDER_CONTEXT  *f_pcontextBuilder,
    __inout_bcount(*f_pcbMovePage)       DRM_BYTE                *f_pbMovePage,
    __inout                              DRM_DWORD               *f_pcbMovePage );

DRM_API DRM_RESULT DRM_CALL DRM_MP_ParsePage(
    __inout_bcount( f_cbStack )       DRM_BYTE                *f_pbStack,
    __in                              DRM_DWORD                f_cbStack,
    __inout_bcount( f_cbStack ) const DRM_BYTE                *f_pbPage,
    __in                              DRM_DWORD                f_cbPage,
    __out                             DRM_MOVE_PAGE           *f_pPage );

/* Use DRM_MOV_Index_Start to begin the building of a move page.  Add object to the move page using
   DRM_XB_AddObject */
DRM_API DRM_RESULT DRM_CALL DRM_MOV_Index_Start(
    __inout_bcount( f_cbStack ) DRM_BYTE                *f_pbStack,
    __in                        DRM_DWORD                f_cbStack,
    __inout_ecount( 1 )         DRM_XB_BUILDER_CONTEXT  *f_pcontextBuilder );


typedef DRM_RESULT ( DRM_CALL *DRM_MOV_CB_SIGNATURE )(
    __in_ecount( 1 )        const                            DRM_VOID  *f_pvSignatureContext,
    __in_bcount( f_cbData )                                  DRM_BYTE  *f_pbData,
    __in                                                     DRM_DWORD  f_cbData,
    __out_bcount( f_cbSignatureBuffer )                      DRM_BYTE  *f_pbSignatureBuffer,
    __in                                                     DRM_DWORD  f_cbSignatureBuffer,
    __in                                                     DRM_DWORD  f_iSignatureBuffer,
    __out_bcount( f_cbPublicKeyBuffer )                      DRM_BYTE  *f_pbPublicKeyBuffer,
    __in                                                     DRM_DWORD  f_cbPublicKeyBuffer,
    __in                                                     DRM_DWORD  f_iPublicKeyBuffer );

DRM_API DRM_RESULT DRM_CALL DRM_MOV_Index_Finish(
    __inout_ecount( 1 )             const DRM_XB_BUILDER_CONTEXT  *f_pcontextBuilder,
    __inout_bcount(*f_pcbMoveIndex)       DRM_BYTE                *f_pbMoveIndex,
    __inout                               DRM_DWORD               *f_pcbMoveIndex,
    __in                                  DRM_MOV_CB_SIGNATURE     f_pfnSignatureCallback,
    __in                            const DRM_VOID                *f_pvSignatureContext );

DRM_API DRM_RESULT DRM_CALL DRM_MI_ParseIndex(
    __inout_bcount( f_cbStack )       DRM_BYTE                *f_pbStack,
    __in                              DRM_DWORD                f_cbStack,
    __inout_bcount( f_cbStack ) const DRM_BYTE                *f_pbIndex,
    __in                              DRM_DWORD                f_cbIndex,
    __out                             DRM_MOVE_INDEX          *f_pIndex);

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_MOV_ParseIndex(
    __inout_bcount( f_cbStack )       DRM_BYTE                *f_pbStack,
    __in                              DRM_DWORD                f_cbStack,
    __inout_bcount( f_cbStack ) const DRM_BYTE                *f_pbIndex,
    __in                              DRM_DWORD                f_cbIndex,
    __out                             DRM_MOVE_INDEX          *f_pIndex,
    __inout                           DRM_BYTE                 f_rgbCryptoContext[__CB_DECL(DRM_PKCRYPTO_CONTEXT_BUFFER_SIZE)]) DRM_NO_INLINE_ATTRIBUTE;


EXIT_PK_NAMESPACE;

#endif /* _DRMMOVEFORMAT_H_ */
