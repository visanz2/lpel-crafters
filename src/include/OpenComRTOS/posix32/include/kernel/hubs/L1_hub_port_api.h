/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2008
 * www.Altreonic.com
 * Module name: ($Path/$Filename)
 * Synopsis: Port Hub API.
 *
 * $LastChangedDate: 2012-09-12 17:18:09 +0200 (Wed, 12 Sep 2012) $
 * $Revision: 2941 $
 * $LastChangedBy: bernhard.sputh $
 *******************************************************************************/

#ifndef __L1_hub_port_api_h__
#define __L1_hub_port_api_h__

#include <L1_types.h>
#include <kernel/hubs/L1_hub.h>
#include <kernel/hubs/L1_hub_data_api.h>


/**
\defgroup OCR_Port_Hub Port Hub
The Port Hub is uses to exchange data between two parts in a reliable way. It's behavior is similar to a CSP-Channel.

\section OCR_Port_Hub_Description Hub Description
The Port Hub, has the following properties, see also the section \ref OCR_Hub :
  - State: void

  - Synchronisation Predicate upon L1_PutPacketToPort_{W,WT,NW}:
    - Predicate: GetWaitingList is not Empty
    -Action: Exchange Data between Put Packet and first waiting Get Packet, and return first waiting Get Packet or initiate the data transfer with the parameters specified in the packet

  - Synchronisation Predicate upon L1_GetPacketFromPort_{W,WT,NW}:
    - Predicate: PutWaitingList is not Empty
    - Action: Exchange Data between Get and first waiting Put Packet, and return first waiting Put Packet or initiate the data transfer with the parameters specified in the packet

  - Invariant(s): both waiting lists are empty, or only one waiting list contains waiting requests, i.e.
    - length (put waiting list) <> 0 implies length (get waiting list) = 0
    - length (get waiting list) <> 0 implies length (put waiting list) = 0

\section OCR_Port_Hub_Example Example
The this example shows how to transfer data from one Task to another Task using a Port.

\subsection OCR_Port_Hub_Example_Entities Entities
  - Port1: Port which is used to exchange data between Task1 and Task2
  - Task1: Task1EntryPoint, shown in section \ref OCR_Port_Hub_Example_Task1
  - Task2: Task2EntryPoint, shown in section \ref OCR_Port_Hub_Example_Task2
  - StdioHostServer1: Access to the console.
  - StdioHostServer1Res: Ensuring that a second task does not interfere with console access.
\section OCR_Port_Hub_Example_Task1 Source Code for Task1EntryPoint
\code
#include <L1_api.h>
#include <L1_node_config.h>

void Task1EntryPoint(L1_TaskArguments Arguments)
{
    L1_Packet *Packet = L1_CurrentTaskCR->RequestPacket;
    L1_BYTE ch;
    for (ch = 'a'; ch <= 'z'; ch++)
    {
        Packet->DataSize = sizeof(L1_BYTE);
        Packet->Data[0]  = ch;

        if (RC_FAIL == L1_PutPacketToPort_W(Port1))
        {
           exit(-1);
        }
    }
}
\endcode

\section OCR_Port_Hub_Example_Task2 Source Code for Task2EntryPoint
\code
#include <L1_api.h>
#include <L1_node_config.h>
#include <StdioHostService/StdioHostClient.h>

void Task2EntryPoint(L1_TaskArguments Arguments)
{
    L1_Packet *Packet = L1_CurrentTaskCR->RequestPacket;

    L1_BYTE ch, i;

    for(i = 0; i < 26; i++)
    {
        if(RC_OK == L1_GetPacketFromPort_W(Port1))
        {
            Packet->DataSize = sizeof(L1_BYTE);
            ch = Packet->Data[0];
            L1_LockResource_W(StdioHostServer1Res);
            Shs_putString_W(StdioHostServer1, "The following symbol was get from Port1: ");
            Shs_putChar_W(StdioHostServer1, ch);
            Shs_putChar_W(StdioHostServer1, '\n');
            L1_UnlockResource_W(StdioHostServer1Res);
        }else
        {
            Shs_putString_W(StdioHostServer1, "Error: Could not acquire a symbol from Port1, terminating. \n");
        }
    }
}
\endcode
*/



/**
 * This service puts the Request-Packet of the task calling it into a Port.
 * This service waits until the put request has synchronised with a corresponding
 * request to get a Packet from the specified Port.
 *
 * @param HubID of type L1_HubID, which identifies the Port.
 *
 * @return L1_Status:
 * - RC_OK  service successful (there was a waiting Get request in the Port)
 * - RC_FAIL    service failed (no corresponding Get request in the Port)
 *
 * @pre
 * - None
 * - Packet is the preallocated Packet
 *
 * @post
 * - The Header field of the RequestPacket are filled in.
 * - Header fields of preallocated Packet filled in
 *
 * \ingroup OCR_Port_Hub
 */
static __inline__ L1_Status L1_PutPacketToPort_W(L1_HubID HubID)
{
    return L1_buildAndInsertPacket((HubID), (L1_CurrentTaskCR->RequestPacket), (L1_UINT16)(L1_SID_SEND_TO_HUB | (L1_PORT << 8)), L1_INFINITE_TIMEOUT);
}



/**
 * Retrieves a packet from a port using the task's Request-Packet.
 * This service waits until the get request has synchronised with a
 * corresponding put packet delivered to the specified Port.
 *
 * @warning The payload part of the task specific request-packet gets overwritten as soon as
 * another request gets sent. Therefore, always copy the payload-data to a local buffer
 * using L1_memcpy(...).
 *
 * @param  HubID L1_HubID which identifies the Port.
 *
 * @return
 * - RC_OK  service successful (there was a waiting Put request in the Port)
 * - RC_FAIL    service failed (no corresponding put request in the Port)
 *
 * @pre
 * - Packet is the preallocated SystemPacket
 *
 * @post
 * - Header fields of Put Packet filled in the Task's System Packet.
 * - Data of Put Packet will have been filled in.
 *
 * \ingroup OCR_Port_Hub
 */
static __inline__ L1_Status  L1_GetPacketFromPort_W(L1_HubID HubID)
{
    return L1_buildAndInsertPacket((HubID), (L1_CurrentTaskCR->RequestPacket), (L1_UINT16)(L1_SID_RECEIVE_FROM_HUB | (L1_PORT << 8)), L1_INFINITE_TIMEOUT);
}



/**
 * This service puts the Request-Packet of the task calling it into a Port.
 * Waits until either the put
 * request has synchronised with a corresponding request to get a Packet from the specified
 * Port, or else the specified timeout has expired. If the timeout has expired the return
 * value indicates a failed request (there was no corresponding request to get a Packet
 * from the specified Port) and the put Packet is removed from the specified Port.
 *
 * @param HubID of type L1_HubID, which identifies the Port.
 * @param timeout of type L1_Timeout, the number of system ticks the call should wait for synchronisation.
 *
 *
 *
 * @return L1_Status:
 * - RC_OK service successful (there was a waiting Get request in the Port)
 * - RC_FAIL service failed (no corresponding Get request in the Port)
 * - RC_TO service timed out.
 *
 * @pre
 * - None
 * - Packet is the preallocated Packet
 *
 * @post
 * - The Header field of the RequestPacket are filled in.
 * - Header fields of preallocated Packet filled in
 *
 * \ingroup OCR_Port_Hub
 */
static __inline__ L1_Status L1_PutPacketToPort_WT(L1_HubID HubID, L1_Timeout timeout)
{
    return L1_buildAndInsertPacket((HubID), (L1_CurrentTaskCR->RequestPacket), (L1_UINT16)(L1_SID_SEND_TO_HUB | (L1_PORT << 8)), (timeout));
}



/**
 * Retrieves a packet from a port using the task's Request-Packet.
 * Waits until either the get request has synchronised
 * with  a corresponding put request delivered to the specified Port, or either the specified
 * timeout has expired. If the timeout has expired the return value indicates a failed request
 * (there was no corresponding request to get a Packet from the specified Port) and the get
 * Packet is removed from the Specified Port.
 *
 * @warning The payload part of the task specific request-packet gets overwritten as soon as
 * another request gets sent. Therefore, always copy the payload-data to a local buffer
 * using L1_memcpy(...).
 *
 * @param  HubID L1_HubID which identifies the Port.
 * @param  timeout of type L1_Timeout, the number of system ticks the call should wait for synchronisation.
 *
 * @return
 * - RC_OK service successful (there was a waiting Put request in the Port)
 * - RC_FAIL service failed (no corresponding put request in the Port)
 * - RC_TO service timed out.
 * @pre
 * - Packet is the preallocated SystemPacket
 *
 * @post
 * - Header fields of Put Packet filled in the Task's System Packet.
 * - Data of Put Packet will have been filled in.
 *
 * \ingroup OCR_Port_Hub
 */
static __inline__ L1_Status L1_GetPacketFromPort_WT(L1_HubID HubID, L1_Timeout timeout)
{
    return L1_buildAndInsertPacket((HubID), (L1_CurrentTaskCR->RequestPacket), (L1_UINT16)(L1_SID_RECEIVE_FROM_HUB | (L1_PORT << 8)), (timeout));
}



/**
 * This service puts the Request-Packet of the task calling it into a Port.
 * The service returns immediately after the Packet was
 * delivered to the specified Port. Indicates either success  (there was a corresponding request to get a Packet
 * from the destination Port) or failure (there was no corresponding request to get a Packet from the specified Port;
 * in that case the put Packet is NOT buffered in the specified Port).
 * @note If the specified Port is remote than the return time includes a communication delay.
 *
 * @param HubID of type L1_HubID, which identifies the Port.
 *
 * @return L1_Status:
 * - RC_OK    service successful (there was a waiting Get request in the Port)
 * - RC_FAIL  service failed (no corresponding Get request in the Port)
 *
 * @pre
 * - None
 * - Packet is the preallocated Packet
 *
 * @post
 * - The Header field of the RequestPacket are filled in.
 * - Header fields of preallocated Packet filled in
 *
 * \ingroup OCR_Port_Hub
 */
static __inline__ L1_Status L1_PutPacketToPort_NW(L1_HubID HubID)
{
    return L1_buildAndInsertPacket((HubID), (L1_CurrentTaskCR->RequestPacket), (L1_UINT16)(L1_SID_SEND_TO_HUB | (L1_PORT << 8)), 0);
}



/**
 * Retrieves a packet from a port using the task's Request-Packet.
 * Returns immediately after the get request was delivered to the specified Port,
 * indicating either success (there was a corresponding put  request at the specified Port) or a failure (there was no put
 * request at the specified Port; in that case the Get Packet is NOT buffered in the specified Port).
 *
 * @warning The payload part of the task specific request-packet gets overwritten as soon as
 * another request gets sent. Therefore, always copy the payload-data to a local buffer
 * using L1_memcpy(...).
 *
 * @param  HubID L1_HubID which identifies the Port.
 * @note If the specified Port is remote than the return time includes a communication delay.
 *
 * @return
 * - RC_OK  service successful (there was a waiting Put request in the Port)
 * - RC_FAIL    service failed (no corresponding put request in the Port)
 *
 * @pre
 * - Packet is the preallocated SystemPacket
 *
 * @post
 * - Header fields of Put Packet filled in the Task's System Packet.
 * - Data of Put Packet will have been filled in.
 *
 * \ingroup OCR_Port_Hub
 */
static __inline__ L1_Status L1_GetPacketFromPort_NW(L1_HubID HubID)
{
    return L1_buildAndInsertPacket((HubID), (L1_CurrentTaskCR->RequestPacket), (L1_UINT16)(L1_SID_RECEIVE_FROM_HUB | (L1_PORT << 8)), 0);
}



#ifdef ASYNC_SERVICES
 /**
  * Puts a Packet (that must be allocated from the Packet Pool) to a Port and returns
  * immediately without being put in the waiting state. Completion is deferred till a
  * corresponding Get service request which will return any of the packets previously
  * Put asynchronously.
  *
  * @note The algorithm for L1_PutPacketToPort_A is the same as of L1_PutPacket_W, except that
  * L1_insertPacketInKernel will not remove the calling Task from the ReadyList.
  *
  * @param HubID of type L1_HubID, which identifies the Port.
  * @param packet of type L1_Packet*, the packet to be put asynchronously into the Port.
  *
  * @return L1_Status:
  * - RC_OK    service successful (there was a waiting Get request in the Port)
  * - RC_FAIL  service failed (no corresponding Get request in the Port)
  *
  * @pre
  * - Packet must have been allocated by the function L1_AllocatePacket.
  *
  * @post
  * - The calling task will remain on the READY List.
  *
  * \ingroup OCR_Port_Hub
  */
static __inline__ L1_Status L1_PutPacketToPort_A(L1_HubID HubID, L1_Packet* packet)
{
    return L1_buildAndInsertPacket((HubID), (packet), (L1_UINT16)(L1_SID_SEND_TO_HUB | (L1_PORT << 8)), L1_ASYNC);
}



/**
 * Request to get a Packet from a Port without being put in the waiting state.
 * This service requires that the Get requests use a Packet has been allocated
 * from the Packet Pool). The completion is deferred till a corresponding
 * L1_WaitForPacket service request which will return any of the packets previously
 * allocated but filled in with the data of a corresponding Put_request to one of the Ports.
 *
 * @param HubID of type L1_HubID which identifies the Port.
 * @param packet of type L1_Packet*
 *
 * @return L1_Status
 * - RC_OK service completed successfully.
 * - RC_FAIL service failed
 *
 * @pre
 * - Packet must have been allocated by the function L1_AllocatePacket().
 *
 * @post
 * - The calling task will remain on the READY List.
 *
 * \ingroup OCR_Port_Hub
 */
static __inline__ L1_Status L1_GetPacketFromPort_A(L1_HubID HubID, L1_Packet* packet)
{
    return L1_buildAndInsertPacket((HubID), (packet), (L1_UINT16)(L1_SID_RECEIVE_FROM_HUB | (L1_PORT << 8)), L1_ASYNC);
}



#endif /* ASYNC_SERVICES */


/**
 * This function performs a data transfer to a Port-Hub.
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
 * \ingroup OCR_Port_Hub
 */
static __inline__ L1_Status L1_PutDataToPort_W(L1_HubID hubID, L1_BYTE * data, L1_UINT32 size)
{
    return L1_PutDataToHub( (hubID), (L1_CurrentTaskCR->RequestPacket), L1_PORT, (data), (size), L1_INFINITE_TIMEOUT);
}



/**
 * This function performs a data transfer to a Port-Hub.
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
 * \ingroup OCR_Port_Hub
 */
static __inline__ L1_Status L1_PutDataToPort_WT(L1_HubID hubID, L1_BYTE * data, L1_UINT32 size, L1_Timeout timeout)
{
    return L1_PutDataToHub( (hubID), (L1_CurrentTaskCR->RequestPacket), L1_PORT, (data), (size), (timeout));
}



/**
 * This function performs a data transfer to a Port-Hub.
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
 * \ingroup OCR_Port_Hub
 */
static __inline__ L1_Status L1_PutDataToPort_NW(L1_HubID hubID, L1_BYTE * data, L1_UINT32 size)
{
    return L1_PutDataToHub( (hubID), (L1_CurrentTaskCR->RequestPacket), L1_PORT, (data), (size), 0);
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
 * \ingroup OCR_Port_Hub
 */
static __inline__ L1_Status L1_GetDataFromPort_W(L1_HubID hubID, L1_BYTE * dataBuffer, L1_UINT32 bufferSize, L1_UINT32 * bytesReceived)
{
    return L1_GetDataFromHub( (hubID), (L1_CurrentTaskCR->RequestPacket), L1_PORT, (dataBuffer), (bufferSize), (bytesReceived), L1_INFINITE_TIMEOUT);
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
 * \ingroup OCR_Port_Hub
 */
static __inline__ L1_Status L1_GetDataFromPort_WT(L1_HubID hubID, L1_BYTE * dataBuffer, L1_UINT32 bufferSize, L1_UINT32 * bytesReceived, L1_Timeout timeout)
{
    return L1_GetDataFromHub( (hubID), (L1_CurrentTaskCR->RequestPacket), L1_PORT, (dataBuffer), (bufferSize), (bytesReceived), (timeout));
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
 * \ingroup OCR_Port_Hub
 */
static __inline__ L1_Status L1_GetDataFromPort_NW(L1_HubID hubID, L1_BYTE * dataBuffer, L1_UINT32 bufferSize, L1_UINT32 * bytesReceived)
{
    return L1_GetDataFromHub( (hubID), (L1_CurrentTaskCR->RequestPacket), L1_PORT, (dataBuffer), (bufferSize), (bytesReceived), 0);
}



#endif /* __L1_hub_port_api_h__ */
