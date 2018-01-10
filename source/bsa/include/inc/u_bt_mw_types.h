/******************************************************************************
 *
 *  Copyright (C) 1999-2012 Broadcom Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at:
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 ******************************************************************************/

#ifndef U_BT_MW_TYPES_H
#define U_BT_MW_TYPES_H

#if !defined (_NO_TYPEDEF_UINT8_) && !defined (_TYPEDEF_UINT8_)
typedef unsigned char UINT8;

#define _TYPEDEF_UINT8_
#endif

#if !defined (_NO_TYPEDEF_VOID_)  && !defined (_TYPEDEF_VOID_)
#define VOID void

#define _TYPEDEF_VOID_
#endif

#if !defined (_NO_TYPEDEF_UINT32_) && !defined (_TYPEDEF_UINT32_)
typedef unsigned int UINT32;

#define _TYPEDEF_UINT32_
#endif

#if !defined (_NO_TYPEDEF_INT32_) && !defined (_TYPEDEF_INT32_)

typedef int INT32;

#define _TYPEDEF_INT32_
#endif

#if !defined (_NO_TYPEDEF_INT8_) && !defined (_TYPEDEF_INT8_)
typedef char INT8;

#define _TYPEDEF_INT8_
#endif

typedef char CHAR;
typedef unsigned char BOOL;
typedef unsigned char BOOLEAN;

#ifndef FALSE
#define FALSE    0
#endif
#ifndef TRUE
#define TRUE     1
#endif

#ifndef EXPORT_SYMBOL
#define EXPORT_SYMBOL
#endif

//typedef unsigned char UINT8;
typedef unsigned short UINT16;
//typedef unsigned int UINT32;
typedef unsigned long long UINT64;
//typedef char INT8;
typedef short INT16;
//typedef int INT32;
typedef long long INT64;


#endif /* U_BT_MW_TYPES_H */
