/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRM_TOKEN_H__
#define __DRM_TOKEN_H__

#include <drmtypes.h>
#include <drmpragmas.h>

ENTER_PK_NAMESPACE;

typedef enum
{
    /* Tokens expected from the expression */
    TOKEN_VARIABLE=0,
    TOKEN_FUNCTION,

    TOKEN_LONG,
    TOKEN_DATETIME,
    TOKEN_BYTEBLOB, /* Indicates that the data is variable length raw binary */
    TOKEN_STRING,

    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_ADD,
    TOKEN_SUB,
    TOKEN_MUL,
    TOKEN_DIV,
    TOKEN_MOD,
    TOKEN_PREINCR,
    TOKEN_POSTINCR,
    TOKEN_PREDECR,
    TOKEN_POSTDECR,
    TOKEN_ASSIGN,
    TOKEN_LESS,
    TOKEN_LESSEQ,
    TOKEN_GREAT,
    TOKEN_GREATEQ,
    TOKEN_NOTEQ,
    TOKEN_EQ,
    TOKEN_NOT,
    TOKEN_AND,
    TOKEN_OR,
    TOKEN_IF,
    TOKEN_COLON,
    TOKEN_SEMICOLON,
    TOKEN_OPEN,
    TOKEN_CLOSE,
    TOKEN_COMMA,
    TOKEN_UNKNOWN,

    /* For internal Use of the processing algorithm */
    TOKEN_IFSKIP,
    TOKEN_COLONSKIP,
    TOKEN_ANDSKIP,
    TOKEN_ORSKIP,
    TOKEN_UNARYSYNC, /* indicates that the pre unary operator just pushed into operator stack needs  right operand. */
    TOKEN_FUNCTIONSYNC, /* indicates that the fucntion sysmbol just pushed need right arguments. Popping of arguments should stop at this token. */
} DRM_EXPR_TOKEN_TYPE;

typedef enum
{
    FN_DATEADD,
    FN_DATEDIFF,
    FN_MIN,
    FN_MAX,
    FN_INDEX,
    FN_DATEPART,
    FN_VERSIONCOMPARE,
    FN_DELETELICENSE,
    FN_EXISTS,
    FN_LENGTH
} DRM_EXPR_FUNCTION_TYPE;

/*
   In the context of the expression evaluator any token can be placed in here.  When one of these tokens
   is given to the secure store the only valid token types are
       TOKEN_LONG and  TOKEN_DATETIME
*/


#if defined (DRM_MSC_VER)
#pragma warning(disable:4103)
#pragma pack(push)
#pragma pack(1)
#elif defined(__MACINTOSH__) && DRM_64BIT_TARGET
#pragma pack(push, 1)
#endif

typedef struct tagTOKEN
{
    DRM_DWORD TokenType;
    union _tagTokenValue
    {
        DRM_UINT64 u64DateTime;
        DRM_LONG lValue;
        DRM_CONST_STRING stringValue;
        DRM_DWORD fnValue;
        DRM_BYTEBLOB byteValue;
    } val;
}TOKEN;

/*
** NOTE:  This structure should be 12 bytes long to allow for binary compatability of the secure store.
**        Using MS Visual C++ we have to use #pragma pack to achieve this
*/
struct tagPERSISTEDTOKEN
{
    DRM_DWORD TokenType;
    union _tagPersistedTokenValue
    {
        DRM_UINT64 u64DateTime;
        DRM_LONG   lValue;
        DRM_WORD   wValue;
    } val;
} DRM_PACKED;

typedef struct tagPERSISTEDTOKEN PERSISTEDTOKEN;

/* Calculates the number of bytes the token takes up when persisted */
#define CALC_PERSISTEDTOKEN_FILE_LENGTH(pToken) (pToken->TokenType == TOKEN_BYTEBLOB ? MAX( SIZEOF( PERSISTEDTOKEN ), SIZEOF( PERSISTEDTOKEN ) + pToken->val.byteValue.cbBlob + (pToken->val.byteValue.cbBlob % 2)) : SIZEOF( PERSISTEDTOKEN ) )

#if defined (DRM_MSC_VER)
#pragma pack(pop)
#pragma warning(default:4103)
#elif defined(__MACINTOSH__) && DRM_64BIT_TARGET
#pragma pack(pop)
#endif

EXIT_PK_NAMESPACE;

#endif /* __DRM_TOKEN_H__ */
