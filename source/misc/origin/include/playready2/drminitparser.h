/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRMINITPARSER_H__
#define __DRMINITPARSER_H__

#include <drmtypes.h>
#include <drmpragmas.h>

ENTER_PK_NAMESPACE_CODE;

typedef enum
{
    DRM_INIT_UNKNOWN            = 0,
    DRM_INIT_JOINDOMAIN         = 1,
    DRM_INIT_LEAVEDOMAIN        = 2,
    DRM_INIT_LICENSEACQUISITION = 3,
    DRM_INIT_METERING           = 4
} DRM_INITIATOR_TYPE;


/*
** Enumerator context
*/
typedef struct
{
    DRM_CONST_STRING dstrXMLData; /* input data string with a list of initiator messages */

    DRM_CONST_STRING dstrCurrent; /* position to start reading and max length of data that can be read */

} DRM_INITIATORS_ENUM_CONTEXT;


/*
** Join/Leave domain
*/
typedef struct
{
    DRM_CONST_STRING dstrDomainServer;

    DRM_GUID         oAccountID;

    DRM_GUID         oServiceID;

} DRM_INIT_DOMAIN_DATA;


/*
** License and content acquisition
*/
typedef struct
{
    DRM_CONST_STRING dstrContentHeader;

    DRM_CONST_STRING dstrContentURL;

    /* Point to the <LA_URL> node in the content header. */
    DRM_CONST_STRING dstrLAURL;

    /* Point to the <LUI_URL> node (if exists) in the content header. */
    DRM_CONST_STRING dstrLUIURL;

    /* Point to the <DS_ID> node (if exists) in the content header. */
    DRM_CONST_STRING dstrDSID;

    /* Point to the content of <WMConvert> node. */
    DRM_CONST_STRING dstrWMConvert;

    /* Flag inidicating whether the <WMConvert> node is available. */
    DRM_BOOL fWMConvert;

} DRM_INIT_LICACQ_DATA;

/*
** Metering data reporting
*/
typedef struct
{
    DRM_CONST_STRING dstrMeteringCertServer;

    DRM_MID          oMID;

    DRM_LONG         lMaxPackets;

} DRM_INIT_METERING_DATA;


/*
** PlayReady Initiator message data
*/
typedef struct
{
    DRM_INITIATOR_TYPE eType;                /* message type */

    DRM_CONST_STRING   dstrCustomData;       /* custom data */

    union
    {
        DRM_INIT_DOMAIN_DATA   oDomainData;   /* Join/Leave domain */
        DRM_INIT_LICACQ_DATA   oLicAcqData;   /* License and content acquisition */
        DRM_INIT_METERING_DATA oMeteringData; /* Metering data reporting */
    } Data;

} DRM_INITIATOR_DATA;


#define EMPTY_DRM_INITIATOR_DATA        { DRM_INIT_UNKNOWN, EMPTY_DRM_STRING, {0} }

EXIT_PK_NAMESPACE_CODE;

#endif /* __DRMINITPARSER_H__ */



