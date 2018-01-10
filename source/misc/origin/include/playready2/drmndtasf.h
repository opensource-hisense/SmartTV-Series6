/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRMNDTASF_H__
#define __DRMNDTASF_H__

ENTER_PK_NAMESPACE;

DRM_API DRM_RESULT DRM_CALL Drm_Ndt_Asf_Init (
    __in_opt   DRM_VOID                 *f_pOEMContext,
    __in       NDTMGR_CONTEXT           *f_pNdtMgrContext,
    __in const DRM_STRING                f_dstrFilePath,
    __in const NDT_ASFDELIVERY_MODE      f_ASFDeliveryMode,
    __in       DRM_APP_CONTEXT          *f_pAppContext,
    __in const DRM_BOOL                  f_fEncryptClear,
    __out      DRM_ID                   *f_pidSession,
    __out      DRM_DWORD                *f_pdwFlags
);

DRM_API DRM_RESULT DRM_CALL Drm_Ndt_Asf_InitTranscryption(
    __in_opt   DRM_VOID                 *f_pOEMContext,
    __in       NDTMGR_CONTEXT           *f_pNdtMgrContext,
    __in const DRM_ID                    f_idSession,
    __in const DRM_BYTEBLOB              f_LicenseChallenge,
    __out      DRM_KID                  *f_pKID,
    __out_bcount_opt(*f_pcbLicenseResponse) DRM_BYTE *f_pbLicenseResponse,
    __inout    DRM_DWORD                *f_pcbLicenseResponse
);

DRM_API DRM_RESULT DRM_CALL Drm_Ndt_Asf_GetHeader(
    __in_opt   DRM_VOID                 *f_pOEMContext,
    __in       NDTMGR_CONTEXT           *f_pNdtMgrContext,
    __in const DRM_ID                    f_idSession,
    __out_bcount(*f_pcbHeader) DRM_BYTE *f_pbHeader,
    __inout    DRM_DWORD                *f_pcbHeader
);

DRM_API DRM_RESULT DRM_CALL Drm_Ndt_Asf_GenerateLeafLicenseResponse(
    __in_opt   DRM_VOID                 *f_pOEMContext,
    __in       NDTMGR_CONTEXT           *f_pNdtMgrContext,
    __in const DRM_ID                    f_idSession,
    __out_bcount(*f_pcbLeafLicenseResponse) DRM_BYTE *f_pbLeafLicenseResponse,
    __inout    DRM_DWORD                *f_pcbLeafLicenseResponse
);

DRM_API DRM_RESULT DRM_CALL Drm_Ndt_Asf_Seek (
    __in_opt   DRM_VOID                 *f_pOEMContext,
    __in       NDTMGR_CONTEXT           *f_pNdtMgrContext,
    __in const DRM_ID                    f_idSession,
    __in const DRM_UINT64                f_qwSeekTimeNS
);

DRM_API DRM_RESULT DRM_CALL Drm_Ndt_Asf_ReadData(
    __in_opt   DRM_VOID                 *f_pOEMContext,
    __in       NDTMGR_CONTEXT           *f_pNdtMgrContext,
    __in const DRM_ID                    f_idSession,
    __out_bcount(*f_pcbData) DRM_BYTE   *f_pbData,
    __inout    DRM_DWORD                *f_pcbData
);

DRM_API DRM_RESULT DRM_CALL Drm_Ndt_Asf_ReadSample(
    __in_opt   DRM_VOID                 *f_pOEMContext,
    __in       NDTMGR_CONTEXT           *f_pNdtMgrContext,
    __in const DRM_ID                    f_idSession,
    __out      NDT_SAMPLEINFO           *f_pSampleInfo,
    __out_bcount(*f_pcbSampleData) DRM_BYTE *f_pbSampleData,
    __inout    DRM_DWORD                *f_pcbSampleData
);

DRM_API DRM_RESULT DRM_CALL Drm_Ndt_Asf_Close(
    __in       NDTMGR_CONTEXT           *f_pNdtMgrContext,
    __in const DRM_ID                    f_idSession,
    __out_opt  DRM_APP_CONTEXT         **f_ppAppContext
);

EXIT_PK_NAMESPACE;

#endif /* __DRMNDTASF_H__ */
