/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2013
 * www.Altreonic.com
 * Module name: L1_hub_event_api.h ($Path/$Filename)
 * Synopsis: API for the Event-Hub.
 *
 * $LastChangedDate: 2010-11-05 10:52:18 +0100 (Fri, 05 Nov 2010) $
 * $Revision: 2037 $
 * $LastChangedBy: bernhard.sputh $
 *******************************************************************************/


#ifndef L1_HUB_DATA_EVENT_API_H_
#define L1_HUB_DATA_EVENT_API_H_

#include <L1_types.h>
#include <kernel/hubs/L1_hub.h>
#include <kernel/L1_kernel_data.h>

/**
 * \defgroup OCR_DataEvent_Hub DataEvent-Hub
 * The DataEvent-Hub is a crossover between am Event-Hub and a Port-Hub. It's
 * usage scenario is to efficiently transfer information about state changes
 * from a Sender-Task to a Receiver-Task. For this purpose the Hub allows the
 * Sender-Task to post data together with raising and Event. Upon a data post,
 * the Hub will wake up the first Task on it's waiting list and pass the data
 * to it as well. If there is currently no Task on the waiting list, the Hub
 * will store the data in an internal buffer and remember that data was posted
 * to it. Upon a Task reading the data the Hub will forget the previously
 * pending data. Thus the Hub performs an auto-reset.
 */



/**
 * \ingroup OCR_DataEvent_Hub
 *
 * This interaction posts data to the DataEvent-Hub id. If the DataEvent-Hub previously contained data already then this will be overwritten, as it has been succeeded by the new data. This interaction always returns directly.
 *
 * @param id ID of the DataEvent-Hub to which to post the data.
 * @param data Pointer to the buffer which contains the data to be posted.
 * @param length Number of bytes that are in the buffer pointed to by data. The maximum number of bytes that can be posted is L1_PACKET_DATA_SIZE.
 *
 * @return RC_OK The data could be posted.
 * @return RC_FAIL Otherwise.
 */
static __inline__ L1_Status L1_PostDataToDataEvent_W(L1_HubID id, L1_BYTE * data, L1_UINT32 length)
{
    return L1_PutDataToHub(id, L1_CurrentTaskCR->RequestPacket, L1_DATAEVENT, data, length, L1_INFINITE_TIMEOUT);
}

/**
 * \ingroup OCR_DataEvent_Hub
 *
 * This interaction posts data to the DataEvent-Hub id. If the DataEvent-Hub previously contained data already then this will be overwritten, as it has been succeeded by the new data. This interaction always returns directly.
 *
 * @param id ID of the DataEvent-Hub to which to post the data.
 * @param data Pointer to the buffer which contains the data to be posted.
 * @param length Number of bytes that are in the buffer pointed to by data. The maximum number of bytes that can be posted is L1_PACKET_DATA_SIZE.
 *
 * @return RC_OK The data could be posted.
 * @return RC_FAIL Otherwise.
 */
static __inline__ L1_Status L1_PostDataToDataEvent_NW(L1_HubID id, L1_BYTE * data, L1_UINT32 length)
{
    return L1_PutDataToHub(id, L1_CurrentTaskCR->RequestPacket, L1_DATAEVENT, data, length, 0);
}

/**
 * \ingroup OCR_DataEvent_Hub
 *
 * This interaction posts data to the DataEvent-Hub id. If the DataEvent-Hub previously contained data already then this will be overwritten, as it has been succeeded by the new data. This interaction always returns directly.
 *
 * @param id ID of the DataEvent-Hub to which to post the data.
 * @param data Pointer to the buffer which contains the data to be posted.
 * @param length Number of bytes that are in the buffer pointed to by data. The maximum number of bytes that can be posted is L1_PACKET_DATA_SIZE.
 * @param timeout The number of ms the interaction should wait for the interaction to succeed before timing out.
 *
 * @return RC_OK The data could be posted.
 * @return RC_TO
 * @return RC_FAIL Otherwise.
 */
static __inline__ L1_Status L1_PostDataToDataEvent_WT(L1_HubID id, L1_BYTE * data, L1_UINT32 length, L1_Timeout timeout)
{
    return L1_PutDataToHub(id, L1_CurrentTaskCR->RequestPacket, L1_DATAEVENT, data, length, timeout);
}


/**
 * \ingroup OCR_DataEvent_Hub
 * This interaction tries to read data from a DataEvent-Hub. If the DataEvent-Hub is currently holding data the interaction will return directly, otherwise it will wait until another Task posts data to the Hub.
 *
 * @param id ID of the DataEvent-Hub from which to read data.
 * @param data Pointer to the buffer which should contain the data that was read from the DataEvent-Hub.
 * @param length The size of the buffer pointed to by data in Bytes. It must be equal or larger than the data posted to the DataEvent-Hub, otherwise the interaction will fail with RC_FAIL.
 * @param pNbrOfReadBytes Pointer to a variable of type L1_UINT32 which will contain the number of Bytes that were actually read from the DataEvent-Hub.
 *
 * @return RC_OK The data could be read.
 * @return RC_FAIL The data could not be read. One cause of this is a too small buffer.
 */
static __inline__ L1_Status L1_ReadDataFromDataEvent_W(L1_HubID id, L1_BYTE * data, L1_UINT32 length, L1_UINT32 * pNbrOfReadBytes)
{
    return L1_GetDataFromHub(id, L1_CurrentTaskCR->RequestPacket, L1_DATAEVENT, data, length, pNbrOfReadBytes, L1_INFINITE_TIMEOUT);
}

/**
 * \ingroup OCR_DataEvent_Hub
 * This interaction tries to read data from a DataEvent-Hub. This interaction always returns directly.
 *
 * @param id ID of the DataEvent-Hub from which to read data.
 * @param data Pointer to the buffer which should contain the data that was read from the DataEvent-Hub.
 * @param length The size of the buffer pointed to by data in Bytes. It must be equal or larger than the data posted to the DataEvent-Hub, otherwise the interaction will fail with RC_FAIL.
 * @param pNbrOfReadBytes Pointer to a variable of type L1_UINT32 which will contain the number of Bytes that were actually read from the DataEvent-Hub.
 *
 * @return RC_OK The data could be read.
 * @return RC_FAIL The data could not be read. One cause of this is a too small buffer.
 */
static __inline__ L1_Status L1_ReadDataFromDataEvent_NW(L1_HubID id, L1_BYTE * data, L1_UINT32 length, L1_UINT32 * pNbrOfReadBytes)
{
    return L1_GetDataFromHub(id, L1_CurrentTaskCR->RequestPacket, L1_DATAEVENT, data, length, pNbrOfReadBytes, 0);
}

/**
 * \ingroup OCR_DataEvent_Hub
 * This interaction tries to read data from a DataEvent-Hub. If the DataEvent-Hub is currently holding data the interaction will return directly, otherwise it will wait until either another Task posts data to the Hub, or the timeout expires.
 *
 * @param id ID of the DataEvent-Hub from which to read data.
 * @param data Pointer to the buffer which should contain the data that was read from the DataEvent-Hub.
 * @param length The size of the buffer pointed to by data in Bytes. It must be equal or larger than the data posted to the DataEvent-Hub, otherwise the interaction will fail with RC_FAIL.
 * @param pNbrOfReadBytes Pointer to a variable of type L1_UINT32 which will contain the number of Bytes that were actually read from the DataEvent-Hub.
 *
 * @return RC_OK The data could be read.
 * @return RC_TO The timeout expired.
 * @return RC_FAIL The data could not be read. One cause of this is a too small buffer.
 */
static __inline__ L1_Status L1_ReadDataFromDataEvent_WT(L1_HubID id, L1_BYTE * data, L1_UINT32 length, L1_UINT32 * pNbrOfReadBytes, L1_Timeout timeout)
{
    return L1_GetDataFromHub(id, L1_CurrentTaskCR->RequestPacket, L1_DATAEVENT, data, length, pNbrOfReadBytes, timeout);
}

/**
 * \ingroup OCR_DataEvent_Hub
 * This interaction clears the content of a DataEvent-Hub. This means the Hub forgets that data has been posted to it previously.
 * @param id ID of the DataEvent-Hub to clear.
 * @return RC_OK The DataEvent-Hub could be cleared.
 * @return RC_FAIL Otherwise.
 */
static __inline__ L1_Status L1_ClearDataEvent_NW(L1_HubID id)
{
    return L1_buildAndInsertPacket(id, L1_CurrentTaskCR->RequestPacket, ((L1_IOCTL_HUB_OPEN << 8) | L1_SID_IOCTL_HUB), 0);
}

#endif /* L1_HUB_DATA_EVENT_API_H_ */
