/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/


#ifndef __DRMXMLBUILDERA_H__
#define __DRMXMLBUILDERA_H__

#include <drmresults.h>
#include <drmtypes.h>
#include <oemaes.h>
#include <drmxmlbuilder.h>

ENTER_PK_NAMESPACE;

#define CB_XMB_EXTRA_A                      100
#define CCH_CDATA_EXTRA_A                   12
#define CCH_CDATA_REQUIRED_A( f_pdastr )    ( ( f_pdastr )->cchString + CCH_CDATA_EXTRA_A )

#define DRM_XMB_OVERHEAD_A                  ( SIZEOF ( _XMBContextA ) + CB_XMB_EXTRA_A )

#define DRM_XMB_RequiredCharsForTagA        DRM_XMB_RequiredCharsForTag

#define DRM_XMB_RequiredCharsForTagNoCloseA DRM_XMB_RequiredCharsForTagNoClose

#define DRM_XMB_RequiredCharsForAttributeA DRM_XMB_RequiredCharsForAttribute

extern const DRM_EXPORT_VAR DRM_DWORD g_cbXMLBuilderMinimumA;

/* XML builder context. */
typedef struct _tagXMBContextA
{
    /*
    ** Usage of buffer:
    **
    ** This context buffer is allocated by user at DRM_XMB_CreateDocumentA().
    ** The XML string is built on the way when each of the API calls are made.
    **
    ** The XML output string being generated grows from lower address to higher address. The end
    ** of the XML output string is indicated by ichNextString. All opened nodes' location at the
    ** buffer and the length of the tag name string are saved on a stack that grows from from higher
    ** address to lower address. The top of the stack is indicated by ichNextOpenNode.
    **
    ** When ichNextString and ichNextOpenNode collides, there is not enough memory available.
    */

    /* !!! Caller is ensuring only 2 byte alignment. Never add any member variable greater than 2 bytes. */

    /* Flag indicating whether the XML builder context has been initialized. */
    DRM_BOOL fInited;

    /* Max stack space used for nested nodes */
    DRM_DWORD cbMaxStackUsed;

    /* Size (number of bytes) of the XML builder context. */
    DRM_DWORD cbContext;

    /* The current pointer to the top of the stack to keep the open nodes. */
    DRM_DWORD ichNextOpenNode;

    /* The current pointer to the output buffer for the XML output. */
    DRM_DWORD ichNextString;

    /* Size (number of CHARs) of internal buffer. */
    DRM_DWORD cchBuffer;

    /* The internal buffer. */
    DRM_CHAR  rgchXML [1];
} _XMBContextA;


/*
*******************************************************************************
** API methods
*******************************************************************************
*/
DRM_API DRM_RESULT DRM_CALL DRM_XMB_CalcNodeSizeA(
    __in  const _XMBContextA  *f_pbContextXMLA,
    __out       DRM_DWORD     *f_pcchContent,  /* ch count of node content */
    __out       DRM_DWORD     *f_pcchTagName); /* ch count of node tag */

DRM_API DRM_RESULT DRM_CALL DRM_XMB_CreateDocumentA(
    __in                      const DRM_DWORD              f_cbXMBContextA,
    __inout_bcount(f_cbXMBContextA) DRM_BYTE              *f_pbXMBContextA,
    __in                      const DRM_ANSI_CONST_STRING *f_pdastrRootNode );

DRM_API DRM_RESULT DRM_CALL DRM_XMB_CloseDocumentA(
    __inout _XMBContextA  *f_poXMBContextA,
    __out   DRM_SUBSTRING *f_pdasstrXML );

DRM_API DRM_RESULT DRM_CALL DRM_XMB_OpenNodeA(
    __inout       _XMBContextA          *f_poXMBContextA,
    __in    const DRM_ANSI_CONST_STRING *f_pdastrNodeName );

DRM_API DRM_RESULT DRM_CALL DRM_XMB_CloseCurrNodeA(
    __inout   _XMBContextA  *f_pbXMBContextA,
    __out_opt DRM_SUBSTRING *f_pdasstrXMLFragment );

DRM_API DRM_RESULT DRM_CALL DRM_XMB_AESEncryptAndCloseCurrNodeA(
    __inout       _XMBContextA  *f_pbContextXMLA,
    __in    const DRM_AES_KEY   *f_pkeyAES,
    __in          DRM_DWORD      f_dwNonce,
    __out         DRM_SUBSTRING *f_pdasstrXMLFragment );

DRM_API DRM_RESULT DRM_CALL DRM_XMB_HashAndCloseCurrNodeA(
    __inout                                                   _XMBContextA      *f_pbContextXMLA,
    __in                                                      DRM_SHA1_CONTEXT  *f_pcontextSHA,
    __in                                                      DRM_BOOL           f_fIncludeTag,
    __out_bcount(DRM_SHA1_DIGEST_LEN)                         DRM_BYTE           f_rgbSHA [__CB_DECL(DRM_SHA1_DIGEST_LEN)],
    __out_ecount(DRM_SHA1_B64ENC_DIGEST_LEN)                  DRM_CHAR           f_rgchSHA[__CB_DECL(DRM_SHA1_B64ENC_DIGEST_LEN)],
    __out_opt                                                 DRM_SUBSTRING     *f_pdasstrXMLFragment );

DRM_API DRM_RESULT DRM_CALL DRM_XMB_AddAttributeA(
    __inout       _XMBContextA          *f_poXMBContextA,
    __in    const DRM_ANSI_CONST_STRING *f_pdastrAttrLabel,
    __in    const DRM_ANSI_CONST_STRING *f_pdastrAttrValue );

DRM_API DRM_RESULT DRM_CALL DRM_XMB_AddDataA(
    __inout       _XMBContextA          *f_poXMBContextA,
    __in    const DRM_ANSI_CONST_STRING *f_pdastrData );

DRM_API DRM_RESULT DRM_CALL DRM_XMB_WriteTagA(
    __inout        _XMBContextA *f_poXMBContextA,
    __in     const DRM_ANSI_CONST_STRING *f_pdastrTag,
    __in_opt const DRM_ANSI_CONST_STRING *f_pdastrData,
    __in_opt const DRM_ANSI_CONST_STRING *f_pdastrAttrLabel,
    __in_opt const DRM_ANSI_CONST_STRING *f_pdastrAttrValue,
    __in           WriteTagType f_wtt );

DRM_API DRM_RESULT DRM_CALL DRM_XMB_GetXMLBaseA(
    __inout _XMBContextA *f_poXMBContextA,
    __out   DRM_CHAR    **f_ppchBase );

DRM_API DRM_RESULT DRM_CALL DRM_XMB_AddCDataA(
    __inout       _XMBContextA          *f_poXMBContextA,
    __in    const DRM_ANSI_CONST_STRING *f_pdastrCData );

DRM_API DRM_RESULT DRM_CALL DRM_XMB_WriteCDATATagA(
    __inout       _XMBContextA *f_poXMBContextA,
    __in    const DRM_ANSI_CONST_STRING *f_pdastrTag,
    __in    const DRM_ANSI_CONST_STRING *f_pdastrCData,
    __in    const DRM_ANSI_CONST_STRING *f_pdastrAttrLabel,
    __in    const DRM_ANSI_CONST_STRING *f_pdastrAttrValue,
    __in          WriteTagType f_wtt );

DRM_API DRM_RESULT DRM_CALL DRM_XMB_ReserveSpaceA(
    __inout       _XMBContextA  *f_poXMBContextA,
    __in          DRM_DWORD      f_cchAlignment,
    __in    const DRM_DWORD      f_cchData,
    __out         DRM_SUBSTRING *f_pdasstrData );

DRM_API DRM_RESULT DRM_CALL DRM_XMB_ShiftDataFromCurrentPositionA(
    __inout       _XMBContextA *f_poXMBContextA,
    __in    const DRM_DWORD     f_cchShift,
    __in    const DRM_DWORD     f_cchData );

DRM_API DRM_RESULT DRM_CALL DRM_XMB_ShiftCurrentPointerA(
    __inout       _XMBContextA *f_poXMBContextA,
    __in    const DRM_DWORD     f_cchShift );

DRM_API DRM_RESULT DRM_CALL DRM_XMB_GetCurrentBufferPointerA(
    __inout _XMBContextA *f_poXMBContextA,
    __in    DRM_BOOL      f_fAligned,
    __out   DRM_CHAR    **f_ppchBufferPointer );

DRM_API DRM_RESULT DRM_CALL DRM_XMB_AppendNodeA(
    __inout       _XMBContextA          *f_poXMBContextA,
    __in    const DRM_ANSI_CONST_STRING *f_pdastrXmlString );

EXIT_PK_NAMESPACE;

#endif /* __DRMXMLBUILDERA_H__ */

