/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef DRMDEVSTORE_H
#define DRMDEVSTORE_H

#include <drmtypes.h>
#include <oemcontextsizes.h>

/* Maximum number of seconds that can pass between the last validation time and a license request */
#define DRM_DEVICESTORE_VALIDATION_TIMEOUT        (48 * 60 * 60)

ENTER_PK_NAMESPACE;

DRM_API DRM_BOOL DRM_CALL DRM_DVS_IsDeviceStoreSupported(DRM_VOID);
DRM_API DRM_BOOL DRM_CALL DRM_DVS_IsDeviceStoreUnsupported(DRM_VOID);

DRM_API DRM_BOOL DRM_CALL DRM_DeviceStore_HasTimedOut(
    __in_opt    DRM_VOID    *f_pOEMContext,
    __in        DRMFILETIME *f_pftStartTime,
    __in const  DRM_DWORD    f_dwTimeoutSeconds );

DRM_API DRM_RESULT DRM_CALL DRM_DeviceStore_MarkDeviceAsValid(
    __in_opt    DRM_VOID            *f_pOEMContext,
    __in const  OEM_DEVICE_HANDLE    f_hDeviceHandle );

DRM_API DRM_BOOL DRM_CALL DRM_DeviceStore_IsDeviceValid(
    __in_opt   DRM_VOID           *f_pOEMContext,
    __in const OEM_DEVICE_HANDLE   f_hDeviceHandle );

DRM_API DRM_VOID DRM_CALL DRM_DeviceStore_FreeDevice(
    __in const   OEM_DEVICE_HANDLE            f_hDeviceHandle );

DRM_API DRM_RESULT DRM_CALL DRM_DeviceStore_RegisterDevice(
    __inout           OEM_DEVICESTORE_CONTEXT *f_pOemDevStoreContext,
    __in     const    DRM_BYTEBLOB             f_DeviceCertificate,
    __in_opt const    DRM_ID                  *f_pDeviceSerialNumber,
    __out             OEM_DEVICE_HANDLE       *f_phDeviceHandle );

DRM_API DRM_RESULT DRM_CALL DRM_DeviceStore_UnRegisterDevice(
    __inout           OEM_DEVICESTORE_CONTEXT *f_pOemDevStoreContext,
    __in     const    DRM_BYTEBLOB             f_DeviceCertificate,
    __in_opt const    DRM_ID                  *f_pDeviceSerialNumber );

DRM_API DRM_RESULT DRM_CALL DRM_DeviceStore_GetFirstDevice(
    __inout OEM_DEVICESTORE_CONTEXT *       f_pOemDevStoreContext,
    __out   OEM_DEVICE_HANDLE       * const f_phDeviceHandle );

DRM_API DRM_RESULT DRM_CALL DRM_DeviceStore_GetNextDevice(
    __inout OEM_DEVICESTORE_CONTEXT *       f_pOemDevStoreContext,
    __out   OEM_DEVICE_HANDLE       * const f_phDeviceHandle );

DRM_API DRM_RESULT DRM_CALL DRM_DeviceStore_GetDeviceByID(
    __inout           OEM_DEVICESTORE_CONTEXT *       f_pOemDevStoreContext,
    __in     const    DRM_BYTEBLOB                    f_DeviceCertificate,
    __in_opt const    DRM_ID                         *f_pDeviceSerialNumber,
    __out             OEM_DEVICE_HANDLE       * const f_phDeviceHandle );

DRM_API DRM_RESULT DRM_CALL DRM_DeviceStore_GetDeviceInfo(
    __in const                                OEM_DEVICE_HANDLE         f_hDeviceHandle,
    __out_bcount_opt(*f_pcbDeviceCertificate) DRM_BYTE          * const f_pbDeviceCertificate,
    __inout                                   DRM_DWORD         * const f_pcbDeviceCertificate,
    __out_opt                                 DRM_ID            * const f_pDeviceSerialNumber );

DRM_API DRM_RESULT DRM_CALL DRM_DeviceStore_GetDeviceAttr(
    __in const                        OEM_DEVICE_HANDLE         f_hDeviceHandle,
    __in const                        DRM_BYTEBLOB              f_AttrName,
    __out_bcount_opt(*f_pcbAttrValue) DRM_BYTE          * const f_pbAttrValue,
    __inout                           DRM_DWORD         * const f_pcbAttrValue );

DRM_API DRM_RESULT DRM_CALL DRM_DeviceStore_GetDeviceAttrCount(
    __in const  OEM_DEVICE_HANDLE            f_hDeviceHandle,
    __out       DRM_DWORD            * const f_pdwAttrCount );

DRM_API DRM_RESULT DRM_CALL DRM_DeviceStore_GetDeviceAttrByIndex(
    __in const                        OEM_DEVICE_HANDLE         f_hDeviceHandle,
    __in const                        DRM_DWORD                 f_dwAttrIndex,
    __out_bcount_opt(*f_pcbAttrName)  DRM_BYTE          * const f_pbAttrName,
    __inout                           DRM_DWORD         * const f_pcbAttrName,
    __out_bcount_opt(*f_pcbAttrValue) DRM_BYTE          * const f_pbAttrValue,
    __inout                           DRM_DWORD         * const f_pcbAttrValue );

DRM_API DRM_RESULT DRM_CALL DRM_DeviceStore_SetDeviceAttr(
    __in const   OEM_DEVICE_HANDLE f_hDeviceHandle,
    __in const   DRM_BYTEBLOB      f_AttrName,
    __in const   DRM_BYTEBLOB      f_AttrValue );

EXIT_PK_NAMESPACE;

#endif   /* DRMDEVSTORE_H */
