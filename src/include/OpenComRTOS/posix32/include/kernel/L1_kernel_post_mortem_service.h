/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2008
 * www.Altreonic.com
 * Module name: ($Path/$Filename) 
 * Synopsis: The post mortem service dumps the state of the node, in the form 
 * of a log of the last handled L1_Packets into a file.
 * 
 * $LastChangedDate: 2013-02-10 19:50:00 +0100 (Sun, 10 Feb 2013) $
 * $Revision: 3414 $
 * $LastChangedBy: bernhard.sputh $
 *******************************************************************************/

#ifndef L1_KERNEL_POST_MORTEM_SERVICE_H_
#define L1_KERNEL_POST_MORTEM_SERVICE_H_

#include<kernel/L1_packet_api.h>
#include<stdio.h>

#ifdef L1_POST_MORTEM_SERVICE
/** 
 * Specifies how many elements a L1_PacketRingBuffer contains.
 */
#ifndef L1_PACKET_LOG_LENGTH
#define L1_PACKET_LOG_LENGTH 1024
#endif /* L1_PACKET_LOG_LENGTH */
/**
 * This structure represents a ring buffer for L1_Packets.
 */
typedef struct _struct_L1_PacketLog {
    /**
     * The index of the oldest package in the array Packets.
     */
    unsigned int OldestPacket;
    /**
     * The index of the most recent package in the array Packets.
     */
    unsigned int NextPacket;
    /**
     * The total number of logged L1_Packets.
     */ 
    unsigned int NbrOfPackets;

    /**
     * This array contains all the L1_Packets stored within the ringbuffer.
     */
    L1_Packet LoggedPackets[L1_PACKET_LOG_LENGTH];
} L1_PacketLog;

/**
 * This creates a variable of type L1_PacketLog and initialises it, by setting both fields: OldestPacket and YoungestPacket to 0.
 * @param pl: Name of the L1_PacketLog structure to create.
 */
#define L1_PACKET_LOG(pl) L1_PacketLog pl = {.OldestPacket = 0, .NextPacket = 0, .NbrOfPackets=0}

/**
 * This function adds a L1_Packet to a L1_PacketLog structure, by creating a complete copy of it. 
 * If there is no free space in the log, the oldest packet gets overwritten.
 * @param pl: Pointer to the L1_PacketLog structure to add the L1_Packet to.
 * @param packet: Pointer to the L1_Packet to be added to the log. 
 * @returns 
 * - 0: If logging was successful.
 * - -1: If a NULL pointer was passed.
 */
int L1_pl_insertPacket(L1_PacketLog *pl, L1_Packet *packet);
#define L1_LOG_PACKET(pl, packet) L1_pl_insertPacket(pl, packet)

/** 
 * Specifies how many elements a L1_PacketRingBuffer contains.
 */
#ifndef L1_TASKID_LOG_LENGTH
#define L1_TASKID_LOG_LENGTH 1024
#endif /* L1_TASKID_LOG_LENGTH */

/**
 * This structure represents a log of TaskIDs in the form of a ring buffer.
 */
typedef struct _struct_L1_TaskID_Log {
    /**
     * The index of the oldest package in the array LoggedTaskIDs.
     */
    unsigned int OldestTaskID;
    /**
     * The index of the most recent package in the array LoggedTaskIDs.
     */
    unsigned int NextTaskID;
    /**
     * The total number of logged TaskIDs.
     */ 
    unsigned int NbrOfTaskIDs;
    /**
     * This array contains all TaskIDs stored within the log.
     */
    unsigned int LoggedTaskIDs[L1_TASKID_LOG_LENGTH];
} L1_TaskID_Log;

#define L1_TASKID_LOG(til) L1_TaskID_Log til = {.OldestTaskID = 0, .NextTaskID = 0, .NbrOfTaskIDs=0}

/**
 * This function adds a TaskID to a L1_TaskID_Log structure.If there is no free 
 * space in the log, the oldest packet gets overwritten.
 * @param til: Pointer to the L1_TaskID_Log structure to add the TaskID to.
 * @param TaskID: TaskID to add to the log. 
 * @returns 
 * - 0: If logging was successful.
 * - -1: If a NULL pointer was passed.
 */
int L1_til_logTaskID(L1_TaskID_Log *til, unsigned int TaskID);
#define L1_LOG_TASKID(til, packet) L1_til_logTaskID(til, packet);

/*
 * Predefined Logs which the system should perform by default
 */
extern L1_PacketLog kernelPackets;
extern L1_PacketLog returnedPackets;
extern L1_TaskID_Log contextSwitches;
#ifdef MP
extern L1_PacketLog receivedPackets; 
extern L1_PacketLog receivedAndInjectedPackets;
extern L1_PacketLog packetsToSend;
extern L1_PacketLog sentPackets;
#endif /*MP*/

extern L1_TaskID_Log SwitchToContext;

int L1_dumpPostMortemReport(char* File, int LineNumber, char* Message);
#define L1_DUMP_POST_MORTEM_REPORT(msg) L1_dumpPostMortemReport(__FILE__, __LINE__, msg);

void L1_initPostMortemReportService(void);

/**
 * @warning This function must be called when initialising the platform.
 */
#define L1_INIT_POST_MORTEM_REPORT_SERVICE L1_initPostMortemReportService(); 

#else /*DEBUG_POST_MORTEM_SERVICE*/

#define L1_PACKET_LOG(pl) {}
#define L1_LOG_PACKET(pl, packet) {}

#define L1_TASKID_LOG(til) {}
#define L1_LOG_TASKID(til, packet) {}

#define L1_DUMP_POST_MORTEM_REPORT(msg) {}
#define L1_INIT_POST_MORTEM_REPORT_SERVICE {}

#endif /*DEBUG_POST_MORTEM_SERVICE*/

#endif /*L1_KERNEL_POST_MORTEM_SERVICE_H_*/
