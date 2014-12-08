/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2008
 * www.Altreonic.com
 * Module name: ($Path/$Filename)
 * Synopsis: Layer 1 kernel data.
 *
 * $LastChangedDate: 2014-02-27 18:01:59 +0100 (Thu, 27 Feb 2014) $
 * $Revision: 4196 $
 * $LastChangedBy: marina.gutierrez $
 *******************************************************************************/

#ifndef __L1_kernel_data_h__
#define __L1_kernel_data_h__

#include <L1_types.h>
#include <kernel/L1_list_api.h>
#include <kernel/L1_task_api.h>
#include <kernel/L1_port_api.h>
#include <kernel/L1_hub_api.h>




#if defined(XMOS) || defined (MCC)
	/* This block is specific to the XMOS port of OpenComRTOS */
	extern L1_TaskControlRecord * L1_TaskControlBlock; /* Points to an array with L1_NODE_NUMBER_OF_TASKS elements */
	extern L1_InputPort * L1_TaskInputPorts; /* Points to an array with L1_NODE_NUMBER_OF_TASKS elements */
	extern L1_Hub * L1_LocalHubs; /* Points to an array with L1_NODE_NUMBER_OF_HUBS elements*/
	#ifdef MP
		/**
		 * This defines the type of the callback function to use for the L1_initLinkDriver function.
		 */
		typedef void (*L1_initLinkDriver_CB)(void);

	#endif /* MP */


	#ifdef MCC
		/* Kernel Packet-Pool */
		extern  const unsigned long L1_KernelPacketPoolID;
		extern void * linkPort_RoutingTable[];
		#ifdef MP
			//extern const unsigned long L1_RxPacketPoolID; /* ID of the global RX-PacketPool. */
			extern L1_TaskControlRecord * L1_RoutingTable[]; /* Points to an array with L1_NUMBER_OF_NODES elements*/
		#endif
	#endif

	/**
	 * Declaring global variables necessary in order to use more than one core of a multi core XMOS chip
	 */
	#if defined(XMOS)
		extern L1_UINT32 L1_PRESENT_NODE_ID;
		/* Kernel Packet-Pool */
		extern  L1_HubID L1_KernelPacketPoolID;
		extern void ** linkPort_RoutingTable;

		#ifdef MP
			/**
			 * Global variable containing the callback to the L1_initLinkDriver function to use.
			 */
			extern L1_initLinkDriver_CB L1_initLinkDriver;
			extern L1_HubID L1_RxPacketPoolID; /* ID of the global RX-PacketPool. */
			extern L1_TaskControlRecord ** L1_RoutingTable; /* Points to an array with L1_NUMBER_OF_NODES elements*/
		#endif

	#endif

	#define L1_KernelPacketPool L1_PacketPool_State(L1_id2localhub(L1_KernelPacketPoolID))

	/*
	 * Global variable to indicate the location of the IsrStack.
	 * It points to the last element of the stack!
	 */
	extern L1_BYTE * L1_hal_IsrStackEndPtr;
	/*
	 * Size of the IsrStack in Byte.
	 */
	extern L1_UINT32 L1_hal_IsrStackSize;

	#ifdef L1_PRIO_INHERITANCE
		/*
		 * Determines how many Resources this particular Node uses. It is used in the initialisation of the L1_FreeKeyList which is used to implement Priority Inheritance purposes.
		 */
		extern L1_UINT32 L1_NumberOfUsedResources;
		/*
		 * These are the preallocated elements that get put in the L1_FreeKeyList.
		 */
		extern L1_KeyedListElement * L1_KeyListElements;
	#endif /* L1_PRIO_INHERITANCE */



#else /* XMOS */



extern L1_TaskControlRecord L1_TaskControlBlock[/*L1_NODE_NUMBER_OF_TASKS*/];
extern L1_InputPort L1_TaskInputPorts[/*L1_NODE_NUMBER_OF_TASKS*/];
extern L1_Hub L1_LocalHubs[/*L1_NODE_NUMBER_OF_HUBS*/];
#ifdef MP
extern L1_TaskControlRecord *L1_RoutingTable[/* L1_NUMBER_OF_NODES */];
/**
 *  Forward declaration of link driver initialization function given in L1_node_config.c
 */
extern void L1_initLinkDriver(void);

#endif /* MP */

/* Kernel Packet-Pool */
extern const L1_HubID L1_KernelPacketPoolID;
#define L1_KernelPacketPool L1_PacketPool_State(L1_id2localhub(L1_KernelPacketPoolID))

/*
 * Global variable to indicate the location of the IsrStack.
 * It points to the last element of the stack!
 */
extern L1_BYTE * L1_hal_IsrStackEndPtr;
/*
 * Size of the IsrStack in Byte.
 */
extern L1_UINT32 L1_hal_IsrStackSize;

extern void * linkPort_RoutingTable[];

#ifdef L1_PRIO_INHERITANCE
/*
 * Determines how many Resources this particular Node uses. It is used in the initialisation of the L1_FreeKeyList which is used to implement Priority Inheritance purposes.
 */
extern L1_UINT32 L1_NumberOfUsedResources;
/*
 * These are the preallocated elements that get put in the L1_FreeKeyList.
 */
extern L1_KeyedListElement L1_KeyListElements[];
#endif /* L1_PRIO_INHERITANCE */


#endif /* XMOS */


#if 0
//#ifdef WT_SERVICES
extern void L1_initTimerFreeList (void);
//#endif /* WT_SERVICES */
#endif /* 0 */

/**
 * This is a forward declaration of the idle task given in the user's project.
 * It is the lowest priority task in the system. Usually implemented as an infinite loop that ignores
 * the arguments received where performance metrics may be performed.
 *
 * @param Arguments function implementation dependent.
 *
 */
extern void L1_idleTask(L1_TaskArguments Arguments);

/**
 * This function initializes the system timer, initializes the link drivers in MP mode, and starts the Kernel loop function.
 *
 * @param Arguments The arguments passed to this function are ignored.
 *
 * \ingroup x
 */
extern void L1_KernelEntryPoint(L1_TaskArguments Arguments);

#define L1_KernelTaskCR (&(L1_TaskControlBlock[0]))
#define L1_KernelTaskID L1_KernelTaskCR->TaskID

/*
 * All requests are passed to  L1_ Kernel using Packets, delivered to  L1_ Kernel Port.
 */
#define L1_KernelInputPort (L1_TaskInputPorts[0])
#define L1_KernelInputPortID ((L1_PortID) L1_KernelTaskCR->TaskID)

extern L1_TaskControlRecord *L1_CurrentTaskCR;

/*
 * L1_ISRNesting indicates nesting of current HW interruption.
 */
extern L1_UINT16 L1_ISRNesting;

/**
 * This counter is to be incremented every time a new packet
 * gets created to be inserted into the KernelInputPort.
 */
extern L1_UINT16 NodePacketCounter;

#endif /* __L1_kernel_data_h__ */
