/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2008
 * www.Altreonic.com
 * Module name: ($Path/$Filename)
 * Synopsis: Hardware Abstraction Layer API.
 *
 * $LastChangedDate: 2013-10-16 20:23:57 +0200 (Wed, 16 Oct 2013) $
 * $Revision: 4070 $
 * $LastChangedBy: bernhard.sputh $
 *******************************************************************************/

#ifndef L1_TIMER_API_H_
#define L1_TIMER_API_H_

#include <L1_types.h>

//#ifdef WT_SERVICES




/**
 * This structure represents a timestamp taken by the local timer device. Use the function the function L1_Timer_getTimeStamp() to acquire a timestamp.
 *
 * @see L1_Timer_getTimeStamp
 * @see L1_Timer_getLowCounterFrequency
 * @see L1_Timer_getHighCounterFrequency
 */
typedef struct
{
    /**
     * This represents the number of expired high frequency timer ticks.
     * To determine the frequency of this counter use the function
     * L1_Timer_getHighCounterFrequency().
     */
    L1_UINT32 highFreqTicks;
    /**
     * This represents the number of expired low frequency timer ticks.
     * To determine the frequency of this counter use the function
     * L1_Timer_getLowCounterFrequency().
     */
    L1_UINT32 lowFreqTicks;
} L1_TimeStamp;

/**
 * This function returns the number of expired high-frequency ticks (normally clock ticks)
 * and low-frequency ticks (normally system timer ticks of ms) to the caller.
 *
 * @param pTimeStamp Pointer to a variable of type L1_TimeStamp. After successful execution of the function this structure contains the timestamp values.
 *
 * @return L1_STATUS:
 *   - RC_OK, upon successful execution
 *   - RC_FAIL, upon an error.
 */
L1_Status L1_Timer_getTimeStamp(L1_TimeStamp * pTimeStamp);

/**
 * This function returns the frequency (in Hz) with which the low counter increments
 * @warning This function is platform specific.
 *
 * @return L1_UINT32 the frequency in Hz with which the low counter increments.
 *
 * @warning Need to determine the correct values
 */
L1_UINT32 L1_Timer_getLowCounterFrequency(void);

/**
 * This function returns the frequency (in Hz) with which the high counter increments
 * @warning This function is platform specific.
 *
 * @return L1_UINT32 the frequency in Hz with which the high counter increments.
 *
 * @warning Need to determine the correct values
 */
L1_UINT32 L1_Timer_getHighCounterFrequency(void);

/**
 * This function converts milliseconds into timer ticks (target specific).
 *
 * @param timeout_ms Milliseconds to be converted to ticks.
 *
 * @return L1_Timeout system ticks that take the milliseconds received.
 */
L1_Timeout L1_msec2ticks(L1_Timeout timeout_ms);

/**
 * \internal
 * This function initializes the target specific timer.
 */
void L1_initTimer(void);

/* should be L1_Duration */
/**
 * \internal
 * This function starts a timeout on local timer device.
 * The timer will send a packet with the SID: SID_AWAKE_TASK,
 * after the given number of system ticks have expired. This packet will
 * contain the given id in the first four bytes of the
 * data part.
 *
 * This function replaces: void L1_startTimer (L1_Timeout time);
 *
 *
 * @param ticks The number of timer ticks that have to expire before the timer sends an L1_Packet to the kernel.
 * @param id The L1_UINT32 value to be stored in the first four bytes of the Packet.
 */
void L1_Timer_setTimeout(L1_Timeout ticks, L1_UINT32 id);

/**
 * \internal
 * This function tells the timer to cancel any previously registered timeout.
 * It replaces the function: void L1_stopTimer (void);
 */
void L1_Timer_cancelTimeout(void);

/**
 * This function checks whether or not the TimerISR packet is currently being processed by the kernel.
 *
 * @return L1_BOOL
 *  - L1_TRUE if the TimerISR packet is being processed.
 *  - L1_FALSE otherwise.
 */
L1_BOOL L1_Timer_isTimerPacketBeingProcessed(void);

/**
 * \internal
 * This function returns the number of system ticks that
 * still have to occur before the timer will send an L1_Packet
 * with the SID: SID_AWAKE_TASK.
 *
 * @return The remaining number of system ticks of the current timeout.
 * If there is currently no running timeout the function returns 0.
 *
 */
L1_Time L1_Timer_getRemainingTimeoutTicks(void);

/**
 *
 * This function returns how many system system ticks have expired since the start of the system.
 * @return The number of systemTicks.
 *
 * @warning The returned value wraps around when an overflow occurred!
 */
L1_Time L1_Timer_getCurrentTime();

#if 0
/**
 * \internal
 * Determines whether or not the desired time interval has already expired.
 *
 * @param baseTime This represents the current number of timer ticks that from which the
 * measurement starts. This value must be acquired using the function L1_Timer_getCurrentTime().
 *
 * @param timeInMs This is the number of miliseconds that must have been expired, for the function to return L1_TRUE.
 *
 * @returns L1_BOOL:
 *  - L1_TRUE --- the desired time interval has expired.
 *  - L1_FALSE --- the desired timer interval has not yet expired.
 *
 *
 */
L1_BOOL L1_Timer_hasTimeExpired(L1_Time baseTime, L1_UINT32 timeInMs);
#endif /* 0 */

/**
 * This function checks whether the timepoint self is later than the timepoint t2
 * @param self Pointer to a variable of type L1_TimeStamp that represents the first timepoint that gets compared
 * @param t2 Pointer to a variable of type L1_TimeStamp which represents the timepoint with which self will be compared.
 * @param isLater Pointer to a variable of type L1_BOOl which will hold the result if the function returns RC_OK.
 * @return RC_OK The operation was performed successfully, one can now use the value in isLater.
 * @return RC_FAIL The operation failed.
 */
L1_Status L1_TimeStamp_isLater(const L1_TimeStamp * self, const L1_TimeStamp * t2, L1_BOOL * isLater);

/**
 * This function calculates the difference between the timepoints t1 and t2.
 *
 * @param self Pointer to a variable of type L1_TimeStamp. This is the first timepoint, this timepoint must be earlier than timepoint t2.
 * @param t2 Pointer to a variable of type L1_TimeStamp. The second timepoint, this timepoint must be later than timepoint self.
 * @param difference Pointer to a variable of type L1_TimeStamp which will contain the difference between the two timepoints.
 * @return RC_OK If the operation could be completed successfully.
 * @return RC_FAIL If the operation could not be completed successfully.
 *
 * @warning Timepoint t2 must be later than timepoint t1 for this to work!
 */
L1_Status L1_TimeStamp_calculateDifference(const L1_TimeStamp * self, const L1_TimeStamp * t2, L1_TimeStamp * difference);


//#endif /* WT_SERVICES */

#endif /* L1_TIMER_API_H_ */
