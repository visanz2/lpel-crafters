/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2008
 * www.Altreonic.com
 * Module name: ($Path/$Filename)
 * Synopsis: This module defines  platform dependent data types involved into
 *   OpenComRTOS Layer L1_ API. Definitions made in this file are part of
 *   a layer that abstracts OpenComRTOS Layer L1_ from POSIX32 environment.
 *   Such way this file plays a role of a PLATFORM ABSTRACTION LAYER.
 *
 * $LastChangedDate: 2013-04-18 16:29:24 +0200 (Thu, 18 Apr 2013) $
 * $Revision: 3699 $
 * $LastChangedBy: bernhard.sputh $
 *******************************************************************************/

/*
 * Changes:
 * - 17.01.2012, BSP: Added the types L1_UINT8 and L1_INT8.
 *
 */

#ifndef __L1_hal_types_h__
#define __L1_hal_types_h__

#include<stdint.h>



typedef unsigned char L1_BOOL; /* int best for code size and performance; char may be better for struct packing  */
#define L1_FALSE 0U
#define L1_TRUE  1U

typedef unsigned char L1_BYTE;

typedef char          L1_INT8;
typedef unsigned char L1_UINT8;

typedef long int L1_INT32;
typedef short int L1_INT16;

typedef unsigned long L1_UINT32;
typedef unsigned short L1_UINT16;

typedef int64_t  L1_INT64;
typedef uint64_t L1_UINT64;

/**
 * The necessary alignment of data for this CPU in Byte, used for the definition of the L1_Packet datatype.
 */
#define L1_DATA_ALIGNMENT 4



/* CPU status register */
/* not used */
typedef L1_UINT32 L1_INTERRUPT_STATUS;

typedef struct _struct_L1_POSIX32_TASK_CONTEXT_ L1_TaskContext;

/*
 * This has been moved here because it is required within the L1_node_config.c
 * file to setup additional ISRs there.
 */
typedef void *(*posix_start_routine_t)(void *arg);


/* defined in stdio.h */
#ifndef NULL
#define NULL ((void *) 0)
#endif

#endif /* __L1_hal_types_h__ */
