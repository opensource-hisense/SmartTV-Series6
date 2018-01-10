/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRMLICGEN_H_
#define __DRMLICGEN_H_ 1

#include <drmmanagertypes.h>
#include <drmxmr.h>
#include <drmxmrbuilder.h>
#include <drmlicgentypes.h>

ENTER_PK_NAMESPACE;

typedef struct __tagDRM_LOCAL_LICENSE_SESSION_CONTEXT
{
    DRM_APP_CONTEXT                      *poAppContext;
    DRM_BB_CONTEXT                       *poBBXContext;

    OEM_CRYPTO_HANDLE                    handleCICK;
    OEM_ENCRYPTION_HANDLE                handleEncryption;

    DRM_KID                              kid;
    DRM_LID                              lid;

    DRM_DWORD                            cbXMRLicense;
    DRM_BYTE                            *pbXMRLicense;

    DRM_DWORD                            dwRefCount;
    DRM_BOOL                             fCannotPersist;
    DRM_LOCAL_LICENSE_TYPE               eLicenseType;
} DRM_LOCAL_LICENSE_SESSION_CONTEXT;

DRM_API DRM_NO_INLINE DRM_BOOL DRM_CALL DRM_LICGEN_IsLicGenSupported(DRM_VOID) DRM_NO_INLINE_ATTRIBUTE;
DRM_API DRM_NO_INLINE DRM_BOOL DRM_CALL DRM_LICGEN_IsLicGenUnsupported(DRM_VOID) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_LOCALLICENSE_CleanCache(
    __inout                             DRM_APP_CONTEXT                     *f_poAppContext ) DRM_NO_INLINE_ATTRIBUTE;

EXIT_PK_NAMESPACE;

#endif /* __DRMLICGEN_H_ */

