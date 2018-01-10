/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __M2TSBUFFERMGR_H__
#define __M2TSBUFFERMGR_H__ 1

#include <drmm2tstypes.h>

ENTER_PK_NAMESPACE_CODE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_M2TS_MemAllocEncryptorContext(
    __in                                      const DRM_DWORD                                f_cbMaxHeapAllowed,                            
    __deref_out                                     DRM_M2TS_ENCRYPTOR_CONTEXT             **f_ppEncContext ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_VOID * DRM_CALL DRM_M2TS_MemAlloc(
    __inout                                         DRM_M2TS_ENCRYPTOR_CONTEXT              *f_pEncContext, 
    __in                                      const DRM_DWORD                                f_cbSize ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_M2TS_MemFree(
    __inout                                         DRM_M2TS_ENCRYPTOR_CONTEXT              *f_pEncContext, 
    __inout                                         DRM_VOID                                *f_pv,
    __in                                      const DRM_DWORD                                f_cbSize ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_M2TS_MemAllocAndCopy(
    __inout                                         DRM_M2TS_ENCRYPTOR_CONTEXT              *f_pEncContext, 
    __in                                      const DRM_DWORD                                f_cbUnitSize,
    __in                                      const DRM_DWORD                                f_cCurrentUnits,
    __in                                      const DRM_DWORD                                f_cIncUnits,
    __in_opt                                  const DRM_VOID                                *f_pvIn,
    __deref_out                                     DRM_VOID                               **f_ppvOut ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_M2TS_InitPackets( 
    __inout                                         DRM_M2TS_ENCRYPTOR_CONTEXT              *f_pEncContext, 
    __in                                      const DRM_DWORD                                f_cRequested ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_M2TS_InitECMs( 
    __inout                                         DRM_M2TS_ENCRYPTOR_CONTEXT              *f_pEncContext, 
    __in                                      const DRM_DWORD                                f_cRequested ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_M2TS_CreateRemovablePID(
    __inout                                         DRM_M2TS_ENCRYPTOR_CONTEXT              *f_pEncContext,
    __in                                      const DRM_WORD                                 f_wPIDRemovable ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_M2TS_CreateStream(
    __inout                                         DRM_M2TS_ENCRYPTOR_CONTEXT              *f_pEncContext, 
    __in                                      const DRM_WORD                                 f_wPID,
    __in                                      const DRM_M2TS_PACKET_TYPE                     f_ePacketType,
    __out_ecount_opt( 1 )                           DRM_M2TS_STREAM                        **f_ppStream ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_M2TS_GetStream(
    __inout                                         DRM_M2TS_ENCRYPTOR_CONTEXT              *f_pEncContext, 
    __in                                      const DRM_WORD                                 f_wPID,
    __out_ecount( 1 )                               DRM_M2TS_STREAM                        **f_ppStream ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_M2TS_GetFreePacket(
    __inout                                         DRM_M2TS_ENCRYPTOR_CONTEXT              *f_pEncContext,
    __in                                      const DRM_BYTE                                 f_cbPayload,
    __in                                      const DRM_M2TS_PACKET_STATE                    f_ePacketState,
    __in                                      const DRM_BOOL                                 f_fIncludePacketNumber,
    __in_bcount_opt( DRM_M2TS_PACKET_SIZE )   const DRM_BYTE                                *f_pbPacketData,
    __out_ecount( 1 )                               DRM_M2TS_PACKET                        **f_ppPacket ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_M2TS_GetFreeECM(
    __inout                                         DRM_M2TS_ENCRYPTOR_CONTEXT              *f_pEncContext,
    __in                                      const DRM_M2TS_ECM_TYPE                        f_eECMType,
    __out_ecount( 1 )                               DRM_M2TS_ECM                           **f_ppECM ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_M2TS_AllocateSamples( 
    __inout                                         DRM_M2TS_ENCRYPTOR_CONTEXT              *f_pEncContext ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_M2TS_AllocateSubsamples( 
    __inout                                         DRM_M2TS_ENCRYPTOR_CONTEXT              *f_pEncContext ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_M2TS_SetECMPID( 
    __inout                                         DRM_M2TS_ENCRYPTOR_CONTEXT              *f_pEncContext )  DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_M2TS_RegisterPID( 
    __inout                                         DRM_M2TS_ENCRYPTOR_CONTEXT              *f_pEncContext,
    __in                                      const DRM_WORD                                 f_wPID ) DRM_NO_INLINE_ATTRIBUTE;

EXIT_PK_NAMESPACE_CODE;

#endif  // __M2TSBUFFERMGR_H__