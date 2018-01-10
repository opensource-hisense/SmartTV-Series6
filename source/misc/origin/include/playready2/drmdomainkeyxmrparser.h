/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/


#ifndef __DRMDOMAINKEYXMRPARSER_H__
#define __DRMDOMAINKEYXMRPARSER_H__

#include <drmtypes.h>

ENTER_PK_NAMESPACE;

#define DRM_DOMKEYXMR_HEADER_CONSTANT 0x444b4559 /* DKEY */
#define DRM_DOMKEYXMR_HEADER_VERSION  1

#define DRM_DOMKEYXMR_SESSIONKEY_ENCTYPE_ECCP256 1

#define DRM_DOMKEYXMR_OBJTYPE_PRIVKEYCONTAINER  0x500
#define DRM_DOMKEYXMR_OBJTYPE_ACCOUNTID         0x501
#define DRM_DOMKEYXMR_OBJTYPE_NONCE             0x502
#define DRM_DOMKEYXMR_OBJTYPE_SESSIOINKEY       0x503
#define DRM_DOMKEYXMR_OBJTYPE_PRIVKEY           0x504

#define DRM_DOMKEYXMR_PRIVKEYOBJ_MIN_LENGTH 20

#define DRM_DOMKEYXMR_PRIVKEY_TYPE_ECCP256         2
#define DRM_DOMKEYXMR_PRIVKEY_ENCTYPE_AESCTR       2
#define DRM_DOMKEYXMR_PRIVKEY_ENCTYPE_MIXED_AESECB 3

/*
** XMR strucutre for DomainKeys data
*/
typedef struct _tagDRM_DOMKEYXMR_HEADER
{
    DRM_DWORD  dwConstant;
    DRM_DWORD  dwVersion;
    DRM_DWORD  dwLength;
    DRM_DWORD  dwSignedLength;
} DRM_DOMKEYXMR_HEADER;

typedef DRM_OBFUS_FIXED_ALIGN struct _tagDRM_DOMKEYXMR_SESSIONKEY
{
    DRM_WORD   wFlags;
    DRM_WORD   wType;
    DRM_DWORD  dwLength;
    DRM_WORD   wKeyType;
    DRM_WORD   wEncryptionType;
    DRM_DWORD  dwKeyLength;
DRM_OBFUS_PTR_TOP
    DRM_BYTE  *pbData;
DRM_OBFUS_PTR_BTM
} DRM_DOMKEYXMR_SESSIONKEY;

typedef struct _tagDRM_DOMKEYXMR_PRIVKEYCONTAINER
{
    DRM_WORD  wFlags;
    DRM_WORD  wType;
    DRM_DWORD dwLength;
} DRM_DOMKEYXMR_PRIVKEYCONTAINER;

typedef DRM_OBFUS_FIXED_ALIGN struct _tagDRM_DOMKEYXMR_PRIVKEY
{
    DRM_WORD  wFlags;
    DRM_WORD  wType;
    DRM_DWORD dwLength;
    DRM_DWORD dwRevision;
    DRM_WORD  wKeyType;
    DRM_WORD  wEncryptionType;
    DRM_DWORD dwKeyLength;
DRM_OBFUS_FILL_BYTES(4)
DRM_OBFUS_PTR_TOP
    DRM_BYTE *pbData;
DRM_OBFUS_PTR_BTM
} DRM_DOMKEYXMR_PRIVKEY;

/*
** ---------------------------------------
** DomainKey XMR Parser implementation API functions
** ---------------------------------------
*/

DRM_API DRM_RESULT DRM_CALL DRM_DOMKEYXMR_GetHeader(
   __in_bcount(f_cbData) const DRM_BYTE              *f_pbData,
   __in                        DRM_DWORD              f_cbData,
   __inout_ecount(1)           DRM_DWORD             *f_pbOffset,
   __inout_ecount(1)           DRM_DOMKEYXMR_HEADER  *f_poHeader );

DRM_API DRM_RESULT DRM_CALL DRM_DOMKEYXMR_GetSessionKey(
   __in_bcount(f_cbData) DRM_BYTE  *f_pbData,
   __in                  DRM_DWORD  f_cbData,
   __inout_ecount(1)     DRM_DWORD *f_pbOffset,
   __inout_ecount(1)     DRM_DOMKEYXMR_SESSIONKEY  *f_poKeyObj);

DRM_API DRM_RESULT DRM_CALL DRM_DOMKEYXMR_GetPrivKeyContainer(
   __in_bcount(f_cbData) const DRM_BYTE                        *f_pbData,
   __in                        DRM_DWORD                        f_cbData,
   __inout_ecount(1)           DRM_DWORD                       *f_pbOffset,
   __inout_ecount(1)           DRM_DOMKEYXMR_PRIVKEYCONTAINER  *f_poKeyContainer );

DRM_API DRM_RESULT DRM_CALL DRM_DOMKEYXMR_GetPrivkey(
   __in_bcount(f_cbData) DRM_BYTE  *f_pbData,
   __in                  DRM_DWORD  f_cbData,
   __inout_ecount(1)     DRM_DWORD *f_pbOffset,
   __inout_ecount(1)     DRM_DOMKEYXMR_PRIVKEY *f_poKeyObj);

EXIT_PK_NAMESPACE;

#endif /* __DRMDOMAINKEYXMRPARSER_H__ */
