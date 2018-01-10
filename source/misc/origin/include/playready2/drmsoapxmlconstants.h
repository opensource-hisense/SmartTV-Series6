/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRM_SOAP_XML_CONSTANTS_H
#define __DRM_SOAP_XML_CONSTANTS_H

ENTER_PK_NAMESPACE;

/*
** -------------------------------------------------------------------
** XML strings used in the parsing of status code from server response
** -------------------------------------------------------------------
*/
extern const DRM_ANSI_CONST_STRING g_dastrSOAPExceptionRootPath;

extern const DRM_ANSI_CONST_STRING g_dastrSOAPExceptionSignaturePath;

extern const DRM_ANSI_CONST_STRING g_dastrSOAPExceptionCustomDataPath;

extern const DRM_ANSI_CONST_STRING g_dastrSOAPStatusCodePath;

extern const DRM_ANSI_CONST_STRING g_dastrSOAPGARDCustomDataPath;

extern const DRM_ANSI_CONST_STRING g_dastrSOAPGARDRedirectUrlPath;

extern const DRM_ANSI_CONST_STRING g_dastrSOAPGARDServiceIdPath;

extern const DRM_ANSI_CONST_STRING g_dastrSOAPGARDAccountIdPath;


/*
** -----------------------------------------------------
** XML strings used in the construction of SOAP envelope
** -----------------------------------------------------
*/
extern const DRM_ANSI_CONST_STRING g_dastrXMLRootTag;

extern const DRM_ANSI_CONST_STRING g_dastrSOAPEnvelopeTag;
extern const DRM_ANSI_CONST_STRING g_dastrSOAPEnvelopeAbbrevTag;
extern const DRM_ANSI_CONST_STRING g_dastrSOAPBodyTag;
extern const DRM_ANSI_CONST_STRING g_dastrSOAPBodyAbbrevTag;


extern const DRM_ANSI_CONST_STRING g_dastrSOAPEnvelopeAttrib1Name;
extern const DRM_ANSI_CONST_STRING g_dastrSOAPEnvelopeAttrib1Value;

extern const DRM_ANSI_CONST_STRING g_dastrSOAPEnvelopeAttrib2Name;
extern const DRM_ANSI_CONST_STRING g_dastrSOAPEnvelopeAttrib2Value;

extern const DRM_ANSI_CONST_STRING g_dastrSOAPEnvelopeAttrib3Name;
extern const DRM_ANSI_CONST_STRING g_dastrSOAPEnvelopeAttrib3Value;

extern const DRM_ANSI_CONST_STRING g_dastrSOAPPreserveSpaceAttribName;
extern const DRM_ANSI_CONST_STRING g_dastrSOAPPreserveSpaceAttribValue;

/*
** -------------------------------------------------------
** XML strings used in the construction of ClientInfo node
** -------------------------------------------------------
*/
extern const DRM_ANSI_CONST_STRING g_dastrReqTagClientInfo;
extern const DRM_ANSI_CONST_STRING g_dastrReqTagClientVersion;

EXIT_PK_NAMESPACE;

#endif /* __DRM_SOAP_XML_CONSTANTS_H */
