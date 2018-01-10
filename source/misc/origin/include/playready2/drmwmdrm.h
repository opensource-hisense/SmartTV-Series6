/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRMWMDRM_H__
#define __DRMWMDRM_H__

#include <drmwmdrmtypes.h>
#include <drmlicevaltypes.h>
#include <drmviewrights.h>
#include <drmsymopt.h>

ENTER_PK_NAMESPACE;
DRM_API DRM_BOOL DRM_CALL DRM_WMDRM_IsWMDRMSupported(DRM_VOID);
DRM_API DRM_BOOL DRM_CALL DRM_WMDRM_IsWMDRMUnsupported(DRM_VOID);

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_WMDRM_LEVL_PerformOperationsXML(
    __inout         DRM_LICEVAL_CONTEXT          *f_pContextLicEval,
    __in            eDRM_LICEVAL_OPERATIONS       f_eOperation,
    __in            eDRM_LICEVAL_OPERATION_STATE  f_eOperationState,
    __in_opt  const DRM_CONST_STRING             *f_pdstrAction,
    __out_opt       DRM_BOOL                     *f_pfPerform,
    __out_opt       DRM_BOOL                     *f_pfActionExisted,
    __in      const DRM_DST                      *f_pDatastore ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_WMDRM_LEVL_GetLicenseReasonForUnusable(
    __in  const DRM_LICEVAL_CONTEXT   *f_pcontextLicEval,
    __out       DRM_LONG              *f_plReasonForUnusable ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_RESULT DRM_CALL DRM_WMDRM_LEVL_ParseV2License(
    __in      const DRM_CONST_STRING *f_pdstrLicense,
    __in      const DRM_CONST_STRING *f_pdstrAttrName,
    __out_opt       DRM_DWORD        *f_pdwValue,
    __out_opt       DRMFILETIME      *f_pfiletime );

DRM_API DRM_BOOL DRM_CALL DRM_WMDRM_LEVL_HasSAP(
    __in      const DRM_CONST_STRING *f_pdstrLicense );

DRM_API DRM_RESULT DRM_CALL DRM_WMDRM_LIC_CheckSymmOptStatus(
    __in      const  DRM_CONST_STRING   *f_pdstrLicense,
    __out            DRM_SYMMOPT_STATUS *f_eStatus,
    __out_opt        DRM_CONST_STRING   *f_pdstrSymmSigNode,
    __out_opt        DRM_CONST_STRING   *f_pdstrSymmSigNodeData,
    __out_opt        DRM_GUID           *f_pCkVerifiedGUID );

DRM_API DRM_RESULT DRM_CALL DRM_WMDRM_LIC_UpdateLicenseWithSymmetricData(
    __inout        DRM_STRING          *f_pdstrLicense,
    __in           DRM_DWORD            f_cchLicenseMax,
    __in           DRM_LICEVAL_CONTEXT *f_pcontextLEVL,
    __in           DRM_BOOL             f_fVerifiedCK,
    __in_opt const DRM_SLK             *f_pslk );

DRM_API DRM_RESULT DRM_CALL DRM_WMDRM_LIC_VerifySymmetricSignatureIfPresent(
    __in  const DRM_CONST_STRING *f_pdstrLicense,
    __in        DRM_BB_CONTEXT   *f_pcontextBBX,
    __in        DRM_CONST_STRING *f_pdstrLIData,
    __in        DRM_CONST_STRING *f_pdstrSignature,
    __out       DRM_LONG         *f_plResult );

DRM_API DRM_RESULT DRM_CALL DRM_WMDRM_PerformAppRevocationCheck(
    __in                                      DRM_CRYPTO_CONTEXT          *f_pContextCrypto,
    __in                                      DRM_REVOCATIONSTORE_CONTEXT *f_pContextRev,
    __in                                const DRM_CONST_STRING            *f_pdstrContentLicense,
    __in                                      APPCERT                     *f_pAppCert,
    __in_bcount( f_cbRevocationBuffer )       DRM_BYTE                    *f_pbRevocationBuffer,
    __in                                      DRM_DWORD                    f_cbRevocationBuffer,
    __inout                                   DRM_REVLIST_ID_VALUES       *f_pRevListIDs );

DRM_API DRM_RESULT DRM_CALL DRM_WMDRM_LIC_GetCopyOPLRestriction(
    __inout     DRM_VIEW_RIGHTS_CONTEXT *f_pcontextLQ,
    __in  const DRM_CONST_STRING        *f_pdstrAction,
    __in  const DRM_CONST_STRING        *f_pdstrRightUsed,
    __out       DRM_BOOL                *f_pfHasOPLs,
    __out       DRM_DWORD               *f_pdwResult );

DRM_API DRM_BOOL DRM_CALL DRM_WMDRM_LIC_HasOPLRestriction(
    __in const DRM_CONST_STRING *f_pdstrLicense,
    __in const DRM_CONST_STRING *f_pdstrRightUsed );

DRM_API DRM_BOOL DRM_CALL DRM_WMDRM_LIC_ShouldCheckClockRollback(
    __in const DRM_CONST_STRING *f_pdstrLicense );

typedef enum
{
    DRM_LICENSE_ATTRIB_VERSION        =  1,
    DRM_LICENSE_ATTRIB_KID            =  2,
    DRM_LICENSE_ATTRIB_LID            =  3,
    DRM_LICENSE_ATTRIB_REVOCATION     =  4,
    DRM_LICENSE_ATTRIB_ISSUEDATE      =  5,
    DRM_LICENSE_ATTRIB_CONTENTPUBKEY  =  6,
    DRM_LICENSE_ATTRIB_META_ATTRIBUTE =  7,
    DRM_LICENSE_ATTRIB_OTHER          =  8,
    DRM_LICENSE_ATTRIB_PRIORITY       =  9,
    DRM_LICENSE_ATTRIB_METERING_ID    = 10,
    DRM_LICENSE_ATTRIB_CHAINEDKID     = 11,
    DRM_LICENSE_ATTRIB_REVINFO        = 12,
    DRM_LICENSE_ATTRIB_SOURCEID       = 13
} eDRM_LICENSE_ATTRIBUTES;

DRM_API DRM_RESULT DRM_CALL DRM_WMDRM_LIC_GetAttribute(
    __in         const DRM_CONST_STRING        *pdstrLicense,
    __in_opt     const DRM_CONST_STRING        *pdstrAttrName,
    __in               eDRM_LICENSE_ATTRIBUTES  eAttribute,
    __inout_opt        DRM_CONST_STRING        *pdstrLIData,
    __out              DRM_CONST_STRING        *pdstrValue,
    __in               DRM_WCHAR                chXPathSeparator );

DRM_API DRM_RESULT DRM_CALL DRM_WMDRM_LIC_GetEvent(
    __in        const DRM_CONST_STRING *pdstrLicense,
    __in        const DRM_CONST_STRING *pdstrEvent,
    __in_opt    const DRM_CONST_STRING *pdstrTypeValue,
    __inout_opt       DRM_CONST_STRING *pdstrLIData,
    __out_opt         DRM_CONST_STRING *pdstrCondition,
    __out_opt         DRM_CONST_STRING *pdstrAction,
    __out_opt         DRM_CONST_STRING *pdstrRestriction );

DRM_API DRM_RESULT DRM_CALL DRM_WMDRM_LIC_LoadLicenseAttributes(
    __in  const DRM_CONST_STRING    *f_rgpdstrEvents[],
    __in        DRM_DWORD            f_cRights,
    __inout     DRM_LICEVAL_CONTEXT *f_pLicEval );

DRM_API DRM_RESULT DRM_CALL DRM_WMDRM_LIC_VerifyCertChain(
    __in  const DRM_CONST_STRING    *pdstrLicense,
    __in        DRM_BOOL             fCheckExpiry,
    __in        DRM_LICEVAL_CONTEXT *pcontextLEVL,
    __out       DRM_LONG            *plResult );

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_WMDRM_LIC_GetLSPubKey(
    __in const DRM_CONST_STRING   *pdstrLicense,
    __in       PUBKEY             *pbPubKey,
    __in       DRM_CRYPTO_CONTEXT *pcontextCrypto );

DRM_API DRM_RESULT DRM_CALL DRM_WMDRM_LIC_GetEnablingBits(
    __in                                     const DRM_CONST_STRING   *pdstrLicense,
    __in                                           DRM_DWORD           dwIndex,
    __out                                          DRM_DWORD          *pdwAlgorithm,
    __out                                          PUBKEY             *pPubKey,
    __out_bcount_opt( *pdValueLen )                DRM_BYTE           *pbValue,
    __out                                          DRM_DWORD          *pdValueLen,
    __out                                          PUBKEY             *pVerPubKey,
    __out_bcount( DRM_ECC160_SIGNATURE_LEN )       DRM_BYTE           *pbSignature,
    __out_bcount_opt( CHECKSUM_LENGTH )            DRM_BYTE            rgbChainedChecksum[CHECKSUM_LENGTH],
    __in                                           DRM_CRYPTO_CONTEXT *pcontextCrypto );

DRM_API DRM_RESULT DRM_CALL DRM_WMDRM_LIC_VerifySignature(
    __in const DRM_CONST_STRING *pdstrLicense,
    __in       DRM_BB_CONTEXT   *pcontextBBX,
    __out      DRM_LONG         *plResult );

DRM_API DRM_RESULT DRM_CALL DRM_WMDRM_LIC_PerformActionsOPLCallbacks(
    __inout       DRM_FFLICENSE               *f_pFFLicense,
    __inout       DRM_STACK_ALLOCATOR_CONTEXT *f_pstack,
    __in    const DRM_CONST_STRING            *f_rgpdstrRights[],
    __in          DRM_DWORD                    f_iRight,
    __in          DRMPFNPOLICYCALLBACK         f_pfnPolicyCallback );

DRM_API DRM_RESULT DRM_CALL DRM_WMDRM_LIC_ExtractRevocationVersions(
    __inout DRM_FFLICENSE    *f_pFFLicense,
    __out   DRM_DWORD        *f_pidCRLWMDRMAppRequired,
    __out   DRM_DWORD        *f_pidCRLDeviceRequired,
    __out   DRM_DWORD        *f_pidCRLWMDRMNETRequired,
    __out   DRM_DWORD        *f_pdwRevInfo );

DRM_API DRM_RESULT DRM_CALL DRM_WMDRM_LIC_GetLicenseInfoAndSetup(
    __inout       DRM_FFLICENSE    *f_pFFLicense,
    __in    const DRM_CONST_STRING *f_rgpdstrRights[],
    __in          DRM_DWORD         f_cRights );

DRM_API DRM_RESULT DRM_CALL DRM_WMDRM_LIC_GetSourceIDFromLicense(
    __inout DRM_FFLICENSE *f_pFFLicense );

DRM_API DRM_RESULT DRM_CALL DRM_WMDRM_LIC_GetInclusionList(
    __in const DRM_CONST_STRING  *f_pdstrLicense,
    __inout    DRM_GUID           f_rgInclusionList[DRM_MAX_INCLUSION_GUIDS],
    __inout    DRM_BOOL           f_rgfGuidValid[DRM_MAX_INCLUSION_GUIDS][DRM_MAX_LICENSE_CHAIN_DEPTH],
    __in       DRM_DWORD          f_dwChainDepth );

DRM_API DRM_RESULT DRM_CALL DRM_WMDRM_EXPRFUNC_FunctionGetValue(
    __in const TOKEN                       *pOperator,
    __in       DRM_LONG                     cArgs,
    __in       TOKEN                        rgArgs[],
    __out      TOKEN                       *pOperandResult,
    __in       DRM_WMDRM_EXPR_EVAL_CONTEXT *pEEContext );

DRM_API DRM_LONG DRM_CALL DRM_WMDRM_EXPRFUNC_Arity(DRM_EXPR_FUNCTION_TYPE fnType);

DRM_API DRM_BOOL DRM_CALL DRM_WMDRM_EXPRFUNC_IsValidFunction(
    __in const DRM_CONST_STRING *pStringToken,
    __in       DRM_DWORD        *pfnType );

/* In the following Extract*Token functions if cchExpression == 0 it is assumed that the string is NULL termintated. */
/* Note: These functions modify the pointer they are given. */
DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_WMDRM_EXPR_ExtractLongToken  ( DRM_CONST_STRING* pdstrExpression, TOKEN* pToken );
DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_WMDRM_EXPR_ExtractDateToken  ( DRM_CONST_STRING* pdstrExpression, TOKEN *pToken );

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_WMDRM_EXPR_EvaluateExpression(
    __in    const DRM_CONST_STRING            *pdstrExpression,
    __inout       DRM_WMDRM_EXPR_EVAL_CONTEXT *pEEContext,
    __out         TOKEN                       *ptResult );

DRM_API DRM_RESULT DRM_CALL DRM_WMDRM_EXPR_LEVL_EvaluateExpression(
    __inout       DRM_LICEVAL_CONTEXT *f_pContextLicEval,
    __in    const DRM_CONST_STRING    *f_pdstrExpression,
    __out         DRM_BOOL            *f_pfValue );

/*
** Secure store variable accessor/mutator functions.
** These will be given to the Expression evaluator via it's context structure.
** The implementation lives in exprvariable.c
*/
DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_WMDRM_EXPR_GlobalSetVariable(
    const DRM_CONST_STRING *pStringToken,
    const TOKEN            *pNewValue,
          TOKEN            *pResult,
          DRM_VOID         *pvOpaqueData );

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_WMDRM_EXPR_GlobalGetVariable(
    const DRM_CONST_STRING *pStringToken,
          TOKEN            *pResult,
          DRM_VOID         *pvOpaqueData );

DRM_API DRM_RESULT DRM_CALL DRM_WMDRM_LA_ProcessResponse(
    __in_bcount( f_cbResponse )        DRM_BYTE *f_pbResponse,
    __in                               DRM_DWORD                             f_cbResponse,
    __in                               DRM_LICEVAL_CONTEXT                  *f_pcontextLEVL,
    __in                               DRM_LICSTORE_CONTEXT                 *f_pcontextLSTXML,
    __in                               DRM_LICSTORE_CONTEXT                 *f_pcontextLSTXMR,
    __in                               DRM_LICSTOREENUM_CONTEXT             *f_pLicStoreEnumContext,
    __in_opt                           DRM_INCLUSION_LIST_CALLBACK_STRUCT   *f_pInclusionListCallback,
    __in_opt                           pfnLicenseResponseCallback            f_pfnCallback,
    __in_opt                           DRM_VOID                             *f_pvCallbackContext,
    __in                               DRM_DST                              *f_pDatastore,
    __in                               DRM_VIEW_RIGHTS_CONTEXT              *f_pcontextASD,
    __in_bcount( DRM_MAX_LICENSESIZE ) DRM_BYTE                              f_rgbLicenseBuffer[__CB_DECL(DRM_MAX_LICENSESIZE)],
    __in_opt                           DRM_SYNC_CONTEXT                     *f_pcontextSync,
    __out_opt                          DRM_LONG                             *f_plReason );

DRM_API DRM_RESULT DRM_CALL DRM_WMDRM_HDR_VerifyLegacySignature(
    __in const DRM_CONST_STRING   *f_pdstrContentHeader,
    __in const DRM_CONST_STRING   *f_pdstrPubKey,
    __in       DRM_CONST_STRING   *f_pdstrData,
    __in       DRM_CRYPTO_CONTEXT *f_pContext );

DRM_API DRM_WORD DRM_CALL DRM_WMDRM_LICOPL_GetOPLLevel(
    __in const DRM_CONST_STRING *f_pdstrRestrictions,
    __in const DRM_CONST_STRING *f_pdstrCategory );

DRM_API DRM_RESULT DRM_CALL DRM_WMDRM_LICOPL_ProcessExclusions(
    __in    const DRM_CONST_STRING             *f_pdstrRestrictions,
    __inout       DRM_OPL_OUTPUT_IDS           *f_pOPLIds,
    __in          DRM_STACK_ALLOCATOR_CONTEXT  *f_pstack );

DRM_API DRM_RESULT DRM_CALL DRM_WMDRM_LICOPL_ProcessInclusions(
    __in    const DRM_CONST_STRING             *f_pdstrRestrictions,
    __inout       DRM_OPL_OUTPUT_IDS           *f_pOPLIds,
    __in          DRM_STACK_ALLOCATOR_CONTEXT  *f_pstack );

DRM_API DRM_RESULT DRM_CALL DRM_WMDRM_LICOPL_ProcessPlayOutputLevelData(
    __in    const DRM_CONST_STRING             *f_pdstrRestrictions,
    __inout       DRM_PLAY_OPL_EX2             *f_pPlayOPL,
    __in          DRM_STACK_ALLOCATOR_CONTEXT  *f_pstack );

DRM_API DRM_RESULT DRM_CALL DRM_WMDRM_LICCOPYOPL_ASD_ExamineOutputLevels(
    __in  const DRM_VIEW_RIGHTS_CONTEXT *f_pcontextLQ,
    __in  const DRM_COPY_OPL            *f_pOutputLevels,
    __out       DRM_DWORD               *f_pdwResult );

DRM_API DRM_RESULT DRM_CALL DRM_WMDRM_LICCOPYOPL_ProcessCopyOutputLevelData(
    __in    const DRM_CONST_STRING             *f_pdstrRestrictions,
    __inout       DRM_COPY_OPL                 *f_pCopyOPL,
    __in          DRM_STACK_ALLOCATOR_CONTEXT  *f_pstack );

EXIT_PK_NAMESPACE;

#endif /* __DRMWMDRM_H__ */

