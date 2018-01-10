/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRM_OUTPUTLEVELTYPES_H__
#define __DRM_OUTPUTLEVELTYPES_H__

#include <drmtypes.h>

ENTER_PK_NAMESPACE;

static const DRM_WORD DRM_DEFAULT_MINIMUM_SECURITY_LEVEL = 100;

#define DRM_MAX_INCLUSION_GUIDS 20

typedef struct __tagDRM_MINIMUM_OUTPUT_PROTECTION_LEVELS
{
    DRM_WORD wCompressedDigitalVideo;
    DRM_WORD wUncompressedDigitalVideo;
    DRM_WORD wAnalogVideo;
    DRM_WORD wCompressedDigitalAudio;
    DRM_WORD wUncompressedDigitalAudio;

} DRM_MINIMUM_OUTPUT_PROTECTION_LEVELS;

typedef struct __tagDRM_OPL_OUTPUT_IDS
{
    DRM_WORD  cIds;
    DRM_GUID  *rgIds;

} DRM_OPL_OUTPUT_IDS;

#define VER_DRM_PLAY_OPL_V1                     1
#define VER_DRM_PLAY_OPL                        2
#define VER_DRM_VIDEO_OUTPUT_PROTECTION         2
#define VER_DRM_PLAY_OPL_V2                     3
#define VER_DRM_VIDEO_AUDIO_OUTPUT_PROTECTION   3

typedef struct __tagDRM_OUTPUT_PROTECTION
{
    DRM_GUID guidId;
    DRM_BYTE bConfigData;

} DRM_OUTPUT_PROTECTION;

typedef struct __tagDRM_OUTPUT_PROTECTION_EX
{
    DRM_DWORD   dwVersion;
    DRM_GUID    guidId;
    DRM_DWORD   dwConfigData;
} DRM_OUTPUT_PROTECTION_EX;

typedef DRM_OUTPUT_PROTECTION DRM_AUDIO_OUTPUT_PROTECTION;
typedef DRM_OUTPUT_PROTECTION DRM_VIDEO_OUTPUT_PROTECTION;

typedef DRM_OUTPUT_PROTECTION_EX DRM_AUDIO_OUTPUT_PROTECTION_EX;
typedef DRM_OUTPUT_PROTECTION_EX DRM_VIDEO_OUTPUT_PROTECTION_EX;

typedef struct __tagDRM_VIDEO_OUTPUT_PROTECTION_IDS
{
    DRM_WORD cEntries;
    DRM_VIDEO_OUTPUT_PROTECTION *rgVop;

} DRM_VIDEO_OUTPUT_PROTECTION_IDS;

typedef struct __tagDRM_VIDEO_OUTPUT_PROTECTION_IDS_EX
{
    DRM_DWORD   dwVersion;
    DRM_WORD    cEntries;
    DRM_VIDEO_OUTPUT_PROTECTION_EX *rgVop;

} DRM_VIDEO_OUTPUT_PROTECTION_IDS_EX;

typedef struct __tagDRM_AUDIO_OUTPUT_PROTECTION_IDS
{
    DRM_WORD cEntries;
    DRM_AUDIO_OUTPUT_PROTECTION *rgAop;

} DRM_AUDIO_OUTPUT_PROTECTION_IDS;

typedef struct __tagDRM_AUDIO_OUTPUT_PROTECTION_IDS_EX
{
    DRM_DWORD   dwVersion;
    DRM_WORD    cEntries;
    DRM_AUDIO_OUTPUT_PROTECTION_EX *rgAop;

} DRM_AUDIO_OUTPUT_PROTECTION_IDS_EX;

typedef struct __tagDRM_PLAY_OPL
{
    DRM_MINIMUM_OUTPUT_PROTECTION_LEVELS minOPL;
    DRM_OPL_OUTPUT_IDS                   oplIdReserved;
    DRM_VIDEO_OUTPUT_PROTECTION_IDS      vopi;

} DRM_PLAY_OPL;

typedef struct __tagDRM_PLAY_OPL_EX
{
    DRM_DWORD                            dwVersion;
    DRM_MINIMUM_OUTPUT_PROTECTION_LEVELS minOPL;
    DRM_OPL_OUTPUT_IDS                   oplIdReserved;
    DRM_VIDEO_OUTPUT_PROTECTION_IDS_EX   vopi;

} DRM_PLAY_OPL_EX;

typedef struct __tagDRM_PLAY_OPL_EX2
{
    DRM_DWORD                            dwVersion;
    DRM_MINIMUM_OUTPUT_PROTECTION_LEVELS minOPL;
    DRM_OPL_OUTPUT_IDS                   oplIdReserved;
    DRM_VIDEO_OUTPUT_PROTECTION_IDS_EX   vopi;
    DRM_AUDIO_OUTPUT_PROTECTION_IDS_EX   aopi;
} DRM_PLAY_OPL_EX2;

typedef struct __tagDRM_COPY_OPL
{
    DRM_WORD           wMinimumCopyLevel;
    DRM_OPL_OUTPUT_IDS oplIdIncludes;
    DRM_OPL_OUTPUT_IDS oplIdExcludes;

} DRM_COPY_OPL;


EXIT_PK_NAMESPACE;

#endif /* __DRM_OUTPUTLEVELS_H__ */
