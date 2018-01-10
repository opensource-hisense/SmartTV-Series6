/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/


#ifndef __OEMKEYFILECONSTS_H__
#define __OEMKEYFILECONSTS_H__

#include <drmnamespace.h>

ENTER_PK_NAMESPACE;

#define KF_MAX_FILE_PATH    256

#define KF_DECRYPTION_TYPE_CLEAR       0x0000
#define KF_DECRYPTION_TYPE_AES_CBC     0x0001
#define KF_DECRYPTION_TYPE_AES_CBC_SIG 0x0006
#define KF_DECRYPTION_TYPE_MAX_VALUE   0x0006

#define KF_MAX_ENCRYPTION_BUFFER 1024 / BITS_PER_BYTE  /* Big Enough to hold RSA1024 Priv Key */
/*
** Not supported in PK code
*/
#define KF_DECRYPTION_TYPE_AES_CTR_WM7       0x0002
#define KF_DECRYPTION_TYPE_AES_CTR_WM7_PLAIN 0x0003
#define KF_DECRYPTION_TYPE_AES_CTR_WM7_SST   0x0004
#define KF_DECRYPTION_TYPE_ACTIVATION_SST    0x0005

EXIT_PK_NAMESPACE;

#endif /*__OEMKEYFILECONSTS_H__ */

