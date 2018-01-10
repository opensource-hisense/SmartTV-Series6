/*************************************************************************************
 *                                                                                   *
 * This file defines client-side TEE APIs directly invoked by PlayReady code.        *
 *                                                                                   *
 * The stub implementations of these APIs in tee.c directly invoke TEE-side APIs,    *
 * which are defined in teeimpl.h and implemented in teeimpl.c.                      *
 *                                                                                   *
 * Real client-side API  implementations in tee.c shall be rewritten to invoke       *
 * TEE-side functions using TEE-specific call mechanisms.                            *
 *                                                                                   *
 *************************************************************************************/

#ifndef __TEE_INCLUDE_H__
#define __TEE_INCLUDE_H__

/*
 * teecommon.h includes some constants required by PlayReady and by the reference TEE implementation.
 * It is included here to avoid multiple includs from the PlayReady code.
 */
#include <teecommon.h>
#include <drmblackboxtypes.h>

/********************************************************************************************************
 *                                                                                                      *
 * Design Notes:                                                                                        *
 *                                                                                                      *
 * TEE is configured with AES-128 "TEE Master Key", presumably set at manufacturing time and unique per *
 * device. teeimpl.c used hardcoded TEE Master Key, which MUST be changed for production TEE. This key  *
 * protects TEE state that aplication stores outside TEE.                                               *
 *                                                                                                      *
 ********************************************************************************************************/

/***************************
 * TEE Lifecycle Functions *
 ***************************/

/*************************************************************************************
 * Is called from Drm_Initialize(). Functionality is specific to TEE implementation. *
 *
 * Input: TEE state data and its size in bytes
 */
int TEE_Initialize(const DRM_BYTE * const inbuf,
                   const DRM_DWORD        inlen);

/*
 * Is called from Drm_Reinitialize(). Functionality is specific to TEE implementation.
 */
int TEE_Reinitialize();

/*
 * Is called from Drm_Unitialize(). Functionality is specific to TEE implementation.
 */
int TEE_Uninitialize();

/***********************************************************************************************
 * Enable/Disable Secure Stop Functionality (default hard-coded into PlayReady implementation) *
 * If Secure Stop is disabled, other secure stops APIs become no-op:                           *
 * they do not fail, just return no secure stop / state data                                   *
 ***********************************************************************************************/
int TEE_TurnSecureStop(const DRM_BOOL inOnOff);

/*************************************************
 * Check if Secure Stop Functionality is Enabled *
 *************************************************/
int TEE_IsSecureStopOn(DRM_BOOL * const isOn);

/***************************************************************************************
 * Create a new Session inside the TEE; generate and return 16-byte random session ID. *
 * The Session ID is to be used as the NONCE in a License Challenge.                   *
 ***************************************************************************************/
int TEE_StartSession(DRM_BYTE * const outSessionId);

/******************************************************************************
 * Cancel a new Session inside the TEE. Only possible before License binding. *
 ******************************************************************************/
int TEE_CancelSession(const DRM_BYTE * const inSessionId);

/***************************
 * Bind license to session *
 ***************************/
int TEE_BindLicense(const DRM_BYTE * const inSessionId,
                    const DRM_BYTE * const inKID);

/***********************************************************************************
 * Bind content decryption key to a given session, at the beginning of a playback. *
 ***********************************************************************************/
int TEE_BindSession(const OEM_HAL_KEY_REGISTER_INDEX inKeyIndex,
                    const DRM_BYTE * const inKID);

/***************************************
 * Stop Session at the end of playback *
 ***************************************/
int TEE_StopSession(const OEM_HAL_KEY_REGISTER_INDEX inKeyIndex);

/**************************************************************************
 * Check if secure stop state needs to be updated for a given content key *
 **************************************************************************/
int TEE_SecureStopUpdated(const OEM_HAL_KEY_REGISTER_INDEX inKeyIndex,
                                DRM_BOOL * const outUpdate);

/*********************************************************************************************
 * Return IDs of outstanding secure stops.                                                   *
 *********************************************************************************************/
int TEE_GetSecureStopIds(DRM_BYTE outSessionIds[TEE_MAX_NUM_SECURE_STOPS][TEE_SESSION_ID_LEN],
                         DRM_DWORD * const outNumSessionIds);

/*********************************************************************************************
 * Return secure stop for a given session ID.                                                *
 * Return error if sessionID does not exist or corresponds to the playback still in-progress *
 *********************************************************************************************/
int TEE_GetSecureStop(const DRM_BYTE * const inSessionId,
                      const OEM_HAL_KEY_REGISTER_INDEX inKeyIndex,
                            DRM_BYTE * const outSecureStop,
                            DRM_DWORD  * const outSecureStopLen,
                            TEE_SIGNATURE * const outSig);

/*********************************************************************************
 * Permanently remove outstanding secure stop for a given session ID.            *
 * Pass updated persistent state back to the caller.                             *
 * Return error if sessionID does not correspond to any outstanding secure stop. *
 *********************************************************************************/
int TEE_CommitSecureStop(const DRM_BYTE  * const inSessionId,
                               DRM_BYTE  * const outState,
                               DRM_DWORD * const outStateLen);

/*************************************************************
 * Permanently remove all outstanding secure stops.          *
 * Pass updated (empty) persistent state back to the caller. *
 *************************************************************/
int TEE_ResetSecureStops(DRM_BYTE  * const outState,
                         DRM_DWORD * const outStateLen,
                         DRM_DWORD * const outNumRemoved);

/*****************************************************************************
 * Get current state to persist. State contains version and all secure stops *
 *****************************************************************************/
int TEE_GetState(DRM_BYTE  * const outState,
                 DRM_DWORD * const outStateLen);

#endif /* __TEE_INCLUDE_H__ */
