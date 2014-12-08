/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2008
 * www.Altreonic.com
 * Module name: UART_Client.h ($Path/$Filename)
 * Synopsis: Uart Host Service Types.
 *
 * $LastChangedDate: 2013-02-22 10:34:23 +0100 (Fri, 22 Feb 2013) $
 * $Revision: 3477 $
 * $LastChangedBy: radu.vadana $
 *******************************************************************************/

#ifndef _UART_TYPES_H_
#define _UART_TYPES_H_

#include <L1_api.h>
#include <L1_types.h>
#include <L1_hal_types.h>

#include <driver/class/L1_Drv_Uart.h>



/**
 * Defines the direction of a Port.
 * \ingroup UART_SERVICE
 */
typedef enum
{
    /**
     *
     * Port is only open for reception (RX).
     */
    UART_SERVICE_PORT_DIRECTION_RX = 1,
    /**
     * Port is only open for reception (TX).
     */
    UART_SERVICE_PORT_DIRECTION_TX = 2,
    /**
     * Port is open for RX and TX.
     */
    UART_SERVICE_PORT_DIRECTION_RXTX = 3
}UartService_PortDirection;

/**
 * This structure represents a handle to an UART port. This gets returned by the open interaction.
 * \ingroup UART_SERVICE
 * \internal
 */
typedef struct
{

    /**
     * \internal
     * The ID of the Event-Hub that will be signaled whenever the ISR has added
     * data to the RX-RingBuffer.
     *
     */
     L1_HubID rxEventID;
     /**
      * \internal
      * The ID of the Port-Hub that the server will send replies to for RX-Operations.
      */
     L1_HubID rxReplyPortID;
    /**
     * \internal
     * The ID of the Event-Hub that will be signaled whenever the ISR has taken
     * out data from the TX-RingBuffer.
     */
    L1_HubID txEventID;
    /**
     * \internal
     * The ID of the Port-Hub that the server will send replies to for TX-Operations.
     */
    L1_HubID txReplyPortID;
    /**
     * \internal
     * The direction(s) the Port has been opened for.
     */
    L1_UINT32 direction;
#ifndef MP
    /**
     * Pointer to the "L1_Drv_UART" which represents the underlying device..
     */
    L1_Drv_UART * pUart;
    /**
     * Used to interface to the UART-Driver.
     */
    L1_Drv_UART_Channel * pChannel;
    /**
     * Pointer to the events that should be raised by the ISR.
     */
    L1_UartEvents * pUartEvents;
#endif /* !MP */
}UartService_PortHandle;


/**
 * UART Status codes. Used Internally and returned to the user of the UART-Client API.
 * \ingroup UART_SERVICE
 */
typedef enum
{
    /**
     * The desired operation was performed successfully.
     */
    UART_SERVICE_RC_OK   = 0,
    /**
     * There was a general failure when performing the operation. Typically, this means that invalid pointers (NULL) were passed.
     */
	UART_SERVICE_RC_FAIL = 1,
	/**
	 * The chosen UART-Driver does not support the specified port-mode.
	 */
	UART_SERVICE_RC_FAIL_INVALID_PORT_MODE = 2,
	/**
	 * The chosen UART-Driver does not support the specified flow control mode.
	 */
	UART_SERVICE_RC_FAIL_INVALID_FLOW_CONTROL = 3,
	/**
	 * The chosen UART-Driver does not support the specified parity setting.
	 */
	UART_SERVICE_RC_FAIL_INVALID_PARITY = 4,
	/**
	 * The chosen UART-Driver does not support the specified word length (bit per byte).
	 */
	UART_SERVICE_RC_FAIL_INVALID_WORD_LENGTH = 5,
	/**
	 * The chosen UART-Driver does not support the specified number of stop bits.
	 */
	UART_SERVICE_RC_FAIL_INVALID_NBR_OF_STOP_BITS = 6,
	/**
	 * The chosen UART-Driver does not support the specified baudrate.
	 */
	UART_SERVICE_RC_FAIL_INVALID_BAUDRATE = 7,
	/**
     * The TX-FIFO of the UART-Server is full and can thus at the moment not accept any more data. The message the user tried to sent was partially copied to the TX-FIFO.
     */
	UART_SERVICE_RC_TX_FIFO_FULL = 8,
    /**
     * The RX-FIFO is currently empty, thus one cannot read any more data from it than the data that was copied already, if any.
     */
	UART_SERVICE_RC_RX_FIFO_EMPTY = 9,
	/**
	 * The port the caller would like to operate on is not ready, i.e. not open.
	 */
	UART_SERVICE_RC_FAIL_PORT_NOT_OPEN = 10,
	/**
	 * If the serial port the user tries to open is already open.
	 */
	UART_SERVICE_RC_FAIL_PORT_ALREADY_OPEN = 11,
	/**
	 * There is no port with the specified number.
	 */
	UART_SERVICE_RC_FAIL_INVALID_PORT = 12
}UartService_Status;


#endif
