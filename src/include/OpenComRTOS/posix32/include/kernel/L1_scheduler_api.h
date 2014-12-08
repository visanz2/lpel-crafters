/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2008
 * www.Altreonic.com
 * Module name: ($Path/$Filename)
 * Synopsis: Task scheduler API
 *
 * $LastChangedDate: 2013-06-13 20:45:48 +0200 (Thu, 13 Jun 2013) $
 * $Revision: 3866 $
 * $LastChangedBy: bernhard.sputh $
 *******************************************************************************/

#ifndef __L1_scheduler_api_h__
#define __L1_scheduler_api_h__

/**
 * List of all Tasks that are ready to run. The Head element of L1_ReadyList is the currently running Task, unless the
 * Kernel-Task is running.
 */
extern L1_List L1_ReadyList;

/**
 * This flag gets set when an ISR demands to switch to ther Kernel-Task.
 */
extern volatile L1_BOOL L1_ScheduleRequest;

/**
 * Checks whether or not the Task identified by TaskCR is currently on the Ready-List or not.
 * @param TaskCR Pointer to the Task Control Record of the Task for which to check the presence on the Ready-List.
 * @return L1_TRUE The Task is on the Ready-List.
 * @return L1_FALSE The Task is not on the Ready-List.
 */
#ifdef API_DOC
    L1_BOOL L1_isReady(L1_TaskControlRecord * TaskCR);
#else
    #define L1_isReady(TaskCR) (L1_List_isMember (&L1_ReadyList, ((L1_ListElement *)(TaskCR))))
#endif /* API_DOC */

/**
 * This function switches from teh Kernel-Task to the next Task on the Ready-List. If an intermediate occurring IRQ
 * requested to switch to the Kenrel-Task then this function will not deschedule the Kernel-Task.
 * @param TaskCR Pointer to the Task Control Record of the currently executing Task, which should be the Kernel-Task.
 */
extern void L1_DescheduleKernel(L1_TaskControlRecord *TaskCR);


/**
 * This function switches to the Kernel-Task.
 * @param TaskCR Pointer to the Task Control Record of the currently executing Task.
 */
extern void L1_Switch2Kernel(L1_TaskControlRecord *TaskCR);


/**
 * This function performs a rescheduling operation. The operation either switches to the Kernel-Task or deschedules
 * the Kernel-Task if it is currently executing.
 *
 * @param TaskCR Pointer to the Task Control Record of the currently running Task.
 *
 */
#ifdef API_DOC
    void L1_Reschedule(L1_TaskControlRecord * TaskCR);
#else
    #define L1_Reschedule(TaskCR) do{\
        if (TaskCR == L1_KernelTaskCR) {\
            L1_DescheduleKernel(TaskCR);\
        }else {\
            L1_Switch2Kernel(TaskCR);\
        }\
    }while(0)
#endif /* API_DOC */





#endif /* __L1_scheduler_api_h__ */
