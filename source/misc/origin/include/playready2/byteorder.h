/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __BYTEORDER_H__
#define __BYTEORDER_H__

#include <drmtypes.h>
#include <drmpragmas.h>

#define DWORD_TO_BYTES(to_bytes, from_dword) do {           \
        DRM_DWORD temp = (from_dword);                      \
        PUT_BYTE((to_bytes),0, (DRM_BYTE)temp); temp>>=8;   \
        PUT_BYTE((to_bytes),1, (DRM_BYTE)temp); temp>>=8;   \
        PUT_BYTE((to_bytes),2, (DRM_BYTE)temp); temp>>=8;   \
        PUT_BYTE((to_bytes),3, (DRM_BYTE)temp);             \
    } while (FALSE)

#define BYTES_TO_DWORD(to_dword, from_bytes) do {   \
        to_dword = GET_BYTE((from_bytes),3);        \
        to_dword <<= 8;                             \
        to_dword |= GET_BYTE((from_bytes),2);       \
        to_dword <<= 8;                             \
        to_dword |= GET_BYTE((from_bytes),1);       \
        to_dword <<= 8;                             \
        to_dword |= GET_BYTE((from_bytes),0);       \
    } while (FALSE)

#define BITS_PER_STANDARD_BYTE 8

#define ROTATE_LEFT_WORD(x, n)   ((DRM_WORD)  (((DRM_WORD)  (((x) << (n)) & 0xFFFF)) | ((DRM_WORD)  (x) >> (16-(n)))))
#define ROTATE_RIGHT_WORD(x, n)  ((DRM_WORD)  (((DRM_WORD)  (x) >> (n)) | ((DRM_WORD)  (((x) << (16-(n))) & 0xFFFF))))
#define ROTATE_LEFT_DWORD(x, n)  ((DRM_DWORD) (((DRM_DWORD) (((x) << (n)) & 0xFFFFFFFF)) | ((DRM_DWORD) (x) >> (32-(n)))))
#define ROTATE_RIGHT_DWORD(x, n) ((DRM_DWORD) (((DRM_DWORD) (x) >> (n)) | ((DRM_DWORD) (((x) << (32-(n))) & 0xFFFFFFFF))))
#if DRM_SUPPORT_NATIVE_64BIT_TYPES
#define ROTATE_LEFT_QWORD(x, n)  ((DRM_UINT64)(((DRM_UINT64)(x) << (n)) | ((DRM_UINT64)(x) >> (64-(n)))))
#define ROTATE_RIGHT_QWORD(x, n) ((DRM_UINT64)(((DRM_UINT64)(x) >> (n)) | ((DRM_UINT64)(x) << (64-(n)))))
#endif /* DRM_SUPPORT_NATIVE_64BIT_TYPES */

#define ROTATE_LEFT(x, n)  (((x) << (n)) | ((x) >> (32-(n))))
#define ROTATE_RIGHT(x, n) (((x) >> (n)) | ((x) << (32-(n))))

#define FLIP_WORD_BYTES(w) ( ROTATE_LEFT_WORD((DRM_WORD)(w), 8) )

/* for initialization of constant values, we define special macro for flipping bytes in DRM_DWORD */
#define FLIP_DWORD_BYTES_CONST(dw) ((ROTATE_RIGHT((dw), 24) & 0x00ff00ff) | (ROTATE_RIGHT((dw), 8) & 0xff00ff00))

#if DRM_SUPPORT_NATIVE_64BIT_TYPES
#if DRM_BUILD_PROFILE == DRM_BUILD_PROFILE_IOS
#define FLIP_DWORD_BYTES(dw) __builtin_bswap32(dw)
#define FLIP_QWORD_BYTES(qw) __builtin_bswap64(qw)
#elif (defined(_M_IX86) || defined(_M_AMD64) || defined(_XBOX)) && !defined(_MANAGED)
#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */
unsigned long  __cdecl _byteswap_ulong (unsigned long _Long);
unsigned __int64 __cdecl _byteswap_uint64(unsigned __int64 _Int64);
#ifdef __cplusplus
} /* extern "C"*/
#endif /* __cplusplus */
PRAGMA_INTRINSIC(_byteswap_ulong)
PRAGMA_INTRINSIC(_byteswap_uint64)
#define FLIP_DWORD_BYTES(dw) ((DRM_DWORD)_byteswap_ulong((unsigned long)(dw)))
#define FLIP_QWORD_BYTES(qw) ((DRM_UINT64)_byteswap_uint64((unsigned __int64)(qw)))
#else
#define FLIP_DWORD_BYTES(dw) FLIP_DWORD_BYTES_CONST(dw)
#define FLIP_QWORD_BYTES(qw) ( FLIP_DWORD_BYTES(qw>>32) | ( ( (DRM_UINT64) FLIP_DWORD_BYTES((DRM_DWORD)qw) ) << 32 ) )
#endif
#else /* DRM_SUPPORT_NATIVE_64BIT_TYPES */
#define FLIP_DWORD_BYTES(dw) FLIP_DWORD_BYTES_CONST(dw)
#define FLIP_QWORD_BYTES(qw) DRM_UI64HL(FLIP_DWORD_BYTES(DRM_UI64Low32(qw)),FLIP_DWORD_BYTES(DRM_UI64High32(qw)))
#endif /* DRM_SUPPORT_NATIVE_64BIT_TYPES */

#define WORDSWAP(d) ROTATE_LEFT(d, 16)

#define ASSIGN_1BYTE( dstaddr, dstidx, srcaddr, srcidx )   do { ((DRM_BYTE*)(dstaddr))[(dstidx)] = ((DRM_BYTE*)(srcaddr))[(srcidx)]; } while( FALSE )

#define ASSIGN_2BYTE( dstaddr, srcaddr )        do { ASSIGN_1BYTE( dstaddr, 0, srcaddr, 0 ); ASSIGN_1BYTE( dstaddr, 1, srcaddr, 1 ); } while( FALSE )

#define ASSIGN_4BYTE( dstaddr, srcaddr )        do { ASSIGN_1BYTE( dstaddr, 0, srcaddr, 0 ); ASSIGN_1BYTE( dstaddr, 1, srcaddr, 1 );  \
                                                     ASSIGN_1BYTE( dstaddr, 2, srcaddr, 2 ); ASSIGN_1BYTE( dstaddr, 3, srcaddr, 3 ); } while( FALSE )

#define ASSIGN_8BYTE( dstaddr, srcaddr )        do { ASSIGN_1BYTE( dstaddr, 0, srcaddr, 0 ); ASSIGN_1BYTE( dstaddr, 1, srcaddr, 1 );  \
                                                     ASSIGN_1BYTE( dstaddr, 2, srcaddr, 2 ); ASSIGN_1BYTE( dstaddr, 3, srcaddr, 3 );  \
                                                     ASSIGN_1BYTE( dstaddr, 4, srcaddr, 4 ); ASSIGN_1BYTE( dstaddr, 5, srcaddr, 5 );  \
                                                     ASSIGN_1BYTE( dstaddr, 6, srcaddr, 6 ); ASSIGN_1BYTE( dstaddr, 7, srcaddr, 7 ); } while( FALSE )

#define BYTES2WORD_LE(  word,  byte  )      ASSIGN_2BYTE( &(word), (byte) )
#define WORD2BYTES_LE(  byte,  word  )      ASSIGN_2BYTE( (byte),  &(word) )
#define BYTES2DWORD_LE( dword, byte  )      ASSIGN_4BYTE( &(dword), (byte) )
#define DWORD2BYTES_LE( byte,  dword )      ASSIGN_4BYTE( (byte), &(dword) )
#define BYTES2QWORD_LE( qword, byte  )      ASSIGN_8BYTE( &(qword), (byte) )
#define QWORD2BYTES_LE( byte,  qword )      ASSIGN_8BYTE( (byte), &(qword) )

#define BYTES2WORD_BE(  word,  byte  )      do { BYTES2WORD_LE( (word), (byte) ); FIX_ENDIAN_WORD( (word) ); }   while( FALSE )
#define WORD2BYTES_BE(  byte,  word  )      do { DRM_WORD __temp = (word);        FIX_ENDIAN_WORD( __temp );   WORD2BYTES_LE( (byte), __temp ); }  while( FALSE )
#define BYTES2DWORD_BE( dword, byte  )      do { BYTES2DWORD_LE( (dword), byte ); FIX_ENDIAN_DWORD( (dword) ); } while( FALSE )
#define DWORD2BYTES_BE( byte,  dword )      do { DRM_DWORD __temp = (dword);      FIX_ENDIAN_DWORD( __temp );  DWORD2BYTES_LE( (byte), __temp ); } while( FALSE )
#define BYTES2QWORD_BE( qword, byte  )      do { BYTES2QWORD_LE( (qword), byte ); FIX_ENDIAN_QWORD( (qword) ); } while( FALSE )
#define QWORD2BYTES_BE( byte,  qword )      do { DRM_UINT64 __temp = (qword);     FIX_ENDIAN_QWORD( __temp );  QWORD2BYTES_LE( (byte), __temp ); } while( FALSE )

#define COPY_WORD( byte, index, word )      do { ASSIGN_1BYTE( (byte), ((index)+0), &(word),  0 ); ASSIGN_1BYTE( (byte), ((index)+1), &(word),  1 ); } while( FALSE )

#define COPY_DWORD( byte, index, dword )    do { ASSIGN_1BYTE( (byte), ((index)+0), &(dword), 0 ); ASSIGN_1BYTE( (byte), ((index)+1), &(dword), 1 ); \
                                                 ASSIGN_1BYTE( (byte), ((index)+2), &(dword), 2 ); ASSIGN_1BYTE( (byte), ((index)+3), &(dword), 3 ); } while( FALSE )

#define COPY_QWORD( byte, index, qword )    do { ASSIGN_1BYTE( (byte), ((index)+0), &(qword), 0 ); ASSIGN_1BYTE( (byte), ((index)+1), &(qword), 1 ); \
                                                 ASSIGN_1BYTE( (byte), ((index)+2), &(qword), 2 ); ASSIGN_1BYTE( (byte), ((index)+3), &(qword), 3 ); \
                                                 ASSIGN_1BYTE( (byte), ((index)+4), &(qword), 4 ); ASSIGN_1BYTE( (byte), ((index)+5), &(qword), 5 ); \
                                                 ASSIGN_1BYTE( (byte), ((index)+6), &(qword), 6 ); ASSIGN_1BYTE( (byte), ((index)+7), &(qword), 7 ); } while( FALSE )

#define COPY_FROMBUFFER(to, from, index, size, buffersize)  do {ChkOverflow((index)+(size),(index));ChkBOOL((index)+(size)<=(buffersize),DRM_E_BUFFERTOOSMALL);DRM_BYT_CopyBytes((DRM_BYTE*)&(to),0,(from),(index),(size));(index)+=(size);} while( FALSE )

#define REVERSE_BYTES_WORD(w)               do { (w)  = FLIP_WORD_BYTES(w);   } while (FALSE)
#define REVERSE_BYTES_DWORD(dw)             do { (dw) = FLIP_DWORD_BYTES(dw); } while (FALSE)
#define REVERSE_BYTES_LONG(l)               do { (l) = (DRM_LONG)FLIP_DWORD_BYTES(l); } while (FALSE)
#if DRM_SUPPORT_NATIVE_64BIT_TYPES
#define REVERSE_BYTES_QWORD(qw)             do { (qw) = FLIP_QWORD_BYTES(qw); } while (FALSE)
#else
#define REVERSE_BYTES_QWORD(qw)             do { unsigned long _temp = qw.val[0]; qw.val[0] = FLIP_DWORD_BYTES(qw.val[1]); qw.val[1] = FLIP_DWORD_BYTES(_temp); } while ( FALSE )
#endif

/* Copies WORD written to buffer in little endian format into WORD variable */
#define LITTLEENDIAN_BYTES_TO_WORD(  word,  byte, index ) do { (word)   = ((DRM_BYTE*)(byte))[(index)+0];  (word)  = ROTATE_RIGHT_WORD((word),  8); \
                                                               (word)  |= ((DRM_BYTE*)(byte))[(index)+1];  (word)  = ROTATE_RIGHT_WORD((word),  8); } while( FALSE )

/* Copies DWORD written to buffer in little endian format into DWORD variable */
#define LITTLEENDIAN_BYTES_TO_DWORD( dword, byte, index ) do { (dword)  = ((DRM_BYTE*)(byte))[(index)+0]; (dword) = ROTATE_RIGHT_DWORD((dword), 8); \
                                                               (dword) |= ((DRM_BYTE*)(byte))[(index)+1]; (dword) = ROTATE_RIGHT_DWORD((dword), 8); \
                                                               (dword) |= ((DRM_BYTE*)(byte))[(index)+2]; (dword) = ROTATE_RIGHT_DWORD((dword), 8); \
                                                               (dword) |= ((DRM_BYTE*)(byte))[(index)+3]; (dword) = ROTATE_RIGHT_DWORD((dword), 8); } while( FALSE )

#if DRM_SUPPORT_NATIVE_64BIT_TYPES
/* Copies QWORD written to buffer in little endian format into QWORD variable */
#define LITTLEENDIAN_BYTES_TO_QWORD( qword, byte, index ) do { (qword)  = ((DRM_BYTE*)(byte))[(index)+0]; (qword) = ROTATE_RIGHT_QWORD((qword), 8); \
                                                               (qword) |= ((DRM_BYTE*)(byte))[(index)+1]; (qword) = ROTATE_RIGHT_QWORD((qword), 8); \
                                                               (qword) |= ((DRM_BYTE*)(byte))[(index)+2]; (qword) = ROTATE_RIGHT_QWORD((qword), 8); \
                                                               (qword) |= ((DRM_BYTE*)(byte))[(index)+3]; (qword) = ROTATE_RIGHT_QWORD((qword), 8); \
                                                               (qword) |= ((DRM_BYTE*)(byte))[(index)+4]; (qword) = ROTATE_RIGHT_QWORD((qword), 8); \
                                                               (qword) |= ((DRM_BYTE*)(byte))[(index)+5]; (qword) = ROTATE_RIGHT_QWORD((qword), 8); \
                                                               (qword) |= ((DRM_BYTE*)(byte))[(index)+6]; (qword) = ROTATE_RIGHT_QWORD((qword), 8); \
                                                               (qword) |= ((DRM_BYTE*)(byte))[(index)+7]; (qword) = ROTATE_RIGHT_QWORD((qword), 8); } while( FALSE )
#endif /* DRM_SUPPORT_NATIVE_64BIT_TYPES */

#define NETWORKBYTES_TO_WORD(word, byte, index)     do { (word)   = ((DRM_BYTE*)(byte))[(index)+0]; (word)  <<= 8; \
                                                         (word)  |= ((DRM_BYTE*)(byte))[(index)+1]; } while( FALSE )

#define NETWORKBYTES_TO_DWORD(dword, byte, index)   do { (dword)  = ((DRM_BYTE*)(byte))[(index)+0]; (dword) <<= 8; \
                                                         (dword) |= ((DRM_BYTE*)(byte))[(index)+1]; (dword) <<= 8; \
                                                         (dword) |= ((DRM_BYTE*)(byte))[(index)+2]; (dword) <<= 8; \
                                                         (dword) |= ((DRM_BYTE*)(byte))[(index)+3]; } while( FALSE )

#if DRM_SUPPORT_NATIVE_64BIT_TYPES
#define NETWORKBYTES_TO_QWORD(qword, byte, index)   do { (qword)  = ((DRM_BYTE*)(byte))[(index)+0]; (qword) <<= 8; \
                                                         (qword) |= ((DRM_BYTE*)(byte))[(index)+1]; (qword) <<= 8; \
                                                         (qword) |= ((DRM_BYTE*)(byte))[(index)+2]; (qword) <<= 8; \
                                                         (qword) |= ((DRM_BYTE*)(byte))[(index)+3]; (qword) <<= 8; \
                                                         (qword) |= ((DRM_BYTE*)(byte))[(index)+4]; (qword) <<= 8; \
                                                         (qword) |= ((DRM_BYTE*)(byte))[(index)+5]; (qword) <<= 8; \
                                                         (qword) |= ((DRM_BYTE*)(byte))[(index)+6]; (qword) <<= 8; \
                                                         (qword) |= ((DRM_BYTE*)(byte))[(index)+7]; } while( FALSE )
#endif /* DRM_SUPPORT_NATIVE_64BIT_TYPES */

#define NETWORKBYTES_FROMBUFFER_TO_WORD(word, byte, index, buffersize)   do { ChkOverflow( (index)+(SIZEOF(DRM_WORD)),  (index) ); ChkBOOL( (index)+(SIZEOF(DRM_WORD))  <= (buffersize), DRM_E_BUFFERTOOSMALL ); NETWORKBYTES_TO_WORD(  (word),  (byte), (index) ); (index) += (SIZEOF(DRM_WORD));  } while( FALSE )
#define NETWORKBYTES_FROMBUFFER_TO_DWORD(dword, byte, index, buffersize) do { ChkOverflow( (index)+(SIZEOF(DRM_DWORD)), (index) ); ChkBOOL( (index)+(SIZEOF(DRM_DWORD)) <= (buffersize), DRM_E_BUFFERTOOSMALL ); NETWORKBYTES_TO_DWORD( (dword), (byte), (index) ); (index) += (SIZEOF(DRM_DWORD)); } while( FALSE )

#if TARGET_LITTLE_ENDIAN

#define MAKE_WORD_BIG_ENDIAN(w)   FLIP_WORD_BYTES(w)
#define MAKE_DWORD_BIG_ENDIAN(dw) FLIP_DWORD_BYTES(dw)
#define MAKE_QWORD_BIG_ENDIAN(qw) FLIP_QWORD_BYTES(qw)
#define MAKE_GUID_BIG_ENDIAN(guid)                       do {REVERSE_BYTES_DWORD((guid).Data1);REVERSE_BYTES_WORD((guid).Data2);REVERSE_BYTES_WORD((guid).Data3);} while( FALSE )

#define BYTES_TO_WORD(  word,  byte )               BYTES2WORD_LE( word, byte )
#define WORD_TO_BYTES(  byte,  word )               WORD2BYTES_LE( byte, word )
#define BYTES_TO_QWORD( qword, byte )               BYTES2QWORD_LE( qword, byte )
#define QWORD_TO_BYTES( byte,  qword )              QWORD2BYTES_LE( byte, qword )

#define WORD_TO_NETWORKBYTES(byte_ptr, index, word)                                 \
    do {                                                                            \
        DRM_WORD _word = (word);                                                    \
        ((DRM_BYTE*)(byte_ptr))[(index)]   = (DRM_BYTE)((( _word) >> 8 ) & 0xff);   \
        ((DRM_BYTE*)(byte_ptr))[(index)+1] = (DRM_BYTE)((( _word)      ) & 0xff);   \
    } while( FALSE )

#define DWORD_TO_NETWORKBYTES(byte_ptr, index, dword)                               \
    do {                                                                            \
        DRM_DWORD _dword = (dword);                                                 \
        ((DRM_BYTE*)(byte_ptr))[(index)]   = (DRM_BYTE)(((_dword) >> 24) & 0xff);   \
        ((DRM_BYTE*)(byte_ptr))[(index)+1] = (DRM_BYTE)(((_dword) >> 16) & 0xff);   \
        ((DRM_BYTE*)(byte_ptr))[(index)+2] = (DRM_BYTE)(((_dword) >> 8 ) & 0xff);   \
        ((DRM_BYTE*)(byte_ptr))[(index)+3] = (DRM_BYTE)(((_dword)      ) & 0xff);   \
    } while (FALSE)

#if !DRM_SUPPORT_NATIVE_64BIT_TYPES
/* Copies QWORD written to buffer in little endian format into QWORD variable */
#define LITTLEENDIAN_BYTES_TO_QWORD( qword, byte, index ) do { ASSIGN_1BYTE( &(qword), 0, (byte), ((index)+0) );  ASSIGN_1BYTE( &(qword), 1, (byte), ((index)+1) ); \
                                                               ASSIGN_1BYTE( &(qword), 2, (byte), ((index)+2) );  ASSIGN_1BYTE( &(qword), 3, (byte), ((index)+3) ); \
                                                               ASSIGN_1BYTE( &(qword), 4, (byte), ((index)+4) );  ASSIGN_1BYTE( &(qword), 5, (byte), ((index)+5) ); \
                                                               ASSIGN_1BYTE( &(qword), 6, (byte), ((index)+6) );  ASSIGN_1BYTE( &(qword), 7, (byte), ((index)+7) ); } while( FALSE )
#endif /* !DRM_SUPPORT_NATIVE_64BIT_TYPES */

/* Copies WORD variable into buffer with WORD in little endian format*/
#define WORD_TO_LITTLEENDIAN_BYTES(byte, index, word)     do {DRM_WORD wTemp = (word);    COPY_WORD((byte),  (index),  wTemp); } while( FALSE )

/* Copies DWORD variable into buffer with DWORD in little endian format*/
#define DWORD_TO_LITTLEENDIAN_BYTES(byte, index, dword)   do {DRM_DWORD dwTemp = (dword); COPY_DWORD((byte), (index), dwTemp); } while( FALSE )

#define QWORD_TO_NETWORKBYTES(byte, index, qword)   do {DRM_UINT64 qwTemp = (qword); REVERSE_BYTES_QWORD(qwTemp); COPY_QWORD((byte), (index), qwTemp);} while( FALSE )

#if !DRM_SUPPORT_NATIVE_64BIT_TYPES
#define NETWORKBYTES_TO_QWORD(qword, byte, index)   do { LITTLEENDIAN_BYTES_TO_QWORD( (qword), (byte), (index) ); REVERSE_BYTES_QWORD((qword)); } while( FALSE )
#endif /* !DRM_SUPPORT_NATIVE_64BIT_TYPES */

#define QWORD_TO_NETWORKBYTES_SECURE(byte, index, qword)   do {DRM_UINT64 qwTemp = (qword); REVERSE_BYTES_QWORD(qwTemp); OEM_SECURE_MEMCPY((DRM_BYTE*)(byte)+(index), &qwTemp, SIZEOF(DRM_UINT64));} while( FALSE )
#define NETWORKBYTES_TO_DWORD_SECURE(dword, byte, index) do {OEM_SECURE_MEMCPY((DRM_BYTE*)&(dword),(DRM_BYTE*)(byte)+(index),SIZEOF(DRM_DWORD)); REVERSE_BYTES_DWORD((dword));} while( FALSE )

#define NETWORKBYTES_FROMBUFFER(to, from, index, size, buffersize)       do {COPY_FROMBUFFER(to,from,index,size,buffersize);DRM_BYT_ReverseBytes((DRM_BYTE*)&(to),(size));} while( FALSE )

#define FIX_ENDIAN_WORD(w)
#define FIX_ENDIAN_DWORD(dw)
#define FIX_ENDIAN_LONG(l)
#define FIX_ENDIAN_QWORD(qw)
#define FIX_ENDIAN_GUID(guid)

#else /* TARGET_LITTLE_ENDIAN */

#define MAKE_WORD_BIG_ENDIAN(w)    (w)
#define MAKE_DWORD_BIG_ENDIAN(dw)  (dw)
#define MAKE_QWORD_BIG_ENDIAN(qw)  (qw)
#define MAKE_GUID_BIG_ENDIAN(guid) (guid)

#define BYTES_TO_WORD(  word,  byte  )               BYTES2WORD_BE( word, byte )
#define WORD_TO_BYTES(  byte,  word  )               WORD2BYTES_BE( byte, word )
#define BYTES_TO_QWORD( qword, byte  )               BYTES2QWORD_BE( qword, byte )
#define QWORD_TO_BYTES( byte,  qword )               QWORD2BYTES_BE( byte, qword )

#define WORD_TO_NETWORKBYTES(byte, index, word)            do { DRM_WORD wTemp = (word);     COPY_WORD((byte),  (index), wTemp);  } while( FALSE )
#define DWORD_TO_NETWORKBYTES(byte, index, dword)          do { DRM_DWORD dwTemp = (dword);  COPY_DWORD((byte), (index), dwTemp); } while( FALSE )
#define QWORD_TO_NETWORKBYTES(byte, index, qword)          do { DRM_UINT64 qwTemp = (qword); COPY_QWORD((byte), (index), qwTemp); } while( FALSE )

#if !DRM_SUPPORT_NATIVE_64BIT_TYPES
#define NETWORKBYTES_TO_QWORD( qword, byte, index )        do { ASSIGN_1BYTE( &(qword), 0, (byte), ((index)+0) );  ASSIGN_1BYTE( &(qword), 1, (byte), ((index)+1) ); \
                                                                ASSIGN_1BYTE( &(qword), 2, (byte), ((index)+2) );  ASSIGN_1BYTE( &(qword), 3, (byte), ((index)+3) ); \
                                                                ASSIGN_1BYTE( &(qword), 4, (byte), ((index)+4) );  ASSIGN_1BYTE( &(qword), 5, (byte), ((index)+5) ); \
                                                                ASSIGN_1BYTE( &(qword), 6, (byte), ((index)+6) );  ASSIGN_1BYTE( &(qword), 7, (byte), ((index)+7) ); } while( FALSE )
#endif /* !DRM_SUPPORT_NATIVE_64BIT_TYPES */

#define QWORD_TO_NETWORKBYTES_SECURE(byte, index, qword)   do { DRM_UINT64 qwTemp = (qword); OEM_SECURE_MEMCPY((DRM_BYTE*)(byte)+(index), &qwTemp, SIZEOF(DRM_UINT64));} while( FALSE )
#define NETWORKBYTES_TO_DWORD_SECURE(dword, byte, index) OEM_SECURE_MEMCPY((DRM_BYTE*)&(dword),(DRM_BYTE*)(byte)+(index),SIZEOF(DRM_DWORD))

#define NETWORKBYTES_FROMBUFFER(to, from, index, size, buffersize)       COPY_FROMBUFFER(to,from,index,size,buffersize)

#define FIX_ENDIAN_WORD(w)   REVERSE_BYTES_WORD(w)
#define FIX_ENDIAN_DWORD(dw) REVERSE_BYTES_DWORD(dw)
#define FIX_ENDIAN_LONG(l)   REVERSE_BYTES_LONG(l)
#define FIX_ENDIAN_QWORD(qw) do {REVERSE_BYTES_QWORD(qw); NATIVE64_TO_NONNATIVE64((qw));} while( FALSE )

#define FIX_ENDIAN_GUID(guid)                       do {FIX_ENDIAN_DWORD((guid).Data1);FIX_ENDIAN_WORD((guid).Data2);FIX_ENDIAN_WORD((guid).Data3);} while( FALSE )

#if !DRM_SUPPORT_NATIVE_64BIT_TYPES
/* Copies QWORD written to buffer in little endian format into QWORD variable */
#define LITTLEENDIAN_BYTES_TO_QWORD( qword, byte,  index )   do { NETWORKBYTES_TO_QWORD( (qword), (byte), (index) ); REVERSE_BYTES_QWORD((qword)); } while( FALSE )
#endif /* !DRM_SUPPORT_NATIVE_64BIT_TYPES */

/* Copies DWORD variable into buffer with DWORD in little endian format*/
#define DWORD_TO_LITTLEENDIAN_BYTES( byte,  index, dword )   do { DRM_DWORD dwTemp = (dword); REVERSE_BYTES_DWORD(dwTemp); COPY_DWORD((byte), (index), dwTemp); } while( FALSE )

/* Copies WORD variable into buffer with WORD in little endian format*/
#define WORD_TO_LITTLEENDIAN_BYTES(  byte, index,  word  )   do { DRM_WORD wTemp   = (word);  REVERSE_BYTES_WORD(wTemp);   COPY_WORD((byte), (index), wTemp);   } while( FALSE )

#endif /* TARGET_LITTLE_ENDIAN */

#endif /* __BYTEORDER_H__ */

