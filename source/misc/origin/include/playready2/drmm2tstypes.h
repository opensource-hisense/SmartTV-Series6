/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRM2TSTYPES_H__
#define __DRM2TSTYPES_H__ 1

#include <drmtypes.h>
#include <drmbytemanip.h>
#include <drmdebug.h>
#include <drmresults.h>
#include <drmerr.h>
#include <drmlicgentypes.h>

ENTER_PK_NAMESPACE_CODE;

typedef DRM_VOID *  DRM_M2TS_ENCRYPTOR_HANDLE;

#define DRM_M2TS_ENCRYPTOR_HANDLE_INVALID               ((DRM_M2TS_ENCRYPTOR_HANDLE)0)

#define DRM_M2TS_INITIAL_PACKET_LIST_LENGTH             500         /* Initial free packet list length */
#define DRM_M2TS_PACKETS_TO_ALLOCATE                    100         /* Number of free packets to allocate to the free packet list */
#define DRM_M2TS_INITIAL_ECM_LIST_LENGTH                10          /* Initial free ECM list length */
#define DRM_M2TS_ECMS_TO_ALLOCATE                       5           /* Number of free ECMs to allocate to the free ECM list */
#define DRM_M2TS_PIDS_TO_ALLOCATE                       5           /* Number of PIDs to allocate to the pwRegisteredPIDs array in the encryptor context */
#define DRM_M2TS_MAX_PES_PACKETS_PER_ECM                10
#define DRM_M2TS_SAMPLES_PER_ECM                        250         /* The encryptor will increase the size if it is too small */
#define DRM_M2TS_SUBSAMPLES_PER_ECM                     500         /* The encryptor will increase the size if it is too small */
#define DRM_M2TS_SAMPLES_BUFFER_INCREASE_PERCENTAGE     0.20        /*
                                                                    ** The encryptor doesn't do a dry run to figure out the sample/subsample count.
                                                                    ** So each time it increases the size by 20% to avoid allocating too much memory.
                                                                    ** The encryptor will reuse the buffer for next set of sample/subsamples until it finds
                                                                    ** it is too small again.  At end the unused space will be 20% or less.
                                                                    */
#define DRM_M2TS_SUBSAMPLES_BUFFER_INCREASE_PERCENTAGE  0.20        /* See above */

#define DRM_M2TS_SCRAMBLING_CONTROL_01                  0x01
#define DRM_M2TS_SCRAMBLING_CONTROL_10                  0x02

#define DRM_M2TS_UNDEFINED_PID                          0
#define DRM_M2TS_FIRST_SELECTABLE_PID                   0x0010
#define DRM_M2TS_MAX_PID_VALUE                          0x1FFF
#define DRM_M2TS_UNDEFINED_TABLE_ID                     0
#define DRM_M2TS_PID_OF_PAT                             0
#define DRM_M2TS_PACKET_SIZE                            188
#define DRM_M2TS_PACKET_HEADER_SIZE                     4
#define DRM_M2TS_MAX_TS_PAYLOAD_SIZE                    184
#define DRM_M2TS_MAX_ADAPTATION_FIELD_LENGTH            183
#define DRM_M2TS_ADAPTATION_LENGTH_FIELD_OFFSET         4
#define DRM_M2TS_START_CODE                             0x47
#define DRM_M2TS_CA_DESCRIPTOT_TAG                      0x09
#define DRM_M2TS_STUFFING_BYTE                          0xFF
#define DRM_M2TS_CRC_SIZE                               4
#define DRM_CA_DESCRIPTOR_MIN_SIZE                      4           /* for the CA_System_ID(16), reserved(3), CA_PID(13) */
#define DRM_CA_SYSTEM_ID_HIGHBYTE                       0x4B
#define DRM_CA_SYSTEM_ID_LOWBYTE                        0x13
#define DRM_M2TS_PLAYREADY_DEFAULT_CA_PID               0x1FFE
#define DRM_M2TS_PLAYREADY_CA_SYSTEM_ID                 0x4b13
#define DRM_M2TS_MINIMUN_PAT_SECTION_LENGTH             9           /* include the fields from transport_stream_id to last_section_number and the CRC_32 field */
#define DRM_M2TS_MINIMUN_PMT_SECTION_LENGTH             13          /* include the fields from program_number to program_info_length field and the CRC_32 field */

#define DRM_M2TS_MAX_PAT_PMT_SPAN                       1000        /*
                                                                    ** A PAT or PMT packet will be dropped if it is at front of the incoming packet list
                                                                    ** and not in eDRM_M2TS_PES_STATE_HAS_FULL_PAYLOAD state after the encryptor has processed
                                                                    ** the number of packet defined here.
                                                                    */
#define DRM_M2TS_MAX_PES_PACKET_SPAN                    6000        /*
                                                                    ** An audio or video stream is considered as ended/stopped if we don't receive next packet within
                                                                    ** the next 6000 packets.  When it happens current PES packet will be dropped becase we don't
                                                                    ** know the PES is completed or not and to unblock the encryption.
                                                                    */

#define DRM_M2TS_CURRENT_PAT_OR_PMT                     1           /* The PAT or PMT packet is currently applicable if the value of the current_next_indicator field in the PAT or PMT is 1 */

#define DRM_M2TS_PID_HIGH_BYTE_MASK                     0x1F        /* PID is a 13-bit field and appears on the 2nd byte of the TS Packet header */
#define DRM_M2TS_UNIT_START_MASK                        0x40        /* Unit Start flag is a 1-bit field and appears on the 2nd byte of the TS Packet header */
#define DRM_M2TS_CONTINUITY_COUNTER_MASK                0x0F        /* Continuity counter field is a 4-bit field and appears on the 4th byte of the TS Packet header */
#define DRM_M2TS_ADAPTATION_FIELD_MASK                  0x20        /* Adaptation field is a 1-bit field and appears on the 4th byte of the TS Packet header */
#define DRM_M2TS_PAYLOAD_MASK                           0x10        /* Payload indicator is a 1-bit field and appears on the 4th byte of the TS Packet header */
#define DRM_M2TS_DISCONTINUITY_INDICATOR_MASK           0x80        /* A one bit indicator on the byte after the adapation_field_length  */


/* Supported media formats (codecs) */
#define DRM_M2TS_STREAM_TYPE_RESERVED                   0x00
#define DRM_M2TS_STREAM_TYPE_MPEG2_VIDEO                0x02
#define DRM_M2TS_STREAM_TYPE_MPEGA_AUDIO                0x03
#define DRM_M2TS_STREAM_TYPE_ADTS                       0x0F        /* aka AAC */
#define DRM_M2TS_STREAM_TYPE_H264                       0x1B        /* aka AVC */
#define DRM_M2TS_STREAM_TYPE_DIGICIPHER_II_VIDEO        0x80        /* same as MPEG2 video */
#define DRM_M2TS_STREAM_TYPE_DDPLUS                     0x81        /* aka AC3 */

#define DRM_M2TS_PACKET_FLAG_LAST_OF_LAST_PES_PACKET            0x0001  /* Indicates that the packet is the last packet that contains the overflow payload of last PES */
#define DRM_M2TS_PACKET_FLAG_START_WITH_PARTIAL_START_CODE      0x0002  /* Indicates that the packet contains partial start code/syncword of last PES */
#define DRM_M2TS_PACKET_FLAG_DONT_INCREMENT_CONTINUITY_COUNTER  0x0004  /* Indicates that the packet should use same continuity counter as previous packet with same PID */
#define DRM_M2TS_PACKET_FLAG_DISCONTINUITY_PACKET               0x0008  /* Indicates that the packet has the discontinuity flag set to 1 */

#define DRM_M2TS_PES_DATA_NOT_ALIGNED                   0
#define DRM_M2TS_PES_DATA_ALIGNED                       1

typedef enum
{
    eDRM_M2TS_LOG_CATEGORY_INFORMATION,
    eDRM_M2TS_LOG_CATEGORY_WARNING,
    eDRM_M2TS_LOG_CATEGORY_ERROR,
}
DRM_M2TS_LOG_CATEGORY;

typedef enum
{
    eDRM_M2TS_LOG_DETAILS_TYPE_PACKET,
    eDRM_M2TS_LOG_DETAILS_TYPE_PES,
    eDRM_M2TS_LOG_DETAILS_TYPE_KEY_ROTATION,
}
DRM_M2TS_LOG_DETAILS_TYPE;

typedef enum
{
    eDRM_M2TS_PROPERTY_TYPE_ENCYRPT_AUDIO,
    eDRM_M2TS_PROPERTY_TYPE_ENABLE_LOGGING,
} DRM_M2TS_PROPERTY_TYPE;

typedef enum
{
    eDRM_M2TS_PES_STATE_BEGIN           = 0,
    eDRM_M2TS_PES_STATE_HAS_SECTION_HEADER,
    eDRM_M2TS_PES_STATE_HAS_FULL_PAYLOAD,
    eDRM_M2TS_PES_STATE_ENCRYPTED,
} DRM_M2TS_PES_STATE;

typedef enum
{
    eDRM_M2TS_PACKET_TYPE_PAT           = 0x00,
    eDRM_M2TS_PACKET_TYPE_PMT           = 0x01,
    eDRM_M2TS_PACKET_TYPE_ECM           = 0x02,
    eDRM_M2TS_PACKET_TYPE_PES_AUDIO     = 0x04,
    eDRM_M2TS_PACKET_TYPE_PES_VIDEO     = 0x08,
    eDRM_M2TS_PACKET_TYPE_PES           = 0x0C,
} DRM_M2TS_PACKET_TYPE;

typedef enum
{
    eDRM_M2TS_PACKET_STATE_PENDING      = 0,        /* Not yet encrypted */
    eDRM_M2TS_PACKET_STATE_BAD,                     /* Don't return packets with this state to caller */
    eDRM_M2TS_PACKET_STATE_READY,                   /* Ready to return to caller */
} DRM_M2TS_PACKET_STATE;

typedef enum
{
    eDRM_M2TS_ECM_TYPE_PRIMARY          = 0x01,
    eDRM_M2TS_ECM_TYPE_SECONDARY        = 0x02,
    eDRM_M2TS_ECM_TYPE_KR               = 0x04
} DRM_M2TS_ECM_TYPE;

typedef enum
{
    eDRM_M2TS_PRO_TYPE_NO_PRO                              = 0x01,
    eDRM_M2TS_PRO_TYPE_KEY_ROTATION_WITH_LICENSE_IN_PRO    = 0x02,
    eDRM_M2TS_PRO_TYPE_KEY_ROTATION_WITH_WRMHEADER_IN_PRO  = 0x04,
} DRM_M2TS_PRO_TYPE;

typedef struct __tagDRM_M2TS_PACKET
{
    DRM_BYTE                         rgbData[ DRM_M2TS_PACKET_SIZE ];
    DRM_DWORD                        dwPacketNumber;                    /* For debugging purpose only */
    DRM_M2TS_PACKET_STATE            ePacketState;
    DRM_BYTE                         cbPayload;                         /* Total number of payload bytes in the packet excluding the TS header and adapation field */
    DRM_BYTE                         cbHeader;                          /* Number of payload bytes are for to the current unit (PES) header */
    DRM_BYTE                         cbPayloadLastPES;                  /*
                                                                        ** Number of payload bytes belong to previous unit
                                                                        ** The order of the TS packet is as followed:
                                                                        **
                                                                        ** | TS Packet Header (4) | Adaptation field | Unit Header | Payload of Last Unit | Payload of this unit |
                                                                        **                                           | <------------          cbPayload        ----------------->|
                                                                        **                                           | <-cbHeader->|
                                                                        **                                                         |<--cbPayloadLastPES-->|
                                                                        **
                                                                        ** Example: cbPayload = 100, cbHeader = 12 and cbPayloadLastPES = 25
                                                                        **          In the case, the first 12 bytes in the payload are for the current unit header,
                                                                        **          the next 25 bytes is the payload belongs to the last unit,
                                                                        **          the remaining 63 ( 100 - 12 - 25 ) bytes belong to the current unit
                                                                        */
    DRM_WORD                         wPacketFlags;
    DRM_VOID                        *pECMData;                          /*
                                                                        ** Only when the packet is for ECM. If it is not null then this packet is just a place holder
                                                                        ** as an indicator to where the real ECM packet(s) will be added.
                                                                        */
    struct __tagDRM_M2TS_PACKET     *pNext;                             /* Chain to next packet in oFreePacketList or oIncomingPacketList of DRM_M2TS_ENCRYPTOR_CONTEXT */
    struct __tagDRM_M2TS_PACKET     *pNextPerUnit;                      /* Chain to next packet data to form a complete unit (e.g. PES) */
} DRM_M2TS_PACKET;

typedef struct __tagDRM_M2TS_PACKET_LIST
{
    DRM_DWORD                        cItems;
    DRM_M2TS_PACKET                 *pHead;
    DRM_M2TS_PACKET                 *pTail;
} DRM_M2TS_PACKET_LIST;


typedef struct __tagDRM_M2TS_SUBSAMPLE
{
    DRM_DWORD                        cbEncryptedBytes;
    DRM_WORD                         cbClearBytes;
    DRM_BOOL                         fAdjustable;                       /*
                                                                        ** Flag to indicate whether we can adjust this subsample's
                                                                        ** clear and encrypted bytes in order to make the total
                                                                        ** length of the encrytped subsamples a multiple of 16 bytes.
                                                                        */
} DRM_M2TS_SUBSAMPLE;

typedef struct __tagDRM_M2TS_SAMPLE
{
    DRM_UINT64                       qwIV;
    DRM_BOOL                         fHasSubsample;
    DRM_DWORD                        dwIndexFirstSubsample;
    DRM_DWORD                        dwIndexLastSubsample;
} DRM_M2TS_SAMPLE;

typedef struct __tagDRM_M2TS_PES
{
    DRM_UINT64                       qwPTS;
    DRM_WORD                         wPID;
    DRM_WORD                         cbPESPacketLength;                 /* Length of the PES packet data, 0 means unbounded applicable to the vidoe only. */
    DRM_WORD                         cbHeader;                          /* Length of the entire PAT section, PMT section or PES packet header. */
    DRM_BYTE                         bDataAlignmentFlag;                /* 0-Not Aligned, 1-aligned which means the payload of the PES starts from the first byte */
    DRM_BYTE                         bStreamType;                       /* MPEG2 TS stream type specified in PMT packet, e.g. 0x02 (DRM_M2TS_STREAM_TYPE_MPEG2_VIDEO) */
    DRM_M2TS_PES_STATE               ePESState;
    DRM_M2TS_PACKET_LIST             oPacketList;                       /* Chain (using pNextPerUnit chain) of packets that belong to this PES */
    DRM_M2TS_PACKET                 *pHeadOfOverflowedPackets;          /*
                                                                        ** Chain (using pNextPerUnit chain) of packets that belong to next PEX but
                                                                        ** has one or more packets that contain the overflowed payload belong to this PES
                                                                        */
    DRM_BOOL                         fHasSample;
    DRM_RESULT                       drPESResult;
    DRM_DWORD                        dwIndexFirstSample;
    DRM_DWORD                        dwIndexLastSample;
    DRM_BOOL                         fNeedRealignment;                  /* for PES that doesn't have its own payload or just contains partial start code of the next PES */
    struct __tagDRM_M2TS_PES        *pLastPESNeedAlignment;             /* for PES that doesn't have its own payload or just contains partial start code of the next PES */
} DRM_M2TS_PES;

typedef struct __tagDRM_M2TS_STREAM
{
    DRM_UINT64                       qwPTS;
    DRM_WORD                         wPID;
    DRM_WORD                         cbHeader;
    DRM_WORD                         cbPESPacketLength;
    DRM_BYTE                         bNextContinuityCounter;
    DRM_BYTE                         bDataAlignmentFlag;
    DRM_BYTE                         bStreamType;
    DRM_BOOL                         fFoundFirstUnitStart;              /* Before this flag changes to TRUE, the incoming packets in this stream will be thrown away */
    DRM_UINT64                       qwAggregatedDuration;              /* the aggregated frame druration in hns */
    DRM_M2TS_PES_STATE               ePESState;
    DRM_M2TS_PACKET_LIST             oPacketList;
    DRM_M2TS_PACKET_TYPE             ePacketType;
    DRM_M2TS_PES                    *pCurrentPES;
    DRM_M2TS_PES                    *pLastPES;                          /*
                                                                        ** Points to last PES of this stream type, in case current PES' length is unbounded that
                                                                        ** we need to append packets from current PES until the start code of the current PES is found
                                                                        */
    struct __tagDRM_M2TS_STREAM     *pNext;
} DRM_M2TS_STREAM;

typedef struct __tagDRM_M2TS_STREAM_LIST
{
    DRM_DWORD                        cItems;
    DRM_M2TS_STREAM                 *pHead;
    DRM_M2TS_STREAM                 *pTail;
} DRM_M2TS_STREAM_LIST;

typedef struct __tagDRM_M2TS_ECM
{
    DRM_WORD                         wPID;
    DRM_M2TS_ECM_TYPE                eECMType;
    DRM_GUID                         oKeyId;
    DRM_M2TS_PRO_TYPE                ePROType;
    DRM_LICENSE_HANDLE               hLicense;
    DRM_BYTE                        *pbPROBlob;
    DRM_DWORD                        cbPROBlob;
    DRM_BOOL                         fHasVideoPES;
    DRM_BOOL                         fSubsampleMappingsCompleted;
    DRM_BOOL                         fEncrypted;
    DRM_WORD                         cPESPackets;
    DRM_M2TS_PES                     rgPESPackets[ DRM_M2TS_MAX_PES_PACKETS_PER_ECM ];
    struct __tagDRM_M2TS_ECM        *pNext;
} DRM_M2TS_ECM;

typedef struct __tagDRM_M2TS_ECM_LIST
{
    DRM_DWORD                        cItems;
    DRM_M2TS_ECM                    *pHead;
    DRM_M2TS_ECM                    *pTail;
} DRM_M2TS_ECM_LIST;

typedef struct __tagDRM_M2TS_REMOVABLE_PID
{
    DRM_WORD                             wPID;
    struct __tagDRM_M2TS_REMOVABLE_PID  *pNext;
} DRM_M2TS_REMOVABLE_PID;

typedef struct __tagDRM_M2TS_REMOVABLE_PID_LIST
{
    DRM_DWORD                        cItems;
    DRM_M2TS_REMOVABLE_PID          *pHead;
    DRM_M2TS_REMOVABLE_PID          *pTail;
} DRM_M2TS_REMOVABLE_PID_LIST;

typedef struct __tagDRM_M2TS_LOG
{
    DRM_M2TS_LOG_CATEGORY            eCategory;
    DRM_RESULT                       drResult;
    DRM_M2TS_LOG_DETAILS_TYPE        eDetailsType;
    union {
        struct
        {
            DRM_BOOL                 fDropped;
            DRM_WORD                 wPID;
            DRM_DWORD                dwPacketNumber;
            DRM_BYTE                 rgbPacketData[DRM_M2TS_PACKET_SIZE];
        } Packet;
        struct
        {
            DRM_BOOL                 fDropped;
            DRM_WORD                 wPID;
            DRM_UINT64               qwPTS;
            DRM_DWORD                cPackets;
            DRM_DWORD                dwFirstPacketNumber;
            DRM_DWORD                dwLastPacketNumber;
            DRM_BYTE                 bDataAligned;
            DRM_BYTE                 bStreamType;
        } PES;
        struct
        {
            DRM_UINT64               qwPTS;
            DRM_UINT64               qwAggregatedDuration;
            DRM_UINT64               qwCurrentKeyDuration;
        } KeyRotation;
    } Details;
} DRM_M2TS_LOG;

/* Logging callback function declaration */
typedef DRM_VOID ( DRM_CALL *DRM_pfnLoggingCallback )( __inout DRM_VOID *pCallbackContext, __in const DRM_M2TS_LOG *f_poLog );

typedef struct __tagDRM_M2TS_ENCRYPTION_PROPERTY
{
    DRM_M2TS_PROPERTY_TYPE           ePropertyType;
    union
    {
        DRM_BOOL                     fValue;
        struct
        {
            DRM_VOID                *pCallbackContext;
            DRM_pfnLoggingCallback   pfnLoggingCallback;
        } LoggingCallback;
    } Value;
} DRM_M2TS_ENCRYPTION_PROPERTY;

typedef struct __tagDRM_M2TS_ENCRYPTOR_CONTEXT
{
    DRM_BOOL                         fInit;
    DRM_DWORD                        cbHeapAllocated;                   /* The amount of heap the encryptor has allocated */
    DRM_DWORD                        cbHeapAllowed;                     /* The max amount of heap the encryptor allowed to allocate */
    DRM_BOOL                         fEncryptAudio;
    DRM_BYTE                         bScramblingControl;
    DRM_DWORD                        dwNextPacketNo;
    DRM_M2TS_PRO_TYPE                ePROType;
    DRM_UINT64                       qwCurrentKeyDuration;              /* The durartion in hns for the current key, 0 - no key roration */
    DRM_BOOL                         fWaitingForNewKey;
    DRM_GUID                         oKeyId;
    DRM_LICENSE_HANDLE               hLicense;
    DRM_DWORD                        cRegisteredPIDsAllocated;          /* Number of items in pwRegisteredPIDs array */
    DRM_DWORD                        cRegisteredPIDs;                   /* Number of items used in pwRegisteredPIDs array */
    DRM_WORD                        *pwRegisteredPIDs;                  /*
                                                                        ** A sorted array of registered PIDs that are used by the content is used
                                                                        ** for selectng the PID of the ECM if PID 0x1FFE is used.  The array is
                                                                        ** sorted by PID in ascending order.
                                                                        */
    DRM_WORD                         wPID_CA;                           /* The PID of ECM packet */
    DRM_BYTE                         bNextECMCC;                        /* next ECM packet's continuity counter */
    DRM_M2TS_ECM                    *pCurrentECM;
    DRM_M2TS_ECM_LIST                oFreeECMList;
    DRM_M2TS_PACKET_LIST             oFreePacketList;
    DRM_M2TS_PACKET_LIST             oIncomingPacketList;
    DRM_M2TS_PACKET_LIST             oCachedPacketList;
    DRM_M2TS_STREAM_LIST             oStreamList;                       /* One PID per entry, include the PAT, PMT and the audio and video streams */
    DRM_BYTE                         rgbCachedLastIncompletedPacket[DRM_M2TS_PACKET_SIZE];
    DRM_BYTE                         bOffsetCachedLastIncompletedPacket;
    DRM_DWORD                        dwIndexNextFreeSample;
    DRM_DWORD                        cSamplesAllocated;                 /* The number of samples allocated in pSamples array */
    __ecount( cSamplesAllocated )    DRM_M2TS_SAMPLE        *pSamples;
    DRM_DWORD                        dwIndexNextFreeSubsample;
    DRM_DWORD                        cSubsamplesAllocated;              /* The number of subsamples allocated in pSubsamples array */
    __ecount( cSubsamplesAllocated ) DRM_M2TS_SUBSAMPLE     *pSubsamples;
    DRM_DWORD                        cEncryptedSegments;
    __ecount( cEncryptedSegments )   DRM_DWORD              *prgcbEncryptedSegments; /* pointer to an array of lengths of encrypted segments  */
    __ecount( cEncryptedSegments )   DRM_BYTE              **ppbEncryptedSegments;   /* pointer to an array of pointers to the encrypted segments */
    DRM_M2TS_REMOVABLE_PID_LIST      oRemovablePIDList;
    DRM_BOOL                         fEncryptionStarted;
    DRM_RESULT                       drLastEncryption;
    DRM_VOID                        *pLoggingCallbackContext;
    DRM_pfnLoggingCallback           pfnLoggingCallback;
    DRM_BOOL                         fClosingSession;
#if DBG
    DRM_DWORD                        cbActualMaxHeapAllocated;
    DRM_DWORD                        cActualPacketsAllocated;
    DRM_DWORD                        cActualECMsAllocated;
    DRM_DWORD                        cActualPacketsUsed;
    DRM_DWORD                        cActualECMsUsed;
    DRM_DWORD                        cActualSamplesUsed;
    DRM_DWORD                        cActualSubsamplesUsed;
#endif /* DBG */

} DRM_M2TS_ENCRYPTOR_CONTEXT;

typedef struct __tagDRM_M2TS_BIT_STREAM_CONTEXT
{
    DRM_BYTE                        *pbData;
    DRM_DWORD                        cbData;
    DRM_DWORD                        dwByteOffset;
    DRM_WORD                         wBitOffset;
    DRM_BOOL                         fOutOfRange;
    DRM_BOOL                         fUseCounter;               /*
                                                                ** Flag to indicate whether cCounter is used
                                                                ** When used, it trumps cbData for deciding the remaining bytes
                                                                */
    DRM_DWORD                        cCounter;                  /* A countdown counter, decrement by one each byte is read/skiped */
    DRM_M2TS_PACKET                 *pPacket;
} DRM_M2TS_BIT_STREAM_CONTEXT;

typedef struct __tagDRM_M2TS_SUBSAMPLE_CONTEXT
{
    DRM_BYTE                         rgbBuffer[ DRM_M2TS_PACKET_SIZE * 3 ]; /* working buffer for containing the PES payload to be processed */
    DRM_WORD                         wOffset;                   /* offset of the buffer */
    DRM_WORD                         cbBuffer;                  /* number of bytes contained/used in the buffer */
    DRM_BOOL                         fProcessProtected;         /* Indicate whether to process clear or protected subsample */
    DRM_BYTE                         cbCountdownToProtected;    /*
                                                                ** The number of bytes left before switching to protected plus one protected byte.
                                                                ** e.g. if the number is 3 then there are two bytes left in clear and the third is protected
                                                                */
    DRM_WORD                         cbFrameHeader;
    DRM_DWORD                        cbFrameSize;               /*
                                                                ** 0 means there is no frame size info.  Otherwiese it is the length of the frame.
                                                                ** It is used to locate the starting position of the next sample in a PES
                                                                ** NOTE: frame size includes the cbFrameHeader
                                                                */
    DRM_DWORD                        dwLastOffset;              /* Overall offset since the beginning of the first byte of the payload.  Doesn't not include dwOffset. */
    DRM_DWORD                        cbCurrentPESOnly;          /* Payload lenght of the PES, doesn't include the overflow bytes */
    DRM_BYTE                         bLast;                     /* For H.264 to determine whether the NAL start code is 001 or 0001 */
    DRM_BOOL                         fLastCall;                 /* Flag to indicate whether the bytes in buffer are the last */
} DRM_M2TS_SUBSAMPLE_CONTEXT;

typedef struct __tagDRM_M2TS_ECM_BUILDER_CONTEXT
{
    DRM_M2TS_ENCRYPTOR_CONTEXT      *pEncContext;
    DRM_M2TS_ECM                    *pECM;
    DRM_M2TS_PACKET_LIST            *pPacketList;
    DRM_BYTE                         rgbBuffer[ DRM_M2TS_PACKET_SIZE * 2 ]; /* working buffer for storing the ECM payload */
    DRM_WORD                         cbBuffer;                  /* number of bytes contained/used in the buffer */
    DRM_DWORD                        cbWritten;                 /* number of bytes actually have been written to the TS packets */
    DRM_WORD                         cECMPacketCreated;
} DRM_M2TS_ECM_BUILDER_CONTEXT;

typedef struct __tagDRM_M2TS_PES_ENCRYPTION_CONTEXT
{
    DRM_M2TS_PACKET                 *pPacket;
    DRM_BYTE                         cbPayloadRemaining;
    DRM_DWORD                        dwIndexNextEncryptedSegment;
} DRM_M2TS_PES_ENCRYPTION_CONTEXT;

EXIT_PK_NAMESPACE_CODE;

#endif  /* __DRM2TSTYPES_H__ */
