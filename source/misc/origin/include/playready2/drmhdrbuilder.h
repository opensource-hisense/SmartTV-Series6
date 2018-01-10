/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/


#ifndef __DRMHEADERBUILDER_H__
#define __DRMHEADERBUILDER_H__

ENTER_PK_NAMESPACE;

#define LOCALSTACKSIZE  200

/*************************************************************************
** Local data structures
**************************************************************************/
typedef enum
{
    eHBCreating=0x0,
    eHBInited,
    eHBAddingData,
    eHBAddedData,
    eHBSigning,
    eHBCreated
} _EHBContextState;

/*
** Header Builder context stucture. This structure contains the following:
** - A Local stack
** - XML Builder context
** The XML Builder context is physically located at end of the buffer after init - for easier
** realloc a bigger size when necessary.
*/
typedef struct _tag_HBContext
{
    DRM_DWORD                wContextSize;
    _EHBContextState         eState;
    DRM_CONTENT_SET_PROPERTY eHeaderType;
    DRM_DWORD                dwItemsAdded;     /* copied from old context when DRM_LA_ReallocRequest() is called */
    DRM_DWORD                dwItemsTracked;       /* 0 when DRM_LA_ReallocRequest() is called */
    DRM_STRING               szXMLString;
    DRM_BOOL                 fKIDAdded;
    DRM_KID                  KID;
    DRM_BOOL                 fLAINFOAdded;
    DRM_BOOL                 fChecksumAdded;
    DRM_BYTE                 rgbLocalStack[__CB_DECL(LOCALSTACKSIZE)];     /* local stack buffer */
    _XMBContext             *pbXmlContext;
    _XMBContext              rgbXmlContext [1];
} _HBContext;

/*
** Header Builder
*/

/**********************************************************************
** Function:    DRM_HB_CreateHeader
** Synopsis:
** Arguments:   [pbContext] --
** Returns:
** Notes:
***********************************************************************/
DRM_API DRM_RESULT DRM_CALL DRM_HB_CreateHeader(
    __in_bcount_opt( *pcbHBContext ) DRM_BYTE                 *pbHBContext,
    __in                             DRM_CONTENT_SET_PROPERTY  eHeaderType,
    __inout                          DRM_DWORD                *pcbHBContext );

DRM_API DRM_RESULT DRM_CALL DRM_HB_CloseHeader(
    __in_bcount( SIZEOF( _HBContext ) )       DRM_BYTE           *pbHBContext,
    __in                                      DRM_CRYPTO_CONTEXT *pCryptoContext,
    __in                                const DRM_CONST_STRING   *pdstrPrivKey,      /* base64 encoded */
    __deref_out_bcount( *pcbHeaderXML )       DRM_BYTE          **ppbHeaderXML,
    __out                                     DRM_DWORD          *pcbHeaderXML );

DRM_API DRM_RESULT DRM_CALL DRM_HB_ReallocHeader(
    __in_bcount( SIZEOF( _HBContext ) ) DRM_BYTE  *pbOldHBContext,
    __in                                DRM_DWORD  cbNewHBContext,
    __in_bcount( cbNewHBContext )       DRM_BYTE  *pbNewHBContext );

DRM_API DRM_RESULT DRM_CALL DRM_HB_GetContextSize(
    __in_bcount( SIZEOF( _HBContext ) ) const DRM_BYTE  *pbHBContext,
    __out                                     DRM_DWORD *pcbContext );

DRM_API DRM_RESULT DRM_CALL DRM_HB_OpenNode(
    __in_bcount( SIZEOF( _HBContext ) )       DRM_BYTE         *pbHBContext,
    __in                                const DRM_CONST_STRING *pdstrNodeName );

DRM_API DRM_RESULT DRM_CALL DRM_HB_CloseCurrNode(
    __in_bcount( SIZEOF( _HBContext ) ) DRM_BYTE *pbHBContext );

DRM_API DRM_RESULT DRM_CALL DRM_HB_AddData(
    __in_bcount( __CB_DECL( SIZEOF( _HBContext ) ) )       DRM_BYTE         *pbHBContext,
    __in                                             const DRM_CONST_STRING *pdstrXMLData );

DRM_API DRM_RESULT DRM_CALL DRM_HB_SetKeyID(
    __in_bcount( SIZEOF( _HBContext ) )       DRM_BYTE         *pbHBContext,
    __in                                const DRM_CONST_STRING *pdstrKID );      /* base64 encoded */

DRM_API DRM_RESULT DRM_CALL DRM_HB_SetLicAcqUrl(
    __in_bcount( SIZEOF( _HBContext ) )       DRM_BYTE         *pbHBContext,
    __in                                const DRM_CONST_STRING *pdstrURL );

/*
** Perform checksum algo to the given content key and set the check to header
*/
DRM_API DRM_RESULT DRM_CALL DRM_HB_SetChecksum(
    __in_bcount( SIZEOF( _HBContext ) )       DRM_BYTE         *pbHBContext,
    __in                                const DRM_CONST_STRING *pdstrContentKey );     /* base64 encoded */

DRM_API DRM_RESULT DRM_CALL DRM_HB_SetAttribute(
    __in_bcount( SIZEOF( _HBContext ) )       DRM_BYTE         *pbHBContext,
    __in                                const DRM_CONST_STRING *pdstrAttrName,
    __in                                const DRM_CONST_STRING *pdstrAttrValue );


EXIT_PK_NAMESPACE;

#endif /* __DRMHEADERBUILDER_H__ */


