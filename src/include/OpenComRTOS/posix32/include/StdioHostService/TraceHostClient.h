/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2008
 * www.Altreonic.com
 * Module name: StdioHostClient.h ($Path/$Filename)
 * Synopsis:
 *
 * $LastChangedDate: 2010-06-17 15:41:42 +0200 (Thu, 17 Jun 2010) $
 * $Revision: 1582 $
 * $LastChangedBy: bernhard.sputh $
 *******************************************************************************/

#ifndef TRACE_HOST_CLIENT_HEADER
#define TRACE_HOST_CLIENT_HEADER

#include <L1_types.h>

/**
 * Temporarily stops the tracing and meanwhile sends the content
 * of the trace buffer to the StdioHostServer specified in the
 * parameter ServerInputPort.
 *
 * @param ServerInputPort address of the Stdio Host Server Input port.
 *
 * @return L1_Status:
 *  - RC_OK: Dumping the trace buffer was completed successfully.
 *  - RC_FAIL: Operation failed.
 */
L1_Status DumpTraceBuffer_W(L1_HubID ServerInputPort);

#endif /*STDIO_HOST_CLIENT_HEADER*/
