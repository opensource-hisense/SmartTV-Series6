/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRMREVOCATIONENUM_H__
#define __DRMREVOCATIONENUM_H__

ENTER_PK_NAMESPACE;

typedef enum _DRM_REVOCATION_TYPE_ENUM
{
    DRM_REVOCATION_TYPE_WMDRM_APP = 0,
    DRM_REVOCATION_TYPE_WMDRM_DEVICE,
    DRM_REVOCATION_TYPE_WMDRM_ND,
    DRM_REVOCATION_TYPE_WMDRM_REVINFO,
    DRM_REVOCATION_TYPE_PLAYREADY_APP,
    DRM_REVOCATION_TYPE_PLAYREADY_RUNTIME,
    DRM_REVOCATION_TYPE_PLAYREADY_REVINFO2
} DRM_REVOCATION_TYPE_ENUM;

EXIT_PK_NAMESPACE;

#endif /* __DRMREVOCATIONENUM_H__ */
