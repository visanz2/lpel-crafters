/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2008
 * www.Altreonic.com
 * Module name: ($Path/$Filename)
 * Synopsis: This module declares and defines  platform independent data types
 *  involved into OpenComRTOS Layer 1 API
 *
 *
 * $LastChangedDate: 2013-12-22 19:45:33 +0100 (Sun, 22 Dec 2013) $
 * $Revision: 4130 $
 * $LastChangedBy: bernhard.sputh $
 *******************************************************************************/

#ifndef __L1_types_h__
#define __L1_types_h__

#include <L1_hal_types.h>
/* The following lines define constants that contain the minimum and maximum
 * value a variable of a specific type can hold.
 */


/**
\defgroup OCR_BASE_TYPES Base Variable types
*/

/**
L1_BYTE is a 8-bit unsigned integer type.
\sa L1_BYTE_MIN
\sa L1_BYTE_MAX
\ingroup OCR_BASE_TYPES
*/
extern const L1_BYTE   L1_BYTE_MIN;
extern const L1_BYTE   L1_BYTE_MAX;



/**
L1_INT32 is a 32-bit signed integer type.
\sa L1_INT32_MIN
\sa L1_INT32_MAX
\ingroup OCR_BASE_TYPES
*/
extern const L1_INT32 L1_INT32_MIN;
extern const L1_INT32 L1_INT32_MAX;

/**
L1_INT16 is a 16-bit signed integer type.
\sa L1_INT16_MIN
\sa L1_INT16_MAX
\ingroup OCR_BASE_TYPES
*/
extern const L1_INT16 L1_INT16_MIN;
extern const L1_INT16 L1_INT16_MAX;

/**
UINT32 is a 32-bit unsigned integer type.
\sa L1_UINT32_MIN
\sa L1_UINT32_MAX
\ingroup OCR_BASE_TYPES
*/
extern const L1_UINT32 L1_UINT32_MIN;
extern const L1_UINT32 L1_UINT32_MAX;


/**
UINT16 is a 16-bit unsigned integer type.
\sa L1_UINT16_MIN
\sa L1_UINT16_MAX
\ingroup OCR_BASE_TYPES
*/
extern const L1_UINT16 L1_UINT16_MIN;
extern const L1_UINT16 L1_UINT16_MAX;



/**
L1_BOOL is a basic integer type sufficient to represent the values: L1_TRUE and L1_FALSE. (size depends on target)
\ingroup OCR_BASE_TYPES
*/
#define L1_FALSE 0U
#define L1_TRUE  1U


/**
L1_Priority is a basic unsigned integer type sufficient to represent the values from 0 to 255, identifying the priority of a Task or a Packet.
*/
typedef L1_BYTE L1_Priority;


/**
Argument to a Task Entry Point.
*/
typedef void * L1_TaskArguments;

/**
\defgroup OCR_TIMER_TYPES Types related to Timing
*/

/**
L1_Timeout is a basic unsigned integer type that represents a timeout value in milliseconds. The maximum value, allowed by the appropriate L1_Timeout integer type, is interpreted as an infinite timeout. For example if L1_Timeout is provided by the means of a 16-bit or 32bit unsigned integer, then the infinite timeout is 0xFFFF(FFFF) Hex. The infinite timeout is (should be) referred as named constant L1_Infinite_TimeOut
\ingroup OCR_TIMER_TYPES
*/
typedef L1_UINT32 L1_Timeout;

#define L1_INFINITE_TIMEOUT 0xFFFFFFFEU

#ifdef ASYNC_SERVICES
#define L1_ASYNC       0xFFFFFFFFU /* for the time being, as no _WT services yet */
/*#define L1_ASYNC       0x1 for the time being, as no _WT services yet */
#endif /* ASYNC_SERVICES */



/**
This datatype is used to represent the number of expired ticks.
\sa L1_Time_MIN
\sa L1_Time_MAX
\ingroup OCR_TIMER_TYPES
*/
typedef L1_UINT32 L1_Time;
extern const L1_UINT32 L1_Time_MIN;
extern const L1_UINT32 L1_Time_MAX;


/**
L1_TaskFunction is a pointer to a function with one input parameter of type L1_TaskArguments. The function, pointed to by L1_TaskFunction is used as an entry point to start a Task.
*/
typedef void (*L1_TaskFunction)(L1_TaskArguments Arguments);



#define L1_GLOBALID_SIZE 32

/**
L1_EntityAddress is an abstract type that represents an identifier of an Entity. L1_EntityAddress is a system wide address represented by a 32 bit data structure with the following 8bit fields: LocalEntityID, NodeID, SiteID, ClusterID. In practice at L1 we will only find EntityAdresses for Tasks en HubID and the context will allow to distinguish between them. In this context we call them L1_TaskID and L1_HubID.
*/

#if (L1_GLOBALID_SIZE == 8)
/* no node, site and cluster ids */
typedef L1_BYTE L1_TaskID;
typedef L1_BYTE L1_PortID;
typedef L1_BYTE L1_HubID;
#elif (L1_GLOBALID_SIZE == 16)
/* no site and cluster ids */
typedef L1_UINT16 L1_TaskID;
typedef L1_UINT16 L1_PortID;
typedef L1_UINT16 L1_HubID;
#elif (L1_GLOBALID_SIZE == 32)
/**
L1_ TaskID is a type that represents an identifier of a Task .L1_TaskID is a system wide identifier represented by a 32 bit data structure divided in the following 8bit fields: LocalTaskID, NodeID, SiteID, ClusterID.
*/
typedef L1_UINT32 L1_TaskID;
/**
L1_PortID is a type that represents an Task Input Port identifier of a Task. L1_PortID is a system wide identifier represented by a 32 bit data structure divided in the following 8bit fields: LocalTaskID, NodeID, SiteID, ClusterID.
*/
typedef L1_UINT32 L1_PortID;
/**
L1_HubID is a type that represents an identifier of a Hub on a Node. L1_HubID is a system wide identifier represented by a 32 bit datastructure divided in the following 8bit fields: LocalHubID, NodeID, SiteID, ClusterID.
*/
typedef L1_UINT32 L1_HubID;

#else
#error "invalid L1_GLOBALID_SIZE value (supported values: 8, 16, 32)"
#endif /* L1_GLOBALID_SIZE == 8, 16, 32 */

#if (L1_GLOBALID_SIZE == 8)
/* correct??, but not used */
/* #define L1_GLOBALID_MASK 0xFFU */
#elif (L1_GLOBALID_SIZE == 16)
#ifdef L1_WIDEIDS
#ifdef MP
#error "MP and use of wide ids require L1_GLOBALID_SIZE of >= 32"
#else
#define L1_GLOBALID_MASK 0x0000U
#endif /* MP */
#else /* L1_WIDEIDS */
#define L1_GLOBALID_MASK 0xFF00U
#endif /* L1_WIDEIDS */
#elif (L1_GLOBALID_SIZE == 32)
#ifdef L1_WIDEIDS
#define L1_GLOBALID_MASK 0xFFFF0000U
#else
#define L1_GLOBALID_MASK 0xFFFFFF00U
#endif /* L1_WIDEIDS */
#endif /* L1_GLOBALID_SIZE == 8, 16, 32 */


/**
This enumerates the different service identifiers available in OpenComRTOS.
*/
typedef enum
{
    /**
    Service identifier for starting a task
    */
    L1_SID_START_TASK,
    /**
    Service identifier for suspension of a task
    */
    L1_SID_SUSPEND_TASK,
    /**
    Service identifier for resumption of a task
    */
    L1_SID_RESUME_TASK,
    /**
    Service identifier for stopping a task
    */
    L1_SID_STOP_TASK,
#ifdef ASYNC_SERVICES
    /**
    wait for packet, local service
    */
    L1_SID_ANY_PACKET,
#endif /* ASYNC_SERVICES */
    /**
    Service identifier for putting a task temporarily in waiting state (timeout).
    */
    L1_SID_WAIT_TASK,
    /**
    Service identifier for notifying the kernel of a timer expiry, i.e. timeout event (typically only used by timer HW ISR).
    */
    L1_SID_AWAKE_TASK,
#ifdef MP
    /**
    Service identifier for returning from a service request.
    */
    L1_SID_RETURN,
#if 0
    , L1_SID_YIELD_TASK
#endif /* 0 */
#ifndef ASYNC_SERVICES
    /**
    Service identifier for receiving any packet (only used for WaitForPacket).
    */
    L1_SID_ANY_PACKET, /* temp, as used by Tx Driver */
#endif /* ! ASYNC_SERVICES */
#endif /* MP */
    /**
    Service identifier for sending an L1_Packet to a Hub (also referred to as putting). The type of Hub gets encoded according to the enumeration L1_ServiceType. \sa L1_ServiceType.
    */
    L1_SID_SEND_TO_HUB,
    /**
    Service identifier for receiving an L1_Packet from a Hub (also referred to as getting). The type of Hub gets encoded according to the enumeration L1_ServiceType. \sa L1_ServiceType.
    */
    L1_SID_RECEIVE_FROM_HUB,
    /**
    Service identifier to control the Hub.
    \sa L1_HubControlType
    */
    L1_SID_IOCTL_HUB
#ifdef L1_PRIO_INHERITANCE
#ifdef MP
    /**
    Service identifier to boost the priority of a Task. Used to boost the priority of a Task in distributed systems.
    \warning This is only used by the Kernel iteself, it is not meant to be used by applications.
    */
    , L1_CHANGE_PRIORITY /* for priority inheritance */
    /**
    Service identifier to boost the priority of a Packet. Used to boost the priority of the Request Packet of a Task in distributed systems.
    \warning This is only used by the Kernel iteself, it is not meant to be used by applications.
    */
    , L1_SID_CHANGE_PACKET_PRIORITY /* Changes the priority of a Packet */
#endif /* MP */
#endif /* L1_PRIO_INHERITANCE */
} L1_ServiceID;


/**
 * This array contains the human readable version of the IDs defined in L1_ServiceID.
 */
extern const char * L1_tracer_ServiceId2Name[];





/**
 * \internal \ingroup OCR_Hub
 * L1_ServiceType is an enumeration type used to identify the L1-Services, provided by the Kernel.
 */
typedef enum
{
    /**
    Service identifier for a generic service.
    */
    L1_SERVICE, /* needed as or-ed with L1_ServiceID in ServiceID */
    /**
    Service identifier for an event.
    */
    L1_EVENT,
    /**
    Service identifier for a semaphore.
    */
    L1_SEMAPHORE,
    /**
    Service identifier for a port.
    */
    L1_PORT,
    /**
    Service identifier for a resource.
    */
    L1_RESOURCE,
    /**
    Service identifier for a FIFO buffer.
    */
    L1_FIFO,
    /**
    Service identifier for a packet pool.
    */
    L1_PACKETPOOL,
    /**
    Service identifier for a memory pool.
    */
    L1_MEMORYPOOL,
    /**
     * Service identifier for a black board hub.
     */
    L1_BLACKBOARD,
    /**
     * Service identifier for a data event hub.
     */
    L1_DATAEVENT,
  /**
     * Identifies this service as being a device driver hub.
     * @warning This does not imply a specific device driver, it is used by all device driver hubs!
     */
    L1_DEVICE_DRIVER
} L1_ServiceType;

/**
 * \internal  \ingroup OCR_Hub
 * This enumeration lists all IO Control Messages that can be sent to a Hub.
 */
typedef enum
{
    /**
    IO Control Message to initialise a Hub. This is used by the Kernel when initialising the Hubs.
    */
    L1_IOCTL_HUB_OPEN, /* initialization */
    /**
     * Signals the driver should initialise. This message is sent to all hubs where
     * the field HubType is L1_DEVICE_DRIVER_HUB, when the Kernel Task starts. At
     * this point interrupts can already be handled.
     */
    L1_IOCTL_HUB_DRIVER_INIT,
    /**
     * This is the offset to be used to define hub specific IOCTL's.
     */
    L1_IOCTL_HUB_OFFSET
} L1_HubControlType;


/**
L1_Status is an enumeration type used to specify the result of a service request (success, failure, etc.).
*/
typedef enum
{
    /**
    Return code for a successful request
    */
    RC_OK,
    /**
    Return code for a failed request
    */
    RC_FAIL,
//#ifdef WT_SERVICES
    /**
    Return code for a failed request after the timeout expired.
    */
    RC_TO
//#endif /* WT_SERVICES */
} L1_Status;

#endif /* __L1_types_h__ */
