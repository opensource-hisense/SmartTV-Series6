/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef _DRMKEYFILEFORMAT_H_
#define _DRMKEYFILEFORMAT_H_

#include <drmkeyfileformattypes.h>
#include <drmxbbuilder.h>
#include <drmxbparser.h>
#include <oemcryptoctx.h>

ENTER_PK_NAMESPACE;

/* Use DRM_KF_Start to begin the building of a keyfile.
** Add object to the move page using
**   DRM_XB_AddObject
*/
DRM_API DRM_RESULT DRM_CALL DRM_KF_Start(
    __inout_bcount( f_cbStack )       DRM_BYTE                *f_pbStack,
    __in                              DRM_DWORD                f_cbStack,
    __in                              DRM_DWORD                f_dwVersion,
    __in_opt                    const KF_SIGNATURE_OBJECT     *f_psignatureData,
    __inout_ecount( 1 )               DRM_XB_BUILDER_CONTEXT  *f_pcontextBuilder );

DRM_API DRM_RESULT DRM_CALL DRM_KF_Finish(
    __inout_ecount( 1 )           const DRM_XB_BUILDER_CONTEXT  *f_pcontextBuilder,
    __inout_bcount(*f_pcbKeyFile)       DRM_BYTE                *f_pbKeyFile,
    __inout                             DRM_DWORD               *f_pcbKeyFile,
    __in                                DRM_KF_CB_SIGNATURE      f_pfnSignatureCallback,
    __in                          const DRM_VOID                *f_pvSignatureContext );

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_KF_Parse(
    __in                              DRM_VOID                *f_pOEMContext,
    __inout_bcount( f_cbStack )       DRM_BYTE                *f_pbStack,
    __in                              DRM_DWORD                f_cbStack,
    __in_bcount( f_cbStack )    const DRM_BYTE                *f_pbKeyFile,
    __in                              DRM_DWORD                f_cbKeyFile,
    __in                              DRM_BOOL                 f_fValidateSignature,
    __out                             DRM_KEYFILE             *f_pKeyFile ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_RESULT DRM_CALL DRM_AD_Start(
    __inout_bcount( f_cbStack ) DRM_BYTE                *f_pbStack,
    __in                        DRM_DWORD                f_cbStack,
    __inout_ecount( 1 )         DRM_XB_BUILDER_CONTEXT  *f_pcontextBuilder);

DRM_API DRM_RESULT DRM_CALL DRM_AD_Parse(
    __inout_bcount( f_cbStack )       DRM_BYTE                *f_pbStack,
    __in                              DRM_DWORD                f_cbStack,
    __in_bcount( f_cbActivationData ) const DRM_BYTE          *f_pbActivationData,
    __in                              DRM_DWORD                f_cbActivationData,
    __out                             DRM_ACTIVATION_DATA     *f_pActivationData );

DRM_DWORD _VersionToFormatDescriptionTranslation( DRM_DWORD f_dwVersion );

extern const DRM_XB_FORMAT_DESCRIPTION g_kfFormatDescription[];

EXIT_PK_NAMESPACE;

#endif /* _DRMKEYFILEFORMAT_H_ */

