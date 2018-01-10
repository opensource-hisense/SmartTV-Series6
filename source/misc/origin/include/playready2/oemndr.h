/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __OEMNDR_H__
#define __OEMNDR_H__

#include <drmprndprotocoltypes.h>

ENTER_PK_NAMESPACE;

/*
** OEM_MANDATORY:
** If the device supports PlayReady-ND-Rx (PRND-Rx), this function MUST be implemented by the OEM.
*/
DRM_API DRM_RESULT DRM_CALL Oem_Ndr_GetSupportedProximityDetectionTypes(
    __out_ecount(1) DRM_DWORD   *f_pdwSupportedProximityDetectionTypes );

EXIT_PK_NAMESPACE;

#endif /*  __OEMNDR_H__ */

