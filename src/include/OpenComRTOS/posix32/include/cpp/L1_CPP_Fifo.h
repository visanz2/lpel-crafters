#ifndef __L1_CPP_FIFO_H__
#define __L1_CPP_FIFO_H__

extern "C" 
{
  #include <L1_api.h>
}

class L1_CPP_Fifo
{
 public:
  L1_CPP_Fifo(L1_HubID fifo);

  /**
  * Inserts the payload-data of a task's Request-Packet into a FIFO. This service waits until it could insert the data into the specified FIFO.
  *
  *
  * @return L1_Status
  * - RC_OK	service successful (the data was inserted in the FIFO)
  * - RC_FAIL	service failed (the data was not inserted in the FIFO)
  *
  * @pre
  *  - None
  *
  * @post
  * - Calling task ready
  *
  */
  L1_Status enqueueFifo_W();

  /**
  * Retrieves data from a FIFO, the data is stored in the payload of the task's Request-Packet.
  * This call waits until there is data in the FIFO to be retrieved.
  *
  * @warning The payload part of the task specific request-packet gets overwritten as soon as
  * another request gets sent. Therefore, always copy the payload-data to a local buffer
  * using L1_memcpy(...).
  *
  * @return L1_Status
  * - RC_OK	service successful (the data was inserted in the FIFO)
  * - RC_FAIL	service failed (the data was not inserted in the FIFO)
  *
  * @pre
  * - None
  *
  * @post
  * - Calling task ready
  */
  L1_Status dequeueFifo_W();

  /**
  *
  * Inserts the payload-data of a task's Request-Packet into a FIFO.
  * This call returns immediately, even if the packet could not be enqueued in the FIFO.
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
  */
  L1_Status enqueueFifo_NW();

  /**
  * Retrieves data from a FIFO, the data is stored in the payload of the task's Request-Packet.
  *
  * This call returns immediately, even if there is no packet available in the FIFO.
  *
  * @warning The payload part of the task specific request-packet gets overwritten as soon as
  * another request gets sent. Therefore, always copy the payload-data to a local buffer
  * using L1_memcpy(...).
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
  */
  L1_Status dequeueFifo_NW();
  
  /**
  * Inserts the payload-data of a task's Request-Packet into a FIFO.
  * This service tries to enqueue a packet into the FIFO until the the timeout expires.
  *
  * @param Timeout of type L1_Timeout, the number of system ticks the call should wait while trying to enqueue the packet.
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
  */
  L1_Status enqueueFifo_WT(L1_Timeout Timeout);

  /**
  * Retrieves data from a FIFO, the data is stored in the payload of the task's Request-Packet.
  * Waits until either data becomes available or the timeout expired, depending on what happens first.
  *
  * @warning The payload part of the task specific request-packet gets overwritten as soon as
  * another request gets sent. Therefore, always copy the payload-data to a local buffer
  * using L1_memcpy(...).
  *
  * @param Timeout of type L1_Timeout, the number of system ticks the call should wait for a packet to become available.
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
  */
  L1_Status dequeueFifo_WT(L1_Timeout Timeout);

  /**
  * This function performs a data transfer to a FIFO-Hub.
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
  *
  * @warning Only use this functions to interact with Port- or Fifo-Hubs. Interacting with other types of Hubs may have undesired effects.
  *
  * \ingroup OCR_FIFO_Hub
  */
  L1_Status putDataToFifo_W(L1_BYTE * data, L1_UINT32 size);

  /**
  * This function performs a data transfer to a FIFO-Hub.
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
  * \ingroup OCR_FIFO_Hub
  */
  L1_Status putDataToFifo_WT(L1_BYTE * data, L1_UINT32 size, L1_Timeout timeout);

  /**
  * This function performs a data transfer to a FIFO-Hub.
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
  * \ingroup OCR_FIFO_Hub
  */
  L1_Status putDataToFifo_NW(L1_BYTE * data, L1_UINT32 size);


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
  * \ingroup OCR_FIFO_Hub
  */

  L1_Status getDataFromFifo_W(L1_BYTE * dataBuffer, L1_UINT32 bufferSize, L1_UINT32 * bytesReceived);

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
  * \ingroup OCR_FIFO_Hub
  */
  L1_Status getDataFromFifo_WT(L1_BYTE * dataBuffer, L1_UINT32 bufferSize, L1_UINT32 * bytesReceived, L1_Timeout timeout);

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
  * \ingroup OCR_FIFO_Hub
  */
  L1_Status getDataFromFifo_NW(L1_BYTE * dataBuffer, L1_UINT32 bufferSize, L1_UINT32 * bytesReceived);

 private:
  L1_HubID HubID;
};


#endif /* !__L1_CPP_FIFO_H__ */
