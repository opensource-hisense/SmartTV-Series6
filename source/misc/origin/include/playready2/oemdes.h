/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __OEMDES_H__
#define __OEMDES_H__

#include <drmtypes.h>

ENTER_PK_NAMESPACE;

#ifndef __DES_H__

typedef struct _destable
{
    DRM_DWORD keytab[16][2];
} DESTable;

#define DES_TABLESIZE    SIZEOF(DESTable)
#define DES_BLOCKLEN    8
#define DES_KEYSIZE        8

#endif // __DES_H__

#define DES_ENCRYPT     1
#define DES_DECRYPT     0


/*********************************************************************
**
**  Function:  deskey
**
**  Synopsis:  Fill in the DESTable struct with the decrypt and encrypt
**               key expansions.
**
**               Assumes that the second parameter points to DES_KEYSIZE
**             bytes of key.
**
**  Arguments:
**     [pTable] -- A DESTable structure that will be filled according to the DES key-schedule algorithm.
**     [rgbKey] -- The DES symmetric key to be used.
**
**  Returns:  None
**
*********************************************************************/

DRM_API DRM_VOID DRM_CALL DRM_DES_KeySetup(
    __out                            DESTable *pTable,
    __in_bcount( DES_KEYSIZE ) const DRM_BYTE  rgbKey[__CB_DECL(DES_KEYSIZE)] );


/*********************************************************************
**
**  Function:  DRM_DES_Cipher
**
**  Synopsis:
**
**  Arguments:
**     [rgbIn] -- Array of bytes to encrypt
**     [rgbOut] -- Encrypted array of bytes
**     [pTable] -- DES table initialized by DRM_DES_KeySetup
**     [op] -- Operation to perform ( DES_ENCRYPT or DES_DECRYPT )
**
**  Returns:  None
**
*********************************************************************/

DRM_API DRM_VOID DRM_CALL DRM_DES_Cipher(
    __in_bcount( DES_BLOCKLEN )  const DRM_BYTE  rgbIn [__CB_DECL(DES_BLOCKLEN)],
    __out_bcount( DES_BLOCKLEN )       DRM_BYTE  rgbOut[__CB_DECL(DES_BLOCKLEN)],
    __in                               DESTable *pTable,
    __in                               DRM_LONG  op );


#define DRM_DES_Encrypt( x, y, z ) \
    DRM_DES_Cipher( (x), (y), (z), DES_ENCRYPT )

#define DRM_DES_Decrypt( x, y, z ) \
    DRM_DES_Cipher( (x), (y), (z), DES_DECRYPT )

EXIT_PK_NAMESPACE;

#endif /* __OEMDES_H__ */
