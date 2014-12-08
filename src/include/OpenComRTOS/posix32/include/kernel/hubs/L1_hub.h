/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2008
 * www.Altreonic.com
 * Module name: ($Path/$Filename)
 * Synopsis: The generic Hub definition.
 *
 * $LastChangedDate: 2012-09-12 17:18:09 +0200 (Wed, 12 Sep 2012) $
 * $Revision: 2941 $
 * $LastChangedBy: bernhard.sputh $
 *******************************************************************************/

#ifndef __L1_hub_h__
#define __L1_hub_h__

#include <kernel/L1_list_api.h>
#include <kernel/L1_packet_api.h>
/* forward declarations */
typedef struct _struct_L1_Hub_ L1_Hub;

/**
 * \internal \ingroup OCR_Hub
 *
 * This function updates the state of a Hub.
 *
 * @param Hub Pointer to the generic Hub state structure associated with this Hub.
 * @param Packet Pointer to the L1_Packet which should be used to update the Hub state.
 * @pre Empty waiting list, as complimentary packets already accounted for.
 */
typedef void (*L1_HubStateUpdateFunction)(L1_Hub * Hub, L1_Packet * Packet);

/**
 * \internal \ingroup OCR_Hub
 *
 * This function checks whether or not the Packet results in a synchronisation with the Hub taking place.
 *
 * @param Hub Pointer to the generic Hub state structure associated with this Hub.
 * @param Packet Pointer to the L1_Packet for which to determine whether a synchronisation happened or not.
 * @return L1_TRUE Synchronisation happened.
 * @return L1_FALSE Otherwise.
 *
 * @pre Empty waiting list and exactly one packet non-null
 */
typedef L1_BOOL (*L1_HubSyncConditionFunction)(L1_Hub * Hub, L1_Packet * Packet);

/**
 * \internal \ingroup OCR_Hub
 *
 * Ioctl like function, e.g. to initialize, set and get state parameters.
 * This function can also be used to implement hubs which abstract hardware devices.
 *
 * @param Hub Pointer to the generic Hub state structure associated with this Hub.
 * @param Packet Pointer to the L1_Packet which caused the function to be called. It will contain additional information.
 * @param ioctl_type Control operation to be executed (L1_IOCTL_HUB_OPEN only for this hub).
 */
typedef void (*L1_HubControlFunction)(L1_Hub * Hub, L1_Packet * Packet,
                                      L1_BYTE ioctl_type);

/**
 * \internal \ingroup OCR_Hub
 * Generic Hub State Structure.
 */
struct _struct_L1_Hub_
{
    /**
     * On this list any L1_Packet that currently does not result in a synchronisation is kept.
     */
    L1_List WaitingList;
    /**
     * The type of hub this structure belongs to. This is relevant to ensure
     * that the field HubState can be casted to the correct type.
     */
    const L1_ServiceType HubType;
    /**
     * Pointer to the Hub-Update function for this Hub. If not used this may be NULL.
     */
    const L1_HubStateUpdateFunction HubUpdateFunction; /* one for sender + receiver */
    /**
     * Pointer to the Hub-SyncCondition function for this Hub. If not used this may be NULL.
     */
    const L1_HubSyncConditionFunction HubSyncConditionFunction; /* one for sender + receiver */
    /**
     * Pointer to the Hub-Control function for this Hub. If not used this may be NULL.
     */
    const L1_HubControlFunction HubControlFunction;
    /**
     * Pointer to the Hub specific data. If not used this may be NULL.
     */
    const void * HubState;
};

#define L1_PortID2HubID(p) (p) /* PortIDs and HubIDs are the same */

#endif /* __L1_hub_h__ */
