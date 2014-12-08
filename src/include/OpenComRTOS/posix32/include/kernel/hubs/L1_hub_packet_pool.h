/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2008
 * www.Altreonic.com
 * Module name: L1_hub_packet_pool.h ($Path/$Filename)
 * Synopsis: Packet Pool Hub data structures.
 *
 * $LastChangedDate: 2014-02-10 11:43:33 +0100 (Mon, 10 Feb 2014) $
 * $Revision: 4175 $
 * $LastChangedBy: bernhard.sputh $
 *******************************************************************************/

#ifndef L1_HUB_PACKET_POOL_H_
#define L1_HUB_PACKET_POOL_H_

#include <L1_types.h>
#include <kernel/L1_list_api.h>
/**
 * \internal \ingroup OCR_PacketPool_Hub
 * The state of a Packet-Pool-Hub.
 */
typedef struct _struct_L1_PacketPoolState_ {
    /**
     * The total number of packets in the pool, only used for initialization.
     */
    L1_UINT16 Size;
#ifdef L1_OSI
    /**
     * The maximum number of packets that have been retrieved from the Packet-Pool.
     */
    L1_UINT16 maxUtilisation;
    /**
     * The current number of packets that have been retrieved from the Packet-Pool.
     */
    L1_UINT16 currentUtilisation;
#endif /* L1_OSI */
    /**
     * Pointer to an array of L1_Packets which has at least Size number of elements.
     */
    L1_Packet * const PacketPool;
    /**
     * List which will contain the currently free packets of the pool.
     */
    L1_List PacketList;
} L1_PacketPool_HubState;

/**
 * \internal \ingroup OCR_PacketPool_Hub
 * Checks whether or not the given data structure represents a PacketPool-Hub.
 * @param pHub Pointer to the data structure, of type L1_Hub, which should be checked whether or not it represents a PacketPool-Hub.
 * @return L1_TRUE if the data structure represents a PacketPool-Hub.
 * @return L1_FALSE otherwise.
 */
static __inline__ L1_BOOL L1_isPacketPoolHub(L1_Hub * pHub)
{
    return (L1_BOOL)((pHub)->HubType == L1_PACKETPOOL);
}

/**
 * \internal \ingroup OCR_PacketPool_Hub
 * This macro casts the HubState void pointer to a pointer to L1_PacketPool_HubState.
 *
 * @param h Pointer to a type of type L1_PACKET_POOl.
 */
#define L1_PacketPool_State(h) ((L1_PacketPool_HubState*)(h)->HubState)

/**
 * \internal \ingroup OCR_PacketPool_Hub
 * This function updates the packet pool when receiving allocate and deallocate requests.
 * To allocate a packet, a packet is taken from the hub's packet list and returned as part of the data field of the get packet that requested the allocation.
 * A deallocation returns the packet to the packet list.
 *
 * @param Hub ID of the packet pool hub.
 * @param Packet Packet used for the update operation.
 *
 */
extern void PacketPoolUpdate(L1_Hub * Hub, L1_Packet * Packet);

/**
 * \internal \ingroup OCR_PacketPool_Hub
 * When deallocating a packet, synchronization should always succeed. For the case of packet allocation, it should succeed only if the packet pool
 * has available packets to allocate.
 *
 * @param Hub ID of the packet pool hub.
 * @param Packet Packet used to test for the synchronization condition.
 *
 */
extern L1_BOOL PacketPoolSyncCondition(L1_Hub * Hub, L1_Packet * Packet);

/**
 * \internal \ingroup OCR_PacketPool_Hub
 * This function provides a standard handler to the packet pool initialization function through an ioctl operation to open packet pool hub.
 *
 * @param Hub Pointer to the packet pool hub.
 * @param Packet Pointer to the L1_Packet which caused the function to be called. It will contain additional information.
 * @param ioctl_type Control operation to be executed (L1_IOCTL_HUB_OPEN only for this hub).
 *
 *
 */
extern void PacketPoolIoctl(L1_Hub * Hub, L1_Packet * Packet, L1_BYTE ioctl_type);

/**
 * \internal \ingroup OCR_PacketPool_Hub
 *
 * This function determines whether or not the Packet Pool pHub still contains
 * L1_Packets which can be allocated from it.
 * @param pHub Pointer to an L1_Hub structure of the Packet Pool for which to check the availability of Packets.
 * @return L1_TRUE If there are L1_Packets available.
 * @return L1_FLASE Otherwise.
 */
static __inline__ L1_BOOL L1_isHubPacketPoolPacketAvailable(L1_Hub * pHub)
{
    return ! L1_List_isEmpty ( &( ((L1_PacketPool_HubState*)(pHub)->HubState)->PacketList) );
}


#endif /* L1_HUB_PACKET_POOL_H_ */
