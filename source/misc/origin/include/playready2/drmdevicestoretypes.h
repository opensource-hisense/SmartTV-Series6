/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/


#ifndef __DRM_DEVICESTORETYPES_H__
#define __DRM_DEVICESTORETYPES_H__

#include <drmtypes.h>
#include <drmblackbox.h>
#include <drmsecurestore.h>
#include <drmdatastore.h>

ENTER_PK_NAMESPACE;

/* Number of seconds for validation timeout, should be 48 hours as per NDT spec */
#define NDTDEVICESTORE_VALIDATION_TIMEOUT 172800

/* Initial size of the dirty attribute buffer */
#define DEVICESTORE_NUMDIRTYATTRIBUTES_INTIAL 5

/*
** Value set in the dwNumAttributes member of a device handle indicating that the number of
** attributes for the device is not known
*/
#define DEVICESTORE_NUMATTRIBUTES_UNKNOWN 0

/*
** Device store context stucture. This contains the DST namespace context it is using and
** the local stack info for internal use
*/
typedef struct _tag_DeviceStoreContext
{
    DRM_DST_SLOT_CONTEXT        oSlotContext;
    DRM_DST_NAMESPACE_CONTEXT   oNamespaceContext;
    DRM_DST                    *pDatastore;
    DRM_BB_CONTEXT             *pBBXContext;
    DRM_SECSTORE_CONTEXT       *pSecureStoreContext;
    DRM_SECSTOREENUM_CONTEXT    oSecStoreEnum;
    DRM_BOOL                    fEnumInited;
} _DeviceStoreContext;

typedef struct _tag_DeviceHandle
{
    DRM_BYTE                   *pbEntry;
    DRM_DWORD                   cbEntry;
    DRM_BYTEBLOB                oDeviceID;
    _DeviceStoreContext        *pDeviceStoreContext;
    DRM_DWORD                  *pdwDirtyAttributes;     /* List of the indices of attributes that have been modified */
    DRM_DWORD                   dwDirtyAttributesSize;  /* Size of the dirty attribute buffer as number of DRM_DWORD elements */
    DRM_DWORD                   dwNumDirtyAttributes;   /* Number of attributes marked as dirty */
    DRM_DWORD                   dwNumAttributes;        /* Number of attributes of the device, 0 if unknown (there should always be at least one attribute, DEVICEID) */
    DRM_BOOL                    fDontCommitOnFree;      /* Don't automatically commit when the handle is freed when this flag is set */
} _DeviceHandle;

typedef struct __tagDRM_DEVICESTORE_CONTEXT{
    DRM_BYTE rgbOpaqueBuffer[ __CB_DECL( SIZEOF( _DeviceStoreContext ) ) ];
} DRM_DEVICESTORE_CONTEXT;

typedef DRM_VOID* DRM_DEVICESTORE_HANDLE;

EXIT_PK_NAMESPACE;

#endif  /* __DRM_DEVICESTORETYPES_H__ */


