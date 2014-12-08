/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2008
 * www.Altreonic.com
 * Module name: ($Path/$Filename)
 * Synopsis: L1_Packet handling API
 *
 * $LastChangedDate: 2014-01-25 18:52:53 +0100 (Sat, 25 Jan 2014) $
 * $Revision: 4163 $
 * $LastChangedBy: bernhard.sputh $
 *******************************************************************************/

#ifndef __L1_packet_api_h__
#define __L1_packet_api_h__

#include <kernel/L1_list_api.h>
#include <L1_types.h>

#include<kernel/L1_timerlist_api.h>


//#define L1_PACKET_DATA_SIZE     32
#define L1_PACKET_DATA_SIZE     1024

typedef struct _struct_L1_Packet_ L1_Packet;

/**
 * \internal \ingroup OCR_PEND_REQ_QUEUE
 * This defines a callback function which is used to handle a request-packet
 * that has been registered for later processing due to missing packets
 * in the KernelPacketPool.
 *
 * @param  packet Pointer to the Packet that was enqueued for later processing.
 * @returns L1_Status
 * - RC_OK: Should be returned when the handling of the request was successful.
 * - RC_FAIL: Must be returned when the handling of the request was not successful.
 */
typedef L1_Status (*L1_PendingRequestHandler)(L1_Packet * request);

struct _struct_L1_Packet_
{
  L1_ListElement ListElement;
  L1_UINT16      ServiceID;
  L1_TaskID      RequestingTaskID;
  L1_PortID      DestinationPortID;
//#ifdef WT_SERVICES
  L1_TimerTimeout TimeoutTimer;
//#endif /* WT_SERVICES*/
//#if defined (NOWAIT_SERVICES) || defined (WT_SERVICES) || defined (ASYNC_SERVICES)
  L1_Timeout	 Timeout;
//#endif /* NOWAIT_SERVICES || WT_SERVICES || ASYNC_SERVICES */
  L1_Status      Status;
  L1_UINT32      SequenceNumber;
  L1_UINT32      DataSize;
  L1_List*       OwnerPool;
#ifdef PENDING_REQUESTS_QUEUE
  /**
   * This is the ListElement is used to add an L1_Packet to the Pending Requests Queue (PRQ).
   */
  L1_ListElement  PendingRequestListElement;
  /**
   * This function represents the function that will be called to handle the pending request.
   */
  L1_PendingRequestHandler  PendingRequestHandler;
#endif
  /**
   * This flag indicates whether or not this L1_Packet is currently being used. This is used by Interrupt Service Routines to check whether or not their Packet has been already returned to them.
   * @warning This is only meant to be used in ISRs where the Packet gets returned implicitly! Do not modify this flag!
   */
  L1_BOOL       inUse;
 #ifdef COOLFLUX
  L1_BYTE        Data[L1_PACKET_DATA_SIZE];
#else
  L1_BYTE        Data[L1_PACKET_DATA_SIZE] __attribute__((aligned(L1_DATA_ALIGNMENT)));
#endif /* COOLFLUX */
};// L1_Packet;


/* #define L1_isLocalService(p) ((((p)->DestinationPortID) & L1_GLOBALID_MASK) == ((L1_KernelTaskID) & L1_GLOBALID_MASK)) */
#define L1_isLocalService(p) (L1_isLocalPortID((p)->DestinationPortID))


//void L1_List_insertPacket(L1_List *List, L1_Packet *Packet);
//void L1_List_removePacket(L1_Packet* Packet);


/**
 * This function inserts a packet into a list.
 * @param l list to where the packet will be inserted.
 * @param p packet to be inserted to the list.
 *
 * @return L1_Status
 *  - RC_OK operation was successful.
 *  - RC_FAIL operation was not successful.
 */
#define L1_List_insertPacket(l, p) L1_List_insert( (l), &((p)->ListElement) )

/**
 * This function removes a packet from a list.
 * @param p packet to be removed from the list.
 *
 * @return L1_Status
 *  - RC_OK operation was successful.
 *  - RC_FAIL operation was not successful.
 */
#define L1_List_removePacket(p) L1_List_remove( &((p)->ListElement) )

/**
 * This function writes a given 8bit value at the given offset in the data-part of the given L1_Packet.
 * @param packet Pointer to the packet where to write the given value, in network byte order, into the data part.
 * @param offset the offset at which value should be written.
 * @param value the 8bit which should be written into the packet.
 * @return L1_Status
 *  - RC_OK operation was successful.
 *  - RC_FAIL operation was not successful.
 */
L1_Status L1_Packet_setUINT8(L1_Packet* packet, L1_UINT32 offset,
		L1_BYTE value);

/**
 * This function converts the given L1_UINT16 value from host byte order to network byte order and writes the resulting value at the given offset in the data-part of the given L1_Packet.
 * @param packet Pointer to the packet where to write the given value, in network byte order, into the data part.
 * @param offset the offset at which value should be written.
 * @param value the L1_UINT16 which should be written into the packet.
 * @return L1_Status
 *  - RC_OK operation was successful.
 *  - RC_FAIL operation was not successful.
 */
L1_Status L1_Packet_setUINT16(L1_Packet* packet, L1_UINT32 offset,
		L1_UINT16 value);

/**
 * This function converts the given L1_UINT32 value from host byte order to network byte order and writes the resulting value at the given offset in the data-part of the given L1_Packet.
 * @param packet Pointer to the packet where to write the given value, in network byte order, into the data part.
 * @param offset the offset at which value should be written.
 * @param value the L1_UINT32 which should be written into the packet.
 * @return L1_Status
 *  - RC_OK operation was successful.
 *  - RC_FAIL operation was not successful.
 */
L1_Status L1_Packet_setUINT32(L1_Packet* packet, L1_UINT32 offset,
		L1_UINT32 value);

/**
 * Retrieves the L1_UINT16 value stored at offset in the given L1_Packet. This function takes care of any necessary byte order conversion.
 * @param packet Pointer to the L1_Packet from which to extract the reply code.
 * @param offset The offset from which to retrieve the value.
 * @param pValue Pointer to a variable of type L1_UINT16 which will contain the retrieved value when the function returns.
 * @return L1_Status
 *  - RC_OK operation was successful.
 *  - RC_FAIL operation was not successful.
 */
L1_Status L1_Packet_getUINT8(L1_Packet* packet, L1_UINT32 offset,
		L1_BYTE* pValue);

/**
 * Retrieves the L1_UINT16 value stored at offset in the given L1_Packet. This function takes care of any necessary byte order conversion.
 * @param packet Pointer to the L1_Packet from which to extract the reply code.
 * @param offset The offset from which to retrieve the value.
 * @param pValue Pointer to a variable of type L1_UINT16 which will contain the retrieved value when the function returns.
 * @return L1_Status
 *  - RC_OK operation was successful.
 *  - RC_FAIL operation was not successful.
 */
L1_Status L1_Packet_getUINT16(L1_Packet* packet, L1_UINT32 offset,
		L1_UINT16* pValue);

/**
 * Retrieves the L1_UINT32 value stored at offset in the given L1_Packet. This function takes care of any necessary byte order conversion.
 * @param packet Pointer to the L1_Packet from which to extract the reply code.
 * @param offset The offset from which to retrieve the value.
 * @param pValue Pointer to a variable of type L1_UINT32 which will contain the retrieved value when the function returns.
 * @return L1_Status
 *  - RC_OK operation was successful.
 *  - RC_FAIL operation was not successful.
 */
L1_Status L1_Packet_getUINT32(L1_Packet* packet, L1_UINT32 offset,
		L1_UINT32* pValue);


#if 0
L1_Status DumpPacket(L1_Packet * pPacket);
#endif



/**
 * This function returns an L1_Packet that was acquired from a Pool to the Pool it was acquired from.
 * @param packet Pointer to the L1_Packet to return.
 *
 * @warning This function enters an leaves a CriticalSection. Do not use this function inside ISRs, instead use the function: L1_returnPacketToItsPool_IsrSafe().
 * @sa L1_returnPacketToItsPool_IsrSafe
 */
void L1_returnPacketToItsPool(L1_Packet * packet);

/**
 * This function returns an L1_Packet that was acquired from a Pool to the Pool it was acquired from.
 * @param packet Pointer to the L1_Packet to return.
 *
 * @warning Only use this function while being inside an ISR, with Interrupts disabled, or while being inside a critical section. Otherwise use the function L1_returnPacketToItsPoolIO.
 * @sa L1_returnPacketToItsPool
 */
void L1_returnPacketToItsPool_IsrSafe(L1_Packet * packet);




#endif /* __L1_packet_api_h__ */
