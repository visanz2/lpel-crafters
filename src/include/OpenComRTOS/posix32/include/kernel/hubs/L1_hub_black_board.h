/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2008
 * www.Altreonic.com
 * Module name: ($Path/$Filename)
 * Synopsis: Black Board Hub definitions.
 *
 * $LastChangedDate: 2012-09-12 17:18:09 +0200 (Wed, 12 Sep 2012) $
 * $Revision: 2941 $
 * $LastChangedBy: bernhard.sputh $
 *******************************************************************************/

#ifndef __L1_hub_black_board_h__
#define __L1_hub_black_board_h__

#include <L1_types.h>
#include <kernel/hubs/L1_hub.h>
/**
 * \internal \ingroup OCR_BlackBoard_Hub
 * Represents the content of a Blackboard.
 */
typedef struct
{
        /**
         * This is a copy of the variable messageNumber in the Hub, but in network endianess.
         */
        L1_UINT32 messageNumber;
        /**
         * This is the message that got published.
         */
        L1_BYTE   message[L1_PACKET_DATA_SIZE - sizeof(L1_UINT32)];
}L1_BlackBoard_Board;

/**
 * \internal \ingroup OCR_BlackBoard_Hub
 * The state of a BlackBoard Hub.
 */
typedef struct
{
    /**
     * This is the board where the Message gets published. This gets copied verbosely to the reader.
     */
    L1_BlackBoard_Board board;
    /**
     * The size of the message on the board. Must be less or equal L1_PACKET_DATA_SIZE - sizeof(L1_UINT32).
     */
    L1_UINT32 dataSize;
    /**
     * This counts the number of messages that have been written to the board. This is in local CPU endinaness.
     */
    L1_UINT32 messageNumber;
} L1_BlackBoard_HubState;

/**
 * \internal \ingroup OCR_BlackBoard_Hub
 * This function performs a blackboard update operation. The packet and blackboard have to be updated when a message is written to it (put packet), and when data is read (get Packet).
 * When receiving a Put packet, the data of the packet is copied to the blackboard as a message, the size of the data in the blackboard is updated and the number of messages increases.
 * When receiving a Get packet, the data from the blackboard is copied to the packet. The message is kept in the blackboard until a wipe operation occurs.
 *
 * @param Hub ID which identifies the blackboard hub to be updated.
 * @param Packet Put or Get packet that updates the blackboard..
 *
 * @pre
 * - None
 *
 * @post
 * - None
 *
 */
void BlackBoardHub_Update(L1_Hub *Hub, L1_Packet *Packet);

/**
 * \internal \ingroup OCR_BlackBoard_Hub
 * This function returns L1_TRUE when synchronization must happen in a blackboard hub when receiving a packet.
 *
 * @param Hub ID of the blackboard hub.
 * @param Packet Pointer to the L1_Packet received at the blackboard Hub.
 *
 * @return L1_BOOL:
 * - L1_FALSE  Synchronization is not needed.
 * - L1_TRUE   Synchronization must take place.
 *
 * @pre
 * - empty waiting list.
 *
 * @post
 * - None
 *
 *
 */
L1_BOOL BlackBoardHub_SyncCondition(L1_Hub *Hub, L1_Packet *Packet);

/**
 * \internal \ingroup OCR_BlackBoard_Hub
 * Checks whether or not the given data structure represents a BlackBoard-Hub.
 * @param pHub Pointer to the data structure, of type L1_Hub, which should be checked whether or not it represents a BlackBoard-Hub.
 * @return L1_TRUE if the data structure represents a BlackBoard-Hub.
 * @return L1_FALSE otherwise.
 */
static __inline__ L1_BOOL L1_isBlackBoardHub(L1_Hub * pHub)
{
	return (L1_BOOL)((pHub)->HubType == L1_BLACKBOARD);
}

#endif /* __L1_hub_black_board_h__ */
