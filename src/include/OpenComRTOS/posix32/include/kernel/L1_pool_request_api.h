/*
 * L1_pool_request_api.h
 *
 *  Created on: 12 Mar 2011
 *      Author: Bernhard.Sputh
 */

#ifndef L1_POOL_REQUEST_API_H_
#define L1_POOL_REQUEST_API_H_

#include <L1_types.h>
#include <kernel/L1_memory_api.h>

/**
 * This function tries to allocate a resource (L1_Packet, L1_MemoryBlock) from
 * a Pool-Hub.
 *
 * @warning Only use this function for local hubs.
 *
 * @param HubID  The ID of the Pool-Hub (PacketPool, MemoryPool) that the request
 * should be sent to.
 * @param PoolType  Identifies which type of pool is meant, can have the values:
 *  - L1_PACKETPOOL
 *  - L1_MEMORYPOOL
 *  @param *Memory  Is a pointer to a pointer variable where the allocated pool
 *  resource should be stored in.
 *  @param Timeout  The desired timeout for this request.
 *
 *  @returns L1_Status
 *  - RC_OK: The operation was successful, *Memory is a pointer to a valid resource.
 *  - RC_FAIL, RC_TO: The operation was not successful, *Memory is NULL.
 */
L1_Status L1_buildAllocateRequest(L1_HubID HubID, L1_ServiceType PoolType, VOIDPTR *Memory,
                                      L1_Timeout Timeout);


/**
 * This function returns a previously allocated resource to a pool
 *
 * @warning Only use this function for local hubs.
 *
 * @param HubID  The ID of the Pool-Hub (PacketPool, MemoryPool) that the request
 * should be sent to.
 * @param PoolType  Identifies which type of pool is meant, can have the values:
 *  - L1_PACKETPOOL
 *  - L1_MEMORYPOOL
 *  @param Memory The pointer to the resource to be returned to the pool.
 */
L1_Status L1_buildDeallocateRequest_W(L1_HubID HubID, L1_ServiceType PoolType, VOIDPTR Memory);

#endif /* L1_POOL_REQUEST_API_H_ */
