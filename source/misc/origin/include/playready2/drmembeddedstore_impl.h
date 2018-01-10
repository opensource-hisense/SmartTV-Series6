/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/


#ifndef __DRM_EMBEDDEDSTORE_IMPL_H__
#define __DRM_EMBEDDEDSTORE_IMPL_H__

#include <drmdatastorecommon.h>

ENTER_PK_NAMESPACE;

#define MAX_EMBEDDED_STORE_LEN 10240

#define BYTES_PER_DWORD      SIZEOF( DRM_DWORD )
#define PAD_AMOUNT(x)        ( ( (x) > 0 ) ? ( ( BYTES_PER_DWORD - ( (x) % BYTES_PER_DWORD ) ) % BYTES_PER_DWORD ) : 0 )
#define PADDED_LEN(x)   ((x) + PAD_AMOUNT(x))

/*
** Context containing information about the embedded store.
*/
typedef struct __tagDRM_EST_CONTEXT
{
    DRM_BOOL   m_fInited;         /* Denotes whether the context has been initialized. */
    DRM_BOOL   m_fStoreOpen;      /* Denotes whether the context contains data for an open store */
    DRM_BOOL   m_fIsDirty;        /* Denotes whether the store has changed since opening */
    DRM_BYTE  *m_pbEmbeddedStore; /* Pointer to the actual store data. */
    DRM_DWORD  m_cbEmbeddedStore; /* Length of m_pbEmbeddedStore that is used in bytes. */
    DRM_DWORD  m_ibUnused;        /* Starting index of the unused buffer within the buffer pointed by m_pbEmbeddedStore. */
    DRM_DWORD  m_cbUnused;        /* Size of the unused buffer within the buffer pointed by m_pbEmbeddedStore. */
    DRM_DWORD  m_dwDeleteCount;   /* Starts at 0, incremented each time a slot is deleted. Used to detect when enumerations should be restarted due to slot deletions */
} DRM_EST_CONTEXT;

/*
** Context containing information about a namespace within an embedded store.
*/
typedef struct __tagDRM_EST_NAMESPACE_CONTEXT
{
    DRM_BOOL          m_fNamespaceOpen; /* Denotes whether the namespace is open */
    DRM_EST_CONTEXT  *m_poESTContext;   /* A pointer to context for the EST used to open the namespace. */
} DRM_EST_NAMESPACE_CONTEXT;

/*
** Context containing information used to find a particular slot.
*/
typedef struct __tagDRM_EST_SLOT_HINT
{
    DRM_DWORD         m_ibOffset;  /* The byte offset of the slot within the current namespace */
    DRM_DWORD         m_cbSlotLen; /* The length of the slot in bytes, without padding */
} DRM_EST_SLOT_HINT;

/*
** Context containing information about a slot.
*/
typedef struct __tagDRM_EST_SLOT_CONTEXT
{
    DRM_BOOL                   m_fSlotOpen;     /* Denotes whether a slot has been opened with this context. */
    DRM_EST_NAMESPACE_CONTEXT *m_poESTNSContext;/* A pointer to context for the namespace  */
    DRM_DST_KEY                m_oKey1;         /* Specifies the first key of the slot */
    DRM_DST_KEY                m_oKey2;         /* Specifies the second key of the slot */
    DRM_DST_LOCKMODE           m_eLockmode;     /* Specifies the lock mode used to open the slot. */
    DRM_DWORD                  m_ibSeekPtr;     /* Maintains the current seek pointer within the slot */
    DRM_EST_SLOT_HINT          m_oSlotLocation; /* Contains the location of the opened slot  */
} DRM_EST_SLOT_CONTEXT;

/*
** Context containing information used to enumerate slots.
*/
typedef struct __tagDRM_EST_ENUM_CONTEXT
{
    DRM_BOOL                    m_fInited;        /* Denotes whether the enum context has been initialized. */
    DRM_EST_NAMESPACE_CONTEXT  *m_poESTNSContext; /* A pointer to context for the namespace. */
    DRM_DWORD                   m_cSlots;         /* Contains the number of slots in the current enumeration */
    DRM_DWORD                   m_iSlot;          /* Contains the index of the current slot in the enumeration. */
    DRM_EST_SLOT_HINT           m_oSlotHint;      /* Slot hint contains the location of current slot */
    DRM_DST_KEY                 m_oKey1;          /* Primary key that is used to find matching slots. */
    DRM_DST_LOCKMODE            m_eLockMode;      /* Locking mode of the enumeration. */
    DRM_BOOL                    m_fSlotValid;     /* Flag indicating whether there is a current slot being enumerated. */
    DRM_DWORD                   m_dwCurrentDeleteCount; /* Delete count when enumeration was started, used to detect if deletions have occurred since starting/restarting */
} DRM_EST_ENUM_CONTEXT;

#define DRM_EST_CONTEXT_LEN             SIZEOF( DRM_EST_CONTEXT )
#define DRM_EST_NAMESPACE_CONTEXT_LEN   SIZEOF( DRM_EST_NAMESPACE_CONTEXT )
#define DRM_EST_SLOT_CONTEXT_LEN        SIZEOF( DRM_EST_SLOT_CONTEXT )
#define DRM_EST_SLOT_HINT_LEN           SIZEOF( DRM_EST_SLOT_HINT )
#define DRM_EST_NAMESPACE_LEN           16
#define DRM_EST_ENUM_CONTEXT_LEN        SIZEOF( DRM_EST_ENUM_CONTEXT )

EXIT_PK_NAMESPACE;

#endif  /* __DRM_EMBEDDEDSTORE_IMPL_H__ */

