/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2008
 * www.Altreonic.com
 * Module name: ($Path/$Filename)
 * Synopsis: Hardware Abstraction Layer API.
 *
 * $LastChangedDate: 2014-02-11 16:56:11 +0100 (Tue, 11 Feb 2014) $
 * $Revision: 4179 $
 * $LastChangedBy: bernhard.sputh $
 *******************************************************************************/

#ifndef __L1_hal_api_h__
#define __L1_hal_api_h__

#include <L1_hal_types.h>
#include <L1_hal_asm.h>
#include <kernel/L1_task_api.h>
#include <kernel/L1_timer_api.h>
#include <driver/linkcommunication.h>
/**
 * \internal
 * \defgroup OCR_HAL Hardware Abstraction Layer
 *
 * This is the interface between the Kernel and the hardware specific platform.
 */

/**
 * \internal \ingroup OCR_HAL
 * Global platform initialization and creation of all tasks and CPU contexts.
 * The function is called when starting OpenComRTOS to provide any platform
 * dependent initialization and creation of tasks.
 *
 * @param NodeNumberOfTasks The number of Tasks on this node, which need to be
 * initialised using the function L1_initializeContextOfTask.
 * @sa L1_initializeContextOfTask
 *
 * Example:
 * \code
 * //Initialize ISR context, if any
 * L1_IsrStackPtr = ...;
 *
 * // Initialize application tasks
 * for (i = 0; i < NodeNumberOfTasks; i++) {
 *     if (L1_TaskControlBlock[i].TaskState == L1_STARTED) {
 *         L1_initializeContextOfTask(&(L1_TaskControlBlock[i]));
 *      }
 * }
 * \endcode
 *
 */
extern void L1_initializePlatform(L1_UINT32 NodeNumberOfTasks);
/**
 * \internal \ingroup OCR_HAL
 *
 * Platform dependent creation and initialization of CPU context of a task.
 *
 * @param TaskCR Reference to the Task Control Record for which the CPU context should be initialized.
 *
 * Example:
 * \code
void L1_initializeContextOfTask (L1_TaskControlRecord  *TaskCR)
{
  L1_TaskContext * TaskContext;

  TaskContext = TaskCR->Context;

  // Configure the Stack to call so that loading the context
  // causes the function L1_runTask() to be called.

  ...

  // initialize all context fields
  ...
}
 * \endcode
 *
 *
 * @remark Function called by L1_initializePlatform and in response to a  L1_StartTask_W service.
 *
 * @sa L1_StartTask_W
 * @sa L1_initializePlatform
 */
extern void L1_initializeContextOfTask(L1_TaskControlRecord *TaskCR);


/**
 * \internal \ingroup OCR_HAL
 * Platform dependent clearance and removal of CPU context of a task.
 * @param TaskCR Reference to the Task Control Record for which the CPU context should be cleared or removed.
 *
 * Example:
 * \code
void L1_deinitializeContextOfTask (L1_TaskControlRecord *TaskCR)
{
    L1_TaskContext *TaskContext = TaskCR->Context;

    // Free all storage and reset any context fields
    // here or in L1_initializeContextOfTask
    ...
    TaskContext->State = TASK_CONTEXT_STATE_TERMINATED;
}
 * \endcode
 * @remark Function called in response to a L1_StopTask_W service. Function can be empty if the context is never changed or if it is followed by a L1_initializeContextOfTask
 *
 * @sa L1_StopTask_W
 */
extern void L1_deinitializeContextOfTask(L1_TaskControlRecord *TaskCR);


/**
 * \internal \ingroup OCR_HAL
 *
 * Platform dependent function to yield execution to another task to run on the CPU.
 *
 * The context of the task to pre-empt should be saved, and the context of the task to resume should be restored. The CPU resources will then be given to the restored task.
 *
 *
 * @param Task2Preempt Reference to the Task that will yield its execution (typically L1_CurrentTaskCR)
 *
 * @param TaskCR2Restore Reference to the Task that will resume execution.
 *
 * Example:
 * \code
void L1_switchContext (L1_TaskControlRecord * Task2Preempt, L1_TaskControlRecord * Task2Restore)
{
    Stack2SwitchON  = Task2Restore->Context->StackPtr;
    Stack2SwitchOFF = &(Task2Preempt->Context->StackPtr);
    L1_CurrentTaskCR = Task2Restore;

    // save context
    ... push registers on the stack ...
    ... store the current stack pointer Stack2SwitchOFF ...
    // load context
    ... load the new stack pointer Stack2SwitchON ...
    ... pop registers from the stack ...
}
 * \endcode
 *
 * @remark OpenComRTOS selects the task to restore. Function is called from within a L1_enterCriticalSection / L1_leaveCriticalSection pair.
 *
 * @sa L1_saveStatusRegister
 * @sa L1_restoreStatusRegister
 */
extern void L1_switchContext(L1_TaskControlRecord * Task2Preempt,
                             L1_TaskControlRecord * TaskCR2Restore);




/**
 * \internal \ingroup OCR_HAL
 * Platform dependent function to start execution of the OpenComRTOS tasks on the CPU. The context of the first task to start should be loaded, and the CPU resources given to that task (typically the Kernel Task).
 *
 * Example:
 * \code
void L1_startTasks (void)
{
    L1_CurrentTaskCR = L1_KernelTaskCR;
    Stack2SwitchON  = L1_CurrentTaskCR->Context->StackPtr;

    // load context
    ... load the new stack pointer Stack2SwitchON ...
    ... pop registers from the stack ...
}
 * \endcode
 */
extern void L1_startTasks(void);





//#if defined (MP) || defined (WT_SERVICES) /* incl WT */
/**
 * \internal \ingroup OCR_HAL
 * Platform dependent prologue of an interrupt service routine.
 *
 * In most platforms this function does not exist but is part of the
 * Interrupt Controller Driver.
 *
 * Example:
 * \code
void L1_enterISR(void)
{
    // push registers onto the stack
    // save the task context if not yet done so
    ... enter critical section for nested interrupts ...
    L1_ISRNesting++;
    if (L0_ISRNesting == 1) {
        ... // save context
        ... // switch to ISR context
    }
    .. leave critical section for nested interrupts ...
}
 * \endcode
 * @remark It is recommended to use a separate context and stack for ISRs.
 */
extern void L1_enterISR(void);



/**
 * \internal \ingroup OCR_HAL
 * Platform dependent epilogue of an interrupt service routine.
 *
 * In most platforms this function does not exist but is part of the
 * Interrupt Controller Driver.
 *
 * Example:
 * \code
L1_leaveISR(void){
    ... enter critical section for nested interrupts ...

    L1_ISRNesting--;
    if (L1_ISRNesting == 0) {
        if (L1_CurrentTaskCR == L1_KernelTaskCR) {
            // only if in process of deschedule
            L1_ScheduleRequest = L1_TRUE;
            TaskCR2Restore = L1_CurrentTaskCR;
        } else if (L1_ScheduleRequest == L1_TRUE) {
            // requested by a user task
            // leave it up to normal flow, since task is about to switch to KernelTask
        } else {
            // we are in a user task, not in a kernel request service, switch to kernel
            L1_ScheduleRequest = L1_FALSE;
            // restore and switch context
            ... L1_switchContext (L1_CurrentTaskCR, L1_KernelTaskCR) ...
        }
        // return
        // resumed the suspended thread again, or other and finish processing this ISR
    } else {
        // nested interrupts, switch context when returning from first/original ISR
        // normal flow
    }
    ... restore context ...
    ... leave critical section for nested interrupts ...
    // pop registers from the stack
    ...
}
 * \endcode
 * @remark It is recommended to use a separate context and stack for ISRs
 */
extern void L1_leaveISR(void);



#if 0
#ifdef MP
/**
 * \internal \ingroup OCR_HAL
 */
extern void L1_initializePlatformNodeLinks(void);
#endif /* MP */

/* to cater for e.g. -fshort-enums and short timeouts */
#define hton_ServiceID(sid)     hton16((L1_UINT16) (sid))
#define hton_Status(status)     hton16((L1_UINT16) (status))
#define hton_Timeout(timeout)   hton32((L1_UINT32) (timeout))
#define ntoh_ServiceID(/* L1_UINT16 */ sid)     (L1_ServiceID) ntoh16((sid))
#define ntoh_Status(/* L1_UINT16 */ status)     (L1_Status)    ntoh16((status))
#define ntoh_Timeout(/* L1_UINT32 */ timeout)   (L1_Timeout)   ntoh32((timeout))

#if (L1_GLOBALID_SIZE == 8)
/* can't be for MP ... */
#define hton_PortID(pid)    (pid)
#define hton_TaskID(tid)    (tid)
#define ntoh_PortID(pid)    (pid)
#define ntoh_TaskID(tid)    (tid)
#elif (L1_GLOBALID_SIZE == 16)
#define hton_PortID(pid)    hton16((pid))
#define hton_TaskID(tid)    hton16((tid))
#define ntoh_PortID(pid)    ntoh16((pid))
#define ntoh_TaskID(tid)    ntoh16((tid))
#elif (L1_GLOBALID_SIZE == 32)
#define hton_PortID(pid)    hton32((pid))
#define hton_TaskID(tid)    hton32((tid))
#define ntoh_PortID(pid)    ntoh32((pid))
#define ntoh_TaskID(tid)    ntoh32((tid))
#else
#error "invalid L1_GLOBALID_SIZE value (supported values: 8, 16, 32)"
#endif /* L1_GLOBALID_SIZE == 8, 16, 32 */
#endif /* 0 */


#if 0
/**
 * \internal \ingroup OCR_HAL
 * Retrieving of current machine status info, e.g. interrupt mask, and entering of critical section for context switch as a side-effect. Paired with L1_restoreStatusRegister.
 *
 * Example
 * \code
L1_INTERRUPT_STATUS L1_saveStatusRegister(void)
{
    L1_INTERRUPT_STATUS status;
    status = SREG;    // get Status Register
    ... disable interrupts ...
    return status;
}
 * \endcode
 *
 * @return The value of the MSR before interrupts got disabled.
 *
 * @remark Return value used as argument to L1_restoreStatusRegister.
 * @remark Should be used instead of L1_enterCriticalSection in new code.
 *
 */
extern L1_INTERRUPT_STATUS L1_saveStatusRegister(void);




/**
 * \internal \ingroup OCR_HAL
 * Restoring of current machine status info, e.g. interrupt mask, and leaving of critical section for context switch as a side-effect. Paired with L1_saveStatusRegister.
 *
 * @param msr Platform dependent status information, e.g. interrupt mask.
 *
 * @warning The parameter MSR must be a return value from L1_saveStatusRegister.
 *
 * @remark Called with value returned from L1_saveStatusRegister
 * @remark Should be used instead of L1_leaveCriticalSection in new code.
 *
 */
extern void L1_restoreStatusRegister(L1_INTERRUPT_STATUS msr);

#endif /* 0 */

#endif /*__L1_hal_api_h__*/
