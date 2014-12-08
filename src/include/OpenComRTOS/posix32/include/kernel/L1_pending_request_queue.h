/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2013
 * www.Altreonic.com
 * Module name: ($Path/$Filename)
 * Synopsis: This file contains the code for the K
 *
 * $LastChangedDate: 2014-02-27 18:01:59 +0100 (Thu, 27 Feb 2014) $
 * $Revision: 4196 $
 * $LastChangedBy: marina.gutierrez $
 *******************************************************************************/

#ifndef L1_PENDING_REQUESTS_QUEUE_H_
#define L1_PENDING_REQUESTS_QUEUE_H_

#include<kernel/L1_list_api.h>
#include<kernel/L1_packet_api.h>

#ifdef PENDING_REQUESTS_QUEUE

/**
 * \internal
 * \defgroup OCR_PEND_REQ_QUEUE Pending Request Queue
 *
 * Pending Request Queue,  is a priority ordered list which contains all the
 * Packets that have to be processed after there are new packets in the
 * Kernel Packet Pool.
 */

/**
 * \internal \ingroup OCR_PEND_REQ_QUEUE
 * The list of requests.
 */
extern L1_List L1_PendingRequestsQueue;

/**
 * \internal \ingroup OCR_PEND_REQ_QUEUE
 * Determines whether or not the Pending Request Queue (DRQ) is empty or not.
 *
 * @returns L1_BOOL
 * - L1_TRUE: The DRQ is empty
 * - L1_FALSE: There are requests waiting on the DRQ.
 */
#define L1_PendingRequestsQueue_isEmpty() L1_List_isEmpty( &L1_PendingRequestsQueue )

/**
 * \internal \ingroup OCR_PEND_REQ_QUEUE
 * Adds a given Packet to the Pending Request Queue (DRQ).
 *
 * @param request Pointer to the request-packet that should be added to the Queue.
 * @param handler The function to call when the request can be handled.
 *
 * @returns L1_Status
 *  - RC_OK: if the request-packet could be added to the queue
 *  - RC_FAIL: otherwise
 */
extern L1_Status L1_PendingRequestsQueue_addRequest(L1_Packet * request, L1_PendingRequestHandler handler);

/**
 * \internal \ingroup OCR_PEND_REQ_QUEUE
 * Removes a previously added Packet from the Pending Request Queue (DRQ).
 *
 * This function is called to deal with the situation that a previously Pending request
 * has been resolved already. Thus this request can be removed from the DRQ
 *
 * @param pRequest Pointer to the request-packet that should be removed from the queue
 * @returns L1_Status
 *  - RC_OK: if the request-packet could be removed from the queue.
 *  - RC_FAIL: otherwise
 */
static __inline__ L1_Status L1_PendingRequestsQueue_removeRequest(L1_Packet * pRequest)
{
    if(L1_TRUE == L1_List_isInAList(&( pRequest->PendingRequestListElement)))
    {
        pRequest->PendingRequestHandler = NULL;
        L1_List_remove( &(pRequest->PendingRequestListElement) );
        return RC_OK;
    }
    return RC_FAIL;
}


/**
 * \internal \ingroup OCR_PEND_REQ_QUEUE
 * This function is called to deal with the situation that a previously Pending request
 * has been resolved already. Thus this request can be removed from the DRQ.
 *
 * @param pRequest pointer to the L1_Packet that represents the request.
 *
 */
static __inline__ void L1_PendingRequestsQueue_cancelRequest(L1_Packet * pRequest)
{
    L1_PendingRequestsQueue_removeRequest(pRequest);
}




/**
 * \internal \ingroup OCR_PEND_REQ_QUEUE
 * Removes the head element of the Pending Request Queue (DRQ) and returns it.
 * If the DRQ is empty then NULL will be returned.
 *
 * @returns L1_Packet*
 * - NULL: The DRQ is empty
 * - !NULL: Pointer the request-packet that was at the front of the queue.
 */
extern L1_Packet* L1_PendingRequestsQueue_getRequest(void);

#endif /* PENDING_REQUESTS_QUEUE */

#endif /* L1_PENDING_REQUESTS_QUEUE_H_ */

