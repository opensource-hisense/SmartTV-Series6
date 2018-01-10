/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __OEMCONTEXTSIZES_H__
#define __OEMCONTEXTSIZES_H__


#include <drmdevicestoretypes.h>

ENTER_PK_NAMESPACE;

typedef DRM_DEVICESTORE_CONTEXT OEM_DEVICESTORE_CONTEXTINTERNAL;

struct __tagOEM_DEVICESTORE_INITDATA;

typedef struct __tagOEM_DEVICESTORE_INITDATA OEM_DEVICESTORE_INITDATA;

#define OEM_DEVICESTORE_CONTEXT_BUFFER_SIZE SIZEOF(OEM_DEVICESTORE_CONTEXTINTERNAL)
typedef struct __tagOEM_DEVICESTORE_CONTEXT {
    DRM_BYTE rbgOpaqueBuffer[ __CB_DECL(OEM_DEVICESTORE_CONTEXT_BUFFER_SIZE ) ];
} OEM_DEVICESTORE_CONTEXT;


EXIT_PK_NAMESPACE;

#endif /* __OEMCONTEXTSIZESH__ */
