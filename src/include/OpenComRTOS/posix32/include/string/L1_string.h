/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2008
 * www.Altreonic.com
 * Module name: ($Path/$Filename)
 * Synopsis: Implementation of basic string manipulation routines.
 *
 * $LastChangedDate: 2014-03-26 13:29:00 +0100 (Wed, 26 Mar 2014) $
 * $Revision: 4218 $
 * $LastChangedBy: bernhard.sputh $
 *******************************************************************************/


#ifndef L1_STRING_H_
#define L1_STRING_H_

#include <L1_types.h>

/**
 * Converts the integer n to a C-string
 * @warning It is the responsibility of the programmer to ensure that the
 * string s is long enough to hold the number.
 * @param n the integer to be converted to a string.
 * @param *s char array which will hold the resulting string.
 *
 * @return L1_Status
 *  - RC_OK: The operation completed successfully.
 *  - RC_FAIL: The operation failed.
 */
L1_Status L1_itoa(L1_INT32 n, L1_INT8 * s);

/**
 * This function is a replacement for the stdio function strlen.
 * It determines the length of a C-String, excluding the terminating 0;
 *
 * @param str C style string;
 *
 * @return
 *  - The number of characters in the string, excluding the terminating NULL;
 *  - -1 If str was a NULL-Pointer.
 */
L1_INT32 L1_strlen(const L1_INT8 * str);

/**
 * This function copies the string contained in source to the string indicated
 * in dest, however a maximum of n bytes is copied.
 *
 * @param dest Pointer to the destination character array.
 * @param source Pointer to the string to be copied.
 * @param n Number of bytes to the copied from source to dest.
 *
 * @return Pointer to dest, if copy operation took place otherwise NULL;
 *
 */
L1_INT8 * L1_strncpy(L1_INT8 * dest, const L1_INT8 *source, const L1_UINT32 n);


#endif /* L1_STRING_H_ */
