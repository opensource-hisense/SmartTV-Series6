#ifndef __TEECOMMON_INCLUDE_H__
#define __TEECOMMON_INCLUDE_H__

#include <oemcommon.h>

/*
 * constants and structs shared inside and outside the TEE
 */

// signature
#define TEE_MAX_SIGNATURE_SIZE                   256 // ECDSA-SHA256 signature

// session ID
#define TEE_SESSION_ID_LEN                        16 // session ID length

// key ID
#define TEE_KEY_ID_LEN                            16 // content key ID length

#define TEE_MAX_NUM_SECURE_STOPS                   8 // maximum number of persisted secure stops
#define TEE_MAX_STATE_SIZE                       512 // maximum state size

typedef struct {
    unsigned char data[TEE_MAX_SIGNATURE_SIZE];
    int length;
} TEE_SIGNATURE;

#endif /* __TEECOMMON_INCLUDE_H__ */
