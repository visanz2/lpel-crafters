/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2008
 * www.Altreonic.com
 * Module name: ($Path/$Filename) 
 * Synopsis: Interface of the Keylist.
 * 
 * $LastChangedDate: 2014-01-10 09:33:15 +0100 (Fri, 10 Jan 2014) $
 * $Revision: 4148 $
 * $LastChangedBy: marina.gutierrez $
 *******************************************************************************/

#ifndef __L1_keylist_api_h__
#define __L1_keylist_api_h__

/**
 * \internal
 * \defgroup OCR_KeyList Key List
 */

/**
 * \internal
 * \ingroup OCR_KeyList
 * The key that is used to identify elements of the L1_KeyedList.
 */
typedef L1_UINT32 L1_Key;

/**
 * \internal
 * \ingroup OCR_KeyList
 * The Elements that get stored inside the L1_KeyedList.
 */
typedef struct _struct_L1_KeyedListElement_ {
    /**
     * The double linked list element.
     */
    L1_ListElement ListElement;
    /**
     * The which identifies the list element.
     */
    L1_Key Key;
} L1_KeyedListElement;

/**
 * \internal
 * \ingroup OCR_KeyList
 * The KeyedList uses a standard priority ordered L1_List internally.
 */
typedef L1_List L1_KeyedList;

/**
 * \internal
 * \ingroup OCR_KeyList
 * This function removes the first (head) element from the list l and returns it.
 * @param l Pointer to the list from which to detach the head element.
 * @return Pointer to the head element of the list l, which has now been removed from the list. If the list was empty NULL will be returned.
 * @sa L1_KeyedList_HeadElement
 */
static __inline__ L1_KeyedListElement * L1_KeyedList_getHeadElement(L1_List * l)
{
    return (L1_KeyedListElement *) L1_List_getHeadElement( l );
}


/**
 * \internal
 * \ingroup OCR_KeyList
 * This function inserts the KeyedListElement e as the first element (head) into the list l.
 * @param l Pointer to the list where the KeyedListElement e should be inserted as head element.
 * @param e Pointer to the KeyedListElement to insert as head element of the list l.
 * @warning This operation does not ensure that the list stays priority ordered.
 */
static __inline__ void L1_KeyedList_putHeadElement(L1_List * l, L1_KeyedListElement * e)
{
    L1_List_putHeadElement ( l, (L1_ListElement*)e );
}


/**
 * \internal
 * \ingroup OCR_KeyList
 * This function inserts the KeyedListElement e into the priority ordered list l.
 * @param l Pointer to the list into which to insert the KeyedListElement e.
 * @param e Pointer to the KeyedListElement to insert.
 */
static __inline__ void  L1_KeyedList_insert(L1_List * l, L1_KeyedListElement * e)
{
    L1_List_insert ( l, (L1_ListElement*)e );
}
/**
 * \internal
 * \ingroup OCR_KeyList
 * Removes the KeyedListElement e from any list it is member of.
 * @param e Pointer to the KeyedListElement which should be removed from the list it is member of.
 *
 * @pre ListElement e is in a KeyedList, and is not the Sentinel.
 * @post e->Prev and e->Next = NULL
 */
static __inline__ void L1_KeyedList_remove(L1_KeyedListElement * e)
{
    L1_List_remove ((L1_ListElement *) (e));
}

/**
 * \internal
 * \ingroup OCR_KeyList
 * Returns the first element in the KeyedList l. It does not remove the element from the KeyedList.
 * @param l Pointer to the KeyedList from which to retrieve the first element.
 * @return Pointer to the first element of the KeyedList l, or NULL if the KeyedList is empty.
 */
static __inline__ L1_KeyedListElement * L1_KeyedList_HeadElement(const L1_KeyedList * l)
{
    return (L1_KeyedListElement *) L1_List_HeadElement ((L1_List *)(l));
}
/**
 * \internal
 * \ingroup OCR_KeyList
 * Determines whether or not the KeyedList is empty.
 * @param l Pointer to the KeyedList for which to determine whether or not it is empty.
 * @return L1_TRUE If the KeyedList l is empty.
 * @return L1_FALSE If the KeyedList l is not empty.
 */
static __inline__ L1_BOOL L1_KeyedList_isEmpty(L1_KeyedList * l)
{
    return L1_List_isEmpty ((L1_List *)l);
}
/**
 * \internal
 * \ingroup OCR_KeyList
 * Returns the sentinel element of the KeyedList l;
 * @param l Pointer to the KeyedList from which to return the sentinel element.
 * @return Pointer to the sentinel element of the KeyedList l.
 */
static __inline__ L1_KeyedListElement * L1_KeyedList_getSentinel(L1_KeyedList * l)
{
    return (L1_KeyedListElement*) L1_List_getSentinel ((L1_List *)l);
}



/**
 * \internal
 * Checks whether the L1_KeyedListElement e is in a KeyedList.
 * @param e Pointer to the L1_KeyedListElement for which to check whether or not it is in a List.
 * @return L1_TRUE Element e is in a list.
 * @return L1_FALSE Element e is not in a list.
 * \ingroup OCR_KeyList
 */
static __inline__ L1_BOOL L1_KeyedList_isInAList(L1_KeyedListElement * e)
{
    return L1_List_isInAList ( (L1_ListElement *)e );
}


/**
 * \internal
 * This function initializes each elements of L1_KeyListElements (one for each resource) to point to the next element.
 *
 * \ingroup OCR_KeyList
 */
extern void L1_initFreeKeyList(void);

/**
 * \internal
 * This function gets the head element of a list, sets its key and priority to the given values, and
 * inserts it back into the list.
 *
 * @param List List from which the element is inserted.
 * @param Key Key value that is associated to the element added to the list.
 * @param Priority Priority associated to the element added to the list.
 *
 * @return L1_Status
 * - RC_OK The element was inserted into the key list.
 * - RC_FAIL Insert operation failed.
 *
 * \ingroup OCR_KeyList
 */
extern L1_Status L1_KeyedList_insertKeyWithPriority(L1_KeyedList *List, L1_Key Key, L1_Priority Priority);

/**
 * \internal
 * This function finds the provided key in the list. If the key is found,
 * the element is removed from the list.
 *
 * @param List List to which the element will be removed.
 * @param Key Key value that will be removed from the list if it is found.
 *
 * @return L1_Status
 * - RC_OK The element with the specified key was removed successfully.
 * - RC_FAIL Remove operation failed.
 *
 * \ingroup OCR_KeyList
 */
extern L1_Status L1_KeyedList_removeKey(L1_KeyedList *List, L1_Key Key);

/**
 * \internal
 * This function tries to locate the element with Key in the List List.
 * @param List Pointer to an L1_KeyedList in which to find an element with the key Key.
 * @param Key The key of the element to find.
 * @returns L1_KeyedListElement
 * - NULL: If no element of with the key Key exists in the list.
 * - !NULL: The pointer to the element with key Key.
 *
 * \ingroup OCR_KeyList
 */
extern L1_KeyedListElement *L1_KeyedList_findKey (const L1_KeyedList *List, const L1_Key Key);

/**
 * \internal
 * This function updates the priority of the element with the L1_Key Key.
 * @param List Pointer to the L1_KeyedList where the Element with Key should be given the newPriority.
 * @param Key The key of the Element to update.
 * @param newPriority The priority to assign to the element with the key Key.
 * @return L1_Status:
 *  - RC_OK if the operation was completed successfully.
 *  - RC_FAIL if there was no element with Key in List.
 *
 * \ingroup OCR_KeyList
 */
extern L1_Status L1_KeyedList_changeKeyPriority(L1_KeyedList *List, L1_Key Key, L1_Priority newPriority);

#endif /* __L1_keylist_api_h__ */
