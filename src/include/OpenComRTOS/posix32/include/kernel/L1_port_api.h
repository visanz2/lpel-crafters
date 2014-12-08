/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2008
 * www.Altreonic.com
 * Module name: ($Path/$Filename) 
 * Synopsis: Port API
 * 
 * $LastChangedDate: 2013-10-22 11:07:28 +0200 (Tue, 22 Oct 2013) $
 * $Revision: 4086 $
 * $LastChangedBy: bernhard.sputh $
 *******************************************************************************/

#ifndef __L1_port_api_h__
#define __L1_port_api_h__

#include <kernel/L1_list_api.h>
typedef struct _struct_L1_Port_ {
    L1_List WaitingList;
}L1_InputPort;//, L1_Port;

#if (L1_GLOBALID_SIZE == 8)
#define L1_isLocalPortID(p)  (1)
#define L1_id2localport(p)   (&L1_LocalPorts[(p)])
#define L1_PortNodeID(p)     (0)
#else /* L1_GLOBALID_SIZE == 8 */
/* can be optimized for L1_GLOBALID_SIZE == 16 && L1_WIDEIDS */
#define L1_isLocalPortID(p)  (((p) & L1_GLOBALID_MASK) == ((L1_KernelInputPortID) & L1_GLOBALID_MASK))
#define L1_id2localport(p)   (&L1_LocalPorts[((p) & ~L1_GLOBALID_MASK)])
#ifdef L1_WIDEIDS
#define L1_PortNodeID(p)     (((p) & L1_GLOBALID_MASK) >> 16)
#else
#define L1_PortNodeID(p)     (((p) & L1_GLOBALID_MASK) >> 8)
#endif /* L1_WIDEIDS */
#endif /* L1_GLOBALID_SIZE == 8 */

#endif /* __L1_port_api_h__ */
