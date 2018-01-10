/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __OEMCBC_H__
#define __OEMCBC_H__

#include <drmtypes.h>

ENTER_PK_NAMESPACE;

typedef struct _CBCKey
{
    DRM_DWORD a1, b1, c1, d1, e1, f1, a2, b2, c2, d2, e2, f2;
} DRM_CBCKey;

/*********************************************************************
**
**  Function:  DRM_CBC_Mac
**
**  Synopsis:  Create a 64-bit MAC
**
**  Arguments:
**     [pbData] -- Byte pointer to DWORD blocks that are to be MAC'd
**     [cBlocks] -- Length of pbData in DWORD's
**     [rgdwKey2] -- 2 DWORD array to hold the 64-bit result
**     [pCBCkey] -- Key structure filled by the caller.
**
**  Returns:  None
** Notes: dwNumBlocks must be in DWORDS and it should be multiple of
**        DWORD. Suppose if length is 8 bytes, dwNumBlocks should be 2
*********************************************************************/
DRM_API DRM_VOID DRM_CALL DRM_CBC_Mac(
    __in   const DRM_BYTE      *pbData,
    __in         DRM_DWORD      cBlocks,
    __out        DRM_DWORD      rgdwKeys[2],
    __in   const DRM_CBCKey    *pCBCkey );

/*********************************************************************
**
**  Function:  DRM_CBC_InverseMac
**
**  Synopsis:  Inverse MAC function.  It decrypts the last two bloacks of pdwData
**              ( replaces 64-bit ciphertext pdwData[dwNumBlocks-1] and pdwData[dwNumBlocks-2]
**              with plaintext ).
**
**  Arguments:
**     [pbData] -- Byte pointer to DWORD blocks that are to be MAC'd( inverse MAC )
**     [cBlocks] -- Length of pbData in DWORD's
**     [key] -- Key structure filled by caller
**     [ikey] -- Inverse key structure filled by caller.
**
**  Returns:
**
** Notes: dwNumBlocks must be in DWORDS and it should be multiple of
**        DWORD. Suppose if length is 8 bytes, dwNumBlocks should be 2
**
*********************************************************************/
DRM_API DRM_VOID DRM_CALL DRM_CBC_InverseMac(
    __inout_bcount( cBlocks * sizeof(DRM_DWORD) )        DRM_BYTE   *pbData,
    __in                                                 DRM_DWORD   cBlocks,
    __in                                           const DRM_CBCKey *key,
    __in                                           const DRM_CBCKey *ikey );

DRM_API DRM_VOID DRM_CALL DRM_CBC64InvKey(
    __in const DRM_CBCKey *cbckey,
    __out      DRM_CBCKey *cbcInvKey );

/*********************************************************************
**
**  Function:  DRM_MAC_inv32
**
**  Synopsis:  Returns the inverse of n ( inverse in terms of what the CBC Mac inverse code wants ).
**
**  Arguments:
**     [n] -- Value of n to compute inverse of.
**
**  Returns:  Inverse of n
**
*********************************************************************/
DRM_API DRM_DWORD DRM_CALL DRM_MAC_inv32( DRM_DWORD n );

typedef struct __tagCBCState
{
    DRM_DWORD sum,t;
    DRM_BYTE  buf[__CB_DECL(8)];
    DRM_DWORD dwBufLen;
} DRM_CBCState;

DRM_API DRM_VOID DRM_CALL DRM_CBC64Init(
    __inout                                       DRM_CBCKey   *cbckey,
    __inout                                       DRM_CBCState *cbcstate,
    __in_bcount( SIZEOF( DRM_DWORD ) * 12 ) const DRM_BYTE     *pKey );

#define DRMV2_MAC_LENGTH 8

DRM_API DRM_VOID DRM_CALL DRM_CBC64Update(
    __in                  const DRM_CBCKey    *key,
    __inout                     DRM_CBCState  *cbcstate,
    __in                        DRM_DWORD      cbData,
    __in_bcount( cbData ) const DRM_BYTE      *pbData );

DRM_API DRM_DWORD DRM_CALL DRM_CBC64Finalize(
    __in            const DRM_CBCKey   *key,
    __inout               DRM_CBCState *cbcstate,
    __out_ecount(1)       DRM_DWORD    *pKey2 );

DRM_API DRM_NO_INLINE DRM_DWORD DRM_CALL DRM_CBC64Invert(
    __in            const DRM_CBCKey  *key,
    __in            const DRM_CBCKey  *ikey,
    __in                  DRM_DWORD    MacA1,
    __in                  DRM_DWORD    MacA2,
    __in                  DRM_DWORD    MacB1,
    __in                  DRM_DWORD    MacB2,
    __out_ecount(1)       DRM_DWORD   *pInvKey2 );

DRM_API DRM_VOID DRM_CALL DRM_CBC64InitState( __inout DRM_CBCState *cbcstate );

EXIT_PK_NAMESPACE;

#endif /* __OEMCBC_H__ */

