/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2008
 * www.Altreonic.com
 * Module name: L1_hub_memory_pool_api.h ($Path/$Filename)
 * Synopsis: Memory Pool Hub API
 *
 * $LastChangedDate: 2014-03-26 10:16:05 +0100 (Wed, 26 Mar 2014) $
 * $Revision: 4216 $
 * $LastChangedBy: antonio.ramos $
 *******************************************************************************/


#ifndef L1_HUB_MEMORY_POOL_API_H_
#define L1_HUB_MEMORY_POOL_API_H_

#include <L1_types.h>
#include <kernel/hubs/L1_hub.h>

/**
\defgroup OCR_MemoryPool_Hub Memory Pool Hub
The Resource Hub, has the following properties, see also the section \ref OCR_Hub.

L1_MemoryPool is a data structure representing a list of memory Resources, managed by a specific instantiation of a L1_Hub.
  - State of every memory block in the pool:
    - Bool: Locked
    - L1_UINT16: size > 0 AND ((2**N-1) < size < (2**N))
    - TaskID: OwningTask
    - L1_Priority: CeilingPriority  // not implemented

  - Synchronisation Predicate upon L1_Allocate_MemoryBlock:
    - Predicate: not Locked AND size available blocks >= requested size AND  size available blocks==2**N
      - Action: Locked := TRUE, OwningTask := Packet->RequestingTaskID
    - Predicate: Locked OR size available blocks < requested size OR size available blocks /= 2**N
      - Action: insert Request Packet in waiting list, (priority inheritance is not used)

  - Synchronisation Predicate upon L1_Deallocate_MemoryBlock:
    - Predicate: Locked AND OwningTask == Packet->RequestingTaskID
    - Action: Locked := FALSE, OwningTask :=  None, apply LockResource Action on next waiting Tasks in waiting list. (whole list myst be checked until the Predicate holds)

  - Invariant(s):
    - If a task is waiting and there is a free block of large enough size, the waiting task will get a block allocated

  - Notes:
    - Locked attribute may be redundant in the implementation.
    - A task can request to lock another memory block while holding a block
    - The current release implements the memory pool as list of equally sized blocks, defined at design time.

\section OCR_MemoryPool_Hub_Example Example
The the code shown in section \ref OCR_MemoryPool_Hub_Example_TEP1 shows a Task that utilises a Memory Pool Hub to allocate one block of 1024 bytes of memory. It then prints the address of the memory block onto the console before deallocating the memory block, before releasing it again.

\subsection OCR_MemoryPool_Hub_Example_Entities Entities
  - MPool1: Memory Pool Hub:
    - BlockSize = 1024
    - NumberOfBlocks = 1
  - Shs1: A Stdio Host Server
  - Task1: The Task that performs the operations, uses the function MemoryPoolExampleTEP() as Task Entry Point.

\subsection OCR_MemoryPool_Hub_Example_TEP1 MemoryPoolExampleTEP
\code
void MemoryPoolExampleTEP(L1_TaskArguments Arguments)
{
    // Pointer of the memory block, to be allocated
    L1_BYTE * memoryBlock = NULL;

    // Allocating the memory block.
    if( RC_FAIL == L1_AllocateMemoryBlock_W(MPool1, &memoryBlock, 1024) )
    {
        Shs_putString_W(Shs1, "Error could not allocate the memory block.\n");
        exit(-1);
    }
    Shs_putString_W(Shs1, "Could successfully allocate the memory block at: ");
    Shs_putInt_W(Shs1, memoryBlock, 'd');
    Shs_putString_W(Shs1, "\n");

    // Deallocating the previously allocated memory block
    if( RC_FAIL == L1_DeallocateMemoryBlock_W(MPool1, memoryBlock) )
    {
        Shs_putString_W(Shs1, "Error in deallocation of the memory block\n");
        exit(-2);
    }
    Shs_putString_W(Shs1, "\nPress enter to terminate the program\n");
}
\endcode
*/

#ifndef API_DOC
 /**
 * Acquires a memory-block from a local memory pool. This service waits till a memory block is available.
 *
 * @param HubID the ID of the MemoryPool from which to acquire a region of memory with the size specified by the parameter Size.
 * @param Memory if the service completed successfully, this will point to a pointer where the allocated memory block is located.
 * This memory can then be used by the Task. Otherwise, this variable will point to a NULL pointer.
 * @param size the desired size of the MemoryBlock.
 * @param Timeout Indicates the timeout value/mode for the request.
 *
 * @return L1_Status
 * - RC_OK The service completed successfully, Memory points to a pointer which points to the allocated MemoryBlock.
 * - RC_FAIL The service failed, Memory will point to a NULL pointer.
 *
 * @warning The memory pool must be mapped to the same node as the task calling this function.
 *
 * @pre
 * - memoryPool must be local
 *
 * @post
 * - Calling task ready.
 *
 * \ingroup OCR_MemoryPool_Hub
 */
	extern L1_Status L1_AllocateMemoryBlock(L1_HubID HubID, L1_BYTE **Memory,
                                            L1_UINT16 Size, L1_Timeout Timeout);
#endif /* !API_DOC */

    /**
     * Acquires a memory-block from a local memory pool. This service waits till a memory block is available.
     *
     * @param memoryPool the ID of the MemoryPool from which to acquire a region of memory with the size specified by the parameter Size.
     *
     * @param memoryBlock if the service completed successfully, this will point to a pointer where the allocated memory block is located.
     * This memory can then be used by the Task. Otherwise, this variable will point to a NULL pointer.
     * @param size the desired size of the MemoryBlock.
     *
     * @return L1_Status
     * - RC_OK The service completed successfully, Memory points to a pointer which points to the allocated MemoryBlock.
     * - RC_FAIL The service failed, Memory will point to a NULL pointer.
     *
     * @warning The memory pool must be mapped to the same node as the task calling this function.
     *
     * @pre
     * - memoryPool must be local
     *
     * @post
     * - Calling task ready.
     *
     * \ingroup OCR_MemoryPool_Hub
     */
static __inline__ L1_Status L1_AllocateMemoryBlock_W(L1_HubID memoryPool, L1_BYTE** memoryBlock, L1_UINT16 size)
{
    return L1_AllocateMemoryBlock(memoryPool, memoryBlock, size, L1_INFINITE_TIMEOUT);
}



/**
 * This Kernel service is called by a Task to release a memory-block back to its memory pool.
 *
 * @param memoryPool identifies the MemoryPool.
 * @param memoryBlock pointer to the memory-block to release
 *
 * @return L1_Status:
 * - RC_OK   service successful (a memory block was released to the memory pool)
 * - RC_FAIL service failed (the memory block was not released to the memory pool)
 * @pre
 * - None
 * @post
 * - Calling task ready
 *
 * \ingroup OCR_MemoryPool_Hub
 */
extern L1_Status L1_DeallocateMemoryBlock_W(L1_HubID memoryPool, void *memoryBlock);

/**
 * Acquires a memory-block from a memory pool. Waits until either a memory-block becomes available or the timeout expired, depending on what happens earlier.
 *
 * @param memoryPool the ID of the MemoryPool from which to acquire a region of memory with the size specified by the parameter Size.
 *
 * @param memoryBlock if the service completed successfully, this will point to a pointer where the allocated memory block is located.
 * This memory can then be used by the Task. Otherwise, this variable will point to a NULL pointer.
 * @param size the desired size of the MemoryBlock. However, it is currently not used correctly by the function.
 * @param timeout of type L1_Timeout, the number of system ticks the call should wait for a MemoryBlock to become available.
 *
 * @return L1_Status
 * - RC_OK The service completed successfully, memoryBlock points to a pointer which points to the allocated MemoryBlock.
 * - RC_FAIL The service failed, memoryBlock will point to a NULL pointer.
 * - RC_TO The timeout expired without a MemoryBlock becoming available, memoryBlock will point to a NULL pointer.
 *
 * @warning The memory pool must be mapped to the same node as the task calling this function.
 *
 * @pre
 * - memoryPool must be local
 *
 * @post
 * - Calling task ready.
 *
 * \ingroup OCR_MemoryPool_Hub
 */
static __inline__ L1_Status L1_AllocateMemoryBlock_WT(L1_HubID memoryPool, L1_BYTE** memoryBlock, L1_UINT16 size, L1_Timeout timeout)
{
    return L1_AllocateMemoryBlock(memoryPool, memoryBlock, size, timeout);
}



/**
 * Acquires a memory-block from a memory pool.
 * This call returns immediately independent of whether or not a MemoryBlock was available or not.
 *
 * @param memoryPool the ID of the MemoryPool from which to acquire a region of
 * memory with the size specified by the parameter Size.
 *
 * @param memoryBlock if the service completed successfully, this will point to a
 * pointer where the allocated memory block is located.This memory can then be used by the Task.
 * Otherwise, this variable will point to a NULL pointer.
 *
 * @param size the desired size of the MemoryBlock. However, it is currently not used correctly by the function.
 *
 * @return L1_Status
 * - RC_OK The service completed successfully, memoryBlock points to a pointer which points to the allocated MemoryBlock.
 * - RC_FAIL The service failed, memoryBlock will point to a NULL pointer.
 *
 *
 * @warning The memory pool must be mapped to the same node as the task calling this function.
 *
 * @pre
 * - memoryPool must be local
 *
 * @post
 * - Calling task ready.
 *
 * \ingroup OCR_MemoryPool_Hub
 */
static __inline__ L1_Status L1_AllocateMemoryBlock_NW(L1_HubID memoryPool, L1_BYTE** memoryBlock, L1_UINT16 size)
{
    return L1_AllocateMemoryBlock(memoryPool, memoryBlock, size, 0);
}



#ifdef ASYNC_SERVICES

#endif /* ASYNC_SERVICES */

#endif /* L1_HUB_MEMORY_POOL_API_H_ */
