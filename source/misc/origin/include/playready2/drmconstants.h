/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRMSTRINGS_H__
#define __DRMSTRINGS_H__

#include <drmtypes.h>
#include <oemcryptoctx.h>

ENTER_PK_NAMESPACE;

    /* License constants */
    extern const PUBKEY  g_pubkeyLicenseServer;
    extern const DRM_LID g_rgbSecStoreGlobalName;

    /* Character constants */
    extern const DRM_WCHAR              g_wchNull;
    extern const DRM_WCHAR              g_wchMinus;
    extern const DRM_WCHAR              g_wchPlus;
    extern const DRM_WCHAR              g_wchForwardSlash;
    extern const DRM_WCHAR              g_wchColon;
    extern const DRM_WCHAR              g_wchComma;
    extern const DRM_WCHAR              g_wchQuote;
    extern const DRM_WCHAR              g_wchSingleQuote;
    extern const DRM_WCHAR              g_wchNewLine;
    extern const DRM_WCHAR              g_wchBackSlash;
    extern const DRM_WCHAR              g_wch0;
    extern const DRM_WCHAR              g_wch1;
    extern const DRM_WCHAR              g_wch2;
    extern const DRM_WCHAR              g_wch9;
    extern const DRM_WCHAR              g_wcha;
    extern const DRM_WCHAR              g_wchd;
    extern const DRM_WCHAR              g_wchf;
    extern const DRM_WCHAR              g_wchh;
    extern const DRM_WCHAR              g_wchm;
    extern const DRM_WCHAR              g_wchn;
    extern const DRM_WCHAR              g_wchs;
    extern const DRM_WCHAR              g_wchx;
    extern const DRM_WCHAR              g_wchy;
    extern const DRM_WCHAR              g_wchz;
    extern const DRM_WCHAR              g_wchA;
    extern const DRM_WCHAR              g_wchF;
    extern const DRM_WCHAR              g_wchG;
    extern const DRM_WCHAR              g_wchM;
    extern const DRM_WCHAR              g_wchT;
    extern const DRM_WCHAR              g_wchX;
    extern const DRM_WCHAR              g_wchZ;
    extern const DRM_WCHAR              g_wchUnderscore;
    extern const DRM_WCHAR              g_wchPeriod;
    extern const DRM_WCHAR              g_wchQuestionMark;
    extern const DRM_WCHAR              g_wchExclamationMark;
    extern const DRM_WCHAR              g_wchOpenParen;
    extern const DRM_WCHAR              g_wchCloseParen;
    extern const DRM_WCHAR              g_wchPound;
    extern const DRM_WCHAR              g_wchSpace;
    extern const DRM_WCHAR              g_wchTab;
    extern const DRM_WCHAR              g_wchLineFeed;
    extern const DRM_WCHAR              g_wchVerticalTab;
    extern const DRM_WCHAR              g_wchFormFeed;
    extern const DRM_WCHAR              g_wchCarriageReturn;
    extern const DRM_WCHAR              g_wchEqual;
    extern const DRM_WCHAR              g_wchOpenCurly;
    extern const DRM_WCHAR              g_wchCloseCurly;
    extern const DRM_WCHAR              g_wchLessThan;
    extern const DRM_WCHAR              g_wchGreaterThan;
    extern const DRM_WCHAR              g_wchLeftBracket;
    extern const DRM_WCHAR              g_wchRightBracket;
    extern const DRM_WCHAR              g_wchAsterisk;
    extern const DRM_WCHAR              g_wchPercent;
    extern const DRM_WCHAR              g_wchSemiColon;
    extern const DRM_WCHAR              g_wchAmpersand;
    extern const DRM_WCHAR              g_wchPipe;

    /* Character constants - ANSI */
    extern const DRM_CHAR               g_chForwardSlash;
    extern const DRM_CHAR               g_chPeriod;
    extern const DRM_CHAR               g_chNull;
    extern const DRM_CHAR               g_chMinus;
    extern const DRM_CHAR               g_chPlus;
    extern const DRM_CHAR               g_ch0;
    extern const DRM_CHAR               g_ch9;
    extern const DRM_CHAR               g_cha;
    extern const DRM_CHAR               g_chA;

    /* Misc strings shared across disparate functional areas */
    extern const DRM_ANSI_CONST_STRING  g_dastrTagSLK;
    extern const DRM_ANSI_CONST_STRING  g_dastrTagSLKID;
    extern const DRM_ANSI_CONST_STRING  g_dastrTagSLKDATA;
    extern const DRM_CONST_STRING       g_dstrXPathSymSig;
    extern const DRM_ANSI_CONST_STRING  g_adstrLicenseRespTag;
    extern const DRM_CONST_STRING       g_dstrGUID;
    extern const DRM_CONST_STRING       g_dstrFlag;
    extern const DRM_CONST_STRING       g_dstrSecureClockNotSet;
    extern const DRM_CONST_STRING       g_dstrSecureClockSet;
    extern const DRM_CONST_STRING       g_dstrSecureClockNeedsRefresh;
    extern const DRM_CONST_STRING       g_dstrExprVarSavedDateTime;
    extern const DRM_CONST_STRING       g_dstrInitialExtensibleStateAttributeName;
    extern const DRM_CONST_STRING       g_dstrTagMetering;
    extern const DRM_CONST_STRING       g_dstrTagHash;
    extern const DRM_CONST_STRING       g_dstrTagCmd;
    extern const DRM_CONST_STRING       g_dstrTagPartialData;
    extern const DRM_CONST_STRING       g_dstrHMAC;
    extern const DRM_CONST_STRING       g_dstr1;
    extern const DRM_CONST_STRING       g_dstrReset;
    extern const DRM_CONST_STRING       g_dstrLicense;
    extern const DRM_CONST_STRING       g_dstrTagRevocation;

    /* Rights */
    extern const DRM_CONST_STRING       g_dstrWMDRM_RIGHT_NONE;
    extern const DRM_CONST_STRING       g_dstrWMDRM_RIGHT_PLAYBACK;
    extern const DRM_CONST_STRING       g_dstrWMDRM_RIGHT_COLLABORATIVE_PLAY;
    extern const DRM_CONST_STRING       g_dstrWMDRM_RIGHT_COPY;
    extern const DRM_CONST_STRING       g_dstrWMDRM_RIGHT_CREATE_THUMBNAIL_IMAGE;
    extern const DRM_CONST_STRING       g_dstrWMDRM_RIGHT_COPY_TO_CD;
    extern const DRM_CONST_STRING       g_dstrWMDRM_RIGHT_MOVE;

    /* Script varibles used for license properties. */
    extern const DRM_CONST_STRING       g_dstrDRM_LS_BEGIN_ATTR;
    extern const DRM_CONST_STRING       g_dstrDRM_LS_COUNT_ATTR;
    extern const DRM_CONST_STRING       g_dstrDRM_LS_BEGDATE_ATTR;
    extern const DRM_CONST_STRING       g_dstrDRM_LS_ENDDATE_ATTR;
    extern const DRM_CONST_STRING       g_dstrDRM_LS_FIRSTUSE_ATTR;
    extern const DRM_CONST_STRING       g_dstrDRM_LS_FIRSTSTORE_ATTR;
    extern const DRM_CONST_STRING       g_dstrDRM_LS_APPSEC_ATTR;
    extern const DRM_CONST_STRING       g_dstrDRM_LS_PLAYCOUNT_ATTR;
    extern const DRM_CONST_STRING       g_dstrDRM_LS_COPYCOUNT_ATTR;
    extern const DRM_CONST_STRING       g_dstrDRM_LS_DELETED_ATTR;

    /* Shared XML tags */
    extern const DRM_CONST_STRING       g_dstrResponse;
    extern const DRM_CONST_STRING       g_dstrAttributeVersion;
    extern const DRM_CONST_STRING       g_dstrTagData;
    extern const DRM_CONST_STRING       g_dstrTagIndex;
    extern const DRM_CONST_STRING       g_dstrTagSymSig;
    extern const DRM_CONST_STRING       g_dstrTagPubkey;
    extern const DRM_CONST_STRING       g_dstrTagPRIVKEY;
    extern const DRM_CONST_STRING       g_dstrAttributePubkey;
    extern const DRM_CONST_STRING       g_dstrAttributeVerifiedCK;
    extern const DRM_CONST_STRING       g_dstrTagValue;
    extern const DRM_CONST_STRING       g_dstrTagSignature;
    extern const DRM_CONST_STRING       g_dstrTagHashAlg;
    extern const DRM_CONST_STRING       g_dstrTagSignAlg;
    extern const DRM_CONST_STRING       g_dstrSHA;
    extern const DRM_CONST_STRING       g_dstrMSDRM;
    extern const DRM_ANSI_CONST_STRING  g_dastrAttributeType;
    extern const DRM_CONST_STRING       g_dstrAttributeType;
    extern const DRM_CONST_STRING       g_dstrTagCertificate;
    extern const DRM_CONST_STRING       g_dstrTagDevCert;
    extern const DRM_CONST_STRING       g_dstrTagWrmHeader;
    extern const DRM_CONST_STRING       g_dstrAttributeVersion2Value;
    extern const DRM_CONST_STRING       g_dstrAttributeVersion4Value;
    extern const DRM_CONST_STRING       g_dstrAttributeVersion4_1Value;
    extern const DRM_CONST_STRING       g_dstrTagLAINFO;
    extern const DRM_CONST_STRING       g_dstrTagV4DATA;
    extern const DRM_CONST_STRING       g_dstrTagLAURL;
    extern const DRM_CONST_STRING       g_dstrTagLUIURL;
    extern const DRM_CONST_STRING       g_dstrTagDSID;
    extern const DRM_CONST_STRING       g_dstrTagKID;
    extern const DRM_CONST_STRING       g_dstrTagChecksum;
    extern const DRM_CONST_STRING       g_dstrTagAlgID;
    extern const DRM_CONST_STRING       g_dstrTagUplink;
    extern const DRM_CONST_STRING       g_dstrTagDecryptorSetup;
    extern const DRM_CONST_STRING       g_dstrTagProtectInfo;
    extern const DRM_CONST_STRING       g_dstrTagKeyLen;
    extern const DRM_CONST_STRING       g_dstrKeyLenNodeDataCocktail;
    extern const DRM_CONST_STRING       g_dstrKeyLenNodeDataAESCTR;
    extern const DRM_CONST_STRING       g_dstrTagCOCKTAIL;
    extern const DRM_CONST_STRING       g_dstrTagAESCTR;
    extern const DRM_CONST_STRING       g_dstrTagCustomAttributes;
    extern const DRM_CONST_STRING       g_dstrTagONDEMAND;
    extern const DRM_CONST_STRING       g_dstrEmptyWRMHeaderV4_1;
    extern const DRM_CONST_STRING       g_dstrTagAction;
    extern const DRM_CONST_STRING       g_dstrTagSecurityVersion;
    extern const DRM_CONST_STRING       g_dstrTagMSDRMSignature;
    extern const DRM_CONST_STRING       g_dstrTagMID;
    extern const DRM_CONST_STRING       g_dstrTagTID;
    extern const DRM_CONST_STRING       g_dstrTagRecords;
    extern const DRM_CONST_STRING       g_dstrTagURL;
    extern const DRM_CONST_STRING       g_dstrLabelValue;
    extern const DRM_CONST_STRING       g_dstrChallenge;
    extern const DRM_CONST_STRING       g_dstrTagCertificateChain;
    extern const DRM_CONST_STRING       g_dstrTagPrivateKey;
    extern const DRM_CONST_STRING       g_dstrTagDevice;
    extern const DRM_CONST_STRING       g_dstrRootSigValueVersionTag;
    extern const DRM_CONST_STRING       g_dstrRootSigValueVersionVal;
    extern const DRM_CONST_STRING       g_dstrTagDataPubKey;
    extern const DRM_CONST_STRING       g_dstrTemplate;
    extern const DRM_CONST_STRING       g_dstrTagDataSecVerPlatform;

    /* Shared Certificate tags */
    extern const DRM_ANSI_CONST_STRING  g_dastrAttributeAlgorithm;
    extern const DRM_ANSI_CONST_STRING  g_dastrAttributeVersionWMDRM;
    extern const DRM_ANSI_CONST_STRING  g_dastrKeyUsageSignCert;
    extern const DRM_ANSI_CONST_STRING  g_dastrKeyUsageEncryptKey;
    extern const DRM_ANSI_CONST_STRING  g_dastrOne;
    extern const DRM_ANSI_CONST_STRING  g_dastrPrefixManufacturer;
    extern const DRM_ANSI_CONST_STRING  g_dastrTagCanonicalization;
    extern const DRM_ANSI_CONST_STRING  g_dastrTagCertificateCollection;
    extern const DRM_ANSI_CONST_STRING  g_dastrTagDigestMethod;
    extern const DRM_ANSI_CONST_STRING  g_dastrURIDSigSHA1;
    extern const DRM_ANSI_CONST_STRING  g_dastrTagDigestValue;
    extern const DRM_ANSI_CONST_STRING  g_dastrTagSignatureValue;
    extern const DRM_ANSI_CONST_STRING  g_dastrTagKeyInfo;
    extern const DRM_ANSI_CONST_STRING  g_dastrTagPublicKey;
    extern const DRM_ANSI_CONST_STRING  g_dastrTagPrivateKey;
    extern const DRM_ANSI_CONST_STRING  g_dastrTagKeyValue;
    extern const DRM_ANSI_CONST_STRING  g_dastrTagRSAKeyValue;
    extern const DRM_ANSI_CONST_STRING  g_dastrTagModulus;
    extern const DRM_ANSI_CONST_STRING  g_dastrTagExponent;
    extern const DRM_ANSI_CONST_STRING  g_dastrTagManufacturerName;
    extern const DRM_ANSI_CONST_STRING  g_dastrTagManufacturerData;
    extern const DRM_ANSI_CONST_STRING  g_dastrURIRSASHA1;
    extern const DRM_ANSI_CONST_STRING  g_dastrURIRSASHA1_Old;
    extern const DRM_ANSI_CONST_STRING  g_dastrTagReference;
    extern const DRM_ANSI_CONST_STRING  g_dastrTagTransforms;
    extern const DRM_ANSI_CONST_STRING  g_dastrTagTransform;
    extern const DRM_ANSI_CONST_STRING  g_dastrURITransformMSCert;
    extern const DRM_ANSI_CONST_STRING  g_dastrURITransformMSCertColl;
    extern const DRM_ANSI_CONST_STRING  g_dastrURITransformMSCert_Old;
    extern const DRM_ANSI_CONST_STRING  g_dastrURITransformC14N;
    extern const DRM_ANSI_CONST_STRING  g_dastrTagWMDRMCertificate;
    extern const DRM_ANSI_CONST_STRING  g_dastrTagWMDRMData;
    extern const DRM_ANSI_CONST_STRING  g_dastrTagWMDRMCertPublicKey;
    extern const DRM_ANSI_CONST_STRING  g_dastrTagWMDRMCertSecurityVersion;
    extern const DRM_ANSI_CONST_STRING  g_dastrTagWMDRMCertSecurityLevel;
    extern const DRM_ANSI_CONST_STRING  g_dastrTagWMDRMCertFeatures;
    extern const DRM_ANSI_CONST_STRING  g_dastrTagWMDRMCertKeyUsage;
    extern const DRM_ANSI_CONST_STRING  g_dastrFeaturesWMDRMTransmitter;
    extern const DRM_ANSI_CONST_STRING  g_dastrFeaturesWMDRMReceiver;
    extern const DRM_ANSI_CONST_STRING  g_dastrTagSignature;
    extern const DRM_ANSI_CONST_STRING  g_dastrTagSignatureMethod;
    extern const DRM_ANSI_CONST_STRING  g_dastrTagSignedInfo;
    extern const DRM_ANSI_CONST_STRING  g_dastrURIC14N;
    extern const DRM_ANSI_CONST_STRING  g_dastrVersionWMDRM;
    extern const DRM_ANSI_CONST_STRING  g_dastrWMDRMCertExponent;
    extern const DRM_ANSI_CONST_STRING  g_dastrPrefixMicrosoftCert;
    extern const DRM_ANSI_CONST_STRING  g_dastrMSNDRootPubKeyB64;

    /* Well-known public Keys */
    extern const DRM_BYTE               g_rgbMSPlayReadyRootIssuerPubKey[];

    /* Revocation GUIDs */
    DRM_DECLARE_GUID( g_guidRevocationTypeRevInfo );
    DRM_DECLARE_GUID( g_guidRevocationTypeRevInfo2 );
    DRM_DECLARE_GUID( g_guidRevocationTypeWMDRMNET );
    DRM_DECLARE_GUID( g_guidRevocationTypeDevice );
    DRM_DECLARE_GUID( g_guidRevocationTypeApp );
    DRM_DECLARE_GUID( g_guidRevocationTypePlayReadySilverLightRuntime );
    DRM_DECLARE_GUID( g_guidRevocationTypePlayReadySilverLightApplication );
    DRM_DECLARE_GUID( g_guidRevocationTypeGRL );

    /* Actions GUIDs. Used with DRM_LEVL_PerformOperationsXMR() API */
    DRM_DECLARE_GUID( DRM_ACTION_PLAY );
    DRM_DECLARE_GUID( DRM_ACTION_COPY );
    DRM_DECLARE_GUID( DRM_ACTION_MOVE );
    DRM_DECLARE_GUID( DRM_ACTION_CREATE_THUMBNAIL );
    DRM_DECLARE_GUID( DRM_ACTION_COLLABORATIVE_PLAY );
    DRM_DECLARE_GUID( DRM_ACTION_COPY_TO_CD );
    DRM_DECLARE_GUID( DRM_ACTION_COPY_TO_PC );
    DRM_DECLARE_GUID( DRM_ACTION_COPY_TO_DEVICE );

    DRM_DECLARE_GUID( DRM_PR_PROTECTION_SYSTEM_ID );

    DRM_DECLARE_GUID( g_guidNull );

    /* PlayEnabler GUIDS */
    DRM_DECLARE_GUID( DRM_PLAYENABLER_UNKNOWN_OUTPUT );
    DRM_DECLARE_GUID( DRM_PLAYENABLER_CONSTRAINED_RESOLUTION_UNKNOWN_OUTPUT );

    /* Versioning constants */
    extern const DRM_BYTE CERT_VER       [__CB_DECL(VERSION_LEN)]; /* Indicates the public root key needed to verify the license server certificates. */
    extern const DRM_BYTE CLIENT_ID_VER  [__CB_DECL(VERSION_LEN)]; /* The version for client id. */

EXIT_PK_NAMESPACE;

#endif /* __DRMSTRINGS_H__ */

