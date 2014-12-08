/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2012
 * www.Altreonic.com
 * Module name: L1_Drv_PTimer.h
 * Synopsis: This file contains the standardised Interface for all Timer drivers
 * that can be used to provide periodic timer (ptimer) services.
 *
 * $LastChangedDate$
 * $Revision$
 * $LastChangedBy$
 *******************************************************************************/

#ifndef L1_DRV_TIMER_H_
#define L1_DRV_TIMER_H_

#include<driver/class/L1_Drv_IntC.h>

/**
 * Initialises the timer driver self points to.
 *
 * @param self: Pointer to the private data of the timer driver.
 *
 * @return L1_Status, indicates whether or not the operation was successful:
 *  - RC_OK: Operation was successful.
 *  - RC_FAIL: Operation failed.
 *
 */
typedef L1_Status (*timer_initialise)(void * self);

/**
 * Registers the callback function to all when the timer expires, either periodic a waiting timer.
 *
 * @param self: Pointer to the private data of the timer driver.
 * @param callback: This is a pointer to a function of type L1_ISR_CALLBACK which will be called when the timer has expired.
 * @param pContext: Private data to pass to the function indicated by the parameter callback.
 *
 * @return L1_Status, indicates whether or not the operation was successful:
 *  - RC_OK: Operation was successful.
 *  - RC_FAIL: Operation failed.
 *
 */
typedef L1_Status (*timer_register_callback)(void * self, L1_ISR_CALLBACK callback, void * pContext);

/**
 * Starts a periodic tick with the period length specified in periodLengthUs.
 *
 * @param self: Pointer to the private data of the timer driver.
 * @param periodLengthUs: The desired length of the period defined in micro
 * seconds ( 10^(-6)s ). Not all timer drivers are however capable to provide
 * such a fine resolution. Expect slight deviations from the specified interval!
 *
 * @return L1_Status, indicates whether or not the operation was successful:
 *  - RC_OK: Operation was successful.
 *  - RC_FAIL: Operation failed.
 *
 * @warning The precision depends on the used hardware timer, most timers do not provide usec accuracy!
 *
 * @pre The following operations must have been performed prior to starting the ticker:
 *  # The timer must have been initialised with a call to a timer_initialise function.
 *  # A callback function must have been registered by calling a timer_register_callback function.
 *  # No current pending operation on timer, i.e. no other ticker running, or a timeout.
 */
typedef L1_Status (*timer_start_ticker)(void * self, L1_UINT32 periodLengthUs);

/**
 * Stop a previously started periodic ticker.
 *
 * @param self: Pointer to the private data of the timer driver.
 *
 * @return L1_Status, indicates whether or not the operation was successful:
 *  - RC_OK: Operation was successful.
 *  - RC_FAIL: Operation failed.
 *
 */
typedef L1_Status (*timer_stop_ticker)(void * self);

#ifdef WAITING_TIMER
/**
 * This sets up a one shot timer which will expire after the time specified by
 * waitLengthUs.
 *
 * @param self: Pointer to the private data of the timer driver.
 * @param waitLengthUs: The desired length of the period defined in micro
 * seconds ( 10^(-6)s ). Not all timer drivers are however capable to provide
 * such a fine resolution. Expect slight deviations from the specified interval!
 *
 * @return L1_Status, indicates whether or not the operation was successful:
 *  - RC_OK: Operation was successful.
 *  - RC_FAIL: Operation failed.
 *
 */
typedef L1_Status (*timer_wait)(void * self, L1_UINT32 waitLengthUs);

/**
 * Cancels a currently running one shot timer.
 *
 * @warning If called just before the timeout occurs, the registered callback
 * function might still be called!
 *
 * @param self: Pointer to the private data of the timer driver.
 *
 * @return L1_Status, indicates whether or not the operation was successful:
 *  - RC_OK: Operation was successful.
 *  - RC_FAIL: Operation failed.
 *
 */
typedef L1_Status (*timer_cancel_wait)(void * self);
#endif /* WAITING_TIMER */


typedef L1_Status (*timer_get_value)(void* self, L1_UINT32 * pValue);
/**
 * Each timer driver will provide the following data structure in a preconfigured
 * form, in its C or ASM file, and reference to it as external in its header file.
 * A pointer to this data structure can then be passed on device drivers that want
 * to use this device driver. Furthermore, each driver will have to have a pointer
 * to the private data of the timer driver. This may be NULL if no private
 * data has to be passed.
 */
typedef struct
{
    timer_initialise          initialise;
    timer_register_callback   registerCallback;
    timer_start_ticker        startTicker;
    timer_stop_ticker         stopTicker;
    timer_get_value           getTicks;
    timer_get_value           getCounterFrequency;
#ifdef WAITING_TIMER
    timer_wait                wait;
    timer_cancel_wait         cancelWait;
#endif /* WAITING_TIMER */
}L1_Drv_Timer_API;



/**
 * Represents an instance of an interrupt controller in OpenComRTOS.
 *
 * @warning This structure has to be initialised during the code generation
 * phase.
 */
typedef struct
{
    /**
     * Points to a structure of L1_Drv_Timer_API. This structure
     * contains pointers to the functions that can be used to interface with
     * the driver that represents this interrupts controller.
     */
    L1_Drv_Timer_API * api;
    /**
     * Pointer to the private data associated with the interrupt controller
     * instance. This pointer may be NULL, if no parameter is necessary.
     */
    void             * self;
}L1_Drv_Timer;

/**
 * Initialises the timer driver pTimer points to.
 *
 * @param pTimer: Pointer to a structure of type L1_Drv_Timer.
 *
 * @return L1_Status, indicates whether or not the operation was successful:
 *  - RC_OK: Operation was successful.
 *  - RC_FAIL: Operation failed.
 *
 * @sa timer_initialise
 */
#define L1_Drv_Timer_initialise(pTimer)\
    (pTimer)->api->initialise( (pTimer)->self)


/**
 * Registers the callback function to all when the timer expires, either periodic a waiting timer.
 *
 * @param pTimer: Pointer to a structure of type L1_Drv_Timer.
 * @param callback: This is a pointer to a function of type L1_ISR_CALLBACK which will be called when the timer has expired.
 * @param pContext: Private data to pass to the function indicated by the parameter callback.
 *
 * @return L1_Status, indicates whether or not the operation was successful:
 *  - RC_OK: Operation was successful.
 *  - RC_FAIL: Operation failed.
 *
 * @sa timer_register_callback
 */
#define L1_Drv_Timer_registerCallback(pTimer, callback, pContext)\
    (pTimer)->api->registerCallback( (pTimer)->self, callback, pContext)

/**
 * Starts a periodic tick with the period length specified in periodLengthUs.
 *
 * @param pTimer: Pointer to a structure of type L1_Drv_Timer.
 * @param periodLengthUs: The desired length of the period defined in micro
 * seconds ( 10^(-6)s ). Not all timer drivers are however capable to provide
 * such a fine resolution. Expect slight deviations from the specified interval!
 *
 * @return L1_Status, indicates whether or not the operation was successful:
 *  - RC_OK: Operation was successful.
 *  - RC_FAIL: Operation failed.
 *
 * @warning The precision depends on the used hardware timer, most timers do not provide usec accuracy!
 *
 * @pre The following operations must have been performed prior to starting the ticker:
 *  # The timer must have been initialised with a call to a timer_initialise function.
 *  # A callback function must have been registered by calling a timer_register_callback function.
 *  # No current pending operation on timer, i.e. no other ticker running, or a timeout.
 *
 * @sa timer_start_ticker
 */
#define L1_Drv_Timer_startTicker(pTimer, periodLengthUs)\
    (pTimer)->api->startTicker( (pTimer)->self, periodLengthUs)

/**
 * Stop a previously started periodic ticker.
 *
 * @param pTimer: Pointer to a structure of type L1_Drv_Timer.
 *
 * @return L1_Status, indicates whether or not the operation was successful:
 *  - RC_OK: Operation was successful.
 *  - RC_FAIL: Operation failed.
 *
 * @sa timer_stop_ticker
 */
#define L1_Drv_Timer_stopTicker(pTimer)\
    (pTimer)->api->stopTicker( (pTimer)->self)



/**
 * Retrieves the number of ticks that have expired since the last time the
 * automatic reload counter has reloaded itself.
 *
 * @param pTimer: Pointer to a structure of type L1_Drv_Timer.
 * @param pValue: Pointer to a variable of type L1_UINT32, which will contain
 * the result of the operation.
 *
 * @return L1_Status, indicates whether or not the operation was successful:
 *  - RC_OK: Operation was successful.
 *  - RC_FAIL: Operation failed.
 *
 */
#define L1_Drv_Timer_getTicks(pTimer, pValue)\
    (pTimer)->api->getTicks( (pTimer)->self, pValue)

/**
 * Returns the frequeqency with which the automatic reload counter counts.
 *
 * @param pTimer: Pointer to a structure of type L1_Drv_Timer.
 * @param pValue: Pointer to a variable of type L1_UINT32, which will contain
 * the result of the operation.
 *
 * @return L1_Status, indicates whether or not the operation was successful:
 *  - RC_OK: Operation was successful.
 *  - RC_FAIL: Operation failed.
 *
 */
#define L1_Drv_Timer_getCounterFrequency(pTimer, pValue)\
    (pTimer)->api->getCounterFrequency( (pTimer)->self, pValue)


#ifdef WAITING_TIMER
/**
 * This sets up a one shot timer which will expire after the time specified by
 * waitLengthUs.
 *
 * @param pTimer: Pointer to a structure of type L1_Drv_Timer.
 * @param waitLengthUs: The desired length of the period defined in micro
 * seconds ( 10^(-6)s ). Not all timer drivers are however capable to provide
 * such a fine resolution. Expect slight deviations from the specified interval!
 *
 * @return L1_Status, indicates whether or not the operation was successful:
 *  - RC_OK: Operation was successful.
 *  - RC_FAIL: Operation failed.
 * @sa timer_wait
 */
#define L1_Drv_Timer_wait(pTimer, waitLengthUs)\
    (pTimer)->api->wait( (pTimer)->self, waitLengthUs)

/**
 * Cancels a currently running one shot timer.
 *
 * @warning If called just before the timeout occurs, the registered callback
 * function might still be called!
 *
 * @param pTimer: Pointer to a structure of type L1_Drv_Timer.
 *
 * @return L1_Status, indicates whether or not the operation was successful:
 *  - RC_OK: Operation was successful.
 *  - RC_FAIL: Operation failed.
 *
 * @sa timer_cancel_wait
 */
#define L1_Drv_Timer_cancelWait(pTimer)\
    (pTimer)->api->cancelWait( (pTimer)->self)
#endif /* WAITING_TIMER */



#endif /* L1_DRV_TIMER_H_ */
