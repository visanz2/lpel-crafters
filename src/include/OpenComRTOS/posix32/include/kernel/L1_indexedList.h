#ifndef L1_INDEXEDLIST_H_
#define L1_INDEXEDLIST_H_

#include <L1_types.h>

/**
 * @defgroup OCR_INDEXED_LIST Indexed List
 */


typedef struct L1_IndexedListElement_struct L1_IndexedListElement;

struct L1_IndexedListElement_struct{
	L1_IndexedListElement* Prev;
	L1_IndexedListElement* Next;
	L1_UINT32         	   Index;
};

typedef struct{
	L1_IndexedListElement SentinelElement;
}L1_IndexedList;



/**
 * \ingroup OCR_INDEXED_LIST
 * This function initializes the Next, Prev and Index members of the sentinel element of a list.
 *
 * @param List List to be initialized.
 *
 * @returns L1_Status Returns RC_FAIL if the List pointer is null.
 */
L1_Status L1_IndexedList_init(L1_IndexedList *List);

/**
 * \ingroup OCR_INDEXED_LIST
 * This function initializes the Next, Prev, and Index members of an element of a list.
 *
 * @param List Indexed list element to be initialized.
 *
 * @returns L1_Status Returns RC_FAIL if the List pointer is null.
 *
 */
L1_Status L1_IndexedListElement_init(L1_IndexedListElement *List);

/**
 * \ingroup OCR_INDEXED_LIST
 * This function inserts an L1_IndexedListElement into an L1_IndexedList.
 * For this purpose it determines the first free index of the list, and then
 * inserts the element at this location. The index at which the element got
 * added is returned to the caller.
 *
 * @param List List where the element will be inserted.
 * @param ListElement Element to be inserted to the list.
 * @param Index The index at which the element got added.
 *
 * @returns L1_Status Returns RC_FAIL if any of the parameters is null.
 *
 */
L1_Status L1_IndexedList_insert(L1_IndexedList *List, L1_IndexedListElement *ListElement, L1_UINT32 *Index);

/**
 * \ingroup OCR_INDEXED_LIST
 * This function removes an element from the list it is in.
 *
 * @param ListElement Element to be removed from list.
 *
 * @returns L1_Status Returns RC_FAIL if ListElement is null.
 *
 */
L1_Status L1_IndexedList_remove(L1_IndexedListElement *ListElement);

/**
 * \ingroup OCR_INDEXED_LIST
 * This function finds an element in an indexed list that matches the specified index.
 *
 * @param List List where the element will be searched in.
 * @param Index Index of the element to be found.
 *
 * @returns L1_IndexedListElement* Pointer to the element if found on the list. If not found, it returns null.
 *
 */
L1_IndexedListElement* L1_IndexedList_findElement(L1_IndexedList *List, L1_UINT32 Index);


#endif /* L1_INDEXEDLIST_H_ */
