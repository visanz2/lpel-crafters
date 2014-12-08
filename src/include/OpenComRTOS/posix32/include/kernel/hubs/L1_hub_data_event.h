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

#ifndef __L1_hub_data_event_h__
#define __L1_hub_data_event_h__

#include <L1_types.h>
#include <kernel/hubs/L1_hub.h>
/**
 * \internal
 * State of a DataEvent-Hub.
 */
typedef struct
{
    /**
     * Indicates whether or not the DataEvent-Hub has been signalled.
     */
    L1_BOOL isSet;
    /**
     * The size of the message on the board. Must be less or equal L1_PACKET_DATA_SIZE .
     */
    L1_UINT32 dataSize;
    /**
     * This is the message that got published.
     */
    L1_BYTE   data[L1_PACKET_DATA_SIZE];
}L1_DataEvent_HubState;

void DataEventHub_Update(L1_Hub *Hub, L1_Packet *Packet);

L1_BOOL DataEventHub_SyncCondition(L1_Hub *Hub, L1_Packet *Packet);

void DataEventHub_Ioctl(L1_Hub *Hub, L1_Packet * Packet, L1_BYTE ioctl_type);

/**
 * This macro checks whether or not a Hub is of type DataEvent
 * @returns
 *  - 0: If the Hub is not a DataEvent Hub.
 *  - 1: If the Hub is a DataEvent Hub.
 */
#define L1_isDataEventHub(h) ((h)->HubType == L1_DATAEVENT)


#endif /* __L1_hub_data_event_h__ */
