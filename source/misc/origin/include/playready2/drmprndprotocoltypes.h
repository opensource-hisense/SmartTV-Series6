/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef _DRMPRNDPROTOCOLTYPES_H_
#define _DRMPRNDPROTOCOLTYPES_H_

#include <drmpragmas.h>
#include <drmerr.h>
#include <drmblackbox.h>
#include <drmrevocation.h>
#include <drmlicstore.h>
#include <drmplayreadyobj.h>
#include <drmprndcallbacktypes.h>

ENTER_PK_NAMESPACE;

#define DRM_PRND_STACK_SIZE                                     20000                   /* ~= 20 KB */
#define DRM_PRND_REGISTRATION_TIMEOUT                           120                     /* 120 seconds, i.e. Two minutes */
#define DRM_PRND_REGISTRATION_VALIDITY                          (48 * 60 * 60)          /* 48 hours, i.e. 172800 seconds */
#define DRM_PRND_MAX_CLOCK_DRIFT_AT_REGISTRATION_SECS           DRM_I64Asgn( 0, 300 )   /* 300 seconds, i.e. Five minutes */
#define DRM_PRND_FURTHER_CLOCK_DRIFT_DURING_SESSION_SECS        60                      /* 60 seconds, i.e. One minute */

#define DRM_PRND_LICENSE_REBIND_MIN_EXPIRE_AFTER_FIRST_PLAY     60                      /* 60 seconds */

typedef enum
{
    DRM_PRND_PROXIMITY_DETECTION_TYPE_UDP                           = 0x00000001,
    DRM_PRND_PROXIMITY_DETECTION_TYPE_TCP                           = 0x00000002,
    DRM_PRND_PROXIMITY_DETECTION_TYPE_TRANSPORT_AGNOSTIC            = 0x00000004,
    /* NOTE: This is used as a Bitmask, so new values must increase as multiples of two! */
} DRM_PRND_PROXIMITY_DETECTION_TYPE;

typedef enum
{
    DRM_PRND_SIGNATURE_TYPE_ECC256_RECEIVER_SIGNING_KEY             = 0x1,
    DRM_PRND_SIGNATURE_TYPE_AES_OMAC1_MI                            = 0x2,
    DRM_PRND_SIGNATURE_TYPE_ECC256_TRANSMITTER_SIGNING_KEY          = 0x3,
} DRM_PRND_SIGNATURE_TYPE;

typedef enum
{
    DRM_PRND_ENCRYPTION_TYPE_ECC256_RECEIVER_PRND_ENCRYPTION_KEY    = 0x1,
    DRM_PRND_ENCRYPTION_TYPE_AES_ECB_MK                             = 0x2,
} DRM_PRND_ENCRYPTION_TYPE;

typedef enum
{
    DRM_PRND_ACTION_PLAY                                            = 0x1,
} DRM_PRND_ACTION;

typedef enum
{
    DRM_PRND_ACTION_QUALIFIER_NONE                                  = 0x0,
} DRM_PRND_ACTION_QUALIFIER;

typedef enum
{
    DRM_PRND_PROXIMITY_DETECTION_STATE_INIT                         = 0x0,  /* Haven't even started proximity detection yet (i.e. still in registration) */
    DRM_PRND_PROXIMITY_DETECTION_STATE_REGISTERED                   = 0x1,  /* Haven't processed the start message yet (but have at least received one) */
    DRM_PRND_PROXIMITY_DETECTION_STATE_CHALLENGED                   = 0x2,  /* Challenge sent, waiting for response */
    DRM_PRND_PROXIMITY_DETECTION_STATE_COMPLETE                     = 0x3,  /* Complete, but may be an error condition, e.g. timeout */
    DRM_PRND_PROXIMITY_DETECTION_STATE_VERIFIED                     = 0x4,  /* Complete and successful */
} DRM_PRND_PROXIMITY_DETECTION_STATE;

/* Maximum number of milliseconds for round trip proximity timeout */
#define DRM_PRND_PROXIMITY_RTT_THRESHOLD_MS     7

#define DRM_PRND_OPTIMIZATION_DIGEST_SIZE       DRM_AES_BLOCKLEN

typedef struct __tagDRM_PRND_TRANSMITTER_SESSION_CONTEXT
{
    /* These are internally allocated and freed when the session ends */
    DRM_BYTE                                            *pbReceiverCertificate;
    DRM_DWORD                                            cbReceiverCertificate;
    DRM_BYTE                                            *pbReceiverCertificateCRL;
    DRM_DWORD                                            cbReceiverCertificateCRL;
    DRM_BYTE                                            *pbTransmitterProximityDetectionChannel;
    DRM_WORD                                             cbTransmitterProximityDetectionChannel;
    DRM_BYTE                                            *pbWorkingSpace;
    DRM_DWORD                                            cbWorkingSpace;

    /* General members */
    DRM_BYTE                                             rgbStack[DRM_PRND_STACK_SIZE];

    /* Determined during Registration and then reused across multiple Proximity Detection and/or License Request/Transmit calls */
    DRM_ID                                               SessionID;
    DRM_PUBLIC_KEY_CONTEXT                               oECC256PubKeyPrndEncryptReceiver;      /* From receiver leaf certificate from registration request. */
    DRM_PUBLIC_KEY_CONTEXT                               oECC256PubKeyContentEncryptReceiver;   /* From receiver leaf certificate from registration request. */
    DRM_DWORD                                            dwReceiverSecurityLevel;               /* From receiver leaf certificate from registration request. [Leaf certificate is verified to not have higher level than any other cert in chain.] */
    DRM_DWORD                                            dwReceiverExpiration;                  /* From receiver certificate chain from registration request. */
    DRM_DWORD                                            dwReceiverRIV;                         /* From registration request directly. */
    DRM_BYTE                                             rgbMIMKEncryptedWithReceiverPubkey[ECC_P256_CIPHERTEXT_SIZE_IN_BYTES];     /* Determined on Tx. */
    OEM_CRYPTO_HANDLE                                    handleMIMK;                            /* Determined on Tx. */
    DRM_GUID                                             guidInitialLicenseMessageID;           /* From registration request directly. */
    DRM_DWORD                                            dwRegistrationRequestFlags;            /* From registration request directly. */
    DRM_BOOL                                             fReceivedRegistrationRequest;          /* Determined on Tx. */
    DRM_PRND_PROXIMITY_DETECTION_TYPE                    eProximityDetectionType;               /* Determined on Tx. */
    DRMFILETIME                                          ftRegistrationTimeoutStart;            /* Determined on Tx. */

    DRM_BOOL                                             fDeviceRegistrationAllowed;                    /* Determined on Tx. */
    DRMFILETIME                                          ftSuccessfulProximity;                         /* Determined on Tx. */
    DRM_BYTE                                             rgbSuccessfulProximitySig[DRM_AES_BLOCKLEN];   /* Determined on Tx. */
    DRM_BOOL                                             fSuccessfulProximityAtLeastOnce;               /* Determined on Tx. */
    DRM_DWORD                                            dwSubtractFromBeginDate;                       /* Determined on Tx based on Rx's current time. */
    DRM_DWORD                                            dwAddToEndDate;                                /* Determined on Tx based on Rx's current time. */

    /* Used only during a single Proximity Detection attempt */
    DRM_PRND_PROXIMITY_DETECTION_STATE                   ePrndProximityDetectionState;
    DRM_UINT64                                           qwProximityStartTimeMilliseconds;
    DRM_RESULT                                           drProximityResult;
    DRM_ID                                               Nonce;

    /* Used across multiple License Request/Transmit calls */
    DRM_GUID                                             guidCurrentLicenseMessageID;
    DRM_BOOL                                             fPRNDLSTOpened;
    DRM_LICSTORE_CONTEXT                                 oLSTContextPRNDStore;
    DRM_DST                                              oDSTContextPRNDStore;
    DRM_EST_CONTEXT                                      oESTContextPRNDStore;
    DRM_BYTE                                             rgbPRNDStore[SIZE_OF_PLAYREADY_EMBEDDED_LICENSE_SPACE];
} DRM_PRND_TRANSMITTER_SESSION_CONTEXT;

typedef struct __tagDRM_PRND_TRANSMITTER_CONTEXT
{
    DRM_PRND_TRANSMITTER_SESSION_CONTEXT                 oPrndTransmitterSessionContext;

    /* From DRM_APP_CONTEXT */
    DRM_BB_CONTEXT                                      *pBBXContext;
    DRM_SECSTORE_CONTEXT                                *pSSTGlobalContext;
    DRM_DST                                             *pDSTContext;
    DRM_REVOCATIONSTORE_CONTEXT                         *pRevocationStoreContext;
    DRM_BYTE                                            *pbRevocationBuffer;
    DRM_DWORD                                            cbRevocationBuffer;
} DRM_PRND_TRANSMITTER_CONTEXT;

typedef struct __tagDRM_PRND_RECEIVER_SESSION_CONTEXT
{
    /* These are internally allocated and freed when the session ends */
    DRM_BYTE                                            *pbTransmitterProximityDetectionChannel;
    DRM_WORD                                             cbTransmitterProximityDetectionChannel;

    /* General members */
    DRM_BYTE                                             rgbStack[DRM_PRND_STACK_SIZE];

    /* Determined during Registration and then reused across multiple Proximity Detection and/or License Request/Transmit calls */
    DRM_ID                                               SessionID;
    DRM_BOOL                                             fInRenewal;                  /* Determined on Rx. */
    DRM_DWORD                                            dwTransmitterExpiration;     /* From transmitter certificate chain from registration response (if present, else DRM_BCERT_DEFAULT_EXPIRATION_DATE). */
    DRM_BYTE                                             rgbMIMKEncryptedWithReceiverPubkey[ECC_P256_CIPHERTEXT_SIZE_IN_BYTES];     /* From registration response directly. */
    OEM_CRYPTO_HANDLE                                    handleMIMK;                  /* Determined on Rx. */
    DRM_GUID                                             guidInitialLicenseMessageID; /* Determined on Rx. */
    DRM_PRND_PROXIMITY_DETECTION_TYPE                    eProximityDetectionType;     /* From registration response directly. */

    /* Used only during a single Proximity Detection attempt */
    DRM_ID                                               Nonce;

    /* Used across multiple License Request/Transmit calls */
    DRM_GUID                                             guidCurrentLicenseMessageID;
    DRM_BOOL                                             fReadyForLicenses;
} DRM_PRND_RECEIVER_SESSION_CONTEXT;

typedef struct __tagDRM_PRND_RECEIVER_CONTEXT
{
    DRM_PRND_RECEIVER_SESSION_CONTEXT                    oPrndReceiverSessionContext;

    /* From DRM_APP_CONTEXT */
    DRM_BB_CONTEXT                                      *pBBXContext;
    DRM_SECSTORE_CONTEXT                                *pSSTGlobalContext;
    DRM_DST                                             *pDSTContext;
    DRM_REVOCATIONSTORE_CONTEXT                         *pRevocationStoreContext;
    DRM_BYTE                                            *pbRevocationBuffer;
    DRM_DWORD                                            cbRevocationBuffer;
    DRM_BOOL                                            *pfPRNDLSTOpened;
    DRM_LICSTORE_CONTEXT                                *pLSTContextPRNDStore;
    DRM_DST                                             *pDSTContextPRNDStore;
    DRM_EST_CONTEXT                                     *pESTContextPRNDStore;
    DRM_BYTE                                            *pbPRNDStore;
    DRM_DWORD                                            cbPRNDStore;
} DRM_PRND_RECEIVER_CONTEXT;

EXIT_PK_NAMESPACE;

#endif /* _DRMPRNDPROTOCOLTYPES_H_ */

