/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2008
 * www.Altreonic.com
 * Module name: ($Path/$Filename)
 * Synopsis: Providing the interface to the kernels own L1_memcpy implementation.
 *
 * $LastChangedDate: 2014-03-26 14:09:51 +0100 (Wed, 26 Mar 2014) $
 * $Revision: 4220 $
 * $LastChangedBy: bernhard.sputh $
 *******************************************************************************/
#ifndef L1_MEMCPY_H_
#define L1_MEMCPY_H_

#include <L1_types.h>
#include <string.h>
/**
 * This function is a replacement for the stdio function memcpy. It copies the number
 * of bytes (num) from the source (source) to the destination (dest).
 *
 * @param dest pointer to the destination where data will be copied.
 * @param source pointer to the source of the data to be copied.
 * @param num the number of bytes to be copied.
 *
 * @return
 *  -  The number of bytes copied
 *  - -1 If either dest or source where a NULL-Pointer.
 */

static __inline__ L1_INT32 L1_memcpy(L1_BYTE * dest, const L1_BYTE * source, L1_UINT32 num)
{
    if((NULL == dest) || (NULL == source))
    {
        return -1;
    }

    memcpy(dest, source, num);

    return num;
}

/**
 * This function is a replacement for the stdio function memset.
 * It sets a given value to the memory region starting at the
 * pointer (dest) and ending at (dest + num).
 *
 * @param dest the start address of the memory region to be set.
 * @param value the value to store in each byte.
 * @param num the number of bytes to be set.
 *
 * @return
 *  - RC_OK to signal that the operation could be performed.
 *  - RC_FAIL in case of an error.
 */

static __inline__ L1_Status L1_memset(L1_BYTE *dest, L1_BYTE value, L1_UINT32 num)
{
    if(NULL == dest)
    {
        return RC_FAIL;
    }

    memset(dest, value, num);

    return RC_OK;
}


#endif /*L1_MEMCPY_H_*/
