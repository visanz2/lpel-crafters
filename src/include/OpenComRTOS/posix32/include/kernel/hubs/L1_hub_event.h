/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2008
 * www.Altreonic.com
 * Module name: L1_hub_event.h ($Path/$Filename)
 * Synopsis: Event Hub data structures.
 *
 * $LastChangedDate: 2014-01-10 09:33:15 +0100 (Fri, 10 Jan 2014) $
 * $Revision: 4148 $
 * $LastChangedBy: marina.gutierrez $
 *******************************************************************************/

#ifndef L1_HUB_EVENT_H_
#define L1_HUB_EVENT_H_

#include <L1_types.h>

/**
 * \internal \ingroup OCR_Event_Hub
 * The state of an Event-Hub.
 */
typedef struct _struct_L1_EventState_ {
        /**
         * Indicates whether or not the Event-Hub is signaled.
         */
        L1_BOOL isSet;
} L1_Event_HubState;

/**
 * \internal \ingroup OCR_Event_Hub
 * Checks whether or not the given data structure represents a Event-Hub.
 * @param pHub Pointer to the data structure, of type L1_Hub, which should be checked whether or not it represents a Event-Hub.
 * @return L1_TRUE if the data structure represents a Event-Hub.
 * @return L1_FALSE otherwise.
 */
static __inline__ L1_BOOL L1_isEventHub(L1_Hub * pHub)
{
    return (L1_BOOL)((pHub)->HubType == L1_EVENT);
}




/**
 * \internal  \ingroup OCR_Event_Hub
 * This function determines whether or not the Event-Hub identified by the argument pHub is set.
 * @param pHub Pointer to a variable of type L1_Hub of an Event-Hub.
 * @warning pHub must not be a NULL-Pointer, this function does not check this.
 * @return L1_TRUE if the Event-Hub is set.
 * @return L1_FALSE if the Event-Hub is not set.
 */
static __inline__ L1_BOOL L1_isHubEventSet(L1_Hub * pHub)
{
	return (((L1_Event_HubState*)(pHub)->HubState)->isSet);
}

/**
 * \internal  \ingroup OCR_Event_Hub
 * This macro casts the HubState void pointer to a pointer to L1_Event_HubState.
 *
 * @param h Pointer to a type of type L1_EVENT.
 */
#define L1_Event_State(h) ((L1_Event_HubState*)(h)->HubState)

/**
 * \internal  \ingroup OCR_Event_Hub
 * This function updates the state of an Event Hub, depending on the type of packet received.
 * Send packets raise the event. Receive packets test the event.
 * @param Hub Event hub that is updated.
 * @param Packet Send or receive packet received by the hub.
 *
 * @pre
 *  - Hub is of L1_Hub type.
 */
extern void EventUpdate(L1_Hub *Hub, L1_Packet *Packet);

/**
 * \internal  \ingroup OCR_Event_Hub
 * This function evaluates if the update function should be executed, depending on the type of packet received.
 * For send packets, the event sync condition is true if the event state is not set. If the event is set, the update condition is false.
 * For receive packets, the event sync condition is true if the event state is set. If the event is not set, the update condition is false.
 * @param Hub Event hub that is tested for synchronization.
 * @param Packet Send or receive packet received by the hub.
 *
 * @return L1_BOOL
 *  - L1_TRUE  Update condition is true (update function should be called).
 *  - L1_FALSE Update condition is false (update function should not be called).
 *
 * @pre
 *  - Hub is of L1_Hub type.
 *  - empty waiting list, as complimentary packets already accounted for?
 */
extern L1_BOOL EventSyncCondition(L1_Hub *Hub, L1_Packet *Packet);


#endif /* L1_HUB_EVENT_H_ */
