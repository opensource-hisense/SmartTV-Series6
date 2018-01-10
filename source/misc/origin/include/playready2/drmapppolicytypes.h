/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRM_APPPOLICYTYPES_H__
#define __DRM_APPPOLICYTYPES_H__

#include <drmtypes.h>
#include <drmbytemanip.h>

ENTER_PK_NAMESPACE;

DRM_DECLARE_GUID( DRM_WM7_APPLICATION_POLICY );


#define DRM_WM7_APP_LICENSE_FULL              0x0001
#define DRM_WM7_APP_LICENSE_TRIAL             0x0002
#define DRM_WM7_APP_LICENSE_DEVELOPER_UNLOCK  0x0004

/*
** Define some constants that are the offset to the specified fields in the ARO
*/
#define DRM_WM7_APP_OFFSET_TO_POLICY_LENGTH            0
#define DRM_WM7_APP_OFFSET_TO_POLICY_TYPE_GUID         2
#define DRM_WM7_APP_OFFSET_TO_POLICY_VERSION          18
#define DRM_WM7_APP_OFFSET_TO_POLICY_FLAGS            20
#define DRM_WM7_APP_OFFSET_TO_POLICY_BEGIN_DATE       22
#define DRM_WM7_APP_OFFSET_TO_POLICY_END_DATE         26
#define DRM_WM7_APP_OFFSET_TO_POLICY_RIV_NUMBER       30
#define DRM_WM7_APP_OFFSET_TO_POLICY_CLIENT_ID        34
#define DRM_WM7_APP_OFFSET_TO_POLICY_SERVICE_ID       50
#define DRM_WM7_APP_OFFSET_TO_POLICY_APP_BINDING_SIZE 66
#define DRM_WM7_APP_OFFSET_TO_POLICY_APP_BINDING      70

#define DRM_WM7_APP_POLICY_SIGNATURE_SIZE             64


typedef struct _DRM_WM7AppPolicyData
{
          DRM_GUID   m_policyType;
          DRM_WORD   m_version;
          DRM_WORD   m_flags;
          DRM_DWORD  m_beginDate;
          DRM_DWORD  m_endDate;
          DRM_DWORD  m_rivSequenceNumber;
          DRM_GUID   m_clientID;
          DRM_GUID   m_serviceID;
          DRM_DWORD  m_cbAppBinding;
    const DRM_BYTE  *m_pbAppBinding;
    const DRM_BYTE  *m_pbSignature;
          DRM_DWORD  m_cbCertChain;
    const DRM_BYTE  *m_pbCertChain;
} DRM_WM7AppPolicyData;

EXIT_PK_NAMESPACE;

#endif /* __DRM_APPPOLICYTYPES_H__ */

