/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef _DRMPRNDPROTOCOL_H_
#define _DRMPRNDPROTOCOL_H_ 1

#include <drmerr.h>
#include <drmblackbox.h>
#include <drmrevocation.h>
#include <drmprndprotocoltypes.h>

ENTER_PK_NAMESPACE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_PRND_Receiver_BeginSession(
    __inout                                                           DRM_PRND_RECEIVER_CONTEXT                        *f_poPrndReceiverContext ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_PRND_Receiver_RegistrationRequest_Generate(
    __inout                                                           DRM_PRND_RECEIVER_CONTEXT                        *f_poPrndReceiverContext,
    __in_opt                                                    const DRM_ID                                           *f_pPreviousSessionID,
    __in_opt                                                    const DRM_ID                                           *f_pCustomDataTypeID,
    __in_bcount_opt( f_cbCustomData )                           const DRM_BYTE                                         *f_pbCustomData,
    __in                                                              DRM_DWORD                                         f_cbCustomData,
    __in                                                              DRM_DWORD                                         f_dwFlags,
    __deref_out_ecount( *f_pcbReqMessage )                            DRM_BYTE                                        **f_ppbReqMessage,
    __out                                                             DRM_DWORD                                        *f_pcbReqMessage ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_PRND_Transmitter_BeginSession(
    __inout                                                           DRM_PRND_TRANSMITTER_CONTEXT                     *f_poPrndTransmitterContext ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_PRND_Transmitter_RegistrationRequest_Process(
    __inout                                                           DRM_PRND_TRANSMITTER_CONTEXT                     *f_poPrndTransmitterContext,
    __in_bcount( f_cbReqMessage )                               const DRM_BYTE                                         *f_pbReqMessage,
    __in                                                              DRM_DWORD                                         f_cbReqMessage,
    __in_opt                                                          Drm_Prnd_Data_Callback                            f_pfnDataCallback,
    __inout_ecount_opt( 1 )                                           DRM_VOID                                         *f_pvDataCallbackContext,
    __out                                                             DRM_PRND_PROXIMITY_DETECTION_TYPE                *f_peProximityDetectionType,
    __deref_out_ecount( *f_pcbTransmitterProximityDetectionChannel )  DRM_BYTE                                        **f_ppbTransmitterProximityDetectionChannel,
    __out                                                             DRM_DWORD                                        *f_pcbTransmitterProximityDetectionChannel,
    __out                                                             DRM_DWORD                                        *f_pdwFlags ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_PRND_Transmitter_RegistrationResponse_Generate(
    __inout                                                           DRM_PRND_TRANSMITTER_CONTEXT                     *f_poPrndTransmitterContext,
    __in_opt                                                    const DRM_ID                                           *f_pCustomDataTypeID,
    __in_bcount_opt( f_cbCustomData )                           const DRM_BYTE                                         *f_pbCustomData,
    __in                                                              DRM_DWORD                                         f_cbCustomData,
    __in                                                              DRM_DWORD                                         f_dwFlags,
    __deref_out_ecount( *f_pcbRespMessage )                           DRM_BYTE                                        **f_ppbRespMessage,
    __out                                                             DRM_DWORD                                        *f_pcbRespMessage ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_PRND_Transmitter_RegistrationError_Generate(
    __inout_opt                                                       DRM_PRND_TRANSMITTER_CONTEXT                     *f_poPrndTransmitterContext,
    __in                                                              DRM_DWORD                                         f_dwFlags,
    __deref_out_ecount( *f_pcbErrMessage )                            DRM_BYTE                                        **f_ppbErrMessage,
    __out                                                             DRM_DWORD                                        *f_pcbErrMessage,
    __in                                                              DRM_RESULT                                        f_drResult ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_PRND_Receiver_RegistrationResponse_Process(
    __inout                                                           DRM_PRND_RECEIVER_CONTEXT                        *f_poPrndReceiverContext,
    __in_bcount( f_cbRespMessage )                              const DRM_BYTE                                         *f_pbRespMessage,
    __in                                                              DRM_DWORD                                         f_cbRespMessage,
    __in_opt                                                          Drm_Prnd_Data_Callback                            f_pfnDataCallback,
    __inout_ecount_opt( 1 )                                           DRM_VOID                                         *f_pvDataCallbackContext,
    __out                                                             DRM_BOOL                                         *f_pfRIVUpdated,
    __out                                                             DRM_PRND_PROXIMITY_DETECTION_TYPE                *f_peProximityDetectionType,
    __deref_out_ecount( *f_pcbTransmitterProximityDetectionChannel )  DRM_BYTE                                        **f_ppbTransmitterProximityDetectionChannel,
    __out                                                             DRM_DWORD                                        *f_pcbTransmitterProximityDetectionChannel,
    __out                                                             DRM_DWORD                                        *f_pdwFlags ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_PRND_Receiver_RegistrationError_Process(
    __inout                                                           DRM_PRND_RECEIVER_CONTEXT                        *f_poPrndReceiverContext,
    __in_bcount( f_cbErrMessage )                               const DRM_BYTE                                         *f_pbErrMessage,
    __in                                                              DRM_DWORD                                         f_cbErrMessage,
    __out                                                             DRM_RESULT                                       *f_pdrResult,
    __out                                                             DRM_DWORD                                        *f_pdwFlags ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_PRND_Receiver_ProximityDetectionStart_Generate(
    __inout                                                           DRM_PRND_RECEIVER_CONTEXT                        *f_poPrndReceiverContext,
    __in                                                              DRM_DWORD                                         f_dwFlags,
    __deref_out_ecount( *f_pcbPDStartMessage )                        DRM_BYTE                                        **f_ppbPDStartMessage,
    __out                                                             DRM_DWORD                                        *f_pcbPDStartMessage ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_PRND_Transmitter_ProximityDetectionResult_Generate(
    __inout_opt                                                       DRM_PRND_TRANSMITTER_CONTEXT                     *f_poPrndTransmitterContext,
    __in_opt                                                    const DRM_ID                                           *f_pSessionID,
    __in                                                              DRM_DWORD                                         f_dwFlags,
    __deref_out_ecount( *f_pcbPDResultMessage )                       DRM_BYTE                                        **f_ppbPDResultMessage,
    __out                                                             DRM_DWORD                                        *f_pcbPDResultMessage,
    __in                                                              DRM_RESULT                                        f_drResult ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_PRND_Transmitter_ProximityDetectionStart_Process(
    __inout                                                           DRM_PRND_TRANSMITTER_CONTEXT                     *f_poPrndTransmitterContext,
    __in_bcount( f_cbPDStartMessage )                           const DRM_BYTE                                         *f_pbPDStartMessage,
    __in                                                              DRM_DWORD                                         f_cbPDStartMessage,
    __in                                                              DRM_DWORD                                         f_dwFlags,
    __deref_out_ecount( *f_pcbPDChlgMessage )                         DRM_BYTE                                        **f_ppbPDChlgMessage,
    __out                                                             DRM_DWORD                                        *f_pcbPDChlgMessage,
    __out                                                             DRM_DWORD                                        *f_pdwFlags ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_PRND_Receiver_ProximityDetectionChallenge_Process(
    __inout                                                           DRM_PRND_RECEIVER_CONTEXT                        *f_poPrndReceiverContext,
    __in_bcount( f_cbPDChlgMessage )                            const DRM_BYTE                                         *f_pbPDChlgMessage,
    __in                                                              DRM_DWORD                                         f_cbPDChlgMessage,
    __in                                                              DRM_DWORD                                         f_dwFlags,
    __deref_out_ecount( *f_pcbPDRespMessage )                         DRM_BYTE                                        **f_ppbPDRespMessage,
    __out                                                             DRM_DWORD                                        *f_pcbPDRespMessage,
    __out                                                             DRM_DWORD                                        *f_pdwFlags ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_PRND_Transmitter_ProximityDetectionResponse_Process(
    __inout                                                           DRM_PRND_TRANSMITTER_CONTEXT                     *f_poPrndTransmitterContext,
    __in_bcount( f_cbPDRespMessage )                            const DRM_BYTE                                         *f_pbPDRespMessage,
    __in                                                              DRM_DWORD                                         f_cbPDRespMessage,
    __in                                                              DRM_DWORD                                         f_dwFlags,
    __deref_out_ecount( *f_pcbPDResultMessage )                       DRM_BYTE                                        **f_ppbPDResultMessage,
    __out                                                             DRM_DWORD                                        *f_pcbPDResultMessage,
    __out                                                             DRM_DWORD                                        *f_pdwFlags ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_PRND_Receiver_ProximityDetectionResult_Process(
    __inout                                                           DRM_PRND_RECEIVER_CONTEXT                        *f_poPrndReceiverContext,
    __in_bcount( f_cbPDResultMessage )                          const DRM_BYTE                                         *f_pbPDResultMessage,
    __in                                                              DRM_DWORD                                         f_cbPDResultMessage,
    __out                                                             DRM_RESULT                                       *f_pdrPDResult,
    __out                                                             DRM_DWORD                                        *f_pdwFlags ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_PRND_Receiver_LicenseRequest_Generate(
    __inout                                                           DRM_PRND_RECEIVER_CONTEXT                        *f_poPrndReceiverContext,
    __in                                                        const DRM_GUID                                         *f_pguidRequestedAction,
    __in_opt                                                    const DRM_GUID                                         *f_pguidRequestedActionQualifier,
    __in                                                              DRM_PRND_CONTENT_IDENTIFIER_TYPE                  f_eContentIdentifierType,
    __in_bcount( f_cbContentIdentifier )                        const DRM_BYTE                                         *f_pbContentIdentifier,
    __in                                                              DRM_DWORD                                         f_cbContentIdentifier,
    __in_opt                                                    const DRM_ID                                           *f_pCustomDataTypeID,
    __in_bcount_opt( f_cbCustomData )                           const DRM_BYTE                                         *f_pbCustomData,
    __in                                                              DRM_DWORD                                         f_cbCustomData,
    __in                                                              DRM_DWORD                                         f_dwFlags,
    __deref_out_ecount( *f_pcbLicReqMessage )                         DRM_BYTE                                        **f_ppbLicReqMessage,
    __out                                                             DRM_DWORD                                        *f_pcbLicReqMessage ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_PRND_Transmitter_LicenseRequest_Process(
    __inout                                                           DRM_PRND_TRANSMITTER_CONTEXT                     *f_poPrndTransmitterContext,
    __in_bcount( f_cbLicReqMessage )                            const DRM_BYTE                                         *f_pbLicReqMessage,
    __in                                                              DRM_DWORD                                         f_cbLicReqMessage,
    __in_opt                                                          Drm_Prnd_Data_Callback                            f_pfnDataCallback,
    __inout_ecount_opt( 1 )                                           DRM_VOID                                         *f_pvDataCallbackContext,
    __in_opt                                                          Drm_Prnd_Content_Identifier_Callback              f_pfnContentIdentifierCallback,
    __inout_ecount_opt( 1 )                                           DRM_VOID                                         *f_pvContentIdentifierCallbackContext,
    __out                                                             DRM_DWORD                                        *f_pdwFlags ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_PRND_Transmitter_LicenseTransmit_Generate(
    __inout                                                           DRM_PRND_TRANSMITTER_CONTEXT                     *f_poPrndTransmitterContext,
    __in_ecount( f_cReceiverBoundOrLeafXMRLicenses )                  DRM_BYTE                                        **f_rgpbReceiverBoundOrLeafXMRLicense,
    __in_ecount( f_cReceiverBoundOrLeafXMRLicenses )            const DRM_DWORD                                        *f_rgcbReceiverBoundOrLeafXMRLicense,
    __in                                                              DRM_DWORD                                         f_cReceiverBoundOrLeafXMRLicenses,
    __in_opt                                                    const DRM_ID                                           *f_pCustomDataTypeID,
    __in_bcount_opt( f_cbCustomData )                           const DRM_BYTE                                         *f_pbCustomData,
    __in                                                              DRM_DWORD                                         f_cbCustomData,
    __in                                                              DRM_DWORD                                         f_dwFlags,
    __deref_out_ecount( *f_pcbLicTransmitMessage )                    DRM_BYTE                                        **f_ppbLicTransmitMessage,
    __out                                                             DRM_DWORD                                        *f_pcbLicTransmitMessage ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_PRND_Transmitter_ClearPRNDStore(
    __inout                                                           DRM_PRND_TRANSMITTER_CONTEXT                     *f_poPrndTransmitterContext ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_PRND_Receiver_LicenseTransmit_Process(
    __inout                                                           DRM_PRND_RECEIVER_CONTEXT                        *f_poPrndReceiverContext,
    __in_bcount( f_cbLicTransmitMessage )                       const DRM_BYTE                                         *f_pbLicTransmitMessage,
    __in                                                              DRM_DWORD                                         f_cbLicTransmitMessage,
    __out                                                             DRM_BOOL                                         *f_pfRIVUpdated,
    __inout_ecount_opt( *f_pcReceiverBoundOrLeafXMRLicenses )         DRM_BYTE                                        **f_rgpbReceiverBoundOrLeafXMRLicense,
    __inout_ecount_opt( *f_pcReceiverBoundOrLeafXMRLicenses )         DRM_DWORD                                        *f_rgcbReceiverBoundOrLeafXMRLicense,
    __inout                                                           DRM_DWORD                                        *f_pcReceiverBoundOrLeafXMRLicenses,
    __in_opt                                                          Drm_Prnd_Data_Callback                            f_pfnDataCallback,
    __inout_ecount_opt( 1 )                                           DRM_VOID                                         *f_pvDataCallbackContext,
    __out_opt                                                         DRM_DWORD                                        *f_pcbLargestLicense,
    __out                                                             DRM_DWORD                                        *f_pdwFlags ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_PRND_Receiver_LicenseError_Process(
    __inout                                                           DRM_PRND_RECEIVER_CONTEXT                        *f_poPrndReceiverContext,
    __in_bcount( f_cbErrMessage )                               const DRM_BYTE                                         *f_pbErrMessage,
    __in                                                              DRM_DWORD                                         f_cbErrMessage,
    __out                                                             DRM_RESULT                                       *f_pdrResult,
    __out                                                             DRM_DWORD                                        *f_pdwFlags ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_PRND_Transmitter_LicenseError_Generate(
    __inout_opt                                                       DRM_PRND_TRANSMITTER_CONTEXT                     *f_poPrndTransmitterContext,
    __in_opt                                                    const DRM_ID                                           *f_pSessionID,
    __in                                                              DRM_DWORD                                         f_dwFlags,
    __deref_out_ecount( *f_pcbErrMessage )                            DRM_BYTE                                        **f_ppbErrMessage,
    __out                                                             DRM_DWORD                                        *f_pcbErrMessage,
    __in                                                              DRM_RESULT                                        f_drResult ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_PRND_Transmitter_EndSession(
    __inout                                                           DRM_PRND_TRANSMITTER_CONTEXT                     *f_poPrndTransmitterContext ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_PRND_Receiver_EndSession(
    __inout                                                           DRM_PRND_RECEIVER_CONTEXT                        *f_poPrndReceiverContext ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_PRND_Transmitter_IsSessionStillValid(
    __inout                                                           DRM_PRND_TRANSMITTER_CONTEXT                     *f_poPrndTransmitterContext,
    __out                                                             DRM_BOOL                                         *f_pfSessionStillValid ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_PRND_Tx_RebindLicenseKeysToNewECCKey(
    __inout_ecount( 1 )                               DRM_BB_CONTEXT                  *f_poBBXContext,
    __in                                              DRM_REVOCATIONSTORE_CONTEXT     *f_poRevStoreContext,
    __in_ecount( 1 )                            const DRM_BINDING_INFO                *f_pRootmostLicenseBindingInfo,
    __in                                        const DRM_PUBLIC_KEY_CONTEXT          *f_poECC256PubKeyTarget,
    __in_ecount_opt( f_cbCertificateTarget )    const DRM_BYTE                        *f_pbCertificateTarget,
    __in                                              DRM_DWORD                        f_cbCertificateTarget,
    __in_ecount_opt( f_cbCertificateTargetCRL ) const DRM_BYTE                        *f_pbCertificateTargetCRL,
    __in                                              DRM_DWORD                        f_cbCertificateTargetCRL,
    __in                                        const DRM_ID                          *f_pidSession,
    __out_ecount( 1 )                                 OEM_CRYPTO_HANDLE               *f_phandleAESIntegrityKey,
    __out_ecount( 1 )                                 CIPHERTEXT_P256                 *f_poEncryptedAESKeyPair ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_PRND_Tx_SignWithAESOMAC(
    __inout_ecount( 1 )                     DRM_BB_CONTEXT                  *f_poBBXContext,
    __in_ecount( 1 )                        OEM_CRYPTO_HANDLE                f_handleAESIntegrityKey,
    __in_bcount( f_cbData )           const DRM_BYTE                        *f_pbData,
    __in                                    DRM_DWORD                        f_cbData,
    __out_ecount( DRM_AES_BLOCKLEN )        DRM_BYTE                         f_rgbSignature[DRM_AES_BLOCKLEN] ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_PRND_OpenPRNDStore(
    __in_opt                                                DRM_VOID                                         *f_pOEMContext,
    __inout_ecount( 1 )                                     DRM_LICSTORE_CONTEXT                             *f_poLSTContextPRNDStore,
    __inout_ecount( 1 )                                     DRM_DST                                          *f_poDSTContextPRNDStore,
    __inout_ecount( 1 )                                     DRM_EST_CONTEXT                                  *f_poESTContextPRNDStore,
    __inout_ecount( f_cbPRNDStore )                   const DRM_BYTE                                         *f_pbPRNDStore,
    __in                                                    DRM_DWORD                                         f_cbPRNDStore,
    __out                                                   DRM_BOOL                                         *f_pfOpened ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_VOID DRM_CALL DRM_PRND_ClosePRNDStore(
    __inout_ecount( 1 )                                     DRM_LICSTORE_CONTEXT                             *f_poLSTContextPRNDStore,
    __inout_ecount( 1 )                                     DRM_DST                                          *f_poDSTContextPRNDStore,
    __inout_ecount( 1 )                                     DRM_EST_CONTEXT                                  *f_poESTContextPRNDStore,
    __inout_ecount( f_cbPRNDStore )                         DRM_BYTE                                         *f_pbPRNDStore,
    __in                                                    DRM_DWORD                                         f_cbPRNDStore,
    __out                                                   DRM_BOOL                                         *f_pfOpened ) DRM_NO_INLINE_ATTRIBUTE;

EXIT_PK_NAMESPACE;

#endif /* _DRMPRNDPROTOCOL_H_ */

