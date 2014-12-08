/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2008
 * www.Altreonic.com
 * Module name: ($Path/$Filename)
 * Synopsis: Declares necessary structures for the win32Uart Rx and Tx drivers.
 *
 * $LastChangedDate: 2013-04-18 19:43:34 +0200 (Thu, 18 Apr 2013) $
 * $Revision: 3701 $
 * $LastChangedBy: bernhard.sputh $
 *******************************************************************************/

#ifndef L1_PIPELINKDRIVER_H_
#define L1_PIPELINKDRIVER_H_

//#define __USE_MISC
//#define _BSD_SOURCE
//#include <termios.h>
//#include <bits/termios.h>

#ifdef MP

#include <L1_types.h>
#include <kernel/L1_packet_api.h>
#include <kernel/L1_task_api.h>
#include <driver/L1_xfer_packet_api.h>
#include <stdio.h>

//#include <pthread.h>

/**
 * This is the configuration structure for a standard Posix UART
 */
typedef struct _PipeLinkDriver {
    /** Name of the DeviceNode to connect to (/dev/tty*)*/
    char  *DeviceName;
    char  *OutputPipePath;
    char  *InputPipePath;
    /** The Baudrate to set, represented by the constants defined in terminos.h: B50 --B230400 */
  //  L1_INT32 BaudRate;
    /** Number of bits in a Byte, can be CS5, CS6, CS7, or CS8 */
 //   L1_INT32 BitsPerByte;
    /** The number of StopBits in use, the values 1 or 2 are permitted, otherwise the default of 1 stopbit is used. */
   // L1_BYTE NbrOfStopBits;
    /** The parity to use, possible values: `N' (None), `E' (Even), or `O' (Odd) parity.*/
   // L1_BYTE Parity;

    /** Whether or not to use HW flow control, to use HW FlowControl set it to L1_TRUE, otherwise set it to L1_FALSE. */
   // L1_BOOL HwFlowControl;
    /* Values below are configured by the init funtion. */
    /** The pipe descriptors */
    FILE * outputPipe;
    FILE * inputPipe;
    L1_XferPacket rxPacket;
//    struct termios uart_attr;
//    pthread_mutex_t mutex;
}PipeLinkDriver;


typedef struct _PipeLinkPort{
        PipeLinkDriver * driver;
}PipeLinkPort;


void pipeLinkDriver_EntryPoint(L1_TaskArguments Arguments);

/*
 * This is the ISR function which needs to be passed to the kernel, the
 * parameter must be a pointer to the associated PipeLink structure.
 */
void* pipeLinkPort_RxIsrHandler(void* arg);


/**
 * This function performs the basic initialisation of the hardware,
 * independent of whether the device represents a client or a server.
 */
L1_Status pipeLinkDriver_init(PipeLinkDriver *self);

/*
 * This function initialises the pipeLink
 */
L1_BOOL pipeLinkPort_initServer(PipeLinkDriver * driver, PipeLinkPort * self);

L1_BOOL pipeLinkPort_initClient(PipeLinkDriver * driver, PipeLinkPort * self);


#define Even 'E'
#define Odd  'I'
#define None 'N'

#endif /*MP*/
#endif /* L1_PIPELINKDRIVER_H_ */
