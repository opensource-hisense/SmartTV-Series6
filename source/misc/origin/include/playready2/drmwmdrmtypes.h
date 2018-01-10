/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRMWMDRMTYPES_H__
#define __DRMWMDRMTYPES_H__

#include <drmtypes.h>
#include <drmtoken.h>

ENTER_PK_NAMESPACE;

typedef DRM_RESULT (DRM_CALL *pfnGetVariable)(const DRM_CONST_STRING*, TOKEN*, DRM_VOID*);
typedef DRM_RESULT (DRM_CALL *pfnSetVariable)(const DRM_CONST_STRING*, const TOKEN*, TOKEN*, DRM_VOID*);

#define DRM_EXPR_EVAL_MAX_TOKEN_STACK_SIZE 15

typedef struct tagDRM_WMDRM_EXPR_EVAL_INTERNAL_DATA
{
    TOKEN rgOperandTokenStack[DRM_EXPR_EVAL_MAX_TOKEN_STACK_SIZE];
    TOKEN rgOperatorTokenStack[DRM_EXPR_EVAL_MAX_TOKEN_STACK_SIZE];
    DRM_DWORD dwOperandStack;
    DRM_DWORD dwOperatorStack;
    DRM_BOOL fShortCircuit;
} DRM_WMDRM_EXPR_EVAL_INTERNAL_DATA;

typedef struct tagDRM_WMDRM_EXPR_EVAL_CONTEXT
{
    /* Data the caller must set  */
    pfnGetVariable GetVariable;     /* Function pointers so variables can be fetched/set */
    pfnSetVariable SetVariable;
    DRM_VOID* pvOpaqueData;         /* Pointer to be passed into GetVariable() and SetVariable() */
    DRM_KID KID;
    DRM_LID LID;

    /* Internal memory sandbox for ExprEval to use.  Caller doesn't set this memory */
    DRM_WMDRM_EXPR_EVAL_INTERNAL_DATA ExprEvalData;
} DRM_WMDRM_EXPR_EVAL_CONTEXT;

EXIT_PK_NAMESPACE;

#endif /* __DRMWMDRMTYPES_H__ */

