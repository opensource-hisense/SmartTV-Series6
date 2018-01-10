/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRMENVELOPE_H__
#define __DRMENVELOPE_H__

#include <oemcommon.h>

ENTER_PK_NAMESPACE;

#define DRM_ENVELOPE_FILE_SIGNATURE 0x07455250

#define DRM_ENVELOPE_CURRENT_FORMAT_VERSION 1

/* This is the size in bytes of a v1 envelope header */
#define DRM_ENVELOPE_MINIMUM_HEADER_SIZE 50

#define DRM_ENVELOPE_CIPHER_DATA_SIZE 24

typedef struct __tagDRM_ENVELOPE_HEADER
{
    DRM_DWORD dwFileSignature;
    DRM_DWORD cbHeaderSize;
    DRM_DWORD dwFileDataOffset;
    DRM_WORD  wFormatVersion;
    DRM_WORD  wCompatibleVersion;
    DRM_DWORD dwCipherType;
    DRM_BYTE  rgbCipherData[DRM_ENVELOPE_CIPHER_DATA_SIZE];
    DRM_WORD  cbOriginalFilename;
    DRM_DWORD cbDrmHeaderLen;
} DRM_ENVELOPE_HEADER;

typedef struct __tagDRM_ENVELOPED_FILE_CONTEXT
{
    OEM_FILEHDL pEnvFileHandle;

    DRM_DWORD dwFileDataStart;

    DRM_CIPHER_CONTEXT oDecrypt;
    DRM_UINT64 qwInitialCipherCounter;
    DRM_ENVELOPE_HEADER oEnvHeader;

} DRM_ENVELOPED_FILE_CONTEXT;

EXIT_PK_NAMESPACE;

#endif /* __DRMENVELOPE_H__ */

