/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRM_DOMAIN_STORE_H
#define __DRM_DOMAIN_STORE_H

#include <drmdomainstoretypes.h>

ENTER_PK_NAMESPACE;

DRM_API DRM_RESULT DRM_CALL DRM_DOMST_OpenStore(
    __in  DRM_DST                 *f_pDatastore,
    __out DRM_DOMAINSTORE_CONTEXT *f_poDomainStoreContext );


DRM_API DRM_RESULT DRM_CALL DRM_DOMST_CloseStore(
    __in DRM_DOMAINSTORE_CONTEXT *f_poDomainStoreContext );


DRM_API DRM_RESULT DRM_CALL DRM_DOMST_AddCert(
    __in_bcount( DRM_SHA1_DIGEST_LEN ) const DRM_BYTE                 f_rgbPasswordSST[__CB_DECL(DRM_SHA1_DIGEST_LEN)],
    __inout_opt                              DRM_VOID                *f_pOEMContext,
    __in                                     DRM_DOMAINSTORE_CONTEXT *f_poDomainStoreContext,
    __in                               const DRM_GUID                *f_poAccountID,
    __in                               const DRM_GUID                *f_poServiceID,
    __in_bcount( f_cbCert )            const DRM_BYTE                *f_pbCert,
    __in                                     DRM_DWORD                f_cbCert );


DRM_API DRM_RESULT DRM_CALL DRM_DOMST_GetCert(
    __in                                 DRM_DOMAINSTORE_CONTEXT *f_poDomainStoreContext,
    __in                           const DRM_GUID                *f_poAccountID,
    __in                                 DRM_GUID                *f_poServiceID,
    __out_bcount_opt( *f_pcbCert )       DRM_BYTE                *f_pbCert,
    __inout                              DRM_DWORD                *f_pcbCert );


DRM_API DRM_RESULT DRM_CALL DRM_DOMST_DeleteCert(
    __in       DRM_DOMAINSTORE_CONTEXT *f_poDomainStoreContext,
    __in const DRM_GUID                *f_poAccountID );


DRM_API DRM_RESULT DRM_CALL DRM_DOMST_InitEnumCert(
    __in  DRM_DOMAINSTORE_CONTEXT      *f_poDomainStoreContext,
    __out DRM_DOMAINSTORE_ENUM_CONTEXT *f_poDomainStoreEnumContext );


DRM_API DRM_RESULT DRM_CALL DRM_DOMST_EnumNextCert(
    __in      DRM_DOMAINSTORE_ENUM_CONTEXT *f_poDomainStoreEnumContext,
    __out     DRM_GUID                     *f_poAccountID,
    __out_opt DRM_GUID                     *f_poServiceID,
    __out_opt DRM_DST_SLOT_HINT            *f_poSlotHint,
    __out_opt DRM_DWORD                    *f_pcbData );


DRM_API DRM_RESULT DRM_CALL DRM_DOMST_AddKey(
    __in                         DRM_DOMAINSTORE_CONTEXT *f_poDomainStoreContext,
    __in                   const DRM_GUID                *f_poAccountID,
    __in                         DRM_DWORD                f_dwRevision,
    __in_bcount( f_cbKey ) const DRM_BYTE                *f_pbKey,
    __in                         DRM_DWORD                f_cbKey );


DRM_API DRM_RESULT DRM_CALL DRM_DOMST_GetKey(
    __in                                DRM_DOMAINSTORE_CONTEXT *f_poDomainStoreContext,
    __in                          const DRM_GUID                *f_poAccountID,
    __in                                DRM_DWORD                f_dwRevision,
    __out_bcount_opt( *f_pcbKey )       DRM_BYTE                *f_pbKey,
    __inout                             DRM_DWORD               *f_pcbKey );


DRM_API DRM_RESULT DRM_CALL DRM_DOMST_DeleteKey(
    __in       DRM_DOMAINSTORE_CONTEXT *f_poDomainStoreContext,
    __in const DRM_GUID                *f_poAccountID,
    __in       DRM_DWORD                f_dwRevision );


DRM_API DRM_RESULT DRM_CALL DRM_DOMST_DeleteKeys(
    __in       DRM_DOMAINSTORE_CONTEXT *f_poDomainStoreContext,
    __in const DRM_GUID                *f_poAccountID );


DRM_API DRM_RESULT DRM_CALL DRM_DOMST_InitEnumKey(
    __in  DRM_DOMAINSTORE_CONTEXT      *f_poDomainStoreContext,
    __out DRM_DOMAINSTORE_ENUM_CONTEXT *f_poDomainStoreEnumContext );


DRM_API DRM_RESULT DRM_CALL DRM_DOMST_EnumNextKey(
    __in                DRM_DOMAINSTORE_ENUM_CONTEXT *f_poDomainStoreEnumContext,
    __out               DRM_GUID                     *f_poAccountID,
    __out_ecount_opt(1) DRM_DWORD                    *f_pdwRevision,
    __out_opt           DRM_DST_SLOT_HINT            *f_poSlotHint,
    __out_opt           DRM_DWORD                    *f_pcbData );

DRM_API DRM_RESULT DRM_CALL DRM_DOMST_CreateDomainStorePassword(
    __in                                const DRM_GUID       *f_poAccountID,
    __in                                      DRM_BB_CONTEXT *f_poBBXContext,
    __out_bcount( DRM_SHA1_DIGEST_LEN )       DRM_BYTE        f_rgbPasswordSST[__CB_DECL(DRM_SHA1_DIGEST_LEN)] );

EXIT_PK_NAMESPACE;

#endif /* __DRM_DOMAIN_STORE_H */
