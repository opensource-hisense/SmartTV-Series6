/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRM_DOMAIN_CONSTANTS_H
#define __DRM_DOMAIN_CONSTANTS_H

ENTER_PK_NAMESPACE;

/*
** ---------------------------------------------------------------------
** XML strings used in the construction of domain join challenge
** ---------------------------------------------------------------------
*/
extern const DRM_ANSI_CONST_STRING g_dastrDomJoinRootTag;

extern const DRM_ANSI_CONST_STRING g_dastrDomJoinVersionTag;

extern const DRM_ANSI_CONST_STRING g_dastrDomJoinChallenge1Tag;

extern const DRM_ANSI_CONST_STRING g_dastrDomJoinChallenge2Tag;

extern const DRM_ANSI_CONST_STRING g_dastrDomJoinDomainTag;

extern const DRM_ANSI_CONST_STRING g_dastrDomJoinDataTag;

extern const DRM_ANSI_CONST_STRING g_dastrDomJoinServiceIDTag;

extern const DRM_ANSI_CONST_STRING g_dastrDomJoinAccountIDTag;

extern const DRM_ANSI_CONST_STRING g_dastrDomJoinRevisionTag;

extern const DRM_ANSI_CONST_STRING g_dastrDomJoinFriendlyNameTag;

extern const DRM_ANSI_CONST_STRING g_dastrDomJoinCustomDataTag;

extern const DRM_ANSI_CONST_STRING g_dastrDomJoinCertificateChainTag;


extern const DRM_ANSI_CONST_STRING g_dastrDomJoinRootAttribName;
extern const DRM_ANSI_CONST_STRING g_dastrDomJoinRootAttribValue;

extern const DRM_ANSI_CONST_STRING g_dastrDomJoinChallenge2AttribName;
extern const DRM_ANSI_CONST_STRING g_dastrDomJoinChallenge2AttribValue;

extern const DRM_ANSI_CONST_STRING g_dastrDomJoinDomainAttrib1Name;
extern const DRM_ANSI_CONST_STRING g_dastrDomJoinDomainAttrib1Value;

extern const DRM_ANSI_CONST_STRING g_dastrDomJoinDomainAttrib2Name;
extern const DRM_ANSI_CONST_STRING g_dastrDomJoinDomainAttrib2Value;

extern const DRM_ANSI_CONST_STRING g_dastrDomJoinCertificateChainAttribName;
extern const DRM_ANSI_CONST_STRING g_dastrDomJoinCertificateChainAttribValue;

extern const DRM_ANSI_CONST_STRING g_dastrDomainJoinVersion;



/*
** -----------------------------------------------------------------------
** XML strings used in the construction of domain leave challenge
** -----------------------------------------------------------------------
*/
extern const DRM_ANSI_CONST_STRING g_dastrDomLeaveRootTag;

extern const DRM_ANSI_CONST_STRING g_dastrDomLeaveVersionTag;

extern const DRM_ANSI_CONST_STRING g_dastrDomLeaveChallenge1Tag;

extern const DRM_ANSI_CONST_STRING g_dastrDomLeaveChallenge2Tag;

extern const DRM_ANSI_CONST_STRING g_dastrDomLeaveDomainTag;

extern const DRM_ANSI_CONST_STRING g_dastrDomLeaveDataTag;

extern const DRM_ANSI_CONST_STRING g_dastrDomLeaveAccountIDTag;

extern const DRM_ANSI_CONST_STRING g_dastrDomLeaveCustomDataTag;

extern const DRM_ANSI_CONST_STRING g_dastrDomLeaveCertificateChainTag;


extern const DRM_ANSI_CONST_STRING g_dastrDomLeaveRootAttribName;
extern const DRM_ANSI_CONST_STRING g_dastrDomLeaveRootAttribValue;

extern const DRM_ANSI_CONST_STRING g_dastrDomLeaveChallenge2AttribName;
extern const DRM_ANSI_CONST_STRING g_dastrDomLeaveChallenge2AttribValue;

extern const DRM_ANSI_CONST_STRING g_dastrDomLeaveDomainAttrib1Name;
extern const DRM_ANSI_CONST_STRING g_dastrDomLeaveDomainAttrib1Value;

extern const DRM_ANSI_CONST_STRING g_dastrDomLeaveDomainAttrib2Name;
extern const DRM_ANSI_CONST_STRING g_dastrDomLeaveDomainAttrib2Value;

extern const DRM_ANSI_CONST_STRING g_dastrDomLeaveCertificateChainAttribName;
extern const DRM_ANSI_CONST_STRING g_dastrDomLeaveCertificateChainAttribValue;

extern const DRM_ANSI_CONST_STRING g_dastrDomainLeaveVersion;



/*
** ---------------------------------------------------------------
** XML strings used in the parsing of domain join response
** ---------------------------------------------------------------
*/
extern const DRM_ANSI_CONST_STRING g_dastrDomJoinResponsePath;

extern const DRM_ANSI_CONST_STRING g_dastrDomJoinDataPath;

extern const DRM_ANSI_CONST_STRING g_dastrDomJoinDataPath;

extern const DRM_ANSI_CONST_STRING g_dastrDomJoinVersionPath;

extern const DRM_ANSI_CONST_STRING g_dastrDomJoinServiceIDPath;

extern const DRM_ANSI_CONST_STRING g_dastrDomJoinAccountIDPath;

extern const DRM_ANSI_CONST_STRING g_dastrDomJoinRevisionPath;

extern const DRM_ANSI_CONST_STRING g_dastrDomJoinCertificateChainPath;

extern const DRM_ANSI_CONST_STRING g_dastrDomJoinDomainKeysPath;

extern const DRM_ANSI_CONST_STRING g_dastrDomJoinSigningCertPath;

/*
** -----------------------------------------------------------------
** XML strings used in the parsing of domain leave response
** -----------------------------------------------------------------
*/
extern const DRM_ANSI_CONST_STRING g_dastrDomLeaveAccountIDPath;


EXIT_PK_NAMESPACE;

#endif /* __DRM_DOMAIN_CONSTANTS_H */

