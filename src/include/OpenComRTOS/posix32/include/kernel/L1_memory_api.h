/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2008
 * www.Altreonic.com
 * Module name: ($Path/$Filename)
 * Synopsis: Declares Memory Pool API.
 *
 * $LastChangedDate: 2014-03-25 15:41:39 +0100 (Tue, 25 Mar 2014) $
 * $Revision: 4214 $
 * $LastChangedBy: bernhard.sputh $
 *******************************************************************************/

/* to be moved to L1_hub_api.h */

#ifndef __L1_memory_api_h__
#define __L1_memory_api_h__

#include <kernel/L1_debug_api.h>
#include <driver/L1_xfer_packet_api.h>
#include <kernel/L1_list_api.h>
#include <L1_types.h>

#define MEMORY_BLOCK_MAGIC_NUMBER 0x4312


typedef void *VOIDPTR;
#define to_VOIDPTR(p)   (p)
#define from_VOIDPTR(p) (p)


/**
 * This structure represents the header part of a memory block.
 */
typedef struct _struct_L1_MemoryBlockHeader_
{
    /**
     * linkage in free list, may overlap with other fields
     */
    L1_ListElement ListElement;
#ifdef L1_DEBUG
    /**
     *  Magic number to check that a block, i.e. pointer to first data,
     *  is given in e.g. L1_MoveMemoryBlock_W Alt: use is_Allocated,
     *  but should be some larger number for safety.
     */
    L1_UINT16 Magic;
    /*
     * The ID of the Hub from where this block was allocated from.
     */
    L1_HubID MemID;
#endif /* L1_DEBUG */
    /**
     * The requested size of this block, can be different from the MemPool
     * Blocksize.
     */
    L1_UINT32 BlockSize;
#if 0
    /**
     * The number of the already written, e.g. already copied, elements for use
     * with MoveData Alt: number of fields still to fill in, i.e. move/copy.
     */
    L1_UINT32 FilledSize;
#endif /* 0 */
    /**
     * The number of bytes currently being in use. This is important for the MemoryBlockQueue users.
     */
    L1_UINT32 UsedBytes;

} MemoryBlockHeader; /* needed as a separate struct? */

/* block = data pointer preceded with administrative header data */
/**
 * This structure represents a memory block that can be allocated form a
 * MemoryPool Hub. It consists of a header and a data part.
 */
typedef struct _struct_L1_MemoryBlock_
{
    /**
     * The header of the MemoryBlock
     */
    MemoryBlockHeader Header;
    /**
     * Payload, the user pointer, i.e. user memory space the size is determined
     * by the memory pool parameters and size request at allocation time.
     */
    L1_BYTE * Data;
} L1_MemoryBlock;


#ifdef MP

/**
 * This declares the signature of a transmit function for any LinkDriver. This
 * function will transfer the L1_Xferpacket passed to it to its communication
 * partner.
 *
 * @param xferPacket pointer to the L1_XferPacket to be transmitted.
 * @param packetSize, the number of bytes the xferPacket has.
 *
 * @return L1_BOOL
 *      - L1_TRUE when transmission was successful
 *      - L1_FALSE otherwise.
 *
 * */
typedef L1_BOOL (*L1_TxDriverSendPacket)(L1_XferPacket *xferPacket,
                                         L1_UINT32 packetSize);

#endif /* MP */

#endif /* __L1_memory_h__ */
