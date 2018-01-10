/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRM_XMR_PARSER_H__
#define __DRM_XMR_PARSER_H__

#include <drmxmr.h>
#include <drmstkalloc.h>

ENTER_PK_NAMESPACE;

DRM_API DRM_RESULT DRM_CALL DRM_XMR_UnpackLicense(
    __in_bcount( f_cbLicense ) const DRM_BYTE                    *f_pbLicense,
    __in                             DRM_DWORD                    f_cbLicense,
    __in                             DRM_STACK_ALLOCATOR_CONTEXT *f_pStack,
    __out                            DRM_XMR_LICENSE             *f_pXmrLicense );

DRM_API DRM_RESULT DRM_CALL DRM_XMR_GetContainer(
    __in    const DRM_BYTE                     *f_pbLicense,
    __in          DRM_DWORD                     f_cbLicense,
    __in          DRM_WORD                      f_wContainerType,
    __in          DRM_STACK_ALLOCATOR_CONTEXT  *f_pstack,
    __inout       DRM_VOID                     *f_pvContainer );

DRM_API DRM_RESULT DRM_CALL DRM_XMR_PopulateInclusionList(
    __in                                    const DRM_XMR_INCLUSION_LIST *f_pInclusionList,
    __inout_ecount(DRM_MAX_INCLUSION_GUIDS)       DRM_GUID                f_rgInclusionList[DRM_MAX_INCLUSION_GUIDS],
    __inout_ecount(DRM_MAX_INCLUSION_GUIDS)       DRM_BOOL                f_rgfGuidValid[DRM_MAX_INCLUSION_GUIDS][DRM_MAX_LICENSE_CHAIN_DEPTH],
    __in                                          DRM_DWORD               f_dwChainDepth );

/******************************************************************************
**
** Function :   DRM_XMR_ValidateLicenseObjects
**
** Synopsis :   Determines if the objects in the given license conform
**                  to the XMR specification based on the license's version
**
** Arguments :
**      [f_pXmrLicense]   : License to validate
**
** Returns :    DRM_SUCCESS             if the license is valid
**              DRM_E_INVALID_LICENSE    if the license is not valid
**              DRM_E_INVALIDARG        if f_pXmrLicense is NULL
**
******************************************************************************/
DRM_API DRM_RESULT DRM_CALL DRM_XMR_ValidateLicenseObjects(
    __in const DRM_XMR_LICENSE *f_pXmrLicense );

/******************************************************************************
**
** Function :   DRM_XMR_PARSE
**
** Synopsis :   Function Prototype to parse a serialized object buffer
**
** Arguments :
**      [f_pStack]   : Stack for intermediate usage
**      [f_pbBuffer] : Object Buffer
**      [f_iObject]  : Index marking beginning of object in the buffer
**      [f_cbObject] : Size of serialized object
**      [f_pvObject] : Actual object returned as void
**
** Returns :
**
** Notes :      Callers must keep the stack around as long as they use the
**              contents of the structure returned. The structure might have
**              some intermediate nodes allocated out of this stack
**
******************************************************************************/
typedef DRM_RESULT  ( DRM_CALL *DRM_XMR_PARSE )(
    __in          DRM_STACK_ALLOCATOR_CONTEXT *f_pStack,
    __in    const DRM_BYTE                    *f_pbBuffer,
    __in          DRM_DWORD                    f_iObject,
    __in          DRM_DWORD                    f_cbObject,
    __inout       DRM_VOID                    *f_pvObject );

DRM_API DRM_RESULT DRM_CALL DRM_XMR_Parse_Invalid(
    __in          DRM_STACK_ALLOCATOR_CONTEXT *f_pStack,
    __in    const DRM_BYTE                    *f_pbBuffer,
    __in          DRM_DWORD                    f_iObject,
    __in          DRM_DWORD                    f_cbObject,
    __inout       DRM_VOID                    *f_pvObject );

DRM_API DRM_RESULT DRM_CALL DRM_XMR_Parse_MinimumEnvironment(
    __in          DRM_STACK_ALLOCATOR_CONTEXT *f_pStack,
    __in    const DRM_BYTE                    *f_pbBuffer,
    __in          DRM_DWORD                    f_iObject,
    __in          DRM_DWORD                    f_cbObject,
    __inout       DRM_VOID                    *f_pvObject );

DRM_API DRM_RESULT DRM_CALL DRM_XMR_Parse_SecurityLevel(
    __in          DRM_STACK_ALLOCATOR_CONTEXT *f_pStack,
    __in    const DRM_BYTE                    *f_pbBuffer,
    __in          DRM_DWORD                    f_iObject,
    __in          DRM_DWORD                    f_cbObject,
    __inout       DRM_VOID                    *f_pvObject );

DRM_API DRM_RESULT DRM_CALL DRM_XMR_Parse_OPLs(
    __in          DRM_STACK_ALLOCATOR_CONTEXT *f_pStack,
    __in    const DRM_BYTE                    *f_pbBuffer,
    __in          DRM_DWORD                    f_iObject,
    __in          DRM_DWORD                    f_cbObject,
    __inout       DRM_VOID                    *f_pvObject );

DRM_API DRM_RESULT DRM_CALL DRM_XMR_Parse_Empty(
    __in          DRM_STACK_ALLOCATOR_CONTEXT *f_pStack,
    __in    const DRM_BYTE                    *f_pbBuffer,
    __in          DRM_DWORD                    f_iObject,
    __in          DRM_DWORD                    f_cbObject,
    __inout       DRM_VOID                    *f_pvObject );

DRM_API DRM_RESULT DRM_CALL DRM_XMR_Parse_UnknownContainer(
    __in          DRM_STACK_ALLOCATOR_CONTEXT *f_pStack,
    __in    const DRM_BYTE                    *f_pbBuffer,
    __in          DRM_DWORD                    f_iObject,
    __in          DRM_DWORD                    f_cbObject,
    __inout       DRM_VOID                    *f_pvObject );

DRM_API DRM_RESULT DRM_CALL DRM_XMR_Parse_UnknownObject(
    __in          DRM_STACK_ALLOCATOR_CONTEXT *f_pStack,
    __in    const DRM_BYTE                    *f_pbBuffer,
    __in          DRM_DWORD                    f_iObject,
    __in          DRM_DWORD                    f_cbObject,
    __inout       DRM_VOID                    *f_pvObject );

DRM_API DRM_RESULT DRM_CALL DRM_XMR_Parse_WORD(
    __in          DRM_STACK_ALLOCATOR_CONTEXT *f_pStack,
    __in    const DRM_BYTE                    *f_pbBuffer,
    __in          DRM_DWORD                    f_iObject,
    __in          DRM_DWORD                    f_cbObject,
    __inout       DRM_VOID                    *f_pvObject );

DRM_API DRM_RESULT DRM_CALL DRM_XMR_Parse_DWORD_Versioned(
    __in          DRM_STACK_ALLOCATOR_CONTEXT *f_pStack,
    __in    const DRM_BYTE                    *f_pbBuffer,
    __in          DRM_DWORD                    f_iObject,
    __in          DRM_DWORD                    f_cbObject,
    __inout       DRM_VOID                    *f_pvObject );

DRM_API DRM_RESULT DRM_CALL DRM_XMR_Parse_DWORD(
    __in          DRM_STACK_ALLOCATOR_CONTEXT *f_pStack,
    __in    const DRM_BYTE                    *f_pbBuffer,
    __in          DRM_DWORD                    f_iObject,
    __in          DRM_DWORD                    f_cbObject,
    __inout       DRM_VOID                    *f_pvObject );

DRM_API DRM_RESULT DRM_CALL DRM_XMR_Parse_GUID(
    __in          DRM_STACK_ALLOCATOR_CONTEXT *f_pStack,
    __in    const DRM_BYTE                    *f_pbBuffer,
    __in          DRM_DWORD                    f_iObject,
    __in          DRM_DWORD                    f_cbObject,
    __inout       DRM_VOID                    *f_pvObject );

DRM_API DRM_RESULT DRM_CALL DRM_XMR_Parse_GUIDLIST(
    __in          DRM_STACK_ALLOCATOR_CONTEXT *f_pStack,
    __in    const DRM_BYTE                    *f_pbBuffer,
    __in          DRM_DWORD                    f_iObject,
    __in          DRM_DWORD                    f_cbObject,
    __inout       DRM_VOID                    *f_pvObject );

DRM_API DRM_RESULT DRM_CALL DRM_XMR_Parse_BYTEARRAY(
    __in          DRM_STACK_ALLOCATOR_CONTEXT *f_pStack,
    __in    const DRM_BYTE                    *f_pbBuffer,
    __in          DRM_DWORD                    f_iObject,
    __in          DRM_DWORD                    f_cbObject,
    __inout       DRM_VOID                    *f_pvObject );

DRM_API DRM_RESULT DRM_CALL DRM_XMR_Parse_DomainID(
    __in          DRM_STACK_ALLOCATOR_CONTEXT *f_pStack,
    __in    const DRM_BYTE                    *f_pbBuffer,
    __in          DRM_DWORD                    f_iObject,
    __in          DRM_DWORD                    f_cbObject,
    __inout       DRM_VOID                    *f_pvObject );

DRM_API DRM_RESULT DRM_CALL DRM_XMR_Parse_VideoOutputConfig(
    __in          DRM_STACK_ALLOCATOR_CONTEXT *f_pStack,
    __in    const DRM_BYTE                    *f_pbBuffer,
    __in          DRM_DWORD                    f_iObject,
    __in          DRM_DWORD                    f_cbObject,
    __inout       DRM_VOID                    *f_pvObject );

DRM_API DRM_RESULT DRM_CALL DRM_XMR_Parse_AudioOutputConfig(
    __in          DRM_STACK_ALLOCATOR_CONTEXT *f_pStack,
    __in    const DRM_BYTE                    *f_pbBuffer,
    __in          DRM_DWORD                    f_iObject,
    __in          DRM_DWORD                    f_cbObject,
    __inout       DRM_VOID                    *f_pvObject );

DRM_API DRM_RESULT DRM_CALL DRM_XMR_Parse_ContentKey(
    __in          DRM_STACK_ALLOCATOR_CONTEXT *f_pStack,
    __in    const DRM_BYTE                    *f_pbBuffer,
    __in          DRM_DWORD                    f_iObject,
    __in          DRM_DWORD                    f_cbObject,
    __inout       DRM_VOID                    *f_pvObject );

DRM_API DRM_RESULT DRM_CALL DRM_XMR_Parse_Expiration(
    __in          DRM_STACK_ALLOCATOR_CONTEXT *f_pStack,
    __in    const DRM_BYTE                    *f_pbBuffer,
    __in          DRM_DWORD                    f_iObject,
    __in          DRM_DWORD                    f_cbObject,
    __inout       DRM_VOID                    *f_pvObject );

DRM_API DRM_RESULT DRM_CALL DRM_XMR_Parse_PlaylistBurnRights(
    __in          DRM_STACK_ALLOCATOR_CONTEXT *f_pStack,
    __in    const DRM_BYTE                    *f_pbBuffer,
    __in          DRM_DWORD                    f_iObject,
    __in          DRM_DWORD                    f_cbObject,
    __inout       DRM_VOID                    *f_pvObject );

DRM_API DRM_RESULT DRM_CALL DRM_XMR_Parse_RsaPubkey(
    __in          DRM_STACK_ALLOCATOR_CONTEXT *f_pStack,
    __in    const DRM_BYTE                    *f_pbBuffer,
    __in          DRM_DWORD                    f_iObject,
    __in          DRM_DWORD                    f_cbObject,
    __inout       DRM_VOID                    *f_pvObject );

DRM_API DRM_RESULT DRM_CALL DRM_XMR_Parse_EccDevicekey(
    __in          DRM_STACK_ALLOCATOR_CONTEXT *f_pStack,
    __in    const DRM_BYTE                    *f_pbBuffer,
    __in          DRM_DWORD                    f_iObject,
    __in          DRM_DWORD                    f_cbObject,
    __inout       DRM_VOID                    *f_pvObject );

DRM_API DRM_RESULT DRM_CALL DRM_XMR_Parse_UserID(
    __in          DRM_STACK_ALLOCATOR_CONTEXT *f_pStack,
    __in    const DRM_BYTE                    *f_pbBuffer,
    __in          DRM_DWORD                    f_iObject,
    __in          DRM_DWORD                    f_cbObject,
    __inout       DRM_VOID                    *f_pvObject );

DRM_API DRM_RESULT DRM_CALL DRM_XMR_Parse_UplinkKID(
    __in          DRM_STACK_ALLOCATOR_CONTEXT *f_pStack,
    __in    const DRM_BYTE                    *f_pbBuffer,
    __in          DRM_DWORD                    f_iObject,
    __in          DRM_DWORD                    f_cbObject,
    __inout       DRM_VOID                    *f_pvObject );

DRM_API DRM_RESULT DRM_CALL DRM_XMR_Parse_UplinkKID2(
    __in          DRM_STACK_ALLOCATOR_CONTEXT *f_pStack,
    __in    const DRM_BYTE                    *f_pbBuffer,
    __in          DRM_DWORD                    f_iObject,
    __in          DRM_DWORD                    f_cbObject,
    __inout       DRM_VOID                    *f_pvObject );

DRM_API DRM_RESULT DRM_CALL DRM_XMR_Parse_OuterContainer(
    __in          DRM_STACK_ALLOCATOR_CONTEXT *f_pStack,
    __in    const DRM_BYTE                    *f_pbBuffer,
    __in          DRM_DWORD                    f_iObject,
    __in          DRM_DWORD                    f_cbObject,
    __inout       DRM_VOID                    *f_pvObject );

DRM_API DRM_RESULT DRM_CALL DRM_XMR_Parse_GlobalContainer(
    __in          DRM_STACK_ALLOCATOR_CONTEXT *f_pStack,
    __in    const DRM_BYTE                    *f_pbBuffer,
    __in          DRM_DWORD                    f_iObject,
    __in          DRM_DWORD                    f_cbObject,
    __inout       DRM_VOID                    *f_pvObject );

DRM_API DRM_RESULT DRM_CALL DRM_XMR_Parse_PlaybackContainer(
    __in          DRM_STACK_ALLOCATOR_CONTEXT *f_pStack,
    __in    const DRM_BYTE                    *f_pbBuffer,
    __in          DRM_DWORD                    f_iObject,
    __in          DRM_DWORD                    f_cbObject,
    __inout       DRM_VOID                    *f_pvObject );

DRM_API DRM_RESULT DRM_CALL DRM_XMR_Parse_ExplicitAnalogVideoOutputProtectionContainer(
    __in          DRM_STACK_ALLOCATOR_CONTEXT *f_pStack,
    __in    const DRM_BYTE                    *f_pbBuffer,
    __in          DRM_DWORD                    f_iObject,
    __in          DRM_DWORD                    f_cbObject,
    __inout       DRM_VOID                    *f_pvObject );

DRM_API DRM_RESULT DRM_CALL DRM_XMR_Parse_ExplicitDigitalAudioOutputProtectionContainer(
    __in          DRM_STACK_ALLOCATOR_CONTEXT *f_pStack,
    __in    const DRM_BYTE                    *f_pbBuffer,
    __in          DRM_DWORD                    f_iObject,
    __in          DRM_DWORD                    f_cbObject,
    __inout       DRM_VOID                    *f_pvObject );

DRM_API DRM_RESULT DRM_CALL DRM_XMR_Parse_PolicyMetadata(
    __in          DRM_STACK_ALLOCATOR_CONTEXT *f_pStack,
    __in    const DRM_BYTE                    *f_pbBuffer,
    __in          DRM_DWORD                    f_iObject,
    __in          DRM_DWORD                    f_cbObject,
    __inout       DRM_VOID                    *f_pvObject );

DRM_API DRM_RESULT DRM_CALL DRM_XMR_Parse_RevocationContainer(
    __in          DRM_STACK_ALLOCATOR_CONTEXT *f_pStack,
    __in    const DRM_BYTE                    *f_pbBuffer,
    __in          DRM_DWORD                    f_iObject,
    __in          DRM_DWORD                    f_cbObject,
    __inout       DRM_VOID                    *f_pvObject );

DRM_API DRM_RESULT DRM_CALL DRM_XMR_Parse_KeyMaterialContainer(
    __in          DRM_STACK_ALLOCATOR_CONTEXT *f_pStack,
    __in    const DRM_BYTE                    *f_pbBuffer,
    __in          DRM_DWORD                    f_iObject,
    __in          DRM_DWORD                    f_cbObject,
    __inout       DRM_VOID                    *f_pvObject );

DRM_API DRM_RESULT DRM_CALL DRM_XMR_Parse_Signature(
    __in          DRM_STACK_ALLOCATOR_CONTEXT *f_pStack,
    __in    const DRM_BYTE                    *f_pbBuffer,
    __in          DRM_DWORD                    f_iObject,
    __in          DRM_DWORD                    f_cbObject,
    __inout       DRM_VOID                    *f_pvObject );

DRM_API DRM_RESULT DRM_CALL DRM_XMR_Parse_CopyToPCContainer(
    __in          DRM_STACK_ALLOCATOR_CONTEXT *f_pStack,
    __in    const DRM_BYTE                    *f_pbBuffer,
    __in          DRM_DWORD                    f_iObject,
    __in          DRM_DWORD                    f_cbObject,
    __inout       DRM_VOID                    *f_pvObject );

DRM_API DRM_RESULT DRM_CALL DRM_XMR_Parse_CopyContainer(
    __in          DRM_STACK_ALLOCATOR_CONTEXT *f_pStack,
    __in    const DRM_BYTE                    *f_pbBuffer,
    __in          DRM_DWORD                    f_iObject,
    __in          DRM_DWORD                    f_cbObject,
    __inout       DRM_VOID                    *f_pvObject );

DRM_API DRM_RESULT DRM_CALL DRM_XMR_Parse_PlaylistBurnContainer(
    __in          DRM_STACK_ALLOCATOR_CONTEXT *f_pStack,
    __in    const DRM_BYTE                    *f_pbBuffer,
    __in          DRM_DWORD                    f_iObject,
    __in          DRM_DWORD                    f_cbObject,
    __inout       DRM_VOID                    *f_pvObject );

DRM_API DRM_RESULT DRM_CALL DRM_XMR_Parse_OptimizedContentKey(
    __in          DRM_STACK_ALLOCATOR_CONTEXT *f_pStack,
    __in    const DRM_BYTE                    *f_pbBuffer,
    __in          DRM_DWORD                    f_iObject,
    __in          DRM_DWORD                    f_cbObject,
    __inout       DRM_VOID                    *f_pvObject );

DRM_API DRM_RESULT DRM_CALL DRM_XMR_Parse_RemovalDate(
    __in          DRM_STACK_ALLOCATOR_CONTEXT *f_pStack,
    __in    const DRM_BYTE                    *f_pbBuffer,
    __in          DRM_DWORD                    f_iObject,
    __in          DRM_DWORD                    f_cbObject,
    __inout       DRM_VOID                    *f_pvObject );

DRM_API DRM_RESULT DRM_CALL DRM_XMR_Parse_AuxKey(
    __in          DRM_STACK_ALLOCATOR_CONTEXT *f_pStack,
    __in    const DRM_BYTE                    *f_pbBuffer,
    __in          DRM_DWORD                    f_iObject,
    __in          DRM_DWORD                    f_cbObject,
    __inout       DRM_VOID                    *f_pvObject );

DRM_API DRM_RESULT DRM_CALL DRM_XMR_Parse_UplinkX(
    __in          DRM_STACK_ALLOCATOR_CONTEXT *f_pStack,
    __in    const DRM_BYTE                    *f_pbBuffer,
    __in          DRM_DWORD                    f_iObject,
    __in          DRM_DWORD                    f_cbObject,
    __inout       DRM_VOID                    *f_pvObject );

DRM_API DRM_RESULT DRM_CALL DRM_XMR_Parse_NDTXAuthContainer(
    __in          DRM_STACK_ALLOCATOR_CONTEXT *f_pStack,
    __in    const DRM_BYTE                    *f_pbBuffer,
    __in          DRM_DWORD                    f_iObject,
    __in          DRM_DWORD                    f_cbObject,
    __inout       DRM_VOID                    *f_pvObject );

DRM_API DRM_RESULT DRM_CALL DRM_XMR_Parse_NDTXAuthObject(
    __in          DRM_STACK_ALLOCATOR_CONTEXT *f_pStack,
    __in    const DRM_BYTE                    *f_pbBuffer,
    __in          DRM_DWORD                    f_iObject,
    __in          DRM_DWORD                    f_cbObject,
    __inout       DRM_VOID                    *f_pvObject );

DRM_API DRM_RESULT DRM_CALL DRM_XMR_FindObject(
    __in                             DRM_WORD   f_wObjectType,
    __in_bcount( f_cbLicense ) const DRM_BYTE  *f_pbLicense,
    __in                             DRM_DWORD  f_cbLicense,
    __out                            DRM_DWORD *f_piObject,
    __out                            DRM_DWORD *f_pcbObject );

DRM_API DRM_RESULT DRM_CALL DRM_XMR_UpdateLicenseSizeForSymmKey(
    __inout_bcount( f_cbLicense )     DRM_BYTE                      *f_pbLicense,
    __in                              DRM_DWORD                      f_cbLicense,
    __inout_ecount( 1 )               DRM_DWORD                     *f_pcbLicenseUsed,
    __in                              DRM_DWORD                     *f_pdwInsertionPoint );

DRM_API DRM_RESULT DRM_CALL DRM_XMR_RequiresSST(
    __in  const DRM_XMR_LICENSE *f_pXmrLicense,
    __out       DRM_BOOL        *f_pfRequiresSST );

typedef struct
{
    DRM_XMR_PARSE           fnParse;
    DRM_BOOL                rgfIsVersionSupported[XMR_VERSION_MAX];
} XMR_PARSER_INTERNAL_DEFINES;

EXIT_PK_NAMESPACE;

#endif  /* __DRM_XMR_PARSER_H__ */

