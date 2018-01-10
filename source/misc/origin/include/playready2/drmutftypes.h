/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/

#ifndef __DRM_UTFTYPES_H
#define __DRM_UTFTYPES_H

#include <drmtypes.h>

ENTER_PK_NAMESPACE;

/******************************************************************************
**  This information is from unicode.org specification.
**
**  Terminology:
**  1. "Code Point" - that which is displayed on the screen. Also called a
**                    linguistic character in Windows documentation.
**  2. "Code Unit" - that which is iterated through via index, each of size
**                   size 1, 2, or 4 8bit bytes. Also called a storage
**                   character in Windows documenation. cch always refers to
**                   these.
**
**  The maximum Code Point in unicode is U+10FFFF.
**  The Code Points in the range U+D800..U+DFFF are illegal and reserved for
**  encodings.
**
**
**  UTF-8 Encoding's Bit Distribution:
**  ==================================
**
**  unicode                     bytes   bits   UTF-8 representation
**  --------------------------  -----   ----   -----------------------------------
**  00000000 0xxxxxxx           1       7      0xxxxxxx
**  00000yyy yyxxxxxx           2       11     110yyyyy 10xxxxxx
**  zzzzyyyy yyxxxxxx           3       16     1110zzzz 10yyyyyy 10xxxxxx
**  000uuuuu zzzzyyyy yyxxxxxx  4       21     11110uuu 10uuzzzz 10yyyyyy 10xxxxxx
**  --------------------------  -----   ----   -----------------------------------
**
**  Well-Formed UTF-8 Byte Sequences:
**
**  Unicode ranges      1st Byte  2nd Byte  3rd Byte  4th Byte
**  ------------------  --------  --------  --------  --------
**  U+0000..U+007F      00..7F
**  U+0080..U+07FF      C2..DF    80..BF
**  U+0800..U+0FFF      E0        A0..BF    80..BF
**  U+1000..U+CFFF      E1..EC    80..BF    80..BF
**  U+D000..U+D7FF      ED        80..9F    80..BF
**  U+E000..U+FFFF      EE..EF    80..BF    80..BF
**  U+10000..U+3FFFF    F0        90..BF    80..BF    80..BF
**  U+40000..U+FFFFF    F1..F3    80..BF    80..BF    80..BF
**  U+100000..U+10FFFF  F4        80..8F    80..BF    80..BF
**
**  Notes:
**  1. The special cases for 3 bytes characters are due to the illegality of
**     the range U+D800..U+DFFF.
**  2. UTF-8 rules do not allow using a larger format to represent a unicode
**     value encode-able with fewer bytes.
**
**
**  UTF-16 Encoding Rules:
**  ======================
**  1. Code points in the range U+0000..U+FFFF are encoded using one UTF-16
**     value.
**  2. Code points in the range U+10000..U+10FFFF are encoded first by
**     subtracting 0x10000 to get a 20bit number, then by storing them in two
**     UTF-16 values, each containing 10bits:
**       1. The first "surrogate" is in the range 0xD800-0xDBFF.
**       2. The second "surrogate" is in the range 0xDC00-0xDFFF.
**
**  Notes:
**  1. There is no confusion between surrogates and U+D800..U+DFFF as the
**     latter is an illegal range.
**  2. UTF-16 *is* endian-specific, and both little endian (UTF-16LE), big
**     endian (UTF-16BE), and auto-detection (via BOM) are defined. This file
**     only supports characters in little endian format.
**     It neither supports characters in big endian
**     nor supports auto-detection.
**
**
**`    (UTF-16LE is used in this file regardless of native architecture)
**     UTF-16LE encoding scheme:
**     The Unicode encoding scheme that serializes a UTF-16
**     code unit sequence as a byte sequence in little-endian format.
**
**     In UTF-16LE, the UTF-16 code unit sequence <004D 0430 4E8C D800 DF02> is
**     serialized as <4D 00 30 04 8C 4E 00 D8 02 DF>.
**
**     In UTF-16LE, an initial byte sequence <FF FE> is interpreted as
**     U+FEFF zero width no-break space.
**
**
**     (UTF-16BE is never used in this file - description for information only)
**     UTF-16BE encoding scheme:
**     The Unicode encoding scheme that serializes a UTF-16
**     code unit sequence as a byte sequence in big-endian format.
**
**     In UTF-16BE, the UTF-16 code unit sequence <004D 0430 4E8C D800 DF02>
**     is serialized as <00 4D 04 30 4E 8C D8 00 DF 02>.
**
**     In UTF-16BE, an initial byte sequence <FE FF> is interpreted as U+FEFF zero
**     width no-break space.
**
**
**
**  UTF-32 Encoding Rules:
**  ======================
**  A 32bit code unit has all the space and more necessary to hold the max
**  code point. As such, no conversion is necessary.
**
**  Notes:
**     UTF-32 *is* endian-specific, and both little endian (UTF-32LE), big
**     endian (UTF-32BE), and auto-detection (via BOM) are defined. This file
**     only supports characters in little endian format.
**     It neither supports characters in big endian
**     nor supports auto-detection.
**
**
**`    (UTF-32LE is used in this file regardless of native architecture)
**     UTF-32LE encoding scheme:
**     The Unicode encoding scheme that serializes a UTF-32
**     code unit sequence as a byte sequence in little-endian format.
**
**     In UTF-32LE, the UTF-32 code unit sequence
**     <0000004D 00000430 00004E8C 00010302> is serialized as
**     <4D 00 00 00 30 04 00 00 8C 4E 00 00 02 03 01 00>.
**
**     In UTF-32LE, an initial byte sequence <FF FE 00 00> is interpreted as
**     U+FEFF zero width no-break space.
**
**
**`    (UTF-32BE is never used in this file - description for information only)
**     UTF-32BE encoding scheme:
**     The Unicode encoding scheme that serializes a UTF-32
**     code unit sequence as a byte sequence in big-endian format.
**
**     In UTF-32BE, the UTF-32 code unit sequence
**     <0000004D 00000430 00004E8C 00010302> is serialized as
**     <00 00 00 4D 00 00 04 30 00 00 4E 8C 00 01 03 02>.
**
**     In UTF-32BE, an initial byte sequence <00 00 FE FF> is interpreted as U+FEFF
**     zero width no-break space.
**
******************************************************************************/

/*
** This file internally deals in code points, which use native endian-ness.
** When converting the DRM_WCHAR32, an endian conversion may be necessary.
*/
typedef DRM_DWORD DRM_CODE_POINT;

/*
** Any code point greater than 0x10FFFF is ill-formed.
*/
#define UTF_MAX_CODE_POINT (DRM_WCHAR32)0x0010FFFFUL

/*
** Unicode has 17 "planes", each with 2^16 code points. The exception is the
** "Base Multilingual Plane" (#0) which lacks the values U+D800..U+DFFF.
*/
#define UTF_PLANE0_MAX     (DRM_WCHAR32)0x0000FFFFUL
#define UTF_PLANE1_MIN     (DRM_WCHAR32)0x00010000UL

/* ---------------------- UTF-8 constants and macros ---------------------- */

#define UTF8_MIN_TWO_BYTE_CP    0x80UL
#define UTF8_MIN_THREE_BYTE_CP  0x800UL
#define UTF8_MIN_FOUR_BYTE_CP   UTF_PLANE1_MIN

/*
** Test that this byte looks like 10vvvvvv
** so that its value is in 80..BF range
*/
#define IS_UTF8_TRAILING_CH(b) (((b) & 0xC0) == 0x80)

/*
** 110yyyyy 10xxxxxx -> 00000000 00000000 00000yyy yyxxxxxx
*/
#define UTF_CP_FROM_TWO_CH(b1,b2) \
    ( ( ( ( (b1) & 0x1FUL ) << 0x6 ) | ( (b2) & 0x3FUL ) ) & 0x7FF )
/*
** 1110zzzz 10yyyyyy 10xxxxxx -> 00000000 00000000 zzzzyyyy yyxxxxxx
*/
#define UTF_CP_FROM_THREE_CH(b1,b2,b3) \
    ( ( ( ( (b1) & 0xFUL ) << 0xC ) | ( ( (b2) & 0x3FUL ) << 0x6 ) | ( (b3) & 0x3FUL ) ) & 0xFFFFUL )

/*
** 11110uuu 10uuzzzz 10yyyyyy 10xxxxxx -> 00000000 000uuuuu zzzzyyyy yyxxxxxx
*/
#define UTF_CP_FROM_FOUR_CH(b1,b2,b3,b4) \
    ( ( ( ( (b1) & 0x7UL ) << 0x12 ) | ( ( (b2) & 0x3FUL ) << 0xC ) | ( ( (b3) & 0x3FUL ) << 0x6 ) | ( (b4) & 0x3FUL ) ) & 0x1FFFFFUL )

/*
** Takes a 6 bit value and converts to a trailing UTF-8 code unit.
*/
#define UTF8_MAKE_TRAILING_CH(_b_) ( (_b_) | 0x80 )

/*
** Creates a lead ch for UTF8 given
** a) The number of code units /top bits (n = 2-4), and
** b) The value bits in the lead byte (max bits is 7-n, i.e. going from 5 to 3).
*/
#define UTF8_MAKE_LEAD_CH(_n_, _b_) \
    ( ( ( 0xF0 << ( 4 - (_n_) ) ) | (_b_) ) & 0xFF )


/* ---------------------- UTF-16 constants and macros --------------------- */

/*
** High-surrogate code unit: A 16-bit code unit in the range 0xD800 to 0xDBFF,
** used in UTF-16 as the leading code unit of a surrogate pair.
**
** Low-surrogate code unit: A 16-bit code unit in the range 0xDC00 to 0xDFFF,
** used in UTF-16 as the trailing code unit of a surrogate pair.
*/
#define UTF16_HIGH_SURROGATE_MIN_CP  (DRM_CODE_POINT)0xD800UL
#define UTF16_HIGH_SURROGATE_MAX_CP  (DRM_CODE_POINT)0xDBFFUL
#define UTF16_LOW_SURROGATE_MIN_CP   (DRM_CODE_POINT)0xDC00UL
#define UTF16_LOW_SURROGATE_MAX_CP   (DRM_CODE_POINT)0xDFFFUL


#if TARGET_LITTLE_ENDIAN

#define IS_UTF16_HIGH_SURROGATE_WCH(_wch16_) \
    ( (_wch16_) >= UTF16_HIGH_SURROGATE_MIN_CP && \
      (_wch16_) <= UTF16_HIGH_SURROGATE_MAX_CP )

#define IS_UTF16_LOW_SURROGATE_WCH(_wch16_) \
    ( (_wch16_) >= UTF16_LOW_SURROGATE_MIN_CP && \
      (_wch16_) <= UTF16_LOW_SURROGATE_MAX_CP )

/* Each half has 10 bits of the 20 bit whole */
#define UTF32_FROM_SURROGATES_WCH(_wch16High_, _wch16Low_) \
    ( ( ( (_wch16High_) - UTF16_HIGH_SURROGATE_MIN_CP ) << 10UL ) + \
      ( (_wch16Low_) - UTF16_LOW_SURROGATE_MIN_CP ) + \
      UTF_PLANE1_MIN )

/* Rebase plane1 to zero (yielding a 20bit number instead of a 20bit + 16bit
** number), then take the top ten bits */
#define UTF16_HIGH_SURROGATE_FROM_CP(_cp_) \
    ( ( ( (_cp_) - UTF_PLANE1_MIN ) >> 10 ) + UTF16_HIGH_SURROGATE_MIN_CP )

/* Same as above, but take the bottom ten bits */
#define UTF16_LOW_SURROGATE_FROM_CP(_cp_) \
    ( ( ( (_cp_) - UTF_PLANE1_MIN ) & 0x3FFUL ) + UTF16_LOW_SURROGATE_MIN_CP )

#define UTF_CP_FROM_UTF32(_wch32_) (_wch32_)
#define UTF_CP_FROM_UTF16(_wch16_) (_wch16_)
#define UTF32_FROM_CP(_cp_) (_cp_)
#define UTF16_FROM_CP(_cp_) (_cp_)

#else

/*
** UTF-16BE encoding scheme:
** The Unicode encoding scheme that serializes a UTF-16
** code unit sequence as a byte sequence in big-endian format.
**
** In UTF-16BE, the UTF-16 code unit sequence <004D 0430 4E8C D800 DF02> is
** serialized as <00 4D 04 30 4E 8C D8 00 DF 02>.
**
** In UTF-16BE, an initial byte sequence <FE FF> is interpreted as
** U+FEFF zero width no-break space
**
**
** UTF-32BE encoding scheme:
** The Unicode encoding scheme that serializes a UTF-32
** code unit sequence as a byte sequence in big-endian format.
**
** In UTF-32BE, the UTF-32 code unit sequence
** <0000004D 00000430 00004E8C 00010302> is serialized as
** <00 00 00 4D 00 00 04 30 00 00 4E 8C 00 01 03 02>.
**
** In UTF-32BE, an initial byte sequence <00 00 FE FF> is interpreted as
** U+FEFF zero width no-break space
**
*/

#define IS_UTF16_HIGH_SURROGATE_WCH(_wch16_) \
    ( ( FLIP_WORD_BYTES( _wch16_ ) ) >= UTF16_HIGH_SURROGATE_MIN_CP && \
      ( FLIP_WORD_BYTES( _wch16_ ) ) <= UTF16_HIGH_SURROGATE_MAX_CP )

#define IS_UTF16_LOW_SURROGATE_WCH(_wch16_) \
    ( ( FLIP_WORD_BYTES( _wch16_ ) ) >= UTF16_LOW_SURROGATE_MIN_CP && \
      ( FLIP_WORD_BYTES( _wch16_ ) ) <= UTF16_LOW_SURROGATE_MAX_CP )

/* Each half has 10 bits of the 20 bit whole */
#define UTF32_FROM_SURROGATES_WCH(_wch16High_, _wch16Low_) \
    FLIP_DWORD_BYTES( ( ( ( ( FLIP_WORD_BYTES( _wch16High_ ) ) - UTF16_HIGH_SURROGATE_MIN_CP ) << 10UL ) + \
                      ( ( FLIP_WORD_BYTES( _wch16Low_ ) ) - UTF16_LOW_SURROGATE_MIN_CP ) + \
                      UTF_PLANE1_MIN ) \
                    )

/* Rebase plane1 to zero (yielding a 20bit number instead of a 20bit + 16bit
** number), then take the top ten bits */
#define UTF16_HIGH_SURROGATE_FROM_CP(_cp_) \
    FLIP_WORD_BYTES( ( ( (_cp_) - UTF_PLANE1_MIN ) >> 10 ) + UTF16_HIGH_SURROGATE_MIN_CP )

/* Same as above, but take the bottom ten bits */
#define UTF16_LOW_SURROGATE_FROM_CP(_cp_) \
    FLIP_WORD_BYTES( ( ( (_cp_) - UTF_PLANE1_MIN ) & 0x3FFUL ) + UTF16_LOW_SURROGATE_MIN_CP )

#define UTF_CP_FROM_UTF32(_wch32_) FLIP_DWORD_BYTES(_wch32_)
#define UTF_CP_FROM_UTF16(_wch16_) FLIP_WORD_BYTES(_wch16_)
#define UTF32_FROM_CP(_cp_) FLIP_DWORD_BYTES(_cp_)
#define UTF16_FROM_CP(_cp_) FLIP_WORD_BYTES(_cp_)

#endif

/* Create a macro that tests for _both_ high and low surrogates.
** Note: high surrogates are always numerically less than low surrogates
*/
#define IS_UTF16_SURROGATE_CP(_cp_) \
    ( ( _cp_ ) >= UTF16_HIGH_SURROGATE_MIN_CP && \
      ( _cp_ ) <= UTF16_LOW_SURROGATE_MAX_CP )

EXIT_PK_NAMESPACE;

#endif /* __DRM_UTFTYPES_H */

