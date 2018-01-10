/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef _DRMPFDMANAGER_H_
#define _DRMPFDMANAGER_H_

#include <drmtypes.h>
#include <pfddrmcontextsizes.h>

#define PFD_MAX_CONTENT_SESSIONS 1

ENTER_PK_NAMESPACE;

typedef struct __tagPFDMGR_CONTEXT
{
    /* This data is Opaque.  Do not set any value in it. */
    DRM_BYTE rgbOpaqueBuffer[ __CB_DECL( PFDMGR_CONTEXT_BUFFER_SIZE ) ];
} PFDMGR_CONTEXT;


DRM_API DRM_WORD DRM_CALL Drm_Pfd_GetMTPStatusFromDRMRESULT(
    __in const DRM_RESULT f_drRes
);

DRM_API DRM_RESULT DRM_CALL Drm_Pfd_Initialize(
    __out          PFDMGR_CONTEXT   *f_pPfdMgrContext,
    __in_opt       DRM_VOID         *f_pOEMContext,
    __in     const DRM_CONST_STRING *f_pdstrDeviceStoreName );

DRM_API DRM_VOID DRM_CALL Drm_Pfd_Uninitialize(
    __in     PFDMGR_CONTEXT *f_pPfdMgrContext
);

DRM_API DRM_RESULT DRM_CALL Drm_Pfd_Registration_ProcessRequest(
    __in_opt   DRM_VOID       *f_pOEMContext,
    __inout    PFDMGR_CONTEXT *f_pPfdMgrContext,
    __in_bcount(f_cbRegistrationRequestMsg) DRM_BYTE *f_pbRegistrationRequestMsg,
    __in const DRM_DWORD       f_cbRegistrationRequestMsg,
    __out      DRM_DWORD      *f_pdwRegistrationTransactionID
);

DRM_API DRM_RESULT DRM_CALL Drm_Pfd_Registration_GenerateResponse(
    __inout                                     const PFDMGR_CONTEXT *f_pPfdMgrContext,
    __in                                        const DRM_DWORD       f_dwRegistrationTransactionID,
    __out_bcount(*f_pcbRegistrationResponseMsg)       DRM_BYTE       *f_pbRegistrationResponseMsg,
    __inout                                           DRM_DWORD      *f_pcbRegistrationResponseMsg );

DRM_API DRM_RESULT DRM_CALL Drm_Pfd_Proximity_GenerateChallenge(
    __in_opt   DRM_VOID       *f_pOEMContext,
    __inout    PFDMGR_CONTEXT *f_pPfdMgrContext,
    __in const DRM_DWORD       f_dwRegistrationTransactionID,
    __out      DRM_DWORD      *f_pdwChallenge1,
    __out      DRM_DWORD      *f_pdwChallenge2,
    __out      DRM_DWORD      *f_pdwChallenge3,
    __out      DRM_DWORD      *f_pdwChallenge4
);

DRM_API DRM_RESULT DRM_CALL Drm_Pfd_Proximity_ProcessResponse(
    __in_opt   DRM_VOID       *f_pOEMContext,
    __inout    PFDMGR_CONTEXT *f_pPfdMgrContext,
    __in const DRM_DWORD       f_dwRegistrationTransactionID,
    __in const DRM_DWORD       f_dwEncryptedChallenge1,
    __in const DRM_DWORD       f_dwEncryptedChallenge2,
    __in const DRM_DWORD       f_dwEncryptedChallenge3,
    __in const DRM_DWORD       f_dwEncryptedChallenge4
);

DRM_API DRM_RESULT DRM_CALL Drm_Pfd_License_ProcessRequest(
    __in_opt                               DRM_VOID       *f_pOEMContext,
    __inout                                PFDMGR_CONTEXT *f_pPfdMgrContext,
    __in const                             DRM_DWORD       f_dwSessionID,
    __in_bcount(f_cbLicenseRequestMsg)     DRM_BYTE       *f_pbLicenseRequestMsg,
    __in const                             DRM_DWORD       f_cbLicenseRequestMsg
);

DRM_API DRM_RESULT DRM_CALL Drm_Pfd_License_GenerateResponse(
    __inout                                const PFDMGR_CONTEXT *f_pPfdMgrContext,
    __in                                   const DRM_DWORD       f_dwSessionID,
    __out_bcount(*f_pcbLicenseResponseMsg)       DRM_BYTE       *f_pbLicenseResponseMsg,
    __inout                                      DRM_DWORD      *f_pcbLicenseResponseMsg );

DRM_API DRM_RESULT DRM_CALL Drm_Pfd_Aavt_OpenMediaSession(
    __in_opt   DRM_VOID         *f_pOEMContext,
    __inout    PFDMGR_CONTEXT   *f_pPfdMgrContext,
    __in const DRM_CONST_STRING *f_pdstrDeviceStoreName,
    __in       DRM_WCHAR        *f_pwszFileName,
    __in const DRM_WORD          f_wFileType,
    __in const DRM_DWORD         f_dwForceNewSession,
    __in const DRM_BOOL          f_fEncryptClear,
    __out      DRM_DWORD        *f_pdwSessionID,
    __out      DRM_DWORD        *f_pdwControlCapabilities,
    __out      DRM_DWORD        *f_pdwDRMStatus,
    __out      DRM_DWORD        *f_pdwLicenseStatus,
    __out      DRM_DWORD        *f_pdwDRMDeliveryOptions );

DRM_API DRM_RESULT DRM_CALL Drm_Pfd_Aavt_CloseMediaSession(
    __inout    PFDMGR_CONTEXT *f_pPfdMgrContext,
    __in const DRM_DWORD       f_dwSessionID
);

DRM_API DRM_RESULT DRM_CALL Drm_Pfd_Aavt_GetNextDataBlock(
    __in_opt   DRM_VOID       *f_pOEMContext,
    __inout    PFDMGR_CONTEXT *f_pPfdMgrContext,
    __in const DRM_DWORD       f_dwSessionID,
    __out      DRM_DWORD      *f_pdwEndOfData,
    __out_bcount(*f_pcbNextDataBlock) DRM_BYTE *f_pbNextDataBlock,
    __out      DRM_DWORD      *f_pcbNextDataBlock
);

DRM_API DRM_RESULT DRM_CALL Drm_Pfd_Aavt_SetCurrentTimePosition(
    __in_opt   DRM_VOID       *f_pOEMContext,
    __inout    PFDMGR_CONTEXT *f_pPfdMgrContext,
    __in const DRM_DWORD       f_dwSessionID,
    __in const DRM_DWORD       f_dwTimeOffsetInMilliseconds
);

EXIT_PK_NAMESPACE;

#endif  /* _DRMPFDMANAGER_H_ */
