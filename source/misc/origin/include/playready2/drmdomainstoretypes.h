/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRM_DOMAIN_STORE_TYPES_H
#define __DRM_DOMAIN_STORE_TYPES_H

#include <drmsecurestoretypes.h>

ENTER_PK_NAMESPACE;

/* The context of the domain store. */
typedef struct _tagDomainStoreContextPrivate
{
    /* Pointer to the underlying DST. */
    DRM_DST *m_poDST;

    /* The underlying DST namespace context. */
    DRM_DST_NAMESPACE_CONTEXT m_oDSTNameSpaceContext;

    /* The underlying DST slot context. */
    DRM_DST_SLOT_CONTEXT m_oDSTSlotContext;

    /* The SST context. */
    DRM_SECSTORE_CONTEXT m_oSSTContext;

    /* Flag indicating whether the context has been initialized. */
    DRM_BOOL m_fInited;

#if DRM_OBFUS_NEED_PADDING
    DRM_VOID *m_rgpvWM7Padding[107];
#endif /* DRM_OBFUS_NEED_PADDING */
} DRM_DOMAINSTORE_CONTEXT_PRIVATE;

/* The context of the domain store in the form of a BLOB. */
typedef struct __tagDRM_DOMAINSTORE_CONTEXT
{
    DRM_BYTE rgbOpaqueData [ SIZEOF( DRM_DOMAINSTORE_CONTEXT_PRIVATE ) ];
} DRM_DOMAINSTORE_CONTEXT;

/* The enumeration context of the domain store. */
typedef struct __tagDRM_DOMAINSTORE_ENUM_CONTEXT
{
    /* The underlying domain store. */
    DRM_DST *m_poDomainStore;

    /* The underlying DST enumeration context. */
    DRM_DST_ENUM_CONTEXT m_oDSTEnumContext;

    /* The underlying DST slot context. */
    DRM_DST_SLOT_CONTEXT m_oDSTSlotContext;

    /*
    ** Flag indicating whether domain certificates
    ** or domain private keys to be enumerated.
    */
    DRM_BOOL m_fCert;

    /* Flag indicating whether the context has been initialized. */
    DRM_BOOL m_fInited;
} DRM_DOMAINSTORE_ENUM_CONTEXT;

EXIT_PK_NAMESPACE;

#endif /* __DRM_DOMAIN_STORE_TYPES_H */

