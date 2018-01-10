/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/


#ifndef __OEMXMLHASH_H__
#define __OEMXMLHASH_H__

#include <drmerr.h>
#include <drmstkalloc.h>

ENTER_PK_NAMESPACE;

/*
** Flag indicating whehther XMLHASH statistics is turned on.
** Statistics will add a few more fields to the runtime data
** structures used by XML hash.
*/
#define ENABLE_OEM_XMLHASH_STATISTICS   0

/* Maximum number of hash table slots. */
#define MAX_XML_ROOT_HASH       32

/* Maximum size of stack buffer of each XML Hash context. */
#define MAX_XML_HASH_STACK      1024

/* Maximum number of threads that can use XML hash at the same time. */
#define MAX_XML_HASH_THREAD     256

/*
** Data structure that stores the signature based on
** the parameters used for XML substring search.
*/
typedef struct __tagDRM_XML_HASH_SIG
{
    /* String hash 1 of the source XML string. */
    DRM_DWORD m_dwSourceHash1;

    /* String hash 2 of the source XML string. */
    DRM_DWORD m_dwSourceHash2;

    /* String hash 1 of the XML tag to be searched. */
    DRM_DWORD m_dwTagHash1;

    /* String hash 2 of the XML tag to be searched. */
    DRM_DWORD m_dwTagHash2;

    /* Occurence of the XML tag within the source XML string. */
    DRM_DWORD m_dwNode;

    /* Number of XML hierarchy levels to skip for the search. */
    DRM_DWORD m_dwLayer;

#if ENABLE_OEM_XMLHASH_STATISTICS
    /* Combined length of the source and tag strings. */
    DRM_DWORD m_dwLen;
#endif /* ENABLE_OEM_XMLHASH_STATISTICS */
} DRM_XML_HASH_SIG;

/*
** Data structure that defines a hash node for the mapping
** between DRM_XML_HASH_SIG and the XML search result.
*/
typedef struct __tagDRM_XML_HASH_NODE
{
    /* The signature of parameters of a XML substring search. */
    DRM_XML_HASH_SIG m_oSig;

    /* The search result (location) of the result XML node (including tag). */
    DRM_SUBSTRING m_dasstrNode;

    /* The search result (location) of the result XML node data (excluding tag). */
    DRM_SUBSTRING m_dasstrNodeData;

#if ENABLE_OEM_XMLHASH_STATISTICS
    /* Total number of hash match. */
    DRM_DWORD m_dwHit;
#endif /* ENABLE_OEM_XMLHASH_STATISTICS */

    struct __tagDRM_XML_HASH_NODE *m_poNext;
} DRM_XML_HASH_NODE;

/* Data structure of the per-thread XML hash context. */
typedef struct __tagDRM_XML_HASH_CONTEXT
{
    /* Thread ID. */
    DRM_DWORD m_dwThreadID;

    /* Stack allocator context. */
    DRM_STACK_ALLOCATOR_CONTEXT m_oXMLHashStackContext;

    /* Flag indicating whether the data structure has been initialized. */
    DRM_BOOL m_fXMLHashStackInit;

    /* Buffer to support the stack allocation. */
    DRM_BYTE m_rgbXMLHashStackBuffer[ MAX_XML_HASH_STACK ];

    /* The hash table. */
    DRM_XML_HASH_NODE *m_rgpoHashNodes[ MAX_XML_ROOT_HASH ];
} DRM_XML_HASH_CONTEXT;

DRM_API DRM_RESULT Oem_XMLHash_Update(
    __in DRM_XML_HASH_CONTEXT *f_poContext,
    __in const DRM_XML_HASH_SIG *f_poSig,
    __in const DRM_CONST_STRING *f_pdstrXML,
    __in const DRM_CONST_STRING *f_pdstrNode,
    __in const DRM_CONST_STRING *f_pdstrNodeData );

DRM_API DRM_RESULT Oem_XMLHash_Lookup(
    __in DRM_XML_HASH_CONTEXT *f_poContext,
    __in const DRM_XML_HASH_SIG *f_poSig,
    __in const DRM_CONST_STRING *f_pdstrXML,
    __in const DRM_CONST_STRING *f_pdstrTag,
    __out DRM_CONST_STRING *f_pdstrNodeOut,
    __out DRM_CONST_STRING *f_pdstrNodeDataOut );

DRM_API DRM_RESULT Oem_XMLHash_CalcParamSig(
    __in const DRM_XML_HASH_CONTEXT *f_poContext,
    __in const DRM_CONST_STRING *f_pdstrXML,
    __in const DRM_CONST_STRING *f_pdstrTag,
    __in const DRM_DWORD f_iNode,
    __in const DRM_DWORD f_iLayer,
    __out DRM_XML_HASH_SIG *f_poSig );

DRM_API DRM_RESULT Oem_XMLHash_GetContext(
    __out DRM_XML_HASH_CONTEXT **f_ppoContext );

DRM_API DRM_RESULT Oem_XMLHash_Start( DRM_VOID );

DRM_API DRM_RESULT Oem_XMLHash_Stop( DRM_VOID );

DRM_API DRM_RESULT Oem_XMLHash_Init( DRM_VOID );

DRM_API DRM_RESULT Oem_XMLHash_UnInit( DRM_VOID );

DRM_API DRM_RESULT Oem_XMLHash_Cleanup( DRM_VOID );

EXIT_PK_NAMESPACE;

#endif /*__OEMXMLHASH_H__ */

