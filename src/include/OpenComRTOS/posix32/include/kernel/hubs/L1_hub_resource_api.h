/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2008
 * www.Altreonic.com
 * Module name: L1_hub_resource_api.h ($Path/$Filename)
 * Synopsis: Resource Hub API.
 *
 * $LastChangedDate: 2014-03-26 10:16:05 +0100 (Wed, 26 Mar 2014) $
 * $Revision: 4216 $
 * $LastChangedBy: antonio.ramos $
 *******************************************************************************/

#ifndef L1_HUB_RESOURCE_API_H_
#define L1_HUB_RESOURCE_API_H_

#include <L1_types.h>
#include <kernel/hubs/L1_hub.h>


/**
\defgroup OCR_Resource_Hub Resource Hub
The Semaphore Hub, has the following properties, see also the section \ref OCR_Hub.
L1_Resource is a data structure representing a logical Resource, which is a specific instantiation of a L1_Hub.

  - State:
    - L1_Bool: Locked
    - L1_TaskID: OwningTask
    - L1_Priority: CeilingPriority

  - Synchronisation Predicate upon L1_LockResource_{W,WT,NW}:
    - Precondition: Current Task != OwningTask
    - Predicate: not Locked:
      - Action: (Locked := TRUE), OwningTask := Packet->RequestingTaskID
    - Predicate: Locked:
      - Action: (Locked := TRUE), insert Request Packet in waiting list, apply priority inheritance if priority (OwningTask) > priority (Requesting Task)

  - Synchronisation Predicate upon L1_UnlockResource_{W,WT,NW}
    - Precondition: Packet->RequestingTaskID == OwningTask
    - Predicate: Locked AND OwningTask == Packet->RequestingTaskID
    - Action: Locked := FALSE, OwningTask :=  None, apply LockResource Action on next waiting Task in waiting list.

  - Invariant(s):
    - Locked = False implies length (get waiting list) = 0

  - Notes:
    - Locked attribute may be redundant in the implementation.
    - It is an application design error if the Synchronization Predicate is not valid for the get waiting list (A task should only Unlock when it has Locked the resource)
    - A task must not request to lock a resource it already has locked.
    - When a predicate holds, the other predicate also has to be (re)evaluated. This evaluation and synchronization can be combined in the implementation.

\section OCR_Resource_Hub_Example Example

This examples illustrates how a Resource Hub can be used to guard access to a shared resource, in this case a Stdio Host Server. It consists of two tasks: Task1 and Task2, which both count from 0 to 19 and print out the counting messages onto the console using the Stdio Host Server StdioHostServer1.

\subsection OCR_Resource_Hub_Example_Entities Entities
  - Task1: Task1EntryPoint, shown in section \ref OCR_Resource_Hub_Example_Task1
  - Task1: Task2EntryPoint, shown in section \ref OCR_Resource_Hub_Example_Task2
  - StdioHostServer1: A Stdio Host Server component which provides acess to the console.
  - StdioHostServer1Res: A Resource Hub to ensure that a second task does not interfere with console access.
\section OCR_Resource_Hub_Example_Task1 Source Code of Task1EntryPoint
\code
#include <L1_api.h>
#include <L1_node_config.h>
#include <StdioHostService/StdioHostClient.h>

void Task1EntryPoint(L1_TaskArguments Arguments)
{
    L1_UINT32 i = 0;
        for(i = 0; i < 20; i++)
        {
                L1_LockResource_W(StdioHostServer1Res);
                Shs_putString_W(StdioHostServer1, "Task 1 outputs: 0x");
                Shs_putInt_W(StdioHostServer1, i, 'x');
                Shs_putChar_W(StdioHostServer1, '\n');
                L1_UnlockResource_W(StdioHostServer1Res);
       }
}
\endcode

\section OCR_Resource_Hub_Example_Task2 Source Code of Task2EntryPoint
\code
#include <L1_api.h>
#include <L1_node_config.h>
#include <StdioHostService/StdioHostClient.h>

void Task2EntryPoint(L1_TaskArguments Arguments)
{
    L1_UINT32 i = 0;
        for(i = 0; i < 20; i++)
        {
                L1_LockResource_W(StdioHostServer1Res);
                Shs_putString_W(StdioHostServer1, "Task 2 outputs: 0x");
                Shs_putInt_W(StdioHostServer1, i, 'x');
                Shs_putChar_W(StdioHostServer1, '\n');
                L1_UnlockResource_W(StdioHostServer1Res);
       }
}
\endcode
*/

/**
 * Locks a logical Resource. This service waits until it could lock the logical Resource.
 *
 * @param HubID identifies the Resource-Hub, that the calling Task wants to lock.
 *
 * @return L1_Status
 * RC_OK    service successful (the resource was acquired and locked)
 * RC_FAIL  service failed (the resource was not acquired)
 *
 * @pre
 * - None
 *
 * @post
 * - Calling task ready
 *
 * \ingroup OCR_Resource_Hub
 */
static __inline__ L1_Status L1_LockResource_W(L1_HubID HubID)
{
    return L1_buildAndInsertPacket((L1_PortID)(HubID), (L1_CurrentTaskCR->RequestPacket), (L1_UINT16) (L1_SID_RECEIVE_FROM_HUB | (L1_RESOURCE << 8)), (L1_Timeout)L1_INFINITE_TIMEOUT);
}



/**
 * Unlocks a logical Resource.
 * This service waits until is could unlock the resource!
 *
 * @param HubID identifies the Resource-Hub, that the calling Task wants to unlock
 *
 * @return L1_Status
 * - RC_OK service successful (the resource was released)
 * - RC_FAIL service failed (the resource could not be unlocked)
 *
 * @pre
 * - None
 *
 * @post
 *  - Calling task ready
 *
 * \ingroup OCR_Resource_Hub
 */
static __inline__ L1_Status L1_UnlockResource_W(L1_HubID HubID)
{
    return L1_buildAndInsertPacket((HubID), (L1_CurrentTaskCR->RequestPacket), (L1_UINT16)(L1_SID_SEND_TO_HUB | (L1_RESOURCE << 8)), L1_INFINITE_TIMEOUT);
}



/**
 * Locks a logical Resource.
 * This service waits until it either could lock the resource or the timeout expired.
 *
 * @param HubID identifies the Resource-Hub, that the calling Task wants to lock
 * @param timeout the number of system ticks the call should wait for synchronisation.
 *
 * @return L1_Status
 * - RC_OK service successful (the resource was acquired and locked)
 * - RC_FAIL service failed (the resource was not acquired)
 * - RC_TO service timed out.
 *
 * @pre
 * - None
 *
 * @post
 * - Calling task ready
 *
 * \ingroup OCR_Resource_Hub
 */
static __inline__ L1_Status L1_LockResource_WT(L1_HubID HubID, L1_Timeout timeout)
{
    return L1_buildAndInsertPacket((HubID), (L1_CurrentTaskCR->RequestPacket), (L1_UINT16)(L1_SID_RECEIVE_FROM_HUB | (L1_RESOURCE << 8)), (timeout));
}



/**
 * Unlocks a logical Resource.
 * This service waits until is could either unlock the resource, or the timeout expired.
 *
 * @param HubID identifies the Resource-Hub, that the calling Task wants to unlock
 * @param timeout the number of system ticks the call should wait while trying to enqueue the packet.
 *
 * @return L1_Status
 * - RC_OK service successful (the resource was released)
 * - RC_FAIL service failed (the resource could not be unlocked)
 * - RC_TO the timeout expired.
 *
 * @pre
 * - None
 *
 * @post
 *  - Calling task ready
 *
 * \ingroup OCR_Resource_Hub
 */
static __inline__ L1_Status L1_UnlockResource_WT(L1_HubID HubID, L1_Timeout timeout)
{
    return L1_buildAndInsertPacket((HubID), (L1_CurrentTaskCR->RequestPacket), (L1_UINT16)(L1_SID_SEND_TO_HUB | (L1_RESOURCE << 8)), (timeout));
}



/**
 * Locks a logical Resource.
 * This service does return immediately, even if it could not lock the resource.
 *
 * @param HubID identifies the Resource-Hub, that the calling Task wants to lock.
 *
 * @return L1_Status
 * RC_OK    service successful (the resource was acquired and locked)
 * RC_FAIL  service failed (the resource was not acquired)
 *
 * @pre
 * - None
 *
 * @post
 * - Calling task ready
 *
 * \ingroup OCR_Resource_Hub
 */
static __inline__ L1_Status L1_LockResource_NW(L1_HubID HubID)
{
    return L1_buildAndInsertPacket((HubID), (L1_CurrentTaskCR->RequestPacket), (L1_UINT16)(L1_SID_RECEIVE_FROM_HUB | (L1_RESOURCE << 8)), 0);
}



/**
 * Unlocks a logical Resource.
 * This service returns immediately, independent whether or not it could decrement the semaphore count.
 *
 * @param HubID identifies the Resource-Hub, that the calling Task wants to unlock.
 *
 * @return L1_Status
 * - RC_OK service successful (the resource was released)
 * - RC_FAIL service failed (the resource could not be unlocked)
 *
 * @pre
 * - None
 *
 * @post
 *  - Calling task ready
 *
 * \ingroup OCR_Resource_Hub
 */
static __inline__ L1_Status L1_UnlockResource_NW(L1_HubID HubID)
{
    return L1_buildAndInsertPacket((HubID), (L1_CurrentTaskCR->RequestPacket), (L1_UINT16)(L1_SID_SEND_TO_HUB | (L1_RESOURCE << 8)), 0);
}



#ifdef ASYNC_SERVICES

#endif /* ASYNC_SERVICES */







#endif /* L1_HUB_RESOURCE_API_H_ */
