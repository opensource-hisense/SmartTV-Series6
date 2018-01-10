/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __OEMDEVSTORE_H__
#define __OEMDEVSTORE_H__

#include <oemcommon.h>
#include <oemcontextsizes.h>

ENTER_PK_NAMESPACE;

DRM_API DRM_RESULT DRM_CALL Oem_DeviceStore_Initialize(
    __inout_ecount(1) OEM_DEVICESTORE_CONTEXT   *f_pDeviceStoreContext,
    __inout_ecount(1) OEM_DEVICESTORE_INITDATA  *f_pDeviceStoreInitData
);


DRM_API DRM_VOID DRM_CALL Oem_DeviceStore_Uninitialize(
    __inout_ecount(1)   OEM_DEVICESTORE_CONTEXT *f_pDeviceStoreContext
);


DRM_API DRM_VOID DRM_CALL Oem_DeviceStore_FreeDevice (
    __in     OEM_DEVICE_HANDLE            f_hDeviceHandle
);


DRM_API DRM_RESULT DRM_CALL Oem_DeviceStore_RegisterDevice(
    __inout_ecount(1) OEM_DEVICESTORE_CONTEXT      *f_pDeviceStoreContext,
    __in              DRM_BYTEBLOB                  f_DeviceID,
    __out_ecount(1)   OEM_DEVICE_HANDLE            *f_phDeviceHandle
);


DRM_API DRM_RESULT DRM_CALL Oem_DeviceStore_UnRegisterDevice(
    __inout_ecount(1) OEM_DEVICESTORE_CONTEXT      *f_pDeviceStoreContext,
    __in              DRM_BYTEBLOB                  f_DeviceID
);


DRM_API DRM_RESULT DRM_CALL Oem_DeviceStore_GetFirstDevice(
    __inout_ecount(1) OEM_DEVICESTORE_CONTEXT      *f_pDeviceStoreContext,
    __out_ecount(1)   OEM_DEVICE_HANDLE            *f_phDeviceHandle
);


DRM_API DRM_RESULT DRM_CALL Oem_DeviceStore_GetNextDevice(
    __in_ecount(1)    OEM_DEVICESTORE_CONTEXT      *f_pDeviceStoreContext,
    __inout_ecount(1) OEM_DEVICE_HANDLE            *f_phDeviceHandle
);


DRM_API DRM_RESULT DRM_CALL Oem_DeviceStore_GetDeviceByID(
    __inout_ecount(1) OEM_DEVICESTORE_CONTEXT      *f_pDeviceStoreContext,
    __in              DRM_BYTEBLOB                  f_DeviceID,
    __out_ecount(1)   OEM_DEVICE_HANDLE            *f_phDeviceHandle
);


DRM_API DRM_RESULT DRM_CALL Oem_DeviceStore_GetDeviceID(
    __in                             OEM_DEVICE_HANDLE    f_hDeviceHandle,
    __out_ecount_opt(*f_pcbDeviceID) DRM_BYTE            *f_pbDeviceID,
    __inout_ecount(1)                DRM_DWORD           *f_pcbDeviceID
);


DRM_API DRM_RESULT DRM_CALL Oem_DeviceStore_GetDeviceAttr(
    __in                              OEM_DEVICE_HANDLE  f_hDeviceHandle,
    __in                              DRM_BYTEBLOB       f_AttrName,
    __out_bcount_opt(*f_pcbAttrValue) DRM_BYTE          *f_pbAttrValue,
    __inout_ecount(1)                 DRM_DWORD         *f_pcbAttrValue
);


DRM_API DRM_RESULT DRM_CALL Oem_DeviceStore_GetDeviceAttrCount(
    __in                OEM_DEVICE_HANDLE            f_hDeviceHandle,
       __out_ecount(1)  DRM_DWORD                   *f_pdwAttrCount
);


DRM_API DRM_RESULT DRM_CALL Oem_DeviceStore_GetDeviceAttrByIndex(
    __in                                OEM_DEVICE_HANDLE    f_hDeviceHandle,
    __in                                DRM_DWORD            f_dwAttrIndex,
    __inout_bcount_opt(*f_pcbAttrName)  DRM_BYTE            *f_pbAttrName,
    __inout_ecount(1)                   DRM_DWORD           *f_pcbAttrName,
    __inout_bcount_opt(*f_pcbAttrValue) DRM_BYTE            *f_pbAttrValue,
    __inout_ecount(1)                   DRM_DWORD           *f_pcbAttrValue
);


DRM_API DRM_RESULT DRM_CALL Oem_DeviceStore_SetDeviceAttr(
    __in     OEM_DEVICE_HANDLE                 f_hDeviceHandle,
    __in     DRM_BYTEBLOB                      f_AttrName,
    __in     DRM_BYTEBLOB                      f_AttrValue
);


DRM_API DRM_RESULT DRM_CALL Oem_DeviceStore_CommitDevice(
    __in     OEM_DEVICE_HANDLE            f_hDeviceHandle
);


EXIT_PK_NAMESPACE;

#endif /*  __OEMDEVSTORE_H__ */
