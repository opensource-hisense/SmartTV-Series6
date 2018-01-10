/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef _DRMPRNDFORMAT_H_
#define _DRMPRNDFORMAT_H_

#include <drmpragmas.h>
#include <drmxbbuilder.h>
#include <oemcryptoctx.h>
#include <drmprndprotocoltypes.h>

ENTER_PK_NAMESPACE;

#define DRM_PRND_CURRENT_VERSION          1

#define DRM_CHECK_CUSTOM_DATA_TYPE( customDataType )                                        \
    ChkBOOL(                                                                                \
            (customDataType) == NULL                                                        \
        ||  ((DRM_BYTE*)(customDataType))[0] != 'M'                                         \
        ||  ((DRM_BYTE*)(customDataType))[1] != 'S'                                         \
        ||  ((DRM_BYTE*)(customDataType))[2] != 'F'                                         \
        ||  ((DRM_BYTE*)(customDataType))[3] != 'T',                                        \
         DRM_E_PRND_INVALID_CUSTOM_DATA_TYPE )

/******************************************************************************
**
** PRND Object Types for all messages
**
******************************************************************************/

typedef enum
{
    DRM_PRND_ENTRY_TYPE_REGISTRATION_REQUEST_BASIC_INFORMATION                  = 0x01,
    DRM_PRND_ENTRY_TYPE_REGISTRATION_REQUEST_CUSTOM_DATA                        = 0x02,
    DRM_PRND_ENTRY_TYPE_REGISTRATION_REQUEST_SIGNATURE                          = 0x03,
} DRM_PRND_ENTRY_REGISTRATION_REQUEST_TYPES;
/* Count Includes XB_OBJECT_GLOBAL_HEADER */
#define DRM_PRND_ENTRY_TYPE_REGISTRATION_REQUEST_OBJECT_TYPE_COUNT              4
#define DRM_PRND_REGISTRATION_REQUEST_MESSAGE_FORMAT_ID                         XB_DEFINE_QWORD_FORMAT_ID( 'P','R','N','D','R','E','G','R' )

typedef enum
{
    DRM_PRND_ENTRY_TYPE_REGISTRATION_RESPONSE_BASIC_INFORMATION                 = 0x04,
    DRM_PRND_ENTRY_TYPE_REGISTRATION_RESPONSE_PROXIMITY_INFORMATION             = 0x05,
    DRM_PRND_ENTRY_TYPE_REGISTRATION_RESPONSE_CUSTOM_DATA                       = 0x06,
    DRM_PRND_ENTRY_TYPE_REGISTRATION_RESPONSE_SIGNATURE                         = 0x07,
    DRM_PRND_ENTRY_TYPE_REGISTRATION_RESPONSE_TRANSMITTER_AUTH                  = 0x17,
} DRM_PRND_ENTRY_REGISTRATION_RESPONSE_TYPES;
/* Count Includes XB_OBJECT_GLOBAL_HEADER */
#define DRM_PRND_ENTRY_TYPE_REGISTRATION_RESPONSE_OBJECT_TYPE_COUNT             6
#define DRM_PRND_REGISTRATION_RESPONSE_MESSAGE_FORMAT_ID                        XB_DEFINE_QWORD_FORMAT_ID( 'P','R','N','D','R','E','G','S' )

typedef enum
{
    DRM_PRND_ENTRY_TYPE_REGISTRATION_ERROR_BASIC_INFORMATION                    = 0x08,
} DRM_PRND_ENTRY_REGISTRATION_ERROR_TYPES;
/* Count Includes XB_OBJECT_GLOBAL_HEADER */
#define DRM_PRND_ENTRY_TYPE_REGISTRATION_ERROR_OBJECT_TYPE_COUNT                2
#define DRM_PRND_REGISTRATION_ERROR_MESSAGE_FORMAT_ID                           XB_DEFINE_QWORD_FORMAT_ID( 'P','R','N','D','R','E','G','E' )

typedef enum
{
    DRM_PRND_ENTRY_TYPE_PROXIMITY_DETECTION_START_BASIC_INFORMATION             = 0x09,
} DRM_PRND_ENTRY_PROXIMITY_DETECTION_START_TYPES;
/* Count Includes XB_OBJECT_GLOBAL_HEADER */
#define DRM_PRND_ENTRY_TYPE_PROXIMITY_DETECTION_START_OBJECT_TYPE_COUNT         2
#define DRM_PRND_PROXIMITY_DETECTION_START_MESSAGE_FORMAT_ID                    XB_DEFINE_QWORD_FORMAT_ID( 'P','R','N','D','P','X','S','T' )

typedef enum
{
    DRM_PRND_ENTRY_TYPE_PROXIMITY_DETECTION_CHALLENGE_BASIC_INFORMATION         = 0x0A,
} DRM_PRND_ENTRY_PROXIMITY_DETECTION_CHALLENGE_TYPES;
/* Count Includes XB_OBJECT_GLOBAL_HEADER */
#define DRM_PRND_ENTRY_TYPE_PROXIMITY_DETECTION_CHALLENGE_OBJECT_TYPE_COUNT     2
#define DRM_PRND_PROXIMITY_DETECTION_CHALLENGE_MESSAGE_FORMAT_ID                XB_DEFINE_QWORD_FORMAT_ID( 'P','R','N','D','P','X','C','H' )

typedef enum
{
    DRM_PRND_ENTRY_TYPE_PROXIMITY_DETECTION_RESPONSE_BASIC_INFORMATION          = 0x0B,
} DRM_PRND_ENTRY_PROXIMITY_DETECTION_RESPONSE_TYPES;
/* Count Includes XB_OBJECT_GLOBAL_HEADER */
#define DRM_PRND_ENTRY_TYPE_PROXIMITY_DETECTION_RESPONSE_OBJECT_TYPE_COUNT      2
#define DRM_PRND_PROXIMITY_DETECTION_RESPONSE_MESSAGE_FORMAT_ID                 XB_DEFINE_QWORD_FORMAT_ID( 'P','R','N','D','P','X','R','S' )

typedef enum
{
    DRM_PRND_ENTRY_TYPE_PROXIMITY_DETECTION_RESULT_BASIC_INFORMATION            = 0x0C,
} DRM_PRND_ENTRY_PROXIMITY_DETECTION_RESULT_TYPES;
/* Count Includes XB_OBJECT_GLOBAL_HEADER */
#define DRM_PRND_ENTRY_TYPE_PROXIMITY_DETECTION_RESULT_OBJECT_TYPE_COUNT        2
#define DRM_PRND_PROXIMITY_DETECTION_RESULT_MESSAGE_FORMAT_ID                   XB_DEFINE_QWORD_FORMAT_ID( 'P','R','N','D','P','X','R','T' )

typedef enum
{
    DRM_PRND_ENTRY_TYPE_LICENSE_REQUEST_BASIC_INFORMATION                       = 0x0D,
    DRM_PRND_ENTRY_TYPE_LICENSE_REQUEST_LICENSE_INFORMATION                     = 0x0E,
    DRM_PRND_ENTRY_TYPE_LICENSE_REQUEST_CUSTOM_DATA                             = 0x0F,
    DRM_PRND_ENTRY_TYPE_LICENSE_REQUEST_SIGNATURE                               = 0x10,
} DRM_PRND_ENTRY_LICENSE_REQUEST_TYPES;
/* Count Includes XB_OBJECT_GLOBAL_HEADER */
#define DRM_PRND_ENTRY_TYPE_LICENSE_REQUEST_OBJECT_TYPE_COUNT                   5
#define DRM_PRND_LICENSE_REQUEST_MESSAGE_FORMAT_ID                              XB_DEFINE_QWORD_FORMAT_ID( 'P','R','N','D','L','I','C','R' )

typedef enum
{
    DRM_PRND_ENTRY_TYPE_LICENSE_TRANSMIT_BASIC_INFORMATION                      = 0x11,
    DRM_PRND_ENTRY_TYPE_LICENSE_TRANSMIT_LICENSE_LIST                           = 0x12,
    DRM_PRND_ENTRY_TYPE_LICENSE_TRANSMIT_LICENSE_INFORMATION                    = 0x13,
    DRM_PRND_ENTRY_TYPE_LICENSE_TRANSMIT_CUSTOM_DATA                            = 0x14,
    DRM_PRND_ENTRY_TYPE_LICENSE_TRANSMIT_SIGNATURE                              = 0x15,
} DRM_PRND_ENTRY_LICENSE_TRANSMIT_TYPES;
/* Count Includes XB_OBJECT_GLOBAL_HEADER */
#define DRM_PRND_ENTRY_TYPE_LICENSE_TRANSMIT_OBJECT_TYPE_COUNT                  6
#define DRM_PRND_LICENSE_TRANSMIT_MESSAGE_FORMAT_ID                             XB_DEFINE_QWORD_FORMAT_ID( 'P','R','N','D','L','I','C','T' )

typedef enum
{
    DRM_PRND_ENTRY_TYPE_LICENSE_ERROR_BASIC_INFORMATION                         = 0x16,
} DRM_PRND_ENTRY_LICENSE_ERROR_TYPES;
/* Count Includes XB_OBJECT_GLOBAL_HEADER */
#define DRM_PRND_ENTRY_TYPE_LICENSE_ERROR_OBJECT_TYPE_COUNT                     2
#define DRM_PRND_LICENSE_ERROR_MESSAGE_FORMAT_ID                                XB_DEFINE_QWORD_FORMAT_ID( 'P','R','N','D','L','I','C','E' )

typedef enum
{
    DRM_PRND_MESSAGE_TYPE_INVALID                       =  0,
    DRM_PRND_MESSAGE_TYPE_REGISTRATION_REQUEST          =  1,
    DRM_PRND_MESSAGE_TYPE_REGISTRATION_RESPONSE         =  2,
    DRM_PRND_MESSAGE_TYPE_REGISTRATION_ERROR            =  3,
    DRM_PRND_MESSAGE_TYPE_PROXIMITY_DETECTION_START     =  4,
    DRM_PRND_MESSAGE_TYPE_PROXIMITY_DETECTION_CHALLENGE =  5,
    DRM_PRND_MESSAGE_TYPE_PROXIMITY_DETECTION_RESPONSE  =  6,
    DRM_PRND_MESSAGE_TYPE_PROXIMITY_DETECTION_RESULT    =  7,
    DRM_PRND_MESSAGE_TYPE_LICENSE_REQUEST               =  8,
    DRM_PRND_MESSAGE_TYPE_LICENSE_TRANSMIT              =  9,
    DRM_PRND_MESSAGE_TYPE_LICENSE_ERROR                 = 10,
} DRM_PRND_MESSAGE_TYPE;

/******************************************************************************
**
** PRND format utility functions
**
******************************************************************************/
DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_PRND_TxRx_GetMessageType(
    __inout_bcount( f_cbUnknownMessage )                        const DRM_BYTE                                         *f_pbUnknownMessage,
    __in                                                              DRM_DWORD                                         f_cbUnknownMessage,
    __out                                                             DRM_PRND_MESSAGE_TYPE                            *f_peMessageType ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_VOID DRM_CALL DRM_PRND_TxRx_IncrementLMID(
    __inout_ecount( 1 )                                               DRM_GUID                                         *f_pguidLMID ) DRM_NO_INLINE_ATTRIBUTE;

/******************************************************************************
**
** PRND Message Signatures
**
******************************************************************************/
#define DRM_PRND_SIGNATURE_SIZE_AES_OMAC1_MI                    DRM_AES_BLOCKLEN
#define DRM_PRND_SIGNATURE_SIZE_ECC256_RECEIVER_SIGNING_KEY     ECDSA_P256_SIGNATURE_SIZE_IN_BYTES

typedef enum
{
    DRM_PRND_SIGNATURE_OPERATION_INVALID,
    DRM_PRND_SIGNATURE_OPERATION_SIGN_USING_ECC256_RECEIVER_SIGNING_KEY,
    DRM_PRND_SIGNATURE_OPERATION_VERIFY_USING_ECC256_RECEIVER_SIGNING_KEY,
    DRM_PRND_SIGNATURE_OPERATION_SIGN_USING_AES_OMAC1_WITH_MI,
    DRM_PRND_SIGNATURE_OPERATION_VERIFY_USING_AES_OMAC1_WITH_MI,
} DRM_PRND_SIGNATURE_OPERATION;

PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_NONCONST_PARAM_25004, "Prefast Noise: Callback contexts should never be const")
typedef DRM_RESULT ( DRM_CALL *DRM_PRND_FORMAT_SIGNATURE_CB )(
    __in_ecount( 1 )                      DRM_VOID                                      *f_pvSignatureContext,
    __in                                  DRM_PRND_SIGNATURE_OPERATION                   f_eSignatureOperation,
    __in_bcount( f_cbData )         const DRM_BYTE                                      *f_pbData,
    __in                                  DRM_DWORD                                      f_cbData,
    __out_bcount( f_cbSignatureBuffer )   DRM_BYTE                                      *f_pbSignatureBuffer,
    __in                                  DRM_DWORD                                      f_cbSignatureBuffer,
    __in                                  DRM_DWORD                                      f_iSignatureBuffer,
    __in_opt                        const DRM_XB_BYTEARRAY                              *f_pxbbaMIMKEncryptedWithReceiverPubkey,        /* Only used for DRM_PRND_SIGNATURE_OPERATION_VERIFY_USING_AES_OMAC1_WITH_MI    */
    __in_opt                        const DRM_XB_BYTEARRAY                              *f_pxbbaReceiverCertificate );                  /* Only used for DRM_PRND_SIGNATURE_OPERATION_VERIFY_USING_ECC256_RECEIVER_SIGNING_KEY */
PREFAST_POP /* __WARNING_NONCONST_PARAM_25004 */

/******************************************************************************
**
** PRND Signature shared structure
**
******************************************************************************/
typedef struct __tagDRM_PRND_MESSAGE_SIGNATURE
{
    DRM_BOOL                  fValid;
    DRM_WORD                  wSignatureType;           /* Member of DRM_PRND_SIGNATURE_TYPE enum */
    DRM_XB_BYTEARRAY          xbbaSignature;
} DRM_PRND_MESSAGE_SIGNATURE;

/******************************************************************************
**
** PRND Custom Data shared structure
**
******************************************************************************/
typedef struct __tagDRM_PRND_CUSTOM_DATA
{
    DRM_BOOL            fValid;
    DRM_ID              customDataTypeID;
    DRM_XB_BYTEARRAY    xbbaCustomData;
} DRM_PRND_CUSTOM_DATA;

/******************************************************************************
**
** PRND Registration Request Message [RX->TX]
**
******************************************************************************/
typedef struct __tagDRM_PRND_REGISTRATION_REQUEST_BASIC_INFORMATION
{
    DRM_BOOL            fValid;
    DRM_DWORD           dwFlags;
    DRM_GUID            guidPreviousSessionID;
    DRM_XB_BYTEARRAY    xbbaReceiverCertificate;
    DRM_DWORD           dwReceiverRIV;
    DRM_DWORD           dwSupportedProximityDetectionTypes;     /* Bitmask of DRM_PRND_PROXIMITY_DETECTION_TYPE enum(s) */
    DRM_GUID            guidInitialLicenseMessageID;
    DRM_UINT64          qwReceiverCurrentTime;
} DRM_PRND_REGISTRATION_REQUEST_BASIC_INFORMATION;

typedef struct __tagDRM_DRM_PRND_REGISTRATION_REQUEST_MESSAGE
{
    DRM_BOOL                                        fValid;
    DRM_PRND_REGISTRATION_REQUEST_BASIC_INFORMATION BasicInformation;
    DRM_PRND_CUSTOM_DATA                            CustomData;
    DRM_PRND_MESSAGE_SIGNATURE                      Signature;
} DRM_PRND_REGISTRATION_REQUEST_MESSAGE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_PRND_RegistrationRequestMessage_Start(
    __inout_bcount( f_cbStack )           DRM_BYTE                                      *f_pbStack,
    __in                                  DRM_DWORD                                      f_cbStack,
    __inout_ecount( 1 )                   DRM_XB_BUILDER_CONTEXT                        *f_pcontextBuilder ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_PRND_RegistrationRequestMessage_Finish(
    __in_ecount( 1 )                const DRM_XB_BUILDER_CONTEXT                        *f_pcontextBuilder,
    __inout_bcount( *f_pcbMessage )       DRM_BYTE                                      *f_pbMessage,
    __inout                               DRM_DWORD                                     *f_pcbMessage,
    __in                                  DRM_PRND_FORMAT_SIGNATURE_CB                   f_pfnSignatureCallback,    /* Must support at least DRM_PRND_SIGNATURE_OPERATION_SIGN_USING_ECC256_RECEIVER_SIGNING_KEY */
    __in                                  DRM_VOID                                      *f_pvSignatureContext ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_PRND_RegistrationRequestMessage_Parse(
    __inout_bcount( f_cbStack )           DRM_BYTE                                      *f_pbStack,
    __in                                  DRM_DWORD                                      f_cbStack,
    __inout_bcount( f_cbMessage )   const DRM_BYTE                                      *f_pbMessage,
    __in                                  DRM_DWORD                                      f_cbMessage,
    __out                                 DRM_PRND_REGISTRATION_REQUEST_MESSAGE         *f_pMessage,
    __in                                  DRM_PRND_FORMAT_SIGNATURE_CB                   f_pfnSignatureCallback,    /* Must support at least DRM_PRND_SIGNATURE_OPERATION_VERIFY_USING_ECC256_RECEIVER_SIGNING_KEY */
    __in                                  DRM_VOID                                      *f_pvSignatureContext ) DRM_NO_INLINE_ATTRIBUTE;

/******************************************************************************
**
** PRND Registration Response Message [TX->RX]
**
******************************************************************************/
typedef struct __tagDRM_PRND_REGISTRATION_RESPONSE_BASIC_INFORMATION
{
    DRM_BOOL            fValid;
    DRM_DWORD           dwFlags;
    DRM_GUID            guidSessionID;
    DRM_XB_BYTEARRAY    xbbaTransmitterRevInfo;
    DRM_WORD            wMIMKEncryptionType;                    /* Member of DRM_PRND_ENCRYPTION_TYPE enum */
    DRM_XB_BYTEARRAY    xbbaMIMKEncryptedWithReceiverPubkey;
} DRM_PRND_REGISTRATION_RESPONSE_BASIC_INFORMATION;

typedef struct __tagDRM_PRND_REGISTRATION_RESPONSE_PROXIMITY_INFORMATION
{
    DRM_BOOL            fValid;
    DRM_DWORD           dwProximityDetectionType;               /* Member of DRM_PRND_PROXIMITY_DETECTION_TYPE enum */
    DRM_XB_BYTEARRAY    xbbaTransmitterProximityDetectionChannel;
} DRM_PRND_REGISTRATION_RESPONSE_PROXIMITY_INFORMATION;

typedef struct __tagDRM_PRND_REGISTRATION_RESPONSE_TRANSMITTER_AUTH
{
    DRM_BOOL            fValid;
    DRM_XB_BYTEARRAY    xbbaTransmitterCertificate;
    DRM_WORD            wTransmitterAuthSignatureType;        /* Member of DRM_PRND_SIGNATURE_TYPE enum */
    DRM_XB_BYTEARRAY    xbbaTransmitterAuthSignature;
} DRM_PRND_REGISTRATION_RESPONSE_TRANSMITTER_AUTH;

typedef struct __tagDRM_PRND_REGISTRATION_RESPONSE_MESSAGE
{
    DRM_BOOL                                                fValid;
    DRM_PRND_REGISTRATION_RESPONSE_BASIC_INFORMATION        BasicInformation;
    DRM_PRND_REGISTRATION_RESPONSE_PROXIMITY_INFORMATION    ProximityInformation;
    DRM_PRND_REGISTRATION_RESPONSE_TRANSMITTER_AUTH         TransmitterAuth;
    DRM_PRND_CUSTOM_DATA                                    CustomData;
    DRM_PRND_MESSAGE_SIGNATURE                              Signature;
} DRM_PRND_REGISTRATION_RESPONSE_MESSAGE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_PRND_RegistrationResponseMessage_Start(
    __inout_bcount( f_cbStack )           DRM_BYTE                                      *f_pbStack,
    __in                                  DRM_DWORD                                      f_cbStack,
    __inout_ecount( 1 )                   DRM_XB_BUILDER_CONTEXT                        *f_pcontextBuilder ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_PRND_RegistrationResponseMessage_Finish(
    __in_ecount( 1 )                const DRM_XB_BUILDER_CONTEXT                        *f_pcontextBuilder,
    __inout_bcount( *f_pcbMessage )       DRM_BYTE                                      *f_pbMessage,
    __inout                               DRM_DWORD                                     *f_pcbMessage,
    __in                                  DRM_PRND_FORMAT_SIGNATURE_CB                   f_pfnSignatureCallback,    /* Must support at least DRM_PRND_SIGNATURE_OPERATION_SIGN_USING_AES_OMAC1_WITH_MI */
    __in                                  DRM_VOID                                      *f_pvSignatureContext ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_PRND_RegistrationResponseMessage_Parse(
    __inout_bcount( f_cbStack )           DRM_BYTE                                      *f_pbStack,
    __in                                  DRM_DWORD                                      f_cbStack,
    __inout_bcount( f_cbMessage )   const DRM_BYTE                                      *f_pbMessage,
    __in                                  DRM_DWORD                                      f_cbMessage,
    __out                                 DRM_PRND_REGISTRATION_RESPONSE_MESSAGE        *f_pMessage,
    __in                                  DRM_PRND_FORMAT_SIGNATURE_CB                   f_pfnSignatureCallback,    /* Must support at least DRM_PRND_SIGNATURE_OPERATION_VERIFY_USING_AES_OMAC1_WITH_MI */
    __in                                  DRM_VOID                                      *f_pvSignatureContext ) DRM_NO_INLINE_ATTRIBUTE;

/******************************************************************************
**
** PRND Registration Error Message [TX->RX]
**
******************************************************************************/
typedef struct __tagDRM_PRND_REGISTRATION_ERROR_BASIC_INFORMATION
{
    DRM_BOOL    fValid;
    DRM_DWORD   dwFlags;
    DRM_DWORD   dwResult;
} DRM_PRND_REGISTRATION_ERROR_BASIC_INFORMATION;

typedef struct __tagDRM_PRND_REGISTRATION_ERROR_MESSAGE
{
    DRM_BOOL                                        fValid;
    DRM_PRND_REGISTRATION_ERROR_BASIC_INFORMATION   BasicInformation;
} DRM_PRND_REGISTRATION_ERROR_MESSAGE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_PRND_RegistrationErrorMessage_Start(
    __inout_bcount( f_cbStack )           DRM_BYTE                                      *f_pbStack,
    __in                                  DRM_DWORD                                      f_cbStack,
    __inout_ecount( 1 )                   DRM_XB_BUILDER_CONTEXT                        *f_pcontextBuilder ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_PRND_RegistrationErrorMessage_Finish(
    __in_ecount( 1 )                const DRM_XB_BUILDER_CONTEXT                        *f_pcontextBuilder,
    __inout_bcount( *f_pcbMessage )       DRM_BYTE                                      *f_pbMessage,
    __inout                               DRM_DWORD                                     *f_pcbMessage ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_PRND_RegistrationErrorMessage_Parse(
    __inout_bcount( f_cbStack )           DRM_BYTE                                      *f_pbStack,
    __in                                  DRM_DWORD                                      f_cbStack,
    __inout_bcount( f_cbMessage )   const DRM_BYTE                                      *f_pbMessage,
    __in                                  DRM_DWORD                                      f_cbMessage,
    __out                                 DRM_PRND_REGISTRATION_ERROR_MESSAGE           *f_pMessage ) DRM_NO_INLINE_ATTRIBUTE;

/******************************************************************************
**
** PRND Proximity Detection Start Messasge [RX->TX]
**
******************************************************************************/
typedef struct __tagDRM_PRND_PROXIMITY_DETECTION_START_BASIC_INFORMATION
{
    DRM_BOOL    fValid;
    DRM_DWORD   dwFlags;
    DRM_GUID    guidSessionID;
} DRM_PRND_PROXIMITY_DETECTION_START_BASIC_INFORMATION;

typedef struct __tagDRM_PRND_PROXIMITY_DETECTION_START_MESSAGE
{
    DRM_BOOL                                             fValid;
    DRM_PRND_PROXIMITY_DETECTION_START_BASIC_INFORMATION BasicInformation;
} DRM_PRND_PROXIMITY_DETECTION_START_MESSAGE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_PRND_ProximityDetectionStartMessage_Start(
    __inout_bcount( f_cbStack )           DRM_BYTE                                      *f_pbStack,
    __in                                  DRM_DWORD                                      f_cbStack,
    __inout_ecount( 1 )                   DRM_XB_BUILDER_CONTEXT                        *f_pcontextBuilder ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_PRND_ProximityDetectionStartMessage_Finish(
    __in_ecount( 1 )                const DRM_XB_BUILDER_CONTEXT                        *f_pcontextBuilder,
    __inout_bcount( *f_pcbMessage )       DRM_BYTE                                      *f_pbMessage,
    __inout                               DRM_DWORD                                     *f_pcbMessage ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_PRND_ProximityDetectionStartMessage_Parse(
    __inout_bcount( f_cbStack )           DRM_BYTE                                      *f_pbStack,
    __in                                  DRM_DWORD                                      f_cbStack,
    __inout_bcount( f_cbMessage )   const DRM_BYTE                                      *f_pbMessage,
    __in                                  DRM_DWORD                                      f_cbMessage,
    __out                                 DRM_PRND_PROXIMITY_DETECTION_START_MESSAGE    *f_pMessage ) DRM_NO_INLINE_ATTRIBUTE;

/******************************************************************************
**
** PRND Proximity Detection Challenge Messasge [TX->RX]
**
******************************************************************************/
typedef struct __tagDRM_PRND_PROXIMITY_DETECTION_CHALLENGE_BASIC_INFORMATION
{
    DRM_BOOL    fValid;
    DRM_DWORD   dwFlags;
    DRM_GUID    guidSessionID;
    DRM_GUID    guidNonce;
} DRM_PRND_PROXIMITY_DETECTION_CHALLENGE_BASIC_INFORMATION;

typedef struct __tagDRM_PRND_PROXIMITY_DETECTION_CHALLENGE_MESSAGE
{
    DRM_BOOL                                                 fValid;
    DRM_PRND_PROXIMITY_DETECTION_CHALLENGE_BASIC_INFORMATION BasicInformation;
} DRM_PRND_PROXIMITY_DETECTION_CHALLENGE_MESSAGE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_PRND_ProximityDetectionChallengeMessage_Start(
    __inout_bcount( f_cbStack )           DRM_BYTE                                      *f_pbStack,
    __in                                  DRM_DWORD                                      f_cbStack,
    __inout_ecount( 1 )                   DRM_XB_BUILDER_CONTEXT                        *f_pcontextBuilder ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_PRND_ProximityDetectionChallengeMessage_Finish(
    __in_ecount( 1 )                const DRM_XB_BUILDER_CONTEXT                        *f_pcontextBuilder,
    __inout_bcount( *f_pcbMessage )       DRM_BYTE                                      *f_pbMessage,
    __inout                               DRM_DWORD                                     *f_pcbMessage ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_PRND_ProximityDetectionChallengeMessage_Parse(
    __inout_bcount( f_cbStack )           DRM_BYTE                                          *f_pbStack,
    __in                                  DRM_DWORD                                          f_cbStack,
    __inout_bcount( f_cbMessage )   const DRM_BYTE                                          *f_pbMessage,
    __in                                  DRM_DWORD                                          f_cbMessage,
    __out                                 DRM_PRND_PROXIMITY_DETECTION_CHALLENGE_MESSAGE    *f_pMessage ) DRM_NO_INLINE_ATTRIBUTE;

/******************************************************************************
**
** PRND Proximity Detection Response Messasge [RX->TX]
**
******************************************************************************/
typedef struct __tagDRM_PRND_PROXIMITY_DETECTION_RESPONSE_BASIC_INFORMATION
{
    DRM_BOOL    fValid;
    DRM_DWORD   dwFlags;
    DRM_GUID    guidSessionID;
    DRM_WORD    wNonceEncryptionType;               /* Member of DRM_PRND_ENCRYPTION_TYPE enum */
    DRM_GUID    guidNonceEncryptedWithMK;
} DRM_PRND_PROXIMITY_DETECTION_RESPONSE_BASIC_INFORMATION;

typedef struct __tagDRM_PRND_PROXIMITY_DETECTION_RESPONSE_MESSAGE
{
    DRM_BOOL                                                fValid;
    DRM_PRND_PROXIMITY_DETECTION_RESPONSE_BASIC_INFORMATION BasicInformation;
} DRM_PRND_PROXIMITY_DETECTION_RESPONSE_MESSAGE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_PRND_ProximityDetectionResponseMessage_Start(
    __inout_bcount( f_cbStack )           DRM_BYTE                                      *f_pbStack,
    __in                                  DRM_DWORD                                      f_cbStack,
    __inout_ecount( 1 )                   DRM_XB_BUILDER_CONTEXT                        *f_pcontextBuilder ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_PRND_ProximityDetectionResponseMessage_Finish(
    __in_ecount( 1 )                const DRM_XB_BUILDER_CONTEXT                        *f_pcontextBuilder,
    __inout_bcount( *f_pcbMessage )       DRM_BYTE                                      *f_pbMessage,
    __inout                               DRM_DWORD                                     *f_pcbMessage ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_PRND_ProximityDetectionResponseMessage_Parse(
    __inout_bcount( f_cbStack )           DRM_BYTE                                      *f_pbStack,
    __in                                  DRM_DWORD                                      f_cbStack,
    __inout_bcount( f_cbMessage )   const DRM_BYTE                                      *f_pbMessage,
    __in                                  DRM_DWORD                                      f_cbMessage,
    __out                                 DRM_PRND_PROXIMITY_DETECTION_RESPONSE_MESSAGE *f_pMessage ) DRM_NO_INLINE_ATTRIBUTE;

/******************************************************************************
**
** PRND Proximity Detection Result Messasge [TX->RX]
**
******************************************************************************/
typedef struct __tagDRM_PRND_PROXIMITY_DETECTION_RESULT_BASIC_INFORMATION
{
    DRM_BOOL    fValid;
    DRM_DWORD   dwFlags;
    DRM_GUID    guidSessionID;
    DRM_DWORD   dwResult;
} DRM_PRND_PROXIMITY_DETECTION_RESULT_BASIC_INFORMATION;

typedef struct __tagDRM_PRND_PROXIMITY_DETECTION_RESULT_MESSAGE
{
    DRM_BOOL                                              fValid;
    DRM_PRND_PROXIMITY_DETECTION_RESULT_BASIC_INFORMATION BasicInformation;
} DRM_PRND_PROXIMITY_DETECTION_RESULT_MESSAGE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_PRND_ProximityDetectionResultMessage_Start(
    __inout_bcount( f_cbStack )           DRM_BYTE                                      *f_pbStack,
    __in                                  DRM_DWORD                                      f_cbStack,
    __inout_ecount( 1 )                   DRM_XB_BUILDER_CONTEXT                        *f_pcontextBuilder ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_PRND_ProximityDetectionResultMessage_Finish(
    __in_ecount( 1 )                const DRM_XB_BUILDER_CONTEXT                        *f_pcontextBuilder,
    __inout_bcount( *f_pcbMessage )       DRM_BYTE                                      *f_pbMessage,
    __inout                               DRM_DWORD                                     *f_pcbMessage ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_PRND_ProximityDetectionResultMessage_Parse(
    __inout_bcount( f_cbStack )           DRM_BYTE                                      *f_pbStack,
    __in                                  DRM_DWORD                                      f_cbStack,
    __inout_bcount( f_cbMessage )   const DRM_BYTE                                      *f_pbMessage,
    __in                                  DRM_DWORD                                      f_cbMessage,
    __out                                 DRM_PRND_PROXIMITY_DETECTION_RESULT_MESSAGE   *f_pMessage ) DRM_NO_INLINE_ATTRIBUTE;

/******************************************************************************
**
** PRND License Request Messasge [RX->TX]
**
******************************************************************************/
typedef struct __tagDRM_PRND_LICENSE_REQUEST_BASIC_INFORMATION
{
    DRM_BOOL    fValid;
    DRM_DWORD   dwFlags;
    DRM_GUID    guidSessionID;
    DRM_DWORD   dwReceiverRIV;
} DRM_PRND_LICENSE_REQUEST_BASIC_INFORMATION;

typedef struct __tagDRM_PRND_LICENSE_REQUEST_LICENSE_INFORMATION
{
    DRM_BOOL            fValid;
    DRM_WORD            wRequestedAction;                   /* Member of DRM_PRND_ACTION enum */
    DRM_WORD            wRequestedActionQualifier;          /* Member of DRM_PRND_ACTION_QUALIFIER enum */
    DRM_WORD            wContentIdentifierType;             /* Member of DRM_PRND_CONTENT_IDENTIFIER_TYPE enum */
    DRM_XB_BYTEARRAY    xbbaContentIdentifier;
} DRM_PRND_LICENSE_REQUEST_LICENSE_INFORMATION;

typedef struct __tagDRM_PRND_LICENSE_REQUEST_MESSAGE
{
    DRM_BOOL                                        fValid;
    DRM_PRND_LICENSE_REQUEST_BASIC_INFORMATION      BasicInformation;
    DRM_PRND_LICENSE_REQUEST_LICENSE_INFORMATION    LicenseInformation;
    DRM_PRND_CUSTOM_DATA                            CustomData;
    DRM_PRND_MESSAGE_SIGNATURE                      Signature;
} DRM_PRND_LICENSE_REQUEST_MESSAGE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_PRND_LicenseRequestMessage_Start(
    __inout_bcount( f_cbStack )           DRM_BYTE                                      *f_pbStack,
    __in                                  DRM_DWORD                                      f_cbStack,
    __inout_ecount( 1 )                   DRM_XB_BUILDER_CONTEXT                        *f_pcontextBuilder ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_PRND_LicenseRequestMessage_Finish(
    __in_ecount( 1 )                const DRM_XB_BUILDER_CONTEXT                        *f_pcontextBuilder,
    __inout_bcount( *f_pcbMessage )       DRM_BYTE                                      *f_pbMessage,
    __inout                               DRM_DWORD                                     *f_pcbMessage,
    __in                                  DRM_PRND_FORMAT_SIGNATURE_CB                   f_pfnSignatureCallback,    /* Must support at least DRM_PRND_SIGNATURE_OPERATION_SIGN_USING_AES_OMAC1_WITH_MI */
    __in                                  DRM_VOID                                      *f_pvSignatureContext ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_PRND_LicenseRequestMessage_Parse(
    __inout_bcount( f_cbStack )           DRM_BYTE                                      *f_pbStack,
    __in                                  DRM_DWORD                                      f_cbStack,
    __inout_bcount( f_cbMessage )   const DRM_BYTE                                      *f_pbMessage,
    __in                                  DRM_DWORD                                      f_cbMessage,
    __out                                 DRM_PRND_LICENSE_REQUEST_MESSAGE              *f_pMessage,
    __in                                  DRM_PRND_FORMAT_SIGNATURE_CB                   f_pfnSignatureCallback,    /* Must support at least DRM_PRND_SIGNATURE_OPERATION_VERIFY_USING_AES_OMAC1_WITH_MI */
    __in                                  DRM_VOID                                      *f_pvSignatureContext ) DRM_NO_INLINE_ATTRIBUTE;

/******************************************************************************
**
** PRND License Transmit Messasge [TX->RX]
**
******************************************************************************/
typedef struct __tagDRM_PRND_LICENSE_TRANSMIT_BASIC_INFORMATION
{
    DRM_BOOL            fValid;
    DRM_DWORD           dwFlags;
    DRM_GUID            guidSessionID;
    DRM_GUID            guidCurrentLicenseMessageID;
    DRM_XB_BYTEARRAY    xbbaTransmitterRevInfo;
} DRM_PRND_LICENSE_TRANSMIT_BASIC_INFORMATION;

typedef struct __tagDRM_PRND_LICENSE_TRANSMIT_LICENSE_INFORMATION
{
    DRM_BOOL                                                    fValid;
    struct __tagDRM_PRND_LICENSE_TRANSMIT_LICENSE_INFORMATION  *pNext;

    DRM_XB_BYTEARRAY                                            xbbaReceiverBoundOrLeafXMRLicense;
} DRM_PRND_LICENSE_TRANSMIT_LICENSE_INFORMATION;

typedef struct __tagDRM_PRND_LICENSE_TRANSMIT_LICENSE_LIST
{
    DRM_BOOL                                         fValid;
    DRM_PRND_LICENSE_TRANSMIT_LICENSE_INFORMATION   *pLicenseListHead;
} DRM_PRND_LICENSE_TRANSMIT_LICENSE_LIST;

typedef struct __tagDRM_PRND_LICENSE_TRANSMIT_MESSAGE
{
    DRM_BOOL                                    fValid;
    DRM_PRND_LICENSE_TRANSMIT_BASIC_INFORMATION BasicInformation;
    DRM_PRND_LICENSE_TRANSMIT_LICENSE_LIST      LicenseList;
    DRM_PRND_CUSTOM_DATA                        CustomData;
    DRM_PRND_MESSAGE_SIGNATURE                  Signature;
} DRM_PRND_LICENSE_TRANSMIT_MESSAGE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_PRND_LicenseTransmitMessage_Start(
    __inout_bcount( f_cbStack )           DRM_BYTE                                      *f_pbStack,
    __in                                  DRM_DWORD                                      f_cbStack,
    __inout_ecount( 1 )                   DRM_XB_BUILDER_CONTEXT                        *f_pcontextBuilder ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_PRND_LicenseTransmitMessage_Finish(
    __in_ecount( 1 )                const DRM_XB_BUILDER_CONTEXT                        *f_pcontextBuilder,
    __inout_bcount( *f_pcbMessage )       DRM_BYTE                                      *f_pbMessage,
    __inout                               DRM_DWORD                                     *f_pcbMessage,
    __in                                  DRM_PRND_FORMAT_SIGNATURE_CB                   f_pfnSignatureCallback,
    __in                                  DRM_VOID                                      *f_pvSignatureContext ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_PRND_LicenseTransmitMessage_Parse(
    __inout_bcount( f_cbStack )           DRM_BYTE                                      *f_pbStack,
    __in                                  DRM_DWORD                                      f_cbStack,
    __inout_bcount( f_cbMessage )   const DRM_BYTE                                      *f_pbMessage,
    __in                                  DRM_DWORD                                      f_cbMessage,
    __out                                 DRM_PRND_LICENSE_TRANSMIT_MESSAGE             *f_pMessage,
    __in                                  DRM_PRND_FORMAT_SIGNATURE_CB                   f_pfnSignatureCallback,
    __in                                  DRM_VOID                                      *f_pvSignatureContext ) DRM_NO_INLINE_ATTRIBUTE;

/******************************************************************************
**
** PRND License Error Message [TX->RX]
**
******************************************************************************/
typedef struct __tagDRM_PRND_LICENSE_ERROR_BASIC_INFORMATION
{
    DRM_BOOL    fValid;
    DRM_DWORD   dwFlags;
    DRM_GUID    guidSessionID;
    DRM_DWORD   dwResult;
} DRM_PRND_LICENSE_ERROR_BASIC_INFORMATION;

typedef struct __tagDRM_PRND_LICENSE_ERROR_MESSAGE
{
    DRM_BOOL                                    fValid;
    DRM_PRND_LICENSE_ERROR_BASIC_INFORMATION    BasicInformation;
} DRM_PRND_LICENSE_ERROR_MESSAGE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_PRND_LicenseErrorMessage_Start(
    __inout_bcount( f_cbStack )           DRM_BYTE                                      *f_pbStack,
    __in                                  DRM_DWORD                                      f_cbStack,
    __inout_ecount( 1 )                   DRM_XB_BUILDER_CONTEXT                        *f_pcontextBuilder ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_PRND_LicenseErrorMessage_Finish(
    __in_ecount( 1 )                const DRM_XB_BUILDER_CONTEXT                        *f_pcontextBuilder,
    __inout_bcount( *f_pcbMessage )       DRM_BYTE                                      *f_pbMessage,
    __inout                               DRM_DWORD                                     *f_pcbMessage ) DRM_NO_INLINE_ATTRIBUTE;

DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_PRND_LicenseErrorMessage_Parse(
    __inout_bcount( f_cbStack )           DRM_BYTE                                      *f_pbStack,
    __in                                  DRM_DWORD                                      f_cbStack,
    __inout_bcount( f_cbMessage )   const DRM_BYTE                                      *f_pbMessage,
    __in                                  DRM_DWORD                                      f_cbMessage,
    __out                                 DRM_PRND_LICENSE_ERROR_MESSAGE                *f_pMessage ) DRM_NO_INLINE_ATTRIBUTE;

EXIT_PK_NAMESPACE;

#endif /* _DRMPRNDFORMAT_H_ */

