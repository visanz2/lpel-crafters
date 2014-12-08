/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2008
 * www.Altreonic.com
 * Module name: ($Path/$Filename)
 * Synopsis: Internal kernel API
 *
 * $LastChangedDate: 2013-10-22 11:07:28 +0200 (Tue, 22 Oct 2013) $
 * $Revision: 4086 $
 * $LastChangedBy: bernhard.sputh $
 *******************************************************************************/

#ifndef __L1_kernel_api_h__
#define __L1_kernel_api_h__

#include<kernel/L1_packet_api.h>

/**
 * \internal
 * This function represents the Kernel-Task. It performs packet-switching on incoming L1_Packets routing them either to
 * a local Hub, a local Task, or another Node for processing. If there are no L1_Packets to process, it deschedules.
 */
extern void L1_KernelLoop(void);

/**
 * \internal
 * This function returns an L1_Packet to the Task that owns it. If the Task is currently not ready to be run, it will
 * be added to the Ready-List. If the Packet is from a remote Node this function will route it to the correct Link-Driver.
 * @param Packet Pointer to the L1_Packet to return to its Task.
 */
extern void L1_returnToTask(L1_Packet *Packet);
#ifdef MP

/**
 * \internal
 * This service gets triggered when a Remote Node returns an L1_Packet to the local node. This service then takes care
 * to return the Packet to the correct Task and make it ready if necessary.
 * @param Packet Pointer to the L1_Packet to return to its Task.
 */
extern void L1_returnPacketService(L1_Packet *Packet);
#endif /* MP */

/**
 * \internal
 * This function starts the task that has the destination ID of the Packet. If the task is inactive,
 * it initializes the task context and sets its state to L1_STARTED. The task is made ready and the
 * kernel is instructed to return to task.
 *
 * @param Packet The task that has the id of the destination ID field of this packet
 * will be started.
 *
 * \ingroup x
 */
extern void L1_startTaskService(L1_Packet *Packet);

/**
 * \internal
 * This function stops the task that has the destination ID of the Packet. If the task is ready,
 * it removes the task from the ready list. Otherwise it removes the task's packet from any waiting
 * list and the suspended field is set to false to be able to start the task again.
 * A task that is stopped is set to the L1_INACTIVE state.
 *
 * @param Packet The task that has the id of the destination ID field of this packet
 * will be stopped
 *
 * \ingroup x
 */
extern void L1_stopTaskService(L1_Packet *Packet);

/**
 * \internal
 * This function suspends the task that has the destination ID of the Packet.
 *
 * @param Packet The task that has the id of the destination ID field of this packet
 * will be suspended.
 *
 * \ingroup x
 */
extern void L1_suspendTaskService(L1_Packet *Packet);

/**
 * \internal
 * This function resumes the task that has the destination ID of the Packet.
 * A task that is in the suspended state will be resumed.
 *
 * @param Packet The task that has the id of the destination ID field of this packet
 * will be resumed.
 *
 * \ingroup x
 */
extern void L1_resumeTaskService(L1_Packet *Packet);


/**
 * \internal
 * This function inserts the L1_Packet, identified by the parameter Packet, into the Timer-List. j
 *
 * @param Packet Pointer to the L1_Packet which should be inserted into the Timer-List.
 * @return L1_Status
 * - RC_OK If the Packet could be inserted into the Timer-List.
 * - RC_FAIL If the Packet could not be inserted into the Timer-List.
 */
extern L1_Status L1_setTimer (L1_Packet *Packet);


/**
 * \internal
 * Cancels the timeout for the L1_Packet, identified by the parameter waitingPacket.
 * @param waitingPacket Pointer to the L1_Packet for which to cancel the timeout.
 */
extern void L1_resetTimer (L1_Packet *waitingPacket);

/**
 * \internal
 * This service handles any incoming timer related tasks. It either suspends or wakes up a Task, depending on the
 * requested Service in field Packet->ServiceID.
 *
 * @param Packet Pointer to the L1_Packet which contains the request.
 */
extern void L1_timerPacketService (L1_Packet *Packet);


#if defined(MP) || defined(ASYNC_SERVICES)

/* called by remoteservice, returntotask with a Task Input Port */
/**
 * \internal
 * Performs the synchronisation of the L1_Packets in a Task-Input-Port.
 * @param Port Pointer to the Input-Port to synchronise.
 * @param Packet Pointer to the L1_Packet to process.
 */
extern void inputPortService(L1_InputPort *Port, L1_Packet *Packet);

/**
 * \internal
 * This service gets invoked by the Kernel if a Task is waiting for an L1_Packet to be placed in it's Input-Port.
 * This function only returns once there is an L1_Packet in the input Port of the Task identified by
 * Packet->DestinationPortID, or the Timeout expired.
 *
 * @param Packet Pointer to the L1_Packet to be processed.
 *
 * @post Packet->Data[0-4] contain the pointer to the L1_Packet that was inserted into the Input-Port of the Task.
 */
extern void L1_anyPacketService(L1_Packet *Packet);
#endif /* MP || ASYNC_SERVICES */

/**
 * \internal
 * Invokes the general Hub-Service of the Hub identified in the L1_Packet (Packet->DestinationPortID). This performs the
 * Hub synchronisation operation.
 * @param Packet Pointer to the L1_Packet to be processed.
 */
extern void L1_genericHubService(L1_Packet *Packet); /* L1_Packet? */

/**
 * \internal
 * Invokes the IOCTL callback of the Hub addressed in the L1_Packet(Packet->DestinationPortID), identified in Packet.
 * @param Packet Pointer to the L1_Packet to be processed.
 */
extern void L1_genericHubControl(L1_Packet *Packet); /* L1_Packet? */


#ifdef MP
#ifdef L1_PRIO_INHERITANCE

/**
 * \internal
 * Routes the L1_Packet, identified by the parameter Packet, to the corresponding Driver-Task.
 * @param Packet Pointer to the L1_Packet to be routed to the corresponding Driver-Task.
 *
 * @warning If the Driver-Task is inactive the Packet gets discarded.
 */
extern void L1_remoteService (L1_Packet *Packet);

/**
 * \internal
 * This function gets called when a Task-Priority-Boost-Packet has arrived, on the node that holds the Task to have its
 * Priority boosted. This function takes care of all necessary priority boosting operations, including boosting the
 * priority of the Request-Packet.
 *
 * @param Packet Pointer to the Task-Priority-Boost-Packet to be processed.
 */
extern void L1_changePriorityService (L1_Packet *Packet);

/**
 * \internal
 * This function gets called when a Packet-Priority-Boost-Packet has arrived, on the node that holds the Request-Packet
 * of a Task  which currently gets it's priority boosted.
 *
 * @param Packet Pointer to the Packet-Priority-Boost-Packet to be processed.
 */
extern void L1_changePacketPriorityService(L1_Packet *Packet);

#endif /* L1_PRIO_INHERITANCE */
#endif /* MP */

/**
 * \internal
 * Configures the L1_Packet identified by the parameter Packet, with values of the PortID, ServiceID, and Timeout.
 * The packet is then inserted into the Kernel-Input-Port and a context switch gets performed to the Kernel-Task to
 * process the Packet.
 *
 * @param PortID The ID of the Port the Packet should be sent to.
 * @param Packet Pointer to the Packet to send.
 * @param ServiceID The Service ID of the Packet, must be a value defined in L1_ServiceID.
 * @param Timeout The amount of ticks the Packet should wait for the Interaction to take place.
 * @return The function returns the return value of the interaction:
 * - RC_OK The interaction was successful.
 * - RC_FAIL The interaction failed.
 * - RC_TO The timeout expired.
 */
extern L1_Status L1_buildAndInsertPacket(L1_PortID PortID, L1_Packet *Packet,
                                         L1_UINT16 ServiceID,
                                         L1_Timeout Timeout);

#ifdef L1_PRIO_INHERITANCE
/**
 * \internal
 * This function changes the priority of the Task identified by TaskCR to the value of newPriority. If the Task is
 * currently on the Ready-List it will be reinserted into it to ensure that the new priority is reflected.
 * @param TaskCR Pointer to the Task Control Record of the Task to adjust the priority of.
 * @param newPriority The new priority the Task should have.
 */
extern void L1_changeTaskPriority (L1_TaskControlRecord *TaskCR, L1_Priority newPriority);
#endif /* L1_PRIO_INHERITANCE */

/**
 * \internal
 * Makes the Task identified by the parameter TaskCR ready. This means that it adds the TaskCR to the Ready-List.
 * @param TaskCR Pointer to the Task Control Record of the Task which should be made ready.
 *
 * @pre
 * - TaskCR must belong to a local Task.
 * - TaskCR must not be on the Ready-List
 *
 * @post
 * - TaskCR is on the Ready-List.
 */
extern void L1_makeTaskReady(L1_TaskControlRecord *TaskCR);




#ifdef MP
/**
 * \internal
 * Allocates a Packet from the KernelPacketPool and returns a pointer it.
 *
 * @returns L1_Packet*
 * - NULL indicates that no packet could be allocated
 * - !NULL is the pointer to the L1_Packet that was allocated from the KernelPacketPool.
 *
 */
L1_Packet* L1_KernelPacketPool_getPacket(void);
#endif /* MP */

#endif /* __L1_kernel_api_h__ */
