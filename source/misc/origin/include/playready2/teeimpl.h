#ifndef __TEEIMPL_INCLUDE_H__
#define __TEEIMPL_INCLUDE_H__

#include <teecommon.h>
#include <drmblackboxtypes.h>

/***************************************************************************************************************
 * NOTE: the APIs defined here are implemented inside the TEE. They are called by the corresponding TEE client *
 * functions defined in tee.h header file, using TEE implementation-specific IPC mechanism.                    *
 *                                                                                                             *
 * See the inline API documentation in tee.h to understand what each TEE API does.                             *
 *                                                                                                             *
 * The function names in tee.h. and teeimpl.h correspond to each other as follows:                             *
 * a) "tee" prefix in a function name in teeimpl.h is replaced with "TEE_" prefix in tee.h                     *
 * b) underscores in function names in tee.h are removed in teeimpl.h                                          *
 * c) the list and types of parameters in matching functions in tee.h and teeimpl.h are identical.             *
 *                                                                                                             *
 ***************************************************************************************************************/

/*****************
 * TEE Lifecycle *
 *****************/
int teeInitialize(const DRM_BYTE * const inbuf,
                  const DRM_DWORD        inlen);

int teeReinitialize();

int teeUninitialize();

/***********************************************************************************************
 * Enable/Disable Secure Stop Functionality (default hard-coded into PlayReady implementation) *
 * If Secure Stop is disabled, other secure stops APIs become no-op:                           *
 * they do not fail, just return no secure stop / state data                                   *
 ***********************************************************************************************/
int teeTurnSecureStop(const DRM_BOOL inOnOff);

/*************************************************
 * Check if Secure Stop Functionality is Enabled *
 *************************************************/
int teeIsSecureStopOn(DRM_BOOL * const isOn);

/***************************************************************************************
 * Create a new Session inside the TEE; generate and return 16-byte random session ID. *
 * The Session ID is to be used as the NONCE in a License Challenge.                   *
 ***************************************************************************************/
int teeStartSession(DRM_BYTE * const outSessionId);

/******************************************************************************
 * Cancel a new Session inside the TEE. Only possible before License binding. *
 ******************************************************************************/
int teeCancelSession(const DRM_BYTE * const inSessionId);

/***************************
 * Bind license to session *
 ***************************/
int teeBindLicense(const DRM_BYTE * const inSessionId,
                   const DRM_BYTE * const inKID);

/***********************************************************************************
 * Bind content decryption key to a given session, at the beginning of a playback. *
 ***********************************************************************************/
int teeBindSession(const OEM_HAL_KEY_REGISTER_INDEX inKeyIndex,
                   const DRM_BYTE * const inKID);

/***************************************
 * Stop Session at the end of playback *
 ***************************************/
int teeStopSession(const OEM_HAL_KEY_REGISTER_INDEX inKeyIndex);

/**************************************************************************
 * Check if secure stop state needs to be updated for a given content key *
 **************************************************************************/
int teeSecureStopUpdated(const OEM_HAL_KEY_REGISTER_INDEX inKeyIndex,
                               DRM_BOOL * const outUpdate);

/*********************************************************************************************
 * Return IDs of outstanding secure stops.                                                   *
 *********************************************************************************************/
int teeGetSecureStopIds(DRM_BYTE outSessionIds[TEE_MAX_NUM_SECURE_STOPS][TEE_SESSION_ID_LEN],
                        DRM_DWORD * const outNumSessionIds);

/**********************************************************************************************
 * Return secure stop for a given session ID. Remove Session from the TEE.                    *
 * Return error if sessionID does not exist or corresponds to the playback still in-progress. *
 **********************************************************************************************/
int teeGetSecureStop(const DRM_BYTE * const inSessionId,
                     const OEM_HAL_KEY_REGISTER_INDEX inKeyIndex,
                           DRM_BYTE * const outSecureStop,
                           DRM_DWORD * const outSecureStopLen,
                           TEE_SIGNATURE * const outSig);

/*********************************************************************************
 * Permanently remove outstanding secure stop for a given session ID.            *
 * Pass updated persistent state back to the caller.                             *
 * Return error if sessionID does not correspond to any outstanding secure stop. *
 *********************************************************************************/
int teeCommitSecureStop(const DRM_BYTE  * const inSessionId,
                              DRM_BYTE  * const outState,
                              DRM_DWORD * const outStateLen);

/*************************************************************
 * Permanently remove all outstanding secure stops.          *
 * Pass updated (empty) persistent state back to the caller. *
 *************************************************************/
int teeResetSecureStops(DRM_BYTE  * const outState,
                        DRM_DWORD * const outStateLen,
                        DRM_DWORD * const outNumDeleted);

/*****************************************************************************
 * Get current state to persist. State contains version and all secure stops *
 *****************************************************************************/
int teeGetState(DRM_BYTE  * const outState,
                DRM_DWORD * const outStateLen);

#endif /* __TEEIMPL_INCLUDE_H__ */
