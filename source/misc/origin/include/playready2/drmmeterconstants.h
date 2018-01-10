/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRM_METER_CONSTANTS_H
#define __DRM_METER_CONSTANTS_H

#include <drmtypes.h>
#include <oemcryptoctx.h>

ENTER_PK_NAMESPACE;

/*
** ------------------------------------------------------------
** XML strings used in the construction of meter data challenge
** ------------------------------------------------------------
*/
extern const DRM_EXPORT_VAR DRM_ANSI_CONST_STRING g_dastrMeterDataRootTag;

extern const DRM_EXPORT_VAR DRM_ANSI_CONST_STRING g_dastrMeterDataChallenge1Tag;

extern const DRM_EXPORT_VAR DRM_ANSI_CONST_STRING g_dastrMeterDataChallenge2Tag;

extern const DRM_EXPORT_VAR DRM_ANSI_CONST_STRING g_dastrMeterDataMeteringDataTag;

extern const DRM_EXPORT_VAR DRM_ANSI_CONST_STRING g_dastrMeterDataVersionTag;

extern const DRM_EXPORT_VAR DRM_ANSI_CONST_STRING g_dastrMeterDataMIDTag;

extern const DRM_EXPORT_VAR DRM_ANSI_CONST_STRING g_dastrMeterDataTIDTag;

extern const DRM_EXPORT_VAR DRM_ANSI_CONST_STRING g_dastrMeterDataCustomDataTag;

extern const DRM_EXPORT_VAR DRM_ANSI_CONST_STRING g_dastrMeterDataPartialDataTag;

extern const DRM_EXPORT_VAR DRM_ANSI_CONST_STRING g_dastrMeterDataDataTag;

extern const DRM_EXPORT_VAR DRM_ANSI_CONST_STRING g_dastrMeterDataDeviceCertTag;

extern const DRM_EXPORT_VAR DRM_ANSI_CONST_STRING g_dastrMeterDataRecordsTag;

extern const DRM_EXPORT_VAR DRM_ANSI_CONST_STRING g_dastrMeterDataRecordTag;

extern const DRM_EXPORT_VAR DRM_ANSI_CONST_STRING g_dastrMeterDataActionTag;


extern const DRM_EXPORT_VAR DRM_ANSI_CONST_STRING g_dastrMeterDataRootAttribName;
extern const DRM_EXPORT_VAR DRM_ANSI_CONST_STRING g_dastrMeterDataRootAttribValue;

extern const DRM_EXPORT_VAR DRM_ANSI_CONST_STRING g_dastrMeterDataChallenge2AttribName;
extern const DRM_EXPORT_VAR DRM_ANSI_CONST_STRING g_dastrMeterDataChallenge2AttribValue;

extern const DRM_EXPORT_VAR DRM_ANSI_CONST_STRING g_dastrMeterDataMeteringDataAttrib1Name;
extern const DRM_EXPORT_VAR DRM_ANSI_CONST_STRING g_dastrMeterDataMeteringDataAttrib1Value;

extern const DRM_EXPORT_VAR DRM_ANSI_CONST_STRING g_dastrMeterDataMeteringDataAttrib2Name;
extern const DRM_EXPORT_VAR DRM_ANSI_CONST_STRING g_dastrMeterDataMeteringDataAttrib2Value;

extern const DRM_EXPORT_VAR DRM_ANSI_CONST_STRING g_dastrMeterDataRecordAttribName;

extern const DRM_EXPORT_VAR DRM_ANSI_CONST_STRING g_dastrMeterDataActionAttrib1Name;

extern const DRM_EXPORT_VAR DRM_ANSI_CONST_STRING g_dastrMeterDataActionAttrib2Name;


extern const DRM_EXPORT_VAR DRM_ANSI_CONST_STRING g_dastrMeterDataVersionValue;

extern const DRM_EXPORT_VAR DRM_ANSI_CONST_STRING g_dastrMeterDataPartialDataValue;


/*
** ------------------------------------------------------
** XML strings used in the parsing of meter data response
** ------------------------------------------------------
*/
extern const DRM_EXPORT_VAR DRM_ANSI_CONST_STRING g_dastrMeterDataMeterCertPath;

extern const DRM_EXPORT_VAR DRM_ANSI_CONST_STRING g_dastrMeterDataEncryptedDataPath;

extern const DRM_EXPORT_VAR DRM_ANSI_CONST_STRING g_dastrMeterDataMIDPath;

extern const DRM_EXPORT_VAR DRM_ANSI_CONST_STRING g_dastrMeterDataTIDPath;

extern const DRM_EXPORT_VAR DRM_ANSI_CONST_STRING g_dastrMeterDataRecordsPath;

extern const DRM_EXPORT_VAR DRM_ANSI_CONST_STRING g_dastrMeterDataKIDPath;

extern const DRM_EXPORT_VAR DRM_ANSI_CONST_STRING g_dastrMeterDataKeyNamePath;

extern const DRM_EXPORT_VAR DRM_ANSI_CONST_STRING g_dastrMeterDataKeyNameValue;

/*
** ------------------------------------------------------------
** XML strings used in the construction of meter cert challenge
** ------------------------------------------------------------
*/
extern const DRM_EXPORT_VAR DRM_ANSI_CONST_STRING g_dastrMeterCertRootTag;

extern const DRM_EXPORT_VAR DRM_ANSI_CONST_STRING g_dastrMeterCertChallenge1Tag;

extern const DRM_EXPORT_VAR DRM_ANSI_CONST_STRING g_dastrMeterCertChallenge2Tag;

extern const DRM_EXPORT_VAR DRM_ANSI_CONST_STRING g_dastrMeterCertMIDTag;

extern const DRM_EXPORT_VAR DRM_ANSI_CONST_STRING g_dastrSupportsMeterCertSignatureTag;

extern const DRM_EXPORT_VAR DRM_ANSI_CONST_STRING g_dastrTrueValue;

extern const DRM_EXPORT_VAR DRM_ANSI_CONST_STRING g_dastrMeterCertVersionTag;

extern const DRM_EXPORT_VAR DRM_ANSI_CONST_STRING g_dastrMeterCertCustomDataTag;

extern const DRM_EXPORT_VAR DRM_ANSI_CONST_STRING g_dastrMeterCertRootAttribName;

extern const DRM_EXPORT_VAR DRM_ANSI_CONST_STRING g_dastrMeterCertRootAttribValue;


extern const DRM_EXPORT_VAR DRM_ANSI_CONST_STRING g_dastrMeterCertVersion;


/*
** ------------------------------------------------------
** XML strings used in the parsing of meter cert response
** ------------------------------------------------------
*/
extern const DRM_EXPORT_VAR DRM_ANSI_CONST_STRING g_dastrMeterCertResponsePath;

extern const DRM_EXPORT_VAR DRM_ANSI_CONST_STRING g_dastrMeterCertMeterCertPath;

/*
** -----------------------------
** Additional metering constants
** -----------------------------
*/
extern const DRM_CONST_STRING       g_dstrTagMeterCert;
extern const PRIVKEY                g_privkeyMeterCert;
extern const PUBKEY                 g_pubkeyMeteringCertVerify;
extern const PUBKEY                 g_pubkeyRootMeteringCert;

EXIT_PK_NAMESPACE;

#endif /* __DRM_METER_CONSTANTS_H */

