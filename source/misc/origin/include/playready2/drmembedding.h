/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRMEMBEDDING_H__
#define __DRMEMBEDDING_H__

#include <drmtypes.h>
#include <drmlicstore.h>
#include <drmliceval.h>

ENTER_PK_NAMESPACE;

DRM_API DRM_RESULT DRM_CALL DRM_EMB_UpdateEmbeddedStore(
    __in                                                             DRM_LICSTORE_CONTEXT    *f_pEmbeddedStore,
    __in                                                             DRM_LICSTORE_CONTEXT    *f_pLicStore,
    __in                                                             DRM_DOMAINSTORE_CONTEXT *f_poDomainStoreContext,
    __in                                                       const DRM_LICEVAL_CONTEXT     *f_pLicEvalBackup,
    __inout                                                          DRM_LICEVAL_CONTEXT     *f_rgbLicEvalBuffer,
    __in_bcount_opt( *f_pcbScratchBuffer )                           DRM_BYTE                *f_pbScratchBuffer,
    __inout                                                          DRM_DWORD               *f_pcbScratchBuffer,
    __in                                                       const DRM_KID                 *f_poKID,
    __out                                                            DRM_BOOL                *f_pfModifiedEST );


EXIT_PK_NAMESPACE;

#endif /* __DRMEMBEDDING_H__ */
