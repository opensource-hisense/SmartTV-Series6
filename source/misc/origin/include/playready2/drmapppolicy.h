/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRM_APPPOLICY_H__
#define __DRM_APPPOLICY_H__

#include <drmtypes.h>
#include <drmapppolicytypes.h>
#include <drmxmr.h>
#include <drmliceval.h>

ENTER_PK_NAMESPACE;

DRM_API DRM_BOOL DRM_CALL DRM_APPP_IsAppPolicySupported(DRM_VOID);

DRM_API DRM_BOOL DRM_CALL DRM_APPP_IsAppPolicyUnsupported(DRM_VOID);

DRM_API DRM_RESULT DRM_CALL DRM_APPP_ExtractWM7AppPolicyData(
    __in_bcount(f_cbPolicyData) const DRM_BYTE             *f_pbPolicyData,
    __in                              DRM_DWORD             f_cbPolicyData,
    __out_ecount( 1 )                 DRM_WM7AppPolicyData *f_pWM7AppPolicyData,
    __out_ecount( 1 )                 DRM_BOOL             *f_pfIsWM7AppPolicy );

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_APPP_RequireExecutePolicy(
    __in                       DRM_WORD                     f_wRightID,
    __in_ecount( 1 )     const DRM_XMR_GLOBAL_REQUIREMENTS *f_pGlobalPolicies,
    __in_ecount( 1 )     const DRM_XMR_UNKNOWN_OBJECT      *f_pUnknownObject,
    __inout_ecount( 1 )        DRM_LICEVAL_CONTEXT         *f_pContextLicEval ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_APPP_AllowExecutePolicy(
    __in_ecount( 1 )     const DRM_XMR_GLOBAL_REQUIREMENTS *f_pGlobalPolicies,
    __in_ecount( 1 )     const DRM_XMR_UNKNOWN_CONTAINER   *f_pUnknownContainer,
    __inout_ecount( 1 )        DRM_LICEVAL_CONTEXT         *f_pContextLicEval ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_BOOL DRM_CALL DRM_APPP_CanBind(
    __in_opt                       const DRM_XMR_LICENSE  *f_plicenseXMR,
    __in_ecount( f_dwChainLength ) const DRM_BINDING_INFO *f_pBindingInfo,
    __in                                 DRM_DWORD         f_dwChainLength,
    __inout_ecount( 1 )                  DRM_BB_CONTEXT   *f_pcontextBBX,
    __out_opt                            DRM_RESULT       *f_pDr );

DRM_API DRM_RESULT DRM_CALL DRM_APPP_AsymmetricToSymmetricKeyXMR(
    __inout_ecount( 1 )               DRM_BB_CONTEXT                *f_pcontextBBX,
    __inout_ecount( 1 )               DRM_BINDING_INFO              *f_pbindinfo,
    __inout_bcount( f_cbLicense )     DRM_BYTE                      *f_pbLicense,
    __in                              DRM_DWORD                      f_cbLicense,
    __inout_ecount( 1 )               DRM_DWORD                     *f_pcbLicenseUsed,
    __inout_ecount( 1 )               DRM_STACK_ALLOCATOR_CONTEXT   *f_pStack,
    __out_ecount( 1 )                 DRM_DWORD                     *f_pcbSymmKey );

DRM_API DRM_RESULT DRM_CALL DRM_APPP_CipherKeySetup(
    __in_opt                       const DRM_XMR_LICENSE     *f_plicenseXMR,
    __in_ecount( f_dwChainLength ) const DRM_BINDING_INFO    *f_pBindingInfo,
    __in                                 DRM_DWORD            f_dwChainLength,
    __out_ecount( 1 )                    DRM_CIPHER_CONTEXT  *f_pCipherContext,
    __inout_ecount( 1 )                  DRM_BB_CONTEXT      *f_pcontextBBX );

EXIT_PK_NAMESPACE;

#endif /* __DRM_APPPOLICY_H__ */

