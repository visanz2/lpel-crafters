/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2008
 * www.Altreonic.com
 * Module name: L1_workload_monitoring.h ($Path/$Filename)
 * Synopsis:  Workload monitoring support for OpenComRTOS.
 *
 * $LastChangedDate: 2010-11-05 10:52:18 +0100 (Fri, 05 Nov 2010) $
 * $Revision: 2037 $
 * $LastChangedBy: bernhard.sputh $
 *******************************************************************************/

#include <L1_types.h>

#ifndef L1_WORKLOAD_MONITORING_H_
#define L1_WORKLOAD_MONITORING_H_


/*
 * Enabling the monitoring of the workload.
 */
#define L1_WLMONIT

/**
 * The integration time defines how often a new workload measurement will be
 * available and the amount of time over which the execution of the idle task
 * will be tracked.
 */
#define L1_WLM_INTEGRATION_TIME_MS 10

/**
 * This function is the idle-loop which should be executed in the Idle-Task.
 * @return This function does not return!
 */
L1_UINT32 L1_wlm_idleTask(void);

/**
 * This function is used to calibrate the idle-loop. I must be called by the
 * periodic timer driver after it enabled the 1ms tick. The function will return
 * after the function L1_wml_timerTickHandler signaled that the calibration is
 * complete.
 * @return The last idle-loop loop count, should be ignored.
 *
 * @warning This function must only be executed when the system is otherwise completely idle.
 */
L1_UINT32 L1_wlm_idleLoopCalibration(void);


/**
 * This function get executed in the 1ms periodic ticker ISR, and does calculate
 * the current workload. Furthermore it determines the maximum idle-loop loop count
 * out of 100 samples, when used in conjunction with the function L1_wml_idleLoopCalibration().
 */
void L1_wlm_timerTickHandler(void);

#ifdef L1_WLMONIT
/**
 * The current workload in units of 0.1%.
 */
extern volatile L1_UINT32 L1_currentWorkLoad;

#endif /*WLMONIT*/

#endif /* L1_WORKLOAD_MONITORING_H_ */
