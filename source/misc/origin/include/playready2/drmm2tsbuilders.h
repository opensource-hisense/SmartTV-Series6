/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __M2TSECMBUILDERS_H__
#define __M2TSECMBUILDERS_H__ 1

#include <drmm2tstypes.h>

ENTER_PK_NAMESPACE_CODE;

/* PMT builder */

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_M2TS_RebuildPMTPacket(
    __inout                 DRM_M2TS_ENCRYPTOR_CONTEXT                  *f_pEncContext,
    __inout                 DRM_M2TS_STREAM                             *f_pStream ) DRM_NO_INLINE_ATTRIBUTE;

/* ECM Builder */

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_M2TS_InsertECM(
    __inout                 DRM_M2TS_ENCRYPTOR_CONTEXT                  *f_pEncContext,
    __in              const DRM_M2TS_ECM_TYPE                            f_eECMType ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_M2TS_CleanupECM(
    __inout                 DRM_M2TS_ENCRYPTOR_CONTEXT                  *f_pEncContext,
    __inout                 DRM_M2TS_ECM                                *f_pECM ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_M2TS_RegisterAndTransferPES(
    __inout                 DRM_M2TS_ENCRYPTOR_CONTEXT                  *f_pEncContext,
    __inout                 DRM_M2TS_STREAM                             *f_pStream,
    __in              const DRM_BOOL                                     f_fStreamStoppped ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_M2TS_BuildSubsamplesMappings(
    __inout                 DRM_M2TS_ENCRYPTOR_CONTEXT                  *f_pEncContext,
    __inout                 DRM_M2TS_ECM                                *f_pECM  ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_M2TS_DropOverflowPayload( 
    __inout                 DRM_M2TS_ENCRYPTOR_CONTEXT                  *f_pEncContext,
    __inout                 DRM_M2TS_PACKET_LIST                        *f_pPacketList ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_M2TS_KeepOverflowPayload( 
    __inout                 DRM_M2TS_ENCRYPTOR_CONTEXT                  *f_pEncContext,
    __inout                 DRM_M2TS_PES                                *f_pPES,
    __inout                 DRM_M2TS_PACKET_LIST                        *f_pPacketList ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_M2TS_EncryptPESPackets(
    __inout                 DRM_M2TS_ENCRYPTOR_CONTEXT                  *f_pEncContext,
    __inout                 DRM_M2TS_ECM                                *f_pECM ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_M2TS_BuildECMPackets(
    __inout                 DRM_M2TS_ENCRYPTOR_CONTEXT                  *f_pEncContext,
    __inout                 DRM_M2TS_ECM                                *f_pECM,
    __inout                 DRM_M2TS_PACKET_LIST                        *f_pECMPacketList ) DRM_NO_INLINE_ATTRIBUTE;

EXIT_PK_NAMESPACE_CODE;

#endif  // __M2TSECMBUILDERS_H__