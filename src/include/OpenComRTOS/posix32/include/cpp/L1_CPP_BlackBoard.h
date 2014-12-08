#ifndef __L1_CPP_BLACKBOARD_H__
#define __L1_CPP_BLACKBOARD_H__


extern "C"
{
#include <L1_api.h>
}

class L1_CPP_BlackBoard
{
public:
	L1_CPP_BlackBoard(L1_HubID blackBoard);

	/**
	 * This interaction erases the message from the black board. Any Task trying to copy the message from the black black will be put onto the waiting list.
	 *
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
	L1_Status wipeBoard_W();

	/**
	 * This interaction erases the message from the black board. Any Task trying to copy the message from the black black will be put onto the waiting list.
	 *
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
	L1_Status wipeBoard_WT(L1_Timeout timeout);

	/**
	 * This interaction erases the message from the black board. Any Task trying to copy the message from the black black will be put onto the waiting list.
	 *
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
	L1_Status wipeBoard_NW();


	/**
	 * Writes a message onto the Black Board.
	 *
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
	L1_Status writeMessageOntoBoard_W(L1_BYTE * message, L1_UINT32 messageSize);



	/**
	 * Writes a message onto the Black Board.
	 *
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
	L1_Status writeMessageOntoBoard_WT(L1_BYTE * message, L1_UINT32 messageSize, L1_Timeout timeout);


	/**
	 * Writes a message onto the Black Board.
	 *
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
	L1_Status writeMessageOntoBoard_NW(L1_BYTE * message, L1_UINT32 messageSize);


	/**
	 * Reads a message from a Black Board Hub and copies it into a buffer.
	 *
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
	L1_Status copyMessageFromBoard_W(L1_BYTE * messageBuffer, L1_UINT32 bufferSize, L1_UINT32 * receivedMessageSize, L1_UINT32 * messageNumber);

	/**
	 * Reads a message from a Black Board Hub and copies it into a buffer.
	 *
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
	L1_Status copyMessageFromBoard_WT(L1_BYTE * messageBuffer, L1_UINT32 bufferSize, L1_UINT32 * receivedMessageSize, L1_UINT32 * messageNumber, L1_Timeout timeout);

	/**
	 * Reads a message from a Black Board Hub and copies it into a buffer.
	 *
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
	L1_Status copyMessageFromBoard_NW(L1_BYTE * messageBuffer, L1_UINT32 bufferSize, L1_UINT32 * receivedMessageSize, L1_UINT32 * messageNumber);

private:
	L1_HubID HubID;
};


#endif /* !__L1_CPP_BLACKBOARD_H__ */
