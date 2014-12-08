/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2008
 * www.Altreonic.com
 * Module name: L1_hub_memory_pool.h ($Path/$Filename)
 * Synopsis: Memory Pool Hub internals
 *
 * $LastChangedDate: 2014-02-10 11:43:33 +0100 (Mon, 10 Feb 2014) $
 * $Revision: 4175 $
 * $LastChangedBy: bernhard.sputh $
 *******************************************************************************/

#ifndef L1_HUB_MEMORY_POOL_H_
#define L1_HUB_MEMORY_POOL_H_


/**
 * \internal \ingroup OCR_MemoryPool_Hub
 * This function provides a standard handler to the memory pool initialization function through an ioctl operation to open memory pool hub.
 *
 * @param Hub Pointer to the memory pool hub to be initialized.
 * @param Packet Pointer to the L1_Packet which caused the function to be called. It will contain additional information.
 * @param ioctl_type Control operation to be executed (L1_IOCTL_HUB_OPEN only for this hub).
 *
 *
 */
void MemoryPoolIoctl(L1_Hub * Hub, L1_Packet * Packet, L1_BYTE ioctl_type);

/**
 * \internal \ingroup OCR_MemoryPool_Hub
 * This function updates the memory pool hub when receiving packets.
 * A get packet allocates a memory block. To allocate a memory block, a free block is taken from the memory pool and it is inserted into the occupied memory block list.
 * A void pointer is returned in the data field of the packed used to allocate the block.
 * A put packet deallocates a memory block. The inverse process is to remove the block from the occupied list, and insert it into the free memory block list.
 * The data size of the packet is set to zero to indicate that not data is returned.
 *
 * @param Hub ID of the memory pool hub.
 * @param Packet Pointer to the L1_Packet used for the update operation.
 *
 *
 */
void MemoryPoolUpdate(L1_Hub * Hub, L1_Packet * Packet);

/**
 * \internal \ingroup OCR_MemoryPool_Hub
 * This function evaluates the synchronization condition.
 * If a deallocation is requested (put packet), the function returns true if the packet has been previously allocated.
 * For allocation requests (get packet), the function evaluates to true if the free memory block list is not empty.
 *
 * @param Hub ID of the memory pool hub.
 * @param Packet Pointer to the L1_Packet used to test for the synchronization condition.
 *
 */
L1_BOOL MemoryPoolSyncCondition(L1_Hub * Hub, L1_Packet * Packet);

#endif /* L1_HUB_MEMORY_POOL_H_ */
