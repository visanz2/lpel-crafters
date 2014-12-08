/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2008
 * www.Altreonic.com
 * Module name: ($Path/$Filename)
 * Synopsis: Tracer API
 *
 * $LastChangedDate: 2013-10-18 17:56:27 +0200 (Fri, 18 Oct 2013) $
 * $Revision: 4082 $
 * $LastChangedBy: bernhard.sputh $
 *******************************************************************************/

#ifndef __L1_trace_api_h__
#define __L1_trace_api_h__
//#include <L1_api.h>

/**
 * This structure represents one event recorded in the tracebuffer.
 */
typedef struct _struct_tracebuffer_
{
    /**
     * This is the first parameter in the tracebuffer, it should be used to
     * encode the 8 bit type in the lowest 8bit of the 32Bit word, the highest
     * 24Bit are used to store the elapsed system ticks (usually ms).
     */
    L1_UINT32 param0;
    /**
     * The second parameter of an event contains the value of the high counter,
     * usually the clock value.
     */
    L1_UINT32 param1;
    /**
     * The content of this parameter depends upon the type of event that was
     * traced.
     */
    L1_UINT32 param2;
    /**
     * The content of this parameter depends upon the type of event that was
     * traced.
     */
    L1_UINT32 param3;
}L1_TraceEvent, L1_Trace_TraceBufferElement;


/**
 * This Macro encodes the timestamp, which consists of the values highCounter
 * and lowCounter in the L1_Trace_Event variable to which pEvent points.
 *
 * @param pEvent a pointer to a variable of L1_TraceEvent, where the timestamp
 * should be encoded in.
 *
 * @param highCounter a variable of type L1_UINT32 containing the value of the
 * high frequency counter to encode in the L1_TraceEvent. Usually that is the
 * counter value of the timer / counter used to derive the system tick.
 *
 * @param lowCounter a variable of type L1_UINT32 which contains the value of
 * the systemtick counter.
 *
 * @warning Do not pass a NULL pointer as pEvent, this will definitely crash!
 */
#define L1_TRACE_SET_EVENT_TIMESTAMP(pEvent, highCounter, lowCounter) do{(pEvent)->param0=((lowCounter)<<8); (pEvent)->param1=(highCounter);}while(0)

/**
 * This Macro retrieves the value of the high counter from the L1_TraceEvent
 * variable pEvent points to.
 *
 * @param pEvent a pointer to a variable of L1_TraceEvent, where the high
 * counter value should be extracted from.
 *
 * @return L1_UINT32 the value of the high counter.
 *
 * @warning Do not pass a NULL pointer as pEvent, this will definitely crash!
 */
#define L1_TRACE_GET_EVENT_HIGH_COUNTER(pEvent) (pEvent)->param1

/**
 * This Macro retrieves the value of the low counter from the L1_TraceEvent
 * variable pEvent points to.
 *
 * @param pEvent a pointer to a variable of L1_TraceEvent, where the low
 * counter value should be extracted from.
 *
 * @return L1_UINT32 the value of the low counter.
 *
 * @warning Do not pass a NULL pointer as pEvent, this will definitely crash!
 */
#define L1_TRACE_GET_EVENT_LOW_COUNTER(pEvent) (0xFFFFFF & ((pEvent)->param0>>8))


/**
 * This Macro encodes the eventType in the L1_Trace_Event variable to which
 * pEvent points.
 *
 * @param pEvent a pointer to a variable of L1_TraceEvent, where the Event type
 * should be encoded in.
 *
 * @param event an 8bit value that represents the type of event.
 */

#define L1_TRACE_SET_EVENT_TYPE(pEvent, eventType) do{(pEvent)->param0=(pEvent)->param0 + (0xFF & (char)(eventType));}while(0)

/**
 * This Macro retrieves the event-type of the L1_TraceEvent variable pEvent
 * points to.
 *
 * @param pEvent a pointer to a variable of L1_TraceEvent, where the event-type
 * should be extracted from.
 *
 * @return char which contains the event-type of this event.
 *
 * @warning Do not pass a NULL pointer as pEvent, this will definitely crash!
 */
#define L1_TRACE_GET_EVENT_TYPE(pEvent) (0xFF & ((pEvent)->param0))


#include<L1_hal_trace.h>

#ifndef HAL_TRACE_API_MACROS

/**
 * This functions sets the timestamp of an L1_TraceEvent. It has to be
 * implemented in the system timer driver of the platform.
 *
 * @param pEvent, pointer to the L1_TraceEvent variable where to set the timestamp in.
 * @return
 *  - RC_OK if the timestamp could be set.
 *  - RC_FAIL if the value of pEvent is NULL.
 */
L1_Status L1_Trace_TimeStamp(L1_TraceEvent *pEvent);


/**
 * This function returns the frequency (in Hz) with which the low counter increments
 * @warning This function is platform specific.
 *
 * @return L1_UINT32 the frequency in Hz with which the low counter increments.
 */
L1_UINT32 L1_Trace_getLowCounterFrequency(void);

/**
 * This function returns the frequency (in Hz) with which the high counter increments
 * @warning This function is platform specific.
 *
 * @return L1_UINT32 the frequency in Hz with which the high counter increments.
 */
L1_UINT32 L1_Trace_getHighCounterFrequency(void);
#endif /* HAL_TRACE_API_MACROS */

#ifdef L1_ALLOW_TRACE


/* To disable tracing while dumping the TraceBuffer */
extern L1_BOOL tracingDisabled;
extern L1_INT32 nextTraceLine;
extern L1_INT32 oldestTraceLine;

#ifdef XMOS
    /* This block is specific to the XMOS port of OpenComRTOS */
    /**
     * The number of L1_Trace_TraceBufferElement elements that are in the L1_Trace_TraceBuffer
     */
    extern int L1_Trace_NumberOfTraceElements;
    /**
     * The Buffer which holds the trace elements.
     */
    extern L1_Trace_TraceBufferElement * L1_Trace_TraceBuffer; /* Points to an array with L1_NODE_NUMBER_OF_TASKS elements */
#else /* XMOS */
    /**
     * The number of L1_Trace_TraceBufferElement elements that are in the L1_Trace_TraceBuffer
     */
    extern const int L1_Trace_NumberOfTraceElements;
    /**
     * The Buffer which holds the trace elements.
     */
    extern L1_Trace_TraceBufferElement L1_Trace_TraceBuffer[/* L1_Trace_NumberOfTraceElements */];

#endif /* XMOS */

/* platform independent functions */
#ifdef MACROLESS_TRACING
/**
 * This function writes a trace-event into the tracebuffer, without using a critical section.
 * @warning To be only used while either being inside a critical section or while inside an ISR, 
 * with interrupts disabled.
 */
void L1_TraceIsrSafe(L1_INT32 type, L1_UINT32 param1, L1_UINT32 param2);
#define L1_TRACE_ISR_SAFE(modifier, service_id, task_id) L1_TraceIsrSafe ((modifier), (service_id), (task_id))


/**
 * This is the standard way to submit a trace Event
 * @warning Do not use in ISR context or inside a Critical Section,
 * as this function enters and leaves a critical section!
 */
void L1_Trace(L1_INT32 type, L1_UINT32 param1, L1_UINT32 param2);
#define L1_TRACE(modifier, service_id, task_id) L1_Trace ((modifier), (service_id), (task_id))
#else /* MACROLESS_TRACING */



#if 0
/**
 * This function writes a trace-event into the tracebuffer, without using a critical section.
 * @warning To be only used while either being inside a critical section or while inside an ISR,
 * with interrupts disabled.
 */
#define L1_TRACE_ISR_SAFE(t, p1, p2)do{\
	    if(L1_FALSE == tracingDisabled) \
	    { \
	    L1_Trace_TimeStamp( &(L1_Trace_TraceBuffer[nextTraceLine]) ); \
	    L1_TRACE_SET_EVENT_TYPE(&(L1_Trace_TraceBuffer[nextTraceLine]), t); \
	    L1_Trace_TraceBuffer[nextTraceLine].param2 = p1; \
	    L1_Trace_TraceBuffer[nextTraceLine].param3 = p2; \
	    nextTraceLine++; \
		if(nextTraceLine == L1_Trace_NumberOfTraceElements) \
	    { \
	        nextTraceLine = 0; \
	    } \
	    if(oldestTraceLine == nextTraceLine) \
	    { \
	        oldestTraceLine++; \
	        if(oldestTraceLine == L1_Trace_NumberOfTraceElements) \
	        { \
	            oldestTraceLine = 0; \
	        } \
	    } \
	    } \
}while(0)
#endif /* 0 */

#include<L1_hal_trace.h>

/**
 * This function writes a trace-event into the tracebuffer, without using a critical section.
 * @warning To be only used while either being inside a critical section or while inside an ISR,
 * with interrupts disabled.
 *
 * //L1_Trace_TimeStamp( &(L1_Trace_TraceBuffer[nextTraceLine]) ); \
 */
#if 0
#define L1_TRACE_ISR_SAFE(t, p1, p2)do{\
	    if(L1_FALSE == tracingDisabled) \
	    { \
			L1_TRACE_TIME_STAMP( &(L1_Trace_TraceBuffer[nextTraceLine]) ); \
			L1_TRACE_SET_EVENT_TYPE(&(L1_Trace_TraceBuffer[nextTraceLine]), t); \
			L1_Trace_TraceBuffer[nextTraceLine].param2 = p1; \
			L1_Trace_TraceBuffer[nextTraceLine].param3 = p2; \
			nextTraceLine = (nextTraceLine + 1) % L1_Trace_NumberOfTraceElements; \
			if(oldestTraceLine == nextTraceLine) \
			{ \
				oldestTraceLine = (oldestTraceLine + 1) % L1_Trace_NumberOfTraceElements; \
			} \
	    } \
}while(0)
#endif

static inline void L1_TRACE_ISR_SAFE(L1_INT8 t, L1_UINT32 p1, L1_UINT32 p2)
{
    if(L1_FALSE == tracingDisabled)
    {
        L1_TRACE_TIME_STAMP( &(L1_Trace_TraceBuffer[nextTraceLine]) );
        L1_TRACE_SET_EVENT_TYPE(&(L1_Trace_TraceBuffer[nextTraceLine]), t);
        L1_Trace_TraceBuffer[nextTraceLine].param2 = p1;
        L1_Trace_TraceBuffer[nextTraceLine].param3 = p2;
        nextTraceLine = (nextTraceLine + 1) % L1_Trace_NumberOfTraceElements;
        if(oldestTraceLine == nextTraceLine)
        {
            oldestTraceLine = (oldestTraceLine + 1) % L1_Trace_NumberOfTraceElements;
        }
    }
}

/**
 * This is the standard way to submit a trace Event
 * @warning Do not use in ISR context or inside a Critical Section,
 * as this function enters and leaves a critical section!
 */
#define L1_TRACE(type, param1, param2)do{\
	L1_enterCriticalSection();\
	L1_TRACE_ISR_SAFE(type, param1, param2);\
	L1_leaveCriticalSection();\
}while(0)


#ifdef L1_TRACE_LEVEL_2
#define L1_TRACE_LEVEL2_ISR_SAFE(t, p1, p2) L1_TRACE_ISR_SAFE(t, p1, p2)
#define L1_TRACE_LEVEL2(t, p1, p2) L1_TRACE(t, p1, p2)
#else
#define L1_TRACE_LEVEL2_ISR_SAFE(t, p1, p2)
#define L1_TRACE_LEVEL2(t, p1, p2)
#endif /*L1_TRACE_LEVEL_2*/




#endif /* MACROLESS_TRACING */


/**
 *
 * This function inserts a user defined value into the TraceBuffer.
 *
 * @param markerID is the user chosen ID for the marker to insert. It gets
 * combined with the TaskID to form the final ID.
 *
 * @param value an unsigned 32Bit value that should accompany that should be
 * stored as well.
 * @warning Do not use this function when inside an ISR or a Critical Section. Instead use L1_Trace_insertMarkerIsrSafe().
 */
void L1_Trace_insertMarker(L1_UINT16 markerID, L1_UINT32 value);

/**
 *
 * This function inserts a user defined value into the TraceBuffer.
 *
 * @param markerID is the user chosen ID for the marker to insert. It gets
 * combined with the TaskID to form the final ID.
 *
 * @param value an unsigned 32Bit value that should accompany that should be
 * stored as well.
 *
 * @warning Only to be used with interrupts disabled, i.e. either insid an ISR or inside a Critical Section
 */
void L1_Trace_insertMarkerIsrSafe(L1_UINT16 markerID, L1_UINT32 value);

#define L1_TRACE_MARKER(markerID, value) L1_Trace_insertMarker ((markerID), (value))

#define L1_TRACE_MARKER_ISR_SAVE(markerID, value) L1_Trace_insertMarkerIsrSafe ((markerID), (value))


#else /* L1_ALLOW_TRACE */

/* undef */
#define L1_TRACE_ISR_SAFE(t, p1, p2)
#define L1_TRACE(t, p1, p2)

#define L1_TRACE_LEVEL2_ISR_SAFE(t, p1, p2)
#define L1_TRACE_LEVEL2(t, p1, p2)


#define L1_TRACE_MARKER(markerID, value)
#define L1_TRACE_MARKER_ISR_SAVE(markerID, value)

#endif /* L1_ALLOW_TRACE */


/**
 * Disables the adding of trace lines.
 */
void L1_Trace_disableTracing(void);

/**
 * Enables the adding of trace lines.
 */
void L1_Trace_enableTracing(void);

/**
 * Returns the index of the oldest traceline in the buffer.
 */
L1_UINT32 L1_Trace_getOldestTraceLine();

/**
 * Returns the index of the place where the next traceline will be written.
 */
L1_UINT32 L1_Trace_getNextTraceLine();

L1_UINT32 L1_Trace_getNumberOfAvailableTraceLines();

#endif /* __L1_trace_api_h__ */
