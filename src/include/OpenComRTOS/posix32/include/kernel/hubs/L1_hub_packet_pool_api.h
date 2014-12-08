/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2008
 * www.Altreonic.com
 * Module name: L1_hub_packet_pool_api.h ($Path/$Filename)
 * Synopsis: Packet-Pool Hub API
 *
 * $LastChangedDate: 2014-03-26 10:16:05 +0100 (Wed, 26 Mar 2014) $
 * $Revision: 4216 $
 * $LastChangedBy: antonio.ramos $
 *******************************************************************************/

#ifndef L1_HUB_PACKET_POOL_API_H_
#define L1_HUB_PACKET_POOL_API_H_

#include <L1_types.h>
#include <kernel/hubs/L1_hub.h>


#ifdef ASYNC_SERVICES
    /**
     * \defgroup OCR_PacketPool_Hub Packet Pool Hub
     * OpenComRTOS offers the following operations on packet pool hubs.
     *
     */

/*
 * API and documentation for the PacketPool-Hub
 */

#ifndef API_DOC
/**
 * This function allocates a packet from a packet pool and initializes the task ID and priority fields.
 *
 * @param HubID The ID of the pool where the packet will be allocated.
 * @param Packet The allocated packet will be pointed by this variable when the function succeeds.
 * @param Timeout Indicates the timeout value/mode for the request.
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
    extern L1_Status L1_AllocatePacket (L1_HubID HubID, L1_Packet **Packet, L1_Timeout Timeout);
#endif /* !API_DOC */

/**
 * This service allocates a Packet from a Packet-Pool on the local Node.
 * It waits until a Packet has been allocated.
 *
 * @param packetPool the ID of the PacketPool on the local Node.
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
static __inline__ L1_Status L1_AllocatePacket_W(L1_HubID packetPool, L1_Packet** packet)
{
    return L1_AllocatePacket(packetPool, packet, L1_INFINITE_TIMEOUT);
}



/**
 * This service deallocates a Packet and returns it to the Packet Pool.
 * @param packetPool the ID of the Packet Pool to which to return packet.
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
L1_Status L1_DeallocatePacket_W (L1_HubID packetPool, L1_Packet * packet);

/**
 * This service allocates a Packet from a Packet-Pool on the local Node.
 * This service waits until either a Packet has been allocated or the specified timeout has expired.
 * If the timeout has expired the return value indicates a failed allocation
 * (there was no available Packet in the Packet pool).
 *
 *
 * @param packetPool of type L1_HubID, the ID of the PacketPool on the local Node.
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
static __inline__ L1_Status L1_AllocatePacket_WT(L1_HubID packetPool, L1_Packet ** packet, L1_Timeout timeout)
{
    return L1_AllocatePacket(packetPool, packet, timeout);
}



/**
 * This service allocates a Packet from a Packet-Pool on the local Node.
 * The service returns immediately either with the allocated Packet or with a return value indicating
 * failure (if there was no available Packet in the Packet pool).
 *
 * @param packetPool the ID of the PacketPool on the local Node.
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
static __inline__ L1_Status L1_AllocatePacket_NW(L1_HubID packetPool, L1_Packet ** packet)
{
    return L1_AllocatePacket(packetPool, packet, 0);
}



#endif

#endif /* L1_HUB_PACKET_POOL_API_H_ */
