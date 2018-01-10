/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRM_LICACQ_V3_CONSTANTS_H
#define __DRM_LICACQ_V3_CONSTANTS_H

ENTER_PK_NAMESPACE;

/*
** ---------------------------------------------------------
** XML strings used in the construction of license challenge
** ---------------------------------------------------------
*/
extern const DRM_ANSI_CONST_STRING g_dastrLicAcqRootTag;

extern const DRM_ANSI_CONST_STRING g_dastrLicAcqVersionTag;

extern const DRM_ANSI_CONST_STRING g_dastrLicAcqChallenge1Tag;

extern const DRM_ANSI_CONST_STRING g_dastrLicAcqChallenge2Tag;

extern const DRM_ANSI_CONST_STRING g_dastrLicAcqLATag;

extern const DRM_ANSI_CONST_STRING g_dastrLicAcqContentHeaderTag;

extern const DRM_ANSI_CONST_STRING g_dastrLicAcqSecurityVersionTag;

extern const DRM_ANSI_CONST_STRING g_dastrLicAcqAppSecurityTag;

extern const DRM_ANSI_CONST_STRING g_dastrLicAcqSubjectID1Tag;

extern const DRM_ANSI_CONST_STRING g_dastrLicAcqSubjectID2Tag;

extern const DRM_ANSI_CONST_STRING g_dastrLicAcqDRMKVersionTag;

extern const DRM_ANSI_CONST_STRING g_dastrLicAcqRevocationListsTag;

extern const DRM_ANSI_CONST_STRING g_dastrLicAcqRevListInfoTag;

extern const DRM_ANSI_CONST_STRING g_dastrLicAcqRevListIDTag;

extern const DRM_ANSI_CONST_STRING g_dastrLicAcqRevVersionTag;

extern const DRM_ANSI_CONST_STRING g_dastrLicAcqCertificateChainsTag;

extern const DRM_ANSI_CONST_STRING g_dastrLicAcqCertificateChainTag;

extern const DRM_ANSI_CONST_STRING g_dastrLicAcqDataTag;

extern const DRM_ANSI_CONST_STRING g_dastrLicAcqUplinksTag;

extern const DRM_ANSI_CONST_STRING g_dastrLicAcqUplinkTag;

extern const DRM_ANSI_CONST_STRING g_dastrLicAcqKIDTag;

extern const DRM_ANSI_CONST_STRING g_dastrLicAcqCategoryTag;

extern const DRM_ANSI_CONST_STRING g_dastrLicAcqCountTag;

extern const DRM_ANSI_CONST_STRING g_dastrLicAcqDateTag;

extern const DRM_ANSI_CONST_STRING g_dastrLicAcqVagueTag;

extern const DRM_ANSI_CONST_STRING g_dastrLicAcqCustomDataTag;

extern const DRM_ANSI_CONST_STRING g_dastrLicAcqLicenseNonceTag;


extern const DRM_ANSI_CONST_STRING g_dastrLicAcqRootAttribName;
extern const DRM_ANSI_CONST_STRING g_dastrLicAcqRootAttribValue;

extern const DRM_ANSI_CONST_STRING g_dastrLicAcqChallenge2AttribName;
extern const DRM_ANSI_CONST_STRING g_dastrLicAcqChallenge2AttribValue;

extern const DRM_ANSI_CONST_STRING g_dastrLicAcqChallengeVAAttrib1Name;
extern const DRM_ANSI_CONST_STRING g_dastrLicAcqChallengeVAAttrib1Value;

extern const DRM_ANSI_CONST_STRING g_dastrLicAcqChallengeVAAttrib2Name;
extern const DRM_ANSI_CONST_STRING g_dastrLicAcqChallengeVAAttrib2Value;

extern const DRM_ANSI_CONST_STRING g_dastrLicAcqVersionValue;


/*
** ---------------------------------------------------------------
** XML strings used in the construction of license acknowledgement
** ---------------------------------------------------------------
*/
extern const DRM_ANSI_CONST_STRING g_dastrLicAckRootTag;

extern const DRM_ANSI_CONST_STRING g_dastrLicAckVersionTag;

extern const DRM_ANSI_CONST_STRING g_dastrLicAckChallenge1Tag;

extern const DRM_ANSI_CONST_STRING g_dastrLicAckChallenge2Tag;

extern const DRM_ANSI_CONST_STRING g_dastrLicAckAckTag;

extern const DRM_ANSI_CONST_STRING g_dastrLicAckDataTag;

extern const DRM_ANSI_CONST_STRING g_dastrLicAckTransactionIDTag;

extern const DRM_ANSI_CONST_STRING g_dastrLicAckLicenseStorageResultsTag;

extern const DRM_ANSI_CONST_STRING g_dastrLicAckLicenseTag;

extern const DRM_ANSI_CONST_STRING g_dastrLicAckKIDTag;

extern const DRM_ANSI_CONST_STRING g_dastrLicAckLIDTag;

extern const DRM_ANSI_CONST_STRING g_dastrLicAckResultTag;

extern const DRM_ANSI_CONST_STRING g_dastrLicAckCertificateChainTag;


extern const DRM_ANSI_CONST_STRING g_dastrLicAckRootAttribName;
extern const DRM_ANSI_CONST_STRING g_dastrLicAckRootAttribValue;

extern const DRM_ANSI_CONST_STRING g_dastrLicAckChallenge2AttribName;
extern const DRM_ANSI_CONST_STRING g_dastrLicAckChallenge2AttribValue;

extern const DRM_ANSI_CONST_STRING g_dastrLicAckAckAttrib1Name;
extern const DRM_ANSI_CONST_STRING g_dastrLicAckAckAttrib1Value;

extern const DRM_ANSI_CONST_STRING g_dastrLicAckAckAttrib2Name;
extern const DRM_ANSI_CONST_STRING g_dastrLicAckAckAttrib2Value;

extern const DRM_ANSI_CONST_STRING g_dastrLicAckVersionValue;


/*
** -----------------------------------------------------
** XML strings used in the construction of SOAP envelope
** -----------------------------------------------------
*/
extern const DRM_ANSI_CONST_STRING g_dastrXMLRootTag;

extern const DRM_ANSI_CONST_STRING g_dastrSOAPEnvelopeTag;

extern const DRM_ANSI_CONST_STRING g_dastrSOAPBodyTag;


extern const DRM_ANSI_CONST_STRING g_dastrSOAPEnvelopeAttrib1Name;
extern const DRM_ANSI_CONST_STRING g_dastrSOAPEnvelopeAttrib1Value;

extern const DRM_ANSI_CONST_STRING g_dastrSOAPEnvelopeAttrib2Name;
extern const DRM_ANSI_CONST_STRING g_dastrSOAPEnvelopeAttrib2Value;

extern const DRM_ANSI_CONST_STRING g_dastrSOAPEnvelopeAttrib3Name;
extern const DRM_ANSI_CONST_STRING g_dastrSOAPEnvelopeAttrib3Value;


/*
** ---------------------------------------------------
** XML strings used in the parsing of license response
** ---------------------------------------------------
*/
extern const DRM_ANSI_CONST_STRING g_dastrLicLicensesPath;

extern const DRM_ANSI_CONST_STRING g_dastrLicLicensePath;

extern const DRM_ANSI_CONST_STRING g_dastrAcquireLicenseResultTag;

extern const DRM_ANSI_CONST_STRING g_dastrLicRevInfoPath;

extern const DRM_ANSI_CONST_STRING g_dastrRevInfo;

extern const DRM_ANSI_CONST_STRING g_dastrLicRevocationPath;

extern const DRM_ANSI_CONST_STRING g_dastrLicTransactionIDPath;
/*
extern const DRM_ANSI_CONST_STRING g_dastrLicRevocationAttribName;
*/
extern const DRM_ANSI_CONST_STRING g_dastrLicSLKPath;

extern const DRM_ANSI_CONST_STRING g_dastrLicRevocationAttribName;

extern const DRM_ANSI_CONST_STRING g_dastrLicListIdPath;

extern const DRM_ANSI_CONST_STRING g_dastrLicListDataPath;

extern const DRM_ANSI_CONST_STRING g_dastrLicNoncePath;

extern const DRM_ANSI_CONST_STRING g_dastrLicResponseIdPath;

extern const DRM_ANSI_CONST_STRING g_dastrLicSigningCertPath;


/*
** ---------------------------------------------------------------
** XML strings used in the parsing of license acknowledge response
** ---------------------------------------------------------------
*/
extern const DRM_ANSI_CONST_STRING g_dastrAcquireLicenseResponseTag;


EXIT_PK_NAMESPACE;

#endif /* __DRM_LICACQ_V3_CONSTANTS_H */
