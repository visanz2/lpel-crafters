/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2008
 * www.Altreonic.com
 * Module name: ($Path/$Filename)
 * Synopsis: This header file contains the xfer version of the packet to
 * transfer between nodes, first use is in the MicroBlaze Uartlite
 * implementation.
 *
 * $LastChangedDate: 2013-06-13 13:16:12 +0200 (Thu, 13 Jun 2013) $
 * $Revision: 3863 $
 * $LastChangedBy: antonio.ramos $
 *******************************************************************************/

#ifdef MP

#ifndef L1_XFER_PACKET_API_H_
#define L1_XFER_PACKET_API_H_

#include <kernel/L1_packet_api.h>
#include <L1_types.h>

/**
 * Represents the header of an XferPacket.
 */
typedef struct _struct_L1_XferPacketHeader{
    L1_UINT32 datasize;
    L1_UINT32 serviceid;
    L1_UINT32 priority;
    L1_UINT32 taskid;
    L1_UINT32 portid;
    L1_UINT32 timeout;
    L1_UINT32 status; /* wablift? (could be 16 bit) */
    L1_UINT32 sequencenumber;
} L1_XferPacketHeader;

/**
 * This is the size of the header field, in byte, of an XFER data packet.
 * It does not contain the size of the field data.
 */
#define L1_XFER_PACKET_HEADER_SIZE sizeof(L1_XferPacketHeader)

/**
 * This is the complete size of an L1_UartXferPacket
 */
#define L1_XFER_PACKET_SIZE  (L1_XFER_PACKET_HEADER_SIZE + L1_PACKET_DATA_SIZE)

/* Value representing infinite timeouts in the XferPacket */
#define XFER_INFINITE_TIMEOUT 0xFFFFFFFEU

/**
 * Represents an L1_Packet that can be transferred over a Link.
 */
typedef struct _struct_L1_XferPacket {
    L1_UINT32 datasize;
    /* should have no gaps */
    L1_UINT32 serviceid;
    L1_UINT32 priority;
    L1_UINT32 taskid;
    L1_UINT32 portid;
    L1_UINT32 timeout;
    L1_UINT32 status;
    L1_UINT32 sequencenumber;
    L1_BYTE   data[L1_PACKET_DATA_SIZE];
} L1_XferPacket;





typedef L1_XferPacket L1_UartXferPacket __attribute__((deprecated));

/**
 * This function copies a packet into a transfer packet. It sets the data to network byte order and copies all the relevant fields.
 *
 * @param xferPacket Pointer to the transfer packet to which the packet will be copied.
 * @param Packet Pointer to the packet to be copied to the transfer packet pointer.
 *
 * \ingroup x
 */
void L1_copyToXferPacket(L1_XferPacket *xferPacket, L1_Packet *Packet);

/**
 * This function copies a transfer packet into a packet. It receives data in network byte order and translates it to host byte order and copies all the relevant fields.
 *
 * @param Packet Pointer to the packet to which the transfer packet will be copied.
 * @param xferPacket Pointer to the transfer packet to be copied to the packet pointer.
 *
 * \ingroup x
 */
void L1_copyFromXferPacket(L1_Packet *Packet, L1_XferPacket *xferPacket);


#endif /*L1_XFER_PACKET_API_H_*/

#endif /*MP*/
