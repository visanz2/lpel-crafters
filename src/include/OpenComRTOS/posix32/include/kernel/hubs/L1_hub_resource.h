/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2008
 * www.Altreonic.com
 * Module name: L1_hub_resource.h ($Path/$Filename)
 * Synopsis: Resource Hub data structures
 *
 * $LastChangedDate: 2014-01-10 09:33:15 +0100 (Fri, 10 Jan 2014) $
 * $Revision: 4148 $
 * $LastChangedBy: marina.gutierrez $
 *******************************************************************************/


#ifndef L1_HUB_RESOURCE_H_
#define L1_HUB_RESOURCE_H_

/**
 * \internal \ingroup OCR_Resource_Hub
 * State of a Resource-Hub.
 */
typedef struct _struct_L1_ResourceState_ {
    /**
     * Identifies whether or not the Resource is currently locked or not.
     */
    L1_BOOL Locked;
    /**
     * If the Resource is locked, i.e. Locked==L1_TRUE, then this field contains the ID of the Task that owns this Resrource.
     */
    L1_TaskID OwningTaskID;
#ifdef L1_PRIO_INHERITANCE
    /**
     * Defines the maximum Priority to which the Task owning this Resource may be boosted. This field is unused in OpenComRTOS 1.4
     */
    L1_Priority CeilingPriority;
    /**
     * The Priority to which the Task owning this Resource has been boosted to already. It is used to avoid repeated boosting of the Priority in cases where a Task has already been boosted to a higher Priority.
     * The maximum priority this field may contain is the value given in the field CeilingPriority.
     */
    L1_Priority OwnerBoostedToPriority;
#endif /* L1_PRIO_INHERITANCE */
} L1_Resource_HubState;

/**
 * \internal \ingroup OCR_Resource_Hub
 * Checks whether or not the given data structure represents a Resource-Hub.
 * @param pHub Pointer to the data structure, of type L1_Hub, which should be checked whether or not it represents a Resource-Hub.
 * @return L1_TRUE If the data structure represents a Resource-Hub.
 * @return L1_FALSE Otherwise.
 */
static __inline__ L1_BOOL L1_isResourceHub(L1_Hub * pHub)
{
    return (L1_BOOL)((pHub)->HubType == L1_RESOURCE);
}

/**
 * \internal \ingroup OCR_Resource_Hub
 * Determines whether the Resource-Hub identified by pHub is locked.
 *
 * @param pHub Pointer to the Hub data structure of a Resource-Hub.
 * @return L1_TRUE If the FIFO is locked.
 * @return L1_FALSE If the FIFO is unlocked.
 */
static __inline__ L1_BOOL L1_isHubResourceLocked(L1_Hub * pHub)
{
    return  ((L1_Resource_HubState*)(pHub)->HubState)->Locked;
}



/**
 * \internal \ingroup OCR_Resource_Hub
 * This function updates the state of the resource when required.
 * When a request to lock a resource is received, it sets the resource to locked, and it sets the owner to the task that locked the resource.
 * When a request to unlock the resource is received, the resource is unlocked.
 *
 * @param Hub ID of the resource hub.
 * @param Packet Packet used for the update operation.
 *
 *
 */
extern void ResourceUpdate(L1_Hub * Hub, L1_Packet * Packet);

/**
 * \internal \ingroup OCR_Resource_Hub
 * This function returns true when synchronization is achieved. For a lock resource request, it returns true if the resource is unlocked.
 * If the resource was previously locked, the function returns false and RC_FAIL in the status of the packet recieved.
 * For an unlock resource request, it returns true if the resource was previously locked and the task unlocking it is the same than the one that set the lock.
 * Otherwise it returns false and RC_FAIL in the status of the packet received.
 *
 * @param Hub ID of the resource hub.
 * @param Packet Packet used for the synchronization operation.
 *
 *
 */
extern L1_BOOL ResourceSyncCondition(L1_Hub * Hub, L1_Packet * Packet);

#endif /* L1_HUB_RESOURCE_H_ */
