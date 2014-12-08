/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2008
 * www.Altreonic.com
 * Module name: ($Path/$Filename)
 * Synopsis: This file contains all Platform specific MACROS used for Tracing.
 *
 * $LastChangedDate: 2010-09-30 19:41:18 +0200 (Thu, 30 Sep 2010) $
 * $Revision: 1896 $
 * $LastChangedBy: bernhard.sputh $
 *******************************************************************************/


#ifndef L1_HAL_TRACE_H_
#define L1_HAL_TRACE_H_

L1_Status L1_Trace_TimeStamp(L1_TraceEvent *pEvent);

#define L1_TRACE_TIME_STAMP(pEvent) L1_Trace_TimeStamp(pEvent)



#endif /* L1_HAL_TRACE_H_ */
