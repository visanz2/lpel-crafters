/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2008
 * www.Altreonic.com
 * Module name: L1_hub_semaphore.h ($Path/$Filename)
 * Synopsis: Semaphore-Hub API
 *
 * $LastChangedDate: 2014-03-26 10:16:05 +0100 (Wed, 26 Mar 2014) $
 * $Revision: 4216 $
 * $LastChangedBy: antonio.ramos $
 *******************************************************************************/

#ifndef L1_HUB_SEMAPHORE_API_H_
#define L1_HUB_SEMAPHORE_API_H_

#include <L1_types.h>
#include <kernel/hubs/L1_hub.h>

/**
\defgroup OCR_Semaphore_Hub Semaphore Hub
L1_Semaphore is a data structure representing a Semaphore, which is a specific instantiation of a L1_Hub.
The Semaphore Hub, has the following properties, see also the section \ref OCR_Hub :

  - State:
    - L1_UINT16 Count

  - Synchronisation Predicate upon L1_SignalSemaphore_{W,WT,NW}:
    - Predicate: True, i.e. always succeeds (assuming Count < MaxInt).
    - Action: Count := Count + 1

  - Synchronisation Predicate upon L1_TestSemaphore_{W,WT,NW}:
    - Predicate: Count > 0
    - Action: Count := Count -1
    - Note: when a predicate holds, the other predicate also has to be (re)evaluated. This evaluation and synchronization can be combined in the implementation.

  - Invariant(s):
    - Put waiting list is empty.
    - count <> 0 implies length (Get waiting list) = 0

  - Notes: Because the Predicate always holds when signaling a semaphore, no data can be transferred via the PutPacket.

\section OCR_Semaphore_Hub_Example Example
This example demonstrates the Tasks synchronization mechanism via the Semaphore Hub, by implementing a so called Semaphore-loop. In the Semaphore-loop Task1 signals Seamaphore Sema1, while Task2 waits for Sema1 to be signalled. Upon being signalled Task2 signals Sema2 for which Task1 waits to become signalled. Then the whole thing repeats.

\subsection OCR_Semaphore_Hub_Example_Entities Entities
  - Task1: Task1EntryPoint, shown in section \ref OCR_Semaphore_Hub_Example_Task1
  - Task1: Task2EntryPoint, shown in section \ref OCR_Semaphore_Hub_Example_Task2
  - Sema1: Semaphore Hub
  - Sema2: Semaphore Hub
  - StdioHostServer1: Stdio Host Server used to print messages onto the screen.

\section OCR_Semaphore_Hub_Example_Task1 Source Code of Task1EntryPoint
\code
#include <L1_api.h>
#include "L1_node_config.h"
#include <StdioHostService/StdioHostClient.h>

void Task1EntryPoint(L1_TaskArguments Arguments)
{
    while(1)
    {
        Shs_putString_W(StdioHostServer1, "Task 1 signals Sema 1\n");
        if(RC_OK != L1_SignalSemaphore_W(Sema1))
        {
            Shs_putString_W(StdioHostServer1, "Not Ok\n");
        }

        Shs_putString_W(StdioHostServer1, "Task 1 tests Sema 2\n");
        if(RC_OK != L1_TestSemaphore_W(Sema2))
        {
            Shs_putString_W(StdioHostServer1, "Not Ok\n");
        }
    }
}
\endcode

\section OCR_Semaphore_Hub_Example_Task2 Source Code of Task2EntryPoint
\code
#include <L1_api.h>
#include <L1_node_config.h>
#include <StdioHostService/StdioHostClient.h>

void Task2EntryPoint(L1_TaskArguments Arguments)
{
    while(1)
    {
        Shs_putString_W(StdioHostServer1, "Task 2 tests Sema 1\n");
        if(RC_OK != L1_TestSemaphore_W(Sema1))
        {
            Shs_putString_W(StdioHostServer1, "Not Ok\n");
        }
        Shs_putString_W(StdioHostServer1, "Task 2 signals Sema 2\n");
        if(RC_OK != L1_SignalSemaphore_W(Sema2))
        {
            Shs_putString_W(StdioHostServer1, "Not Ok\n");
        }
    }
}
\endcode

*/

/**
 *
 * Signals a semaphore, i.e. increases the semaphore count.
 * This call waits until it could increment the Semaphore count.
 *
 * Parameters:
 * @param HubID the L1_HubID which identifies the Semaphore, that the calling Task wants to signal
 *
 * @return L1_Status:
 * - RC_OK  service successful (the semaphore count was incremented)
 * - RC_FAIL    service failed (the semaphore count was not incremented)
 *
 * @pre
 * - None
 *
 * @post
 * - Semaphore count incremented
 * - Calling tasks ready
 *
 * \ingroup OCR_Semaphore_Hub
 */
static __inline__ L1_Status L1_SignalSemaphore_W(L1_HubID HubID)
{
    return L1_buildAndInsertPacket((HubID), (L1_CurrentTaskCR->RequestPacket), (L1_UINT16)(L1_SID_SEND_TO_HUB | (L1_SEMAPHORE << 8)), L1_INFINITE_TIMEOUT);
}



/**
 * Tests whether or not a Semaphore is ready, i.e. the semaphore count is larger than zero.
 * This service waits until it could decrement the semaphore count.
 *
 *
 * @param HubID identifies the Semaphore-Hub, that the calling Task wants to test.
 *
 * @return L1_Status
 * - RC_OK  The service call was successful (the semaphore count was >1 and decremented)
 * - RC_FAIL The service call failed.
 *
 * @pre
 * - None
 *
 * @post
 * - Semaphore count is 0 or decremented by one.
 * - Calling tasks ready
 *
 * \ingroup OCR_Semaphore_Hub
 *
 */
static __inline__ L1_Status L1_TestSemaphore_W(L1_HubID HubID)
{
    return L1_buildAndInsertPacket((HubID), (L1_CurrentTaskCR->RequestPacket), (L1_UINT16)(L1_SID_RECEIVE_FROM_HUB | (L1_SEMAPHORE << 8)), L1_INFINITE_TIMEOUT);
}



/**
 *
 * Signals a semaphore, i.e. increases the semaphore count.
 * This service waits until it either could increment the semaphore count or the timout expired.
 *
 * Parameters:
 * @param HubID is the L1_HubID which identifies the Semaphore, that the calling Task wants to signal
 * @param timeout the number of system ticks the call should wait for synchronisation.
 *
 * @return L1_Status:
 * - RC_OK service successful (the semaphore count was incremented)
 * - RC_FAIL service failed (the semaphore count was not incremented)
 * - RC_TO service timed out.
 *
 * @pre
 * - None
 *
 * @post
 * - Semaphore count incremented
 * - Calling tasks ready
 *
 * \ingroup OCR_Semaphore_Hub
 */
static __inline__ L1_Status L1_SignalSemaphore_WT(L1_HubID HubID, L1_Timeout timeout)
{
    return L1_buildAndInsertPacket((HubID), (L1_CurrentTaskCR->RequestPacket), (L1_UINT16)(L1_SID_SEND_TO_HUB | (L1_SEMAPHORE << 8)), (timeout));
}



/**
 * Tests whether or not a Semaphore is ready, i.e. the semaphore count is larger than zero.
 * This service waits until it either could decrement the semaphore or the timeout expired.
 *
 * @param HubID is of type L1_HubID and identifies the Semaphore, that the calling Task wants to test.
 * @param timeout the number of system ticks the call should wait for synchronisation.
 *
 * @return L1_Status, the following return values are possible:
 * - RC_OK service successful (there was a set Event)
 * - RC_FAIL service failed (there was no set Event)
 * - RC_TO service timed out.
 *
 * @pre
 * - None
 *
 * @post
 * - Semaphore count is 0 or decremented by one.
 * - Calling tasks ready
 *
 * \ingroup OCR_Semaphore_Hub
 */
static __inline__ L1_Status L1_TestSemaphore_WT(L1_HubID HubID, L1_Timeout timeout)
{
    return L1_buildAndInsertPacket((HubID), (L1_CurrentTaskCR->RequestPacket), (L1_UINT16)(L1_SID_RECEIVE_FROM_HUB | (L1_SEMAPHORE << 8)), (timeout));
}



/**
 *
 * Signals a semaphore, i.e. increases the semaphore count.
 * This call returns immediately.
 *
 * Parameters:
 * @param HubID is the L1_HubID which identifies the Semaphore, that the calling Task wants to signal
 *
 * @return L1_Status:
 * - RC_OK  service successful (the semaphore count was incremented)
 * - RC_FAIL    service failed (the semaphore count was not incremented)
 *
 * @pre
 * - None
 *
 * @post
 * - Semaphore count incremented
 * - Calling tasks ready
 *
 * \ingroup OCR_Semaphore_Hub
 */
static __inline__ L1_Status L1_SignalSemaphore_NW(L1_HubID HubID)
{
    return L1_buildAndInsertPacket((HubID), (L1_CurrentTaskCR->RequestPacket), (L1_UINT16)(L1_SID_SEND_TO_HUB | (L1_SEMAPHORE << 8)), 0);
}



/**
 * Tests whether or not a Semaphore is ready, i.e. the semaphore count is larger than zero.
 * This service returns immediately, even if it could not decrement the semaphore counter.
 *
 *
 * @param HubID identifies the Semaphore, that the calling Task wants to test.
 *
 * @return L1_Status
 * - RC_OK  The service call was successful (the semaphore count was >1 and decremented)
 * - RC_FAIL The service call failed.
 *
 * @pre
 * - None
 *
 * @post
 * - Semaphore count is 0 or decremented by one.
 * - Calling tasks ready
 *
 * \ingroup OCR_Semaphore_Hub
 */
static __inline__ L1_Status L1_TestSemaphore_NW(L1_HubID HubID)
{
    return L1_buildAndInsertPacket((HubID), (L1_CurrentTaskCR->RequestPacket), (L1_UINT16)(L1_SID_RECEIVE_FROM_HUB | (L1_SEMAPHORE << 8)), 0);
}



#ifdef ASYNC_SERVICES
/**
 * Tests whether or not a Semaphore is ready, i.e. the semaphore count is larger than zero.
 * The completion is deferred until a corresponding L1_WaitForPacket call happens.
 *
 * @param HubID is of type L1_HubID and identifies the Event, that the calling Task wants to test.
 * @param packet is a pointer to the L1_Packet that should wait for the Event-Hub to become raised.
 *
 * @return L1_Status, the following return values are possible:
 * - RC_OK  service successful
 * - RC_FAIL    service failed
 *
 * @pre
 * - Packet is a preallocated L1_Packet, initialised using L1_initialiseAsyncPacket().
 *
 * @post
 * - Header fields of preallocated Packet filled in
 * - Data of Put Packet will have been filled in
 *
 * \warning This interaction must not be used with Semaphore-Hubs that are not local to the Node the calling Task is located at.
 *
 * @sa L1_initialiseAsyncPacket
 * \ingroup OCR_Semaphore_Hub
 * \ingroup OCR_ISR_API
 *
 */

static __inline__ L1_Status L1_TestSemaphore_A(L1_HubID HubID, L1_Packet * packet)
{
    return L1_buildAndInsertPacket((HubID), (packet), (L1_UINT16)(L1_SID_RECEIVE_FROM_HUB | (L1_SEMAPHORE << 8)), L1_ASYNC);
}



#endif /* ASYNC_SERVICES */


#endif /* L1_HUB_SEMAPHORE_H_ */
