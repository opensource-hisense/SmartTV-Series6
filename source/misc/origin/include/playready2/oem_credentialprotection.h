/*
** calvin create
*/

#ifndef _OEM_CREDENTIALPROTECTION_H_
#define _OEM_CREDENTIALPROTECTION_H_


/*******************************************************************************
 * type definition                                                             *
 *******************************************************************************/
typedef int (*HWFuncPtr_LoadCredentialProtectionKey)(unsigned char key[16], unsigned char iv[16]);


/*******************************************************************************
 * external variables                                                          *
 *******************************************************************************/
extern HWFuncPtr_LoadCredentialProtectionKey  gHWFunc_LoadCredentialProtectionKey;


/*******************************************************************************
 * API                                                                         *
 *******************************************************************************/
DRM_API DRM_RESULT DRM_CALL Oem_RegisterLoadCredentialProtectionKey
(
    HWFuncPtr_LoadCredentialProtectionKey pfunc_LoadCredentialProtectionKey
);


#endif //_OEM_CREDENTIALPROTECTION_H_
