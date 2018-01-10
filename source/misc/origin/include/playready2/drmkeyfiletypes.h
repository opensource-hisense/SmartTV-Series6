/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef _DRMKEYFILETYPES_H_
#define _DRMKEYFILETYPES_H_

#include <oemcommon.h>

#include <drmkeyfileformattypes.h>
#include <drmxbbuilder.h>

ENTER_PK_NAMESPACE;

/* TASK: Set reasonable numbers here for the buffer/stack sizes */
#define DRM_KEYFILE_MAX_SIZE 16384

typedef struct {
    DRM_WORD       wKeypairDecryptionMethod;
    DRM_WORD       wKeySize;
    DRM_BYTE       rgbInitializationVector[64];
DRM_OBFUS_FILL_BYTES(4)
DRM_OBFUS_PTR_TOP
    DRM_BYTE      *pbEncryptedKey;
DRM_OBFUS_PTR_BTM
    DRM_DWORD      cbEncryptedKey;
    DRM_GUID       guidKeypairDecryptionKeyID;
    DRM_WORD       wReserved;
} DRM_ENCRYPTED_KEY;

typedef struct
{
    DRM_BOOL fInited;
    DRM_BOOL fLoaded;
    DRM_VOID *pOEMContext;
    OEM_FILEHDL hKeyfile;
    DRM_KEYFILE keyfile;
    DRM_XB_BUILDER_CONTEXT builderContext;
    DRM_BYTE rgbParserStack[DRM_KEYFILE_PARSER_STACK_SIZE];
    DRM_BYTE rgbBuilderStack[DRM_KEYFILE_BUILDER_STACK_SIZE];
    DRM_DWORD cbKeyfileBuffer;
    DRM_BYTE *pbKeyfileBuffer;
    DRM_BYTE rgbKeyfileBuffer[DRM_KEYFILE_MAX_SIZE];
} DRM_KEYFILE_CONTEXT;


typedef enum DRM_KF_CERT_TYPE
{
    eKF_CERT_TYPE_INVALID,
    eKF_CERT_TYPE_NDT,
    eKF_CERT_TYPE_WMDRM,
    eKF_CERT_TYPE_PLAYREADY,
} DRM_KF_CERT_TYPE;

typedef enum DRM_KF_KEY_TYPE
{
    eKF_KEY_TYPE_INVALID,
    eKF_KEY_TYPE_RSA,
    eKF_KEY_TYPE_ECC_160,
    eKF_KEY_TYPE_ECC_256,
    eKF_KEY_SECURE_STORE
} DRM_KF_KEY_TYPE;

EXIT_PK_NAMESPACE;

#endif /* _DRMKEYFILETYPES_H_ */

