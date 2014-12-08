#ifndef __L1_CPP_PORT_H__
#define __L1_CPP_PORT_H__


extern "C" 
{
#include <L1_api.h>
}

class L1_CPP_Port
{
public:
	L1_CPP_Port(L1_HubID port);

	/**
	 * This service puts the Request-Packet of the task calling it into a Port.
	 * This service waits until the put request has synchronised with a corresponding
	 * request to get a Packet from the specified Port.
	 *
	 * @return L1_Status:
	 * - RC_OK	service successful (there was a waiting Get request in the Port)
	 * - RC_FAIL	service failed (no corresponding Get request in the Port)
	 *
	 * @pre
	 * - None
	 * - Packet is the preallocated Packet
	 *
	 * @post
	 * - The Header field of the RequestPacket are filled in.
	 * - Header fields of preallocated Packet filled in
	 */
	L1_Status putPacketToPort_W();

	/**
	 * Retrieves a packet from a port using the task's Request-Packet.
	 * This service waits until the get request has synchronised with a
	 * corresponding put packet delivered to the specified Port.
	 *
	 * @warning The payload part of the task specific request-packet gets overwritten as soon as
	 * another request gets sent. Therefore, always copy the payload-data to a local buffer
	 * using L1_memcpy(...).
	 *
	 * @return
	 * - RC_OK	service successful (there was a waiting Put request in the Port)
	 * - RC_FAIL	service failed (no corresponding put request in the Port)
	 *
	 * @pre
	 * - Packet is the preallocated SystemPacket
	 *
	 * @post
	 * - Header fields of Put Packet filled in the Task's System Packet.
	 * - Data of Put Packet will have been filled in.
	 */
	L1_Status getPacketFromPort_W();

	/**
	 * This service puts the Request-Packet of the task calling it into a Port.
	 * The service returns immediately after the Packet was
	 * delivered to the specified Port. Indicates either success  (there was a corresponding request to get a Packet
	 * from the destination Port) or failure (there was no corresponding request to get a Packet from the specified Port;
	 * in that case the put Packet is NOT buffered in the specified Port).
	 * @note If the specified Port is remote than the return time includes a communication delay.
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
	 */
	L1_Status putPacketToPort_NW();

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
	 */
	L1_Status getPacketFromPort_NW();

	/**
	 * This service puts the Request-Packet of the task calling it into a Port.
	 * Waits until either the put
	 * request has synchronised with a corresponding request to get a Packet from the specified
	 * Port, or else the specified timeout has expired. If the timeout has expired the return
	 * value indicates a failed request (there was no corresponding request to get a Packet
	 * from the specified Port) and the put Packet is removed from the specified Port.
	 *
	 * @param Timeout of type L1_Timeout, the number of system ticks the call should wait for synchronisation.
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
	 */
	L1_Status putPacketToPort_WT(L1_Timeout Timeout);

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
	 * @param Timeout of type L1_Timeout, the number of system ticks the call should wait for synchronisation.
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
	 */
	L1_Status getPacketFromPort_WT(L1_Timeout Timeout);

	/**
	 * Puts a Packet (that must be allocated from the Packet Pool) to a Port and returns
	 * immediately without being put in the waiting state. Completion is deferred till a
	 * corresponding Get service request which will return any of the packets previously
	 * Put asynchronously.
	 *
	 * @note The algorithm for L1_PutPacket_A is the same as of L1_PutPacket_W, except that
	 * L1_insertPacketInKernel will not remove the calling Task from the ReadyList.
	 *
	 * @param Packet of type L1_Packet*, the packet to be put asynchronously into the Port.
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
	 */
	L1_Status putPacketToPort_A(L1_Packet * Packet);

	/**
	 * Request to get a Packet from a Port without being put in the waiting state.
	 * This service requires that the Get requests use a Packet has been allocated
	 * from the Packet Pool). The completion is deferred till a corresponding
	 * L1_WaitForPacket service request which will return any of the packets previously
	 * allocated but filled in with the data of a corresponding Put_request to one of the Ports.
	 *
	 * @param Packet of type L1_Packet**
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
	 */
	L1_Status getPacketFromPort_A(L1_Packet * Packet);

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
	L1_Status putDataToPort_W(L1_BYTE * data, L1_UINT32 size);


	/**
	* This function performs a data transfer to a Port-Hub.
	* It copies the data stored in the buffer indicated by data into the data
	* part of an L1_Packet and then sends this packet to the Hub.
	*
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
	*
	*/
	L1_Status putDataToPort_WT(L1_BYTE * data, L1_UINT32 size, L1_Timeout timeout);

	/**
	* This function performs a data transfer to a Port-Hub.
	* It copies the data stored in the buffer indicated by data into the data
	* part of an L1_Packet and then sends this packet to the Hub.
	*
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
	L1_Status putDataToPort_NW(L1_BYTE * data, L1_UINT32 size);

    /**
	* Receives data from a Port-Hub.
	*
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
	L1_Status getDataFromPort_W(L1_BYTE * dataBuffer, L1_UINT32 bufferSize, L1_UINT32 * bytesReceived);

    /**
	* Receives data from a Port-Hub.
	*
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
	L1_Status getDataFromPort_WT(L1_BYTE * dataBuffer, L1_UINT32 bufferSize, L1_UINT32 * bytesReceived, L1_Timeout timeout);

	/**
	* Receives data from a Port-Hub.
	*
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
	L1_Status getDataFromPort_NW(L1_BYTE * dataBuffer, L1_UINT32 bufferSize, L1_UINT32 * bytesReceived);

private:
	L1_HubID HubID;
};


#endif /* !__L1_CPP_PORT_H__ */
