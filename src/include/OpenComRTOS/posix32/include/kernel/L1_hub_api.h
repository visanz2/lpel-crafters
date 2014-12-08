/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2008
 * www.Altreonic.com
 * Module name: ($Path/$Filename)
 * Synopsis: Generic Hub API
 *
 * $LastChangedDate: 2013-11-06 22:36:50 +0100 (Wed, 06 Nov 2013) $
 * $Revision: 4094 $
 * $LastChangedBy: bernhard.sputh $
 *******************************************************************************/

#ifndef __L1_hub_api_h__
#define __L1_hub_api_h__

#include <kernel/hubs/L1_hub.h>
#include <kernel/hubs/L1_hub_black_board.h>
#include <kernel/hubs/L1_hub_event.h>
#include <kernel/hubs/L1_hub_fifo.h>
#include <kernel/hubs/L1_hub_memory_pool.h>
#include <kernel/hubs/L1_hub_packet_pool.h>
#include <kernel/hubs/L1_hub_port.h>
#include <kernel/hubs/L1_hub_resource.h>
#include <kernel/hubs/L1_hub_semaphore.h>
#include <kernel/hubs/L1_hub_data_event.h>

#include <kernel/L1_list_api.h>
#include <kernel/L1_packet_api.h>
#include <kernel/L1_memorypool_api.h>

/* DEBUG only? */


#define L1_isSendPacket(p)  ((((p)->ServiceID) % 256) == L1_SID_SEND_TO_HUB)
#define L1_isControlPacket(p)  ((((p)->ServiceID) % 256) == L1_SID_IOCTL_HUB)


#include<kernel/L1_kernel_data.h>

#if (L1_GLOBALID_SIZE == 8)
#define L1_isLocalHubID(h)  (1)
#define L1_id2localhub(h)   (&L1_LocalHubs[(h)])
#define L1_HubNodeID(h)     (0)
#else /* L1_GLOBALID_SIZE == 8 */
/* can be optimized for L1_GLOBALID_SIZE == 16 && L1_WIDEIDS */
#define L1_isLocalHubID(h)  (((h) & L1_GLOBALID_MASK) == ((L1_KernelInputPortID) & L1_GLOBALID_MASK))
#define L1_id2localhub(h)   (&L1_LocalHubs[((h) & ~L1_GLOBALID_MASK)])
#ifdef L1_WIDEIDS
#define L1_HubNodeID(h)     (((h) & L1_GLOBALID_MASK) >> 16)
#else
#define L1_HubNodeID(h)     (((h) & L1_GLOBALID_MASK) >> 8)
#endif /* L1_WIDEIDS */
#endif /* L1_GLOBALID_SIZE == 8 */




#endif /* __L1_hub_api_h__ */

