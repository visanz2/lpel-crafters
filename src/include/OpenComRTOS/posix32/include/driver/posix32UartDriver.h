/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2013
 * www.Altreonic.com
 * Module name: posix32UartDriver.h ($Path/$Filename)
 * Synopsis: UART Driver for Posix.
 *
 * $LastChangedDate: 2010-11-05 10:52:18 +0100 (Fri, 05 Nov 2010) $
 * $Revision: 2037 $
 * $LastChangedBy: bernhard.sputh $
 *******************************************************************************/

#ifndef POSIX32UARTDRIVER_H_
#define POSIX32UARTDRIVER_H_



#include <L1_types.h>
#include <driver/class/L1_Drv_Uart.h>
#include <driver/L1_lrb.h>
#include <termios.h>
#define POSIX32_UART_RING_BUFFER_SIZE 0x400


typedef struct
{
    L1_BOOL open;
    /**
     * This represents a callback to be called whenever an RX-Data interrupt has been handled.
     */
    ISR_Callback rxCallback;
    /**
     * This represents a callback to be called whenever an TX-FIFO Empty interrupt has been handled.
     */
    ISR_Callback txCallback;
    /**
     * Pointer to a Previously initialised Lockless Ring Buffer structure to be used for received data (RX).
     */
    L1_lrb rxRingBuffer;
    /**
     * Pointer to a Previously initialised Lockless Ring Buffer structure to be used for data to be sent (TX).
     */
    L1_lrb txRingBuffer;
    /**
     * The buffer for the RX-Ring-Buffer.
     */
    L1_UINT8 rxBuffer[POSIX32_UART_RING_BUFFER_SIZE];
    /**
     * The buffer for the TX-Ring-Buffer.
     */
    L1_UINT8 txBuffer[POSIX32_UART_RING_BUFFER_SIZE];
}Posix32UartChannel;


/**
 * Private data of a Posix32-UART.
 */
typedef struct
{
        /**
         * Name of the UART-Device to interface to.
         */
        char * deviceName;
        /**
         * Device-handle for reading
         */
        int readFd;
        /**
         * Device- handle for writing.
         */
        int writeFd;
        /**
         * Flag to indicate to the TX/RX ISR's that they can start.
         */
        L1_UINT32 driverInitialised;
        /**
         * Mutex used to signal the TX-ISR emulating thread that new data must be sent out.
         */
        pthread_mutex_t txMutex;
        /**
         * Conditional Variable used to signal the TX-ISR emulating thread that new data must be sent out.
         */
        pthread_cond_t txCv;
        /**
         * The UART-Channel to be used by this driver.
         */
        Posix32UartChannel channel;
}Posix32UartDevice;

/**
 * Forward declaration of the UART Driver API
 */
extern const L1_Drv_UART_API POSIX32_UART_API;

#endif /* POSIX32UARTDRIVER_H_ */
