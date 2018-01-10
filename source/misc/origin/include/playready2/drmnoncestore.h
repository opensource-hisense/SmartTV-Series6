/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRM_NONCE_STORE_H
#define __DRM_NONCE_STORE_H

#include <drmdatastore.h>
#include <drmembeddedstore_impl.h>
#include <drmlicstore.h>

ENTER_PK_NAMESPACE;

/* The data structure of a nonce token. */
typedef struct _tag_DRM_NONCE_TOKEN
{
    /* Nonce value. */
    DRM_ID m_oNonce;

    /* Associated KID. */
    DRM_ID m_oKID;

    /* Flag indicating whether the token has an associated license. */
    DRM_BOOL m_fAllocated;
} DRM_NONCE_TOKEN;

/* The context of the nonce store. */
typedef struct _tagDRM_NONCESTORE_CONTEXT_INTERNAL
{
    /* Pointer to an OEM context. */
    DRM_VOID *m_pvOEMContext;

    /* Data store context. */
    DRM_DST m_oDataStore;

    /* Data store context using embedded store implementation. */
    DRM_EST_CONTEXT m_oESTContext;

    /* License store context. */
    DRM_LICSTORE_CONTEXT *m_poLicStoreContext;

    /* Nonce store buffer. */
    DRM_BYTE *m_pbBuffer;

    /* Size of nonce store buffer. */
    DRM_DWORD m_cbBuffer;

    /* Flag indicating whether this structure is initialized. */
    DRM_BOOL m_fInited;

    /* A single nonce token. */
    DRM_NONCE_TOKEN m_oToken;
} DRM_NONCESTORE_CONTEXT_INTERNAL;

/* The context of the nonce store in the form of a BLOB. */
typedef struct __tagDRM_NONCESTORE_CONTEXT
{
    DRM_BYTE rgbOpaqueData[ __CB_DECL( SIZEOF( DRM_NONCESTORE_CONTEXT_INTERNAL ) ) ];
} DRM_NONCESTORE_CONTEXT;

DRM_API DRM_RESULT DRM_CALL DRM_NST_Open(
    __in_opt DRM_VOID *f_pvOEMContext,
    __in_bcount( f_cbNonceStore ) DRM_BYTE *f_pbNonceStore,
    __in DRM_DWORD f_cbNonceStore,
    __out DRM_LICSTORE_CONTEXT *f_poLicStoreContext,
    __out DRM_NONCESTORE_CONTEXT *f_poNonceStore );

DRM_API DRM_RESULT DRM_CALL DRM_NST_Close(
    __in DRM_NONCESTORE_CONTEXT *f_poNonceStore );

DRM_API DRM_RESULT DRM_CALL DRM_NST_GenerateNonce(
    __in DRM_NONCESTORE_CONTEXT *f_poNonceStore,
    __out DRM_ID *f_poNonce );

DRM_API DRM_RESULT DRM_CALL DRM_NST_AddLicense(
    __in                       DRM_NONCESTORE_CONTEXT *f_poNonceStore,
    __in                       DRM_DWORD               f_cbLicense,
    __in_bcount( f_cbLicense ) DRM_BYTE               *f_pbLicense,
    __in const                 DRM_KID                *f_poKID,
    __in const                 DRM_LID                *f_poLID,
    __in                       DRM_DWORD               f_dwPriority );

EXIT_PK_NAMESPACE;

#endif /* __DRM_NONCE_STORE_H */
