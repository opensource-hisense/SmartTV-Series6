/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/


#ifndef __DRM_DEVICESTORE_H__
#define __DRM_DEVICESTORE_H__

#include <drmtypes.h>
#include <drmcontextsizes.h>
#include <drmmanager.h>
#include <drmdatastore.h>
#include <drmdevicestoretypes.h>

ENTER_PK_NAMESPACE;

/*
** API Functions
*/

/**********************************************************************
** Function:    DRM_DVS_Initialize
**
**
** Parameters
  f_pDeviceStoreContext [in]  Pointer to an allocated context that will be initialized. Must not be NULL.

Return Values
If the function succeeds, it returns DRM_SUCCESS and f_pDeviceStoreContext points to an initialized context. If the function fails, an appropriate error code will be returned.
Remarks
Defined in OEM Layer (See architectural diagram)
The NDT PK must call DRM_DVS_Initialize with an allocated context before it can invoke any other device store APIs with that context. This function will initialize the incoming context as the OEM deems fit.

***********************************************************************/

DRM_API DRM_RESULT DRM_CALL DRM_DVS_Initialize(
    __in     DRM_DEVICESTORE_CONTEXT   *f_pDeviceStoreContext,
    __in     DRM_APP_CONTEXT           *f_pDeviceStoreInitData );



DRM_API DRM_VOID DRM_CALL DRM_DVS_Uninitialize(
    __inout DRM_DEVICESTORE_CONTEXT      *f_pDeviceStoreContext );



DRM_API DRM_VOID DRM_CALL DRM_DVS_FreeDevice(
    __in_opt    DRM_DEVICESTORE_HANDLE            f_hDeviceHandle );



DRM_API DRM_RESULT DRM_CALL DRM_DVS_RegisterDevice(
    __inout  DRM_DEVICESTORE_CONTEXT      *f_pDeviceStoreContext,
    __in     DRM_BYTEBLOB                  f_DeviceID,
    __out    DRM_DEVICESTORE_HANDLE       *f_pDeviceHandle );



DRM_API DRM_RESULT DRM_CALL DRM_DVS_UnRegisterDevice(
    __inout DRM_DEVICESTORE_CONTEXT      *f_pDeviceStoreContext,
    __in    DRM_BYTEBLOB                  f_DeviceID );



DRM_API DRM_RESULT DRM_CALL DRM_DVS_GetFirstDevice(
    __inout DRM_DEVICESTORE_CONTEXT      *f_pDeviceStoreContext,
    __out   DRM_DEVICESTORE_HANDLE       *f_pDeviceHandle );



DRM_API DRM_RESULT DRM_CALL DRM_DVS_GetNextDevice(
    __inout DRM_DEVICESTORE_CONTEXT      *f_pDeviceStoreContext,
    __out   DRM_DEVICESTORE_HANDLE       *f_pDeviceHandle );



DRM_API DRM_RESULT DRM_CALL DRM_DVS_GetDeviceByID(
    __inout DRM_DEVICESTORE_CONTEXT           *f_pDeviceStoreContext,
    __in    DRM_BYTEBLOB                       f_DeviceID,
    __out   DRM_DEVICESTORE_HANDLE            *f_pDeviceHandle );


PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_PARAM, "Prefast still complains that f_hDeviceHandle can be const even though it already is.")
DRM_API DRM_RESULT DRM_CALL DRM_DVS_GetDeviceID(
    __in                             const DRM_DEVICESTORE_HANDLE  f_hDeviceHandle,
    __out_ecount_opt(*f_pcbDeviceID)       DRM_BYTE               *f_pbDeviceID,
    __inout                                DRM_DWORD              *f_pcbDeviceID );
PREFAST_POP


PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_PARAM, "Prefast still complains that f_hDeviceHandle can be const even though it already is.")
DRM_API DRM_RESULT DRM_CALL DRM_DVS_GetDeviceAttr(
    __in                              const DRM_DEVICESTORE_HANDLE  f_hDeviceHandle,
    __in                                    DRM_BYTEBLOB            f_AttrName,
    __out_ecount_opt(*f_pcbAttrValue)       DRM_BYTE               *f_pbAttrValue,
    __inout                                 DRM_DWORD              *f_pcbAttrValue );
PREFAST_POP



DRM_API DRM_RESULT DRM_CALL DRM_DVS_GetDeviceAttrCount(
    __in     DRM_DEVICESTORE_HANDLE               f_hDeviceHandle,
    __out    DRM_DWORD                           *f_pdwAttrCount );



PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_PARAM, "Prefast still complains that f_hDeviceHandle can be const even though it already is.")
DRM_API DRM_RESULT DRM_CALL DRM_DVS_GetDeviceAttrByIndex(
    __in                              const DRM_DEVICESTORE_HANDLE  f_hDeviceHandle,
    __in                                    DRM_DWORD               f_dwAttrIndex,
    __out_ecount_opt(*f_pcbAttrName)        DRM_BYTE               *f_pbAttrName,
    __inout                                 DRM_DWORD              *f_pcbAttrName,
    __out_ecount_opt(*f_pcbAttrValue)       DRM_BYTE               *f_pbAttrValue,
    __inout                                 DRM_DWORD              *f_pcbAttrValue );
PREFAST_POP


DRM_API DRM_RESULT DRM_CALL DRM_DVS_SetDeviceAttr(
    __in     DRM_DEVICESTORE_HANDLE           f_hDeviceHandle,
    __in     DRM_BYTEBLOB                     f_AttrName,
    __in     DRM_BYTEBLOB                     f_AttrValue );



DRM_API DRM_RESULT DRM_CALL DRM_DVS_CommitDevice(
    __in     DRM_DEVICESTORE_HANDLE             f_hDeviceHandle );

EXIT_PK_NAMESPACE;

#endif  /* __DRM_DEVICESTORE_H__ */


