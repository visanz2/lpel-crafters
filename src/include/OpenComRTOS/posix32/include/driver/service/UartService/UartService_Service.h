/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2013
 * www.Altreonic.com
 * Module name: UART_Client.h ($Path/$Filename)
 * Synopsis: UART-Service Version Number.
 *
 * $LastChangedDate: 2013-02-03 20:10:21 +0100 (Sun, 03 Feb 2013) $
 * $Revision: 3377 $
 * $LastChangedBy: bernhard.sputh $
 *******************************************************************************/

#ifndef _UART_SERVICE_
#define _UART_SERVICE_

/**
 * The L1_UINT32 value of is formatted the following way:
 * - MSByte: Major Version
 * - 23--16: Minor Version
 * - 15--8 : Release status:
 *          - 0: Alpha
 *          - 1: Beta
 *          - 2: Release Candidate
 *          - 3: Public Release
 * - LSByte: Patch-level
 *
 */
#define UART_VERSION 0x01010100

#endif
