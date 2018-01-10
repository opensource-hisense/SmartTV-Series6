/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef _DRMPRNDCALLBACKTYPES_H_
#define _DRMPRNDCALLBACKTYPES_H_

#include <drmpragmas.h>
#include <drmtypes.h>

ENTER_PK_NAMESPACE;

typedef enum
{
    DRM_PRND_CONTENT_IDENTIFIER_TYPE_KID                            = 0x1,
    DRM_PRND_CONTENT_IDENTIFIER_TYPE_CUSTOM                         = 0x2,
} DRM_PRND_CONTENT_IDENTIFIER_TYPE;

#define DRM_PRND_CERTIFICATE_DATA_DIGEST_SIZE                       32
#define DRM_PRND_CERTIFICATE_DATA_CLIENT_ID_SIZE                    16
#define DRM_PRND_CERTIFICATE_DATA_MAX_MANUFACTURER_STRING_LENGTH    129 /* Null-terminated */
typedef struct __tagDRM_PRND_CERTIFICATE_DATA
{
    DRM_DWORD                       dwType;                 /* Should be: DRM_BCERT_CERTTYPE_PC (0x1) or DRM_BCERT_CERTTYPE_DEVICE (0x2).  Refer to drmbcert.h. */
    DRM_DWORD                       dwPlatformIdentifier;   /* One of many DRM_BCERT_SECURITY_VERSION_PLATFORM_* values.    Refer to drmbcert.h. */
    DRM_DWORD                       dwSecurityLevel;        /* Typically will be 150 or 2000. */

    DRM_DWORD                       cSupportedFeatures;
    DRM_DWORD                       rgdwSupportedFeatureSet[ DRM_BCERT_MAX_FEATURES ];

    DRM_BYTE                        rgbClientID[ DRM_PRND_CERTIFICATE_DATA_CLIENT_ID_SIZE ];

    DRM_BYTE                        rgbModelDigest[ DRM_PRND_CERTIFICATE_DATA_DIGEST_SIZE ];
    DRM_CHAR                        szModelManufacturerName[ DRM_PRND_CERTIFICATE_DATA_MAX_MANUFACTURER_STRING_LENGTH ];
    DRM_CHAR                        szModelName[ DRM_PRND_CERTIFICATE_DATA_MAX_MANUFACTURER_STRING_LENGTH ];
    DRM_CHAR                        szModelNumber[ DRM_PRND_CERTIFICATE_DATA_MAX_MANUFACTURER_STRING_LENGTH ];
} DRM_PRND_CERTIFICATE_DATA;

PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_PARAM_25004, "Prefast Noise: Callback contexts should never be const")
typedef DRM_RESULT ( DRM_CALL *Drm_Prnd_Data_Callback )(
    __inout_ecount_opt( 1 )                        DRM_VOID                                    *f_pvDataCallbackContext,
    __in_opt                                       DRM_PRND_CERTIFICATE_DATA                   *f_pCertificateData,
    __in_opt                                 const DRM_ID                                      *f_pCustomDataTypeID,
    __in_bcount_opt( f_cbCustomData )        const DRM_BYTE                                    *f_pbCustomData,
    __in                                           DRM_DWORD                                    f_cbCustomData );
PREFAST_POP /* __WARNING_NONCONST_PARAM_25004 */

PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_PARAM_25004, "Prefast Noise: Callback contexts should never be const")
typedef DRM_RESULT ( DRM_CALL *Drm_Prnd_Content_Identifier_Callback )(
    __inout_ecount_opt( 1 )                        DRM_VOID                                    *f_pvContentIdentifierCallbackContext,
    __in                                           DRM_PRND_CONTENT_IDENTIFIER_TYPE             f_eContentIdentifierType,
    __in_bcount_opt( f_cbContentIdentifier ) const DRM_BYTE                                    *f_pbContentIdentifier,
    __in                                           DRM_DWORD                                    f_cbContentIdentifier,
    __in_ecount_opt( 1 )                           DRM_KID                                     *f_pkidContent );
PREFAST_POP /* __WARNING_NONCONST_PARAM_25004 */

EXIT_PK_NAMESPACE;

#endif /* _DRMPRNDCALLBACKTYPES_H_ */

