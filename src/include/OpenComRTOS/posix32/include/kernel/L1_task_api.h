/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2008
 * www.Altreonic.com
 * Module name: ($Path/$Filename)
 * Synopsis: Task API
 *
 * $LastChangedDate: 2013-12-11 14:36:31 +0100 (Wed, 11 Dec 2013) $
 * $Revision: 4123 $
 * $LastChangedBy: marina.gutierrez $
 *******************************************************************************/

/*
 * TODO: write API doc
 */
#ifndef __L1_task_api_h__
#define __L1_task_api_h__

#include <kernel/L1_list_api.h>
#ifdef L1_PRIO_INHERITANCE
#include <kernel/L1_keylist_api.h>
#endif /* L1_PRIO_INHERITANCE */
#include <kernel/L1_packet_api.h>
#include <kernel/L1_port_api.h>

typedef enum _enum_L1_TASK_STATUS
{
  L1_INACTIVE, /* a tasks which is not started when system boots, or which has been stopped */
  L1_STARTED
  /* to add: L1_STOPPED */
} L1_TaskStatus;




/* L1_TaskControlRecord is a structure that represents a Task */
typedef struct _struct_L1_TaskControlRecord_
{
  L1_ListElement             ListElement; /* contains effective priority */
  const L1_TaskID            TaskID;
  L1_Packet*                 const RequestPacket;
  L1_TaskContext*            Context;
  L1_TaskStatus              TaskState; /* need an additional isSuspended field */
  const L1_TaskFunction      EntryPoint;
  L1_TaskArguments           Arguments;
#ifdef L1_PRIO_INHERITANCE
  L1_KeyedList               CriticalSectionWaitingList; /* list of resources locked to track priority inheritance */
  //const L1_Priority          IntrinsicPriority; /* default static priority */
  L1_Priority                IntrinsicPriority; /* default static priority */
#endif /* L1_PRIO_INHERITANCE */
  /**
   * Indicates whether or not a Task is currently suspended.
   */
  L1_BOOL                    isSuspended;
  L1_InputPort *             const TaskInputPort;
} L1_TaskControlRecord;



#define L1_tcb2id(tcb)              ((tcb)->TaskID)

#if (L1_GLOBALID_SIZE == 8)
#define L1_isLocalTaskID(tid)	    (1)
#define L1_id2tcb(tid)              (&(L1_TaskControlBlock[(tid)]))
#define L1_tcb2localid(tcb)         (((tcb)->TaskID))
#else /* L1_GLOBALID_SIZE == 8 */
/* can be optimized for L1_GLOBALID_SIZE == 16 && L1_WIDEIDS */
#define L1_isLocalTaskID(tid)  	    (((tid) & L1_GLOBALID_MASK) == ((L1_KernelTaskID) & L1_GLOBALID_MASK))
#define L1_id2tcb(tid)              (&L1_TaskControlBlock[((tid) & (~L1_GLOBALID_MASK))])
#define L1_tcb2localid(tcb)         (((tcb)->TaskID) & (~L1_GLOBALID_MASK))
#endif /* L1_GLOBALID_SIZE == 8 */

/**
 *
 * Given a task control record, the function initializes the sequence number of the request packet
 * and starts the entry point function with the arguments pointed by the control block structure.
 *
 * @param TaskCR is a pointer to the task control record of the task to be run.
 *
 */
extern void L1_runTask (L1_TaskControlRecord *TaskCR);

/* #define L1_isLocalTaskID(t)  (((t) & L1_GLOBALID_MASK) == ((L1_KernelTaskID) & L1_GLOBALID_MASK)) */

#if 0
#define L1_List_insertTask(l,t) (L1_List_insert((l), ((L1_ListElement *)(t))))
#define L1_List_removeTask(t) (L1_List_remove(((L1_ListElement *)(t))))
#endif

//void L1_List_insertTask(L1_List* List, L1_TaskControlRecord* Task);
//void L1_List_removeTask(L1_TaskControlRecord* Task);


#define L1_List_insertTask(l, t) L1_List_insert( (l), &((t)->ListElement))
#define L1_List_removeTask(t) L1_List_remove( &((t)->ListElement) )


#endif /* __L1_task_api_h__ */
