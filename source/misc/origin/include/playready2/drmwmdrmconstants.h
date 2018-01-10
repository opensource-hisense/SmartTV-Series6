/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRMWMDRMCONSTANTS_H__
#define __DRMWMDRMCONSTANTS_H__

#include <drmtypes.h>

ENTER_PK_NAMESPACE;

    extern const DRM_ANSI_CONST_STRING  g_dastrAttributeVersion;
    extern const DRM_ANSI_CONST_STRING  g_dastrTagLicense;
    extern const DRM_ANSI_CONST_STRING  g_dastrAttributeEncrypted;
    extern const DRM_ANSI_CONST_STRING  g_dastrAttributeFALSE;

    extern const DRM_CONST_STRING       g_dstrDRM_LS_SAP_ATTR;
    extern const DRM_CONST_STRING       g_dstrDRM_LS_MACHINE_DATETIME_GE;
    extern const DRM_CONST_STRING       g_dstrDRM_LS_MACHINE_DATETIME_LE;
    extern const DRM_CONST_STRING       g_dstrDRM_LS_APP_MINSECLEVEL_GE;
    extern const DRM_CONST_STRING       g_dstrEqual;
    extern const DRM_CONST_STRING       g_dstrDrmRestoreInfo;
    extern const DRM_CONST_STRING       g_dstrTagDataInclusionList;
    extern const DRM_CONST_STRING       g_dstrTagHashAlgorithm;
    extern const DRM_CONST_STRING       g_dstrMSDRM_CK;
    extern const DRM_CONST_STRING       g_dstrMeta;
    extern const DRM_CONST_STRING       g_dstrTagRevInfoVersion;
    extern const DRM_CONST_STRING       g_dstrTagSourceID;
    extern const DRM_CONST_STRING       g_dstrDeviceRevocationLicenseTag;
    extern const DRM_CONST_STRING       g_dstrWMDRMNETRevocationLicenseTag;
    extern const DRM_CONST_STRING       g_dstrAction;
    extern const DRM_CONST_STRING       g_dstrRestrictions;
    extern const DRM_CONST_STRING       g_dstrChainedEnablingBits;
    extern const DRM_CONST_STRING       g_dstrDrmRestoreInfoEnablingBits;
    extern const DRM_CONST_STRING       g_dstrCertChain;
    extern const DRM_CONST_STRING       g_dstrLISigHashAlgo;
    extern const DRM_CONST_STRING       g_dstrLISigAlgo;
    extern const DRM_CONST_STRING       g_dstrLISigValue;
    extern const DRM_CONST_STRING       g_dstrUplinkKid;
    extern const DRM_CONST_STRING       g_dstrChainedCheckSum;

    extern const DRM_CONST_STRING       g_dstrExprFuncDateAdd;
    extern const DRM_CONST_STRING       g_dstrExprFuncDateDiff;
    extern const DRM_CONST_STRING       g_dstrExprFuncMin;
    extern const DRM_CONST_STRING       g_dstrExprFuncMax;
    extern const DRM_CONST_STRING       g_dstrExprFuncDatePart;
    extern const DRM_CONST_STRING       g_dstrExprFuncVersionCompare;
    extern const DRM_CONST_STRING       g_dstrExprFuncDeleteLicense;
    extern const DRM_CONST_STRING       g_dstrExprFuncExists;
    extern const DRM_CONST_STRING       g_dstrLicEvalOnSelect;
    extern const DRM_CONST_STRING       g_dstrLicEvalOnDelete;
    extern const DRM_CONST_STRING       g_dstrLicEvalOnStore;

    /* Strings for expression evaluator variable evaluation */
    extern const DRM_CONST_STRING       g_dstrDRM_PREFIX;
    extern const DRM_CONST_STRING       g_dstrDRMK_PREFIX;
    extern const DRM_CONST_STRING       g_dstrMACHINE_PREFIX;
    extern const DRM_CONST_STRING       g_dstrAPP_PREFIX;
    extern const DRM_CONST_STRING       g_dstrSECSTATE_PREFIX;
    extern const DRM_CONST_STRING       g_dstrLICENSE_PREFIX;
    extern const DRM_CONST_STRING       g_dstrCONTENT_PREFIX;
    extern const DRM_CONST_STRING       g_dstrDEVICE_PREFIX;
    extern const DRM_CONST_STRING       g_dstrSECURETIME_PREFIX;

#if DRM_SUPPORT_SST_REDUNANCY
    extern const DRM_CONST_STRING       g_dstrSSTREDUNDANCY_PREFIX;
#endif

    extern const DRM_CONST_STRING       g_dstrExprVarVersion;
    extern const DRM_CONST_STRING       g_dstrExprVarParameter;
    extern const DRM_CONST_STRING       g_dstrExprVarReason;
    extern const DRM_CONST_STRING       g_dstrExprVarBBMSDRMVersion;
    extern const DRM_CONST_STRING       g_dstrExprVarDateTime;
    extern const DRM_CONST_STRING       g_dstrExprVarCount;
    extern const DRM_CONST_STRING       g_dstrExprVarMinSecLevel;
    extern const DRM_CONST_STRING       g_dstrExprVarSecLevel;
    extern const DRM_CONST_STRING       g_dstrExprVarAppSecLevel;
    extern const DRM_CONST_STRING       g_dstrExprVarSubjID;
    extern const DRM_CONST_STRING       g_dstrExprVarAppSubjID;
    extern const DRM_CONST_STRING       g_dstrExprVarGlobal;
    extern const DRM_CONST_STRING       g_dstrExprVarSaveDateTime;
    extern const DRM_CONST_STRING       g_dstrExprVarDRMReason;
    extern const DRM_CONST_STRING       g_dstrExprVarDevReg;

    /* Output restriction strings */
    extern const DRM_CONST_STRING       g_dstrLabelGuid;
    extern const DRM_CONST_STRING       g_dstrLabelLevel;
    extern const DRM_CONST_STRING       g_dstrTagUncompressedDigitalVideo;
    extern const DRM_CONST_STRING       g_dstrTagCompressedDigitalVideo;
    extern const DRM_CONST_STRING       g_dstrTagUncompressedDigitalAudio;
    extern const DRM_CONST_STRING       g_dstrTagCompressedDigitalAudio;
    extern const DRM_CONST_STRING       g_dstrTagAnalogVideo;
    extern const DRM_CONST_STRING       g_dstrTagCopy;
    extern const DRM_CONST_STRING       g_dstrTagExtensionList;
    extern const DRM_CONST_STRING       g_dstrTagExtension;
    extern const DRM_CONST_STRING       g_dstrTagIncludeList;
    extern const DRM_CONST_STRING       g_dstrTagInclude;
    extern const DRM_CONST_STRING       g_dstrTagExcludeList;
    extern const DRM_CONST_STRING       g_dstrTagExclude;

    extern const DRM_CONST_STRING       g_dstrTagLID;
    extern const DRM_CONST_STRING       g_dstrTagEnablingbits;
    extern const DRM_CONST_STRING       g_dstrTagSymValue;
    extern const DRM_CONST_STRING       g_dstrLicensorInfoNode;
    extern const DRM_CONST_STRING       g_dstrXPathSymValue;

    extern const DRM_CONST_STRING       g_dstrXPathSigValue;

    extern const DRM_CONST_STRING       g_dstrLIData;
    extern const DRM_CONST_STRING       g_dstrAppRevocation;
    extern const DRM_CONST_STRING       g_dstrPriority;
    extern const DRM_CONST_STRING       g_dstrIssueDate;
    extern const DRM_CONST_STRING       g_dstrContentPubKey;
    extern const DRM_CONST_STRING       g_dstrCondition;
    extern const DRM_CONST_STRING       g_dstrSourceID;
    extern const DRM_CONST_STRING       g_dstrInclusionList;
    extern const DRM_CONST_STRING       g_dstrLicEvalOnAction;
    extern const DRM_CONST_STRING       g_dstrLicEvalOnClockRollback;


EXIT_PK_NAMESPACE;

#endif /* __DRMWMDRMCONSTANTS_H__ */

