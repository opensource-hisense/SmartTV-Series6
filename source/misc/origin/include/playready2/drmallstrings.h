/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRMALLSTRINGS_H__
#define __DRMALLSTRINGS_H__

ENTER_PK_NAMESPACE;

DRM_API DRM_VOID DRM_InitAllStrings();

/*
** Every time a string is protected, it has to be added to one of these
** corresponding arrays. The size of these arrays must be updated here
** to enable compile time tests.
*/

#define CHAR_STRING_COUNT 432
extern DRM_STR_CONST DRM_CHAR * g_rpcAllCharStrings[CHAR_STRING_COUNT];

#define WCHAR_STRING_COUNT 304
extern DRM_STR_CONST DRM_WCHAR * g_rpwcAllWCharStrings[WCHAR_STRING_COUNT];
EXIT_PK_NAMESPACE;

/*
** This is used in testing to verify that the correct strings are encoded and decoded.
** It cannot be replaced by mathematical expressions from constants above because
** it is used to create variable names consisting of these numbers.
*/
#define STRING_TOTAL_COUNT 736

#endif /* __DRMALLSTRINGS_H__ */