/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2008
 * www.Altreonic.com
 * Module name: L1_Drv_Uart.h ($Path/$Filename)
 * Synopsis: Types that are used by UART drivers.
 *
 * $LastChangedDate: 2014-02-11 16:56:11 +0100 (Tue, 11 Feb 2014) $
 * $Revision: 4179 $
 * $LastChangedBy: bernhard.sputh $
 *******************************************************************************/

#ifndef L1_DRV_UART_H_
#define L1_DRV_UART_H_

#include <L1_types.h>
#include <L1_api.h>
#include <driver/class/L1_Drv_Version.h>
#include <driver/class/L1_Drv_IntC.h>

/** The different baudrates a UART-Channel can support.
 * \ingroup L1_DRV_UART
 */
typedef enum
{
  eBaudRate100    = 100,
  eBaudRate150    = 150,
  eBaudRate300    = 300,
  eBaudRate600    = 600,
  eBaudRate1200   = 1200,
  eBaudRate2400   = 2400,
  eBaudRate4800   = 4800,
  eBaudRate9600   = 9600,
  eBaudRate14400  = 14400,
  eBaudRate19200  = 19200,
  eBaudRate28800  = 28800,
  eBaudRate38400  = 38400,
  eBaudRate57600  = 57600,
  eBaudRate115200 = 115200,
  eBaudRate230400 = 230400,
  eBaudRate460800 = 460800,
  eBaudRate921600 = 921600
} L1_Drv_Uart_BaudRate;


/**
 * Parity of a UART-Channel.
 * \ingroup L1_DRV_UART
 */

typedef enum
{
  eSerialParityNone = 0,
  eSerialParityOdd  = 1,
  eSerialParityEven = 2
} L1_Drv_Uart_Parity;


/**
 * Bits per byte values.
 * \ingroup L1_DRV_UART
 */
typedef enum
{
  eSerialDataLen5 = 5,
  eSerialDataLen6 = 6,
  eSerialDataLen7 = 7,
  eSerialDataLen8 = 8,
  eSerialDataLen9 = 9
} L1_Drv_Uart_ByteLength;

/**
 * Number of stop bits to use.
 * \ingroup L1_DRV_UART
 */
typedef enum
{
  eSerialStopBits1 = 0,
  eSerialStopBits1p5 = 1,
  eSerialStopBits2 = 2
} L1_Drv_Uart_NbrOfStopBits;


/** Enumeration used for setting the UART Channel's type of flow control*/
typedef enum
{
  eSerialHwFlowControlOn = 0,
  eSerialHwFlowControlOff
} L1_Drv_Uart_FlowControl;

/**
 * Lists the permitted operational modes of a UART-Port.
 * \ingroup L1_DRV_UART
 */
typedef enum
{
    /**
     * RS-232 Mode
     */
    eEia232Mode = 1,
    /**
     * RS-422 Mode
     */
    eEia422Mode = 2,
    /**
     * RS-485 Mode
     */
    eEia485Mode = 4
} L1_Drv_Uart_PortMode;

typedef enum
{
	UART_OK = 0,
	UART_FAIL = 1,
	UART_FAIL_INVALID_PORT_MODE = 2,
	UART_FAIL_INVALID_FLOW_CONTROL = 3,
	UART_FAIL_INVALID_PARITY = 4,
	UART_FAIL_INVALID_WORD_LENGTH = 5,
	UART_FAIL_INVALID_NBR_OF_STOP_BITS = 6,
	UART_FAIL_INVALID_BAUDRATE = 7
}L1_Drv_Uart_Status;

/**
 * This structure contains the communication parameters of an UART.
 */
typedef struct
{
  /**
   * The communication's Baud Rate.
   */
  L1_Drv_Uart_BaudRate eBaudRate;

  /**
   * The Receiver's and Transmitter's parity.
   */
  L1_Drv_Uart_Parity eParity;

  /**
   * The communication word's length.
   */
  L1_Drv_Uart_ByteLength eLength;

  /**
   * The number of stop bits for the communication word.
   */
  L1_Drv_Uart_NbrOfStopBits eStopBit;

  /**
   * Whether the hardware's flow control is enabled or disabled.
   */
  L1_Drv_Uart_FlowControl eHwFlow;

  /**
   * The Port mode can be RS-232, RS-422 or RS-485.
   */
   L1_Drv_Uart_PortMode ePortMode;

   /**
    * Whether the loopback mode is enabled or disabled.
    */
   L1_BOOL eLoopbackModeEnabled;

} L1_SerialPortConfig;

/**
 * Events that a UART ISR can trigger.
 */
typedef struct{
    /**
     * This flag indicates whether or not the Task using this UART expects to be signaled once data gets received. It is set by the Task to L1_TRUE and the call back routine sets it to L1_FALSE upon signalling.
     * @warning Access to this field must be protected from interrupts.
     */
    L1_BOOL rxFifoEmpty;
    /**
     * This flag indicates whether or not the Task using this UART expects to be signaled once data got removed from the TX-RingBuffer. It is set by the Task to L1_TRUE and the call back routine sets it to L1_FALSE upon signalling.
     * @warning Access to this field must be protected from interrupts.
     */
    L1_BOOL txFifoFull;
    /**
     * The ID of the Event-Hub that will be signalled whenever the ISR has added
     * data to the RX-RingBuffer.
     */
    L1_HubID rxEventID;
    /**
     * The ID of the Event-Hub that will be signalled whenever the ISR has taken
     * out data from the TX-RingBuffer.
     */
    L1_HubID txEventID;
    /**
     * Packet to use to signal the rxEvent.
     */
    L1_Packet rxPacket;
    /**
     * Packet to use to signal the txEvent.
     */
    L1_Packet txPacket;
}L1_UartEvents;


/*
 * New UART driver class.
 */
struct L1_Drv_UART_t;
/**
 * \defgroup L1_DRV_UART UART API
 *
 * This is the unified API for UARTs in OpenComRTOS.
 */

/**
 * The configuration of a UART-Port.
 * \ingroup L1_DRV_UART
 */
typedef struct
{
  /**
   * The communication's Baud Rate.
   */
  L1_Drv_Uart_BaudRate baudRate;

  /**
   * The Receiver's and Transmitter's parity.
   */
  L1_Drv_Uart_Parity parity;

  /**
   * The communication word's length.
   */
  L1_Drv_Uart_ByteLength byteLength;

  /**
   * The number of stop bits for the communication word.
   */
  L1_Drv_Uart_NbrOfStopBits nbrOfStopBits;

  /**
   * Whether the hardware's flow control is enabled or disabled.
   */
  L1_BOOL hardwareFlowControl;

  /**
   * The Port mode can be RS-232, RS-422 or RS-485.
   */
   L1_Drv_Uart_PortMode portMode;

   /**
    * Whether the loopback mode is enabled or disabled.
    */
   L1_BOOL loopbackMode;

} L1_Drv_Uart_portConfig;

/**
 * Return codes for UART's.
 * \ingroup L1_DRV_UART
 */
typedef enum{
	/**
	 * The operation was performed successfully.
	 */
	UART_RC_OK = 1,
	/**
	 * The operation failed, for an unknown reason.
	 */
	UART_RC_FAIL = 2,
	/**
	 * The desired number of bits per byte (word length) is invalid.
	 */
	UART_RC_FAIL_INVALID_WORD_LENGTH =3 ,
	/**
	 * The number of Stop bits is invalid.
	 */
	UART_RC_FAIL_INVALID_NBR_OF_STOP_BITS = 4,
	/**
	 * This UART-Channel does not support hardware flow control.
	 */
	UART_RC_FAIL_INVALID_FLOW_CONTROL = 5,
	/**
	 * This UART-Channel does not support the desired mode of operation.
	 */
	UART_RC_FAIL_INVALID_UART_MODE = 6,
	/**
	 * The desired baud-rate is not supported, by this UART-Channel.
	 */
	UART_RC_FAIL_INVALID_BAUDRATE = 7,
	/**
	 * The desired parity is not supported by the UART-Channel
	 */
	UART_RC_FAIL_INVALID_PARITY = 8,
	/**
	 * The UART-Channel is already open, thus it cannot be opened a second time.
	 */
	UART_RC_FAIL_CHANNEL_ALREADY_OPEN = 9,
	/**
	 * The UART-Channel is closed, thus no operation is possible on it.
	 */
	UART_RC_FAIL_CHANNEL_CLOSED = 10,
	/**
	 * The type of call-back is not supported by the UART-Driver.
	 */
	UART_RC_FAIL_CALLBACK_TYPE_UNSUPPORTED = 11,
	/**
	 * The receiver buffer is empty, thus no data can be retrieved from it.
	 */
	UART_RC_FAIL_RX_BUFFER_EMPTY = 12,
	/**
	 * There is no space left in the TX-Ring-Buffer of the UART-Channel.
	 */
	UART_RC_FAIL_TX_BUFFER_FULL = 13,
	/**
	 * The desired channel does not exist.
	 */
	UART_RC_FAIL_NO_SUCH_CHANNEL = 14,
	/**
	 * The operation is not supported by this driver. This code gets returned whenever the user tries to use an
	 * unsupported operation, because it has not been implemented yet, or cannot be implemented.
	 */
	UART_RC_FAIL_UNSUPPORTED_OPERATION
}UART_Status;

/**
 * Represents a UART-Channel.
 * \ingroup L1_DRV_UART
 */
typedef struct{
	/**
	 * Pointer to UART-Channel and UART-Driver specific information.
	 */
	void * pData;
}L1_Drv_UART_Channel;


/**
 * Initialises a UART driver.
 *
 * @param this Pointer to the L1_Drv_UART_t structure
 *
 * @return UART_RC_OK The operation was performed successfully.
 * @return UART_RC_FAIL The operation failed, the UART-Driver has not been initialised.
 * \ingroup L1_DRV_UART_DEVEL
 */
typedef UART_Status (*uart_api_init)(struct L1_Drv_UART_t * self);

/**
 * Initialises a UART driver.
 *
 * @param this Pointer to the L1_Drv_UART_t structure
 *
 * @return UART_RC_OK The operation was performed successfully.
 * @return UART_RC_FAIL The operation failed, the UART-Driver has not been initialised.
 * \ingroup L1_DRV_UART
 */
#ifdef API_DOC
UART_Status L1_Drv_UART_init(struct L1_Drv_UART_t * this);
#else
#define L1_Drv_UART_init(self)\
    (self)->api->init( (self) )
#endif /* API_DOC */
/**
 * Opens a UART-Channel.
 * @param this  Pointer to the L1_Drv_UART structure which represents the UART driver to open the channel of.
 * @param channelNbr Number of the UART-Channel to open. This is only relevant for drivers which handle more than one UART channel.
 * @param pConfig The configuration of the UART-Channel.
 * @param pChannel Pointer to a variable of type L1_Drv_UART_Channel which will be used to communicate with the UART-Channel after this function returned successfully.
 *
 * @return The function returns the following elements of UART_Status:
 * @return UART_RC_OK The desired operation was performed successfully.
 * @return UART_RC_FAIL The desired operation failed, for an unknown reason.
 * @return UART_RC_FAIL_CHANNEL_ALREADY_OPEN The UART-Channel is already open.
 * @return UART_RC_FAIL_INVALID_WORD_LENGTH An invalid number of bits per byte was desired.
 * @return UART_RC_FAIL_INVALID_NBR_OF_STOP_BITS An invalid number of stop bits was desired.
 * @return UART_RC_FAIL_INVALID_FLOW_CONTROL Hardware flow control is not available.
 * @return UART_RC_FAIL_INVALID_UART_MODE The UART cannot provide the desired UART-Mode.
 * @return UART_RC_FAIL_INVALID_BAUDRATE The desired baud rate is not supported by this UART.
 * @return UART_RC_FAIL_INVALID_PARITY The desired parity is not supported by this UART-Channel
 *
 * \ingroup L1_DRV_UART_DEVEL
 */
typedef UART_Status (*uart_api_open)(struct L1_Drv_UART_t * self, L1_UINT32 channelNbr, L1_Drv_Uart_portConfig * pConfig, L1_Drv_UART_Channel * pChannel);

/**
 * Opens a UART-Channel.
 * @param this  Pointer to the L1_Drv_UART structure which represents the UART driver to open the channel of.
 * @param channelNbr Number of the UART-Channel to open. This is only relevant for drivers which handle more than one UART channel.
 * @param pConfig The configuration of the UART-Channel.
 * @param pChannel Pointer to a variable of type L1_Drv_UART_Channel which will be used to communicate with the UART-Channel after this function returned successfully.
 *
 * @return The function returns the following elements of UART_Status:
 * @return UART_RC_OK The desired operation was performed successfully.
 * @return UART_RC_FAIL The desired operation failed, for an unknown reason.
 * @return UART_RC_FAIL_CHANNEL_ALREADY_OPEN The UART-Channel is already open.
 * @return UART_RC_FAIL_INVALID_WORD_LENGTH An invalid number of bits per byte was desired.
 * @return UART_RC_FAIL_INVALID_NBR_OF_STOP_BITS An invalid number of stop bits was desired.
 * @return UART_RC_FAIL_INVALID_FLOW_CONTROL Hardware flow control is not available.
 * @return UART_RC_FAIL_INVALID_UART_MODE The UART cannot provide the desired UART-Mode.
 * @return UART_RC_FAIL_INVALID_BAUDRATE The desired baud rate is not supported by this UART.
 * @return UART_RC_FAIL_INVALID_PARITY The desired parity is not supported by this UART-Channel
 *
 * \ingroup L1_DRV_UART
 */
#ifdef API_DOC
UART_Status L1_Drv_UART_open(struct L1_Drv_UART_t * self, L1_UINT32 channelNbr, L1_Drv_Uart_portConfig * pConfig, L1_Drv_UART_Channel * pChannel);
#else
#define L1_Drv_UART_open(self, channelNbr, pConfig, pChannel)\
    (self)->api->open( (self), (channelNbr), (pConfig), (pChannel) )
#endif /* API_DOC */
/**
 * Prototype of a function that has a pointer to a variable of type L1_Drv_UART_Channel as parameter.
 * @param this Pointer to the L1_Drv_UART structure which represents the UART driver to operate on.
 * @param pChannel Pointer to a variable of type L1_Drv_UART_Channel which represents the UART-Channel to operate on.
 * @return UART_RC_OK The desired operation was performed successfully.
 * @return UART_RC_FAIL The desired operation failed, for an unknown reason.
 * \ingroup L1_DRV_UART_DEVEL
 */
typedef UART_Status (*uart_api_channelParam)(struct L1_Drv_UART_t * self, L1_Drv_UART_Channel * pChannel);

/**
 * Closes a UART-Channel.
 * @param this Pointer to the L1_Drv_UART structure which represents the UART driver to operate on.
 * @param pChannel Pointer to a variable of type L1_Drv_UART_Channel which represents the UART-Channel to close.
 * @return UART_RC_OK The desired operation was performed successfully.
 * @return UART_RC_FAIL The desired operation failed, for an unknown reason.
 * @return UART_RC_FAIL_CHANNEL_CLOSED The channel is closed, thus no operation on it is possible.
 * \ingroup L1_DRV_UART
 */
#ifdef API_DOC
UART_Status L1_Drv_UART_close(struct L1_Drv_UART_t * self, L1_Drv_UART_Channel * pChannel);
#else
#define L1_Drv_UART_close(self, pChannel)\
    (self)->api->close( (self), (pChannel) )
#endif /* API_DOC */


/**
 * This function tries to read data from the UART-Channel indicated by pCannel. This function copies at most the
 * number of bytes indicated by nbrOfBytesToRead to the buffer pBuffer, if there are less bytes available it copies what
 * is available and then returns. Thus this function does not wait for new data to be available before returning.
 *
 * @param this Pointer to the L1_Drv_UART structure which represents the UART driver to operate on.
 * @param pChannel Pointer to a variable of type L1_Drv_UART_Channel which represents the UART-Channel to read from.
 * @param nbrOfBytesToRead Maximum number of bytes to read.
 * @param pBuffer Pointer to the buffer where the read data should be copied to, must at least have the size indicated by nbrOfBytesToRead.
 * @param pNbrOfBytesRead The actual number of bytes that could be read.
 *
 * @return UART_RC_OK The operation could be performed successfully.
 * @return UART_RC_FAIL Something unspecified has gone wrong and caused this interaction to fail.
 * @return UART_RC_FAIL_CHANNEL_CLOSED The channel is closed, thus no operation on it is possible.
 * @return UART_RC_FAIL_RX_BUFFER_EMPTY There is no data in the ring buffer that keeps the received data.
 *
 * @warning In case the function returns UART_RC_OK the user must check the value in pNbrOfBytesRead to see how many bytes were actually read.
 *
 * \ingroup L1_DRV_UART_DEVEL
 */
typedef UART_Status (*uart_api_read)(struct L1_Drv_UART_t * self, L1_Drv_UART_Channel * pChannel, L1_UINT8 * pBuffer, L1_UINT32 nbrOfBytesToRead, L1_UINT32 * pNbrOfBytesRead);

/**
 * This function tries to read data from the UART-Channel indicated by pCannel. This function copies at most the
 * number of bytes indicated by nbrOfBytesToRead to the buffer pBuffer, if there are less bytes available it copies what
 * is available and then returns. Thus this function does not wait for new data to be available before returning.
 *
 * @param this Pointer to the L1_Drv_UART structure which represents the UART driver to operate on.
 * @param pChannel Pointer to a variable of type L1_Drv_UART_Channel which represents the UART-Channel to read from.
 * @param nbrOfBytesToRead Maximum number of bytes to read.
 * @param pBuffer Pointer to the buffer where the read data should be copied to, must at least have the size indicated by nbrOfBytesToRead.
 * @param pNbrOfBytesRead The actual number of bytes that could be read.
 *
 * @return UART_RC_OK The operation could be performed successfully.
 * @return UART_RC_FAIL Something unspecified has gone wrong and caused this interaction to fail.
 * @return UART_RC_FAIL_CHANNEL_CLOSED The channel is closed, thus no operation on it is possible.
 * @return UART_RC_FAIL_RX_BUFFER_EMPTY There is no data in the ring buffer that keeps the received data.
 *
 * @warning In case the function returns UART_RC_OK the user must check the value in pNbrOfBytesRead to see how many bytes were actually read.
 *
 * \ingroup L1_DRV_UART
 */
#ifdef API_DOC
UART_Status L1_Drv_UART_read(struct L1_Drv_UART_t * self, L1_Drv_UART_Channel * pChannel, L1_UINT8 * pBuffer, L1_UINT32 nbrOfBytesToRead, L1_UINT32 * pNbrOfBytesRead);
#else
#define L1_Drv_UART_read(self, pChannel, pBuffer, nbrOfBytesToRead, pNbrOfBytesRead)\
    (self)->api->read( (self), (pChannel), (pBuffer), (nbrOfBytesToRead), (pNbrOfBytesRead) )
#endif /* API_DOC */


/**
 * This function tries to write data the the UART-Channel indicated by pCannel. This function copies at most the
 * number of bytes indicated by nbrOfBytesToWrite to the TX-Ring-Buffer of the UART-Channel, if there are less space available in the TX-Ring-Buffer it copies what
 * is available and then returns.
 *
 * @param this Pointer to the L1_Drv_UART structure which represents the UART driver to operate on.
 * @param pChannel Pointer to a variable of type L1_Drv_UART_Channel which represents the UART-Channel to read from.
 * @param nbrOfBytesToWrite Maximum number of bytes to write.
 * @param pBuffer Pointer to the buffer which contains the data to be written to the TX-Ring-Buffer.
 * @param pNbrOfBytesWritten The actual number of bytes that could be copied.
 *
 * @return UART_RC_OK The operation could be performed successfully.
 * @return UART_RC_FAIL Something unspecified has gone wrong and caused this interaction to fail.
 * @return UART_RC_FAIL_CHANNEL_CLOSED The channel is closed, thus no operation on it is possible.
 * @return UART_RC_FAIL_TX_BUFFER_FULL There is no space left in the TX-Ring-Buffer of the UART-Channel.
 *
 * @warning In case the function returns UART_RC_OK the user must check the value in pNbrOfBytesWritten to see how many bytes were actually written.
 *
 * \ingroup L1_DRV_UART_DEVEL
 */
typedef UART_Status (*uart_api_write)(struct L1_Drv_UART_t * self, L1_Drv_UART_Channel * pChannel, L1_UINT8 * pBuffer, L1_UINT32 nbrOfBytesToWrite, L1_UINT32 * pNbrOfBytesWritten);

/**
 * This function tries to write data the the UART-Channel indicated by pCannel. This function copies at most the
 * number of bytes indicated by nbrOfBytesToWrite to the TX-Ring-Buffer of the UART-Channel, if there are less space available in the TX-Ring-Buffer it copies what
 * is available and then returns.
 *
 * @param this Pointer to the L1_Drv_UART structure which represents the UART driver to operate on.
 * @param pChannel Pointer to a variable of type L1_Drv_UART_Channel which represents the UART-Channel to read from.
 * @param nbrOfBytesToWrite Maximum number of bytes to write.
 * @param pBuffer Pointer to the buffer which contains the data to be written to the TX-Ring-Buffer.
 * @param pNbrOfBytesWritten The actual number of bytes that could be copied.
 *
 * @return UART_RC_OK The operation could be performed successfully.
 * @return UART_RC_FAIL Something unspecified has gone wrong and caused this interaction to fail.
 * @return UART_RC_FAIL_CHANNEL_CLOSED The channel is closed, thus no operation on it is possible.
 * @return UART_RC_FAIL_TX_BUFFER_FULL There is no space left in the TX-Ring-Buffer of the UART-Channel.
 *
 * @warning In case the function returns UART_RC_OK the user must check the value in pNbrOfBytesWritten to see how many bytes were actually written.
 *
 * \ingroup L1_DRV_UART
 */
#ifdef API_DOC
UART_Status L1_Drv_UART_write(struct L1_Drv_UART_t * self, L1_Drv_UART_Channel * pChannel, L1_UINT8 * pBuffer, L1_UINT32 nbrOfBytesToWrite, L1_UINT32 * pNbrOfBytesWritten);
#else
#define L1_Drv_UART_write(self, pChannel, pBuffer, nbrOfBytesToWrite, pNbrOfBytesWritten)\
    (self)->api->write( (self), (pChannel), (pBuffer), (nbrOfBytesToWrite), (pNbrOfBytesWritten) )
#endif /* API_DOC */


/**
 * Different possible callbacks that can be registered for a UART-Channel, using the registerCallBack operation of a UART-Driver.
 * \ingroup L1_DRV_UART
 */
typedef enum
{
	/**
	 * Gets called every time new data has been received.
	 */
	UART_CB_RX_DATA  = 1,
	/**
	 * Gets called if there is free space in a previously full TX-RingBuffer.
	 */
	UART_CB_TX_FREE  = 2,
	/**
	 * Gets called once an overflow error was detected.
	 */
	UART_CB_OVERFLOW_ERROR = 3,
	/**
	 * Gets called once a parity error was detected.
	 */
	UART_CB_PARITY_ERROR = 4

}L1_Drv_UART_CallBackTypes;

/**
 *
 * @param this Pointer to the L1_Drv_UART structure which represents the UART driver to operate on.
 * @param pChannel Pointer to a variable of type L1_Drv_UART_Channel which represents the UART-Channel to operate on.
 * @param type The type of call-back to register. Please note not all UART-Drivers support all types of call-backs.
 * @param callBack The call back function to register.
 * @param pParam The parameter to pass to the call-back function when calling it.
 * @return UART_RC_OK The desired operation was performed successfully.
 * @return UART_RC_FAIL The desired operation failed, for an unknown reason.
 * @return UART_RC_FAIL_CALLBACK_TYPE_UNSUPPORTED The type of call-back is not supported by the UART-Driver.
 * \ingroup L1_DRV_UART_DEVEL
 */
typedef UART_Status (*uart_api_registerCallBack)(struct L1_Drv_UART_t * self, L1_Drv_UART_Channel * pChannel, L1_Drv_UART_CallBackTypes type, L1_ISR_CALLBACK callBack, void * pParam);

/**
 *
 * @param this Pointer to the L1_Drv_UART structure which represents the UART driver to operate on.
 * @param pChannel Pointer to a variable of type L1_Drv_UART_Channel which represents the UART-Channel to operate on.
 * @param type The type of call-back to register. Please note not all UART-Drivers support all types of call-backs.
 * @param callBack The call back function to register.
 * @param pParam The parameter to pass to the call-back function when calling it.
 * @return UART_RC_OK The desired operation was performed successfully.
 * @return UART_RC_FAIL The desired operation failed, for an unknown reason.
 * @return UART_RC_FAIL_CALLBACK_TYPE_UNSUPPORTED The type of call-back is not supported by the UART-Driver.
 * \ingroup L1_DRV_UART
 */
#ifdef API_DOC
UART_Status L1_Drv_UART_registerCallBack(struct L1_Drv_UART_t * self, L1_Drv_UART_Channel * pChannel, L1_Drv_UART_CallBackTypes type, L1_ISR_CALLBACK callBack, void * pParam);
#else
#define L1_Drv_UART_registerCallBack(self, pChannel, type, callBack, pParam)\
    (self)->api->registerCallBack( (self), (pChannel), (type), (callBack), (pParam) )
#endif /* API_DOC */



/**
 * This function tries to read data directly from the UART device indicated by pChannel.
 * This function always returns immediately.
 *
 * @param this Pointer to the L1_Drv_UART structure which represents the UART driver to operate on.
 * @param pChannel Pointer to a variable of type L1_Drv_UART_Channel which represents the UART-Channel to read from.
 * @param pValue Pointer to a variable of type L1_UINT8  where the read data should be stored.
 *
 * @return UART_RC_OK The operation could be performed successfully.
 * @return UART_RC_FAIL Something unspecified has gone wrong and caused this interaction to fail.
 * @return UART_RC_FAIL_CHANNEL_CLOSED The channel is closed, thus no operation on it is possible.
 * @return UART_RC_FAIL_RX_BUFFER_EMPTY There is no data in the ring buffer that keeps the received data.
 *
 * \ingroup L1_DRV_UART_DEVEL
 */
typedef UART_Status (*uart_api_readByte_NW)(struct L1_Drv_UART_t * self, L1_Drv_UART_Channel * pChannel, L1_UINT8 * pValue);

/**
 * This function tries to read data directly from the UART device indicated by pChannel.
 * This function always returns immediately.
 *
 * @param this Pointer to the L1_Drv_UART structure which represents the UART driver to operate on.
 * @param pChannel Pointer to a variable of type L1_Drv_UART_Channel which represents the UART-Channel to read from.
 * @param pValue Pointer to a variable of type L1_UINT8  where the read data should be stored.
 *
 * @return UART_RC_OK The operation could be performed successfully.
 * @return UART_RC_FAIL Something unspecified has gone wrong and caused this interaction to fail.
 * @return UART_RC_FAIL_CHANNEL_CLOSED The channel is closed, thus no operation on it is possible.
 * @return UART_RC_FAIL_RX_BUFFER_EMPTY There is no data in the ring buffer that keeps the received data.
 *
 * \ingroup L1_DRV_UART
 */
#ifdef API_DOC
UART_Status L1_Drv_UART_readByte_NW(struct sL1_Drv_UART * self, L1_Drv_UART_Channel * pChannel, L1_UINT8 * pValue);
#else
#define L1_Drv_UART_readByte_NW(self, pChannel, pValue)\
    (self)->api->readByte_NW( (self), (pChannel), (pValue))
#endif /* API_DOC */
/**
 * This function writes a byte the the UART-Channel indicated by pCannel. This function waits until it write the byte to the UART-Channel.
 *
 * @param this Pointer to the L1_Drv_UART structure which represents the UART driver to operate on.
 * @param pChannel Pointer to a variable of type L1_Drv_UART_Channel which represents the UART-Channel to read from.
 * @param value The byte to write to the UART-Channel.
 *
 * @return UART_RC_OK The operation could be performed successfully.
 * @return UART_RC_FAIL Something unspecified has gone wrong and caused this interaction to fail.
 * @return UART_RC_FAIL_CHANNEL_CLOSED The channel is closed, thus no operation on it is possible.
 *
 * @warning This function waits until it write the byte to the UART-Channel.
 *
 * \ingroup L1_DRV_UART_DEVEL
 */
typedef UART_Status (*uart_api_writeByte_W)(struct L1_Drv_UART_t * self, L1_Drv_UART_Channel * pChannel, L1_UINT8 value);


/**
 * This function writes a byte the the UART-Channel indicated by pCannel. This function waits until it write the byte to the UART-Channel.
 *
 * @param this Pointer to the L1_Drv_UART structure which represents the UART driver to operate on.
 * @param pChannel Pointer to a variable of type L1_Drv_UART_Channel which represents the UART-Channel to read from.
 * @param value The byte to write to the UART-Channel.
 *
 * @return UART_RC_OK The operation could be performed successfully.
 * @return UART_RC_FAIL Something unspecified has gone wrong and caused this interaction to fail.
 * @return UART_RC_FAIL_CHANNEL_CLOSED The channel is closed, thus no operation on it is possible.
 *
 * @warning This function waits until it write the byte to the UART-Channel.
 *
 * \ingroup L1_DRV_UART
 */
#ifdef API_DOC
UART_Status L1_Drv_UART_writeByte_W(struct L1_Drv_UART_t * self, L1_Drv_UART_Channel * pChannel, L1_UINT8 value);
#else
#define L1_Drv_UART_writeByte_W(self, pChannel, value)\
    (self)->api->writeByte_W( (self), (pChannel), (value))
#endif /* API_DOC */


/**
 * This function enables the interrupt line of the UART-Device. This should also ensure that hte RX-Interrupt is enabled at the same time.
 *
 * @param this Pointer to the L1_Drv_UART structure which represents the UART driver to operate on.
 * @param pChannel Pointer to a variable of type L1_Drv_UART_Channel which represents the UART-Channel to read from.
 * @param value The byte to write to the UART-Channel.
 *
 * @return UART_RC_OK The operation could be performed successfully.
 * @return UART_RC_FAIL Something unspecified has gone wrong and caused this interaction to fail.
 * @return UART_RC_FAIL_CHANNEL_CLOSED The channel is closed, thus no operation on it is possible.
 *
 * @warning This function waits until it write the byte to the UART-Channel.
 *
 * \ingroup L1_DRV_UART
 */
#ifdef API_DOC
UART_Status L1_Drv_UART_enableInterrupt(struct L1_Drv_UART_t * self, L1_Drv_UART_Channel * pChannel);
#else
#define L1_Drv_UART_enableInterrupt(self, pChannel)\
    (self)->api->enableInterrupt( (self), (pChannel))
#endif /* API_DOC */


/**
 * This function disables the interrupt line of the UART-Device. This should not change the the interupts generated by the UART.
 *
 * @param this Pointer to the L1_Drv_UART structure which represents the UART driver to operate on.
 * @param pChannel Pointer to a variable of type L1_Drv_UART_Channel which represents the UART-Channel to read from.
 * @param value The byte to write to the UART-Channel.
 *
 * @return UART_RC_OK The operation could be performed successfully.
 * @return UART_RC_FAIL Something unspecified has gone wrong and caused this interaction to fail.
 * @return UART_RC_FAIL_CHANNEL_CLOSED The channel is closed, thus no operation on it is possible.
 *
 * @warning This function waits until it write the byte to the UART-Channel.
 *
 * \ingroup L1_DRV_UART
 */
#ifdef API_DOC
UART_Status L1_Drv_UART_disableInterrupt(struct L1_Drv_UART_t * self, L1_Drv_UART_Channel * pChannel);
#else
#define L1_Drv_UART_disableInterrupt(self, pChannel)\
    (self)->api->disableInterrupt( (self), (pChannel))
#endif /* API_DOC */
/**
 * This is the list of call-back functions which represents the UART-Driver.
 * \ingroup L1_DRV_UART_DEVEL
 */
typedef struct{
    drv_api_get_version getVersion;
    uart_api_init  init;
    uart_api_open  open;
    uart_api_channelParam close;
    uart_api_read  read;
    uart_api_write write;
    uart_api_registerCallBack registerCallBack;
    uart_api_readByte_NW readByte_NW;
    uart_api_writeByte_W writeByte_W;
    uart_api_channelParam enableInterrupt;
    uart_api_channelParam disableInterrupt;
}L1_Drv_UART_API;

/**
 * This represents a UART-Driver object.
 * \ingroup L1_DRV_UART
 */
typedef struct L1_Drv_UART_t{
    /**
     * Pointer to the functions that implement the UART-API.
     */
    L1_Drv_UART_API * api;
    /**
     * Private data structures of the UART Driver Instance.
     */
    void * self;
}L1_Drv_UART;

/**
 * This is the API-Version of the L1_Drv_Uart API. It has the following structure:
  * - MSByte: Major Version
  * - 23--16: Minor Version
  * - 15--8 : Release status:
  * 			- 0: Alpha
  * 			- 1: Beta
  * 			- 2: Release Candidate
  * 			- 3: Public Release
  * - LSByte: Patch-level
  * \ingroup L1_DRV_UART_DEVEL
  */
#define L1_DRV_UART_API_VERSION 0x00020200

#endif /* L1_DRV_UART_H_ */
