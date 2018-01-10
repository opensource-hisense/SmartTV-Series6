/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/


#ifndef _HDS_IMPL_H
#define _HDS_IMPL_H

#include <oemmd5types.h>
#include <drmdatastorecommon.h>
#include <oemplatform.h>
#include <drmstkalloctypes.h>
#include <oemcommon.h>
#include <drmpragmas.h>

ENTER_PK_NAMESPACE;

/*
** uncomment the following if do not need DRM_HDS_InitSlotEnum() and DRM_HDS_SlotEnumNext()
*/
/* #define _NOENUMALL */


/*
** Note: this is implementation specific.
*/
#define DRM_HDS_CONTEXT_LENGTH      2068+DRM_HDS_COPY_BUFFER_SIZE
#define MAXSLOTPOS                  0xFFFF
#define ROOTPARENTNUM               0x00


#define DRM_E_HDSINVALIDSTORE     DRM_E_INVALID_LICENSE_STORE
#define DRM_E_HDSSRNCORRUPTED     DRM_E_DST_CORRUPTED

#define DRM_HDS_HASHKEY_SIZE        SIZEOF( DRM_DST_KEY )
#define DRM_HDS_UNIQUEKEY_SIZE      SIZEOF( DRM_DST_KEY )
#define DRM_HDS_NSNAME_SIZE         16

/* create a namespace tree in the data store */
#define DRM_HDS_MAXIMUM_CHILDREN 16


/* Bloom filter constants for child block
NOTE: Changing these values will break forward and backward compatibility */
#define HDS_CHILDBLOCK_BLOOM_MAX_M 128 /* Size of Bloom data in bytes */
#define HDS_CHILDBLOCK_BLOOM_MAX_K 710 /* Maximum Bloom K coefficient */

#define HDS_CHILDBLOCK_PRERELEASE_BLOOM_K 7  /* Number of Bloom hash functions for V1 file format */
#define HDS_CHILDBLOCK_PRERELEASE_BLOOM_M 20 /* Size of Bloom data in bytes for V1 file format */

/*
** Useful macros used in this source file only
*/
#define HDS_CONTEXT_LENGTH(srnsize)    \
    (SIZEOF(_HdsContext) - SIZEOF(_SRN) + (srnsize) + DRM_HDS_CONTEXT_LENGTH)

#define ISVALIDCONTEXT(ctx, eSignature) \
    ((ctx)!=NULL && (((ctx)->eContextSignature==(eSignature))?TRUE : FALSE))

#define CALC_SLOTCONTEXTLEN(cfg) \
    (SIZEOF(_SlotContext)+GetMemsize_ChildBlock((cfg))+GetMemsize_DataBlock())

/* There cound be an integer overflow, as pointed out by PREfast */
#define ChkOverflowSLOTCONTEXTLEN(cfg) \
    ChkOverflow( CALC_SLOTCONTEXTLEN(cfg), SIZEOF(_SlotContext) + SIZEOF(_ChildBlockHDR) + GetMemsize_DataBlock() );

#define CALC_MAXSLOTCONTEXTLEN \
    (SIZEOF(_SlotContext)+GetMaxMemsize_ChildBlock()+GetMemsize_DataBlock())

#define CALC_MAXENUMCONTEXTLEN \
    (SIZEOF(_EnumContext)+GetMaxMemsize_ChildBlock()-SIZEOF(_CommBlockHDR))

#define CALC_MAXBLOCKHEADERLEN \
    GetMaxMemsize_ChildBlock()

/*
**  NOTE:
**  -Child Node number = (Fileposition / NodeSize) + 1
**  -Node number of the RootNode is always 0
**  -Uses DRM_USHORT for Nodenum gives roughly 64K nodes in a file. On average, if a node
**   can store 5 licenses, a license file can store up to 320K licenses.
**  -If a larger number of licneses need to be stored, DRM_DWORD can be used. This will gives
**   4096M nodes or 20480M licenses.
**  -to search a node containing a particular license, we only have to traverse Log(N) times where
**   N is the number of licenses in the file.
*/




/******************************************************************************
** Major implementation data structure
*******************************************************************************
*/


/*
** Block Type
*/
typedef enum
{
    eINVALIDBLOCK = 0x00,
    eCHILDBLOCK,
    eDATABLOCK,
    eFREEBLOCK
} _EBlockType;

typedef enum
{
    eHdsContextSignature  = 0x01,
    eCfgContextSignature  = 0x02,
    eSlotContextSignature = 0x03,
    eEnumContextSignature = 0x04
} _EContextSignature;


/*
**
*/
typedef enum
{
    eSlotCtxUninit = 0,
    eSlotCtxInited,
    eSlotCtxReady
} _ESlotContextStatus;


typedef enum
{
    eSearchSlotDontCare,
    eSearchDataSlot,
    eSearchNamespace,
    eSearchHiddenOnly
} _ESlotSearchMode;


typedef enum
{
    eRemoveSlotSetHidden = 1,
    eRemoveSlotSetNull   = 2,
    eRemoveSlotPermanent = 3
} _ERemoveSlotMode;


typedef struct __tagDRM_HDS_NAMESPACE_BLOB
{
    DRM_BYTE rgb[__CB_DECL(DRM_HDS_NSNAME_SIZE)];
} DRM_HDS_NAMESPACE;

/*
** Namespace entry in SRN's namespace alloc table
*/
typedef struct _tag_NSEntry
{
    DRM_WORD  wMaxNumChildren;
    DRM_WORD  wPadding;
    DRM_DWORD nNSRBlockNum;                  /* block # of the Namespace Root node */
    DRM_BYTE  bNSName [__CB_DECL(DRM_HDS_NSNAME_SIZE)]; /* Namespace name */
    DRM_WORD  wBloomBytesM;
    DRM_WORD  wBloomK;
} _NSEntry;


/* HDS Namespace cache definitions */

#define DRM_HDS_NAMESPACECACHE_FLAG_VALID 0x01

typedef struct _tag_NamespaceCacheEntry
{
    DRM_DWORD dwCacheFlags;
    _NSEntry nsEntry;
} _NamespaceCacheEntry;

#define DRM_HDS_NAMESPACECACHE_MAX_ENTRIES 8

/*
** Super Root Node
*/
typedef struct _tag_SRN
{
    DRM_UINT64    ui64Timestamp;    /* updates every time SRN is updated */
    DRM_DWORD     dwSRNSize;        /* super root node size */
    DRM_DWORD     dwBlockSize;      /* File block size */
    DRM_DWORD     eBlockNumType;    /* DRM_DST_BLKNUMTYPE */
    DRM_DWORD     nFreeListHead;
    DRM_DWORD     nNsStoreRootBlockNum;
    DRM_DWORD     nHighestFormattedBlockNum;  /* block num of the highest formated block */
    DRM_BYTE      bSRNHash [__CB_DECL(MD5DIGESTLEN)];    /* MD5 hash value of SRN */
} _SRN;

/*
** HDS context
*/
typedef struct _tag_Context
{
    DRM_BOOL fCSInited;
    OEM_CRITICAL_SECTION oCS;
    DRM_DWORD   dwContextSize;
    DRM_BOOL    fInited;
    DRM_DWORD   eContextSignature;
    OEM_FILEHDL fp;
    DRM_VOID   *pOEMContext;
    DRM_MD5_CTX contextMD5;
    DRM_DWORD   nGrowbySizeinKB;
    DRM_DWORD   dwStoreVersion;

    /* computed when HDS is 'opened' */
    DRM_DWORD   nImagesize_FileBlockHDR;     /* file image size of _CommBlockHDR, not including payload */
    DRM_DWORD   nImagesize_DataBlockHDR;     /* file image size of _DataBlockHDR, not including payload */
    DRM_DWORD   nImagesize_DataBlockPayload; /* payload size of a _DataBlockHDR */
    DRM_DWORD   nDataBlockPayloadPos;        /* payload pos from begining of a _DataBlockHDR */

    /* Cache for namespace store entries */
    _NamespaceCacheEntry namespaceCache[DRM_HDS_NAMESPACECACHE_MAX_ENTRIES];

    /* work buffer initialized when HDS is opened */
    DRM_STACK_ALLOCATOR_CONTEXT oHeap;

    _SRN oSRN;    /* super root node, pbStack points to the area after oSRN */
} _HdsContext;

/*
** HDS Config context
*/
typedef struct _tag_CfgContext
{
    DRM_DWORD wContextSize;
    DRM_DWORD eContextSignature;
    DRM_BOOL fInited;
    _HdsContext *pHDS;
    DRM_BYTE oNamespace[__CB_DECL(DRM_HDS_NSNAME_SIZE)];

    /* computed when a Namespace is 'used' */
    DRM_DWORD nCfgRootBlockNum;
    DRM_DWORD wMaxNumChildren;                /* # of children of the current selected Namespace */
    DRM_DWORD nImagesize_ChildBlockHDR;       /* file image size of _ChildBlockHDR, not including payload */
    DRM_DWORD nImagesize_ChildAllocTable;     /* file image size of ChildAlloc table of _ChildBlockHDR and _NSRootBlock */
    DRM_DWORD nImagesize_ChildBlockPayload;   /* payload size of _ChildBlockHDR  */
    DRM_DWORD nChildBlockPayloadPos;          /* payload pos from begining of _ChildBlockHDR */
    DRM_WORD  wBloomBytesM;
    DRM_WORD  wBloomK;
} _NsContext;


#define Memsize_FileBlock  SIZEOF(_CommBlockHDR)
typedef struct _tag_GenericBlockHeader {
    DRM_UINT64  ui64TimeStamp;
    DRM_BYTE    bBlockHash [__CB_DECL(MD5DIGESTLEN)];   /* MD5 hash of the above */
    DRM_DWORD   nParentBlockNum;
    DRM_BYTE    bBlockType;
} _CommBlockFileHDR;    /*_FileImage; */

typedef struct _tag_FileBlock
{
    /* computed at run time */
    DRM_DWORD nBlockNum;
    _NsContext *pNS;

    /* read from file */
    union
    {
        _CommBlockFileHDR _image;
        DRM_BYTE bFileImage[__CB_DECL(SIZEOF( _CommBlockFileHDR ))];
    } File;
} _CommBlockHDR;


typedef struct _tag_ChildBlockHeader
{
    DRM_DWORD nFreeMem;
    DRM_BYTE bBloomData[HDS_CHILDBLOCK_BLOOM_MAX_M];
    DRM_BYTE bChildAllocTable[DRM_HDS_MAXIMUM_CHILDREN*eDRM_DSTBLKNUM_DWORD];
    DRM_BYTE bReserved;
} _ChildBlockFileHDR;


#define GetMemsize_ChildBlock(cfg)    (SIZEOF(_ChildBlockHDR))
#define GetMaxMemsize_ChildBlock()    (SIZEOF(_ChildBlockHDR))
typedef struct _tag_ChildBlock
{
    _CommBlockHDR oBlockHeader;    /* derive from _CommBlockHDR */

    /* calculated during init'd */
    DRM_DWORD nCurrSlotPos;
    DRM_DWORD nNextSlotPos;
    DRM_DWORD nPayloadSize;
    union
    {
        DRM_BYTE bFileImage[__CB_DECL(SIZEOF(_ChildBlockFileHDR))];
        _ChildBlockFileHDR _image;
    } File;
} _ChildBlockHDR;

typedef struct _tag_DataBlockHeader {
    DRM_DWORD nCascadingBlockNum;
} _DataBlockFileHDR;


#define GetMemsize_DataBlock()   SIZEOF(_DataBlockHDR)
typedef struct _tag_DataBlock
{
    _CommBlockHDR oBlockHeader;    /* derive from _CommBlockHDR */

    DRM_DWORD nPayloadSize;
    union
    {
        DRM_BYTE bFileImage[__CB_DECL(SIZEOF(DRM_DWORD))];
        _DataBlockFileHDR _image;
    } File;
} _DataBlockHDR;



typedef enum
{
    eSlotIsNamespace = 0x00000001,
    eSlotIsHidden    = 0x00000002
} _ESlotAtributes;

/*
** record header structure precedes the actual storage of data record
*/
typedef struct _tag_SlotHeader
{
    DRM_DWORD   dwSlotSize;           /* actual Data Record Size */
    DRM_DWORD   dwAttributes;         /* Attributes for this slot (see _ESlotAtributes) */
    DRM_DST_KEY oHashkey;
    DRM_DST_KEY oUniquekey;
} _SlotHeader;


/*
** License FindFirst /  FindNext context
*/
typedef struct _tag_SlotContext
{
    DRM_DWORD dwContextSize;
    DRM_DWORD eContextSignature;
    DRM_DWORD eStatus;
    _NsContext *pNS;
    DRM_DST_LOCKMODE eLockMode;

    /* cache of search result for slot allocation */
    DRM_DWORD nBlockWithLargestFreeSpace;
    DRM_DWORD dwLargestSpace;

    _CommBlockHDR oFileBlock;      /* a copy of the file block in _ChildBlockHDR for verification purpose */
    _CommBlockHDR *pCurrChildBlock; /* pointer of the _ChildBlockHDR containing the Slot, pointing somewhere in bBuff */
    DRM_DWORD dwSlotPosInBlock;   /* the position in ChildBlock's payload where the slot is located (at begining _SlotHeader ) */
    _SlotHeader oSlotHeader;    /* Slot header record in _ChildBlockHDR */
    DRM_DWORD dwSeekPointer;      /* the current position in Slot where next slot read/write occurs */

    /* the following is valid if slot data is stored in _DataBlockHDR chain */
    DRM_DWORD dwNumofDataBlockVisited;  /* num of _DataBlockHDR visited not including current one */
    DRM_DWORD dwFirstDataBlockNum;    /* first _DataBlockHDR number in the chain */
    _CommBlockHDR *pCurrDataBlock;

    /* buffer to contain _ChildBlockHDR and _DataBlockHDR */
    DRM_BYTE bBuff [1];  /* size = dynamic size of _ChildBlockHDR + _DataBlockHDR */
} _SlotContext;

/*
** Slot Enum context
** this structure's size must be greater than or equal to CALC_MAXENUMCONTEXTLEN
*/
typedef struct _tag_EnumContext
{
    DRM_DWORD wContextSize;
    DRM_DWORD eContextSignature;
    _NsContext *pNS;
    DRM_BOOL fInited;

    _CommBlockHDR oFileBlock;      /* a copy of the file block in _ChildBlockHDR for verification purpose */
    _SlotHeader oSlotHeader;    /* current slot header */

    DRM_DST_LOCKMODE eLockMode;
    DRM_BOOL fIsQuery;             /* TRUE if oHashKey is not NULL, FALSE if enum all */
    DRM_DST_KEY oHashKey;

    DRM_BOOL fCurrBlockIsValid;
    _CommBlockHDR oCurrBlock;  /* this field must be located at end of structure */
} _EnumContext;

typedef struct _tag_BlockScanContext
{
    DRM_DWORD                cbContext;
    DRM_DWORD                eContextSignature;
    _NsContext              *pcontextNS;
    DRM_BOOL                 fInited;
    _CommBlockHDR            blockheader;  /* a copy of the file block in _ChildBlockHDR for verification purpose */
    _SlotHeader              slotheader;   /* current slot header */
    DRM_DST_LOCKMODE         lockmode;
    DRM_DST_KEY              keyUnique;
    const DRM_DST_KEY       *pkeyHash;  /* array of KIDs to delete */
    DRM_DWORD                cKeysHash; /* size of array */
    DRM_DWORD                cKeysFound;  /* number of KIDs marked for deletion thus far */
    DRM_DWORD                iKeyCurrent; /* index of next unmarked KID in the array */
    DRM_BOOL                 fCurrBlockIsValid;
    _ChildBlockHDR           blockheaderCurrent;  /* this field must be located at end of structure */
} _BlockScanContext;

typedef struct _tag_SlotHint
{
    DRM_DWORD nSlotPosInBlock;
    DRM_DWORD nBlockNum;
} _SlotHint;

/* HDS context sizes */
#define DRM_HDS_CONTEXT_LEN HDS_CONTEXT_LENGTH(SIZEOF(_SRN))
#define DRM_HDS_NAMESPACE_CONTEXT_LEN (SIZEOF( _NsContext ))
#define DRM_HDS_SLOT_CONTEXT_LEN       CALC_MAXSLOTCONTEXTLEN
#define DRM_HDS_ENUM_CONTEXT_LEN       CALC_MAXENUMCONTEXTLEN
#define DRM_HDS_SLOT_HINT_LEN          (SIZEOF(_SlotHint))

DRM_API DRM_NO_INLINE DRM_RESULT DRM_HDSIMPL_AllocBlockBuffer(
    __in  _NsContext     *f_pNS,
    __in  _EBlockType     f_eBlockType,
    __out _CommBlockHDR **f_ppBlock );

EXIT_PK_NAMESPACE;

#endif  /* _HDS_IMPL_H */


