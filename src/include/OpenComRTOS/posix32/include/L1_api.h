/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2008
 * www.Altreonic.com
 * Module name: ($Path/$Filename)
 * Synopsis: This module declares and defines functional interfaces of
 *     OpenComRTOS Layer 1 API
 *
 * $LastChangedDate: 2014-03-26 13:29:00 +0100 (Wed, 26 Mar 2014) $
 * $Revision: 4218 $
 * $LastChangedBy: bernhard.sputh $
 *******************************************************************************/

#ifndef _L1_api_h_
#define _L1_api_h_

#include <L1_types.h>
#include <kernel/L1_port_api.h>
#include <kernel/L1_packet_api.h>
#include <kernel/L1_task_api.h>
#include <kernel/L1_kernel_types.h>
#include <kernel/L1_kernel_api.h>
#include <L1_hal_asm.h>
#include <kernel/L1_timer_api.h>

#include <kernel/hubs/L1_hub_black_board_api.h>
#include <kernel/hubs/L1_hub_port_api.h>
#include <kernel/hubs/L1_hub_fifo_api.h>
#include <kernel/hubs/L1_hub_event_api.h>
#include <kernel/hubs/L1_hub_data_event_api.h>
#include <kernel/hubs/L1_hub_semaphore_api.h>
#include <kernel/hubs/L1_hub_resource_api.h>
#include <kernel/hubs/L1_hub_packet_pool_api.h>
#include <kernel/hubs/L1_hub_memory_pool_api.h>


/**
 * The L1_UINT32 value of is formatted the following way:
 * - MSByte: Major Version of the Kernel
 * - 23--16: Minor Version
 * - 15--8 : Patch-level
 * - LSByte: Release status:
 * 			- 0: Alpha
 * 			- 1: Beta
 * 			- 2: Release Candidate
 * 			- 3: Public Release
 *
 * This number is loosely associated with the OpenVE version number.
 */
#define OCR_VERSION 0x01060100  // 1.6.1 Alpha

/**
 * This service returns the Kernel version of OpenComRTOS.
 *
 * @return L1_UINT32, the value of is formatted the following way:
 * - MSByte: Major Version of the Kernel
 * - 23--16: Minor Version
 * - 15--8 : Patch-level
 * - LSByte: Release status:
 *          - 0: Alpha
 *          - 1: Beta
 *          - 2: Release Candidate
 *          - 3: Public Release
 *
 */
static __inline__  L1_UINT32 L1_GetVersion(void)
{
    return (L1_UINT32) OCR_VERSION;
}




#include<kernel/L1_hub_api.h>

/**
 * This function starts the execution of the OpenComRTOS kernel.
 *
 * @param NodeNumberOfTasks is the number of tasks on the given node.
 * @param NodeNumberOfHubs the number of Hubs on this node.
 * @return This function does not return.
 */
extern int L1_runOpenComRTOS (L1_UINT32 NodeNumberOfTasks, L1_UINT32 NodeNumberOfHubs);


/**
 * This is the pointer to the preallocated service packet of the current task.
 */
#define theServicePacket (L1_CurrentTaskCR->RequestPacket)


/**
\defgroup OCR_Hub The OpenComRTOS Hub Concept

L1_Hub is a data structure representing a generic Hub.

The architecture defines the logical view of a Hub as one that has two waiting lists: the Get Request Waiting List and the Put Request Waiting List. From the design point of view there is no need to operate with two waiting lists for all L1 services. \ref OCR_Port_Hub, \ref OCR_Event_Hub, \ref OCR_Semaphore_Hub, \ref OCR_Resource_Hub, \ref OCR_FIFO_Hub, \ref OCR_MemoryPool_Hub only have one that is used in the implementation as at any given point in time, there can either be only Get request(s), or only Put request(s) in the waiting lists or the waiting lists are empty.

Inserting or removing an element in the waiting list must be an atomic operation. This is guaranteed as only the Kernel Task performs operations on a Hub.

The Synchronization Predicate determines whether a Put or Get request synchronizes according to the State of the Hub and the content of the WaitingList(s). If synchronization can occur, the appropriate Synchronization Action is called to perform the synchronization and to update the state. These two functions are also called the Synchonisation Predicate of the Hub, and are dependent on the HubType.

The Synchronization Predicate (\ref L1_HubSyncConditionFunction) is a function that takes as arguments:
  - the Hub to retrieve the WaitingLists and the State
  - the Packet, i.e. the L1 service request, that arrives in the Hub

The Synchronization Predicate returns:
  - TRUE, if the newly arrived Packets can synchronize, The Synchronization Action is then called.
  - FALSE otherwise. The Packet will then be inserted into the WaitingList.

When synchronization occurs, the Packet is returned to the Requesting Task.
Note that upon an execution of a Synchronization Action, the Synchronization Predicate may need to be re-evaluated as the (Packet in the other) WaitingList could become enabled for synchronization.

*/


/**
 * \defgroup OCR_TaskManagement Task Management Operations
 * OpenComRTOS offers the following operations to manage Tasks.
 *
 */

/**
 * This service will start the task with TaskID and adds it to the READY list of
 * the node on which the Task resides.
 *
 * @param task the ID of the Task to be started.
 *
 * @return L1_Status:
 * - RC_OK, if the Task has started successfully.
 * - RC_FAIL, if the service failed.
 *
 * @pre
 * - Task is inactive
 * - Task is initialised and ready to start
 * - All elements of TaskControlRecord are filled in, including entry-point and
 * stack pointer.
 * - The Task cannot start itself
 *
 * @post
 * - Task is on the READY list  (case RC_OK)
 * - RC_Fail will be raised in following cases:
 *   - Task starts itself
 *   - Task is not yet initialised (i.e. not all TCR fields are filled in)
 *
 * \ingroup OCR_TaskManagement
 */
static __inline__ L1_Status L1_StartTask_W(L1_PortID task)
{
    return L1_buildAndInsertPacket((L1_PortID) (task), L1_CurrentTaskCR->RequestPacket, (L1_UINT16)(L1_SID_START_TASK), L1_INFINITE_TIMEOUT);
}



/**
 * This service will stop the task with TaskID, removes it from the READY list, removes any pending Packets on all waiting lists and restores the entry point.
 *
 * @param task the ID of the Task to be stopped.
 * @return L1_Status:
 * - RC_OK  the Task has started successfully.
 * - RC_FAIL the service failed.
 *
 * @pre
 * - Task is not stopped
 * - The Task is not the requesting task itself
 * - The Task should not lock any resource. (Task should release all resources first using a secondary entrypoint function

 * @post
 * - Task is no longer on any waiting list
 * - Entry Point restored
 * - Any data may be lost
 * - Task is in stopped state
 *
 * @note
 * Requests for the task can continue to arrive from other tasks
 * No clean up yet for pending asynchronous packets
 * The kernel task will discard any Packets with as destination a stopped Task.
 *
 * @warning This service must be used with caution. It assumes perfect knowledge
 * about the system by the invoking Task. Normally only to be used when the Task
 * is found to be misbehaving (e.g. Stack overflow, numerical exception, etc.)
 * Care should also be taken when stopping a driver task as this impacts the
 * routing functionality. Additional kernel service (messages) are used for the
 * clean-up of pending Packets in waiting list on other nodes  Except for the case
 * of two-phase services, it is sufficient to remove the (at most single waiting)
 * Packet from the appropriate waiting list (either local or remote)
 * (Waiting List of Port, Packet Pool or Kernel Input Port, or Driver Task Input Port).
 * Only for (returning of) remote services, it is possible that a Packet is
 * destined for a stopped Task.
 *
 * \ingroup OCR_TaskManagement
 *
 */
static __inline__ L1_Status L1_StopTask_W(L1_PortID task)
{
    return L1_buildAndInsertPacket((L1_PortID) (task), L1_CurrentTaskCR->RequestPacket, (L1_UINT16)(L1_SID_STOP_TASK), L1_INFINITE_TIMEOUT);
}



/**
 * This service suspends task and marks it as such in the Task Control Record.
 *
 * @param task the ID of the Task to be suspended.
 *
 * @return L1_Status:
 *  - RC_OK, the Task has been suspended successfully.
 *  - RC_FAIL, the service failed.
 *
 * @pre
 *  - The Task is not the requesting task itself
 *
 * @post
 *  - Task is marked as suspended
 *  - Requests for the task can continue to arrive from other tasks.
 *
 * @note
 * The suspend service is the fastest way to prevent a Task from executing any
 * further code. It should only be used when the application has a good reason
 * and needs to be followed by an analysis, eventually resulting in a corrective
 * action (e.g. by an operator or stopping and restarting a Task).
 *
 * Pending Packets in any waiting list remain pending, and are continued to be
 * processed e.g. synchronisation. In particular, the Task may remain and
 * inserted in the READY List. The task is however never made RUNNING. Hence,
 * the suspend state of a Task is only changing the status of the task
 * preventing it from being scheduled until the task is resumed.
 *
 *
 * \ingroup OCR_TaskManagement
 */
static __inline__ L1_Status L1_SuspendTask_W(L1_PortID task)
{
    return L1_buildAndInsertPacket((L1_PortID) (task), L1_CurrentTaskCR->RequestPacket, (L1_UINT16)(L1_SID_SUSPEND_TASK), L1_INFINITE_TIMEOUT);
}



/**
 * This service resumes the task at the point it was when suspended.
 * @param task ID of the Task to be resumed.
 *
 * @return L1_Status:
 * - RC_OK, the Task has been resumed successfully.
 * - RC_FAIL, the service failed.
 *
 * @pre
 * - Task was in suspend state
 *
 * @post
 * - Task resumed at the point it was when suspended.
 *
 * \ingroup OCR_TaskManagement
 */
static __inline__ L1_Status L1_ResumeTask_W(L1_PortID task)
{
    return L1_buildAndInsertPacket((L1_PortID) (task), L1_CurrentTaskCR->RequestPacket, (L1_UINT16)(L1_SID_RESUME_TASK), L1_INFINITE_TIMEOUT);
}



/**
 * This Kernel service is called by a Task to wait for a specified time interval.
 * @param timeout how many system ticks the task wants to wait.
 *
 * @return L1_Status:
 * - RC_TO    Service returned after Timeout.
 * - RC_FAIL  service failed.
 *
 * @pre
 * - None
 *
 * @post
 * - Calling task ready.
 *
 * \ingroup OCR_TaskManagement
 */
static __inline__ L1_Status L1_WaitTask_WT(L1_Timeout timeout)
{
    return L1_buildAndInsertPacket((L1_PortID) (L1_tcb2id (L1_CurrentTaskCR)), L1_CurrentTaskCR->RequestPacket, (L1_UINT16)(L1_SID_WAIT_TASK), (timeout) );
}



/**
 * This function allows a Task to prematurely pass execution to another Task
 * with at least the same priority than the currently active Task.
 *
 * @return RC_OK
 * @return RC_FAIL
 *
 * \ingroup OCR_TaskManagement
 */
static __inline__ L1_Status L1_Yield_W(void)
{
    if(RC_TO == L1_buildAndInsertPacket((L1_PortID) (L1_tcb2id (L1_CurrentTaskCR)), L1_CurrentTaskCR->RequestPacket, (L1_UINT16)(L1_SID_WAIT_TASK), 0))
    {
        return RC_OK;
    }
    return RC_FAIL;
}




#ifdef ASYNC_SERVICES

#ifndef API_DOC
/**
 * Resynchronises a Task with the Packet it earlier requested by
 * calling the L1_GetPacketFromPort_A service.
 *
 * Returns when the Packet is available.
 *
 * @param Packet Pointer to a pointer to an L1_Packet, the function will return the
 * L1_Packet here.
 * @param Timeout The number of ticks the function should wait for synchronisation.
 * @return RC_OK If the operation was successful.
 * @return RC_TO If the timeout expired.
 * @return RC_FAIL If the function was unable to perform the desired operation.
 */

extern L1_Status L1_WaitForPacket (L1_Packet **Packet, L1_Timeout Timeout);
#endif /* !API_DOC */

/**
 * Resynchronises a Task with the Packet it earlier requested by
 * calling the L1_GetPacketFromPort_A service.
 *
 * Returns when the Packet is available.
 *
 * @param packet is will contain the pointer to the L1_Packet that was returned to the Task.
 *
 * @return L1_Status
 * - RC_OK service completed successfully (there was a waiting Packet in the Port)/.
 * - RC_FAIL the the service failed.
 *
 * @pre
 * -This service must have been preceded by a L1_GetPacketFromPort_A or L1_PutPacketToPort_A.
 * @post
 * -The preallocated Packet must contain a pointer to a previously allocated Packet from the Packet Pool,
 * containing the result of a preceding L1_PutPacketToPort_A or L1_GetPacketFromPort_A.
 *
 * \ingroup OCR_WaitForPacket
 */
static __inline__ L1_Status L1_WaitForPacket_W(L1_Packet ** packet)
{
    return L1_WaitForPacket ((packet), L1_INFINITE_TIMEOUT);
}



/**
 * A Task calls this service to resynchronize on Packets earlier requested by calling the L1_GetPacketFromPort_A service.
 * Returns when the Packet is available or when the timeout expires.
 * @param packet is will contain the pointer to the L1_Packet that was returned to the Task.
 * @param timeout the number of system ticks the call should wait for a packet to become available.
 *
 *
 * @return L1_Status
 * - RC_OK service completed successfully (there was a waiting Packet in the Port)/.
 * - RC_FAIL the the service failed, Packet* is set to NULL.
 * - RC_TO the timeout expired, Packet* is set to NULL.
 *
 * @pre
 * -This service must have been preceded by a L1_GetPacketFromPort_A or L1_PutPacketToPort_A.
 * @post
 * -The preallocated Packet must contain a pointer to a previously allocated Packet from the Packet Pool,
 * containing the result of a preceding L1_PutPacketToPort_A or L1_GetPacketFromPort_A.
 *
 * \ingroup OCR_WaitForPacket
 */
static __inline__ L1_Status L1_WaitForPacket_WT(L1_Packet ** packet, L1_Timeout timeout)
{
    return L1_WaitForPacket ((packet), (timeout));
}



/**
 * Resynchronises a Task with the Packet it earlier requested by
 * calling the L1_GetPacketFromPort_A service.
 * Returns immediately.
 *
 * @param packet is will contain the pointer to the L1_Packet that was returned to the Task.
 *
 * @return L1_Status
 * - RC_OK service completed successfully (there was a waiting Packet in the Port)/.
 * - RC_FAIL the the service failed, Packet* is then set to NULL.
 *
 * @pre
 * -This service must have been preceded by a L1_GetPacketFromPort_A or L1_PutPacketToPort_A.
 * @post
 * -The preallocated Packet must contain a pointer to a previously allocated Packet from the Packet Pool,
 * containing the result of a preceding L1_PutPacketToPort_A or L1_GetPacketFromPort_A.
 *
 * \ingroup OCR_WaitForPacket
 */
static __inline__ L1_Status L1_WaitForPacket_NW(L1_Packet ** packet)
{
    return L1_WaitForPacket ((packet), 0);
}



/**
 * This function initalises an L1_Packet to be used for an Asynchronous interaction.
 * The following fields get initialised:
 * - RequestingTaskID: Is set to the Task ID of the currently running Task.
 * - ListElement.Next: NULL;
 * - ListElement.Prev: NULL;
 * - ListElement.Priority: Is set to the IntrinsicPriority of the currently running Task.
 * - PendingRequestHandler: NULL;
 * - PendingRequestListElement.Prev = NULL;
 * - PendingRequestListElement.Next = NULL;
 * - PendingRequestListElement.Priority: Is set to the IntrinsicPriority of the currently running Task.
 * - OwnerPool: NULL, because this packet is not part of a Packet Pool.
 * @param packet Pointer to the L1_Packet to Initialise.
 * @return RC_OK if the operation was successful
 * @return RC_FAIL if the operation was not successful.
 *
 */
L1_Status L1_initialiseAsyncPacket(L1_Packet * packet);

#endif /* ASYNC_SERVICES */


#endif /* _L1_api_h_ */

