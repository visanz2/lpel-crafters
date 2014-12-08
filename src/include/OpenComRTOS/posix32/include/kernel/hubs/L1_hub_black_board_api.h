/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2008
 * www.Altreonic.com
 * Module name: ($Path/$Filename)
 * Synopsis: Black Board Hub API.
 *
 * $LastChangedDate: 2012-09-12 17:18:09 +0200 (Wed, 12 Sep 2012) $
 * $Revision: 2941 $
 * $LastChangedBy: bernhard.sputh $
 *******************************************************************************/

#ifndef __L1_hub_black_board_api_h__
#define __L1_hub_black_board_api_h__

#include <L1_types.h>
#include <kernel/hubs/L1_hub.h>
#include <kernel/L1_kernel_data.h>

/**
\defgroup OCR_BlackBoard_Hub Black Board Hub

\section OCR_BlackBoard_Hub Hub Description

The Blackboard Hub is meant as a `safe global data structure', where data can be published to. It is safer than a normal global data structure for the following reasons:

 - There is no read operation taking place while a write operation takes place.
 - The readers of the black board get told how many times the message on the board has been updated already, thus they can check whether they missed an update and thus take corrective action if needed.
 - If the blackboard is empty, i.e. no data is present, the readers will be put onto the Waiting List of the Hub (_WT and _NW semantics are obeyed) and will be released upon the writer posting a message onto the board. There are two reasons why no data might be present on the board, the first one being because no one has written any data yet, i.e. after system start up. The second reason is that the board has been wiped.
 - The readers have their own private copy of the contents of the blackboard and they decide when it will be updated with new contents. This prevents changes of the global variable contents half way during processing.


The Port Hub, has the following properties, see also the section \ref OCR_Hub :
  - State: void

  - Synchronisation Predicate upon L1_WriteMessageOntoBoard_{W,WT,NW}:
    - Predicate: None
    - Action: Copy the content of the message onto the Black Board, unless the defined message size is 0. A message size of zero indicates that the Black Board should be wiped.

  - Synchronisation Predicate upon L1_CopyMessageFromBoard_{W,WT,NW}:
    - Predicate: messageSize non zero.
    - Action: Copies the message that is currently on the Black Board to a user defined buffer.
*/


/**
 * This function erases the message from the black board. Any Task trying to copy the message from the black black will be put onto the waiting list.
 * Interactions with the blackboard can have an infinite timeout, or be set to expire after a specific time.
 *
 * @param hubID ID which identifies the blackboard hub.
 * @param packet Message to be written to the blackboard.
 * @param Timeout Amount of milliseconds to wait for the interaction to expire. Can be set to the max value to wait forever.
 *
 * @return L1_Status:
 * - RC_OK  service successful
 * - RC_FAIL service failed
 * - RC_TO service timed out
 *
  * @pre
 * - None
 *
 * @post
 * - None
 *
 * \ingroup OCR_BlackBoard_Hub
 */
L1_Status L1_WipeBoard(L1_HubID hubID, L1_Packet * packet, L1_Timeout Timeout);


/**
 * This interaction erases the message from the black board. Any Task trying to copy the message from the black black will be put onto the waiting list.
 *
 * @param hubID of type L1_HubID, which identifies the Black Board Hub.
 *
 * @return L1_Status:
 * - RC_OK  service successful
 * - RC_FAIL    service failed
 *
 * @pre
 * - None
 *
 * @post
 * - None
 *
 * \ingroup OCR_BlackBoard_Hub
 */
static __inline__ L1_Status L1_WipeBoard_W(L1_HubID hubID)
{
    return L1_WipeBoard(hubID, L1_CurrentTaskCR->RequestPacket, L1_INFINITE_TIMEOUT);
}



/**
 * This interaction erases the message from the black board. Any Task trying to copy the message from the black black will be put onto the waiting list.
 *
 * @param hubID of type L1_HubID, which identifies the Black Board Hub.
 * @param timeout of type L1_Timeout, the number of system ticks the call should wait for synchronisation.
 *
 *
 * @return L1_Status:
 * - RC_OK  service successful
 * - RC_FAIL service failed
 * - RC_TO service timed out.
 *
 * @pre
 * - None
 *
 * @post
 * - None
 *
 * \ingroup OCR_BlackBoard_Hub
 */
static __inline__ L1_Status L1_WipeBoard_WT(L1_HubID hubID, L1_Timeout timeout)
{
    return L1_WipeBoard(hubID, L1_CurrentTaskCR->RequestPacket, timeout);
}



/**
 * This interaction erases the message from the black board. Any Task trying to copy the message from the black black will be put onto the waiting list.
 *
 * @param hubID of type L1_HubID, which identifies the Black Board Hub.
 *
 * @return L1_Status:
 * - RC_OK  service successful
 * - RC_FAIL    service failed
 *
 * @pre
 * - None
 *
 * @post
 * - None
 *
 * \ingroup OCR_BlackBoard_Hub
 */
static __inline__ L1_Status L1_WipeBoard_NW(L1_HubID hubID)
{
    return L1_WipeBoard(hubID, L1_CurrentTaskCR->RequestPacket, 0);
}



/**
 * Writes a message onto the Black Board.
 * This function copies the message into the packet and inserts it into the hub with the specified timeout.
 *
 * @param hubID ID of the identifies the blackboard hub.
 * @param packet Packet to be used to write message to blackboard hub.
 * @param message Pointer to the message to write onto the Black Board.
 * @param messageSize Size of the message that should be written onto the Black Board. The size of the message must be less or equal `L1_PACKET_SIZE - sizeof(L1_UINT32)', otherwise the interaction will fail.
 * @param Timeout Timeout value the operation.
 *
 * @return L1_Status:
 * - RC_OK  service successful
 * - RC_FAIL service failed
 * - RC_TO service timed out
 *
 * @pre
 * - None
 *
 * @post
 * - None
 *
 * \ingroup OCR_BlackBoard_Hub
 */
L1_Status L1_WriteMessageOntoBoard(L1_HubID hubID, L1_Packet * packet, L1_BYTE * message, L1_UINT32 messageSize, L1_Timeout Timeout);

/**
 * Writes a message onto the Black Board.
 *
 * @param hubID of type L1_HubID, which identifies the Black Board Hub.
 * @param message Pointer to the message to write onto the Black Board.
 * @param messageSize Size of the message that should be written onto the Black Board. The size of the message must be less or equal `L1_PACKET_SIZE - sizeof(L1_UINT32)', otherwise the interaction will fail.
 *
 * @return L1_Status:
 * - RC_OK  service successful
 * - RC_FAIL service failed
 *
 * @pre
 * - None
 *
 * @post
 * - None
 *
 * \ingroup OCR_BlackBoard_Hub
 */
static __inline__ L1_Status L1_WriteMessageOntoBoard_W(L1_HubID hubID, L1_BYTE * message, L1_UINT32 messageSize)
{
    return L1_WriteMessageOntoBoard(hubID, L1_CurrentTaskCR->RequestPacket, message, messageSize, L1_INFINITE_TIMEOUT);
}



/**
 * Writes a message onto the Black Board.
 *
 * @param hubID of type L1_HubID, which identifies the Black Board Hub.
 * @param message Pointer to the message to write onto the Black Board.
 * @param messageSize Size of the message that should be written onto the Black Board. The size of the message must be less or equal `L1_PACKET_SIZE - sizeof(L1_UINT32)', otherwise the interaction will fail.
 * @param timeout of type L1_Timeout, the number of system ticks the call should wait for synchronisation.
 * @return L1_Status:
 * - RC_OK  service successful
 * - RC_FAIL service failed
 * - RC_TO service timed out
 * @pre
 * - None
 *
 * @post
 * - None
 *
 * \ingroup OCR_BlackBoard_Hub
 */
static __inline__ L1_Status L1_WriteMessageOntoBoard_WT(L1_HubID hubID, L1_BYTE * message, L1_UINT32 messageSize, L1_Timeout timeout)
{
    return L1_WriteMessageOntoBoard(hubID, L1_CurrentTaskCR->RequestPacket, message, messageSize, timeout);
}



/**
 * Writes a message onto the Black Board.
 *
 * @param hubID of type L1_HubID, which identifies the Black Board Hub.
 * @param message Pointer to the message to write onto the Black Board.
 * @param messageSize Size of the message that should be written onto the Black Board. The size of the message must be less or equal `L1_PACKET_SIZE - sizeof(L1_UINT32)', otherwise the interaction will fail.
 *
 * @return L1_Status:
 * - RC_OK  service successful
 * - RC_FAIL service failed
 *
 * @pre
 * - None
 *
 * @post
 * - None
 *
 * \ingroup OCR_BlackBoard_Hub
 */
static __inline__ L1_Status L1_WriteMessageOntoBoard_NW(L1_HubID hubID, L1_BYTE * message, L1_UINT32 messageSize)
{
    return L1_WriteMessageOntoBoard(hubID, L1_CurrentTaskCR->RequestPacket, message, messageSize, 0);
}



/**
 * Reads a message from a Black Board Hub and copies it into a buffer.
 *
 * @param hubID ID of the Black Board Hub.
 * @param packet Packet to be used for the interaction. The data and data size fields of this packet are copied into the message buffer.
 * @param messageBuffer Pointer to the buffer where to store the message retrieved from the Black Board Hub. If NULL this function returns RC_FAIL;
 * @param bufferSize size of the buffer, must be greater or equal to the message retrieved from the Black Board Hub, otherwise RC_FAIL will be returned.
 * @param receivedMessageSize Pointer to a variable of type L1_UINT32 where the size in byte of the retrieved message will be stored. This parameter may be set to NULL if this information is not desired.
 * @param messageNumber Pointer to a variable of type L1_UINT32 where the number of the message will be stored. The message number gets incremented by the Black Board Hub every time a Task writes a message onto the board.
 * @param Timeout Timeout value for the operation. When set to max, timeout is disabled.
 *
 * @return L1_Status:
 * - RC_OK   operation successful
 * - RC_FAIL operation failed
 * - RC_TO   operation timed out
 *
 * @pre
 * - None
 *
 * @post
 * - None
 *
 * \ingroup OCR_BlackBoard_Hub
 */
L1_Status L1_CopyMessageFromBoard(L1_HubID hubID, L1_Packet * packet, L1_BYTE * messageBuffer, L1_UINT32 bufferSize, L1_UINT32 * receivedMessageSize, L1_UINT32 * messageNumber, L1_Timeout Timeout);

/**
 * Reads a message from a Black Board Hub and copies it into a buffer.
 *
 * @param hubID of type L1_HubID, which identifies the Black Board Hub.
 * @param messageBuffer pointer to the buffer where to store the message retrieved from the Black Board Hub. If NULL this interaction will return RC_FAIL;
 * @param bufferSize size of the buffer, must be greater or equal to the message retrieved from the Black Board Hub, otherwise RC_FAIL will be returned.
 * @param receivedMessageSize pointer to a variable of type L1_UINT32 where the size in byte of the retrieved message will be stored. This parameter may be set to NULL if this information is not desired.
 * @param messageNumber pointer to a variable of type L1_UINT32 where the number of the message will be stored. The message number gets incremented by the Black Board Hub every time a Task writes a message onto the board.
 * @return L1_Status:
 * - RC_OK   service successful
 * - RC_FAIL service failed
 *
 * @pre
 * - None
 *
 * @post
 * - None
 *
 * \ingroup OCR_BlackBoard_Hub
 */
static __inline__ L1_Status L1_CopyMessageFromBoard_W(L1_HubID hubID, L1_BYTE * messageBuffer, L1_UINT32 bufferSize, L1_UINT32 * receivedMessageSize, L1_UINT32 * messageNumber)
{
    return L1_CopyMessageFromBoard(hubID, L1_CurrentTaskCR->RequestPacket, messageBuffer, bufferSize, receivedMessageSize, messageNumber, L1_INFINITE_TIMEOUT);
}



/**
 * Reads a message from a Black Board Hub and copies it into a buffer.
 *
 * @param hubID of type L1_HubID, which identifies the Black Board Hub.
 * @param messageBuffer pointer to the buffer where to store the message retrieved from the Black Board Hub. If NULL this interaction will return RC_FAIL;
 * @param bufferSize size of the buffer, must be greater or equal to the message retrieved from the Black Board Hub, otherwise RC_FAIL will be returned.
 * @param receivedMessageSize pointer to a variable of type L1_UINT32 where the size in byte of the retrieved message will be stored. This parameter may be set to NULL if this information is not desired.
 * @param messageNumber pointer to a variable of type L1_UINT32 where the number of the message will be stored. The message number gets incremented by the Black Board Hub every time a Task writes a message onto the board.
 * @param timeout of type L1_Timeout, the number of system ticks the call should wait for synchronisation.
 *
 * @return L1_Status:
 * - RC_OK  service successful
 * - RC_FAIL service failed
 * - RC_TO service timed out
 *
 * @pre
 * - None
 *
 * @post
 * - None
 *
 * \ingroup OCR_BlackBoard_Hub
 */
static __inline__ L1_Status L1_CopyMessageFromBoard_WT(L1_HubID hubID, L1_BYTE * messageBuffer, L1_UINT32 bufferSize, L1_UINT32 * receivedMessageSize, L1_UINT32 * messageNumber, L1_Timeout timeout)
{
    return L1_CopyMessageFromBoard(hubID, L1_CurrentTaskCR->RequestPacket, messageBuffer, bufferSize, receivedMessageSize, messageNumber, timeout);
}



/**
 * Reads a message from a Black Board Hub and copies it into a buffer.
 *
 * @param hubID of type L1_HubID, which identifies the Black Board Hub.
 * @param messageBuffer pointer to the buffer where to store the message retrieved from the Black Board Hub. If NULL this interaction will return RC_FAIL;
 * @param bufferSize size of the buffer, must be greater or equal to the message retrieved from the Black Board Hub, otherwise RC_FAIL will be returned.
 * @param receivedMessageSize pointer to a variable of type L1_UINT32 where the size in byte of the retrieved message will be stored. This parameter may be set to NULL if this information is not desired.
 * @param messageNumber pointer to a variable of type L1_UINT32 where the number of the message will be stored. The message number gets incremented by the Black Board Hub every time a Task writes a message onto the board.
 * @return L1_Status:
 * - RC_OK   service successful
 * - RC_FAIL service failed
 *
 * @pre
 * - None
 *
 * @post
 * - None
 *
 * \ingroup OCR_BlackBoard_Hub
 */
static __inline__ L1_Status L1_CopyMessageFromBoard_NW(L1_HubID hubID, L1_BYTE * messageBuffer, L1_UINT32 bufferSize, L1_UINT32 * receivedMessageSize, L1_UINT32 * messageNumber)
{
    return L1_CopyMessageFromBoard(hubID, L1_CurrentTaskCR->RequestPacket, messageBuffer, bufferSize, receivedMessageSize, messageNumber, 0);
}



#endif /* __L1_hub_black_board_api_h__ */
