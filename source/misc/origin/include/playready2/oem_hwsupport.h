/*
** calvin create this file to utilize HW support functions
*/

#ifndef _OEM_HWSUPPORT_H_
#define _OEM_HWSUPPORT_H_

/*******************************************************************************
 * type definition                                                             *
 *******************************************************************************/
 typedef enum
{
    DRM_CDT_WMDRMPD = 1,
    DRM_CDT_WMDRMPD_TEMPLATE,
    DRM_CDT_PLAYREADY,
    DRM_CDT_PLAYREADY_TEMPLATE,
    DRM_CDT_NETRECEIVER,
    DRM_CDT_NETRECEIVER_TEMPLATE,
    DRM_CDT_WMDRMPD_GROUP,
    DRM_CDT_PLAYREADY_DEVICE_SIGN,
    DRM_CDT_PLAYREADY_DEVICE_ENCRYPT,
    DRM_CDT_PLAYREADY_MODEL,
    DRM_CDT_PLAYREADY_NDR,
    DRM_CDT_PLAYREADY_NDR_MODEL
} PLAYREADY_CREDENTIAL_TYPE;


typedef int (*HWFuncPtr_GetUniqueSerialNumber)(unsigned char pSN[], int *pSize);
typedef int (*HWFuncPtr_GetRandomNumber)(unsigned char pRandomNum[], int size);
typedef int (*HWFuncPtr_AES128ECBEncrypt)(unsigned char key[16], unsigned char *pSrc, int size, unsigned char *pDst);
typedef int (*HWFuncPtr_GetSetCredential)(PLAYREADY_CREDENTIAL_TYPE type, unsigned char *pBuffer, unsigned int *dataSize, int bRead);

typedef struct _hw_functions
{
    HWFuncPtr_GetUniqueSerialNumber         pHWFunc_GetUniqueSerialNumber;
    HWFuncPtr_GetRandomNumber               pHWFunc_GetRandomNumber;
    HWFuncPtr_AES128ECBEncrypt              pHWFunc_AES128ECBEncrypt;
    HWFuncPtr_GetSetCredential              pHWFunc_GetSetCredential;
}HWFunctions_t;

/*******************************************************************************
 * Global or external variables                                                *
 *******************************************************************************/
extern HWFunctions_t gHWFunctions;


/*******************************************************************************
 * API                                                                         *
 *******************************************************************************/
//==============================================================================
// Oem_RegisterGetUniqueSerialNumberFunc
//
// Arguments:
//      pfunc_GetUniqueSerialNumber:
//          function pointer to get a HW unique serial number of the device.
//          the function procotype is:
//              int (*Function) (unsigned char pSN[], int *pSize)
//              Arguments:
//                  pSN[]: OUT, serial number buffer
//                  pSize: OUT, size of serial number buffer
//              return 0 for sucess and non-zero otherwise.
//              if this function is called with pSN set to NULL, then *pSize
//              should returned with actual serial number size.
// Returns:
//      DRM error code
// Descriptions:
//      This function is optional. If it is not called, the DRM will generate
//      a fake serial number
//=============================================================================
DRM_API DRM_RESULT DRM_CALL Oem_RegisterGetUniqueSerialNumberFunc
(
    HWFuncPtr_GetUniqueSerialNumber  pfunc_GetUniqueSerialNumber
);

//=============================================================================
// Oem_RegisterGetRandomNumberFunc
//
// Arguments:
//      pfunc_GetRandomNumber:
//          function pointer to generate HW random number
//          the function procotype is:
//              int (*Function)(unsigned char pRandomNum[], int size)
//          Arguments:
//              pRandomNum: OUT, random number buffer
//              size:       IN,  the size of random number wanted
//          return 0 for success and non-zero otherwise.
// Returns:
//      DRM error code
// Descriptions:
//      This function is optional. If it is not called, the DRM will generate
//      random number in a software way.
//============================================================================
DRM_API DRM_RESULT DRM_CALL Oem_RegistserGetRandomNumberFunc
(
    HWFuncPtr_GetRandomNumber  pfunc_GetRandomNumber
);


//============================================================================
// Oem_RegisterAES128ECBEncryptFunc
//
// Arguments:
//      pfunc_AES128ECBEncryptFunc:
//          function pointer to do the AES-128-ECB encryption operation in HW.
//          the function prototype is:
//              int (*Function)(unsigned char key[16], unsigned char *pSrc, int size, unsigned char *pDst)
//          Arguments:
//              key: IN, key for AES-128-ECB encryption
//              pSrc: IN, source data, data needs to be encrypted.
//              size: IN, the size for the source data. the passed in size value will be multiple of 16.
//              pDst: OUT, the generated encrypted data. its size is same as source data.
//          return 0 for success and non-zero otherwise.
// Resturns:
//      DRM error code
// Descriptions:
//      This function can be used to take advantage of HW AES accelerator. and 
//      it is optional. If it is not called, the DRM will use SW AES implementation.
//============================================================================
DRM_API DRM_RESULT DRM_CALL Oem_RegisterAES128ECBEncryptFunc
(
    HWFuncPtr_AES128ECBEncrypt  pfunc_AES128ECBEncryptFunc
);

//==============================================================================
// Oem_RegisterGetSetCredentialFunc
//
// Arguments:
//      Oem_RegisterGetSetCredentialFunc:
//          function pointer to read/write playready credential files.
//          the function procotype is:
//              int (*Function) (PLAYREADY_CREDENTIAL_TYPE type, unsigned char *pBuffer, unsigned int *dataSize, bool bRead)
//              Arguments:
//                  PLAYREADY_CREDENTIAL_e: IN, The type of credential file to read
//                  pBuffer: IN/OUT The data buffer to read/write data, For read, if NULL, the function need to allocate buffer for it 
//                  dataSize: IN/OUT Out: the pBufferSize, IN: The data size read/write
//                  bRead: True: Read False: Write
//              return 0 for sucess and non-zero otherwise.
// Returns:
//      DRM error code
// Descriptions:
//      This function is optional. If it is not called, the DRM will read/write credential files 
//      encrypted with the default key or the key application assigned
//=============================================================================
DRM_API DRM_RESULT DRM_CALL Oem_RegisterGetSetCredentialFunc
(
    HWFuncPtr_GetSetCredential  pfunc_GetSetCredential
);

#endif
