/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef _DRMNDR_H_
#define _DRMNDR_H_

#include <drmtypes.h>
#include <drmmanager.h>
#include <drmstkalloc.h>
#include <oemaes.h>

ENTER_PK_NAMESPACE;

enum NDRState
{
    NDR_InitialState,
    NDR_RegisteredState,
    NDR_ChallengedState,
    NDR_ProximityDetectedState,
    NDR_HaveLicenseState
};

/*
** Define a context for Proximity Detection
*/
typedef struct
{
    enum NDRState   State;

    /*
    ** Data from the Registration Response message
    ** This data is valid in the RegisteredState and ChallengedState
    */
    DRM_AES_KEY  *ProximityContentEncryptionKey;
    DRM_ID        SessionId;
    DRM_WORD      AddressSize;
    DRM_BYTE     *Address;

    /*
    ** Data from the proximity challenge message
    ** This data is valid in the ChallengedState
    */
    DRM_ID   Challenge;
    DRM_BYTE Sequence;

    /*
    ** Data for the License Request message
    ** This data is valid in the ProximityDetectedState and HaveLicenseState
    */
    DRM_ID RightsId;
} DRM_ND_PROXIMITY_CONTEXT;


DRM_API DRM_RESULT DRM_CALL Drm_Ndr_Registration_GenerateChallenge(
    __in_opt DRM_VOID                                    *f_pOEMContext,
    __deref_out_bcount_full(*f_pcbMessageSize) DRM_BYTE **f_ppbMessage,
    __out DRM_DWORD                                      *f_pcbMessageSize
);


DRM_API DRM_RESULT DRM_CALL Drm_Ndr_Registration_ProcessResponse(
    __in_opt DRM_VOID                                         *f_pOEMContext,
    __in DRM_ND_PROXIMITY_CONTEXT                             *f_pProximityContext,
    __in_bcount(f_cbRegistrationResponseMessageSize) DRM_BYTE *f_pbRegistrationResponseMessage,
    __in const DRM_DWORD                                       f_cbRegistrationResponseMessageSize,
    __in DRM_CRYPTO_CONTEXT                                   *f_pCryptoCtx

);


DRM_API DRM_RESULT DRM_CALL Drm_Ndr_License_GenerateChallenge(
    __in_opt DRM_VOID                                     *f_pOEMContext,
    __out DRM_ID                                          *f_pRightsId,
    __deref_out_bcount_full(*f_pcbMessageSize) DRM_BYTE  **f_ppbMessage,
    __out DRM_DWORD                                       *f_pcbMessageSize
);


DRM_API DRM_RESULT DRM_CALL Drm_Ndr_License_ProcessResponse(
    __in_opt       DRM_VOID                              *f_pOEMContext,
    __in           DRM_ND_PROXIMITY_CONTEXT              *f_pProximityContext,
    __in_bcount(f_cbLicenseResponseMessageSize) DRM_BYTE *f_pbLicenseResponseMessage,
    __in const     DRM_DWORD                              f_cbLicenseResponseMessageSize,
    __in           DRM_STACK_ALLOCATOR_CONTEXT           *f_pStack,
    __in_opt       DRMPFNPOLICYCALLBACK                   f_pfnPolicyCallback,
    __in_opt const DRM_VOID                              *f_pv,
    __out          DRM_DECRYPT_CONTEXT                   *f_pcontextDCRY,
    __in           DRM_CRYPTO_CONTEXT                    *f_pCryptoCtx
);


DRM_API DRM_RESULT DRM_CALL Drm_Ndr_Proximity_GenerateStart(
    __in_opt                                         DRM_VOID                  *f_pOEMContext,
    __in                                       const DRM_ND_PROXIMITY_CONTEXT  *f_pProximityContext,
    __deref_out_bcount_full(*f_pcbMessageSize)       DRM_BYTE                 **f_ppbMessage,
    __out                                            DRM_DWORD                 *f_pcbMessageSize );


DRM_API DRM_RESULT DRM_CALL Drm_Ndr_Proximity_GenerateResponse(
    __in_opt                                         DRM_VOID                  *f_pOEMContext,
    __in                                       const DRM_ND_PROXIMITY_CONTEXT  *f_pProximityContext,
    __deref_out_bcount_full(*f_pcbMessageSize)       DRM_BYTE                 **f_ppbMessage,
    __out                                            DRM_DWORD                 *f_pcbMessageSize );


DRM_API DRM_RESULT DRM_CALL Drm_Ndr_Proximity_ProcessChallenge(
    __in_opt DRM_VOID                     *f_pOEMContext,
    __in DRM_ND_PROXIMITY_CONTEXT         *f_pProximityContext,
    __in_bcount(f_cbMessageSize) DRM_BYTE *f_pbMessage,
    __in const DRM_DWORD                   f_cbMessageSize
);


DRM_API DRM_RESULT DRM_CALL Drm_Ndr_Proximity_ProcessResult(
    __in_opt DRM_VOID                     *f_pOEMContext,
    __in DRM_ND_PROXIMITY_CONTEXT         *f_pProximityContext,
    __in_bcount(f_cbMessageSize) DRM_BYTE *f_pbMessage,
    __in const DRM_DWORD                   f_cbMessageSize,
    __out      DRM_WORD                   *f_pwResult
);


DRM_API DRM_BYTE DRM_CALL Drm_Ndr_GetMessageType(
    __in_bcount(f_cbMessageSize) const DRM_BYTE  * const f_pbMessage,
    __in                         const DRM_DWORD         f_cbMessageSize
);


EXIT_PK_NAMESPACE;

#endif    /* _DRMNDR_H_ */

