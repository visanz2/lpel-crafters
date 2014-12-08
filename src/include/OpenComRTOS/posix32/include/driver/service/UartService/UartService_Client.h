/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2013
 * www.Altreonic.com
 * Module name: UartService_Client.h ($Path/$Filename)
 * Synopsis: UART-Service API definition.
 *
 * $LastChangedDate: 2013-03-22 12:19:43 +0100 (Fri, 22 Mar 2013) $
 * $Revision: 3593 $
 * $LastChangedBy: bernhard.sputh $
 *******************************************************************************/


#ifndef _UartService_CLIENT_
#define _UartService_CLIENT_

#include <L1_api.h>
#include <L1_hal_types.h>
#include <L1_types.h>

#include <driver/service/UartService/UartService_Types.h>
#include <driver/service/UartService/UartService_Protocol.h>
#include <driver/service/UartService/UartService_Client.h>

/**
 * \defgroup UART_SERVICE UART-Service
 * The UART-Service is a unified API to communicate with any UART in a system.
 * The API allows to open unidirectional and bidirectional connections to a UART.
 * In case of an unidirectional connection, two Tasks can interact with an UART
 * concurrently, thus one Task may perform TX-Operations (writing) while the second
 * Task can perform RX-Operations (read).
 *
 * Before allowing a Task to communicate with a UART, the UART-Service requires the
 * Task to open a so called UART-Port-Handle. For this purpose the following functions
 * exist:
 * - \link UartService_openPortRx_W \endlink: Opens a UART-Port in RX-Direction (read).
 * - \link UartService_openPortTx_W \endlink: Opens a UART-PORT in TX-Direction (write).
 * - \link UartService_openPort_W \endlink: Opens a UART-PORT in RX- and TX-Direction (read and write).
 *
 * If a Task does not require the services of a UART-Port, it must close the UART-Port using the following functions:
 * - \link UartService_closePortRx_W \endlink: Closes a UART-Port that was opened in RX-Direction (read).
 * - \link UartService_closePortTx_W \endlink: Closes a UART-PORT that was opened in TX-Direction (write).
 * - \link UartService_closePort_W \endlink: Closes a UART-PORT that was opened in RX- and TX-Direction (read and write).
 *
 * To send data to a UART-Device, the following functions have been defined:
 * - \link UartService_writeByte_NB \endlink: Tries to write a byte to a UART-Device.
 * - \link UartService_writeBuffer_NB \endlink: Tries to write a buffer to a UART-Device.
 * - \link UartService_writeBuffer_W \endlink: Writes a buffer to a UART-Device.
 *
 * To receive data from a UART-Device, the following functions have been defined:
 * - \link UartService_readByte_NB \endlink: Tries to read a byte from a UART-Device.
 * - \link UartService_readBuffer_NB \endlink: Tries to read a buffer from a UART-Device.
 * - \link UartService_readBuffer_W \endlink: Reads a buffer from a UART-Device.
 *
 *
 *
 * The following example shows how to utilise the UART-Service to open a bidirectional UART-Port with the UART-Service named `FPGA_CH2'.
 *
\code
#include <driver/service/UartService/UartService_Client.h>

// Byte array used as the buffer for the data to be read
L1_BYTE cReadBuffer[2048];

void Task1_EP(L1_TaskArguments Arguments)
{
	// This stored the data acquired when the UART-Port was successfully opened.
    UartService_PortHandle portHandle;
    UartService_Status retVal = UART_SERVICE_RC_FAIL;

    // The number of bytes which have been actually written.
    L1_UINT32 nbrOfBytesWritten = 0;

    // The number of bytes which have been actually read.
    L1_UINT32 nbrOfBytesRead    = 0;

    L1_BYTE cMsg[3];

	// Open a a bidirectional port.
    retVal = UartService_openPort_W(FPGA_CH2, &portHandle);
    if (retVal != UART_SERVICE_RC_OK)
    {
        printf("UartService_openPort_W(FPGA_CH2) failed.\n\r");
  	  	return;
    }
    while(1)
    {
    	// Write three bytes to the UART-Device.
        retVal = UartService_writeBuffer_W(FPGA_CH2, &portHandle, cMsg, 3, &nbrOfBytesWritten);
        if ( (retVal != UART_SERVICE_RC_OK) || (nbrOfBytesWritten != 3)){
            printf("ERROR: UartService_writeBuffer_W(FPGA_CH2) failed, retVal: %x\n\r", retVal);
        }
        // Read any data from the UART-Device.
        retVal = UartService_readBuffer_NB(FPGA_CH2, &portHandle, cReadBuffer, 2048, &nbrOfBytesRead);
        if (retVal == UART_SERVICE_RC_FAIL)
        {
            printf("ERROR: UartService_readBuffer_NB(FPGA_CH2) failed\n\r");
        }
    }
}
\endcode
 */


/**
 * This function requests the Server to open a UART-Port for each specified communication direction.
 * @param UART - The UART-Port used to send the request.
 * @param direction The direction(s) to open.
 * @param pPortHandle Pointer to the variable of type UartService_PortHandle where the acquired UART-Port-Handle will be stored.
 *
 * @return UART_SERVICE_RC_OK - Operation successful.
 * @return UART_SERVICE_RC_FAIL - Operation unsuccessful.
 * @return UART_SERVICE_RC_FAIL_PORT_ALREADY_OPEN - A UART-Port with the given direction has already opened.
 * @return UART_SERVICE_RC_FAIL_INVALID_PORT_MODE - The chosen UART-Driver does not support the specified port-mode.
 * @return UART_SERVICE_RC_FAIL_INVALID_FLOW_CONTROL - The chosen UART-Driver does not support the specified flow control mode.
 * @return UART_SERVICE_RC_FAIL_INVALID_PARITY - The chosen UART-Driver does not support the specified parity setting.
 * @return UART_SERVICE_RC_FAIL_INVALID_WORD_LENGTH - The chosen UART-Driver does not support the specified word length (bit per byte).
 * @return UART_SERVICE_RC_FAIL_INVALID_NBR_OF_STOP_BITS - The chosen UART-Driver does not support the specified number of stop bits.
 * @return UART_SERVICE_RC_FAIL_INVALID_BAUDRATE - The chosen UART-Driver does not support the specified baudrate.
 * \ingroup UART_SERVICE
 */
UartService_Status UartService_openPortEx_W(L1_HubID UART, UartService_PortDirection direction, UartService_PortHandle * pPortHandle);




/**
 * This function requests the Server to open an RX- and a TX-UART-Port.
 * @param UART - The port used to send the request.
 * @param pPortHandle Pointer to the variable of type UartService_PortHandle where the acquired port-handle will be stored.
 *
 * @return UART_SERVICE_RC_OK - Operation successful.
 * @return UART_SERVICE_RC_FAIL - Operation unsuccessful.
 * @return UART_SERVICE_RC_FAIL_PORT_ALREADY_OPEN - This UART-Port has already been opened before.
 * @return UART_SERVICE_RC_FAIL_INVALID_PORT_MODE - The chosen UART-Driver does not support the specified UART-Port-Mode.
 * @return UART_SERVICE_RC_FAIL_INVALID_FLOW_CONTROL - The chosen UART-Driver does not support the specified flow control mode.
 * @return UART_SERVICE_RC_FAIL_INVALID_PARITY - The chosen UART-Driver does not support the specified parity setting.
 * @return UART_SERVICE_RC_FAIL_INVALID_WORD_LENGTH - The chosen UART-Driver does not support the specified word length (bit per byte).
 * @return UART_SERVICE_RC_FAIL_INVALID_NBR_OF_STOP_BITS - The chosen UART-Driver does not support the specified number of stop bits.
 * @return UART_SERVICE_RC_FAIL_INVALID_BAUDRATE - The chosen UART-Driver does not support the specified baudrate.
 * \ingroup UART_SERVICE
 */
static __inline__ UartService_Status UartService_openPort_W(L1_HubID UART, UartService_PortHandle * pPortHandle)
{
    return UartService_openPortEx_W(UART, UART_SERVICE_PORT_DIRECTION_RXTX, pPortHandle);
}

/**
 * This function requests the Server to open an RX-UART-Port.
 * @param UART - The port used to send the request.
 * @param pPortHandle Pointer to the variable of type UartService_PortHandle where the acquired UART-Port-Handle will be stored.
 *
 * @return UART_SERVICE_RC_OK - Operation successful.
 * @return UART_SERVICE_RC_FAIL - Operation unsuccessful.
 * @return UART_SERVICE_RC_FAIL_PORT_ALREADY_OPEN - An RX-UART-Port has already been opened before.
 * @return UART_SERVICE_RC_FAIL_INVALID_PORT_MODE - The chosen UART-Driver does not support the specified port-mode.
 * @return UART_SERVICE_RC_FAIL_INVALID_FLOW_CONTROL - The chosen UART-Driver does not support the specified flow control mode.
 * @return UART_SERVICE_RC_FAIL_INVALID_PARITY - The chosen UART-Driver does not support the specified parity setting.
 * @return UART_SERVICE_RC_FAIL_INVALID_WORD_LENGTH - The chosen UART-Driver does not support the specified word length (bit per byte).
 * @return UART_SERVICE_RC_FAIL_INVALID_NBR_OF_STOP_BITS - The chosen UART-Driver does not support the specified number of stop bits.
 * @return UART_SERVICE_RC_FAIL_INVALID_BAUDRATE - The chosen UART-Driver does not support the specified baudrate.
 * \ingroup UART_SERVICE
 */
static __inline__ UartService_Status UartService_openPortRx_W(L1_HubID UART, UartService_PortHandle * pPortHandle)
{
    return UartService_openPortEx_W(UART, UART_SERVICE_PORT_DIRECTION_RX, pPortHandle);
}

/**
 * This function requests the Server to open a TX-UART-Port.
 * @param UART - The port used to send the request.
 * @param pPortHandle Pointer to the variable of type UartService_PortHandle where the acquired UART-Port-handle will be stored.
 *
 * @return UART_SERVICE_RC_OK - Operation successful.
 * @return UART_SERVICE_RC_FAIL - Operation unsuccessful.
 * @return UART_SERVICE_RC_FAIL_PORT_ALREADY_OPEN - A TX-UART-Port has already been opened before.
 * @return UART_SERVICE_RC_FAIL_INVALID_PORT_MODE - The chosen UART-Driver does not support the specified port-mode.
 * @return UART_SERVICE_RC_FAIL_INVALID_FLOW_CONTROL - The chosen UART-Driver does not support the specified flow control mode.
 * @return UART_SERVICE_RC_FAIL_INVALID_PARITY - The chosen UART-Driver does not support the specified parity setting.
 * @return UART_SERVICE_RC_FAIL_INVALID_WORD_LENGTH - The chosen UART-Driver does not support the specified word length (bit per byte).
 * @return UART_SERVICE_RC_FAIL_INVALID_NBR_OF_STOP_BITS - The chosen UART-Driver does not support the specified number of stop bits.
 * @return UART_SERVICE_RC_FAIL_INVALID_BAUDRATE - The chosen UART-Driver does not support the specified baudrate.
 * \ingroup UART_SERVICE
 */
static __inline__ UartService_Status UartService_openPortTx_W(L1_HubID UART, UartService_PortHandle * pPortHandle)
{
    return UartService_openPortEx_W(UART, UART_SERVICE_PORT_DIRECTION_TX, pPortHandle);
}

/**
 * This function requests the Server to close the given UART's channel.
 * @param UART - The port used to send the request.
 * @param direction The direction(s) to close.
 * @param handle Pointer to the UartService_PortHandle acquired from UartService_openPort_W().
 *
 * @return UART_SERVICE_RC_OK - Operation successful.
 * @return UART_SERVICE_RC_FAIL - Operation unsuccessful.
 * @return UART_SERVICE_RC_FAIL_PORT_NOT_OPEN - The UART-Port with the given direction(s) has not been opened before.
 *
 * \ingroup UART_SERVICE
 */
UartService_Status UartService_closePortEx_W(L1_HubID UART, UartService_PortHandle * handle, UartService_PortDirection direction);

/**
 * This function requests the Server to close RX- and TX-Ports associated with the given UART-Channel.
 * @param UART - The port used to send the request.
 * @param handle Pointer to the UartService_PortHandle acquired from UartService_openPort_W().
 *
 * @return UART_SERVICE_RC_OK - Operation successful.
 * @return UART_SERVICE_RC_FAIL - Operation unsuccessful.
 * @return UART_SERVICE_RC_FAIL_PORT_NOT_OPEN - The UART-Port has not been opened.
 * \ingroup UART_SERVICE
 */
static __inline__ UartService_Status UartService_closePort_W(L1_HubID UART, UartService_PortHandle * handle)
{
    return UartService_closePortEx_W(UART, handle, UART_SERVICE_PORT_DIRECTION_RXTX);
}

/**
 * This function requests the Server to close the RX-UART-Port associated with the given UART-Channel.
 * @param UART - The port used to send the request.
 * @param handle Pointer to the UartService_PortHandle acquired from UartService_openPort_W().
 *
 * @return UART_SERVICE_RC_OK - Operation successful.
 * @return UART_SERVICE_RC_FAIL - Operation unsuccessful.
 * @return UART_SERVICE_RC_FAIL_PORT_NOT_OPEN - The UART-Port has not been opened for the RX-direction.
 * \ingroup UART_SERVICE
 */
static __inline__ UartService_Status UartService_closePortRx_W(L1_HubID UART, UartService_PortHandle * handle)
{
    return UartService_closePortEx_W(UART, handle, UART_SERVICE_PORT_DIRECTION_RX);
}

/**
 * This function requests the Server to close the RX-UART-Port associated with the given UART-Channel.
 * @param UART - The port used to send the request.
 * @param handle Pointer to the UartService_PortHandle acquired from UartService_openPort_W().
 *
 * @return UART_SERVICE_RC_OK - Operation successful.
 * @return UART_SERVICE_RC_FAIL - Operation unsuccessful.
 * @return UART_SERVICE_RC_FAIL_PORT_NOT_OPEN - The UART-Port has not been opened for the TX-direction.
 * \ingroup UART_SERVICE
 */
static __inline__ UartService_Status UartService_closePortTx_W(L1_HubID UART, UartService_PortHandle * handle)
{
    return UartService_closePortEx_W(UART, handle, UART_SERVICE_PORT_DIRECTION_TX);
}



/**
 * This function requests the Server to retrieve the given channel's status, whether it is opened or closed.
 * @param UART - The port used to send the request.
 * @param handle Pointer to the UartService_PortHandle acquired from UartService_openPort_W().
 * @param pbPortStatus - pointer to a boolean where the truth value will be stored.
 *
 * @return UART_SERVICE_RC_OK - Operation successful.
 * @return UART_SERVICE_RC_FAIL - Operation unsuccessful.
 * \ingroup UART_SERVICE
 */
UartService_Status UartService_isPortOpen_W(L1_HubID UART, UartService_PortHandle * handle, L1_BOOL *pbPortStatus);

/**
 * This function requests the Server to transmit a byte over the UART device.
 * @param UART - The port used to send the request.
 * @param handle Pointer to the UartService_PortHandle acquired from UartService_openPort_W().
 * @param byteToWrite - The value to be transmitted.
 *
 * @return UART_SERVICE_RC_OK - Operation successful.
 * @return UART_SERVICE_RC_FAIL - Operation unsuccessful.
 * @return UART_SERVICE_RC_FAIL_PORT_NOT_OPEN - The UART-Port identified by handle is not open in the TX-Direction.
 * @return UART_SERVICE_RC_TX_FIFO_FULL - The FIFO in the UART driver is full.
 * \ingroup UART_SERVICE
 */
UartService_Status UartService_writeByte_NB(L1_HubID UART, UartService_PortHandle * handle, const L1_BYTE byteToWrite);

/**
 * This function requests the Server to read a byte from the UART device after waiting a given number of iterations.
 * @param UART - The port used to send the request.
 * @param handle Pointer to the UartService_PortHandle acquired from UartService_openPort_W().
 * @param byteRead - Pointer to a byte where the read value will be stored.
 *
 * @return UART_SERVICE_RC_OK - Operation successful.
 * @return UART_SERVICE_RC_FAIL - Operation unsuccessful.
 * @return UART_SERVICE_RC_FAIL_PORT_NOT_OPEN - The UART-Port identified by handle is not open in the RX-Direction.
 * @return UART_SERVICE_RC_RX_FIFO_EMPTY - There is currently no data in the RX-FIFO of the UART.
 * \ingroup UART_SERVICE
 */
UartService_Status UartService_readByte_NB(L1_HubID UART, UartService_PortHandle * handle, L1_BYTE *byteRead);

/**
 * This function requests the Server to transmit the given Buffer over the UART device. This is a blocking implementation.
 * @param UART - The port used to send the request.
 * @param handle Pointer to the UartService_PortHandle acquired from UartService_openPort_W().
 * @param pBuffer - Pointer to the Buffer to transmit.
 * @param byteCount - The number of bytes to write.
 * @param bytesWritten - Pointer to the variable where to store how many bytes have been actually written.
 *
 * @return UART_SERVICE_RC_OK - Operation successful.
 * @return UART_SERVICE_RC_FAIL - Operation unsuccessful.
 * @return UART_SERVICE_RC_FAIL_PORT_NOT_OPEN - The UART-Port identified by handle is not open in the TX-Direction.
 * \ingroup UART_SERVICE
 */
UartService_Status UartService_writeBuffer_W(L1_HubID UART,UartService_PortHandle * handle, const L1_BYTE *pBuffer, L1_UINT32 byteCount, L1_UINT32 *bytesWritten);

/**
 * This function requests the Server to retrieve a given amount of received data from the UART device. This is a blocking implementation.
 * @param UART - The port used to send the request.
 * @param handle Pointer to the UartService_PortHandle acquired from UartService_openPort_W().
 * @param pBuffer - Pointer to the buffer in which to store the received data.
 * @param byteCount - The number of bytes to read.
 * @param bytesRead - Pointer to the variable where to store how many bytes have been actually read.
 *
 * @return UART_SERVICE_RC_OK - Operation successful.
 * @return UART_SERVICE_RC_FAIL - Operation unsuccessful.
 * @return UART_SERVICE_RC_FAIL_PORT_NOT_OPEN - The UART-Port identified by handle is not open in the RX-Direction.
 * \ingroup UART_SERVICE
 */
UartService_Status UartService_readBuffer_W(L1_HubID UART,UartService_PortHandle * handle, L1_BYTE *pBuffer, L1_UINT32 byteCount, L1_UINT32 *bytesRead);

/**
 * This function waits for the UART-Service to signal the arrival of new RX-Data.
 * @param UART - The port used to send the request.
 * @param handle Pointer to the UartService_PortHandle acquired from UartService_openPort_W().
 * @return UART_SERVICE_RC_FAIL - Operation unsuccessful.
 * @return  UART_SERVICE_RC_OK - UART signaled the arrival of data.
 * @return UART_SERVICE_RC_FAIL_PORT_NOT_OPEN - The UART-Port identified by handle is not open in the RX-Direction.
 *
 * \warning This function only checks and waits for the RX-Data-Event, which gets signaled every time the UART-Service
 * retrieves data from the UART-Device.
 * \ingroup UART_SERVICE
 */
UartService_Status UartService_waitForRxData_W(L1_HubID UART, UartService_PortHandle * handle);

/**
 * This function requests the Server to transmit the given Buffer over the UART device. This is a non-blocking implementation.
 * @param UART - The port used to send the request.
 * @param handle Pointer to the UartService_PortHandle acquired from UartService_openPort_W().
 * @param pBuffer - Pointer to the Buffer to transmit.
 * @param byteCount - The number of bytes to write.
 * @param bytesWritten - Pointer to the variable where to store how many bytes have been actually written.
 *
 * @return UART_SERVICE_RC_OK - Operation successful.
 * @return UART_SERVICE_RC_FAIL - Operation unsuccessful.
 * @return UART_SERVICE_RC_FAIL_PORT_NOT_OPEN - The UART-Port identified by handle is not open in the TX-Direction.
 * @return UART_SERVICE_RC_TX_FIFO_FULL - The FIFO in the UART driver is full.
 * \ingroup UART_SERVICE
 */
UartService_Status UartService_writeBuffer_NB(L1_HubID UART, UartService_PortHandle * handle, const L1_BYTE *pBuffer, L1_UINT32 byteCount, L1_UINT32 *bytesWritten);

/**
 * This function requests the Server to retrieve a given amount of received data from the UART device. This is a non-blocking implementation.
 * @param UART - The port used to send the request.
 * @param handle Pointer to the UartService_PortHandle acquired from UartService_openPort_W().
 * @param pBuffer - Pointer to the buffer in which to store the received data.
 * @param byteCount - The number of bytes to read.
 * @param bytesRead - Pointer to the variable where to store how many bytes have been actually read.
 *
 * @return UART_SERVICE_RC_OK - Operation successful.
 * @return UART_SERVICE_RC_FAIL - Operation unsuccessful.
 * @return UART_SERVICE_RC_FAIL_PORT_NOT_OPEN - The UART-Port identified by handle is not open in the RX-Direction.
 * @return UART_SERVICE_RC_RX_FIFO_EMPTY - There is currently no data in the RX-FIFO of the UART.
 * \ingroup UART_SERVICE
 */
UartService_Status UartService_readBuffer_NB(L1_HubID UART, UartService_PortHandle * handle, L1_BYTE *pBuffer, L1_UINT32 byteCount, L1_UINT32 *bytesRead);

#endif
