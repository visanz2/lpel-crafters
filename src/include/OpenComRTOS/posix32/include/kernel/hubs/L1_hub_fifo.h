/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2008
 * www.Altreonic.com
 * Module name: L1_hub_fifo.h ($Path/$Filename)
 * Synopsis: FIFO Hub data structures.
 *
 * $LastChangedDate: 2014-01-10 09:33:15 +0100 (Fri, 10 Jan 2014) $
 * $Revision: 4148 $
 * $LastChangedBy: marina.gutierrez $
 *******************************************************************************/

#ifndef L1_HUB_FIFO_H_
#define L1_HUB_FIFO_H_

#include <L1_types.h>
/**
 * \internal \ingroup OCR_FIFO_Hub
 * This structure represents an Element in the FIFO-Hub. It buffers the data given to it.
 */
typedef struct _struct_L1_FifoData_ {
        /**
         * Number of bytes that are used in the field Data
         */
        L1_UINT16 DataSize;
        /**
         * The data stored in this
         */
        L1_BYTE Data[L1_PACKET_DATA_SIZE];
} L1_FifoData;

/**
 * \internal \ingroup OCR_FIFO_Hub
 *
 * State of a FIFO-Hub.
 */
typedef struct _struct_L1_FifoState_ {
    /**
     * Number of L1_FifoData elements the array Buffer contains.
     */
    const L1_UINT16 Size;
    /**
     * Current number of used elements of the array Buffer.
     */
    L1_UINT16 Count;
    /**
     * Index of the Head element in the array Buffer.
     */
    L1_UINT16 Head;
    /**
     * Index of the Tail element in the array Buffer.
     */
    L1_UINT16 Tail;
    /**
     * Array fo L1_FifoData elements which are used to store the data passed to the FIFO-Hub.
     */
    L1_FifoData * const Buffer;
} L1_Fifo_HubState;


/**
 * \internal \ingroup OCR_FIFO_Hub
 * Checks whether or not the given data structure represents a FIFO-Hub.
 * @param pHub Pointer to the data structure, of type L1_Hub, which should be checked whether or not it represents a FIFO-Hub.
 * @return L1_TRUE If the data structure represents a FIFO-Hub.
 * @return L1_FALSE Otherwise.
 */
static __inline__ L1_BOOL L1_isFifoHub(L1_Hub * pHub)
{
    return (L1_BOOL)((pHub)->HubType == L1_FIFO);
}

/**
 * \internal \ingroup OCR_FIFO_Hub
 * Determines whether the FIFO-Hub identified by pHub is full.
 *
 * @param pHub Pointer to the Hub data structure of a FIFO-Hub.
 * @return L1_TRUE If the FIFO is full.
 * @return L1_FALSE If the FIFO is not full.
 */
static __inline__ L1_BOOL L1_isHubFifoFull(L1_Hub * pHub)
{
    return (L1_BOOL) (((L1_Fifo_HubState*)(pHub)->HubState)->Count == ((L1_Fifo_HubState*)(pHub)->HubState)->Size);
}

/**
 * \internal \ingroup OCR_FIFO_Hub
 * Determines whether the FIFO-Hub identified by pHub is empty.
 *
 * @param pHub Pointer to the Hub data structure of a FIFO-Hub.
 * @return L1_TRUE If the FIFO is empty.
 * @return L1_FALSE If the FIFO is not empty.
 */
static __inline__ L1_BOOL L1_isHubFifoEmpty(L1_Hub * pHub)
{
    return (L1_BOOL) (((L1_Fifo_HubState*)(pHub)->HubState)->Count == 0);
}

/**
 * \internal \ingroup OCR_FIFO_Hub
 * This function updates the state of a Fifo Hub, depending on the type of packet received.
 * Put packets increase the count of the Fifo, data from the packet is copied into the fifo buffer and the data size is updated.
 * Get packets decrease the count of the Fifo and copies the data from the hub's buffer to the data field of the packet.
 *
 * @param Hub ID of the Fifo Hub.
 * @param Packet Packet used for the update operation.
 *
 *
 */
extern void FifoUpdate(L1_Hub * Hub, L1_Packet * Packet);

/**
 * \internal \ingroup OCR_FIFO_Hub
 * This function signals if synchronization occurs when receiving put/get packets in a fifo.
 * When receiving a put packet, returns true when the fifo is not full (more packets can be received).
 * When receiving a get packet, returns true when the fifo is not empty (there is data to be read from the fifo).
 *
 * @param Hub ID of the Fifo Hub.
 * @param Packet Packet used for the synchronization operation.
 *
 * @return L1_TRUE If synchronisation took place.
 * @return L1_FALSE If no synchronisation took place.
 */
extern L1_BOOL FifoSyncCondition(L1_Hub * Hub, L1_Packet * Packet);

#endif /* L1_HUB_FIFO_H_ */
