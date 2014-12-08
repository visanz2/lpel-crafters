/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2008
 * www.Altreonic.com
 * Module name: ($Path/$Filename)
 * Synopsis: FIFO Hub API.
 *
 * $LastChangedDate: 2012-09-12 17:18:09 +0200 (Wed, 12 Sep 2012) $
 * $Revision: 2941 $
 * $LastChangedBy: bernhard.sputh $
 *******************************************************************************/

#ifndef __L1_hub_fifo_api_h__
#define __L1_hub_fifo_api_h__

#include <L1_types.h>
#include <kernel/hubs/L1_hub.h>
#include <kernel/hubs/L1_hub_data_api.h>

/**
\defgroup OCR_FIFO_Hub FIFO Hub
The Resource Hub, has the following properties, see also the section \ref OCR_Hub.
L1_FIFO is a data structure representing a L1_FIFO buffer, which is a specific instantiation of a L1_Hub.

  - State:
    - const L1_UINT16: Size // number of fixed size data blocks in FIFO
    - L1_UINT16: Count
    - L1_List: Buffer

  - Synchronisation Predicate upon L1_EnqueueFIFO:
    - Predicate: Count < Size
    - Action: Count := Count + 1, retrieve Data from Packet, and insert Data at end of List/Buffer

  - Synchronisation Predicate upon L1_DequeueFIFO:
    - Predicate: ount <> 0
    - Action: Count := Count – 1, retrieve Data from (first element) of List/Buffer and exchange with Packet, rerun L1_EnqueueFIFO I any waiting Task in the Put Waiting List

  - Invariant(s):
    - both waiting lists are empty, or only one waiting list contains waiting requests, i.e.
      - length (put waiting list) <> 0 implies length (get waiting list) = 0
      - length (get waiting list) <> 0 implies length (put waiting list) = 0
    - content of waiting lists are dependent on the current state, i.e.
      - Count <> 0 implies length (get waiting list) = 0
      - length (Put waiting list) <> 0 implies Count == Size
      - Count <> Size implies length (put waiting list) = 0

\section OCR_FIFO_Hub_Example Example
This example illustrates the use of the FIFO Hub. Task1 puts a character into a packet and sends this to FIFO1. Task2 initially waits for 2 seconds for the FIFO to fill up and then retrieves the packets from FIFO1 and displays their content.
\subsection OCR_FIFO_Hub_Example_Entities Entities
  - FIFO1: The FIFO bugger between Task1 and Task2, it can store 5 elements.
  - Task1: Task1EntryPoint, shown in section \ref OCR_FIFO_Hub_Example_Task1
  - Task1: Task2EntryPoint, shown in section \ref OCR_FIFO_Hub_Example_Task2
  - StdioHostServer1: A Stdio Host Server component which provides acess to the console.
  - StdioHostServer1Res: A Resource Hub to ensure that a second task does not interfere with console access.

\section OCR_FIFO_Hub_Example_Task1 Source Code of Task1EntryPoint
\code
void Task1EntryPoint(L1_TaskArguments Arguments)
{
    L1_BYTE ch;
    L1_Packet *Packet = L1_CurrentTaskCR->RequestPacket;

    for(L1_UINT32 i=0; i<5; i++)
    {
        for(ch = 'a'; ch < 'j'; ch++)
        {
            Packet->DataSize = sizeof(L1_BYTE);
            Packet->Data[0] = ch;

            if(RC_OK == L1_EnqueueFifo_W(FIFO1))
            {
                L1_LockResource_W(StdioHostServer1Res);
                Shs_putString_W(StdioHostServer1,
                                "The Task1 put into the FIFO1 the symbol ");
                Shs_putChar_W(StdioHostServer1, ch);
                Shs_putChar_W(StdioHostServer1, '\n');
                L1_UnlockResource_W(StdioHostServer1Res);
            }else
            {
                Shs_putString_W(StdioHostServer1,
                                "A symbol is not put by Task1 into FIFO1\n");
            }
        }
    }
}
\endcode

\section OCR_FIFO_Hub_Example_Task2 Source Code of Task2EntryPoint
\code
#include <L1_api.h>
#include "L1_node_config.h"
#include <StdioHostService/StdioHostClient.h>

void Task2EntryPoint(L1_TaskArguments Arguments)
{
    L1_Packet *Packet = L1_CurrentTaskCR->RequestPacket;
    L1_BYTE i, ch;

    while(1)
    {
        L1_LockResource_W(StdioHostServer1Res);
        Shs_putString_W(StdioHostServer1, "Task2 sleeps for 2 s waiting for the FIFO to fill up\n\n");
        L1_UnlockResource_W(StdioHostServer1Res);
        L1_WaitTask_WT(2000);

        for(i = 'a'; i < 'j'; i++)
        {
            if(RC_OK == L1_DequeueFifo_W(FIFO1))
            {
                ch = Packet->Data[0];
                L1_LockResource_W(StdioHostServer1Res);
                Shs_putString_W(StdioHostServer1,
                                "The Task2 read from the FIFO1 the symbol ");
                Shs_putChar_W(StdioHostServer1, ch);
                Shs_putChar_W(StdioHostServer1, '\n');
                L1_UnlockResource_W(StdioHostServer1Res);
            }else
            {
                L1_LockResource_W(StdioHostServer1Res);
                Shs_putString_W(StdioHostServer1,
                                "A symbol is not read by Task2 from FIFO1\n");
                L1_UnlockResource_W(StdioHostServer1Res);
            }
        }
    }
}
\endcode


*/

/**
 * Inserts the payload-data of a task's Request-Packet into a FIFO. This service waits until it could insert the data into the specified FIFO.
 *
 * @param HubID identifies the FIFO-Hub to use.
 *
 * @return L1_Status
 * - RC_OK  service successful (the data was inserted in the FIFO)
 * - RC_FAIL    service failed (the data was not inserted in the FIFO)
 *
 * @pre
 *  - None
 *
 * @post
 * - Calling task ready
 *
 * \ingroup OCR_FIFO_Hub
 *
 */
static __inline__ L1_Status L1_EnqueueFifo_W(L1_HubID HubID)
{
    return L1_buildAndInsertPacket((HubID), (L1_CurrentTaskCR->RequestPacket), (L1_UINT16)(L1_SID_SEND_TO_HUB | (L1_FIFO << 8)), L1_INFINITE_TIMEOUT);
}



/**
 * Retrieves data from a FIFO, the data is stored in the payload of the task's Request-Packet.
 * This call waits until there is data in the FIFO to be retrieved.
 *
 * @warning The payload part of the task specific request-packet gets overwritten as soon as
 * another request gets sent. Therefore, always copy the payload-data to a local buffer
 * using L1_memcpy(...).
 *
 * @param HubID the L1_HubID which identifies the FIFO-Hub.
 *
 * @return L1_Status
 * - RC_OK  service successful (the data was inserted in the FIFO)
 * - RC_FAIL    service failed (the data was not inserted in the FIFO)
 *
 * @pre
 * - None
 *
 * @post
 * - Calling task ready
 *
 * \ingroup OCR_FIFO_Hub
 */
static __inline__ L1_Status L1_DequeueFifo_W(L1_HubID HubID)
{
    return L1_buildAndInsertPacket((HubID), (L1_CurrentTaskCR->RequestPacket), (L1_UINT16)(L1_SID_RECEIVE_FROM_HUB | (L1_FIFO << 8)), L1_INFINITE_TIMEOUT);
}



/**
 * Inserts the payload-data of a task's Request-Packet into a FIFO.
 * This service tries to enqueue a packet into the FIFO until the the timeout expires.
 *
 * @param HubID identifies the FIFO-Hub to use.
 * @param timeout the number of system ticks the call should wait while trying to enqueue the packet.
 *
 * @return L1_Status
 * - RC_OK service successful (the data was inserted in the FIFO)
 * - RC_FAIL service failed (the data was not inserted in the FIFO)
 * - RC_TO the timeout expired.
 * @pre
 *  - None
 *
 * @post
 * - Calling task ready
 *
 *
 * \ingroup OCR_FIFO_Hub
 */
static __inline__ L1_Status L1_EnqueueFifo_WT(L1_HubID HubID, L1_Timeout timeout)
{
    return L1_buildAndInsertPacket((HubID), (L1_CurrentTaskCR->RequestPacket), (L1_UINT16)(L1_SID_SEND_TO_HUB | (L1_FIFO << 8)), (timeout));
}



/**
 * Retrieves data from a FIFO, the data is stored in the payload of the task's Request-Packet.
 * Waits until either data becomes available or the timeout expired, depending on what happens first.
 *
 * @warning The payload part of the task specific request-packet gets overwritten as soon as
 * another request gets sent. Therefore, always copy the payload-data to a local buffer
 * using L1_memcpy(...).
 *
 * @param HubID the L1_HubID which identifies the FIFO-Hub to use.
 * @param timeout the number of system ticks the call should wait for a packet to become available.
 *
 * @return L1_Status
 * - RC_OK  service successful (the data was inserted in the FIFO)
 * - RC_FAIL    service failed (the data was not inserted in the FIFO)
 * - RC_TO the timeout expired without a package being available.
 * @pre
 * - None
 *
 * @post
 * - Calling task ready
 *
 * \ingroup OCR_FIFO_Hub
 */
static __inline__ L1_Status L1_DequeueFifo_WT(L1_HubID HubID, L1_Timeout timeout)
{
    return L1_buildAndInsertPacket((HubID), (L1_CurrentTaskCR->RequestPacket), (L1_UINT16)(L1_SID_RECEIVE_FROM_HUB | (L1_FIFO << 8)), (timeout));
}



/**
 *
 * Inserts the payload-data of a task's Request-Packet into a FIFO.
 * This call returns immediately, even if the packet could not be enqueued in the FIFO.
 *
 * @param HubID the L1_HubID which identifies the FIFO-Hub.
 *
 * @return L1_Status
 * - RC_OK  service successful (the data was inserted in the FIFO)
 * - RC_FAIL    service failed (the data was not inserted in the FIFO)
 *
 * @pre
 *  - None
 *
 * @post
 * - Calling task ready
 *
 *
 * \ingroup OCR_FIFO_Hub
 */
static __inline__ L1_Status L1_EnqueueFifo_NW(L1_HubID HubID)
{
    return L1_buildAndInsertPacket((HubID), (L1_CurrentTaskCR->RequestPacket), (L1_UINT16)(L1_SID_SEND_TO_HUB | (L1_FIFO << 8)), 0);
}



/**
 * Retrieves data from a FIFO, the data is stored in the payload of the task's Request-Packet.
 *
 * This call returns immediately, even if there is no packet available in the FIFO.
 *
 * @warning The payload part of the task specific request-packet gets overwritten as soon as
 * another request gets sent. Therefore, always copy the payload-data to a local buffer
 * using L1_memcpy(...).
 *
 * @param HubID the L1_HubID which identifies the FIFO-Hub.
 *
 * @return L1_Status
 * - RC_OK  service successful (the data was inserted in the FIFO)
 * - RC_FAIL    service failed (the data was not inserted in the FIFO)
 *
 * @pre
 * - None
 *
 * @post
 * - Calling task ready
 *
 * \ingroup OCR_FIFO_Hub
 */
static __inline__ L1_Status L1_DequeueFifo_NW(L1_HubID HubID)
{
    return L1_buildAndInsertPacket((HubID), (L1_CurrentTaskCR->RequestPacket), (L1_UINT16)(L1_SID_RECEIVE_FROM_HUB | (L1_FIFO << 8)), 0);
}



#ifdef ASYNC_SERVICES

#endif /* ASYNC_SERVICES */


/**
 * This function performs a data transfer to a FIFO-Hub.
 * It copies the data stored in the buffer indicated by data into the data
 * part of an L1_Packet and then sends this packet to the Hub.
 *
 * @param hubID ID of the Hub to send data to.
 * @param data pointer to a buffer of type L1_BYTE which contains the data that should be sent to the Hub.
 * @param size size of the buffer pointed to by data. This must not be larger than L1_PACKET_SIZE, otherwise the interaction will return RC_FAIL.
 *
 * @return L1_Status:
 * - RC_OK: The interaction was successful;
 * - RC_FAIL: The interaction failed. There are multiple reasons for the interaction to fail;
 * -- The buffer data does not fit in the data part of the L1_Packet (L1_PACKET_DATA_SIZE).
 * -- dataBuffer is NULL
 * -- packet is NULL
 * -- General failure of the system causing the interaction with the Hub to fail.
 *
 * @warning Only use this functions to interact with Port- or Fifo-Hubs. Interacting with other types of Hubs may have undesired effects.
 *
 * \ingroup OCR_FIFO_Hub
 */
static __inline__ L1_Status L1_PutDataToFifo_W(L1_HubID hubID, L1_BYTE * data, L1_UINT32 size)
{
    return L1_PutDataToHub( (hubID), (L1_CurrentTaskCR->RequestPacket), L1_FIFO, (data), (size), L1_INFINITE_TIMEOUT);
}



/**
 * This function performs a data transfer to a FIFO-Hub.
 * It copies the data stored in the buffer indicated by data into the data
 * part of an L1_Packet and then sends this packet to the Hub.
 *
 * @param hubID ID of the Hub to send data to.
 * @param data pointer to a buffer of type L1_BYTE which contains the data that should be sent to the Hub.
 * @param size size of the buffer pointed to by data. This must not be larger than L1_PACKET_SIZE, otherwise the interaction will return RC_FAIL.
 * @param timeout The timeout in ticks for the interaction.
 *
 * @return L1_Status:
 * - RC_OK: The interaction was successful;
 * - RC_FAIL: The interaction failed. There are multiple reasons for the interaction to fail;
 * -- The buffer data does not fit in the data part of the L1_Packet (L1_PACKET_DATA_SIZE).
 * -- dataBuffer is NULL
 * -- packet is NULL
 * -- General failure of the system causing the interaction with the Hub to fail.
 * - RC_TO: The timeout of the interaction expired.
 *
 * @warning Only use this functions to interact with Port- or Fifo-Hubs. Interacting with other types of Hubs may have undesired effects.
 *
 * \ingroup OCR_FIFO_Hub
 */
static __inline__ L1_Status L1_PutDataToFifo_WT(L1_HubID hubID, L1_BYTE * data, L1_UINT32 size, L1_Timeout timeout)
{
    return L1_PutDataToHub( (hubID), (L1_CurrentTaskCR->RequestPacket), L1_FIFO, (data), (size), (timeout));
}



/**
 * This function performs a data transfer to a FIFO-Hub.
 * It copies the data stored in the buffer indicated by data into the data
 * part of an L1_Packet and then sends this packet to the Hub.
 *
 * @param hubID ID of the Hub to send data to.
 * @param data pointer to a buffer of type L1_BYTE which contains the data that should be sent to the Hub.
 * @param size size of the buffer pointed to by data. This must not be larger than L1_PACKET_SIZE, otherwise the interaction will return RC_FAIL.
 *
 * @return L1_Status:
 * - RC_OK: The interaction was successful;
 * - RC_FAIL: The interaction failed. There are multiple reasons for the interaction to fail;
 * -- The buffer data does not fit in the data part of the L1_Packet (L1_PACKET_DATA_SIZE).
 * -- dataBuffer is NULL
 * -- packet is NULL
 * -- General failure of the system causing the interaction with the Hub to fail.
 * - RC_TO: The timeout of the interaction expired.
 *
 * @warning Only use this functions to interact with Port- or Fifo-Hubs. Interacting with other types of Hubs may have undesired effects.
 *
 * \ingroup OCR_FIFO_Hub
 */
static __inline__ L1_Status L1_PutDataToFifo_NW(L1_HubID hubID, L1_BYTE * data, L1_UINT32 size)
{
    return L1_PutDataToHub( (hubID), (L1_CurrentTaskCR->RequestPacket), L1_FIFO, (data), (size), 0);
}



/**
 * Receives data from a Port-Hub.
 *
 * @param hubID ID of the Hub to send data to.
 * @param dataBuffer This is the pointer to the buffer where to store the data received from the Hub.
 * @param bufferSize This is the size of the dataBuffer in L1_BYTE. This does not indicate that the interaction
 * will receive so much data, it is just an indication of the maximum number of bytes the function can store
 * safely in the dataBuffer. The real number of received bytes is stored, upon return in the parameter bytesReceived.
 * @param bytesReceived Pointer to an L1_UINT32 which will contain the number of bytes that were received from the Hub after the interaction was performed successfully. This parameter may be set to NULL to indicate that no interest in this value exists. However, this is generally not advised.
 *
 * @return L1_Status:
 * - RC_OK: The interaction was successful;
 * - RC_FAIL: The interaction failed. There are multiple reasons for the interaction to fail:
 * -- Not enough space in the dataBuffer. In this case the data is not lost but is still present in the field Data of the used L1_Packet.
 * -- dataBuffer is NULL
 * -- packet is NULL
 * -- General failure of the system causing the interaction with the Hub to fail.
 *
 * \ingroup OCR_FIFO_Hub
 */
static __inline__ L1_Status L1_GetDataFromFifo_W(L1_HubID hubID, L1_BYTE * dataBuffer, L1_UINT32 bufferSize, L1_UINT32 * bytesReceived)
{
    return L1_GetDataFromHub( (hubID), (L1_CurrentTaskCR->RequestPacket), L1_FIFO, (dataBuffer), (bufferSize), (bytesReceived), L1_INFINITE_TIMEOUT);
}



/**
 * Receives data from a Port-Hub.
 *
 * @param hubID ID of the Hub to send data to.
 * @param dataBuffer This is the pointer to the buffer where to store the data received from the Hub.
 * @param bufferSize This is the size of the dataBuffer in L1_BYTE. This does not indicate that the interaction
 * will receive so much data, it is just an indication of the maximum number of bytes the function can store
 * safely in the dataBuffer. The real number of received bytes is stored, upon return in the parameter bytesReceived.
 * @param bytesReceived Pointer to an L1_UINT32 which will contain the number of bytes that were received from the Hub after the interaction was performed successfully. This parameter may be set to NULL to indicate that no interest in this value exists. However, this is generally not advised.
 * @param timeout The timeout to use for the interaction with the Hub.
 *
 * @return L1_Status:
 * - RC_OK: The interaction was successful;
 * - RC_FAIL: The interaction failed. There are multiple reasons for the interaction to fail:
 * -- Not enough space in the dataBuffer. In this case the data is not lost but is still present in the field Data of the used L1_Packet.
 * -- dataBuffer is NULL
 * -- packet is NULL
 * -- General failure of the system causing the interaction with the Hub to fail.
 * - RC_TO: The timeout of the interaction expired.
 *
 * \ingroup OCR_FIFO_Hub
 */
static __inline__ L1_Status L1_GetDataFromFifo_WT(L1_HubID hubID, L1_BYTE * dataBuffer, L1_UINT32 bufferSize, L1_UINT32 * bytesReceived, L1_Timeout timeout)
{
    return L1_GetDataFromHub((hubID), (L1_CurrentTaskCR->RequestPacket), L1_FIFO, (dataBuffer), (bufferSize), (bytesReceived), (timeout));
}



/**
 * Receives data from a Port-Hub.
 *
 * @param hubID ID of the Hub to send data to.
 * @param dataBuffer This is the pointer to the buffer where to store the data received from the Hub.
 * @param bufferSize This is the size of the dataBuffer in L1_BYTE. This does not indicate that the interaction
 * will receive so much data, it is just an indication of the maximum number of bytes the function can store
 * safely in the dataBuffer. The real number of received bytes is stored, upon return in the parameter bytesReceived.
 * @param bytesReceived Pointer to an L1_UINT32 which will contain the number of bytes that were received from the Hub after the interaction was performed successfully. This parameter may be set to NULL to indicate that no interest in this value exists. However, this is generally not advised.
 *
 * @return L1_Status:
 * - RC_OK: The interaction was successful;
 * - RC_FAIL: The interaction failed. There are multiple reasons for the interaction to fail:
 * -- Not enough space in the dataBuffer. In this case the data is not lost but is still present in the field Data of the used L1_Packet.
 * -- dataBuffer is NULL
 * -- packet is NULL
 * -- General failure of the system causing the interaction with the Hub to fail.
 *
 * \ingroup OCR_FIFO_Hub
 */
static __inline__ L1_Status L1_GetDataFromFifo_NW(L1_HubID hubID, L1_BYTE * dataBuffer, L1_UINT32 bufferSize, L1_UINT32 * bytesReceived)
{
    return L1_GetDataFromHub( (hubID), (L1_CurrentTaskCR->RequestPacket), L1_FIFO, (dataBuffer), (bufferSize), (bytesReceived), 0);
}



#endif /* __L1_hub_fifo_api_h__ */
