/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRM_INITPARSER_CONSTANTS_H__
#define __DRM_INITPARSER_CONSTANTS_H__


ENTER_PK_NAMESPACE;

/*
** ---------------------------------------------------------------
** XML strings used in the construction of an initiators
** ---------------------------------------------------------------
*/


extern const DRM_CONST_STRING g_dstrMeteringInitiator;
extern const DRM_CONST_STRING g_dstrJoinDomainInitiator;
extern const DRM_CONST_STRING g_dstrLeaveDomainInitiator;
extern const DRM_CONST_STRING g_dstrLicenseAcquisitionInitiator;
extern const DRM_CONST_STRING g_dstrCustomDataInitiatorTag;
extern const DRM_CONST_STRING g_dstrPRInitiatorTag;
extern const DRM_CONST_STRING g_dstrCertificateServerTag;
extern const DRM_CONST_STRING g_dstrMeteringIDTag;
extern const DRM_CONST_STRING g_dstrMaxPacketsTag;
extern const DRM_CONST_STRING g_dstrDomainControllerTag;
extern const DRM_CONST_STRING g_dstrServiceIDTag;
extern const DRM_CONST_STRING g_dstrAccountIDTag;
extern const DRM_CONST_STRING g_dstrContentURLTag;
extern const DRM_CONST_STRING g_dstrHeaderTag;
extern const DRM_CONST_STRING g_dstrWMConvertTag;

EXIT_PK_NAMESPACE;

#endif /* __DRM_INITPARSER_CONSTANTS_H__ */
