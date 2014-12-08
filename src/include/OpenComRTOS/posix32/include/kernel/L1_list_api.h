/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2008
 * www.Altreonic.com
 * Module name: ($Path/$Filename)
 * Synopsis: efines the aplication programmers interface to the list.
 *
 * $LastChangedDate: 2014-01-10 09:33:15 +0100 (Fri, 10 Jan 2014) $
 * $Revision: 4148 $
 * $LastChangedBy: marina.gutierrez $
 *******************************************************************************/

#ifndef __L1_list_api_h__
#define __L1_list_api_h__

#include <L1_types.h>
typedef struct _struct_L1_ListElement_ L1_ListElement;

/* according to L1_ Architecture document, need 2 types of lists; priority ordered and non-priority? */
struct _struct_L1_ListElement_ {
    L1_ListElement *Prev;
    L1_ListElement *Next;
    L1_Priority Priority;
};


typedef struct _struct_L1_List_ {
    L1_ListElement SentinelElement; /* HeadElement */
} L1_List;

/* TODO: Write API Doc */

/**
 * This function returns the head element of the list and removes it from the list.
 *
 * @param List List from which the head element will be returned and removed.
 *
 * @return L1_ListElement Element at the head of the list.
 */
extern L1_ListElement *L1_List_getHeadElement(L1_List *List); /* detachHeadElement, pop */

/**
 * This function tests if an element is found in a list.
 *
 * @param List List to be tested for the presence of the element.
 * @param ListElement Element to be tested.
 */
extern L1_BOOL L1_List_isMember (const L1_List *List, const L1_ListElement *ListElement);

/**
 * This function inserts an element into the list right before the first element with lower priority *, i.e. in fifo order
 *
 * @param List List to which the element will be inserted.
 * @param ListElement Element to be inserted in the list.
 */
extern void L1_List_insert(L1_List *List, L1_ListElement *ListElement); /* insert into priority ordered list */

/**
 * This function removes an element into the list right before the first element with lower priority *, i.e. in fifo order
 *
 * @param ListElement Element to be inserted in the list.
 */
extern void L1_List_remove(L1_ListElement *ListElement);


#define LIST_API_DEFINES
#ifdef LIST_API_DEFINES

	/**
	 *
	 * This macro receives a list and returns the head element of the list without modifying the list.
	 *
	 * Parameters:
	 * @param List is of type L1_List, identifies the List whose head element is returned.
	 *
	 * @return List element of type L1_ListElement that is the head element of the list.
	 *
	 * @pre
	 * - List is of L1_List type
	 *
	 * \ingroup OCR_List
	 */
    //#define L1_List_HeadElement(List) ( (List)->SentinelElement.Next )

    static __inline__ L1_ListElement* L1_List_HeadElement(const L1_List* List){
        return List->SentinelElement.Next;
    }


    /**
     *
     * This macro receives a list and returns a boolean that indicates if the list is empty.
     *
     * Parameters:
     * @param List is of type L1_List, identifies the List that is tested.
     *
     * @return L1_BOOL:
     * - L1_TRUE  The list is empty.
     * - L1_FALSE The list is not empty.
     *
     * @pre
     * - List is of L1_List type
     *
     * \ingroup OCR_List
     */
    //#define L1_List_isEmpty(List) ((L1_BOOL)(NULL == (List)->SentinelElement.Next))
    static __inline__ L1_BOOL L1_List_isEmpty(const L1_List *List){
        return (L1_BOOL)(NULL == List->SentinelElement.Next);
    }

    //#define L1_List_getSentinel(List) (&((List)->SentinelElement))
    static __inline__ L1_ListElement* L1_List_getSentinel(L1_List *List){
        return &(List->SentinelElement);
    }


    //#define L1_List_isInAList(ListElement) ((L1_BOOL)(NULL != (ListElement)->Prev))
    static __inline__ L1_BOOL L1_List_isInAList(const L1_ListElement* ListElement){
        return (L1_BOOL)(NULL != ListElement->Prev); /* also caters for Sentinel */
    }

#if 0
    #define L1_List_putHeadElement(l, e)  do{\
        L1_ListElement *PreviousLE = L1_List_getSentinel( (l) );\
        (e)->Prev = PreviousLE;\
        (e)->Next = PreviousLE->Next;\
        PreviousLE->Next = (e);\
        if ( (e)->Next != NULL ) {\
            (e)->Next->Prev = (e);\
        }\
    }while(0)
#endif
    static __inline__ void L1_List_putHeadElement(L1_List *List, L1_ListElement *ListElement) {
        L1_ListElement *PreviousListElement = L1_List_getSentinel(List);
        ListElement->Prev = PreviousListElement;
        ListElement->Next = PreviousListElement->Next;
        PreviousListElement->Next = ListElement;
        if (ListElement->Next != NULL) {
            ListElement->Next->Prev = ListElement;
        }
    }


#else /* LIST_DEFINES */
    L1_ListElement* L1_List_HeadElement(const L1_List* List);

    L1_BOOL L1_List_isEmpty(const L1_List *List);

    L1_ListElement* L1_List_getSentinel(L1_List *List);
    L1_BOOL L1_List_isInAList(const L1_ListElement* ListElement);

    extern void L1_List_putHeadElement(L1_List *List, L1_ListElement *ListElement);


#endif /* LIST_API_DEFINES */


#if 0
/* MISRA 19.4: C macros shall only expand to a braced initialiser, a constant, a parenthesised expression, a type qualifier, a storage class specifier, or a do-while-zero construct. */
#define L1_List_setHeadElement(l,h)  do { \
                                      (l)->SentinelElement.Next = (h); \
                                      if ((h) != NULL) { \
                                        (h)->Prev = &((l)->SentinelElement); \
                                      } \
                                    } while (0)
#endif

#if 0
void L1_List_setHeadElement(L1_List* List, L1_ListElement* NewHeadElement);
#endif /* 0 */


#endif /* __L1_list_api_h__ */
