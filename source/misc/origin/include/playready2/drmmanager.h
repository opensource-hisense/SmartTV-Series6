/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRMMANAGER_H__
#define __DRMMANAGER_H__

#include <drmrevocation.h>
#include <drmcontextsizes.h>
#include <drmviewrights.h>
#include <drmenvelope.h>
#include <drmcallbacks.h>
#include <drmdomainapi.h>
#include <drmlicacqv3.h>
#include <drmmanagertypes.h>
#include <drmprndformat.h>
#include <drmlicgentypes.h>
#include <drmm2tstypes.h>
#include <drminitparser.h>

#ifdef PLAYREADY2TEE
#include <teecommon.h>
#endif

ENTER_PK_NAMESPACE;

/* Minimum OpaqueBuffer size. */
#define MINIMUM_APPCONTEXT_OPAQUE_BUFFER_SIZE                  ( DRM_MAX_LICENSE_CHAIN_DEPTH * ( DWORD_ALIGNED_SIZE( DRM_STANDARD_PLAYREADYOBJSIZE ) + DWORD_ALIGNED_SIZE( DRM_MAX_LICENSESIZE ) ) )

DRM_API DRM_RESULT DRM_CALL Drm_Initialize(
    __in                                    DRM_APP_CONTEXT     *f_poAppContext,
    __in_opt                                DRM_VOID            *f_pOEMContext,
    __in_bcount( f_cbOpaqueBuffer )         DRM_BYTE            *f_pbOpaqueBuffer,
    __in                                    DRM_DWORD            f_cbOpaqueBuffer,
    __in                              const DRM_CONST_STRING    *f_pdstrDeviceStoreName );

DRM_API DRM_RESULT DRM_CALL Drm_ResizeOpaqueBuffer(
    __in                                    DRM_APP_CONTEXT     *f_poAppContext,
    __in_bcount( f_cbOpaqueBuffer )         DRM_BYTE            *f_pbOpaqueBuffer,
    __in                                    DRM_DWORD            f_cbOpaqueBuffer );

DRM_API DRM_RESULT DRM_CALL Drm_GetOpaqueBuffer(
    __in                                    DRM_APP_CONTEXT     *f_poAppContext,
    __out                                   DRM_BYTE           **f_ppbOpaqueBuffer,
    __out                                   DRM_DWORD           *f_pcbOpaqueBuffer );

DRM_API DRM_VOID DRM_CALL Drm_Uninitialize(
    __in DRM_APP_CONTEXT *f_poAppContext );

DRM_API DRM_RESULT DRM_CALL Drm_Reinitialize(
    __in DRM_APP_CONTEXT *f_poAppContext );

DRM_API DRM_VOID DRM_CALL Drm_ClearAllCaches( DRM_VOID );

DRM_API DRM_RESULT DRM_CALL Drm_Content_SetProperty(
    __in                                      DRM_APP_CONTEXT          *f_poAppContext,
    __in                                      DRM_CONTENT_SET_PROPERTY  f_eProperty,
    __in_bcount_opt( f_cbPropertyData ) const DRM_BYTE                 *f_pbPropertyData,
    __in                                      DRM_DWORD                 f_cbPropertyData );

DRM_API DRM_RESULT DRM_CALL Drm_Content_GetProperty(
    __inout                                DRM_APP_CONTEXT          *f_poAppContext,
    __in                                   DRM_CONTENT_GET_PROPERTY  f_eProperty,
    __out_bcount_opt( *f_pcbPropertyData ) DRM_BYTE                 *f_pbPropertyData,
    __inout                                DRM_DWORD                *f_pcbPropertyData );

DRM_API DRM_RESULT DRM_CALL Drm_Content_UpdateEmbeddedStore(
    __in    DRM_APP_CONTEXT     *f_poAppContext );

DRM_API DRM_RESULT DRM_CALL Drm_Content_UpdateEmbeddedStore_Commit(
    __in const DRM_APP_CONTEXT     *f_poAppContext );

DRM_API DRM_RESULT DRM_CALL Drm_Device_GetProperty(
    __in                                DRM_APP_CONTEXT         *f_poAppContext,
    __in                                DRM_DEVICE_GET_PROPERTY  f_eProperty,
    __out_bcount_opt( *f_pcbProperty )  DRM_BYTE                *f_pbProperty,
    __inout                             DRM_DWORD               *f_pcbProperty );

DRM_API DRM_RESULT DRM_CALL Drm_SyncListItem_InitEnum(
    __in DRM_APP_CONTEXT *f_poAppContext );

DRM_API DRM_RESULT DRM_CALL Drm_SyncListItem_EnumNext(
    __in      DRM_APP_CONTEXT *f_poAppContext,
    __in      DRM_DWORD        f_cMaxCount,
    __in      DRM_DWORD        f_cMaxHours,
    __out_opt DRM_KID         *f_pKID );

/*
** ---------------------------------------
** License acquisition API functions
** ---------------------------------------
*/
DRM_API DRM_RESULT DRM_CALL Drm_LicenseAcq_GenerateChallenge(
    __in                                          DRM_APP_CONTEXT  *f_poAppContext,
    __in_ecount_opt( f_cRights )            const DRM_CONST_STRING *f_rgpdstrRights[],
    __in                                          DRM_DWORD         f_cRights,
    __in_opt                                const DRM_DOMAIN_ID    *f_poDomainID,
    __in_ecount_opt( f_cchCustomData )      const DRM_CHAR         *f_pchCustomData,
    __in                                          DRM_DWORD         f_cchCustomData,
    __out_ecount_opt( *f_pcchSilentURL )          DRM_CHAR         *f_pchSilentURL,
    __inout_opt                                   DRM_DWORD        *f_pcchSilentURL,
    __out_ecount_opt( *f_pcchNonSilentURL )       DRM_CHAR         *f_pchNonSilentURL,
    __inout_opt                                   DRM_DWORD        *f_pcchNonSilentURL,
    __out_bcount_opt( *f_pcbChallenge )           DRM_BYTE         *f_pbChallenge,
    __inout                                       DRM_DWORD        *f_pcbChallenge );

DRM_API DRM_RESULT DRM_CALL Drm_LicenseAcq_ProcessResponse(
    __in                        DRM_APP_CONTEXT                *f_poAppContext,
    __in                        DRM_PROCESS_LIC_RESPONSE_FLAG   f_dwFlags,
    __in_opt                    pfnLicenseResponseCallback      f_pfnCallback,
    __in_opt                    DRM_VOID                       *f_pvCallbackContext,
    __in_bcount( f_cbResponse ) DRM_BYTE                       *f_pbResponse,
    __in                        DRM_DWORD                       f_cbResponse,
    __out                       DRM_LICENSE_RESPONSE           *f_poLicenseResponse );

#ifdef PLAYREADY2TEE
DRM_API DRM_RESULT DRM_CALL Drm_LicenseAcq_ProcessResponse_SecStop(
    __in                        DRM_APP_CONTEXT                *f_poAppContext,
    __in                        DRM_PROCESS_LIC_RESPONSE_FLAG   f_dwFlags,
    __in_opt                    pfnLicenseResponseCallback      f_pfnCallback,
    __in_opt                    DRM_VOID                       *f_pvCallbackContext,
    __in_bcount( f_cbResponse ) DRM_BYTE                       *f_pbResponse,
    __in                        DRM_DWORD                       f_cbResponse,
    __out_bcount( 16 )          DRM_BYTE                       *f_pbSessionID, /* expected length 16 */
    __out                       DRM_LICENSE_RESPONSE           *f_poLicenseResponse );

#endif

DRM_API DRM_RESULT DRM_CALL Drm_LicenseAcq_GenerateAck(
    __in                                DRM_APP_CONTEXT      *f_poAppContext,
    __in                                DRM_LICENSE_RESPONSE *f_poLicenseResponse,
    __out_bcount_opt( *f_pcbChallenge ) DRM_BYTE             *f_pbChallenge,
    __inout                             DRM_DWORD            *f_pcbChallenge );

DRM_API DRM_RESULT DRM_CALL Drm_LicenseAcq_ProcessAckResponse(
    __in                        const DRM_APP_CONTEXT *f_poAppContext,
    __in_bcount( f_cbResponse )       DRM_BYTE        *f_pbResponse,
    __in                              DRM_DWORD        f_cbResponse,
    __out_opt                         DRM_RESULT      *f_pResult );

DRM_API DRM_RESULT DRM_CALL Drm_LicenseAcq_GetContentHeader(
    __in                                           DRM_APP_CONTEXT *f_poAppContext,
    __in                                     const DRM_KID         *f_pkid,
    __out_ecount_opt( *f_pcchContentHeader )       DRM_WCHAR       *f_pwszContentHeader,
    __inout                                        DRM_DWORD       *f_pcchContentHeader );

DRM_API DRM_RESULT DRM_CALL Drm_GetAdditionalResponseData(
    __in                            const DRM_APP_CONTEXT  *f_poAppContext,
    __in_bcount( f_cbResponse )     const DRM_BYTE         *f_pbResponse,
    __in                                  DRM_DWORD         f_cbResponse,
    __in                                  DRM_DWORD         f_dwDataType,
    __out_ecount_opt( *f_pcchDataString ) DRM_CHAR         *f_pchDataString,
    __inout                               DRM_DWORD        *f_pcchDataString );

DRM_API DRM_RESULT DRM_CALL Drm_Reader_Bind(
    __in                           DRM_APP_CONTEXT      *f_poAppContext,
    __in_ecount( f_cRights ) const DRM_CONST_STRING     *f_rgpdstrRights[],
    __in                           DRM_DWORD             f_cRights,
    __in_opt                       DRMPFNPOLICYCALLBACK  f_pfnPolicyCallback,
    __in_opt                 const DRM_VOID             *f_pv,
    __out_opt                      DRM_DECRYPT_CONTEXT  *f_pcontextDCRY );

DRM_API DRM_VOID DRM_CALL Drm_Reader_Close(
    __in_ecount( 1 ) DRM_DECRYPT_CONTEXT *f_pcontextDCRY );

DRM_API DRM_RESULT DRM_CALL Drm_Reader_Commit(
    __in           DRM_APP_CONTEXT      *f_poAppContext,
    __in_opt       DRMPFNPOLICYCALLBACK  f_pfnPolicyCallback,
    __in_opt const DRM_VOID             *f_pvCallbackData );

DRM_API DRM_RESULT DRM_CALL Drm_Reader_InitDecrypt(
    __inout_ecount( 1 )                                                DRM_DECRYPT_CONTEXT *f_pDecryptContext,
    __in_bcount_opt( MIN(DRM_CPHR_CB_FOR_INITDECRYPT,f_cbData) ) const DRM_BYTE            *f_pbLast15,
    __in                                                               DRM_DWORD            f_cbData );

#define DRM_REAL_TIME_EXPIRATION_CHECK_BYTE_COUNT   0x400000  /* Check for expiration every 4MB (0x400000 == 4*1024*1024 == 4,194,304 bytes) of data processed */

DRM_API DRM_RESULT DRM_CALL Drm_Reader_Decrypt(
    __in_ecount( 1 )           DRM_DECRYPT_CONTEXT          *f_pDecryptContext,
    __inout_opt                DRM_AES_COUNTER_MODE_CONTEXT *f_pCtrContext,
    __inout_bcount( f_cbData ) DRM_BYTE                     *f_pbData,
    __in                       DRM_DWORD                     f_cbData );

DRM_API DRM_RESULT DRM_CALL Drm_Reader_DecryptOpaque(
    __in_ecount( 1 )           DRM_DECRYPT_CONTEXT          *f_pDecryptContext,
    __inout                    DRM_AES_COUNTER_MODE_CONTEXT *f_pCtrContext,
    __in                       OEM_OPAQUE_BUFFER_HANDLE      f_hInBuf,
    __in                       OEM_OPAQUE_BUFFER_HANDLE      f_hOutBuf,
    __in                       DRM_DWORD                     f_cbData );

DRM_API DRM_RESULT DRM_CALL Drm_License_GetProperty(
    __in                                        DRM_APP_CONTEXT           *f_poAppContext,
    __in                                        DRM_LICENSE_GET_PROPERTY   f_eProperty,
    __inout_bcount_opt( *f_pcbExtraData ) const DRM_BYTE                  *f_pbExtraData,
    __in_opt                              const DRM_DWORD                 *f_pcbExtraData,
    __out                                       DRM_DWORD                 *f_pdwOutputData );

DRM_API DRM_RESULT DRM_CALL Drm_LicenseQuery_GetState(
    __in                                  DRM_APP_CONTEXT        *f_poAppContext,
    __in_ecount( f_cRightsQueried ) const DRM_CONST_STRING       *f_rgpdstrRights[],
    __in                                  DRM_DWORD               f_cRightsQueried,
    __out_ecount( f_cRightsQueried )      DRM_LICENSE_STATE_DATA  f_rgStateData[],
    __in_opt                              DRMPFNPOLICYCALLBACK    f_pfnPolicyCallback,
    __in_opt                        const DRM_VOID               *f_pv );

DRM_API DRM_RESULT DRM_CALL Drm_LicenseQuery_IsAllowed(
    __in           DRM_APP_CONTEXT            *f_poAppContext,
    __in     const DRM_CONST_STRING           *f_pdstrQuery,
    __in_opt       DRMPFNPOLICYCALLBACK        f_pfnPolicyCallback,
    __in_opt const DRM_VOID                   *f_pvCallbackData,
    __out          DRM_LICENSE_STATE_CATEGORY *f_pCategory );

DRM_API DRM_RESULT DRM_CALL Drm_PlayReadyObject_ConvertFromWmdrmHeader(
    __in_bcount( f_cbWmdrmHeader )  const DRM_BYTE  *f_pbWmdrmHeader,
    __in                            const DRM_DWORD  f_cbWmdrmHeader,
    __in_ecount_nz_opt( f_cchPlayReadySilentURL )
                                    const DRM_WCHAR *f_pwchPlayReadySilentURL,
    __in                            const DRM_DWORD  f_cchPlayReadySilentURL,
    __in_ecount_nz_opt( f_cchPlayReadyNonSilentURL )
                                    const DRM_WCHAR *f_pwchPlayReadyNonSilentURL,
    __in                            const DRM_DWORD  f_cchPlayReadyNonSilentURL,
    __in_ecount_nz_opt( f_cchServiceID )
                                    const DRM_WCHAR *f_pwchServiceID,
    __in                            const DRM_DWORD  f_cchServiceID,
    __in                                  DRM_BOOL   f_fIncludeELS,
    __in_ecount_nz_opt( f_cchCustomAttributes )
                                    const DRM_WCHAR *f_pwchCustomAttributes,
    __in                            const DRM_DWORD  f_cchCustomAttributes,
    __inout_bcount_opt( *f_pcbPlayReadyObject )
                                          DRM_BYTE  *f_pbPlayReadyObject,
    __inout                               DRM_DWORD *f_pcbPlayReadyObject );

/*
** ---------------------------------------
** Sync list API functions
** ---------------------------------------
*/
#define DRM_SYNC_IGNORE_THRESHOLD_PARAMETER    0xFFFFFFFF

DRM_API DRM_RESULT DRM_CALL Drm_Sync_GenerateChallenge(
    __in                           DRM_APP_CONTEXT *f_poAppContext,
    __in                           DRM_DWORD        f_cMaxCount,
    __in                           DRM_DWORD        f_cMaxHours,
    __in                           DRM_DWORD        f_iKIDStart,
    __in                           DRM_DWORD        f_cKIDs,
    __out_opt                      DRM_DWORD       *f_piKIDNext,
    __out_opt                      DRM_DWORD       *f_pcKIDs,
    __out_bcount_opt( *f_pcbData ) DRM_BYTE        *f_pbData,
    __inout                        DRM_DWORD       *f_pcbData );

/*
** ---------------------------------------
** Secure Clock API functions
** ---------------------------------------
*/

DRM_API DRM_RESULT DRM_CALL Drm_SecureClock_ProcessResponse(
    __in                        DRM_APP_CONTEXT *f_poAppContext,
    __in_bcount( f_cbResponse ) DRM_BYTE        *f_pbResponse,
    __in                        DRM_DWORD        f_cbResponse,
    __out                       DRM_RESULT      *f_pResult );

DRM_API DRM_RESULT DRM_CALL Drm_SecureClock_GenerateChallenge(
    __in                                DRM_APP_CONTEXT *f_poAppContext,
    __out_ecount_opt( *f_pcchURL )      DRM_WCHAR       *f_pwszURL,
    __inout_opt                         DRM_DWORD       *f_pcchURL,
    __out_bcount_opt( *f_pcbChallenge ) DRM_BYTE        *f_pbChallenge,
    __inout                             DRM_DWORD       *f_pcbChallenge );

DRM_API DRM_RESULT DRM_CALL Drm_SecureClock_GetValue(
    __in                                          DRM_APP_CONTEXT *f_poAppContext,
    __in_ecount_opt( *f_pcchSecureTime )          DRM_WCHAR       *f_pwszSecureTime,
    __inout_opt                                   DRM_DWORD       *f_pcchSecureTime,
    __in_opt                                      DRM_DWORD       *f_pdwFlags,
    __in_bcount_opt( *f_pcbSecureTimeWithStatus ) DRM_BYTE        *f_pbSecureTimeWithStatus,
    __inout                                       DRM_DWORD       *f_pcbSecureTimeWithStatus );

DRM_API DRM_RESULT DRM_CALL Drm_StoreMgmt_CleanupStore(
    __in           DRM_APP_CONTEXT        *f_poAppContext,
    __in           DRM_DWORD               f_dwFlags,
    __in_opt const DRM_VOID               *f_pvCallerData,
    __in           DRM_DWORD               f_dwCallbackInterval,
    __in_opt       pfnStoreCleanupProgress f_pfnCallback );

DRM_API DRM_RESULT DRM_CALL Drm_StoreMgmt_DeleteLicenses(
    __in            DRM_APP_CONTEXT  *f_poAppContext,
    __in      const DRM_CONST_STRING *f_pdcstrKID,
    __out_opt       DRM_DWORD        *f_pcLicDeleted );

DRM_API DRM_RESULT DRM_CALL Drm_ProcessCommand(
    __in                                 DRM_APP_CONTEXT *f_poAppContext,
    __in                                 DRM_DWORD        f_dwOperationCode,
    __in                                 DRM_DWORD        f_dwRequestArgument1,
    __in                                 DRM_DWORD        f_dwRequestArgument2,
    __in                                 DRM_DWORD        f_dwRequestArgument3,
    __in                                 DRM_DWORD        f_dwRequestArgument4,
    __in_bcount( f_dwRequestDataLength ) DRM_BYTE        *f_pbRequestData,
    __in                                 DRM_DWORD        f_dwRequestDataLength,
    __out_opt                            DRM_DWORD       *f_pdwResponseResult1,
    __out_opt                            DRM_DWORD       *f_pdwResponseResult2,
    __out_opt                            DRM_DWORD       *f_pdwResponseResult3,
    __out_opt                            DRM_DWORD       *f_pdwResponseResult4 );

DRM_API DRM_RESULT DRM_CALL Drm_ProcessRequest(
    __in                                     DRM_APP_CONTEXT *f_poAppContext,
    __in                                     DRM_DWORD        f_dwOperationCode,
    __in                                     DRM_DWORD        f_dwRequestArgument1,
    __in                                     DRM_DWORD        f_dwRequestArgument2,
    __in                                     DRM_DWORD        f_dwRequestArgument3,
    __in                                     DRM_DWORD        f_dwRequestArgument4,
    __out                                    DRM_DWORD       *f_pdwResponseResult1,
    __out                                    DRM_DWORD       *f_pdwResponseResult2,
    __out                                    DRM_DWORD       *f_pdwResponseResult3,
    __out                                    DRM_DWORD       *f_pdwResponseResult4,
    __out_bcount( *f_pdwResponseDataLength ) DRM_BYTE        *f_pbResponseData,
    __out                                    DRM_DWORD       *f_pdwResponseDataLength );

/*
** ---------------------------------------
** Envelope API functions
** ---------------------------------------
*/

DRM_API DRM_RESULT DRM_CALL Drm_Envelope_Open(
    __in           DRM_APP_CONTEXT            *f_poAppContext,
    __in_opt       DRM_VOID                   *f_pOEMContext,
    __in_z   const DRM_WCHAR                  *f_pwszFilename,
    __out          DRM_ENVELOPED_FILE_CONTEXT *f_pEnvFile );

DRM_API DRM_RESULT DRM_CALL Drm_Envelope_DuplicateFileContext(
    __in_opt       DRM_VOID                   *f_pOEMContext,
    __in_z   const DRM_WCHAR                  *f_pwszFilename,
    __in     const DRM_ENVELOPED_FILE_CONTEXT *f_pSourceHandle,
    __out          DRM_ENVELOPED_FILE_CONTEXT *f_pNewHandle );

DRM_API DRM_RESULT DRM_CALL Drm_Envelope_InitializeRead(
    __in DRM_ENVELOPED_FILE_CONTEXT *f_pEnvFile,
    __in DRM_DECRYPT_CONTEXT        *f_pDecrypt );

DRM_API DRM_RESULT DRM_CALL Drm_Envelope_Close(
    __in DRM_ENVELOPED_FILE_CONTEXT *f_pEnvFile );

DRM_API DRM_RESULT DRM_CALL Drm_Envelope_GetSize(
    __in  DRM_ENVELOPED_FILE_CONTEXT *f_pEnvFile,
    __out DRM_DWORD                  *f_pcbFileSize );

DRM_API DRM_RESULT DRM_CALL Drm_Envelope_Read(
    __in                                              DRM_ENVELOPED_FILE_CONTEXT *f_pEnvFile,
    __out_ecount_part( f_cbToRead, *f_pcbBytesRead )  DRM_BYTE                   *f_pbBuffer,
    __in                                              DRM_DWORD                   f_cbToRead,
    __out                                             DRM_DWORD                  *f_pcbBytesRead );

DRM_API DRM_RESULT DRM_CALL Drm_Envelope_WritePlayReadyObject(
    __in         DRM_APP_CONTEXT            *f_poAppContext,
    __inout_opt  DRM_VOID                   *f_pOEMContext,
    __in_z const DRM_WCHAR                  *f_pwszFilename,
    __inout      DRM_ENVELOPED_FILE_CONTEXT *f_pEnvFile );

DRM_API DRM_RESULT DRM_CALL Drm_Envelope_Seek(
    __in  DRM_ENVELOPED_FILE_CONTEXT *f_pEnvFile,
    __in  DRM_LONG                    f_lDistanceToMove,
    __in  DRM_DWORD                   f_dwMoveMethod,
    __out DRM_DWORD                  *f_pdwNewFilePointer );

DRM_API DRM_RESULT DRM_CALL Drm_Envelope_GetOriginalFilename(
    __in                                        DRM_ENVELOPED_FILE_CONTEXT *f_pEnvFile,
    __out_ecount_opt( *f_pcchOriginalFilename ) DRM_WCHAR                  *f_pwszOriginalFilename,
    __inout                                     DRM_DWORD                  *f_pcchOriginalFilename );

/*
** ---------------------------------------
** Revocation API functions
** ---------------------------------------
*/

/* Recommeded revocation buffer size. */
#define REVOCATION_BUFFER_SIZE                  30 * 1024

DRM_API DRM_RESULT DRM_CALL Drm_Revocation_SetBuffer(
    __inout                                 DRM_APP_CONTEXT *f_poAppContext,
    __in_bcount_opt( f_cbRevocationBuffer ) DRM_BYTE        *f_pbRevocationBuffer,
    __in                                    DRM_DWORD        f_cbRevocationBuffer );

DRM_API DRM_RESULT DRM_CALL Drm_Revocation_GetBuffer(
    __inout                                      DRM_APP_CONTEXT  *f_poAppContext,
    __deref_out_bcount( *f_pcbRevocationBuffer ) DRM_BYTE        **f_ppbRevocationBuffer,
    __out                                        DRM_DWORD        *f_pcbRevocationBuffer );

DRM_API DRM_RESULT DRM_CALL Drm_Revocation_StoreRevListArray(
    __inout                           DRM_APP_CONTEXT *f_poAppContext,
    __in                              DRM_DWORD        f_cRevocationLists,
    __in_ecount( f_cRevocationLists ) DRM_RVK_LIST    *f_pRevocationLists );

DRM_API DRM_RESULT DRM_CALL Drm_Revocation_GetList(
    __inout                          DRM_APP_CONTEXT          *f_poAppContext,
    __in                             DRM_REVOCATION_TYPE_ENUM  f_eRevType,
    __out_bcount_opt( *f_pcbBuffer ) DRM_BYTE                 *f_pbBuffer,
    __inout_opt                      DRM_DWORD                *f_pcbBuffer,
    __out_opt                        DRM_DWORD                *f_pdwVersion );

DRM_API DRM_RESULT DRM_CALL Drm_Revocation_StorePackage(
    __inout                           DRM_APP_CONTEXT *f_poAppContext,
    __in_ecount( f_cchPackage ) const DRM_CHAR        *f_pchPackage,
    __in                              DRM_DWORD        f_cchPackage );

DRM_API DRM_RESULT DRM_CALL Drm_Platform_Initialize( DRM_VOID );

DRM_API DRM_RESULT DRM_CALL Drm_Platform_Uninitialize( DRM_VOID );

/*
** ---------------------------------------
** Domain API functions
** ---------------------------------------
*/
DRM_API DRM_RESULT DRM_CALL Drm_JoinDomain_GenerateChallenge(
    __in                                       DRM_APP_CONTEXT *f_poAppContext,
    __in                                       DRM_DWORD        f_dwFlags,
    __in_opt                                   DRM_DOMAIN_ID   *f_poDomainID,
    __in_ecount_opt( f_cchFriendlyName ) const DRM_CHAR        *f_pchFriendlyName,
    __in                                       DRM_DWORD        f_cchFriendlyName,
    __in_ecount_opt( f_cchData )         const DRM_CHAR        *f_pchData,
    __in                                       DRM_DWORD        f_cchData,
    __out_bcount_opt( *f_pcbChallenge )        DRM_BYTE        *f_pbChallenge,
    __inout                                    DRM_DWORD       *f_pcbChallenge );

DRM_API DRM_RESULT DRM_CALL Drm_JoinDomain_ProcessResponse(
    __in                        DRM_APP_CONTEXT              *f_poAppContext,
    __in                        DRM_PROCESS_DJ_RESPONSE_FLAG  f_dwFlags,
    __in_bcount( f_cbResponse ) DRM_BYTE                     *f_pbResponse,
    __in                        DRM_DWORD                     f_cbResponse,
    __out                       DRM_RESULT                   *f_pResult,
    __out_opt                   DRM_DOMAIN_ID                *f_poDomainID );

DRM_API DRM_RESULT DRM_CALL Drm_LeaveDomain_GenerateChallenge(
    __in                                      DRM_APP_CONTEXT *f_poAppContext,
    __in                                      DRM_DWORD        f_dwFlags,
    __in_opt                                  DRM_DOMAIN_ID   *f_poDomainID,
    __in_ecount_opt( f_cchData )        const DRM_CHAR        *f_pchData,
    __in                                      DRM_DWORD        f_cchData,
    __out_bcount_opt( *f_pcbChallenge )       DRM_BYTE        *f_pbChallenge,
    __inout                                   DRM_DWORD       *f_pcbChallenge );

DRM_API DRM_RESULT DRM_CALL Drm_LeaveDomain_ProcessResponse(
    __in                        const DRM_APP_CONTEXT *f_poAppContext,
    __in_bcount( f_cbResponse )       DRM_BYTE        *f_pbResponse,
    __in                              DRM_DWORD        f_cbResponse,
    __out                             DRM_RESULT      *f_pResult );

DRM_API DRM_RESULT DRM_CALL Drm_DomainCert_Find(
    __in                                       DRM_APP_CONTEXT *f_poAppContext,
    __in                                 const DRM_DOMAIN_ID   *f_poDomainID,
    __out_bcount_opt( *f_pcbDomainCert )       DRM_BYTE        *f_pbDomainCert,
    __inout                                    DRM_DWORD       *f_pcbDomainCert );

DRM_API DRM_RESULT DRM_CALL Drm_DomainCert_InitEnum(
    __in  DRM_APP_CONTEXT              *f_poAppContext,
    __out DRM_DOMAIN_CERT_ENUM_CONTEXT *f_poDomainCertEnumContext );

DRM_API DRM_RESULT DRM_CALL Drm_DomainCert_EnumNext(
    __in  DRM_DOMAIN_CERT_ENUM_CONTEXT  *f_poDomainCertEnumContext,
    __out DRM_DWORD                     *f_pcchDomainCert,
    __out DRM_DOMAINCERT_INFO           *f_poDomainCertInfo );

/*
** ---------------------------------------
** Initiator API Functions
** ---------------------------------------
*/
DRM_API DRM_RESULT DRM_CALL Drm_Initiator_InitEnum(
    __in    const DRM_CONST_STRING            *f_pdstrXML,
    __inout       DRM_INITIATORS_ENUM_CONTEXT *f_poEnumContext );


DRM_API DRM_RESULT DRM_CALL Drm_Initiator_EnumNext(
    __inout     DRM_INITIATORS_ENUM_CONTEXT *f_poEnumContext,
    __inout_opt DRM_INITIATOR_DATA         *f_poInitiatorData );

/*
** ---------------------------------------
** Metering Certificate API Functions
** ---------------------------------------
*/
DRM_API DRM_RESULT DRM_CALL Drm_MeterCert_InitEnum(
    __in    DRM_APP_CONTEXT     *pAppContext,
    __out   DRM_METERCERT_ENUM  *pMeterCertEnumContext );

DRM_API DRM_RESULT DRM_CALL Drm_MeterCert_EnumNext(
    __in                                DRM_METERCERT_ENUM  *pMeterCertEnumContext,
    __inout                             DRM_MID             *pmid,
    __out_ecount_opt( *f_cchLAINFO )    DRM_WCHAR           *pwszLAINFO,
    __out_opt                           DRM_DWORD           *f_cchLAINFO,
    __out_opt                           DRM_BOOL            *f_pfIsV2,
    __out_bcount_opt( *f_pcbMeterCert ) DRM_BYTE            *f_pbMeterCert,
    __out_opt                           DRM_DWORD           *f_pcbMeterCert );

DRM_API DRM_RESULT DRM_CALL Drm_MeterCert_Update(
    __in                        DRM_APP_CONTEXT    *pAppContext,
    __in_bcount( cbMeterCert )  DRM_BYTE           *pbMeterCert,
    __in                        DRM_DWORD           cbMeterCert,
    __out_opt                   DRM_MID            *pmid);

DRM_API DRM_RESULT DRM_CALL Drm_MeterCert_Invalidate(
    __in       DRM_APP_CONTEXT  *f_pcontextMGR,
    __in const DRM_MID          *f_pmid );

DRM_API DRM_RESULT DRM_CALL Drm_MeterCert_Delete(
    __in       DRM_APP_CONTEXT  *f_pcontextMGR,
    __in const DRM_MID          *f_pmid );

DRM_API DRM_RESULT DRM_CALL Drm_MeterCert_ProcessResponse(
    __in                        DRM_APP_CONTEXT *f_poAppContext,
    __in_bcount( f_cbResponse ) DRM_BYTE        *f_pbResponse,
    __in                        DRM_DWORD        f_cbResponse,
    __out                       DRM_RESULT      *f_pResult );

DRM_API DRM_RESULT DRM_CALL Drm_MeterCert_GenerateChallenge(
    __in                                    DRM_APP_CONTEXT *f_poAppContext,
    __in                              const DRM_MID         *f_poMID,
    __in_ecount_opt( f_cchCustomData) const DRM_CHAR        *f_pchCustomData,
    __in_opt                                DRM_DWORD        f_cchCustomData,
    __out_bcount_opt( *f_pcbChallenge )     DRM_BYTE        *f_pbChallenge,
    __inout                                 DRM_DWORD       *f_pcbChallenge );

DRM_API DRM_RESULT DRM_CALL Drm_Metering_GenerateChallenge(
    __in                                DRM_APP_CONTEXT  *f_poAppContext,
    __in_bcount( f_cbMeterCert ) const  DRM_BYTE         *f_pbMeterCert,
    __in                                DRM_DWORD         f_cbMeterCert,
    __in_ecount_opt( f_cchCustomData )  DRM_CHAR         *f_pchCustomData,
    __in_opt                            DRM_DWORD         f_cchCustomData,
    __out_ecount_opt( *f_pcchURL )      DRM_CHAR         *f_pchURL,
    __inout_opt                         DRM_DWORD        *f_pcchURL,
    __out_bcount_opt( *f_pcbChallenge ) DRM_BYTE         *f_pbChallenge,
    __inout                             DRM_DWORD        *f_pcbChallenge );

DRM_API DRM_RESULT DRM_CALL Drm_Metering_ProcessResponse(
    __in                        DRM_APP_CONTEXT  *f_poAppContext,
    __in_bcount( f_cbResponse ) DRM_BYTE         *f_pbResponse,
    __in                        DRM_DWORD         f_cbResponse,
    __out                       DRM_DWORD        *f_pfFlags );

/*
** ---------------------------------------
** Prnd API functions: General
** ---------------------------------------
*/

DRM_API DRM_RESULT DRM_CALL Drm_Prnd_GetMessageType(
    __inout_bcount( f_cbUnknownMessage )                        const DRM_BYTE                                         *f_pbUnknownMessage,
    __in                                                              DRM_DWORD                                         f_cbUnknownMessage,
    __out                                                             DRM_PRND_MESSAGE_TYPE                            *f_peMessageType );

DRM_API DRM_BYTE* DRM_CALL Drm_Prnd_MemAlloc(
    __in                                                              DRM_DWORD                                         f_cbToAlloc );

DRM_API DRM_VOID DRM_CALL Drm_Prnd_MemFree(
    __in                                                              DRM_BYTE                                         *f_pbToFree );

#define DRM_PRND_SAFEMEMFREE( pbToFree ) do {   \
        Drm_Prnd_MemFree( pbToFree );           \
        pbToFree = NULL;                        \
    } while(FALSE)

#define DRM_PRND_FLAG_NO_FLAGS                                      0x00000000
#define DRM_PRND_FLAG_REGISTRATION_REQUEST_SUPPORTS_LICENSE_PUSH    0x00000001
#define DRM_PRND_FLAG_LICENSE_TRANSMIT_IS_LICENSE_PUSH              0x00000002

/*
** ---------------------------------------
** Prnd API functions: Transmitter
** ---------------------------------------
*/
DRM_API DRM_RESULT DRM_CALL Drm_Prnd_Transmitter_BeginSession(
    __in                                                              DRM_APP_CONTEXT                                  *f_poAppContext,
    __in                                                              DRM_PRND_TRANSMITTER_CONTEXT                     *f_poNewPrndTransmitterContext );

DRM_API DRM_RESULT DRM_CALL Drm_Prnd_Transmitter_RegistrationRequest_Process(
    __in                                                              DRM_APP_CONTEXT                                  *f_poAppContext,
    __in_bcount( f_cbReqMessage )                               const DRM_BYTE                                         *f_pbReqMessage,
    __in                                                              DRM_DWORD                                         f_cbReqMessage,
    __in_opt                                                          Drm_Prnd_Data_Callback                            f_pfnDataCallback,
    __inout_ecount_opt( 1 )                                           DRM_VOID                                         *f_pvDataCallbackContext,
    __out_ecount( 1 )                                                 DRM_ID                                           *f_pSessionID,
    __out                                                             DRM_PRND_PROXIMITY_DETECTION_TYPE                *f_peProximityDetectionType,
    __deref_out_ecount( *f_pcbTransmitterProximityDetectionChannel )  DRM_BYTE                                        **f_ppbTransmitterProximityDetectionChannel,
    __out                                                             DRM_DWORD                                        *f_pcbTransmitterProximityDetectionChannel,
    __out                                                             DRM_DWORD                                        *f_pdwFlags );

DRM_API DRM_RESULT DRM_CALL Drm_Prnd_Transmitter_RegistrationResponse_Generate(
    __in                                                              DRM_APP_CONTEXT                                  *f_poAppContext,
    __in_opt                                                    const DRM_ID                                           *f_pCustomDataTypeID,
    __in_bcount_opt( f_cbCustomData )                           const DRM_BYTE                                         *f_pbCustomData,
    __in                                                              DRM_DWORD                                         f_cbCustomData,
    __in                                                              DRM_DWORD                                         f_dwFlags,
    __deref_out_ecount( *f_pcbRespMessage )                           DRM_BYTE                                        **f_ppbRespMessage,
    __out                                                             DRM_DWORD                                        *f_pcbRespMessage );

DRM_API DRM_RESULT DRM_CALL Drm_Prnd_Transmitter_RegistrationError_Generate(
    __in_opt                                                          DRM_APP_CONTEXT                                  *f_poAppContext,
    __in                                                              DRM_RESULT                                        f_drResult,
    __in                                                              DRM_DWORD                                         f_dwFlags,
    __deref_out_ecount( *f_pcbErrMessage )                            DRM_BYTE                                        **f_ppbErrMessage,
    __out                                                             DRM_DWORD                                        *f_pcbErrMessage );

DRM_API DRM_RESULT DRM_CALL Drm_Prnd_Transmitter_ProximityDetectionResult_Generate(
    __in_opt                                                          DRM_APP_CONTEXT                                  *f_poAppContext,
    __in_opt                                                    const DRM_ID                                           *f_pSessionID,
    __in                                                              DRM_RESULT                                        f_drResult,
    __in                                                              DRM_DWORD                                         f_dwFlags,
    __deref_out_ecount( *f_pcbPDResultMessage )                       DRM_BYTE                                        **f_ppbPDResultMessage,
    __out                                                           DRM_DWORD                                        *f_pcbPDResultMessage );

DRM_API DRM_RESULT DRM_CALL Drm_Prnd_Transmitter_ProximityDetectionStart_Process(
    __in                                                              DRM_APP_CONTEXT                                  *f_poAppContext,
    __in_bcount( f_cbPDStartMessage )                           const DRM_BYTE                                         *f_pbPDStartMessage,
    __in                                                              DRM_DWORD                                         f_cbPDStartMessage,
    __in                                                              DRM_DWORD                                         f_dwFlags,
    __deref_out_ecount( *f_pcbPDChlgMessage )                         DRM_BYTE                                        **f_ppbPDChlgMessage,
    __out                                                             DRM_DWORD                                        *f_pcbPDChlgMessage,
    __out                                                             DRM_DWORD                                        *f_pdwFlags );

DRM_API DRM_RESULT DRM_CALL Drm_Prnd_Transmitter_ProximityDetectionResponse_Process(
    __in                                                              DRM_APP_CONTEXT                                  *f_poAppContext,
    __in_bcount( f_cbPDRespMessage )                            const DRM_BYTE                                         *f_pbPDRespMessage,
    __in                                                              DRM_DWORD                                         f_cbPDRespMessage,
    __in                                                              DRM_DWORD                                         f_dwFlags,
    __deref_out_ecount( *f_pcbPDResultMessage )                       DRM_BYTE                                        **f_ppbPDResultMessage,
    __out                                                             DRM_DWORD                                        *f_pcbPDResultMessage,
    __out                                                             DRM_DWORD                                        *f_pdwFlags );

DRM_API DRM_RESULT DRM_CALL Drm_Prnd_Transmitter_LicenseRequest_Process(
    __in                                                              DRM_APP_CONTEXT                                  *f_poAppContext,
    __in_bcount( f_cbLicReqMessage )                            const DRM_BYTE                                         *f_pbLicReqMessage,
    __in                                                              DRM_DWORD                                         f_cbLicReqMessage,
    __in_opt                                                          Drm_Prnd_Data_Callback                            f_pfnDataCallback,
    __inout_ecount_opt( 1 )                                           DRM_VOID                                         *f_pvDataCallbackContext,
    __in_opt                                                          Drm_Prnd_Content_Identifier_Callback              f_pfnContentIdentifierCallback,
    __inout_ecount_opt( 1 )                                           DRM_VOID                                         *f_pvContentIdentifierCallbackContext,
    __out                                                             DRM_DWORD                                        *f_pdwFlags );

DRM_API DRM_RESULT DRM_CALL Drm_Prnd_Transmitter_LicenseTransmit_Generate(
    __in                                                              DRM_APP_CONTEXT                                  *f_poAppContext,
    __in_opt                                                    const DRM_ID                                           *f_pCustomDataTypeID,
    __in_bcount_opt( f_cbCustomData )                           const DRM_BYTE                                         *f_pbCustomData,
    __in                                                              DRM_DWORD                                         f_cbCustomData,
    __in                                                              DRM_DWORD                                         f_dwFlags,
    __deref_out_ecount( *f_pcbLicTransmitMessage )                    DRM_BYTE                                        **f_ppbLicTransmitMessage,
    __out                                                             DRM_DWORD                                        *f_pcbLicTransmitMessage );

DRM_API DRM_RESULT DRM_CALL Drm_Prnd_Transmitter_LicenseError_Generate(
    __in_opt                                                          DRM_APP_CONTEXT                                  *f_poAppContext,
    __in_opt                                                    const DRM_ID                                           *f_pSessionID,
    __in                                                              DRM_RESULT                                        f_drResult,
    __in                                                              DRM_DWORD                                         f_dwFlags,
    __deref_out_ecount( *f_pcbErrMessage )                            DRM_BYTE                                        **f_ppbErrMessage,
    __out                                                             DRM_DWORD                                        *f_pcbErrMessage );

DRM_API DRM_RESULT DRM_CALL Drm_Prnd_Transmitter_EndSession(
    __in                                                              DRM_APP_CONTEXT                                  *f_poAppContext );

DRM_API DRM_RESULT DRM_CALL Drm_Prnd_Transmitter_PrepareLicensesForTransmit(
    __in                                                              DRM_APP_CONTEXT                                  *f_poAppContext );

DRM_API DRM_RESULT DRM_CALL Drm_Prnd_Transmitter_IsSessionStillValid(
    __in                                                              DRM_APP_CONTEXT                                  *f_poAppContext,
    __out                                                             DRM_BOOL                                         *f_pfSessionStillValid );

/*
** ---------------------------------------
** Prnd API functions: Receiver
** ---------------------------------------
*/
DRM_API DRM_RESULT DRM_CALL Drm_Prnd_Receiver_BeginSession(
    __in                                                              DRM_APP_CONTEXT                                  *f_poAppContext,
    __in                                                              DRM_PRND_RECEIVER_CONTEXT                        *f_poNewPrndReceiverContext );

DRM_API DRM_RESULT DRM_CALL Drm_Prnd_Receiver_RegistrationRequest_Generate(
    __in                                                              DRM_APP_CONTEXT                                  *f_poAppContext,
    __in_opt                                                    const DRM_ID                                           *f_pPreviousSessionID,
    __in_opt                                                    const DRM_ID                                           *f_pCustomDataTypeID,
    __in_bcount_opt( f_cbCustomData )                           const DRM_BYTE                                         *f_pbCustomData,
    __in                                                              DRM_DWORD                                         f_cbCustomData,
    __in                                                              DRM_DWORD                                         f_dwFlags,
    __deref_out_ecount( *f_pcbReqMessage )                            DRM_BYTE                                        **f_ppbReqMessage,
    __out                                                             DRM_DWORD                                        *f_pcbReqMessage );

DRM_API DRM_RESULT DRM_CALL Drm_Prnd_Receiver_RegistrationResponse_Process(
    __in                                                              DRM_APP_CONTEXT                                  *f_poAppContext,
    __inout_bcount( f_cbRespMessage )                           const DRM_BYTE                                         *f_pbRespMessage,
    __in                                                              DRM_DWORD                                         f_cbRespMessage,
    __in_opt                                                          Drm_Prnd_Data_Callback                            f_pfnDataCallback,
    __inout_ecount_opt( 1 )                                           DRM_VOID                                         *f_pvDataCallbackContext,
    __out_ecount( 1 )                                                 DRM_ID                                           *f_pSessionID,
    __out                                                             DRM_PRND_PROXIMITY_DETECTION_TYPE                *f_peProximityDetectionType,
    __deref_out_ecount( *f_pcbTransmitterProximityDetectionChannel )  DRM_BYTE                                        **f_ppbTransmitterProximityDetectionChannel,
    __out                                                             DRM_DWORD                                        *f_pcbTransmitterProximityDetectionChannel,
    __out                                                             DRM_DWORD                                        *f_pdwFlags );

DRM_API DRM_RESULT DRM_CALL Drm_Prnd_Receiver_RegistrationError_Process(
    __in                                                              DRM_APP_CONTEXT                                  *f_poAppContext,
    __in_bcount( f_cbErrMessage )                               const DRM_BYTE                                         *f_pbErrMessage,
    __in                                                              DRM_DWORD                                         f_cbErrMessage,
    __out                                                             DRM_RESULT                                       *f_pdrResult,
    __out                                                             DRM_DWORD                                        *f_pdwFlags );

DRM_API DRM_RESULT DRM_CALL Drm_Prnd_Receiver_ProximityDetectionStart_Generate(
    __in                                                              DRM_APP_CONTEXT                                  *f_poAppContext,
    __in                                                              DRM_DWORD                                         f_dwFlags,
    __deref_out_ecount( *f_pcbPDStartMessage )                        DRM_BYTE                                        **f_ppbPDStartMessage,
    __out                                                             DRM_DWORD                                        *f_pcbPDStartMessage );

DRM_API DRM_RESULT DRM_CALL Drm_Prnd_Receiver_ProximityDetectionChallenge_Process(
    __in                                                              DRM_APP_CONTEXT                                  *f_poAppContext,
    __in_bcount( f_cbPDChlgMessage )                            const DRM_BYTE                                         *f_pbPDChlgMessage,
    __in                                                              DRM_DWORD                                         f_cbPDChlgMessage,
    __in                                                              DRM_DWORD                                         f_dwFlags,
    __deref_out_ecount( *f_pcbPDRespMessage )                         DRM_BYTE                                        **f_ppbPDRespMessage,
    __out                                                             DRM_DWORD                                        *f_pcbPDRespMessage,
    __out                                                             DRM_DWORD                                        *f_pdwFlags );

DRM_API DRM_RESULT DRM_CALL Drm_Prnd_Receiver_ProximityDetectionResult_Process(
    __in                                                              DRM_APP_CONTEXT                                  *f_poAppContext,
    __in_bcount( f_cbPDResultMessage )                          const DRM_BYTE                                         *f_pbPDResultMessage,
    __in                                                              DRM_DWORD                                         f_cbPDResultMessage,
    __out                                                             DRM_RESULT                                       *f_pdrPDResult,
    __out                                                             DRM_DWORD                                        *f_pdwFlags );

DRM_API DRM_RESULT DRM_CALL Drm_Prnd_Receiver_LicenseRequest_Generate(
    __in                                                              DRM_APP_CONTEXT                                  *f_poAppContext,
    __in                                                        const DRM_GUID                                         *f_pguidRequestedAction,
    __in_opt                                                    const DRM_GUID                                         *f_pguidRequestedActionQualifier,
    __in                                                              DRM_PRND_CONTENT_IDENTIFIER_TYPE                  f_eContentIdentifierType,
    __in_bcount( f_cbContentIdentifier )                        const DRM_BYTE                                         *f_pbContentIdentifier,
    __in                                                              DRM_DWORD                                         f_cbContentIdentifier,
    __in_opt                                                    const DRM_ID                                           *f_pCustomDataTypeID,
    __in_bcount_opt( f_cbCustomData )                           const DRM_BYTE                                         *f_pbCustomData,
    __in                                                              DRM_DWORD                                         f_cbCustomData,
    __in                                                              DRM_DWORD                                         f_dwFlags,
    __deref_out_ecount( *f_pcbLicReqMessage )                         DRM_BYTE                                        **f_ppbLicReqMessage,
    __out                                                             DRM_DWORD                                        *f_pcbLicReqMessage );

DRM_API DRM_RESULT DRM_CALL Drm_Prnd_Receiver_LicenseTransmit_Process(
    __in                                                              DRM_APP_CONTEXT                                  *f_poAppContext,
    __in_bcount( f_cbLicTransmitMessage )                       const DRM_BYTE                                         *f_pbLicTransmitMessage,
    __in                                                              DRM_DWORD                                         f_cbLicTransmitMessage,
    __in_opt                                                          Drm_Prnd_Data_Callback                            f_pfnDataCallback,
    __inout_ecount_opt( 1 )                                           DRM_VOID                                         *f_pvDataCallbackContext,
    __out                                                             DRM_DWORD                                        *f_pdwFlags );

DRM_API DRM_RESULT DRM_CALL Drm_Prnd_Receiver_LicenseError_Process(
    __in                                                              DRM_APP_CONTEXT                                  *f_poAppContext,
    __in_bcount( f_cbErrMessage )                               const DRM_BYTE                                         *f_pbErrMessage,
    __in                                                              DRM_DWORD                                         f_cbErrMessage,
    __out                                                             DRM_RESULT                                       *f_pdrResult,
    __out                                                             DRM_DWORD                                        *f_pdwFlags );

DRM_API DRM_RESULT DRM_CALL Drm_Prnd_Receiver_EndSession(
    __in                                                              DRM_APP_CONTEXT                                  *f_poAppContext );

/*
** ---------------------------------------
** Local License Generation API functions
** ---------------------------------------
*/
DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL Drm_LocalLicense_InitializePolicyDescriptor(
    __inout                             DRM_LOCAL_LICENSE_POLICY_DESCRIPTOR *f_poDescriptor ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL Drm_LocalLicense_CreateLicense(
    __inout                               DRM_APP_CONTEXT                     *f_poAppContext,
    __in                            const DRM_LOCAL_LICENSE_POLICY_DESCRIPTOR *f_poDescriptor,
    __in                            const DRM_LOCAL_LICENSE_TYPE               f_eLicensType,
    __in                            const DRM_KID                             *f_pKeyId,
    __in_opt                        const DRM_DWORD                            f_cbRemoteCert,
    __in_ecount_opt(f_cbRemoteCert) const DRM_BYTE                            *f_pbRemoteCert,
    __in_opt                        const DRM_LICENSE_HANDLE                   f_hRootLicense,
    __out                                 DRM_LICENSE_HANDLE                  *f_phLicense ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL Drm_LocalLicense_CreatePlayReadyObject(
    __in_opt                      const DRM_LICENSE_HANDLE                   f_hLicense,
    __in_opt                      const DRM_DWORD                            f_cbRMHeader,
    __in_opt                      const DRM_BYTE                            *f_pbRMHeader,
    __out                               DRM_DWORD                           *f_pcbPROBlob,
    __out_bcount( *f_pcbPROBlob )       DRM_BYTE                           **f_ppbPROBlob ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL Drm_LocalLicense_CreateRMHeader(
    __in_opt                      const DRM_KID                             *f_pKeyId,
    __out                               DRM_DWORD                           *f_pcbRMHeader,
    __out_bcount( *f_pcbRMHeader )      DRM_BYTE                           **f_ppbRMHeader ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL Drm_LocalLicense_StoreLicense(
    __in                          const DRM_LICENSE_HANDLE                   f_hLicense,
    __in                          const DRM_LOCAL_LICENSE_STORE              f_eLicenseStore ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL Drm_LocalLicense_EncryptSample(
    __in                          const DRM_LICENSE_HANDLE                   f_hLicense,
    __in                          const DRM_DWORD                            f_cSubsamples,
    __in_ecount( f_cSubsamples )  const DRM_DWORD                           *f_pcbSubamples,
    __inout_ecount( f_cSubsamples )     DRM_BYTE                           **f_ppbSubamples,
    __out                               DRM_UINT64                          *f_pqwIV ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL Drm_LocalLicense_EncryptOpaqueSample(
    __in                          const DRM_LICENSE_HANDLE               f_hLicense,
    __out_ecount_opt(1)                 OEM_HAL_SAMPLE_METADATA         *f_pMetadata,
    __in                                OEM_OPAQUE_BUFFER_HANDLE         f_hInBuf,
    __in                                OEM_OPAQUE_BUFFER_HANDLE         f_hOutBuf,
    __in                                DRM_DWORD                        f_cbData,
    __out                               DRM_UINT64                      *f_pqwIV ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL Drm_LocalLicense_GetKID(
    __in                          const DRM_LICENSE_HANDLE                   f_hLicense,
    __out                               DRM_KID                             *f_pKeyID ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL Drm_LocalLicense_GetXMRLicense(
    __in                          const DRM_LICENSE_HANDLE                   f_hLicense,
    __out                               DRM_DWORD                           *f_pcbXMRLicense,
    __out                               DRM_BYTE                           **f_ppbXMRLicense ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL Drm_LocalLicense_AddRef (
    __inout                             DRM_LICENSE_HANDLE                   f_hLicense ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL Drm_LocalLicense_Release(
    __inout                             DRM_LICENSE_HANDLE                  *f_phLicense ) DRM_NO_INLINE_ATTRIBUTE;

/*
** ---------------------------------------
** MPEG2 Transport Stream Encryptor API functions
** ---------------------------------------
*/
DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL Drm_M2ts_Initialize(
    __in                              const DRM_DWORD                        f_cbMaxHeapAllowed,
    __out                                   DRM_M2TS_ENCRYPTOR_HANDLE       *f_phEncryptor ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL Drm_M2ts_Uninitialize(
    __in                                    DRM_M2TS_ENCRYPTOR_HANDLE        f_hEncryptor ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL Drm_M2ts_SetEncryptionProperty(
        __in                                DRM_M2TS_ENCRYPTOR_HANDLE        f_hEncryptor,
        __in                          const DRM_M2TS_ENCRYPTION_PROPERTY    *f_poProperty ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL Drm_M2ts_SetKeyData(
    __in                                    DRM_M2TS_ENCRYPTOR_HANDLE        f_hEncryptor,
    __in                                    DRM_LICENSE_HANDLE               f_hLicense,
    __in                              const DRM_GUID                        *f_poKeyId,
    __in                              const DRM_M2TS_PRO_TYPE                f_ePROType,
    __in                              const DRM_DWORD                        f_dwDuration ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL Drm_M2ts_Encrypt(
    __in                                    DRM_M2TS_ENCRYPTOR_HANDLE        f_hEncryptor,
    __in_bcount_opt( f_cbDataIn )     const DRM_BYTE                        *f_pbDataIn,
    __in                              const DRM_DWORD                        f_cbDataIn,
    __out_bcount( *f_pcbDataOut )           DRM_BYTE                        *f_pbDataOut,
    __inout                                 DRM_DWORD                       *f_pcbDataOut,
    __in                              const DRM_BOOL                         f_fLastTSPackets ) DRM_NO_INLINE_ATTRIBUTE;

/*
** ---------------------------------------
** Activation API functions
** ---------------------------------------
*/
DRM_API DRM_RESULT DRM_CALL Drm_Activation_ProcessResponseGenerateChallenge(
    __inout_bcount( ACTIVATION_CONTEXT_SIZE )  DRM_BYTE        *f_pbActivationCtx,
    __in_bcount_opt( f_cbResponse )            DRM_BYTE        *f_pbResponse,
    __in_opt                                   DRM_DWORD        f_cbResponse,
    __out_bcount_opt( *f_pcbChallenge )        DRM_BYTE        *f_pbChallenge,
    __inout                                    DRM_DWORD       *f_pcbChallenge,
    __out_ecount_opt( *f_pcchUrl )             DRM_CHAR        *f_pszUrl,
    __inout                                    DRM_DWORD       *f_pcchUrl,
    __out                                      DRM_RESULT      *f_pResult );

DRM_API DRM_RESULT DRM_CALL Drm_GetContextSizes(
    __out     DRM_DWORD *f_pdwAppContextSize,
    __out     DRM_DWORD *f_pdwOpaqueBufferSize,
    __out     DRM_DWORD *f_pdwDecryptContextSize,
    __out_opt DRM_DWORD *f_pdwTransmitterContextSize,
    __out_opt DRM_DWORD *f_pdwReceiverContextSize );

DRM_API DRM_RESULT DRM_CALL Drm_Reader_CloneDecryptContext(
    __inout_ecount(1)  DRM_DECRYPT_CONTEXT *f_pDecryptContextIn,
    __out_ecount(1)    DRM_DECRYPT_CONTEXT *f_pDecryptContextOut );

/*
** ---------------------------------------
** Policy State API functions
** ---------------------------------------
*/
DRM_API DRM_RESULT DRM_CALL Drm_Policy_GetStateData(
    __in    DRM_APP_CONTEXT         *f_poAppContext,
    __in    const DRM_CONST_STRING  *f_pdstrKID,
    __in    const DRM_CONST_STRING  *f_pdstrStateName,
    __out_bcount_opt( *f_pcbStateData )
            DRM_BYTE                *f_pbStateData,
    __inout DRM_DWORD               *f_pcbStateData );

DRM_API DRM_RESULT DRM_CALL Drm_Policy_SetStateData(
    __in    DRM_APP_CONTEXT         *f_poAppContext,
    __in    const DRM_CONST_STRING  *f_pdstrKID,
    __in    const DRM_CONST_STRING  *f_pdstrStateName,
    __in_bcount( f_cbStateData )
            DRM_BYTE                *f_pbStateData,
    __inout DRM_DWORD                f_cbStateData );

// Cleaning up PlayReady macros and adding missing definitions, to build NRD ref app -- vspector
//#ifndef DRM_INTERNAL_USE
//#undef min
//#undef max
//#endif

#ifdef PLAYREADY2TEE
/*
** ---------------------------------------
** Secure Stop functions
** ---------------------------------------
*/
DRM_API DRM_RESULT DRM_CALL Drm_Reader_Unbind(
                                    DRM_APP_CONTEXT      *f_poAppContext,
                                    DRM_DECRYPT_CONTEXT  *f_pcontextDCRY );

DRM_API DRM_BOOL DRM_CALL Drm_SupportSecureStop( DRM_VOID );

DRM_API DRM_RESULT DRM_CALL Drm_TurnSecureStop( DRM_BOOL f_OnOff );

DRM_API DRM_RESULT DRM_CALL Drm_GetSecureStopIds(
                                    DRM_APP_CONTEXT *f_poAppContext,   /* application context */
    __out                           DRM_BYTE         f_pbSessionIDs[TEE_MAX_NUM_SECURE_STOPS][TEE_SESSION_ID_LEN],    /* sessionID, expected length 16 */
    __out                           DRM_DWORD       *f_count            /* number of returned secure stop IDs */
    );

DRM_API DRM_RESULT DRM_CALL Drm_GetSecureStop(
                                    DRM_APP_CONTEXT *f_poAppContext,   /* application context */
    __in_bcount( 16 )               DRM_BYTE        *f_pbSessionID,    /* sessionID, expected length 16 */
    __out_bcount ( f_cbSecureStop ) DRM_BYTE        *f_pbSecureStop,   /* secure stop buffer */
    __inout                         DRM_WORD        *f_cbSecureStop    /* secure stop data length */
    );

DRM_API DRM_RESULT DRM_CALL Drm_CommitSecureStop(
                                    DRM_APP_CONTEXT *f_poAppContext,   /* application context */
    __in_bcount( 16 )               DRM_BYTE        *f_pbSessionID     /* sessionID, expected length 16 */
    );

DRM_API DRM_RESULT DRM_CALL Drm_ResetSecureStops(
                                    DRM_APP_CONTEXT *f_poAppContext,  /* application context */
    __out                           DRM_WORD        *f_count          /* number of deleted secure stops */
    );
#endif // ifdef TEE

/*
** ---------------------------------------
** State Cleanup functions
** ---------------------------------------
*/
DRM_API DRM_RESULT DRM_CALL Drm_DeleteSecureStore( __in const DRM_CONST_STRING *f_pdstrDeviceStoreName );

DRM_API DRM_RESULT DRM_CALL Drm_GetSecureStoreHash(
    __in const DRM_CONST_STRING *f_pdstrDeviceStoreName,
    __out_bcount( SHA256_DIGEST_SIZE_IN_BYTES ) DRM_BYTE *f_pbSecureStoreHash );

DRM_API DRM_RESULT DRM_CALL Drm_DeleteKeyStore( DRM_VOID );

DRM_API DRM_RESULT DRM_CALL Drm_GetKeyStoreHash(
    __out_bcount( SHA256_DIGEST_SIZE_IN_BYTES ) DRM_BYTE *f_pbKeyFileHash );

EXIT_PK_NAMESPACE;

#endif /* __DRMMANAGER_H__ */

