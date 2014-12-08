/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2008
 * www.Altreonic.com
 * Module name: ($Path/$Filename)
 * Synopsis: Hub data exchange API functions.
 *
 * $LastChangedDate: 2012-09-12 17:18:09 +0200 (Wed, 12 Sep 2012) $
 * $Revision: 2941 $
 * $LastChangedBy: bernhard.sputh $
 *******************************************************************************/

#ifndef __L1_hub_data_api_h__
#define __L1_hub_data_api_h__

#include <L1_types.h>
#include <kernel/hubs/L1_hub.h>


/**
 * \internal
 * This function performs a data transfer to either a Port- or a Fifo-Hub.
 * It copies the data stored in the buffer indicated by data into the data
 * part of an L1_Packet and then sends this packet to the Hub.
 *
 * @param hubID ID of the Hub to send data to. This must be either a Port-Hub or a Fifo-Hub
 * @param packet Pointer to the L1_Packet to use for this interaction.
 * @param hubType Indicates the type of Hub the function interacts with, permitted values are: L1_PORT and L1_FIFO.
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
 */

L1_Status L1_PutDataToHub(L1_HubID hubID, L1_Packet * packet, L1_UINT32 hubType, L1_BYTE * data, L1_UINT32 size, L1_Timeout timeout);


/**
 * \internal
 * @param hubID ID of the Hub to send data to. This must be either a Port-Hub or a Fifo-Hub
 * @param packet Pointer to the L1_Packet to use for this interaction.
 * @param hubType Indicates the type of Hub the function interacts with, permitted values are: L1_PORT and L1_FIFO.
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
 * @warning Only use this functions to interact with Port- or Fifo-Hubs. Interacting with other types of Hubs may have undesired effects.
 */
L1_Status L1_GetDataFromHub(L1_HubID hubID, L1_Packet * packet, L1_UINT32 hubType, L1_BYTE * dataBuffer, L1_UINT32 bufferSize, L1_UINT32 * bytesReceived, L1_Timeout timeout);



#endif /* __L1_hub_data_api_h__ */
