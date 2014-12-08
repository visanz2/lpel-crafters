/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2008
 * www.Altreonic.com
 * Module name: L1_hub_event_api.h ($Path/$Filename)
 * Synopsis: API for the Event-Hub
 *
 * $LastChangedDate: 2014-03-26 10:16:05 +0100 (Wed, 26 Mar 2014) $
 * $Revision: 4216 $
 * $LastChangedBy: antonio.ramos $
 *******************************************************************************/


#ifndef L1_HUB_EVENT_API_H_
#define L1_HUB_EVENT_API_H_

#include <L1_types.h>
#include <kernel/hubs/L1_hub.h>


/**
\defgroup OCR_Event_Hub Event Hub
The Event Hub, has the following properties, see also the section \ref OCR_Hub :

L1_Event is a data structure representing a logical Event, which is a specific instantiation of an L1_Hub.
  - State:
    - L1_BOOL: isSet (True or False)

  - Synchronisation Action upon L1_RaiseEvent_{W,WT,NW}:
    - Predicate: isSet == False
    - Action: isSet := True, Packet := PutPacket inserted in waiting list

  - Synchronisation Action upon L1_TestEvent_{W,WT,NW}:
    - Predicate: isSet == True
    - Action: isSet := False, GetPacket := Packet removed from waiting list

  - Invariant(s):
    - both waiting lists are empty, or only one waiting list contains waiting requests, i.e.
      - length (put waiting list) <> 0 implies length (Get waiting list) = 0
      - length (get waiting list) <> 0 implies length (Put waiting list) = 0

    - content of waiting lists are dependent on the current state, i.e.
      - isSet = True implies length (Get waiting list) = 0
      - isSet = False implies length (Put waiting list) = 0

- Notes: One example of a user defined Event could be to copy the data from the PutPacket. In this case the data must be copied into the Hub when the Event is raised. Note also that the Boolean condition can be any well formed logical expression that evaluates to true or false.

\section OCR_Event_Hub_Example Example
This example illustrates the use of the Event Hub. Task1 periodically raises the Event Event1 on which the Task2 is waiting. When the Event is raised the waiting Task2 will receive a RC_OK return value.\n\
 The program uses the L1_TestEvent_W and L1_RaiseEvent_W waiting kernel services.

\subsection OCR_Event_Hub_Example_Entities Entities
  - Task1: Task1EntryPoint, shown in section \ref OCR_Event_Hub_Example_Task1
  - Task2: Task2EntryPoint, shown in section \ref OCR_Event_Hub_Example_Task2
  - Event1: The Event Hub used to synchronise between Task1 and Task2.
  - StdioHostServer1: Stdio Host Server used to print messages onto the screen.
  - StdioHostServer1Res: Resource Lock used to prevent disruptions while printing messages onto the console using StdioHostServer1.
\section OCR_Event_Hub_Example_Task1 Source Code of Task1EntryPoint
\code
#include <L1_api.h>
#include <L1_node_config.h>
#include <StdioHostService/StdioHostClient.h>

void Task1EntryPoint(L1_TaskArguments Arguments)
{
    L1_INT32 EventCounter = 0;
    while(1)
    {
        // Here Event1 gets raised.
        if(RC_OK == L1_RaiseEvent_W(Event1))
        {
            L1_LockResource_W(StdioHostServer1Res);
            Shs_putString_W(StdioHostServer1, "Task1 raised the Event1 N \n");
            Shs_putInt_W(StdioHostServer1, EventCounter++, 'd');
            Shs_putChar_W(StdioHostServer1, '\n');
            L1_UnlockResource_W(StdioHostServer1Res);
        }
    }
}
\endcode

\section OCR_Event_Hub_Example_Task2 Source Code of Task2EntryPoint
\code
#include <L1_api.h>
#include <L1_node_config.h>
#include <StdioHostService/StdioHostClient.h>

void Task2EntryPoint(L1_TaskArguments Arguments)
{
    L1_INT32 EventCounter = 0;

    while(1)
    {
    // Here Event1 gets tested.
        if(RC_OK == L1_TestEvent_W(Event1))
        {
            L1_LockResource_W(StdioHostServer1Res);
            Shs_putString_W(StdioHostServer1, "Task2 tested Event1 N ");
            Shs_putInt_W(StdioHostServer1, EventCounter++, 'd');
            Shs_putString_W(StdioHostServer1, " - synchronization is done\n");
            L1_UnlockResource_W(StdioHostServer1Res);
        }
    }
}
\endcode
*/

/**
 *
 * This service raises an Event from False to True. If the Event is already set, wait.
 *
 * Parameters:
 * @param HubID is of type L1_HubID, identifies the Event, i.e. Hub, that the calling Task wants to raise.
 *
 * @return L1_Status:
 * - RC_OK  service successful (the Event has been raised)
 * - RC_FAIL    service failed (the Event has not been raised)
 *
 * @pre
 * - Packet is the preallocated Packet
 * - Hub is of Event type
 *
 * @post
 * - Header fields of preallocated Packet filled in
 *
 * \ingroup OCR_Event_Hub
 */
static __inline__ L1_Status L1_RaiseEvent_W(L1_HubID HubID)
{
    return L1_buildAndInsertPacket((HubID), (L1_CurrentTaskCR->RequestPacket), (L1_UINT16)(L1_SID_SEND_TO_HUB | (L1_EVENT << 8)), L1_INFINITE_TIMEOUT);
}



/**
 * This service tests an Event.
 * This call waits until the Event has been signalled.
 *
 * @param HubID is of type L1_HubID and identifies the Event, that the calling Task wants to test.
 *
 * @return L1_Status, the following return values are possible:
 * - RC_OK  service successful (there was a set Event)
 * - RC_FAIL    service failed (there was no set Event)
 *
 * @pre
 * - Packet is the preallocated Packet
 *
 * @post
 * - Header fields of preallocated Packet filled in
 *
 * \ingroup OCR_Event_Hub
 */
static __inline__ L1_Status L1_TestEvent_W(L1_HubID HubID)
{
    return L1_buildAndInsertPacket((HubID), (L1_CurrentTaskCR->RequestPacket), (L1_UINT16)(L1_SID_RECEIVE_FROM_HUB | (L1_EVENT << 8)), L1_INFINITE_TIMEOUT);
}



/**
 * This service raises an Event from False to True.
 * This call waits until either the event could be raised or the timeout expired.
 *
 * Parameters:
 * @param HubID of type L1_HubID, identifies the Event, i.e. Hub, that the calling Task wants to raise.
 * @param timeout of type L1_Timeout, the number of system ticks the call should wait for synchronisation.
 *
 * @return L1_Status:
 * - RC_OK  service successful (the Event has been raised)
 * - RC_FAIL    service failed (the Event has not been raised)
 * - RC_TO service timed out.
 *
 * @pre
 * - Packet is the preallocated Packet
 * - Hub is of Event type
 *
 * @post
 * - Header fields of preallocated Packet filled in
 *
 * \ingroup OCR_Event_Hub
 */
static __inline__ L1_Status L1_RaiseEvent_WT(L1_HubID HubID, L1_Timeout timeout)
{
    return L1_buildAndInsertPacket((HubID), (L1_CurrentTaskCR->RequestPacket), (L1_UINT16)(L1_SID_SEND_TO_HUB | (L1_EVENT << 8)), (timeout));
}



/**
 * This service tests an Event.
 * This call waits until either the Event has been signalled, or the timeout expired.
 *
 * @param HubID is of type L1_HubID and identifies the Event, that the calling Task wants to test.
 * @param timeout of type L1_Timeout, the number of system ticks the call should wait for synchronisation.
 *
 * @return L1_Status, the following return values are possible:
 * - RC_OK service successful (there was a set Event).
 * - RC_FAIL service failed (there was no set Event).
 * - RC_TO timeout expired.
 *
 * @pre
 * - Packet is the preallocated Packet
 *
 * @post
 * - Header fields of preallocated Packet filled in
 *
 * \ingroup OCR_Event_Hub
 */
static __inline__ L1_Status L1_TestEvent_WT(L1_HubID HubID, L1_Timeout timeout)
{
    return L1_buildAndInsertPacket((HubID), (L1_CurrentTaskCR->RequestPacket), (L1_UINT16)(L1_SID_RECEIVE_FROM_HUB | (L1_EVENT << 8)), (timeout));
}



/**
 * This service raises an Event from False to True.
 * This service returns immediately independent of whether or not it could raise the event.
 *
 *
 * Parameters:
 * @param HubID is of type L1_HubID, identifies the Event, i.e. Hub, that the calling Task wants to raise.
 *
 * @return L1_Status:
 * - RC_OK  service successful (the Event has been raised)
 * - RC_FAIL    service failed (the Event has not been raised)
 *
 * @pre
 * - Packet is the preallocated Packet
 * - Hub is of Event type
 *
 * @post
 * - Header fields of preallocated Packet filled in
 *
 * \ingroup OCR_Event_Hub
 */
static __inline__ L1_Status L1_RaiseEvent_NW(L1_HubID HubID)
{
    return L1_buildAndInsertPacket((HubID), (L1_CurrentTaskCR->RequestPacket), (L1_UINT16)(L1_SID_SEND_TO_HUB | (L1_EVENT << 8)), 0);
}



/**
 * This service tests an Event.
 * Returns immediately.
 *
 * @param HubID is of type L1_HubID and identifies the Event, that the calling Task wants to test.
 *
 * @return L1_Status, the following return values are possible:
 * - RC_OK  service successful (there was a set Event)
 * - RC_FAIL    service failed (there was no set Event)
 *
 * @pre
 * - Packet is the preallocated Packet
 *
 * @post
 * - Header fields of preallocated Packet filled in
 *
 * \ingroup OCR_Event_Hub
 */
static __inline__ L1_Status L1_TestEvent_NW(L1_HubID HubID)
{
    return L1_buildAndInsertPacket((HubID), (L1_CurrentTaskCR->RequestPacket), (L1_UINT16)(L1_SID_RECEIVE_FROM_HUB | (L1_EVENT << 8)), 0);
}



#ifdef ASYNC_SERVICES
/**
 * Request to test an Event-Hub without being put in the waiting state.
 * The completion is deferred until a corresponding L1_WaitForPacket call happens.
 *
 * @param HubID is of type L1_HubID and identifies the Event, that the calling Task wants to test.
 * @param packet is a pointer to the L1_Packet that should wait for the Event-Hub to become raised.
 *
 * @return L1_Status, the following return values are possible:
 * - RC_OK  service successful
 * - RC_FAIL    service failed
 *
 *
 * @pre
 * - Packet is a preallocated L1_Packet, initialised using L1_initialiseAsyncPacket().
 *
 * @post
 * - Header fields of preallocated Packet filled in
 * - Data of Put Packet will have been filled in
 *
 * \warning This interaction must not be used with Event-Hubs that are not local to the Node the calling Task is located at.
 *
 * @sa L1_initialiseAsyncPacket
 * \ingroup OCR_Event_Hub
 * \ingroup OCR_ISR_API
 *
 */
static __inline__ L1_Status L1_TestEvent_A(L1_HubID HubID, L1_Packet * packet)
{
    return L1_buildAndInsertPacket((HubID), (packet), (L1_UINT16)(L1_SID_RECEIVE_FROM_HUB | (L1_EVENT << 8)), L1_ASYNC);
}



#endif /* ASYNC_SERVICES */


#endif /* L1_HUB_EVENT_API_H_ */
