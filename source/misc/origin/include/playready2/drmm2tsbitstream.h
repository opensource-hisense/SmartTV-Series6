/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __M2TSBITSTREAMREADER_H__
#define __M2TSBITSTREAMREADER_H__ 1

#include <drmm2tstypes.h>

ENTER_PK_NAMESPACE_CODE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_M2TS_BSR_Init(
    __inout                                 DRM_M2TS_BIT_STREAM_CONTEXT         *f_poBSRContext,
    __in                              const DRM_DWORD                            f_cbData,
    __inout_bcount( f_cbData )              DRM_BYTE                            *f_pbData,
    __in                              const DRM_DWORD                            f_dwOffset ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_M2TS_BSR_Init_UsePacket(
    __inout                                 DRM_M2TS_BIT_STREAM_CONTEXT         *f_poBSRContext,
    __inout                                 DRM_M2TS_PACKET                     *f_pPacket ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_DWORD DRM_CALL DRM_M2TS_BSR_GetRemainingBytes(
    __inout                                 DRM_M2TS_BIT_STREAM_CONTEXT         *f_poBSRContext ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_M2TS_BSR_SetCounter(
    __inout                                 DRM_M2TS_BIT_STREAM_CONTEXT         *f_poBSRContext,
    __in                              const DRM_DWORD                            f_cbCounter ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_M2TS_BSR_ReadBitsToBYTE(
    __inout                                 DRM_M2TS_BIT_STREAM_CONTEXT         *f_poBSRContext,
    __in                              const DRM_DWORD                            f_cBitsToRead,
    __out_ecount( 1 )                       DRM_BYTE                            *f_pbValue ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_M2TS_BSR_ReadBitsToWORD(
    __inout                                 DRM_M2TS_BIT_STREAM_CONTEXT         *f_poBSRContext,
    __in                              const DRM_DWORD                            f_cBitsToRead,
    __out_ecount( 1 )                       DRM_WORD                            *f_pwValue ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_M2TS_BSR_ReadBitsToDWORD(
    __inout                                 DRM_M2TS_BIT_STREAM_CONTEXT         *f_poBSRContext,
    __in                              const DRM_DWORD                            f_cBitsToRead,
    __out_ecount ( 1 )                      DRM_DWORD                           *f_pdwValue ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_M2TS_BSR_SkipBits(
    __inout                                 DRM_M2TS_BIT_STREAM_CONTEXT         *f_poBSRContext,
    __in                              const DRM_DWORD                            f_cBitsToSkip ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_RESULT DRM_CALL DRM_M2TS_BSR_SkipPointerField(
    __inout                                 DRM_M2TS_BIT_STREAM_CONTEXT         *f_poBSRContext );

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_M2TS_BSR_WriteBitsFromBYTE(
    __inout                                 DRM_M2TS_BIT_STREAM_CONTEXT         *f_poBSRContext,
    __in                              const DRM_DWORD                            f_cBitsToWrite,
    __in                                    DRM_BYTE                             f_bValue ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_M2TS_BSR_WriteBitsFromWORD(
    __inout                                 DRM_M2TS_BIT_STREAM_CONTEXT         *f_poBSRContext,
    __in                              const DRM_DWORD                            f_cBitsToWrite,
    __in                              const DRM_WORD                             f_wValue ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_M2TS_BSR_SkipBytes(
    __inout                                 DRM_M2TS_BIT_STREAM_CONTEXT         *f_poBSRContext,
    __in                              const DRM_DWORD                            f_cBytesToSkip ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_M2TS_BSR_InsertBytes(
    __inout                                 DRM_M2TS_BIT_STREAM_CONTEXT         *f_poBSRContext,
    __in                              const DRM_DWORD                            f_cbBytesToInsert,
    __in_bcount( f_cbBytesToInsert )  const DRM_BYTE                            *f_pbByteToInsert) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_M2TS_BSR_UpdateCRC(
    __inout                                 DRM_M2TS_BIT_STREAM_CONTEXT         *f_poBSRContext,
    __in                              const DRM_DWORD                            f_cbBytesToCalculate ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_M2TS_BSR_ValidateCRC(
    __inout                                 DRM_M2TS_BIT_STREAM_CONTEXT         *f_poBSRContext,
    __in                              const DRM_DWORD                            f_cbBytesToCalculate ) DRM_NO_INLINE_ATTRIBUTE;

EXIT_PK_NAMESPACE_CODE;

#endif  // __M2TSBITSTREAMREADER_H__