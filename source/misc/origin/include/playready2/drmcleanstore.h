/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRM_CLEANSTORE__
#define __DRM_CLEANSTORE__

#include <drmtypes.h>
#include <drmlicstore.h>

ENTER_PK_NAMESPACE;

DRM_API DRM_BOOL DRM_CALL DRM_CLEANSTORE_IsCleanStoreSupported(DRM_VOID);
DRM_API DRM_BOOL DRM_CALL DRM_CLEANSTORE_IsCleanStoreUnsupported(DRM_VOID);

DRM_API DRM_RESULT DRM_CALL DRM_CLEANSTORE_RemoveUnusableLicenses(
    __in                                                DRM_BYTE                    *f_pContextLEVL,
    __in_bcount( SIZEOF( DRM_LICSTORE_CONTEXT ) )       DRM_BYTE                    *f_pContextLSTXML,
    __in_bcount_opt( SIZEOF( DRM_LICSTORE_CONTEXT ) )   DRM_BYTE                    *f_pContextLSTXMR,
    __in                                                DRM_LICSTOREENUM_CONTEXT    *f_pLicStoreEnumContext,
    __in                                                DRM_DWORD                    f_dwFlags,
    __in_bcount(f_cbBuffer )                            DRM_BYTE                    *f_pbBuffer,
    __in                                                DRM_DWORD                    f_cbBuffer,
    __in_opt                                      const DRM_VOID                    *f_pvCallerData,
    __in                                                DRM_DWORD                    f_dwCallbackInterval,
    __in_opt                                            pfnStoreCleanupProgress      f_pfnCallback,
    __inout_ecount( 1 )                                 DRM_DST                     *f_pDatastore ) DRM_NO_INLINE_ATTRIBUTE;

EXIT_PK_NAMESPACE;

#endif /* __DRM_CLEANSTORE__ */

