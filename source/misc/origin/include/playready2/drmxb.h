/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRM_XB_H__
#define __DRM_XB_H__

#include <drmtypes.h>
#include <drmpragmas.h>

ENTER_PK_NAMESPACE;

typedef enum
{
    XB_FORMAT_ID_LENGTH_DWORD = SIZEOF( DRM_DWORD ),
    XB_FORMAT_ID_LENGTH_QWORD = SIZEOF( DRM_UINT64 ),
} XB_FORMAT_ID_LENGTH;

#define XB_HEADER_LENGTH( formatIdLength )      ( ( formatIdLength ) + SIZEOF( DRM_DWORD ) * 2 )    /* XB headers are 1 DWORD/QWORD long plus 2 DWORDs long (id, version, length) */
#define XB_BASE_OBJECT_LENGTH                   ( SIZEOF( DRM_WORD ) * 2  + SIZEOF( DRM_DWORD ) )   /* Each obect/container always has type (WORD), flags (WORD), and length (DWORD) */
#define XB_MAXIMUM_OBJECT_DEPTH 6

/*
** valid flags for containers and objects
*/
enum XB_OBJECT_FLAGS
{
    XB_FLAGS_NONE                  = 0x0000,
    XB_FLAGS_MUST_UNDERSTAND       = 0x0001,
    XB_FLAGS_CONTAINER             = 0x0002,
    XB_FLAGS_ALLOW_EXTERNAL_PARSE  = 0x0004  /* Not currently supported */
};

enum XB_OBJECT_TYPE
{
    XB_OBJECT_TYPE_INVALID                                          = MAX_UNSIGNED_TYPE(DRM_WORD), /* Invalid is -1 */
    XB_OBJECT_GLOBAL_HEADER                                         = 0                            /* All formats based on the XB system should start their objects from XB_OBJECT_GLOBAL_HEADER+1 */
};

/* Base struct that all XB structs can be cast to */
typedef struct __tagDRM_XB_EMPTY
{
    DRM_BOOL  fValid;
} DRM_XB_EMPTY;

/* Base struct for all types that allow duplicates as they are parsed into a linked list */
typedef struct __tagDRM_XB_BASELIST
{
    DRM_BOOL fValid;
    struct __tagDRM_XB_BASELIST *pNext;

} DRM_XB_BASELIST;

/*
** A flat array of GUIDs.  When represented in the binary format it is serialized as
** a DWORD followed by cGUIDs consecutive 16 byte GUID values.
*/
typedef struct __tagDRM_XB_GUIDLIST
{
    DRM_BOOL   fValid;
    DRM_DWORD  cGUIDs;
    DRM_BYTE  *pguidBuffer;
    DRM_DWORD  iGuids;
} DRM_XB_GUIDLIST;


/*
** A flat array of WORDs.  When represented in the binary format it is serialized as
** a DWORD followed by cWORDs consecutive WORD values.
*/
typedef struct __tagDRM_XB_WORDLIST
{
    DRM_BOOL   fValid;
    DRM_DWORD  cWORDs;
DRM_OBFUS_PTR_TOP
    DRM_BYTE  *pwordBuffer;
DRM_OBFUS_PTR_BTM
    DRM_DWORD  iWords;
DRM_OBFUS_FILL_BYTES(4)
} DRM_XB_WORDLIST;

/*
**  An array of byte.  When serialized it may be serialized as
**  a DWORD followed by cbData consecutive bytes or just cbData bytes if the
**  defining format specifies the data as a fixed size.
*/
typedef struct __tagDRM_XB_BYTEARRAY
{
    DRM_BOOL   fValid;
    DRM_DWORD  cbData;
DRM_OBFUS_PTR_TOP
    DRM_BYTE  *pbDataBuffer;
DRM_OBFUS_PTR_BTM
    DRM_DWORD  iData;
DRM_OBFUS_FILL_BYTES(4)
} DRM_XB_BYTEARRAY;

/* Note: These macros are not 16-bit byte safe. */
#define XBBA_TO_PB( xbba ) ( ( (xbba).cbData != 0 ) ? ( (xbba).pbDataBuffer + (xbba).iData ) : NULL )
#define XBBA_TO_CB( xbba ) ( (xbba).cbData )

typedef struct __tagDRM_XB_OBJECT
{
    DRM_BOOL                            fValid;
    DRM_WORD                            wType;
    DRM_WORD                            wFlags;
    DRM_BYTE                           *pbBuffer;
    DRM_DWORD                           ibData;
    DRM_DWORD                           cbData;
    struct __tagDRM_XB_OBJECT *pNext; /* Linked list */
} DRM_XB_OBJECT;


/*
**  Each element in an object can be one of these base types
*/
typedef enum
{
    XB_ELEMENT_TYPE_INVALID,
    XB_ELEMENT_TYPE_WORD,
    XB_ELEMENT_TYPE_DWORD,
    XB_ELEMENT_TYPE_QWORD,
    XB_ELEMENT_TYPE_GUID,
    XB_ELEMENT_TYPE_GUIDLIST,
    XB_ELEMENT_TYPE_WORDLIST,
    XB_ELEMENT_TYPE_BYTEARRAY,
} XB_ELEMENT_BASE_TYPE;

PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_ENUM_TYPEDEF, "typedef is required in strict ANSI C")
typedef enum
{
    XB_SIZE_IS_ABSOLUTE,        /* Absolute means that the size value is an exact value as specified by the accompanying DWORD */
    XB_SIZE_IS_RELATIVE_WORD,   /* Relative means that there is an adjoining WORD in the binary format that specifies the size */
    XB_SIZE_IS_RELATIVE_DWORD,  /* Relative means that there is an adjoining DWORD in the binary format that specifies the size */
    XB_SIZE_IS_IGNORED = 0xBAAD /* Relative means that there is an adjoining DWORD in the binary format that specifies the size */
} XB_SIZE_TYPE;
PREFAST_POP

typedef struct __tagDRM_XB_SIZE
{
    XB_SIZE_TYPE         eSizeType;
    DRM_WORD             wSize;
} DRM_XB_SIZE;

/* Unless you are using a BYTEARRAY use XB_SIZE_IGNORED for the xbSize field  */
#define XB_SIZE_IGNORED { XB_SIZE_IS_IGNORED, 0xBAAD }

#define XB_SIZE_RELATIVE_DWORD { XB_SIZE_IS_RELATIVE_DWORD, 0 }
#define XB_SIZE_RELATIVE_WORD  { XB_SIZE_IS_RELATIVE_WORD,  0 }
#define XB_SIZE_ABSOLUTE(x)    { XB_SIZE_IS_ABSOLUTE,      (x)}

/*
** Each element in an object is described be the following structure.
** Constructing an array of such objects will describe an entire object
*/
typedef struct __tagDRM_XB_ELEMENT_DESCRIPTION
{
    XB_ELEMENT_BASE_TYPE eElementType;              /* Type of element */
    DRM_WORD             wOffsetInCurrentStruct;    /* Where in the containing struct the element should be serialized to/from */
    DRM_XB_SIZE          xbSize;                    /* If the object is a BYTEARRAY is the size relative or absolute */
} DRM_XB_ELEMENT_DESCRIPTION;

/*
**  Each entry(container or object) is represented by the following structure.
*/
PREFAST_PUSH_DISABLE_EXPLAINED(__WARNING_POOR_DATAALIGNMENT, "Structure sequence maintained to avoid manually modifying large structure arrays.")
typedef struct __tagDRM_XB_ENTRY_DESCRIPTION
{
    DRM_WORD  wType;                                /* Type identifier -- should be the same value as the entries order in the entry array in the format description */
    DRM_WORD  wFlags;                               /* Flags for this type */
    DRM_WORD  wParent;                              /* The container that can hold this object/container */
    DRM_BOOL  fDuplicateAllowed;                    /* Are multiple objects allowed */
    DRM_BOOL  fOptional;                            /* Is this a required object for the binary format to be valid? */
    DRM_WORD  wOffsetInCurrentStruct;               /* Where in the containing structure should the data be serialized from/to */
    DRM_DWORD dwStructureSize;                      /* Size of the containing structure.  This is necessary when duplicates are allocated in a linked list */
    DRM_WORD  wBuilderSortOrder;                    /* Order in which elements should be serialized during building.  Has no affect during parsing */
    const DRM_VOID *pContainerOrObjectDescriptions; /* This pointer is either an array of DRM_XB_ELEMENT_DESCRIPTION if the entry is an object or NULL if this is a container . */
    DRM_WORD  cContainerOrObjectDescriptions;
} DRM_XB_ENTRY_DESCRIPTION;
PREFAST_POP

typedef struct __tagDRM_XB_HEADER_DESCRIPTION
{
    XB_FORMAT_ID_LENGTH         eFormatIdLength;
    DRM_UINT64                  qwFormatIdentifier; /* 4 or 8 byte string identifier.  Use XB_DEFINE_DWORD_FORMAT_ID or XB_DEFINE_QWORD_FORMAT_ID to create this value */
    DRM_DWORD                   dwFormatVersion;    /* Version supported by this description */
    DRM_WORD                    wOffsetOfSizeInHeaderStruct;               /* Where in the containing structure should the data be serialized from/to */
    const DRM_XB_ENTRY_DESCRIPTION   *pEntryDescription;  /* The header can have optional extra data -- but only 1 */
} DRM_XB_HEADER_DESCRIPTION;

/*
**  Single descrption point for a format.  This format is composed of arrays of other objects as noted below.
*/
typedef struct __tagDRM_XB_FORMAT_DESCRIPTION
{
    const DRM_XB_HEADER_DESCRIPTION *pHeaderDescription;
    const DRM_XB_ENTRY_DESCRIPTION  *pEntryDescriptions; /* An array of entry descriptions.  Each entry description is either a container or an object */
    DRM_WORD                         cEntryDescriptions;
} DRM_XB_FORMAT_DESCRIPTION;

#define XB_DEFINE_FOUR_BYTE_FORMAT_ID( ch0, ch1, ch2, ch3 )                             \
        ( (DRM_DWORD)(DRM_BYTE)(ch3)         | ( (DRM_DWORD)(DRM_BYTE)(ch2) << 8 ) |    \
        ( (DRM_DWORD)(DRM_BYTE)(ch1) << 16 ) | ( (DRM_DWORD)(DRM_BYTE)(ch0) << 24 ) )

#define XB_DEFINE_DWORD_FORMAT_ID( ch0, ch1, ch2, ch3 )                                 \
        DRM_UI64LITERAL( 0, XB_DEFINE_FOUR_BYTE_FORMAT_ID( ch0, ch1, ch2, ch3 ) )

#define XB_DEFINE_QWORD_FORMAT_ID( ch0, ch1, ch2, ch3, ch4, ch5, ch6, ch7 )             \
        DRM_UI64LITERAL( XB_DEFINE_FOUR_BYTE_FORMAT_ID( ch0, ch1, ch2, ch3 ), XB_DEFINE_FOUR_BYTE_FORMAT_ID( ch4, ch5, ch6, ch7 ) )

#define XB_NULL_DESCRIPTOR NULL, 0
#define XB_USE_DESCRIPTOR( descriptor ) (DRM_VOID*)(descriptor), NO_OF( (descriptor) )

#define XB_DECLARE_OFFSET_AND_SIZE_DEREF(struc, member) DRM_OFFSET_OF(struc,member), DRM_SIZEOF_MEMBER_DEREF(struc,member)
#define XB_DECLARE_OFFSET_AND_SIZE( struc, member ) DRM_OFFSET_OF(struc,member), DRM_SIZEOF_MEMBER(struc,member)

/*
** Internal helper functions
*/
DRM_WORD DRM_CALL _XB_MapObjectTypeToEntryDescriptionIndex(
    __in  const   DRM_XB_FORMAT_DESCRIPTION   *f_pFormat,
    __in          DRM_WORD                     f_wType );

DRM_BOOL DRM_CALL _XB_IsKnownObjectType(
    __in  const   DRM_XB_FORMAT_DESCRIPTION   *f_pFormat,
    __in          DRM_WORD                     f_wType );

EXIT_PK_NAMESPACE;

#endif  /* __DRM_XB_H__ */

