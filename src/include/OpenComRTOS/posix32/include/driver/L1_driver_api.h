/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2008
 * www.Altreonic.com
 * Module name: ($Path/$Filename)
 * Synopsis: This module declares and defines the functional interfaces of the
 *   driver layer OpenComRTOS Layer L1_API.
 *
 *
 * $LastChangedDate: 2013-05-08 14:44:52 +0200 (Wed, 08 May 2013) $
 * $Revision: 3740 $
 * $LastChangedBy: bernhard.sputh $
 *******************************************************************************/
#include <L1_types.h>
#include <kernel/L1_packet_api.h>


/**
 * This function retrieves an L1_Packet from the RX-PacketPool, and returns a
 * pointer to it if successful, otherwise it returns NULL.
 * @return
 *  - NULL indicates that no L1_Packet was available.
 *  - !NULL is the pointer to the L1_Packet that was retrieved.
 *
 * @warning This function calls L1_enterCriticlSection() and L1_leaveCriticalSection().
 * Using it inside ISRs might depending on the platform enable interrupts as a side
 * effect. An alternative is the function L1_getRxPacket_IsrSafe() which does not use the critical section.
 */
extern L1_Packet * L1_getRxPacket(void);

/**
 * This function retrieves an L1_Packet from the RX-PacketPool, and returns a
 * pointer to it if successful, otherwise it returns NULL.
 * @return
 *  - NULL indicates that no L1_Packet was available.
 *  - !NULL is the pointer to the L1_Packet that was retrieved.
 *
 * @warning Only use this function in situations where it is certain that no interrupts can occur,
 * for instance when you disabled interrupts already. In normal user space or when writing nested
 * Interrupts use the function L1_getRxPacket() instead.
 */
extern L1_Packet * L1_getRxPacket_IsrSafe(void);
