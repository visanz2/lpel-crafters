/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2011
 * www.Altreonic.com
 * Module name: L1_memorypool.h
 * Synopsis: Datatype definitions for the memory-pool.
 *
 * $LastChangedDate$
 * $Revision$
 * $LastChangedBy$
 *******************************************************************************/

#ifndef L1_MEMORYPOOL_H_
#define L1_MEMORYPOOL_H_


#include <L1_types.h>
#include <kernel/L1_memory_api.h>

/**
 * The state information of the Memory-Pool Hub.
 *
\code
// These are the blocks of memory that get allocated for the user.
L1_BYTE MemoryPool_MP1_Memory[1][1024];

// Data structures that combine the memory block with the management infromation.
L1_MemoryBlock MemoryPool_MP1_MemoryBlocks[1] =
{
    {
        .Header =
        {
            .ListElement = {NULL,NULL,1},
            // This parameter comes from the system.xml
            .DataSize    = 1024,
        },
        .Data = &MemoryPool_MP1_Memory[0]
    },
};

// The HubState information for the Memroy.
L1_MemoryPool_HubState MemoryPool_MP1_HubState =
{
    // This parameter comes from the system.xml
    .NumberOfBlocks = 1,
    // This parameter comes from the system.xml
    .BlockSize = 1024,
    .MemoryBlockPool = MemoryPool_MP1_MemoryBlocks,
    .FreeMemoryBlockList = { .SentinelElement = {NULL, NULL, 1} },
    .OccupiedMemoryBlockList = { .SentinelElement = {NULL, NULL, 1} }
};
\endcode
 *
 */
typedef struct {
    /**
     * Number of Memory-Blocks in the pool, only used for initialisation.
     * Set by the codegens
     */
    const L1_UINT16 NumberOfBlocks;
    /**
     * Size of the individual blocks in byte.
     * Set by the codegens
     */
    const L1_UINT32 BlockSize;
    /**
     * Pointer to an array of elements of type L1_MemoryBlock.
     */
    const L1_MemoryBlock * MemoryBlockPool;
    /**
     * List that contains the currently available Free MemoryBlocks.
     */
    L1_List FreeMemoryBlockList; /* list of free Memory Blocks */
    /**
     * List that contains the currently occupied MemoryBlocks
     */
    L1_List OccupiedMemoryBlockList; /* list of free Memory Blocks */
} L1_MemoryPool_HubState;



/**
 * This expression checks whether the pointer h, points to a Memory-Pool hub.
 */
#define L1_isMemoryPoolHub(h) ((h)->HubType == L1_MEMORYPOOL)



/**
 * This macro casts the HubState void pointer to a pointer to L1_MemoryPool_HubState.
 *
 * @param h Pointer to a type of type L1_MemoryPool_HubState.
 */
#define L1_MemoryPool_State(h) ((L1_MemoryPool_HubState*)(h)->HubState)


#endif /* L1_MEMORYPOOL_H_ */
