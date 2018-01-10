/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/


/* Description: The error codes to indicate the reason why a license is not usable.
              The error codes are used to give a better feedback to the user.
              These codes are used in the license to indicate the reason.
              drm.reason variable is set to this reason.
*/

#ifndef __LICREASON_H__
#define __LICREASON_H__

#include <drmnamespace.h>

ENTER_PK_NAMESPACE;

/* Server can help with these values. These are reasons why a license that was just obtained is not usable. */
/* Clearly, playcount cannot be a reason unless the count started with 0. Similarly, clockrollback is not a reason. */
enum
{
    LR_LICENSE_EXPIRED = 1,
    LR_LICENSE_NOTENABLED = 2,
    LR_LICENSE_APPSECLOW = 3,
    LR_LICENSE_NEEDINDI = 4,
    LR_LICENSE_STORE_NOT_ALLOWED = 5,
    LR_LICENSE_APP_NOT_ALLOWED = 6,
    LR_LICENSE_PLEDGE_LICENSE = 7,
    LR_LICENSE_CERT_EXPIRED = 8,
    LR_LICENSE_SECLOW = 9,
    LR_LICENSE_CONTENT_REVOKED = 10,
    LR_LICENSE_DEVICE_NOT_REGISTERED = 11,
    LR_LICENSE_TRACK_BURN_LIMIT_EXCEEDED = 12,
    LR_LICENSE_RESTRICTED_SOURCE = 13,
};

/* Client side detectable reasons */
enum
{
    LR_LICENSE_NOSAP = 50,
    LR_LICENSE_NOSVP,
    LR_LICENSE_NOWDM,
    LR_LICENSE_NOTRUSTEDCODEC,
    LR_LICENSE_DUMMY_TO_SIGNAL_END2,
    LR_LICENSE_NEED_UPGRADE_MSSAP,        /* special cases as the corresponding error codes in nserror.h are not consecutive to the others */
    LR_LICENSE_INVALID_APPLICATION,
    LR_LICENSE_CLOCK_NOT_SET,
    LR_LICENSE_TIME_CHECK_FAILURE,         /* special case for if the current time is before the first use/store time, rollback is detected, or graceperiod is violated */
    LR_LICENSE_EXTENSIBLE_RIGHT_NOT_FOUND
};

EXIT_PK_NAMESPACE;

#endif /* __LICREASON_H__ */
