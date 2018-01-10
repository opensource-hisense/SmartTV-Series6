/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRMMETERIMPL_H__
#define __DRMMETERIMPL_H__

#include <drmmetering.h>
#include <drmxmlbuilder.h>
#include <drmutilities.h>

ENTER_PK_NAMESPACE;

#define DRM_METERING_CONTEXT        DRM_SECSTORE_CONTEXT

typedef struct __tagDRM_METERINGENUM_CONTEXT
{
    DRM_MID                     oMID;
    DRM_SECSTOREENUM_CONTEXT    oSecStoreEnum;
} DRM_METERINGENUM_CONTEXT;

#define DRM_METER_RESPONSE_PARTIAL 0x00000001

extern DRM_EXPORT_VAR const DRM_KID g_kidTID;

extern DRM_EXPORT_VAR const DRM_KID g_kidTIDPrev;

PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_BUFFER_PARAM_25033, "Out params can't be const")
PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_PARAM_25004, "Out params can't be const")
__checkReturn DRM_RESULT DRM_MTR_GetKIDData(
    __inout                           DRM_METERING_CONTEXT         *f_pmeterstore,
    __inout                           DRM_STACK_ALLOCATOR_CONTEXT  *f_pstack,
    __deref_out_ecount(*f_pcbDataOut) DRM_BYTE                    **f_ppbDataOut,
    __out                             DRM_DWORD                    *f_pcbDataOut );
PREFAST_POP
PREFAST_POP

PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_PARAM_25004, "f_pOEMContext can never be const")
DRM_API DRM_RESULT DRM_MTR_CreateNewTID(
    __in_opt DRM_VOID *f_pOEMContext,
    __out    DRM_TID  *f_ptid );
PREFAST_POP

PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_PARAM, "Out params can't be const, DRM_DST should not be const")
DRM_API DRM_RESULT DRM_NO_INLINE DRM_MTR_ReadTIDFromMeteringStore(
    __in            DRM_METERING_CONTEXT   *f_pmeterstore,
    __in      const DRM_BYTE                f_rgbPasswordSST [__CB_DECL(DRM_SHA1_DIGEST_LEN)],
    __in      const DRM_MID                *f_pmid,
    __out           DRM_TID                *f_ptid,
    __out_opt       DRM_CONST_STRING       *f_pdstrTidBase64,
    __in            DRM_DST                *f_pDatastore );
PREFAST_POP

PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_PARAM, "DRM_DST should not be const")
PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_PARAM_25004, "Out params can't be const")
DRM_API DRM_RESULT DRM_NO_INLINE DRM_MTR_WriteTIDToMeteringStore(
    __inout     DRM_METERING_CONTEXT *f_pmeterstore,
    __in  const DRM_BYTE              f_rgbPasswordSST [__CB_DECL(DRM_SHA1_DIGEST_LEN)],
    __in  const DRM_MID              *f_pmid,
    __in  const DRM_TID              *f_ptid,
    __in        DRM_DST              *f_pDatastore );
PREFAST_POP
PREFAST_POP

PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_BUFFER_PARAM_25033, "Out params can't be const")
PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_PARAM_25004, "Out params can't be const")
DRM_API DRM_RESULT DRM_CALL DRM_MTR_GetAllData(
    __inout                        DRM_METERING_CONTEXT *f_pcontextMTR,
    __out_bcount_opt( *f_pcbData ) DRM_BYTE             *f_pbData,
    __out                          DRM_DWORD            *f_pcbData );
PREFAST_POP
PREFAST_POP

PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_PARAM, "DRM_DST should not be const")
DRM_API DRM_RESULT DRM_CALL DRM_MTR_InitEnum(
    __in  const DRM_MID                   *f_pmid,
    __out       DRM_METERINGENUM_CONTEXT  *f_pcontextMTREnum,
    __in        DRM_DST                   *f_pDatastore );
PREFAST_POP

PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_BUFFER_PARAM_25033, "Out params can't be const")
PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_PARAM_25004, "Out params can't be const")
DRM_API DRM_RESULT DRM_CALL DRM_MTR_EnumNext(
    __inout  DRM_METERINGENUM_CONTEXT *f_pcontextMTREnum,
    __out    DRM_KID                  *f_pkid,
    __out    DRM_DWORD                *f_pcbData );
PREFAST_POP
PREFAST_POP

PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_BUFFER_PARAM_25033, "Out params can't be const")
PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_PARAM, "Out params can't be const")
DRM_API DRM_RESULT DRM_CALL DRM_MTR_GenerateMeterChallenge(
    __in                                 DRM_LICEVAL_CONTEXT *f_pcontextLEVL,
    __inout_bcount( f_cbStack )          DRM_BYTE            *f_pbStack,
    __in                                 DRM_DWORD            f_cbStack,
    __in                           const DRM_CONST_STRING    *f_pdstrMeterCert,
    __out                                _XMBContext         *f_pChallenge,
    __inout                              DRM_DWORD           *f_pcbChallenge,
    __out_ecount_opt( *f_pcchURL )       DRM_CHAR            *f_pchURL,
    __inout                              DRM_DWORD           *f_pcchURL );
PREFAST_POP
PREFAST_POP

PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_BUFFER_PARAM_25033, "Out params can't be const")
PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_PARAM_25004, "Out params can't be const")
DRM_API DRM_RESULT DRM_CALL DRM_MTR_ProcessMeterResponse(
    __inout                        DRM_LICEVAL_CONTEXT *f_pcontextLEVL,
    __inout_bcount( f_cbStack )    DRM_BYTE            *f_pbStack,
    __in                           DRM_DWORD            f_cbStack,
    __in_bcount( f_cbData )  const DRM_BYTE            *f_pbData,
    __in                           DRM_DWORD            f_cbData,
    __out                          DRM_DWORD           *f_pfFlags );
PREFAST_POP
PREFAST_POP

PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_PARAM, "DRM_DST should not be const")
PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_PARAM_25004, "Out params can't be const")
DRM_API DRM_RESULT DRM_CALL DRM_MTR_CloseContext(
    __inout DRM_METERING_CONTEXT *pcontextMetering,
    __in    DRM_DST              *pDataStore);
PREFAST_POP
PREFAST_POP

PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_PARAM, "DRM_DST should not be const")
PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_PARAM_25004, "Out params can't be const")
DRM_API DRM_RESULT DRM_CALL DRM_MTR_OpenId(
    __inout                                  DRM_METERING_CONTEXT *f_pcontextMTR,
    __in                               const DRM_MID              *f_pmid,
    __in                               const DRM_KID              *f_pkid,
    __in_bcount( DRM_SHA1_DIGEST_LEN ) const DRM_BYTE              f_rgbPasswordMTR[ __CB_DECL( DRM_SHA1_DIGEST_LEN ) ],
    __in                                     DRM_DST              *f_pDatastore );
PREFAST_POP
PREFAST_POP

PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_PARAM_25004, "Out params can't be const")
DRM_API DRM_RESULT DRM_CALL DRM_MTR_IncrementCount(
    __inout       DRM_METERING_CONTEXT *pcontextMetering,
    __in    const DRM_CONST_STRING     *pdstrAction );
PREFAST_POP

PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_BUFFER_PARAM_25033, "Out params can't be const")
PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_PARAM_25004, "Out params can't be const")
DRM_API DRM_RESULT DRM_CALL DRM_MTR_CreateMeterStorePassword(
    __in                                             const DRM_CONST_STRING *f_pdstrMID,
    __out_bcount( DRM_SHA1_DIGEST_LEN )                    DRM_BYTE          f_rgbPasswordSST[ __CB_DECL( DRM_SHA1_DIGEST_LEN ) ],
    __inout_ecount( 1 )                                    DRM_BB_CONTEXT   *f_pcontextBBX );
PREFAST_POP
PREFAST_POP

PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_BUFFER_PARAM_25033, "Out params can't be const")
PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_PARAM_25004, "Out params can't be const")
DRM_API DRM_RESULT DRM_CALL DRM_MTR_CreateMeterStorePasswordFromBinaryMID(
    __in                                const DRM_MID        *f_pmid,
    __out_bcount( DRM_SHA1_DIGEST_LEN )       DRM_BYTE        f_rgbPasswordSST[ __CB_DECL( DRM_SHA1_DIGEST_LEN ) ],
    __inout_ecount( 1 )                       DRM_BB_CONTEXT *f_pcontextBBX );
PREFAST_POP
PREFAST_POP

DRM_API DRM_RESULT DRM_CALL DRM_MTR_UpdateData(
    __in                    const DRM_MID                 *f_pmid,
    __in                    const DRM_LID                 *f_plid,
    __in                    const DRM_KID                 *f_pkid,
    __in_ecount(f_cActions) const DRM_CONST_STRING       **f_ppdstrActions,
    __in                          DRM_DWORD                f_cActions,
    __in                          DRM_METERING_CONTEXT    *f_pcontextMTR,
    __in                          DRM_DST                 *f_pDatastore,
    __in                          DRM_BB_CONTEXT          *f_pbcontextBBX );

DRM_API DRM_RESULT DRM_CALL DRM_MTR_EnumLoadCurrent(
    __in                                     DRM_METERINGENUM_CONTEXT *f_pcontextMTREnum,
    __in                                     DRM_METERING_CONTEXT     *f_pcontextMTR,
    __in_bcount( DRM_SHA1_DIGEST_LEN ) const DRM_BYTE                  f_rgbPasswordMTR[ __CB_DECL( DRM_SHA1_DIGEST_LEN ) ],
    __out                                    DRM_KID                  *f_pkid,
    __out                                    DRM_DWORD                *f_pcbData );

DRM_API DRM_RESULT DRM_CALL DRM_MTR_EnumDeleteCurrent(
    __in DRM_METERINGENUM_CONTEXT *f_pcontextMTREnum,
    __in DRM_METERING_CONTEXT     *f_pcontextMTR );

DRM_API DRM_RESULT DRM_CALL DRM_MTR_ParseMeterCert(
    __in      const DRM_CONST_STRING    *f_pdstrMeterCert,
    __in            DRM_LICEVAL_CONTEXT *f_pcontextLEVL,
    __out_opt       PUBKEY              *f_ppubkeyMAS,
    __out_opt       DRM_CONST_STRING    *f_pdstrDataMID,
    __out_opt       DRM_MID             *f_pmid,
    __out_opt       DRM_CONST_STRING    *f_pdstrDataURL );

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_MTR_ParseBinaryMeterCert(
    __inout                            DRM_BB_CONTEXT               *f_poBBXContext,
    __inout                            DRM_DST                      *f_poDSTContext,
    __inout                            DRM_SECSTORE_CONTEXT         *f_poSSTContext,
    __inout_opt                        DRM_REVOCATIONSTORE_CONTEXT  *f_poRevStore,
    __in_bcount_opt(f_cbRevocationBuffer)
                                       DRM_BYTE                     *f_pbRevocationBuffer,
    __in                               DRM_DWORD                     f_cbRevocationBuffer,
    __in_bcount(f_cbMeterCert)   const DRM_BYTE                     *f_pbMeterCert,
    __in                         const DRM_DWORD                     f_cbMeterCert,
    __out                              DRM_MID                      *f_poMID,
    __out_ecount_opt(*f_pcchURL)       DRM_CHAR                     *f_pchURL,
    __inout_opt                        DRM_DWORD                    *f_pcchURL,
    __out                              PUBKEY_P256                  *f_poServerPubKey );

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_MTR_GenerateMeterDataChallenge(
    __inout                                DRM_BB_CONTEXT *f_poBBXContext,
    __inout                                DRM_DST        *f_poDSTContext,
    __inout                                DRM_SECSTORE_CONTEXT *f_poSSTContext,
    __inout_opt                            DRM_REVOCATIONSTORE_CONTEXT *f_poRevStore,
    __in_bcount_opt(f_cbRevocationBuffer)  DRM_BYTE       *f_pbRevocationBuffer,
    __in                                   DRM_DWORD       f_cbRevocationBuffer,
    __in_bcount(f_cbStack)                 DRM_BYTE       *f_pbStack,
    __in                                   DRM_DWORD       f_cbStack,
    __in_bcount(f_cbMeterCert)       const DRM_BYTE       *f_pbMeterCert,
    __in                                   DRM_DWORD       f_cbMeterCert,
    __in_bcount(f_cbDeviceCert)      const DRM_BYTE       *f_pbDeviceCert,
    __in                                   DRM_DWORD       f_cbDeviceCert,
    __in_ecount_opt(f_cchCustomData) const DRM_CHAR       *f_pchCustomData,
    __in                                   DRM_DWORD       f_cchCustomData,
    __out_ecount_opt(*f_pcchURL)           DRM_CHAR       *f_pchURL,
    __inout                                DRM_DWORD      *f_pcchURL,
    __out_bcount_opt( *f_pcbChallenge )    DRM_BYTE       *f_pbChallenge,
    __inout                                DRM_DWORD      *f_pcbChallenge );

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_MTR_ProcessMeterDataResponse(
    __in                                    DRM_BB_CONTEXT              *f_poBBXContext,
    __in                                    DRM_DST                     *f_poDSTContext,
    __inout                                 DRM_SECSTORE_CONTEXT        *f_poSSTContext,
    __inout_opt                             DRM_REVOCATIONSTORE_CONTEXT *f_poRevStore,
    __in_bcount_opt(f_cbRevocationBuffer)   DRM_BYTE                    *f_pbRevocationBuffer,
    __in                                    DRM_DWORD                    f_cbRevocationBuffer,
    __inout_bcount(*f_pcbScratch)           DRM_BYTE                    *f_pbScratch,
    __inout                                 DRM_DWORD                   *f_pcbScratch,
    __inout_bcount(f_cbResponse)            DRM_BYTE                    *f_pbResponse,
    __in                                    DRM_DWORD                    f_cbResponse,
    __inout                                 DRM_BOOL                    *f_pfResponseSignatureChecked,
    __inout                                 DRM_DWORD                   *f_pdwProtocol,
    __out_opt                               DRM_RESULT                  *f_pResult );

DRM_API DRM_RESULT DRM_CALL DRM_MTR_GenerateMeterCertChallenge(
    __in                                    DRM_BB_CONTEXT  *f_poBBXContext,
    __in                              const DRM_MID         *f_poMID,
    __in_ecount_opt(f_cchCustomData)  const DRM_CHAR        *f_pchCustomData,
    __in                                    DRM_DWORD        f_cchCustomData,
    __out_bcount_opt(*f_pcbChallenge)       DRM_BYTE        *f_pbChallenge,
    __inout                                 DRM_DWORD       *f_pcbChallenge );

DRM_API DRM_RESULT DRM_CALL DRM_MTR_ProcessMeterCertResponse(
    __in                       DRM_LICEVAL_CONTEXT   *f_poLicEvalContext,
    __in                       DRM_METERCERT_CONTEXT *f_poMeterCertStoreContext,
    __in_bcount(*f_pcbScratch) DRM_BYTE              *f_pbScratch,
    __inout                    DRM_DWORD             *f_pcbScratch,
    __in_bcount(f_cbResponse)  DRM_BYTE              *f_pbResponse,
    __in                       DRM_DWORD              f_cbResponse,
    __out_opt                  DRM_RESULT            *f_pResult );

EXIT_PK_NAMESPACE;

#endif /* __DRMMETERIMPL_H__ */

