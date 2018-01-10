/**@@@+++@@@@******************************************************************
**
** Microsoft (r) PlayReady (r)
** Copyright (c) Microsoft Corporation. All rights reserved.
**
***@@@---@@@@******************************************************************
*/
#ifndef __DRMMATHSAFE_H_
#define __DRMMATHSAFE_H_ 1

#include <drmtypes.h>

ENTER_PK_NAMESPACE;

/* DRM_UInt32x32To64 macro */
#define DRM_UInt32x32To64(a, b)     DRM_UI64Mul( DRM_UI64HL( 0, (a) ), DRM_UI64HL( 0, (b) ) )

/* Min values */
#define DRM_CHAR_MIN        (-127 - 1)
#define DRM_SHORT_MIN       (-32768)
#define DRM_LONG_MIN        (-2147483647 - 1)
#define DRM_INT64_MIN       DRM_I64Asgn( 0x80000000, 0 )

/* Max value */
#define DRM_CHAR_MAX        127
#define DRM_SHORT_MAX       32767
#define DRM_LONG_MAX        2147483647
#define DRM_INT64_MAX       DRM_I64Asgn( 0x7FFFFFFF, MAX_UNSIGNED_TYPE( DRM_DWORD ) )
#define DRM_UINT64_MAX      DRM_UI64HL( MAX_UNSIGNED_TYPE( DRM_DWORD ), MAX_UNSIGNED_TYPE( DRM_DWORD ) )

/* It is common for -1 to be used as an error value */
#define DRM_CHAR_ERROR      (-1)
#define DRM_BYTE_ERROR      MAX_UNSIGNED_TYPE( DRM_BYTE )
#define DRM_SHORT_ERROR     (-1)
#define DRM_WORD_ERROR      MAX_UNSIGNED_TYPE( DRM_WORD )
#define DRM_LONG_ERROR      (-1)
#define DRM_DWORD_ERROR     MAX_UNSIGNED_TYPE( DRM_DWORD )
#define DRM_INT64_ERROR     DRM_I64Asgn( 0, -1 )
#define DRM_UINT64_ERROR    DRM_UI64HL( MAX_UNSIGNED_TYPE( DRM_DWORD ), MAX_UNSIGNED_TYPE( DRM_DWORD ) )

#ifdef DRM_64BIT_TARGET
#define DRM_DWORD_PTR_ERROR DRM_UINT64_ERROR
#else /* DRM_64BIT_TARGET */
#define DRM_DWORD_PTR_ERROR DRM_DWORD_ERROR
#endif /* DRM_64BIT_TARGET */

#define DRM_ByteIncOne( arg )       DRM_ByteAdd( (arg), 1, &(arg) )
#define DRM_WordIncOne( arg )       DRM_WordAdd( (arg), 1, &(arg) )
#define DRM_DWordIncOne( arg )      DRM_DWordAdd( (arg), 1, &(arg) )

#define DRM_ByteDecOne( arg )       DRM_ByteSub( (arg), 1, &(arg) )
#define DRM_WordDecOne( arg )       DRM_WordSub( (arg), 1, &(arg) )
#define DRM_DWordDecOne( arg )      DRM_DWordSub( (arg), 1, &(arg) )

/*=============================================================================
** Conversion functions
**
** There are three reasons for having conversion functions:
**
** 1. We are converting from a signed type to an unsigned type of the same
**    size, or vice-versa.
**
** 2. We are converting to a smaller type, and we could therefore possibly
**    overflow.
**
** 3. We are converting to a bigger type, and we are signed and the type we are
**    converting to is unsigned.
**
**=============================================================================
*/

/* BYTE -> CHAR conversion */
extern DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_ByteToChar(
    __in                      DRM_BYTE        f_bOperand,
    __deref_out               DRM_CHAR       *f_pchResult ) DRM_NO_INLINE_ATTRIBUTE;

/* SHORT -> CHAR conversion */
extern DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_ShortToChar(
    __in                      DRM_SHORT       f_sOperand,
    __deref_out               DRM_CHAR       *f_pchResult ) DRM_NO_INLINE_ATTRIBUTE;

/* SHORT -> BYTE conversion */
extern DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_ShortToByte(
    __in                      DRM_SHORT       f_sOperand,
    __deref_out_ecount(1)     DRM_BYTE       *f_pbResult ) DRM_NO_INLINE_ATTRIBUTE;

/* SHORT -> WORD conversion */
extern DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_ShortToWord(
    __in                      DRM_SHORT       f_sOperand,
    __deref_out               DRM_WORD       *f_pwResult ) DRM_NO_INLINE_ATTRIBUTE;

/* SHORT -> WCHAR conversion */
#define DRM_ShortToWChar   DRM_ShortToWord

/* SHORT -> DWORD conversion */
extern DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_ShortToDWord(
    __in                      DRM_SHORT       f_sOperand,
    __deref_out               DRM_DWORD      *f_pdwResult ) DRM_NO_INLINE_ATTRIBUTE;

/* SHORT -> UINT64 conversion */
extern DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_ShortToUInt64(
    __in                      DRM_SHORT       f_sOperand,
    __deref_out               DRM_UINT64     *f_pui64Result ) DRM_NO_INLINE_ATTRIBUTE;

/* SHORT -> DWORD_PTR conversion */
extern DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_ShortToDWordPtr(
    __in                      DRM_SHORT       f_sOperand,
    __deref_out               DRM_DWORD_PTR  *f_pdwResult ) DRM_NO_INLINE_ATTRIBUTE;

/* SHORT -> SIZE_T conversion */
#define DRM_ShortToSizeT    DRM_ShortToDWordPtr

/* WORD -> CHAR conversion */
extern DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_WordToChar(
    __in                      DRM_WORD       f_wOperand,
    __deref_out               DRM_CHAR      *f_pchResult ) DRM_NO_INLINE_ATTRIBUTE;

/* WORD -> BYTE conversion */
extern DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_WordToByte(
    __in                      DRM_WORD       f_wOperand,
    __deref_out_ecount(1)     DRM_BYTE      *f_pbResult ) DRM_NO_INLINE_ATTRIBUTE;

/* WORD -> SHORT conversion */
extern DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_WordToShort(
    __in                      DRM_WORD       f_wOperand,
    __deref_out               DRM_SHORT     *f_psResult ) DRM_NO_INLINE_ATTRIBUTE;

/* LONG -> CHAR conversion */
extern DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_LongToChar(
    __in                      DRM_LONG       f_lOperand,
    __deref_out               DRM_CHAR      *f_pchResult ) DRM_NO_INLINE_ATTRIBUTE;

/* LONG -> BYTE conversion */
extern DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_LongToByte(
    __in                      DRM_LONG       f_lOperand,
    __deref_out_ecount(1)     DRM_BYTE      *f_pbResult ) DRM_NO_INLINE_ATTRIBUTE;

/* LONG -> SHORT conversion */
extern DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_LongToShort(
    __in                      DRM_LONG       f_lOperand,
    __deref_out               DRM_SHORT     *f_psResult ) DRM_NO_INLINE_ATTRIBUTE;

/* LONG -> WORD conversion */
extern DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_LongToWord(
    __in                      DRM_LONG       f_lOperand,
    __deref_out               DRM_WORD      *f_pwResult ) DRM_NO_INLINE_ATTRIBUTE;

/* LONG -> DWORD conversion */
extern DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_LongToDWord(
    __in                      DRM_LONG       lOperand,
    __deref_out               DRM_DWORD     *f_pdwResult ) DRM_NO_INLINE_ATTRIBUTE;

/* LONG -> DWORD_PTR conversion */
extern DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_LongToDWordPtr(
    __in                      DRM_LONG       f_lOperand,
    __deref_out               DRM_DWORD_PTR *f_pdwResult ) DRM_NO_INLINE_ATTRIBUTE;

/* LONG -> SIZE_T conversion */
#define DRM_LongToSizeT DRM_LongToDWordPtr

/* DWORD -> CHAR conversion */
extern DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_DWordToChar(
    __in                      DRM_DWORD     f_dwOperand,
    __deref_out               DRM_CHAR     *f_pchResult ) DRM_NO_INLINE_ATTRIBUTE;

/* DWORD -> BYTE conversion */
extern DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_DWordToByte(
    __in                      DRM_DWORD     f_dwOperand,
    __deref_out_ecount(1)     DRM_BYTE     *f_pbResult ) DRM_NO_INLINE_ATTRIBUTE;

/* DWORD -> SHORT conversion */
extern DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_DWordToShort(
    __in                      DRM_DWORD     f_dwOperand,
    __deref_out               DRM_SHORT    *f_psResult ) DRM_NO_INLINE_ATTRIBUTE;

/* DWORD -> WORD conversion */
extern DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_DWordToWord(
    __in                      DRM_DWORD     f_dwOperand,
    __deref_out               DRM_WORD     *f_pwResult ) DRM_NO_INLINE_ATTRIBUTE;

/* DWORD -> LONG conversion */
extern DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_DWordToLong(
    __in                      DRM_DWORD     f_dwOperand,
    __deref_out               DRM_LONG     *f_plResult ) DRM_NO_INLINE_ATTRIBUTE;

/* DWORD_PTR -> CHAR conversion */
#ifdef DRM_64BIT_TARGET
#define DRM_DWordPtrToChar  DRM_UInt64ToChar
#else /* DRM_64BIT_TARGET */
#define DRM_DWordPtrToChar  DRM_DWordToChar
#endif /* DRM_64BIT_TARGET */

/* DWORD_PTR -> BYTE conversion */
#ifdef DRM_64BIT_TARGET
#define DRM_DWordPtrToByte  DRM_UInt64ToByte
#else /* DRM_64BIT_TARGET */
#define DRM_DWordPtrToByte  DRM_DWordToByte
#endif /* DRM_64BIT_TARGET */

/* DWORD_PTR -> SHORT conversion */
#ifdef DRM_64BIT_TARGET
#define DRM_DWordPtrToShort DRM_UInt64ToShort
#else /* DRM_64BIT_TARGET */
#define DRM_DWordPtrToShort DRM_DWordToShort
#endif /* DRM_64BIT_TARGET */

/* DWORD_PTR -> WORD conversion */
#ifdef DRM_64BIT_TARGET
#define DRM_DWordPtrToWord  DRM_UInt64ToWord
#else /* DRM_64BIT_TARGET */
#define DRM_DWordPtrToWord  DRM_DWordToWord
#endif /* DRM_64BIT_TARGET */

/* DWORD_PTR -> LONG conversion */
#ifdef DRM_64BIT_TARGET
#define DRM_DWordPtrToLong  DRM_UInt64ToLong
#else /* DRM_64BIT_TARGET */
#define DRM_DWORDPtrToLong  DRM_DWordToLong
#endif /* DRM_64BIT_TARGET */

/* DWORD_PTR -> DWORD conversion */
#ifdef DRM_64BIT_TARGET
#define DRM_DWordPtrToDWord  DRM_UInt64ToDWord
#else /* DRM_64BIT_TARGET */
extern DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_DWordPtrToDWord(
    __in                      DRM_DWORD_PTR  f_dwOperand,
    __deref_out               DRM_DWORD     *f_pdwResult ) DRM_NO_INLINE_ATTRIBUTE;
#endif /* DRM_64BIT_TARGET */

/* SIZE_T -> CHAR conversion */
#define DRM_SizeTToChar     DRM_DWordPtrToChar

/* SIZE_T -> BYTE conversion */
#define DRM_SizeTToByte     DRM_DWordPtrToByte

/* SIZE_T -> SHORT conversion */
#define DRM_SizeTToShort    DRM_DWordPtrToShort

/* SIZE_T -> WORD */
#define DRM_SizeTToWord     DRM_DWordPtrToWord

/* SIZE_T -> LONG conversion */
#define DRM_SizeTToLong     DRM_DWordPtrToLong

/* SIZE_T -> DWORD conversion */
#define DRM_SizeTToDWord    DRM_DWordPtrToDWord

/* INT64 -> CHAR conversion */
extern DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_Int64ToChar(
    __in                      DRM_INT64     f_i64Operand,
    __deref_out               DRM_CHAR     *f_pchResult ) DRM_NO_INLINE_ATTRIBUTE;

/* INT64 -> WORD conversion */
extern DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_Int64ToWord(
    __in                      DRM_INT64     f_i64Operand,
    __deref_out               DRM_WORD     *f_pwResult ) DRM_NO_INLINE_ATTRIBUTE;

/* INT64 -> BYTE conversion */
extern DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_Int64ToByte(
    __in                      DRM_INT64     f_i64Operand,
    __deref_out_ecount(1)     DRM_BYTE     *f_pbResult ) DRM_NO_INLINE_ATTRIBUTE;

/* INT64 -> SHORT conversion */
extern DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_Int64ToShort(
    __in                      DRM_INT64     f_i64Operand,
    __deref_out               DRM_SHORT    *f_psResult ) DRM_NO_INLINE_ATTRIBUTE;

/* INT64 -> LONG conversion */
extern DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_Int64ToLong(
    __in                      DRM_INT64     f_i64Operand,
    __deref_out               DRM_LONG     *f_plResult ) DRM_NO_INLINE_ATTRIBUTE;

/* INT64 -> DWORD conversion */
extern DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_Int64ToDWord(
    __in                      DRM_INT64     f_i64Operand,
    __deref_out               DRM_DWORD    *f_pdwResult ) DRM_NO_INLINE_ATTRIBUTE;

/* INT64 -> DWORDPTR conversion */
#ifdef DRM_64BIT_TARGET
#define DRM_Int64ToDWordPtr DRM_Int64ToUInt64
#else /* DRM_64BIT_TARGET */
#define DRM_Int64ToDWordPtr DRM_Int64ToDWord
#endif /* DRM_64BIT_TARGET */

/* INT64 -> UINT64 conversion */
extern DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_Int64ToUInt64(
    __in                      DRM_INT64     f_i64Operand,
    __deref_out               DRM_UINT64   *f_pui64Result ) DRM_NO_INLINE_ATTRIBUTE;

/* INT64 -> SIZE_T conversion */
#define DRM_Int64ToSizeT       DRM_Int64ToDWordPtr

/* UINT64 -> CHAR conversion */
extern DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_UInt64ToChar(
    __in                      DRM_UINT64     f_ui64Operand,
    __deref_out               DRM_CHAR      *f_pchResult ) DRM_NO_INLINE_ATTRIBUTE;

/* UINT64 -> WORD conversion */
extern DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_UInt64ToWord(
    __in                      DRM_UINT64     f_ui64Operand,
    __deref_out               DRM_WORD      *f_pwResult ) DRM_NO_INLINE_ATTRIBUTE;

/* UINT64 -> BYTE conversion */
extern DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_UInt64ToByte(
    __in                      DRM_UINT64     f_ui64Operand,
    __deref_out_ecount(1)     DRM_BYTE      *f_pbResult ) DRM_NO_INLINE_ATTRIBUTE;

/* UINT64 -> SHORT conversion */
extern DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_UInt64ToShort(
    __in                      DRM_UINT64     f_ui64Operand,
    __deref_out               DRM_SHORT     *f_psResult ) DRM_NO_INLINE_ATTRIBUTE;

/*  UINT64 -> LONG conversion */
extern DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_UInt64ToLong(
    __in                      DRM_UINT64     f_ui64Operand,
    __deref_out               DRM_LONG      *f_plResult ) DRM_NO_INLINE_ATTRIBUTE;

/* UINT64 -> DWORD conversion */
extern DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_UInt64ToDWord(
    __in                      DRM_UINT64     ui64Operand,
    __deref_out               DRM_DWORD     *f_pdwResult ) DRM_NO_INLINE_ATTRIBUTE;

/* UINT64 -> DWORD_PTR conversion */
#ifdef DRM_64BIT_TARGET
extern DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_UInt64ToDWordPtr(
    __in                      DRM_UINT64     f_ui64Operand,
    __deref_out               DRM_DWORD_PTR *f_pdwResult ) DRM_NO_INLINE_ATTRIBUTE;
#else /* DRM_64BIT_TARGET */
#define DRM_UInt64ToDWordPtr  DRM_UInt64ToDWord
#endif /* DRM_64BIT_TARGET */

/* UINT64 -> INT64 conversion */
extern DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_UInt64ToInt64(
    __in                      DRM_UINT64     f_ui64Operand,
    __deref_out               DRM_INT64     *f_pi64Result ) DRM_NO_INLINE_ATTRIBUTE;

/* UINT64 -> SIZE_T conversion */
#define DRM_UInt64ToSizeT    DRM_UInt64ToDWordPtr

/*
** Addition functions
**
*/

/* BYTE addition */
extern DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_ByteAdd(
    __in                      DRM_BYTE       f_bAugend,
    __in                      DRM_BYTE       f_bAddend,
    __deref_out_ecount(1)     DRM_BYTE      *f_pbResult ) DRM_NO_INLINE_ATTRIBUTE;

/* WORD addition */
extern DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_WordAdd(
    __in                      DRM_WORD       f_wAugend,
    __in                      DRM_WORD       f_wAddend,
    __deref_out               DRM_WORD      *f_pwResult ) DRM_NO_INLINE_ATTRIBUTE;

/* DWORD addition */
extern DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_DWordAdd(
    __in                      DRM_DWORD       f_dwAugend,
    __in                      DRM_DWORD       f_dwAddend,
    __deref_out               DRM_DWORD      *f_pdwResult ) DRM_NO_INLINE_ATTRIBUTE;

/* DWORD_PTR addition */
#ifdef DRM_64BIT_TARGET
#define DRM_DWordPtrAdd   DRM_UInt64Add
#else /* DRM_64BIT_TARGET */
#define DRM_DWordPtrAdd   DRM_DWordAdd
#endif /* DRM_64BIT_TARGET */

#define DRM_SizeTAdd    DRM_DWordPtrAdd

/* UINT64 addition */
extern DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_UInt64Add(
    __in                      DRM_UINT64       f_ui64Augend,
    __in                      DRM_UINT64       f_ui64Addend,
    __deref_out               DRM_UINT64      *f_pui64Result ) DRM_NO_INLINE_ATTRIBUTE;

/*
** Subtraction functions
*/

/* BYTE subtraction */
extern DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_ByteSub(
    __in                      DRM_BYTE       f_bMinuend,
    __in                      DRM_BYTE       f_bSubtrahend,
    __deref_out               DRM_BYTE      *f_pbResult ) DRM_NO_INLINE_ATTRIBUTE;

/* WORD subtraction */
extern DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_WordSub(
    __in                      DRM_WORD       f_wMinuend,
    __in                      DRM_WORD       f_wSubtrahend,
    __deref_out               DRM_WORD      *f_pwResult ) DRM_NO_INLINE_ATTRIBUTE;

/* DWORD subtraction */
extern DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_DWordSub(
    __in                      DRM_DWORD       f_dwMinuend,
    __in                      DRM_DWORD       f_dwSubtrahend,
    __deref_out               DRM_DWORD      *f_pdwResult ) DRM_NO_INLINE_ATTRIBUTE;

/* DWORD_PTR subtraction */
#ifdef DRM_64BIT_TARGET
#define DRM_DWordPtrSub    DRM_UInt64Sub
#else /* DRM_64BIT_TARGET */
#define DRM_DWordPtrSub    DRM_DWordSub
#endif /* DRM_64BIT_TARGET */

/* SIZE_T subtraction */
#define DRM_SizeTSub       DRM_DWordPtrSub

/* UINT64 subtraction */
extern DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_UInt64Sub(
    __in                      DRM_UINT64       f_ui64Minuend,
    __in                      DRM_UINT64       f_ui64Subtrahend,
    __deref_out               DRM_UINT64      *f_pui64Result ) DRM_NO_INLINE_ATTRIBUTE;

/*
** Multiplication functions
*/

/* WORD multiplication */
extern DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_WordMult(
    __in                      DRM_WORD       f_wMultiplicand,
    __in                      DRM_WORD       f_wMultiplier,
    __deref_out               DRM_WORD      *f_pwResult ) DRM_NO_INLINE_ATTRIBUTE;

/* DWORD multiplication */
extern DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_DWordMult(
    __in                      DRM_DWORD       f_dwMultiplicand,
    __in                      DRM_DWORD       f_dwMultiplier,
    __deref_out               DRM_DWORD      *f_pdwResult ) DRM_NO_INLINE_ATTRIBUTE;

/* DWORD_PTR multiplication */
#ifdef DRM_64BIT_TARGET
#define DRM_DWordPtrMult    DRM_UInt64Mult
#else /* DRM_64BIT_TARGET */
#define DRM_DWordPtrMult    DRM_DWordMult
#endif /* DRM_64BIT_TARGET */

/* SIZET multiplicaiton */
#define DRM_SizeTMult       DRM_DWordPtrMult


/* UINT64 multiplication */
extern DRM_API DRM_NO_INLINE DRM_RESULT DRM_UInt64Mult(
    __in                      DRM_UINT64       f_ui64Multiplicand,
    __in                      DRM_UINT64       f_ui64Multiplier,
    __deref_out               DRM_UINT64      *f_pui64Result ) DRM_NO_INLINE_ATTRIBUTE;

/*
**
** signed operations
**
** Strongly consider using unsigned numbers.
**
** Signed numbers are often used where unsigned numbers should be used.
** For example file sizes and array indices should always be unsigned.
** (File sizes should be 64bit integers; array indices should be SIZE_T.)
** Subtracting a larger positive signed number from a smaller positive
** signed number with IntSubwill succeed, producing a negative number,
** that then must not be used as an array index (but can occasionally be
** used as a pointer index.) Similarly for adding a larger magnitude
** negative number to a smaller magnitude positive number.
**
** drmmathsafe.h does not protect you from such errors. It tells you if your
** integer operations overflowed, not if you are doing the right thing
** with your non-overflowed integers.
**
** Likewise you can overflow a buffer with a non-overflowed unsigned index.
*/

/*
** Signed addition functions
*/

/* SHORT Addition */
extern DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_ShortAdd(
    __in                      DRM_SHORT       f_sAugend,
    __in                      DRM_SHORT       f_sAddend,
    __deref_out               DRM_SHORT      *f_psResult ) DRM_NO_INLINE_ATTRIBUTE;

/* LONG Addition */
extern DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_LongAdd(
    __in                      DRM_LONG       f_lAugend,
    __in                      DRM_LONG       f_lAddend,
    __deref_out               DRM_LONG      *f_plResult ) DRM_NO_INLINE_ATTRIBUTE;

/* INT64 Addition */
extern DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_Int64Add(
    __in                      DRM_INT64       f_i64Augend,
    __in                      DRM_INT64       f_i64Addend,
    __deref_out               DRM_INT64      *f_pi64Result ) DRM_NO_INLINE_ATTRIBUTE;

/*
** Signed subtraction functions
*/

/* SHORT Subtraction */
extern DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_ShortSub(
    __in                      DRM_SHORT       f_sMinuend,
    __in                      DRM_SHORT       f_sSubtrahend,
    __deref_out               DRM_SHORT      *f_psResult ) DRM_NO_INLINE_ATTRIBUTE;

/* LONG Subtraction */
extern DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_LongSub(
    __in                      DRM_LONG       f_lMinuend,
    __in                      DRM_LONG       f_lSubtrahend,
    __deref_out               DRM_LONG      *f_plResult ) DRM_NO_INLINE_ATTRIBUTE;

/* INT64 Subtraction */
extern DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_Int64Sub(
    __in                      DRM_INT64       f_i64Minuend,
    __in                      DRM_INT64       f_i64Subtrahend,
    __deref_out               DRM_INT64      *f_pi64Result ) DRM_NO_INLINE_ATTRIBUTE;

/*
** Signed multiplication functions
*/

/* SHORT multiplication */
extern DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_ShortMult(
    __in                      DRM_SHORT       f_sMultiplicand,
    __in                      DRM_SHORT       f_sMultiplier,
    __deref_out               DRM_SHORT      *f_psResult ) DRM_NO_INLINE_ATTRIBUTE;

/* LONG multiplication */
extern DRM_API DRM_NO_INLINE DRM_RESULT DRM_CALL DRM_LongMult(
    __in                      DRM_LONG       f_lMultiplicand,
    __in                      DRM_LONG       f_lMultiplier,
    __deref_out               DRM_LONG      *f_plResult ) DRM_NO_INLINE_ATTRIBUTE;

/* INT64 multiplication */
extern DRM_API DRM_NO_INLINE DRM_RESULT DRM_Int64Mult(
    __in                      DRM_INT64       f_i64Multiplicand,
    __in                      DRM_INT64       f_i64Multiplier,
    __deref_out               DRM_INT64      *f_pi64Result ) DRM_NO_INLINE_ATTRIBUTE;

EXIT_PK_NAMESPACE;

#endif /* __DRMMATHSAFE_H_ */
