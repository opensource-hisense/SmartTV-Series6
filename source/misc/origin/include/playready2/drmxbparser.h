/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRM_XB_PARSER_H__
#define __DRM_XB_PARSER_H__

#include <drmxb.h>
#include <drmstkalloc.h>

ENTER_PK_NAMESPACE;


DRM_API DRM_RESULT DRM_CALL DRM_XB_UnpackBinary(
    __in_bcount( f_cb ) const DRM_BYTE                    *f_pb,
    __in                      DRM_DWORD                    f_cb,
    __inout                   DRM_STACK_ALLOCATOR_CONTEXT *f_pStack,
    __in                const DRM_XB_FORMAT_DESCRIPTION   *f_pformat,
    __in                      DRM_DWORD                    f_cformat,
    __out_opt                 DRM_DWORD                   *f_pdwVersionFound,
    __out                     DRM_VOID                    *f_pStruct ) DRM_NO_INLINE_ATTRIBUTE;


DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_XB_FindObject(
    __in                       DRM_WORD                     f_wObjectType,
    __in  const                DRM_XB_FORMAT_DESCRIPTION   *f_pformat,
    __in_bcount( f_cb )  const DRM_BYTE                    *f_pb,
    __in                       DRM_DWORD                    f_cb,
    __out                      DRM_DWORD                   *f_piObject,
    __out                      DRM_DWORD                   *f_pcbObject );

EXIT_PK_NAMESPACE;

#endif  /* __DRM_XB_PARSER_H__ */

