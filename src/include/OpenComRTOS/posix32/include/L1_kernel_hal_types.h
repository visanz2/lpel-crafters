/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2008
 * www.Altreonic.com
 * Module name: ($Path/$Filename) 
 * Synopsis: Declares platform specific types used by the kernel.
 * 
 * $LastChangedDate: 2012-11-15 12:50:05 +0100 (Thu, 15 Nov 2012) $
 * $Revision: 3007 $
 * $LastChangedBy: bernhard.sputh $
 *******************************************************************************/

#ifndef __L1_kernel_hal_types_h__
#define __L1_kernel_hal_types_h__

#include <pthread.h>
#include <semaphore.h>

typedef enum
{
    TASK_STATE_CREATED = 0,
    TASK_STATE_SUSPENDED = 1,
    TASK_STATE_RUNNING = 2,
    TASK_STATE_TERMINATED = 3
} L1_POSIX32_TASK_STATE;

/* typedef */struct _struct_L1_POSIX32_TASK_CONTEXT_ {
    pthread_t Thread;
    L1_BOOL SuspendEvent;
    //sem_t ResumeEvent;
    /**
     * This flag is set for the scheduler thread to wait for the ISR thread to have received the ResumeEvent.
     */
    pthread_mutex_t ResumeMutex;
    pthread_cond_t ResumeCV;
    L1_BOOL ResumeFlag;
    L1_POSIX32_TASK_STATE State;
    volatile int SelfSuspended;
    volatile int Interrupted; /* used in enter/leaveISR, and for Enter/LeaveCriticalSection */
#ifdef L1_DEBUG
int IndentSize;
#endif /* L1_DEBUG */
} /* L1_TaskContext */;

/** 
 * This structure describes an ISR
 */
typedef struct _struct_L1_Posix32_ISR{
    /** The function which represents the ISR */
    posix_start_routine_t entryPoint;
    /** The parameter to pass to the isrFunctoin */
    void* param;
    /** The context of the ISR function */
    struct _struct_L1_POSIX32_TASK_CONTEXT_ context;
}L1_Posix32_ISR;



#endif /* __L1_kernel_hal_types_h__ */
