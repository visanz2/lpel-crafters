/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2008
 * www.Altreonic.com
 * Module name: L1_hub_semaphore.h ($Path/$Filename)
 * Synopsis: Semaphore Hub data structures
 *
 * $LastChangedDate: 2014-01-10 09:33:15 +0100 (Fri, 10 Jan 2014) $
 * $Revision: 4148 $
 * $LastChangedBy: marina.gutierrez $
 *******************************************************************************/


#ifndef L1_HUB_SEMAPHORE_H_
#define L1_HUB_SEMAPHORE_H_

#include <L1_types.h>
/**
 * \internal \ingroup OCR_Semaphore_Hub
 *
 * State of a Semaphore-Hub.
 */
typedef struct _struct_L1_SemaphoreState_ {
        /**
         * How often the Semaphore-Hub has been signaled.
         */
        L1_UINT16 Count;
} L1_Semaphore_HubState;


/**
 * \internal \ingroup OCR_Semaphore_Hub
 * Checks whether or not the given data structure represents a Semaphore-Hub.
 * @param pHub Pointer to the data structure, of type L1_Hub, which should be checked whether or not it represents a Semaphore-Hub.
 * @return L1_TRUE If the data structure represents a Semaphore-Hub.
 * @return L1_FALSE Otherwise.
 */
static __inline__ L1_BOOL L1_isSemaphoreHub(L1_Hub * pHub)
{
    return (L1_BOOL)((pHub)->HubType == L1_SEMAPHORE);
}

/**
 * \internal \ingroup OCR_Semaphore_Hub
 * Determines if the count of an L1_Semaphore_HubState is higher than zero (semaphore set).
 *
 * @param pHub Pointer to a Hub data structure of a Semaphore-Hub.
 *
 * @return L1_TRUE If the Semaphore-Hub is set.
 * @return L1_FALSE Otherwise.
 */
//#define L1_isHubSemaphoreSet(h) (((L1_Semaphore_HubState*)(h)->HubState)->Count > 0)

static __inline__ L1_BOOL L1_isHubSemaphoreSet(L1_Hub * pHub)
{
    return (L1_BOOL)(((L1_Semaphore_HubState*)(pHub)->HubState)->Count > 0);
}

/**
 * \internal \ingroup OCR_Semaphore_Hub
 * This function updates the state of a Semaphore Hub, depending on the type of packet received.
 * Put packets signal the semaphore. Get packets test the semaphore.
 * @param Hub Event hub that is updated.
 * @param Packet Put or get packet received by the hub.
 *
 * @pre
 *  - Hub is of L1_Hub type.
 */
extern void SemaphoreUpdate(L1_Hub * Hub, L1_Packet * Packet);

/**
 * \internal \ingroup OCR_Semaphore_Hub
 * This function evaluates if the update function should be executed, depending on the type of packet received.
 * For put packets, the semaphore sync condition is always true.
 * For get packets, the semaphore sync condition is true if the count is larger than zero.
 * @param Hub Semahpore hub that is tested for synchronization.
 * @param Packet Put or get packet received by the hub.
 *
 * @return L1_BOOL
 *  - L1_TRUE  Update condition is true (update function should be called).
 *  - L1_FALSE Update condition is false (update function should not be called).
 *
 * @pre
 *  - Hub is of L1_Hub type.
 *  - empty waiting list, as complimentary packets already accounted for?
 */
extern L1_BOOL SemaphoreSyncCondition(L1_Hub * Hub, L1_Packet * Packet);

#endif /* L1_HUB_SEMAPHORE_H_1 */
