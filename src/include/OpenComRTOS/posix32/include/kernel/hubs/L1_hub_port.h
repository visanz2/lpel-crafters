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

#ifndef __L1_hub_port_h__
#define __L1_hub_port_h__

#include <L1_types.h>
#include <kernel/hubs/L1_hub.h>

/**
 * \internal \ingroup OCR_Port_Hub
 *
 */


#ifdef L1_DEBUG
/**
 * \internal \ingroup OCR_Port_Hub
 * This function performs a port update operation.
 *
 * @param Hub ID which identifies the port hub to be updated.
 * @param Packet Put or Get packet that updates the port.
 *
 * @pre
 * - None
 *
 * @post
 * - None
 *
 */
extern void LocalPortUpdate (L1_Hub *Hub, L1_Packet *Packet);
#endif /* L1_DEBUG */


/**
 * \internal \ingroup OCR_Port_Hub
 * This function returns L1_TRUE when synchronisation happens in a Port Hub.
 *
 * @param Hub Pointer to the L1_Hub structure of the Port Hub to check..
 * @param Packet Pointer to the L1_Packet received at the Port Hub.
 *
 * @return L1_BOOL:
 * - L1_FALSE  Synchronisation occurred.
 * - L1_TRUE   Synchronisation did not occur.
 *
 * @pre
 * - empty waiting list.
 *
 * @post
 * - None
 */
extern L1_BOOL LocalPortSyncCondition(L1_Hub *Hub, L1_Packet *Packet);

/**
 * \internal \ingroup OCR_Port_Hub
 * Checks whether or not the given data structure represents a Port-Hub.
 * @param pHub Pointer to the data structure, of type L1_Hub, which should be checked whether or not it represents a Port-Hub.
 * @return L1_TRUE if the data structure represents a BlackBoard-Hub.
 * @return L1_FALSE otherwise.
 */
static __inline__ L1_BOOL L1_isLocalPortHub(L1_Hub * pHub)
{
	return (L1_BOOL)((pHub)->HubType == L1_PORT);
}

#endif /* __L1_hub_port_h__ */
