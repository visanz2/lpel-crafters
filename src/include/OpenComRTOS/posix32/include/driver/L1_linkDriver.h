#ifndef L1_LINKDRIVER_H_
#define L1_LINKDRIVER_H_

#ifdef MP

#include <driver/L1_xfer_packet_api.h>
#include <kernel/L1_memory_api.h>

void L1_injectXferPacketIntoKernel_IsrSafe(L1_XferPacket *rxPacket);
void L1_injectXferPacketIntoKernel(L1_XferPacket *rxPacket);

#define L1_injectXferPacketIntoKernel_NestedIsrSafe(rxPacket) L1_injectXferPacketIntoKernel(rxPacket)


/**
 * 
 * @param *txDriverSend: Pointer to the function which sends a packet over the link. 
 * 
 * @return This function should not return if there are no problems, otherwise it returns L1_FALSE.
 * @deprecated This function is deprecated, and should no longer be used. Instead use the function L1_txDriverLoop2.
 * @warning This function allocates a complete L1_XferPacket on the stack, it is the responsibiliyt of the user to ensure that there is enough space on the stack.
 */ 
L1_BOOL L1_txDriverLoop(L1_TxDriverSendPacket txDriverSendPacket);

/**
 * This function represents a generic Link Driver Task, which will wait for an
 * L1_Packet to be transferred and then converts it into an L1_Packet before
 * calling the callback function txDriverSendPacket.
 *
 * @param txDriverSendPacket The function to call when there a Packet to be transferred.
 * @param txXferPacket Pointer to the L1_XferPacket to store the transformed L1_Packet in. This must not be NULL.
 * @return This function should not return if there are no problems, otherwise it returns RC_FAIL.
 */
L1_Status L1_txDriverLoop2(L1_TxDriverSendPacket txDriverSendPacket, L1_XferPacket *txXferPacket);

#endif /*MP*/

#endif /*L1_LINKDRIVER_H_*/
