/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2011
 * www.Altreonic.com
 * Module name: L1_ptimer.h
 * Synopsis: Collection of the default pTimer data structure.
 *
 * $LastChangedDate$
 * $Revision$
 * $LastChangedBy$
 *******************************************************************************/


#ifndef L1_PTIMER_H_
#define L1_PTIMER_H_

#include<L1_types.h>
#include<driver/class/L1_Drv_Timer.h>
/**
 * Data structure that is used to initialise pTimer drivers. Currently only used
 * by the TMSC66x timer driver, but in future other drivers will be adjusted.
 */
typedef struct L1_Drv_pTimer_struct
{
    /**
     * Pointer to the L1_Drv_Timer to use.
     */
    L1_Drv_Timer * timer;
    /**
     * The expired timeout ticks since start of the pTimer.
     *
     * \note Initialise to 0.
     */
    L1_UINT32  currentTime;
    /**
     * If larger than 0, then it represents the length of the currently running
     * timeout. If 0 no timeout is pending.
     *
     * \note Initialise to 0.
     */
    L1_Timeout ticksTillTimeout;

    /**
     * How many ticks must still expire until the current timeout expires. If 0 no timeout is running.
     *
     * \note Initialise to 0
     */
    L1_Timeout ticksRemainingTillTimeout;
    /**
     * Identification number of the currently running timeout. This is used to prevent early timeouts.
     *
     * \note Initialise to 0
     */
    L1_UINT32  timeoutId;
    /**
     * Packet to send when a timeout has expired.
     */
    L1_Packet timerISRPacket;
}L1_Drv_pTimer;

L1_Status L1_Drv_pTimer_initialise(L1_Drv_pTimer * self);

#endif /* L1_PTIMER_H_ */
