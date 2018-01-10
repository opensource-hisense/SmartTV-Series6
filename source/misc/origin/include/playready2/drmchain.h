/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRM_CHAIN_H__
#define __DRM_CHAIN_H__

#include <drmchaintypes.h>
#include <drmcallbacks.h>
#include <drmliceval.h>

ENTER_PK_NAMESPACE;

/* This function is recursive!!!
   INPUTS -- stuff in DRM_FFLICENSE struct
   OUTPUT -- array of binding info structures to pass to CreateDecryptor
             Array of open secure store contexts
             Array of KID/LID pairs that were used in the chain
             Initialized cipher context if correct key found.
  Caller should call CreateDecryptor when ready
  Will have to read the license in again.
  Caller should then read each license in and do the DoneWithOperation for each license
  Caller should then update metering data for each license */

DRM_API DRM_RESULT DRM_CALL DRM_LIC_CompleteLicenseChain(
    __out_opt     DRM_CIPHER_CONTEXT          *f_pCipherContext,
    __inout       DRM_FFLICENSE               *f_pFFLicense,
    __in    const DRM_CONST_STRING            *f_rgpdstrRights[], /* Array of DRM_CONST_STRING pointers */
    __in          DRM_DWORD                    f_cRights,
    __out         DRM_DWORD                   *f_pdwChainDepth,
    __in          DRM_DST                     *f_pDatastore,
    __in          DRMPFNPOLICYCALLBACK         f_pfnPolicyCallback,
    __in    const DRM_VOID                    *f_pv );

DRM_API DRM_RESULT DRM_CALL DRM_LIC_ReportActions(
    __inout       DRM_FFLICENSE                *f_pFFLicense,
    __in    const DRM_CONST_STRING             *f_rgpdstrRights[], /* Array of DRM_CONST_STRING pointers */
    __in          DRM_DWORD                     f_cRights,
    __in          DRM_DWORD                     f_dwChainDepth,
    __in    const DRM_DST                      *f_pDatastore,
    __in          DRMPFNPOLICYCALLBACK          f_pfnPolicyCallback,
    __in    const DRM_VOID                     *f_pv );

DRM_API DRM_RESULT DRM_CALL DRM_LIC_CheckClockRollback(
    __in                           DRM_LICEVAL_CONTEXT      *f_pLicEval,
    __in                           DRM_LICSTORE_CONTEXT     *f_pLicStoreXML,
    __in                           DRM_LICSTORE_CONTEXT     *f_pLicStoreXMR,
    __in                           DRM_LICSTOREENUM_CONTEXT *f_pLicEnum,
    __in_bcount( f_cbBuffer )      DRM_BYTE                 *f_pbBuffer,
    __in                           DRM_DWORD                 f_cbBuffer,
    __in                           DRM_DST                  *f_pDatastore,
    __in_bcount( f_cbStackBuffer ) DRM_BYTE                 *f_pbStackBuffer,
    __in                           DRM_DWORD                 f_cbStackBuffer );

DRM_API DRM_RESULT DRM_CALL DRM_LICOPL_ProcessPlayOutputLevelDataXMR(
    __in    const DRM_XMR_PLAYBACK_RIGHTS      *f_pxmrPlaybackRights,
    __inout       DRM_PLAY_OPL_EX2             *f_pPlayOPL,
    __in          DRM_STACK_ALLOCATOR_CONTEXT  *f_pstack );

EXIT_PK_NAMESPACE;

#endif  /* __DRM_CHAIN_H__ */
