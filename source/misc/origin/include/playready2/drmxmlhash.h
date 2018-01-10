/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRM_XMLHASH__
#define __DRM_XMLHASH__

#include <oemxmlhash.h>

ENTER_PK_NAMESPACE;

DRM_API DRM_BOOL DRM_CALL DRM_XMLHASH_IsXmlHashSupported(DRM_VOID);
DRM_API DRM_BOOL DRM_CALL DRM_XMLHASH_IsXmlHashUnsupported(DRM_VOID);

DRM_API DRM_RESULT DRM_CALL DRM_XMLHASH_Update(
    __in DRM_XML_HASH_CONTEXT *f_poContext,
    __in const DRM_XML_HASH_SIG *f_poSig,
    __in const DRM_CONST_STRING *f_pdstrXML,
    __in const DRM_CONST_STRING *f_pdstrNode,
    __in const DRM_CONST_STRING *f_pdstrNodeData );

DRM_API DRM_RESULT DRM_CALL DRM_XMLHASH_Lookup(
    __in DRM_XML_HASH_CONTEXT *f_poContext,
    __in const DRM_XML_HASH_SIG *f_poSig,
    __in const DRM_CONST_STRING *f_pdstrXML,
    __in const DRM_CONST_STRING *f_pdstrTag,
    __out DRM_CONST_STRING *f_pdstrNodeOut,
    __out DRM_CONST_STRING *f_pdstrNodeDataOut );

DRM_API DRM_RESULT DRM_CALL DRM_XMLHASH_CalcParamSig(
    __in const DRM_XML_HASH_CONTEXT *f_poContext,
    __in const DRM_CONST_STRING *f_pdstrXML,
    __in const DRM_CONST_STRING *f_pdstrTag,
    __in const DRM_DWORD f_iNode,
    __in const DRM_DWORD f_iLayer,
    __out DRM_XML_HASH_SIG *f_poSig );

DRM_API DRM_RESULT DRM_CALL DRM_XMLHASH_GetContext(
    __out DRM_XML_HASH_CONTEXT **f_ppoContext );

DRM_API DRM_RESULT DRM_CALL DRM_XMLHASH_Start( DRM_VOID );

DRM_API DRM_RESULT DRM_CALL DRM_XMLHASH_Stop( DRM_VOID );

DRM_API DRM_RESULT DRM_CALL DRM_XMLHASH_Init( DRM_VOID );

DRM_API DRM_RESULT DRM_CALL DRM_XMLHASH_UnInit( DRM_VOID );

DRM_API DRM_RESULT DRM_CALL DRM_XMLHASH_Cleanup( DRM_VOID );

EXIT_PK_NAMESPACE;

#endif /* __DRM_XMLHASH__ */

