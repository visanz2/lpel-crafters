/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2008
 * www.Altreonic.com
 * Module name: ($HeadURL: http://dev.altreonic.com/projects/OpenComRTOS/svn/OpenComRTOS/branches/1.6/include/kernel/L1_debug_api.h $)
 * Synopsis: Platform independent switchable debug macros and functions.
 *
 * $LastChangedDate: 2013-05-28 17:15:36 +0200 (Tue, 28 May 2013) $
 * $Revision: 3785 $
 * $LastChangedBy: bernhard.sputh $
 *******************************************************************************/

#ifndef __L1_debug_h__
#define __L1_debug_h__

#include <L1_kernel_hal_types.h>

#ifndef L1_DEBUG

#ifdef L1_DBG_OS_ALLOW_ASSERT
#undef L1_DBG_OS_ALLOW_ASSERT
#endif /* L1_DBG_OS_ALLOW_ASSERT */


#ifndef L1_DBG_API_DISABLE_ASSERT
#define L1_DBG_API_DISABLE_ASSERT
#endif /* L1_DBG_API_DISABLE_ASSERT */

#ifndef L1_DBG_APP_DISABLE_ASSERT
#define L1_DBG_APP_DISABLE_ASSERT
#endif /* L1_DBG_APP_DISABLE_ASSERT */

#ifndef L1_DBG_PLATFORM_DISABLE_ASSERT
#define L1_DBG_PLATFORM_DISABLE_ASSERT
#endif /* L1_DBG_PLATFORM_DISABLE_ASSERT */


#else

extern unsigned int L1_Debug_NumberOfTasks;
extern unsigned int L1_Debug_NumberOfHubs;

extern void L1_Debug_PlatformAssert (int expression, char *file, int line);

#endif /* L1_DEBUG */

#ifdef L1_DBG_OS_ALLOW_ASSERT
#define L1_DBG_OS_ASSERT(a) L1_Debug_PlatformAssert((a), __FILE__, __LINE__);
#else
#define L1_DBG_OS_ASSERT(a)
#endif /* L1_DBG_OS_ALLOW_ASSERT */


#ifdef L1_DBG_LIST_DISABLE_ASSERT
#define L1_DBG_LIST_ASSERT(a)
#else
#define L1_DBG_LIST_ASSERT(a) L1_DBG_OS_ASSERT((a))
#endif /* L1_DBG_LIST_DISABLE_ASSERT */


#ifdef L1_DBG_API_DISABLE_ASSERT
#define L1_DBG_API_ASSERT(a)
#else
#define L1_DBG_API_ASSERT(a) L1_DBG_OS_ASSERT((a))
#endif /* L1_DBG_API_DISABLE_ASSERT */


#ifdef  L1_DBG_APP_DISABLE_ASSERT
#define L1_DBG_APP_ASSERT(a)
#else
#define L1_DBG_APP_ASSERT(a) L1_DBG_OS_ASSERT((a))
#endif /* L1_DBG_APP_DISABLE_ASSERT */


#ifdef  L1_DBG_PLATFORM_DISABLE_ASSERT
#define L1_DBG_PLATFORM_ASSERT(a)
#else
#define L1_DBG_PLATFORM_ASSERT(a) L1_DBG_OS_ASSERT((a))
#endif /* L1_DBG_PLATFORM_DISABLE_ASSERT */



#endif /* __L1_debug_h__ */
