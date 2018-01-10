/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __M2TSPARSERS_H__
#define __M2TSPARSERS_H__ 1

#include <drmm2tstypes.h>

ENTER_PK_NAMESPACE_CODE;

typedef DRM_BOOL ( DRM_CALL *DRM_pfnSearchStartCodeCallback )(
    __in_bcount( f_cbPayload )    const DRM_BYTE                                *f_pbPayload,
    __in                          const DRM_DWORD                                f_cbPayload,
    __inout                             DRM_DWORD                               *f_dwOffset, 
    __inout                             DRM_DWORD                               *f_dwStartCodeOffset,
    __inout_ecount( 1 )                 DRM_BYTE                                *f_pbLast );   

typedef DRM_RESULT ( DRM_CALL *DRM_pfnSyncAndParseFrameHeaderCallback )(
    __inout                             DRM_M2TS_SUBSAMPLE_CONTEXT              *f_poSubsampleContext,
    __inout                             DRM_WORD                                *f_pwSyncOffset,
    __out                               DRM_BOOL                                *f_pfSynced,
    __out                               DRM_UINT64                              *f_pqwDuration );

/* TS packet Header parsers */

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_M2TS_ParseTSPacketHeader( 
    __inout                             DRM_M2TS_PACKET                         *f_pPacket,
    __out_ecount( 1 )                   DRM_WORD                                *f_pwPID,
    __out_ecount( 1 )                   DRM_BOOL                                *f_pfUnitStart,
    __out_ecount( 1 )                   DRM_BYTE                                *f_pbContinuityCounter ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_M2TS_SetTSPacketHeader(
    __in                          const DRM_BOOL                                 f_fUnitStart,
    __in                          const DRM_WORD                                 f_wPID,
    __in                          const DRM_BOOL                                 f_fPayload,
    __in                          const DRM_BOOL                                 f_fAdaptation,
    __in                          const DRM_BYTE                                 f_bContinuityCounter,
    __in                          const DRM_DWORD                                f_cbPacketHeader,
    __out_bcount( f_cbPacketHeader )    DRM_BYTE                                *f_pbPacketHeader ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_M2TS_ParsePacketHeader(  
    __inout                             DRM_M2TS_ENCRYPTOR_CONTEXT              *f_pEncContext,
    __inout                             DRM_M2TS_STREAM                         *f_pStream,
    __inout                             DRM_M2TS_PACKET                         *f_pPacket ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_M2TS_UpdatePESPacketLength( 
    __in                          const DRM_M2TS_ENCRYPTOR_CONTEXT              *f_pEncContext,
    __in                          const DRM_LONG                                 f_cbAdjustment,
    __inout                             DRM_M2TS_PACKET_LIST                    *f_pPacketList )  DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_M2TS_UpdateAlignmentFlag( 
    __in                          const DRM_M2TS_ENCRYPTOR_CONTEXT              *f_pEncContext,
    __in                          const DRM_BYTE                                 f_bAlignmentFlag,
    __inout                             DRM_M2TS_PACKET_LIST                    *f_pPacketList )  DRM_NO_INLINE_ATTRIBUTE;

/* media format parsers */

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_M2TS_CheckPESCompleteness(
    __inout                             DRM_M2TS_ENCRYPTOR_CONTEXT              *f_pEncContext,
    __inout                             DRM_M2TS_STREAM                         *f_pStream,
    __out                               DRM_BOOL                                *f_pfPESCompleted ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_M2TS_CheckLastPESContinuityCounter(
    __inout                             DRM_M2TS_STREAM                         *f_pStream ) DRM_NO_INLINE_ATTRIBUTE;


DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_M2TS_H264_CreateSubsampleMappings(
    __inout                             DRM_M2TS_ENCRYPTOR_CONTEXT              *f_pEncContext,
    __inout                             DRM_M2TS_SUBSAMPLE_CONTEXT              *f_poSubsampleContext,
    __inout                             DRM_M2TS_PES                            *f_pPES ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_M2TS_MPEG2_VIDEO_CreateSubsampleMappings(
    __inout                             DRM_M2TS_ENCRYPTOR_CONTEXT              *f_pEncContext,
    __inout                             DRM_M2TS_SUBSAMPLE_CONTEXT              *f_poSubsampleContext,
    __inout                             DRM_M2TS_PES                            *f_pPES ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_M2TS_CreateAudioSubsampleMappings(
    __inout                             DRM_M2TS_ENCRYPTOR_CONTEXT              *f_pEncContext,
    __in                          const DRM_pfnSyncAndParseFrameHeaderCallback   f_pfnSyncAndParseFrameHeader,
    __inout                             DRM_M2TS_SUBSAMPLE_CONTEXT              *f_poSubsampleContext,
    __inout                             DRM_M2TS_PES                            *f_pPES,
    __inout                             DRM_M2TS_STREAM                         *f_pStream ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_M2TS_SyncAndParseMPEGAAudioFrameHeaderCallback(
    __inout                             DRM_M2TS_SUBSAMPLE_CONTEXT              *f_poSubsampleContext,
    __inout                             DRM_WORD                                *f_pwSyncOffset,
    __out                               DRM_BOOL                                *f_pfSynced,
    __out                               DRM_UINT64                              *f_pqwDuration ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_M2TS_SyncAndParseADTSFrameHeaderCallback(
    __inout                             DRM_M2TS_SUBSAMPLE_CONTEXT              *f_poSubsampleContext,
    __inout                             DRM_WORD                                *f_pwSyncOffset,
    __out                               DRM_BOOL                                *f_pfSynced,
    __out                               DRM_UINT64                              *f_pqwDuration ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_M2TS_SyncAndParseDDPlusFrameHeaderCallback(
    __inout                             DRM_M2TS_SUBSAMPLE_CONTEXT              *f_poSubsampleContext,
    __inout                             DRM_WORD                                *f_pwSyncOffset,
    __out                               DRM_BOOL                                *f_pfSynced,
    __out                               DRM_UINT64                              *f_pqwDuration ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_BOOL DRM_CALL DRM_M2TS_HasPayload(
    __in                          const DRM_M2TS_PES                            *f_pPES ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_M2TS_FillSubsampleContextBuffer(
    __in                          const DRM_BOOL                                 f_fCheckPESCompleteness,
    __inout                             DRM_M2TS_SUBSAMPLE_CONTEXT              *f_poSubsampleContext,
    __inout                             DRM_M2TS_PACKET                        **f_ppPacket,
    __inout_opt                         DRM_M2TS_PACKET                        **f_ppOverflowPacket ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_BOOL DRM_CALL DRM_M2TS_FindVideoStartCode(
    __in                          const DRM_M2TS_STREAM                         *f_pStream,
    __in_bcount( f_cbDada )       const DRM_BYTE                                *f_pbData,
    __in                          const DRM_DWORD                                f_cbDada,
    __out                               DRM_DWORD                               *f_pdwStartCodeOffset ) DRM_NO_INLINE_ATTRIBUTE;

EXIT_PK_NAMESPACE_CODE;

#endif  // __M2TSPARSERS_H__