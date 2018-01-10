/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __OEMCOMMON_H__
#define __OEMCOMMON_H__

#include <oemshahash.h>
#include <oempkcrypto.h>
#include <oemcommonmem.h>
#include <drmbase64.h>

#if defined(__cplusplus) && USE_CLAW

#include <clawrt/rt.h>

#else /* defined(__cplusplus) && USE_CLAW */

#define CLAW_AUTO_RANDOM_CIPHER
#define CLAW_ATTRIBUTE_NOINLINE

#endif /* defined(__cplusplus) && USE_CLAW */


ENTER_PK_NAMESPACE;

extern DRM_EXPORT_VAR DRM_CONST_STRING g_dstrDrmPath;
extern DRM_EXPORT_VAR DRM_CONST_STRING g_dstrDrmDataPath;
extern DRM_EXPORT_VAR DRM_CONST_STRING g_dstrDrmAssetPath;
extern const DRM_EXPORT_VAR DRM_CHAR   g_chPathSeparator;
extern const DRM_EXPORT_VAR DRM_WCHAR  g_wchPathSeparator;

#if DRM_BUILD_PROFILE != DRM_BUILD_PROFILE_WM7
extern const DRM_CONST_STRING g_dstrPrivKey;
#endif /* !DRM_BUILD_PROFILE_WM7 */

/* Session Expiration Timeout Config Values */
#define Oem_Config_SETimeout_Key     "SessionExpirationTimeout"
/*
** SIZEOF(static string) includes null terminating byte
** which we don't want since we are going to append it with session id
*/
#define Oem_Config_SETimeout_Key_LEN ( SIZEOF( Oem_Config_SETimeout_Key ) - 1 )

/* Revocation List Timeout Config Values */
#define Oem_Config_RLTimeout_Key     "RevocationListTimeout"
/*
** SIZEOF(static string) includes null terminating byte
** which we don't want since we are going to append it with session id
*/
#define Oem_Config_RLTimeout_Key_LEN ( SIZEOF( Oem_Config_RLTimeout_Key ) - 1 )

#define Oem_Config_NoTxAuth_Key      "NoTxAuth"
/*
** SIZEOF(static string) includes null terminating byte
** which we don't want since we are going to append it with session id
*/
#define Oem_Config_NoTxAuth_Key_LEN ( SIZEOF( Oem_Config_NoTxAuth_Key ) - 1 )

typedef enum DRMFILESPATH
{
    CERTPATH = 0,
    CERTTEMPLATEPATH,
    HDSPATH,
    KEYFILEPATH
} DRMFILESPATH;

typedef enum _DRM_DEVICE_CERT_SOURCE
{
    DRM_DCT_SOURCE_FILE = 1,
    DRM_DCT_SOURCE_DLL_RESOURCE,
} DRM_DEVICE_CERT_SOURCE;

typedef enum _DRM_DEVICE_CERT_TYPE
{
    DRM_DCT_WMDRMPD = 1,
    DRM_DCT_WMDRMPD_TEMPLATE,
    DRM_DCT_PLAYREADY,
    DRM_DCT_PLAYREADY_TEMPLATE,
    DRM_DCT_NETRECEIVER,
    DRM_DCT_NETRECEIVER_TEMPLATE,
} DRM_DEVICE_CERT_TYPE;

typedef enum _DRM_DEVICE_KEY_TYPE
{
    DRM_DKT_INVALID=0,
    DRM_DKT_WMDRMPD_GROUP = 1,
    DRM_DKT_WMDRMPD_FALLBACK,
    DRM_DKT_PLAYREADY_DEVICE_SIGN,
    DRM_DKT_PLAYREADY_DEVICE_ENCRYPT,
    DRM_DKT_PLAYREADY_MODEL,
    DRM_DKT_PLAYREADY_NDR,
    DRM_DKT_PLAYREADY_NDR_MODEL,
    DRM_DKT_WMDRMPD_DEVICE,
    DRM_DKT_SECURE_STORE,
    DRM_DKT_PLAYREADY_DEVICE_PRND_ENCRYPT,
} DRM_DEVICE_KEY_TYPE;

typedef enum _DRM_DEVICE_ID_TYPE
{
    DRM_DIT_WMDRMPD_ID = 1,
    DRM_DIT_PLAYREADY_ID,
} DRM_DEVICE_ID_TYPE;

typedef DRM_VOID * OEM_DEVICE_HANDLE;

#ifdef PLAYREADY2TEE
DRM_API DRM_RESULT DRM_CALL Oem_ReadTeeState(
    DRM_BYTE * const buf,
    DRM_DWORD * len);

DRM_API DRM_RESULT DRM_CALL Oem_WriteTeeState(
    DRM_BYTE * const buf,
    const DRM_DWORD len);
#endif

/*
** Internal functions that should be implemented by each OEM
** implementation (oeminfo*.c).
*/
#if DRM_SUPPORT_EMBEDDED_CERTS
/* There is no need to implement these two functions unless DRM_SUPPORT_EMBEDDED_CERTS is set to 1. */
DRM_API DRM_RESULT DRM_CALL _GetDeviceCertSource(
    __in const DRM_DEVICE_CERT_TYPE    f_eCertType,
    __out      DRM_DEVICE_CERT_SOURCE *f_peCertSource );

DRM_API DRM_RESULT DRM_CALL _ReadFromResource(
    __in                       const  DRM_DEVICE_CERT_TYPE  f_eCertType,
    __out_bcount_opt( *f_pcbDevCert ) DRM_BYTE             *f_pbDevCert,
    __inout                           DRM_DWORD            *f_pcbDevCert );
#endif /* DRM_SUPPORT_EMBEDDED_CERTS */

/*
** OEM_MANDATORY:
** For all devices, this function MUST be implemented by the OEM.
*/
DRM_API DRM_RESULT DRM_CALL _GetDRMFullPathName(
    __out DRM_WCHAR **f_ppwszFullPath,
    __in_opt const DRM_CONST_STRING *f_pdstrFilename,
    __in DRMFILESPATH f_eFilesPath );

/*
** OEM_MANDATORY:
** If the device supports Device Assets (DRM_SUPPORT_DEVICEASSETS=1), this function MUST be implemented by the OEM.
*/
DRM_RESULT _GetPrivateKey(
    __in_opt DRM_VOID *f_pOEMContext,
    __in const DRM_BOOL f_fGCprivkey,
    __out_bcount( f_cbPrivKey ) DRM_BYTE *f_pbPrivkey,
    __in DRM_DWORD f_cbPrivKey );

/*
** OEM_MANDATORY:
** If the device supports Device Assets (DRM_SUPPORT_DEVICEASSETS=1), this function MUST be implemented by the OEM.
*/
DRM_RESULT _GetHWID(
    __out_bcount(DRM_SHA1_DIGEST_LEN) DRM_BYTE *shaOut );

/*
** OEM_MANDATORY:
** If the device supports Device Assets (DRM_SUPPORT_DEVICEASSETS=1), this function MUST be implemented by the OEM.
*/
DRM_API DRM_RESULT DRM_CALL Oem_Device_GetCert(
    __in_opt DRM_VOID *f_pOEMContext,
    __in const DRM_DEVICE_CERT_TYPE f_eCertType,
    __out_bcount_opt( *f_pcbDevCert ) DRM_BYTE *f_pbDevCert,
    __inout DRM_DWORD *f_pcbDevCert );

/*
** OEM_MANDATORY:
** If the device supports Device Assets (DRM_SUPPORT_DEVICEASSETS=1), this function MUST be implemented by the OEM.
*/
DRM_API DRM_RESULT DRM_CALL Oem_Device_SetCert(
    __in_opt DRM_VOID *f_pOEMContext,
    __in const DRM_DEVICE_CERT_TYPE f_eCertType,
    __in_bcount(f_cbDevCert) DRM_BYTE *f_pbDevCert,
    __in const DRM_DWORD f_cbDevCert );

/*
** OEM_MANDATORY:
** If the device supports Device Assets (DRM_SUPPORT_DEVICEASSETS=1), this function MUST be implemented by the OEM.
*/
DRM_API DRM_RESULT DRM_CALL Oem_Device_GetSecureStoreGlobalPasswordSeed(
    __out_bcount(DRM_SHA1_DIGEST_LEN) DRM_BYTE f_rgbSecStorePassword[ __CB_DECL( DRM_SHA1_DIGEST_LEN ) ] );

/*
** OEM_MANDATORY:
** If the device supports Device Assets (DRM_SUPPORT_DEVICEASSETS=1), this function MUST be implemented by the OEM.
*/
DRM_API DRM_RESULT DRM_CALL Oem_Device_GetKey(
    __in_opt DRM_VOID *f_pOEMContext,
    __in const DRM_DEVICE_KEY_TYPE f_eKeyType,
    __out_bcount_opt( *f_pcbKey ) DRM_BYTE *f_pbKey,
    __inout DRM_DWORD *f_pcbKey );

/*
** OEM_MANDATORY:
** If the device supports WMDRM-ND-Rx, this function MUST be implemented by the OEM.
*/
DRM_API DRM_RESULT DRM_CALL Oem_Device_SetKey(
    __in_opt DRM_VOID *f_pOEMContext,
    __in const DRM_DEVICE_KEY_TYPE f_eKeyType,
    __in_bcount(f_cbKey) DRM_BYTE *f_pbKey,
    __in const DRM_DWORD f_cbKey );

/*
** OEM_MANDATORY:
** If the device supports Device Assets (DRM_SUPPORT_DEVICEASSETS=1), this function MUST be implemented by the OEM.
*/
DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL Oem_Device_GetUniqueId(
    __in_opt DRM_VOID *f_pOEMContext,
    __in const DRM_DEVICE_ID_TYPE f_eIDType,
    __out_bcount_opt(*f_pcbLength) DRM_BYTE *f_pbUniqueId,
    __inout DRM_DWORD *f_pcbLength ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL Oem_Device_GetModelInfo(
    __in_opt DRM_VOID   *f_pOEMContext,
    __out_ecount_opt(*f_pcchModelInfo) DRM_WCHAR *f_pwchModelInfo,
    __inout DRM_DWORD *f_pcchModelInfo ) DRM_NO_INLINE_ATTRIBUTE;

PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_BUFFER_PARAM_25033, "Out params can't be const.")
DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL Oem_Config_Read(
    __in_opt DRM_VOID *f_pOEMContext,
    __in_z DRM_CHAR *f_szKey,
    __out_bcount_opt( *f_pcbValue ) DRM_BYTE *f_pbValue,
    __inout DRM_DWORD *f_pcbValue );
PREFAST_POP /* __WARNING_NONCONST_BUFFER_PARAM_25033 "Out params can't be const." */

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL Oem_Config_Write(
    __in_opt DRM_VOID *f_pOEMContext,
    __in_z DRM_CHAR *f_szKey,
    __in_bcount( f_cbValue ) DRM_BYTE *f_pbValue,
    __in DRM_DWORD f_cbValue );

/*
** OEM_MANDATORY:
** If the device supports Secure Clock (DRM_SUPPORT_SECURE_CLOCK=1), this function MUST be implemented by the OEM.
*/
DRM_API DRM_RESULT DRM_CALL Oem_Clock_GetResetState(
    __in_opt DRM_VOID *f_pOEMContext,
    __out DRM_BOOL *f_pfReset );

/*
** OEM_MANDATORY:
** If the device supports Secure Clock (DRM_SUPPORT_SECURE_CLOCK=1), this function MUST be implemented by the OEM.
*/
DRM_API DRM_RESULT DRM_CALL Oem_Clock_SetResetState(
    __in_opt DRM_VOID *f_pOEMContext,
    __in DRM_BOOL f_fReset );

PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_PARAM_25004, "OEM contexts can't be const." )
/*
** OEM_MANDATORY:
** For all devices, this function MUST be implemented by the OEM.
** Note: The OEM implementation of this function must:
**  1) Have sufficient resolution, specifically <= 20 ms for this function.
**  2) Continue to increase in value while the process is not running (e.g. while sleeping) 
*/
DRM_API DRM_DWORD DRM_CALL Oem_Clock_GetTickCount(
    __in_opt    DRM_VOID      *f_pOEMContext );
PREFAST_POP /* __WARNING_NONCONST_BUFFER_PARAM_25033 "OEM contexts can't be const." */

/*
** OEM_MANDATORY:
** If the device supports PlayReady-ND-Tx (PRND-Tx), this function MUST be implemented by the OEM.
** Note: This function (when paired with Oem_Clock_QueryPerformanceFrequency) MUST support an overall resolution of 1 millisecond (ms) or better.
*/
DRM_API DRM_UINT64 DRM_CALL Oem_Clock_QueryPerformanceCounter(
    __in_opt    DRM_VOID      *f_pOEMContext );

/*
** OEM_MANDATORY:
** If the device supports PlayReady-ND-Tx (PRND-Tx), this function MUST be implemented by the OEM.
** Note: This function (when paired with Oem_Clock_QueryPerformanceCounter) MUST support an overall resolution of 1 millisecond (ms) or better.
*/
DRM_API DRM_UINT64 DRM_CALL Oem_Clock_QueryPerformanceFrequency(
    __in_opt    DRM_VOID      *f_pOEMContext );


/* OEM file IO functions (oemfileio.c). */

/* File Handle */
typedef DRM_VOID *OEM_FILEHDL;
#define OEM_INVALID_HANDLE_VALUE ((OEM_FILEHDL)-1)

/* Oem_File_Open Access modes */
#define OEM_GENERIC_READ       (0x80000000L)
#define OEM_GENERIC_WRITE      (0x40000000L)
#define OEM_GENERIC_EXECUTE    (0x20000000L)
#define OEM_GENERIC_ALL        (0x10000000L)

/* Oem_File_Open Share modes */
#define OEM_FILE_SHARE_NONE     0x00000000
#define OEM_FILE_SHARE_READ     0x00000001
#define OEM_FILE_SHARE_WRITE    0x00000002

/* Oem_File_Open Creation dispositions */
#define OEM_CREATE_NEW          1
#define OEM_CREATE_ALWAYS       2
#define OEM_OPEN_EXISTING       3
#define OEM_OPEN_ALWAYS         4
#define OEM_TRUNCATE_EXISTING   5

#define OEM_ATTRIBUTE_HIDDEN    0x00000002
#define OEM_ATTRIBUTE_SYSTEM    0x00000004
#define OEM_ATTRIBUTE_NORMAL    0x00000080

#define OEM_FILE_FLAG_WRITE_THROUGH 0x80000000

/* SetFilePointer move methods */
#define OEM_FILE_BEGIN          0
#define OEM_FILE_CURRENT        1
#define OEM_FILE_END            2

/*
** For information on these functions and parameters see MSDN
** For Oem_File_Open see CreateFile in MSDN -- not all flags are supported.
*/

/**********************************************************************
** Function:    Oem_File_Open
** Synopsis:    Creates, opens, reopens a file
** Arguments:   [f_pOEMContext]--Optional pointer to OEM specific context data
**              [f_pwszFileName]--Pointer to DRM_WCHAR buffer holding File
**              name.
**              [f_dwAccessMode]--Type of access to the object.
**              OEM_GENERIC_READ, OEM_GENERIC_WRITE,
**              OEM_GENERIC_EXECUTE and OEM_GENERIC_ALL
**              [f_dwShareMode]--Sharing mode of the object
**              OEM_FILE_SHARE_NONE, OEM_FILE_SHARE_READ
**              and OEM_FILE_SHARE_WRITE
**              [f_dwCreationDisposition]--Action to take on files
**              that exist, and on files that do not exist.
**              OEM_CREATE_NEW, OEM_CREATE_ALWAYS, OEM_OPEN_EXISTING
**              OEM_OPEN_ALWAYS and OEM_TRUNCATE_EXISTING
**              [f_dwAttributes]--File attributes and flags.
**              OEM_ATTRIBUTE_HIDDEN, OEM_ATTRIBUTE_SYSTEM and
**              OEM_ATTRIBUTE_NORMAL
** Returns:     Valid OEM FILE HANDLE. If fails,
**              returns OEM_INVALID_HANDLE_VALUE
**
** OEM_MANDATORY:
** For all devices, this function MUST be implemented by the OEM.
**
***********************************************************************/
DRM_API OEM_FILEHDL DRM_CALL Oem_File_Open(
    __in_opt DRM_VOID *f_pOEMContext,
    __in_z const DRM_WCHAR *f_pwszFileName,
    __in DRM_DWORD f_dwAccessMode,
    __in DRM_DWORD f_dwShareMode,
    __in DRM_DWORD f_dwCreationDisposition,
    __in DRM_DWORD f_dwAttributes );

/**********************************************************************
** Function:    Oem_File_Close
** Synopsis:    Closes an open handle opened by Oem_File_Open.
** Arguments:   [f_hFile]--File Handle
** Returns:     Non zero value if succeeds, zero if failed.
**
** OEM_MANDATORY:
** For all devices, this function MUST be implemented by the OEM.
**
***********************************************************************/
DRM_API DRM_BOOL DRM_CALL Oem_File_Close(
    __in OEM_FILEHDL f_hFile );

/**********************************************************************
** Function:    Oem_File_Delete
** Synopsis:    Deletes a file with the given name
** Arguments:   [f_pwszFileName]--Path to file to be deleted
** Returns:     Non zero value if succeeds, zero if failed.
**
** OEM_MANDATORY:
** For all devices, this function MUST be implemented by the OEM.
**
***********************************************************************/
DRM_API DRM_BOOL DRM_CALL Oem_File_Delete(
    __in_z const DRM_WCHAR *f_pwszFileName );

#ifdef PLAYREADY2TEE
/**********************************************************************
** Function:    Oem_File_Rename
** Synopsis:    Renames a file
** Arguments:   [f_pwszFileNameFrom] -- Path to file to be renamed
** Arguments:   [f_pwszFileNameTo] -- Path to renamed file
** Returns:     Non zero value if succeeds, zero if failed.
***********************************************************************/
DRM_API DRM_BOOL DRM_CALL Oem_File_Rename(
    __in_z const DRM_WCHAR *f_pwszFileNameFrom,
    __in_z const DRM_WCHAR *f_pwszFileNameTo );

/**********************************************************************
** Function:    Oem_File_GetHash
** Synopsis:    Get File Hash
** Arguments:   [f_pwszFileName] -- Path to the file
** Arguments:   [f_pbFileHash] -- SHA256 of the file
** Returns:     Non zero value if succeeds, zero if failed.
***********************************************************************/
DRM_API DRM_BOOL DRM_CALL Oem_File_GetHash(
    __in_z const DRM_WCHAR *f_pwszFileName,
    __out_bcount( SHA256_DIGEST_SIZE_IN_BYTES ) DRM_BYTE *f_pbFileHash);
#endif

/**********************************************************************
** Function:    Oem_File_Read
** Synopsis:    Reads data from a file.
** Arguments:   [f_hFile]--File Handle
**              [f_pvBuffer]--Pointer to the buffer that receives the
**              data read from the file.
**              [f_nNumberOfBytesToRead]--Number of bytes to read.
**              [f_pNumberOfBytesRead]--Total number of bytes read.
** Returns:     Non zero value if succeeds, zero if failed.
**
** OEM_MANDATORY:
** For all devices, this function MUST be implemented by the OEM.
**
***********************************************************************/
DRM_API DRM_BOOL DRM_CALL Oem_File_Read(
    __in OEM_FILEHDL f_hFile,
    __out_ecount_part( f_nNumberOfBytesToRead, *f_pNumberOfBytesRead ) DRM_VOID *f_pvBuffer,
    __in DRM_DWORD f_nNumberOfBytesToRead,
    __out DRM_DWORD *f_pNumberOfBytesRead );

/**********************************************************************
** Function:    Oem_File_Write
** Synopsis:    Writes data to a file.
** Arguments:   [f_hFile]--File Handle
**              [f_pvBuffer]--Pointer to the buffer holding the
**              data read to the file.
**              [f_nNumberOfBytesToWrite]--Number of bytes to write.
**              [f_pNumberOfBytesWritten]--Total number of bytes written.
** Returns:     Non zero value if succeeds, zero if failed.
**
** OEM_MANDATORY:
** For all devices, this function MUST be implemented by the OEM.
**
***********************************************************************/
DRM_API DRM_BOOL DRM_CALL Oem_File_Write(
    __in OEM_FILEHDL f_hFile,
    __in_ecount( f_nNumberOfBytesToWrite ) DRM_VOID *f_pvBuffer,
    __in DRM_DWORD f_nNumberOfBytesToWrite,
    __out DRM_DWORD *f_pNumberOfBytesWritten );

/**********************************************************************
** Function:    Oem_File_SetFilePointer
** Synopsis:    Sets File pointer.
** Arguments:   [f_lDistanceToMove]--Number of bytes to move
**              [f_dwMoveMethod]--Starting point for the file pointer move
**              OEM_FILE_BEGIN, OEM_FILE_CURRENT and  OEM_FILE_END
**              [f_pdwNewFilePointer]--New File pointer.
** Returns:     Non zero value if succeeds, zero if failed.
**
** OEM_MANDATORY:
** For all devices, this function MUST be implemented by the OEM.
**
***********************************************************************/
DRM_API DRM_BOOL DRM_CALL Oem_File_SetFilePointer(
    __in OEM_FILEHDL f_hFile,
    __in DRM_LONG f_lDistanceToMove,
    __in DRM_DWORD f_dwMoveMethod,
    __out_opt DRM_DWORD *f_pdwNewFilePointer );

/**********************************************************************
** Function:    Oem_File_Lock
** Synopsis:    Immidiately locks the portion of specified file.
** Arguments:   [f_hFile]--File Handle
**              [f_fExclusive]-- If TRUE, locks file for exclusive access
**              by the calling process.
**              [f_dwFileOffset]--Offset from begining of file.
**              [f_nNumberOfBytesToLock]--Number of bytes to lock.
**              [f_fWait]--Whether to wait for the lock to complete.
** Returns:     Non zero value if succeeds, zero if failed.
**
** OEM_MANDATORY:
** If the device supports locking (DRM_SUPPORT_LOCKING=1), this function MUST be implemented by the OEM.
**
***********************************************************************/
DRM_API DRM_BOOL DRM_CALL Oem_File_Lock(
    __in OEM_FILEHDL f_hFile,
    __in DRM_BOOL f_fExclusive,
    __in DRM_DWORD f_dwFileOffset,
    __in DRM_DWORD f_nNumberOfBytesToLock,
    __in DRM_BOOL f_fWait );

/**********************************************************************
** Function:    Oem_File_Unlock
** Synopsis:    Unlocks the locked portion of specified file.
** Arguments:   [f_hFile]--File Handle
**              [f_dwFileOffset]--Offset from begining of file.
**              [f_nNumberOfBytesToLock]--Number of bytes to lock.
** Returns:     Non zero value if succeeds, zero if failed.
**
** OEM_MANDATORY:
** If the device supports locking (DRM_SUPPORT_LOCKING=1), this function MUST be implemented by the OEM.
**
***********************************************************************/
DRM_API DRM_BOOL DRM_CALL Oem_File_Unlock(
    __in OEM_FILEHDL f_hFile,
    __in DRM_DWORD f_dwFileOffset,
    __in DRM_DWORD f_nNumberOfBytesToUnlock );

/**********************************************************************
** Function:    Oem_File_SetEndOfFile
** Synopsis:    Moves the end-of-file (EOF) position for the
**              specified file to the current position of the file
**              pointer.
** Arguments:   [f_hFile]--File Handle
** Returns:     Non zero value if succeeds, zero if failed.
**
** OEM_MANDATORY:
** For all devices, this function MUST be implemented by the OEM.
**
***********************************************************************/
DRM_API DRM_NO_INLINE DRM_BOOL DRM_CALL Oem_File_SetEndOfFile(
    __in OEM_FILEHDL f_hFile) DRM_NO_INLINE_ATTRIBUTE;

/**********************************************************************
** Function:    Oem_File_GetSize
** Synopsis:    Gets size of the file.
** Arguments:   [f_hFile]--File Handle
**              [f_pdwFileSize]--Pointer to DRM_DWORD to get the size.
** Returns:     Non zero value if succeeds, zero if failed.
**
** OEM_MANDATORY:
** For all devices, this function MUST be implemented by the OEM.
**
***********************************************************************/
DRM_API DRM_BOOL DRM_CALL Oem_File_GetSize(
    __in OEM_FILEHDL f_hFile,
    __out DRM_DWORD  *f_pdwFileSize );

/**********************************************************************
** Function:    Oem_File_FlushBuffers
** Synopsis:    Flushes the buffers of the specified file and causes
**              all buffered data to be written to the file.
** Arguments:   [f_hFile]--File Handle
** Returns:     Non zero value if succeeds, zero if failed.
**
** OEM_MANDATORY:
** For all devices, this function MUST be implemented by the OEM.
**
***********************************************************************/
DRM_API DRM_BOOL DRM_CALL Oem_File_FlushBuffers(
    __in OEM_FILEHDL f_hFile );

/* OEM time functions (oemtime.c). */

/**********************************************************************
** Function:    Oem_Clock_SystemTimeToFileTime
** Synopsis:    Converts System Time format to File time format.
** Arguments:   [f_lpSystemTime]--Pointer to DRMSYSTEMTIME structure
**              containing system time
**              [f_lpFileTime]--Pointer to DRMFILETIME structure to get
**              the time.
** Returns:     Non zero value if succeeds, zero if failed.
**
** OEM_MANDATORY:
** For all devices, this function MUST be implemented by the OEM.
**
***********************************************************************/
DRM_API DRM_BOOL DRM_CALL Oem_Clock_SystemTimeToFileTime(
    __in const DRMSYSTEMTIME *f_lpSystemTime,
    __out DRMFILETIME *f_lpFileTime );

/**********************************************************************
** Function:    Oem_Clock_FileTimeToSystemTime
** Synopsis:    Converts File time format to System Time format.
** Arguments:   [f_lpFileTime]--Pointer to DRMFILETIME structure
**              containing file time
**              [f_lpSystemTime]--Pointer to DRMSYSTEMTIME structure to
**              get the time.
** Returns:     Non zero value if succeeds, zero if failed.
**
** OEM_MANDATORY:
** For all devices, this function MUST be implemented by the OEM.
**
***********************************************************************/
DRM_API DRM_BOOL DRM_CALL Oem_Clock_FileTimeToSystemTime(
    __in const DRMFILETIME *f_lpFileTime,
    __out DRMSYSTEMTIME *f_lpSystemTime );

/**********************************************************************
** Function:    Oem_Clock_GetSystemTime
** Synopsis:    Gets current System time. It is expressed in UTC.
** Arguments:   [f_pOEMContext]--OEM specific data
**              [f_lpSystemTime]--Pointer to DRMSYSTEMTIME structure
**              to get the time.
**
** OEM_MANDATORY:
** For all devices, this function MUST be implemented by the OEM.
**
***********************************************************************/
DRM_API DRM_VOID DRM_CALL Oem_Clock_GetSystemTime(
    __in_opt    DRM_VOID      *f_pOEMContext,
    __out       DRMSYSTEMTIME *f_psystime );

/**********************************************************************
** Function:    Oem_Clock_GetSystemTimeAsFileTime
** Synopsis:    Gets current System time. It is expressed in UTC.
** Arguments:   [f_pOEMContext]--OEM specific data
**              [f_pfiletime]--Pointer to DRMFILETIME structure
**              to get the time.
**
** OEM_MANDATORY:
** For all devices, this function MUST be implemented by the OEM.
**
***********************************************************************/
DRM_API DRM_VOID DRM_CALL Oem_Clock_GetSystemTimeAsFileTime(
    __in_opt    DRM_VOID    *f_pOEMContext,
    __out       DRMFILETIME *f_pfiletime );

/**********************************************************************
** Function:    Oem_Clock_SetSystemTime
** Synopsis:    Sets the System time. It is expressed in UTC.
** Arguments:   [f_pOEMContext]--OEM specific data
**              [f_lpSystemTime]--Pointer to DRMSYSTEMTIME structure
**              holding the time.
**
** OEM_MANDATORY:
** For all devices, this function MUST be implemented by the OEM.
**
***********************************************************************/
DRM_API DRM_VOID DRM_CALL Oem_Clock_SetSystemTime(
    __in_opt       DRM_VOID      *f_pOEMContext,
    __in     const DRMSYSTEMTIME *f_lpSystemTime );

/* OEM platform initialization functions (oemimpl.c). */
/*
** OEM_MANDATORY:
** For all devices, this function MUST be implemented by the OEM.
*/
DRM_API DRM_RESULT DRM_CALL Oem_Platform_Init();

/*
** OEM_MANDATORY:
** For all devices, this function MUST be implemented by the OEM.
*/
DRM_API DRM_RESULT DRM_CALL Oem_Platform_UnInit();


/* OEM memory allocation functions (oemimpl.c). */

/*
** OEM_MANDATORY:
** For all devices, this function MUST be implemented by the OEM.
*/
DRM_API DRM_VOID * DRM_CALL Oem_MemAlloc(
    __in DRM_DWORD f_cbSize );

/*
** OEM_MANDATORY:
** For all devices, this function MUST be implemented by the OEM.
*/
DRM_API DRM_NO_INLINE DRM_VOID DRM_CALL Oem_MemFree(
    __in DRM_VOID *f_pv );

#define SAFE_OEM_FREE( p )                  \
    if ( (p) != NULL )                      \
    {                                       \
        Oem_MemFree( ( DRM_VOID * )(p) );   \
        (p) = NULL;                         \
    }

/*
** OEM_MANDATORY:
** For all devices, this function MUST be implemented by the OEM.
*/
DRM_API DRM_VOID * DRM_CALL Oem_MemRealloc(
    __inout DRM_VOID  *f_pv,
    __in DRM_DWORD f_cbSize );

#define SAFE_SECURE_OEM_FREE( p, c )                                    \
    if (p != NULL)                                                      \
    {                                                                   \
        OEM_SECURE_ZERO_MEMORY( p, c );                                 \
        Oem_MemFree( ( DRM_VOID * ) p );                                \
        p = NULL;                                                       \
    }

/*
** OEM_MANDATORY:
** For all devices, this function MUST be implemented by the OEM.
*/
DRM_API DRM_VOID DRM_CALL Oem_Random_SetSeed(
    __in_opt DRM_VOID *f_pOEMContext,
    __in const DRM_UINT64 f_qwNewSeed );

PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_PARAM_25004, "OEM contexts can't be const" );
/*
** OEM_MANDATORY:
** For all devices, this function MUST be implemented by the OEM.
*/
DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL Oem_Random_GetBytes(
    __in_opt               DRM_VOID  *f_pOEMContext,
    __out_bcount(f_cbData) DRM_BYTE  *f_pbData,
    __in                   DRM_DWORD  f_cbData ) DRM_NO_INLINE_ATTRIBUTE;
PREFAST_POP

/*
** OEM_MANDATORY:
** If the device supports XML hashing (DRM_SUPPORT_XMLHASH=1), this function MUST be implemented by the OEM.
*/
DRM_API DRM_DWORD DRM_CALL Oem_GetCurrentThreadId( DRM_VOID );

DRM_API DRM_VOID DRM_CALL Oem_Hds_ClearBlockHeaderCache( DRM_VOID );

DRM_API DRM_RESULT DRM_CALL Oem_Hds_CheckBlockHeaderCache(
    __in      DRM_DWORD   f_dwBlockNumber,
    __in_opt  OEM_FILEHDL f_hHDSFileHandle,
    __out_opt DRM_DWORD  *f_pdwBlockHeaderMetadata,
    __out_bcount_opt( f_cbBytesToRead ) DRM_BYTE   *f_pbBlock,
    __in      DRM_DWORD   f_cbBytesToRead );

DRM_API DRM_RESULT DRM_CALL Oem_Hds_UpdateBlockHeaderCache(
    __in                                      DRM_DWORD   f_dwBlockNumber,
    __in_opt                                  OEM_FILEHDL f_hHDSFileHandle,
    __in                                      DRM_DWORD   f_dwBlockHeaderMetadata,
    __in_bcount_opt( f_cbBytesToWrite ) const DRM_BYTE   *f_pbBlock,
    __in                                      DRM_DWORD   f_cbBytesToWrite );

DRM_API DRM_RESULT DRM_CALL Oem_Hds_GetParams(
    __in_opt        DRM_VOID  *f_pOEMContext,
    __in      const DRM_WCHAR *f_pwszDeviceStoreName,
    __out_opt       DRM_DWORD *f_pdwDataStoreFileSizeInitKB,
    __out_opt       DRM_DWORD *f_pdwDataStoreFileSizeGrowKB,
    __out_opt       DRM_DWORD *f_pdwDataStoreBlockSize );

#if DRM_SUPPORT_SST_REDUNANCY

EXIT_PK_NAMESPACE;

#include <drmtoken.h>

ENTER_PK_NAMESPACE;

DRM_API DRM_RESULT DRM_CALL VariableSSTRedundancyGetorSet(
   __in const DRM_CONST_STRING *f_pdstrToken,
   __in TOKEN *f_pNewValue,
   __out TOKEN *f_pResult,
   __inout DRM_VOID *f_pvOpaqueData,
   __in DRM_BOOL f_fSet );

#endif /* DRM_SUPPORT_SST_REDUNANCY */

typedef struct
{
    DRM_BOOL    fFreezeTickCount;
    DRM_DWORD   dwTickCount;
} DRM_TEST_OEM_CONTEXT;


/* Code Coverage functions (oemimpl.c) */
DRM_API DRM_VOID DRM_CALL Oem_CodeCoverage_FlushData(
    __in_opt const DRM_VOID  *f_pOEMContext );

typedef       DRM_VOID * OEM_CRYPTO_HANDLE;
typedef const DRM_VOID * OEM_CRYPTO_CONST_HANDLE;
#define OEM_CRYPTO_HANDLE_INVALID ((OEM_CRYPTO_HANDLE)0)

/*
** Key Types.
*/
typedef enum
{
    OEM_HAL_KEY_TYPE_INVALID                          = -1,
    OEM_HAL_KEY_TYPE_ECC_P256_CONTENT_ENCRYPT         = 0,
    OEM_HAL_KEY_TYPE_ECC_P256_DOMAIN_ENCRYPT          = 1,
    OEM_HAL_KEY_TYPE_ECC_P256_MESSAGE_ENCRYPT         = 2,
    OEM_HAL_KEY_TYPE_ECC_P256_SIGN                    = 3,
    OEM_HAL_KEY_TYPE_ECC_P256_PUBLIC                  = 4,
    OEM_HAL_KEY_TYPE_ECC_P256_MODEL_SIGN              = 5,
    OEM_HAL_KEY_TYPE_AES_ECB_ROOT                     = 6,
    OEM_HAL_KEY_TYPE_AES_CTR_CONTENT                  = 7,
    OEM_HAL_KEY_TYPE_AES_ECB_MESSAGE_ENCRYPT          = 8,
    OEM_HAL_KEY_TYPE_AES_ECB_DOMAIN_PROTECT           = 9,
    OEM_HAL_KEY_TYPE_AES_OMAC1_SECURE_STORE           = 10,
    OEM_HAL_KEY_TYPE_AES_KEYFILE                      = 11,
    OEM_HAL_KEY_TYPE_AES_GENERIC_KEY_CONTENT          = 12,
    OEM_HAL_KEY_TYPE_AES_GENERIC_KEY_ROOT             = 13,

    /*
    ** Keys generated locally for new licenses can have
    ** different operations performed on/with them than
    ** keys from existing licenses.
    */
    OEM_HAL_KEY_TYPE_AES_ECB_NEW_LICENSE_ROOT         = 14,
    OEM_HAL_KEY_TYPE_AES_CTR_NEW_LICENSE_CONTENT      = 15,

    /*
    ** Legacy and SLK key types, and OEM HAL functionality
    ** pertaining to them, should only be implemented for
    ** devices that support legacy WMDRM codecs and functionality
    */
    OEM_HAL_KEY_TYPE_LEGACY                           = 16,
    OEM_HAL_KEY_TYPE_AES_SLK                          = 17,

    /*
    ** Always ensure OEM_HAL_KEY_TYPE_NUM_VALID_TYPES is
    ** one greater than the last valid key type value
    */
    OEM_HAL_KEY_TYPE_NUM_VALID_TYPES                  = 18,
    OEM_HAL_KEY_TYPE_UNDEFINED                        = 255
} OEM_HAL_KEY_TYPE;

EXIT_PK_NAMESPACE;

#endif /* __OEMCOMMON_H__ */

