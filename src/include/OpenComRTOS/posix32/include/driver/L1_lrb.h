/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2008
 * www.Altreonic.com
 * Module name: L1_lrb.h ($Path/$Filename)
 * Synopsis:
 *
 * $LastChangedDate: 2010-11-05 10:52:18 +0100 (Fri, 05 Nov 2010) $
 * $Revision: 2037 $
 * $LastChangedBy: bernhard.sputh $
 *******************************************************************************/

#ifndef L1_LRB_H_
#define L1_LRB_H_

#include <L1_types.h>

typedef struct _L1_LRB
{
	/**The Buffer's size*/
	L1_UINT32 size;

	/**The Read Location*/
	L1_UINT32 nextReadPos;

	/**The Write Location*/
	L1_UINT32 nextWritePos;

	/**The Ring Buffer Array*/
	L1_UINT8 *buffer;
}L1_lrb;

/**Initializes the L1_lrb Data Structure.
 *
 * @param self - pointer to a L1_lrb Data Structure
 *
 * @return RC_OK - if the Lockless Ring Buffer initialization was successful
 * @return RC_FAIL - if the Lockless Ring Buffer initialization failed
 * */
L1_Status L1_lrb_init(L1_lrb *self, L1_UINT8 * buffer, L1_UINT32 size);

/**Polls the Read and Write pointers to find out whether the Buffer is empty or not.
 *
 * @param self - pointer to a L1_lrb Data Structure
 *
 * @return RC_OK - if the Lockless Ring Buffer is empty
 * @return RC_FAIL - if the Lockless Ring Buffer is not empty
 * */
L1_Status L1_lrb_isEmpty(L1_lrb *self, L1_BOOL * pEmpty);

/**Polls the Read and Write pointers to find out whether the Buffer is full or not.
 *
 * @param self - pointer to a L1_lrb Data Structure
 *
 * @return RC_OK - if the Lockless Ring Buffer is full
 * @return RC_FAIL - if the Lockless Ring Buffer is not full
 * */
L1_Status L1_lrb_isFull(L1_lrb *self, L1_BOOL * pFull);

/**Inserts a data byte into the Lockless Ring Buffer.
 *
 * @param self - pointer to a L1_lrb Data Structure
 * @param data - the data byte to be written into the Lockless Ring Buffer
 * @param pWritten - boolean value stating if the byte has been successfully written or not
 *
 * @return RC_OK - if the function has successfully executed
 * @return RC_FAIL - if at least one of the values passed by reference is NULL
 * */
L1_Status L1_lrb_writeByte(L1_lrb *self, L1_UINT8 data, L1_BOOL * pWritten);

/**Removes a data byte from the Lockless Ring Buffer.
 *
 * @param self - pointer to a L1_lrb Data Structure
 * @param data - pointer to a location where the removed data byte to be copied
 * @param pRead - boolean value stating if the byte has been successfully read or not
 *
 * @return RC_OK - if the function has successfully executed
 * @return RC_FAIL - if at least one of the values passed by reference is NULL
 * */
L1_Status L1_lrb_readByte(L1_lrb *self,L1_UINT8 *data, L1_BOOL * pRead);

/**Gets the number of available bytes within the Lockless Ring Buffer.
 *
 * @param self - pointer to a L1_lrb Data Structure
 * @param bytesAvailable - pointer to a location where the number of available bytes to be copied
 *
 * @return RC_OK - if the number of available bytes was successfully read
 * @return RC_FAIL - if the pointer to the L1_lrb Data Structure is NULL
 * */
L1_Status L1_lrb_numberOfFreeBytesInBuffer(L1_lrb *self, L1_UINT32 *bytesAvailable);

/**Gets the number of written bytes within the Lockless Ring Buffer.
 *
 * @param self - pointer to a L1_lrb Data Structure
 * @param bytesAvailable - pointer to a location where the number of available bytes to be copied
 *
 * @return RC_OK - if the number of written bytes was successfully read
 * @return RC_FAIL - if the pointer to the L1_lrb Data Structure is NULL
 * */
L1_Status L1_lrb_numberOfBytesInBuffer(L1_lrb *self, L1_UINT32 *bytesUsed);

/**
 * Writes a given buffer into the Lockless Ring Buffer.
 * @param self - pointer to a L1_lrb Data Structure
 * @param buffer - the byte buffer to be written
 * @param bufferSize - the buffer's size
 * @param writtenBytes - the number of bytes that have been written
 * @return RC_OK - if at least one byte has been successfully written
 * @return RC_FAIL - if writing into the Lockless Ring Buffer failed
 */
L1_Status L1_lrb_writeBuffer(L1_lrb *self, const L1_UINT8 * buffer, L1_UINT32 bufferSize, L1_UINT32 * writtenBytes);

/**
 * Reads a given number of bytes into a given buffer from the Lockless Ring Buffer.
 * @param self - pointer to a L1_lrb Data Structure
 * @param buffer - the byte buffer where the read bytes will be stored
 * @param bufferSize - the buffer's size
 * @param readBytes - the number of bytes that have been read
 * @return RC_OK - if at least one byte has been successfully read
 * @return RC_FAIL - if reading the Lockless Ring Buffer failed
 */
L1_Status L1_lrb_readBuffer(L1_lrb *self, L1_UINT8 *buffer, L1_UINT32 bufferSize, L1_UINT32 *readBytes);

#endif /* L1_LRB_H_ */
