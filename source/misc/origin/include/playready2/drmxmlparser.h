/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/


#ifndef __DRMXMLPARSER_H__
#define __DRMXMLPARSER_H__

#include <drmtypes.h>
#include <oemcryptoctx.h>
#include <oemshahmac.h>

ENTER_PK_NAMESPACE;

/*
** UNICODE
*/

DRM_API DRM_RESULT DRM_CALL DRM_XML_GetNode(
    __in      const DRM_CONST_STRING *f_pdstrXML,
    __in      const DRM_CONST_STRING *f_pdstrTag,
    __in_opt  const DRM_CONST_STRING *f_pdstrAttrName,
    __in_opt  const DRM_CONST_STRING *f_pdstrAttrValue,
    __in      const DRM_DWORD         f_iNode,
    __out_opt       DRM_CONST_STRING *f_pdstrXMLNode,
    __out_opt       DRM_CONST_STRING *f_pdstrXMLNodeData );

DRM_API DRM_RESULT DRM_CALL DRM_XML_GetAndDecryptNode(
    __in      const DRM_CONST_STRING   *f_pdstrXML,
    __in      const DRM_CONST_STRING   *f_pdstrTag,
    __in_opt  const DRM_CONST_STRING   *f_pdstrAttrName,
    __in_opt  const DRM_CONST_STRING   *f_pdstrAttrValue,
    __in      const DRM_DWORD           f_iNode,
    __in            DRM_CRYPTO_CONTEXT *f_pCryptoContext,
    __in      const PRIVKEY            *f_pPrivkey,
    __out_opt       DRM_CONST_STRING   *f_pdstrXMLNode,
    __out_opt       DRM_CONST_STRING   *f_pdstrXMLNodeData );

DRM_API DRM_RESULT DRM_CALL DRM_XML_GetAndVerifyNode(
    __in      const DRM_CONST_STRING   *f_pdstrXML,
    __in      const DRM_CONST_STRING   *f_pdstrTag,
    __in_opt  const DRM_CONST_STRING   *f_pdstrAttrName,
    __in_opt  const DRM_CONST_STRING   *f_pdstrAttrValue,
    __in      const DRM_DWORD           f_iNode,
    __in            DRM_CRYPTO_CONTEXT *f_pCryptoContext,
    __in      const PUBKEY             *f_pPubkey,
    __in            DRM_BOOL            f_fIncludeTag,
    __in      const DRM_CONST_STRING   *f_pdstrB64Signature,
    __out_opt       DRM_CONST_STRING   *f_pdstrXMLNode,
    __out_opt       DRM_CONST_STRING   *f_pdstrXMLNodeData );

#define DRM_XML_HASH_INCLUDE_TAGS   TRUE
#define DRM_XML_HASH_EXCLUDE_TAGS   FALSE

DRM_API DRM_RESULT DRM_CALL DRM_XML_GetAndVerifyKeyedHashNode(
    __in                     const DRM_CONST_STRING *f_pdstrXML,
    __in                     const DRM_CONST_STRING *f_pdstrTag,
    __in                     const DRM_CONST_STRING *f_pdstrAttrName,
    __in                     const DRM_CONST_STRING *f_pdstrAttrValue,
    __in                     const DRM_DWORD         f_iNode,
    __in                           DRM_HMAC_CONTEXT *f_pHmacContext,
    __in_ecount(f_cbKeyHash) const DRM_BYTE         *f_pbHashkey,
    __in                           DRM_DWORD         f_cbHashkey,
    __in                           DRM_BOOL          f_fIncludeTag,
    __in                     const DRM_CONST_STRING *f_pdstrB64Signature,
    __out                          DRM_CONST_STRING *f_pdstrXMLNode,
    __out                          DRM_CONST_STRING *f_pdstrXMLNodeData );

DRM_API DRM_RESULT DRM_CALL DRM_XML_GetNodeAttribute(
    __in  const DRM_CONST_STRING *f_pdstrXMLNode,
    __in  const DRM_CONST_STRING *f_pdstrAttrName,
    __out       DRM_CONST_STRING *f_pdstrAttrValue );

DRM_API DRM_RESULT DRM_CALL DRM_XML_GetNodeCData(
    __in  const DRM_CONST_STRING *f_pdstrXMLNode,
    __out       DRM_CONST_STRING *f_pdstrCData );

DRM_API DRM_RESULT DRM_CALL DRM_XML_GetSubNode(
    __in      const DRM_CONST_STRING *f_pdstrXML,
    __in      const DRM_CONST_STRING *f_pdstrTag,
    __in_opt  const DRM_CONST_STRING *f_pdstrAttrName,
    __in_opt  const DRM_CONST_STRING *f_pdstrAttrValue,
    __in      const DRM_DWORD         f_iNode,
    __out_opt       DRM_CONST_STRING *f_pdstrXMLNode,
    __out_opt       DRM_CONST_STRING *f_pdstrXMLNodeData,
    __in            DRM_DWORD         f_iLayer );

DRM_API DRM_RESULT DRM_CALL DRM_XML_GetAndDecryptSubNode(
    __in      const DRM_CONST_STRING   *f_pdstrXML,
    __in      const DRM_CONST_STRING   *f_pdstrTag,
    __in_opt  const DRM_CONST_STRING   *f_pdstrAttrName,
    __in_opt  const DRM_CONST_STRING   *f_pdstrAttrValue,
    __in      const DRM_DWORD           f_iNode,
    __in            DRM_CRYPTO_CONTEXT *f_pCryptoContext,
    __in      const PRIVKEY            *f_pPrivkey,
    __out_opt       DRM_CONST_STRING   *f_pdstrXMLNode,
    __out_opt       DRM_CONST_STRING   *f_pdstrXMLNodeData,
    __in            DRM_DWORD           f_iLayer );

DRM_API DRM_RESULT DRM_CALL DRM_XML_GetAndVerifySubNode(
    __in      const DRM_CONST_STRING   *f_pdstrXML,
    __in      const DRM_CONST_STRING   *f_pdstrTag,
    __in_opt  const DRM_CONST_STRING   *f_pdstrAttrName,
    __in_opt  const DRM_CONST_STRING   *f_pdstrAttrValue,
    __in      const DRM_DWORD           f_iNode,
    __in            DRM_CRYPTO_CONTEXT *f_pCryptoContext,
    __in      const PUBKEY             *f_pPubkey,
    __in            DRM_BOOL            f_fIncludeTag,
    __in      const DRM_CONST_STRING   *f_pdstrB64Signature,
    __out_opt       DRM_CONST_STRING   *f_pdstrXMLNode,
    __out_opt       DRM_CONST_STRING   *f_pdstrXMLNodeData,
    __in            DRM_DWORD           f_iLayer );

DRM_API DRM_RESULT DRM_CALL DRM_XML_GetAndVerifyKeyedHashSubNode(
    __in                     const DRM_CONST_STRING *f_pdstrXML,
    __in                     const DRM_CONST_STRING *f_pdstrTag,
    __in                     const DRM_CONST_STRING *f_pdstrAttrName,
    __in                     const DRM_CONST_STRING *f_pdstrAttrValue,
    __in                     const DRM_DWORD         f_iNode,
    __in                           DRM_HMAC_CONTEXT *f_pcontextHMAC,
    __in_ecount(f_cbKeyHash) const DRM_BYTE         *f_pbKeyHash,
    __in                           DRM_DWORD         f_cbKeyHash,
    __in                           DRM_BOOL          f_fIncludeTag,
    __in                     const DRM_CONST_STRING *f_pdstrB64Signature,
    __out                          DRM_CONST_STRING *f_pdstrNode,
    __out                          DRM_CONST_STRING *f_pdstrNodeData,
    __in                           DRM_DWORD         f_iLayer );

DRM_API DRM_RESULT DRM_CALL DRM_XML_GetSubNodeByPath(
    __in      const DRM_CONST_STRING *f_pdstrXML,
    __in      const DRM_CONST_STRING *f_pdstrXMLNode,
    __in_opt  const DRM_CONST_STRING *f_pdstrAttrName,
    __in_opt  const DRM_CONST_STRING *f_pdstrAttrValue,
    __out_opt       DRM_CONST_STRING *f_pdstrXMLNodeOut,
    __out_opt       DRM_CONST_STRING *f_pdstrXMLDataOut,
    __in            DRM_WCHAR         f_chSeparator );


DRM_API DRM_RESULT DRM_CALL DRM_XML_EnumNextNode(
    __in  const DRM_CONST_STRING *f_pdstrXML,
    __out       DRM_CONST_STRING *f_pdstrTag,
    __out_opt   DRM_CONST_STRING *f_pdstrXMLNode,
    __out_opt   DRM_CONST_STRING *f_pdstrXMLNodeData,
    __out_opt   DRM_CONST_STRING *f_pdstr1stAttrName,
    __out_opt   DRM_CONST_STRING *f_pdstr1stAttrValue,
    __out       DRM_BOOL         *f_pfIsLeafNode );

DRM_API DRM_RESULT DRM_CALL DRM_XML_EnumNextSubNode(
    __in  const DRM_CONST_STRING *f_pdstrXML,
    __out       DRM_CONST_STRING *f_pdstrTag,
    __out_opt   DRM_CONST_STRING *f_pdstrXMLNode,
    __out_opt   DRM_CONST_STRING *f_pdstrXMLNodeData,
    __out_opt   DRM_CONST_STRING *f_pdstr1stAttrName,
    __out_opt   DRM_CONST_STRING *f_pdstr1stAttrValue,
    __out       DRM_BOOL         *f_pfIsLeafNode,
    __in        DRM_DWORD         f_iLayer );

/*
** ANSI
*/

DRM_API DRM_RESULT DRM_CALL DRM_XML_GetNodeA(
    __in_ecount( f_padstrXML->m_ich + f_padstrXML->m_cch ) const DRM_CHAR              *f_pszBase,
    __in                                                   const DRM_SUBSTRING         *f_padstrXML,
    __in                                                   const DRM_ANSI_CONST_STRING *f_padstrTag,
    __in_opt                                               const DRM_ANSI_CONST_STRING *f_padstrAttrName,
    __in_opt                                               const DRM_ANSI_CONST_STRING *f_padstrAttrValue,
    __in                                                   const DRM_DWORD              f_iNode,
    __out_opt                                                    DRM_SUBSTRING         *f_psubstrXMLNode,
    __out_opt                                                    DRM_SUBSTRING         *f_psubstrXMLNodeData );

DRM_API DRM_RESULT DRM_CALL DRM_XML_GetSubNodeA(
    __in_ecount( f_padstrXML->m_ich + f_padstrXML->m_cch ) const DRM_CHAR              *f_pszBase,
    __in                                                   const DRM_SUBSTRING         *f_padstrXML,
    __in                                                   const DRM_ANSI_CONST_STRING *f_padstrTag,
    __in_opt                                               const DRM_ANSI_CONST_STRING *f_padstrAttrName,
    __in_opt                                               const DRM_ANSI_CONST_STRING *f_padstrAttrValue,
    __in                                                   const DRM_DWORD              f_iNode,
    __out_opt                                                    DRM_SUBSTRING         *f_psubstrXMLNode,
    __out_opt                                                    DRM_SUBSTRING         *f_psubstrXMLNodeData,
    __in                                                         DRM_DWORD              f_iLayer );

DRM_API DRM_RESULT DRM_CALL DRM_XML_GetNodeAttributeA(
    __in_ecount( f_padstrXML->m_ich + f_padstrXML->m_cch ) const DRM_CHAR              *f_pszBase,
    __in                                                   const DRM_SUBSTRING         *f_padstrXML,
    __in                                                   const DRM_ANSI_CONST_STRING *f_padstrAttrName,
    __out                                                        DRM_SUBSTRING         *f_psubstrAttrValue );

DRM_API DRM_RESULT DRM_CALL DRM_XML_GetNodeCDataA(
    __in_ecount( f_pdasstrXML->m_ich + f_pdasstrXML->m_cch ) const DRM_CHAR      *f_pszXMLBase,
    __in                                                     const DRM_SUBSTRING *f_pdasstrXML,
    __out                                                          DRM_SUBSTRING *f_pdasstrCData );

DRM_API DRM_RESULT DRM_CALL DRM_XML_GetSubNodeByPathA(
    __in_ecount( f_pdasstrXML->m_ich + f_pdasstrXML->m_cch ) const DRM_CHAR              *f_pszBase,
    __in                                                     const DRM_SUBSTRING         *f_pdasstrXML,
    __in                                                     const DRM_ANSI_CONST_STRING *f_pdastrNodePath,
    __in_opt                                                 const DRM_ANSI_CONST_STRING *f_pdastrAttrName,
    __in_opt                                                 const DRM_ANSI_CONST_STRING *f_pdastrAttrValue,
    __out_opt                                                      DRM_SUBSTRING         *f_pdasstrXMLNodeOut,
    __out_opt                                                      DRM_SUBSTRING         *f_pdasstrXMLDataOut,
    __in                                                           DRM_CHAR               f_chSeparator );

DRM_API DRM_RESULT DRM_CALL DRM_XML_EnumNextNodeA(
    __in_ecount( f_pdasstrXML->m_ich + f_pdasstrXML->m_cch ) const DRM_CHAR      *f_pszBase,
    __in                                                     const DRM_SUBSTRING *f_pdasstrXML,
    __in                                                     const DRM_DWORD      f_iNode,
    __out                                                          DRM_SUBSTRING *f_pdasstrTag,
    __out_opt                                                      DRM_SUBSTRING *f_pdasstrNode,
    __out_opt                                                      DRM_SUBSTRING *f_pdasstrNodeData,
    __out_opt                                                      DRM_SUBSTRING *f_pdasstr1stAttrName,
    __out_opt                                                      DRM_SUBSTRING *f_pdasstr1stAttrValue );

DRM_API DRM_RESULT DRM_CALL DRM_XML_CountMatchingNodesA(
    __in_ecount( f_pdasstrXML->m_ich + f_pdasstrXML->m_cch ) const DRM_CHAR              *f_pszBase,
    __in                                                     const DRM_SUBSTRING         *f_pdasstrXML,
    __in_opt                                                 const DRM_ANSI_CONST_STRING *f_pdasstrTag,
    __in_opt                                                 const DRM_ANSI_CONST_STRING *f_pdasstr1stAttrName,
    __in_opt                                                 const DRM_ANSI_CONST_STRING *f_pdasstr1stAttrValue,
    __out                                                          DRM_DWORD             *f_cMatchingNodes );

DRM_API DRM_BOOL DRM_CALL DRM_XML_Validate(
    __in const DRM_CONST_STRING *f_pdstrXML );

DRM_API DRM_RESULT DRM_CALL DRM_XML_TranslateXMLError(
    __in DRM_RESULT f_drXML );

DRM_API DRM_RESULT DRM_CALL DRM_XMU_MatchNodeFromTemplate(
    __in  const   DRM_CONST_STRING    *f_pdstrXmlNodeList,
    __in  const   DRM_CONST_STRING    *f_pdstrXmlTemplate,
    __in          DRM_BOOL             f_fAttributeMatch,
    __out         DRM_BOOL            *f_pfMatch );

EXIT_PK_NAMESPACE;

#endif      /* __DRMXMLPARSER_H__ */



