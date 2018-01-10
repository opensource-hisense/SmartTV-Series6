/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRMPLAYREADYOBJ_H__
#define __DRMPLAYREADYOBJ_H__

#include <oemcipher.h>
#include <drmembeddedstore_impl.h>
#include <drmheaderparser.h>

ENTER_PK_NAMESPACE;

#define DRM_MAX_HEADERDATASIZE        ( 5 * 1024 )                         /* 5K of header data  */

/*
** PlayReady Data Header Format
**
** Field         | Type
** -----------------------------
** Data Size     | DWORD
** Record Count  | WORD
*/
#define SIZE_OF_DRM_PLAYREADY_DATA_HEADER   ( SIZEOF( DRM_DWORD ) + SIZEOF( DRM_WORD ) )

/*
** PlayReady Record Header Format
**
** Field         | Type
** -----------------------------
** Record Type   | WORD
** Record Size   | WORD
*/
#define SIZE_OF_DRM_PLAYREADY_RECORD_HEADER ( 2 * SIZEOF( DRM_WORD ) )
#define SIZE_OF_PLAYREADY_EMBEDDED_LICENSE_SPACE (1024*10)

/*
** Contains space for the PlayReady Object header, two record headers,
** WMDRM header data, and the embedded license store.
*/
#define DRM_STANDARD_PLAYREADYOBJSIZE         ( SIZE_OF_DRM_PLAYREADY_DATA_HEADER + \
                                              2 * SIZE_OF_DRM_PLAYREADY_RECORD_HEADER + \
                                              DRM_MAX_HEADERDATASIZE + \
                                              MAX_EMBEDDED_STORE_LEN  )

typedef enum
{
    PLAYREADY_WRMHEADER              = 0x0001,
    PLAYREADY_V4_SIGNATURE           = 0x0002,
    PLAYREADY_EMBEDDED_LICENSE_STORE = 0x0003
} eDRMPlayReady_RECORD_TYPES;

#define RECORD_TYPE_TO_BIT( eRecordType )                   ( 1 << ( ( (DRM_DWORD)(eRecordType) ) - 1 ) )
#define IS_RECORD_TYPE_BIT_SET( eBitMask, eRecordType )     ( ( (eBitMask) & RECORD_TYPE_TO_BIT(eRecordType) ) != 0 )

typedef enum
{
    DRM_DECRYPTORSETUP_INVALID     = 0,
    DRM_DECRYPTORSETUP_ONDEMAND    = 1,
    DRM_DECRYPTORSETUP_MAX_DEFINED = 1,
} eDRM_DECRYPTORSETUP_TYPE;

DRM_API DRM_RESULT DRM_CALL DRM_PRO_GetRMHeaderVersion(
    __in_bcount( f_cbHeader ) const DRM_BYTE            *f_pbHeader,
    __in                      const DRM_DWORD            f_cbHeader,
    __out_ecount( 1 )               eDRM_HEADER_VERSION *f_peVersion );

DRM_API DRM_RESULT DRM_CALL DRM_PRO_IsValidObject(
    __in_bcount( f_cbBuffer ) const DRM_BYTE  *f_pbBuffer,
    __in                      const DRM_DWORD  f_cbBuffer,
    __out_opt                       DRM_DWORD *f_pdwRecordTypeBitMask );

DRM_API DRM_RESULT DRM_CALL DRM_PRO_GetRecord(
    __in_bcount( f_cbBuffer )                const DRM_BYTE   *f_pbBuffer,
    __in                                     const DRM_DWORD   f_cbBuffer,
    __in                                           DRM_WORD    f_wRecordType,
    __deref_out_bcount(*f_pcbEmbeddedRecord)       DRM_BYTE  **f_ppbEmbeddedRecord,
    __out                                          DRM_DWORD  *f_pcbEmbeddedRecord );

DRM_API DRM_RESULT DRM_CALL DRM_PRO_Create(
    __in_opt                                  DRM_CONST_STRING           *f_pdstrPlayReadyHeader,
    __out_bcount_opt( *f_pcbPlayReadyObject ) DRM_BYTE                   *f_pbPlayReadyObject,
    __inout                                   DRM_DWORD                  *f_pcbPlayReadyObject,
    __in                                      DRM_DWORD                   f_cbEmbeddedStore );

DRM_API DRM_RESULT DRM_CALL DRM_PRO_GetCipherTypeFromPlayReadyHeader(
    __in_bcount( f_cbPlayReadyHeader ) DRM_BYTE                 *f_pbPlayReadyHeader,
    __in                               DRM_DWORD                 f_cbPlayReadyHeader,
    __out                              DRM_SUPPORTED_CIPHERS    *f_peCipherType );

DRM_API DRM_RESULT DRM_CALL DRM_PRO_GetCipherType(
    __in_bcount( f_cbPlayReadyObject ) const DRM_BYTE                 *f_pbPlayReadyObject,
    __in                                     DRM_DWORD                 f_cbPlayReadyObject,
    __out                                    DRM_SUPPORTED_CIPHERS    *f_peCipherType );

DRM_API DRM_RESULT DRM_CALL DRM_PRO_GetDecryptorSetupTypeFromPlayReadyHeader(
    __in_ecount( f_cbPlayReadyHeader ) DRM_BYTE                 *f_pbPlayReadyHeader,
    __in                               DRM_DWORD                 f_cbPlayReadyHeader,
    __out_ecount( 1 )                  eDRM_DECRYPTORSETUP_TYPE *f_peDecryptorSetupType );

DRM_API DRM_RESULT DRM_CALL DRM_PRO_GetDecryptorSetupType(
    __in_ecount( f_cbPlayReadyObject ) const DRM_BYTE                 *f_pbPlayReadyObject,
    __in                                     DRM_DWORD                 f_cbPlayReadyObject,
    __out_ecount( 1 )                        eDRM_DECRYPTORSETUP_TYPE *f_peDecryptorSetupType );

DRM_API DRM_RESULT DRM_CALL DRM_PRO_CalculateRMHeaderChecksum(
    __in                                const DRM_SUPPORTED_CIPHERS             f_eCipherType,
    __in_bcount( f_cbContentKey )       const DRM_BYTE                         *f_pbContentKey,
    __in                                const DRM_DWORD                         f_cbContentKey,
    __in_ecount_opt( 1 )                const DRM_KID                          *f_pKID,
    __inout_bcount_opt( *f_pcbChecksum )      DRM_BYTE                         *f_pbChecksum,
    __in                                      DRM_DWORD                        *f_pcbChecksum );

DRM_API DRM_RESULT DRM_CALL DRM_PRO_CreateRMHeader(
    __in                                const eDRM_HEADER_VERSION    f_eWRMHeaderVersion,
    __in                                const DRM_SUPPORTED_CIPHERS  f_eCipherType,
    __in_ecount_nz( 1 )                 const DRM_CONST_STRING      *f_pdstrKID,
    __in_ecount_nz_opt( 1 )             const DRM_CONST_STRING      *f_pdstrCheckSum,
    __in_ecount_nz_opt( 1 )             const DRM_CONST_STRING      *f_pdstrPlayReadySilentURL,
    __in_ecount_nz_opt( 1 )             const DRM_CONST_STRING      *f_pdstrPlayReadyNonSilentURL,
    __in_ecount_nz_opt( 1 )             const DRM_CONST_STRING      *f_pdstrServiceID,
    __in_ecount_nz_opt( 1 )             const DRM_CONST_STRING      *f_pdstrCustomAttributesXML,
    __in_ecount_nz_opt( 1 )             const DRM_CONST_STRING      *f_pdstrDecryptorSetup,
    __inout_bcount_opt( *f_pcbRightsManagementHeader )
                                              DRM_BYTE              *f_pbRightsManagementHeader,
    __in                                      DRM_DWORD             *f_pcbRightsManagementHeader );

DRM_API DRM_RESULT DRM_CALL DRM_PRO_ConvertHeaderFromWmdrmToPlayReady(
    __in_bcount( f_cbWmdrmHeader )      const DRM_BYTE  *f_pbWmdrmHeader,
    __in                                const DRM_DWORD  f_cbWmdrmHeader,
    __in_ecount_nz_opt( f_cchPlayReadySilentURL )
                                        const DRM_WCHAR *f_pwchPlayReadySilentURL,
    __in                                const DRM_DWORD  f_cchPlayReadySilentURL,
    __in_ecount_nz_opt( f_cchPlayReadyNonSilentURL )
                                        const DRM_WCHAR *f_pwchPlayReadyNonSilentURL,
    __in                                const DRM_DWORD  f_cchPlayReadyNonSilentURL,
    __in_ecount_nz_opt( f_cchServiceID )
                                        const DRM_WCHAR *f_pwchServiceID,
    __in                                const DRM_DWORD  f_cchServiceID,
    __in_ecount_nz_opt( f_cchCustomAttributes )
                                        const DRM_WCHAR *f_pwchCustomAttributes,
    __in                                const DRM_DWORD  f_cchCustomAttributes,
    __inout_bcount_opt( *f_pcbPlayReadyHeader )
                                              DRM_BYTE  *f_pbPlayReadyHeader,
    __in                                      DRM_DWORD *f_pcbPlayReadyHeader );

EXIT_PK_NAMESPACE;

#endif /* __DRMPLAYREADYOBJ_H__ */

