/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRMNDTMANAGER_H__
#define __DRMNDTMANAGER_H__

#include <drmtypes.h>
#include <ndtcontextsizes.h>
#include <ndttypes.h>

ENTER_PK_NAMESPACE;

typedef struct _tagNDTMGR_CONTEXT {
    DRM_BYTE rgbOpaqueBuffer[ __CB_DECL( NDTMGR_CONTEXT_BUFFER_SIZE ) ];
} NDTMGR_CONTEXT;

/* Maximum number of seconds that can pass between a registration request and a registration response */
#define NDT_REGISTRATION_TIMEOUT      120

/* Maximum number of milliseconds for round trip proximity timeout */
#define PROXIMITY_RTT_THRESHOLD_MS    7


DRM_API DRM_RESULT DRM_CALL Drm_Ndt_Initialize(
    __out    NDTMGR_CONTEXT             *f_pNdtMgrContext,
    __in     DRM_APP_CONTEXT            *f_pAppContext
);

DRM_API DRM_VOID DRM_CALL Drm_Ndt_Uninitialize(
    __in     NDTMGR_CONTEXT             *f_pNdtMgrContext
);

DRM_API DRM_RESULT DRM_CALL Drm_Ndt_Session_Create(
    __in_opt    DRM_VOID                *f_pOEMContext,
    __in        NDTMGR_CONTEXT          *f_pNdtMgrContext,
    __in const  NDTMGR_SESSION_TYPE      f_eSessionType,
    __in_opt    DRM_APP_CONTEXT         *f_pAppContext,
    __out       DRM_ID                  *f_pID
);

DRM_API DRM_RESULT DRM_CALL Drm_Ndt_Session_Close(
    __in        NDTMGR_CONTEXT          *f_pNdtMgrContext,
    __in const  DRM_ID                   f_idSession,
    __out_opt   DRM_APP_CONTEXT        **f_ppAppContext
);

DRM_API DRM_RESULT DRM_CALL Drm_Ndt_Registration_ProcessRequest(
    __in_opt DRM_VOID                   *f_pOEMContext,
    __in     NDTMGR_CONTEXT             *f_pNdtMgrContext,
    __in     DRM_ID                      f_idRegistrationSession,
    __in     DRM_BYTEBLOB                f_RegistrationRequest,
    __out_bcount_opt(*f_pcbRegistrationResponse) DRM_BYTE *f_pbRegistrationResponse,
    __inout  DRM_DWORD                  *f_pcbRegistrationResponse
);

DRM_API DRM_RESULT DRM_CALL Drm_Ndt_Proximity_ProcessStartMsg (
    __in_opt DRM_VOID                   *f_pOEMContext,
    __in     NDTMGR_CONTEXT             *f_pNdtMgrContext,
    __in     DRM_BYTEBLOB                f_ProximityStartMsg,
    __out_bcount(*f_pcbProximityChallengeMsg) DRM_BYTE *f_pbProximityChallengeMsg,
    __inout  DRM_DWORD                  *f_pcbProximityChallengeMsg
);

DRM_API DRM_RESULT DRM_CALL Drm_Ndt_Proximity_ProcessResponseMsg (
    __in_opt DRM_VOID                   *f_pOEMContext,
    __in     NDTMGR_CONTEXT             *f_pNdtMgrContext,
    __in     DRM_BYTEBLOB                f_ProximityResponseMsg,
    __out_bcount(*f_pcbProximityResultMsg) DRM_BYTE *f_pbProximityResultMsg,
    __inout  DRM_DWORD                  *f_pcbProximityResultMsg
);

DRM_API DRM_RESULT DRM_CALL Drm_Ndt_License_ProcessChallenge(
    __in_opt   DRM_VOID                 *f_pOEMContext,
    __in       NDTMGR_CONTEXT           *f_pNdtMgrContext,
    __in const DRM_ID                    f_idSession,
    __in const DRM_BYTEBLOB              f_LicenseChallenge,
    __in const NDT_LICENSE_MODE          f_LicenseMode,
    __in       WMDRMNET_POLICY          *f_pPolicy,
    __out      DRM_KID                  *f_pKID,
    __out_bcount(*f_pcbLicenseResponse) DRM_BYTE *f_pbLicenseResponse,
    __inout    DRM_DWORD                *f_pcbLicenseResponse
);

DRM_API DRM_RESULT DRM_CALL Drm_Ndt_License_GenerateLeafResponse(
    __in_opt   DRM_VOID                 *f_pOEMContext,
    __in       NDTMGR_CONTEXT           *f_pNdtMgrContext,
    __in const DRM_ID                    f_idSession,
    __in       WMDRMNET_POLICY          *f_pPolicy,
    __out_bcount(*f_pcbLicenseResponse) DRM_BYTE *f_pbLicenseResponse,
    __inout    DRM_DWORD                *f_pcbLicenseResponse
);

DRM_API DRM_RESULT DRM_CALL Drm_Ndt_RevocationList_GenerateChallenge(
    __in const NDTMGR_CONTEXT           *f_pNdtMgrContext,
    __in const DRM_REVOCATION_LIST_TYPE  f_eRevocationList,
    __out_bcount_opt(*f_pcbRevocationListRequest) DRM_BYTE *f_pbRevocationListRequest,
    __inout    DRM_DWORD                *f_pcbRevocationListRequest
);

DRM_API DRM_RESULT DRM_CALL Drm_Ndt_RevocationList_ProcessRequest(
    __in       NDTMGR_CONTEXT          *f_pNdtMgrContext,
    __in const DRM_BYTEBLOB             f_RevocationListRequest,
    __out_bcount_opt(*f_pcbRevocationListResponse) DRM_BYTE *f_pbRevocationListResponse,
    __inout    DRM_DWORD               *f_pcbRevocationListResponse
);

DRM_API DRM_RESULT DRM_CALL Drm_Ndt_RevocationList_ProcessResponse(
    __in       NDTMGR_CONTEXT          *f_pNdtMgrContext,
    __in const DRM_BYTEBLOB             f_RevocationListResponse
);

EXIT_PK_NAMESPACE;

#endif /* __DRMNDTMANAGER_H__ */
