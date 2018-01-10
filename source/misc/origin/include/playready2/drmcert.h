/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef _DRM_CERT_H_
#define _DRM_CERT_H_

#include <drmpragmas.h>

ENTER_PK_NAMESPACE;

#define DRM_CERTIFICATE_COLLECTION_MIN 1
#define DRM_CERTIFICATE_COLLECTION_MAX 6

#define DRM_DSIG_TYPE_STANDARD FALSE
#define DRM_DSIG_TYPE_WMDRMNET TRUE

typedef enum
{
    DRM_WMDRM_CERT_ATTR_SECURITY_LEVEL,
    DRM_WMDRM_CERT_ATTR_KEY_USAGE,
    DRM_WMDRM_CERT_ATTR_FEATURES,
    DRM_WMDRM_CERT_ATTR_DIGEST_VALUE,

    /* parser only */

    DRM_WMDRM_CERT_ATTR_SECURITY_VERSION,
    DRM_WMDRM_CERT_ATTR_PUBLIC_KEY_SELF_RSA,
    DRM_WMDRM_CERT_ATTR_PUBLIC_KEY_SIGNER_RSA
} DRM_WMDRM_CERT_ATTRIBUTE;

typedef enum
{
    DRM_WMDRM_CERT_KEYUSAGE_SIGNCRL     = 0x01,
    DRM_WMDRM_CERT_KEYUSAGE_SIGNCERT    = 0x02,
    DRM_WMDRM_CERT_KEYUSAGE_ENCRYPTKEY  = 0x04
} DRM_WMDRM_CERT_KEYUSAGE;

typedef enum
{
    DRM_WMDRM_CERT_FEATURES_TRUSTEDTRANSMITTER     = 0x01,
    DRM_WMDRM_CERT_FEATURES_TRUSTEDRECEIVER        = 0x02,
    DRM_WMDRM_CERT_FEATURES_SAMPLEPROTECTION       = 0x04,
} DRM_WMDRM_CERT_FEATURES;

EXIT_PK_NAMESPACE;

#endif /* _DRM_CERT_H_ */
