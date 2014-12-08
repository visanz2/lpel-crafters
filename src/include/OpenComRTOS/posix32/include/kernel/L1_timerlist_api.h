/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2008
 * www.Altreonic.com
 * Module name: ($Path/$Filename)
 * Synopsis: Timerlist API
 *
 * $LastChangedDate: 2010-10-06 17:52:49 +0200 (Wed, 06 Oct 2010) $
 * $Revision: 1916 $
 * $LastChangedBy: bernhard.sputh $
 *******************************************************************************/

#ifndef __L1_timerlist_api_h__
#define __L1_timerlist_api_h__


typedef struct _struct_L1_TimerListElement_ L1_TimerListElement;

/**
 * This structure represents an element of the TimerList, which can be
 * sorted according to a timeout value.
 */
struct _struct_L1_TimerListElement_ {
	/** Pointer to the previous element in the list.*/
    L1_TimerListElement *Prev;
	/** Pointer to the next element in the list.*/
    L1_TimerListElement *Next;
    /** The timeout value of this TimerListElement.*/
    L1_Timeout Timeout;
    /** The ID of this timeout, this is used to determine whether or not an early timeout occurred.*/
    L1_UINT32 Id;
};

/**
 * This is represents the complete TimerList.
 */
typedef struct _struct_L1_TimerList_ {
	/** The sentinel element is the anchor of the list. Its Next pointer points
	 * to the first entry of the list. Its Prev pointer must point to NULL.
	 */
    L1_TimerListElement SentinelElement;
} L1_TimerList;

/**
 * This represents an entry of a L1_TimerList
 */
typedef struct _struct_L1_Timer_ {
    /** Linkage element for the list */
    L1_TimerListElement TimerListElement;
    /** Pointer to the packet that contains this L1_TimerTimeout structure */
    //L1_Packet *Packet;
    void * Packet;
}L1_TimerTimeout;

/**
 * This function inserts a NewTimerListElement in to a TimerList. It inserts
 * element into the TimerList right after the first element with a lower
 * timeout, i.e. in fifo order.
 *
 * Thus if the list contains entries with the timeouts 5ms and 10ms, and a new
 * element should be added with a timeout of 7ms, this new element will be
 * inserted between the 5ms and 10ms timeout elements.
 *
 * @param TimerList is a pointer to the L1_TimerList where the new element should be added to.
 * @param NewTimerListElement is a pointer to the L1_TimerListElement that should be added to the list.
 *
 */
void L1_TimerList_insert( L1_TimerList *TimerList,
                          L1_TimerListElement *NewTimerListElement);

/**
 * Removes a L1_TimerListElement from a TimerList. First the timeout value of
 * the element gets adjusted before the element gets removed from the list.
 *
 * @param TimerListElement the L1_TimerListElement to remove from the
 * TimerList it is associated with.
 */
void L1_TimerList_remove(L1_TimerListElement *TimerListElement);


/**
 * This function removes the first element from the List and returns it.
 *
 * @param List pointer to the L1_TimerList from which to remove the head element.
 *
 * @return Pointer to the removed L1_TimerListElement that was the head element.
 * If there is no head element the function returns NULL.
 */
L1_TimerListElement* L1_TimerList_getHeadElement(L1_TimerList* List);

/**
 * This function set the HeadElement of List to ListElement.
 *
 * @param List pointer to the L1_TimerList where to set the head element to ListElement.
 * @param ListElement pointer to the L1_TimerListElement to set as head element in the List.
 *
 */
void L1_TimerList_putHeadElement(L1_TimerList* List, L1_TimerListElement* ListElement);


/**
 * Determines the head element of List and returns it. The head element is not removed from the List.
 *
 * @param List pointer to the L1_TimerList from which to return a pointer to the head element from.
 *
 * @return A pointer of the L1_TimerListElement which is the current head element of the List.
 */
L1_TimerListElement* L1_TimerList_HeadElement(const L1_TimerList* List);

/**
 * Checks whether or not List contains any elements.
 *
 * @param List pointer to the L1_TimerList which should be checked for emptiness.
 *
 * @return L1_BOOL
 * - L1_TRUE if the List is empty.
 * - L1_FALSE if the List contains at least one element.
 */
L1_BOOL L1_TimerList_isEmpty(const L1_TimerList* List);

/**
 * Returns a pointer to the sentinel element (Anchor) of the List.
 *
 * @param List pointer to the L1_TimerList to return the sentiel element from.
 *
 * @return Pointer to a L1_TimerListElement which represents the sentinel of the List.
 */
L1_TimerListElement* L1_TimerList_getSentinel(L1_TimerList *List);

#if 0
void L1_TimerList_setHeadElement(L1_TimerList* List, L1_TimerListElement* ListElement);
#endif /* 0 */

/**
 * This function determines whether or not ListElement is part of List.
 *
 * @param List pointer to a L1_TimerList which should be checked for the containment of ListElement.
 * @param ListElement pointer to a L1_TimerListElement for which its membership in the List should be determined.
 *
 * @return L1_BOOL:
 * - L1_TRUE ListElement is member of List.
 * - L1_FALSE ListElement is not a member of List.
 */
L1_BOOL L1_TimerList_isMember(const L1_TimerList* List, const L1_TimerListElement *ListElement);
#endif /* __L1_timerlist_api_h__ */

