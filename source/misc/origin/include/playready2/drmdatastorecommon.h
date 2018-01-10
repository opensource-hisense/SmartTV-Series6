/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/


#ifndef __DRM_DATASTORECOMMON_H__
#define __DRM_DATASTORECOMMON_H__

#include <drmtypes.h>
#include <drmpragmas.h>

ENTER_PK_NAMESPACE;

/*
** DRM_DST_BLKNUMTYPE specifies the block-numbering type for a given store.
*/
typedef enum
{
    eDRM_DSTBLKNUM_WORD  = 2,  /* Number blocks by WORD */
    eDRM_DSTBLKNUM_DWORD = 4   /* Number blocks by DWORD */
} DRM_DST_BLKNUMTYPE;

/*
** DRM_DST_OPENMODE specifies the open mode for a store or namespace.
*/
typedef enum
{
    eDRM_DST_CREATE_NEW    = 0x1000,      /* Create only, fail if it already exists. */
    eDRM_DST_OPEN_EXISTING = 0x2000,      /* Open if exists, fail if not. */
    eDRM_DST_OPEN_ALWAYS   = 0x4000       /* Open if exists, create if not. */
} DRM_DST_OPENMODE;

/*
** DRM_DST_LOCKMODE specifies the locking mode for a store, namespace, or slot.
*/
typedef enum
{
    eDRM_DST_LOCKSHARED    = 0x0, /* Opened for shared access. */
    eDRM_DST_LOCKEXCLUSIVE = 0x1, /* Opened for exclusive access. */
    eDRM_DST_LOCKWAIT      = 0x2, /* Wait for existing lock before access. */
    eDRM_DST_LOCKMODE_MASK = 0x3  /* Bitmask defining the bits used for the lock mode */
} DRM_DST_LOCKMODE;

/*
** DRM_DST_SEEKMODE specifies the seek mode for seeking within a slot.
*/
typedef enum
{
    eDRM_DST_SEEKCUR = 1, /* Seek from the current position */
    eDRM_DST_SEEKEND = 2, /* Seek from the end of the slot */
    eDRM_DST_SEEKSET = 3  /* Seek from the beginning of the slot */
} DRM_DST_SEEKMODE;

/*
** Both keys used in the data store are of type DRM_ID.
*/
typedef DRM_ID DRM_DST_KEY;

EXIT_PK_NAMESPACE;

#endif  /* __DRM_DATASTORECOMMON_H__ */
