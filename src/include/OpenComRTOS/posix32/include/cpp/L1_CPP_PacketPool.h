/*
 * L1_CPP_PacketPool.h
 *
 *  Created on: Oct 25, 2013
 *      Author: Marina
 */

#ifndef __L1_CPP_PACKETPOOL_H__
#define __L1_CPP_PACKETPOOL_H__

extern "C"
{
#include <L1_api.h>
}

class L1_CPP_PacketPool
{
public:
	L1_CPP_PacketPool(L1_HubID packetPool);

	/**
	 * This service allocates a Packet from a Packet-Pool on the local Node.
	 * It waits until a Packet has been allocated.
	 *
	 * @param packet of type L1_Packet**,  will contain the Packet upon successful return
	 *
	 * @return
	 * - RC_OK    service completed successfully (there was an available Packet in the Packet Pool).
	 * - RC_FAIL service failed (no available Packet in the Packet Pool), Packet will the point to NULL.
	 *
	 * @pre
	 * - There is a Kernel Packet Pool on the Node
	 * - This service cannot be called from the ISR LAYER
	 * @post
	 * - ServiceID of the pre-allocated Packet of the calling Task will be set to SID_Allocate_Packet.
	 * - Task is on READY list upon return
	 * - Packet can be used for two-phase services.
	 *
	 * \ingroup OCR_PacketPool_Hub
	 */
	L1_Status allocatePacket_W(L1_Packet** packet);

	/**
	 * This service deallocates a Packet and returns it to the Packet Pool.
	 * @param packet the Packet that needs to be de-allocated.
	 * @return
	 * - RC_OK service completed successfully.
	 * - RC_FAIL service failed.
	 * @pre
	 * - This service cannot be called by the ISR LAYER.
	 * - Packet must have been allocated by L1_AllocatePacket.
	 * - Packet must be a Packet on a local PacketPool.
	 * @post
	 * - Packet is no longer available for use by the Task.
	 * - Packet is available for use by other Tasks.
	 *
	 * @note The L1_DeallocatePacket kernel service is served by the Kernel Task of the Node at which the requesting Task resides. Hence, the destination Port is implicitly set to the KernelPort.
	 *
	 * \ingroup OCR_PacketPool_Hub
	 */
	L1_Status deallocatePacket_W (L1_Packet * packet);

	/**
	 * This service allocates a Packet from a Packet-Pool on the local Node.
	 * This service waits until either a Packet has been allocated or the specified timeout has expired.
	 * If the timeout has expired the return value indicates a failed allocation
	 * (there was no available Packet in the Packet pool).
	 *
	 * @param packet will contain the Packet upon successful return.
	 * @param timeout the number of system ticks the call should wait for a packet to become available.
	 *
	 * @return
	 * - RC_OK service completed successfully (there was an available Packet in the Packet Pool).
	 * - RC_FAIL service failed (no available Packet in the Packet Pool), Packet* is set to NULL.
	 * - RC_TO the timeout has expired, Packet will point to NULL.
	 *
	 * @pre
	 * - There is a Packet Pool on the Node.
	 * - This service cannot be called from the ISR LAYER.
	 * @post
	 * - ServiceID of the pre-allocated Packet of the calling Task will be set to SID_Allocate_Packet.
	 * - Task is on the ReadyList upon return.
	 * - Packet can be used for two-phase services.
	 *
	 * \ingroup OCR_PacketPool_Hub
	 */
	L1_Status allocatePacket_WT(L1_Packet ** packet, L1_Timeout timeout);

	/**
	 * This service allocates a Packet from a Packet-Pool on the local Node.
	 * The service returns immediately either with the allocated Packet or with a return value indicating
	 * failure (if there was no available Packet in the Packet pool).
	 *
	 * @param packet will contain a pointer to Packet upon successful return.
	 *
	 * @return
	 * - RC_OK the service completed successfully (there was an available Packet in the Packet Pool).
	 * - RC_FAIL service failed (no available Packet in the Packet Pool), Packet will the point to NULL.
	 *
	 * @pre
	 * - There is a local Packet Pool on the Node
	 * - This service cannot be called from the ISR LAYER
	 * @post
	 * - ServiceID of the pre-allocated Packet of the calling Task will be set to SID_Allocate_Packet.
	 * - Task is on READY list upon return
	 * - Packet can be used for two-phase services.
	 *
	 * \ingroup OCR_PacketPool_Hub
	 */
	L1_Status allocatePacket_NW(L1_Packet ** packet);

private:
	L1_HubID HubID;
};


#endif /* !__L1_CPP_TASK_H__ */
