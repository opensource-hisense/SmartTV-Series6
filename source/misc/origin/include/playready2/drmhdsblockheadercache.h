/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRM_HDSBLOCKHEADERCACHE__
#define __DRM_HDSBLOCKHEADERCACHE__

#include <drmtypes.h>
#include <drmhds_impl.h>

ENTER_PK_NAMESPACE;

DRM_API DRM_BOOL DRM_CALL DRM_HBHC_IsHdsBlockHeaderCacheSupported(DRM_VOID);
DRM_API DRM_BOOL DRM_CALL DRM_HBHC_IsHdsBlockHeaderCacheUnsupported(DRM_VOID);

DRM_API DRM_RESULT DRM_CALL DRM_HBHC_GetBlockHeaderFromCache(
    __in     _NsContext     *f_pNS,
    __in     DRM_DWORD       f_nBlkNum,
    __inout  _CommBlockHDR **f_ppBlock,
    __in     DRM_BOOL        f_fGenericHeaderOnly,
    __out    DRM_BOOL       *f_pfFound );

DRM_API DRM_RESULT DRM_CALL DRM_HBHC_UpdateBlockHeaderCache(
    __in                                      DRM_DWORD   f_dwBlockNumber,
    __in_opt                                  OEM_FILEHDL f_hHDSFileHandle,
    __in                                      DRM_DWORD   f_dwBlockHeaderMetadata,
    __in_bcount_opt( f_cbBytesToWrite ) const DRM_BYTE   *f_pbBlock,
    __in                                      DRM_DWORD   f_cbBytesToWrite ) DRM_NO_INLINE_ATTRIBUTE;

EXIT_PK_NAMESPACE;

#endif /* __DRM_HDSBLOCKHEADERCACHE__ */

