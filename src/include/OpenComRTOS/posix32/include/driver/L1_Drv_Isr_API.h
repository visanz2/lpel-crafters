/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2008
 * www.Altreonic.com
 * Module name: L1_Drv_Isr_API.h ($Path/$Filename)
 * Synopsis:
 *
 * $LastChangedDate: 2010-11-05 10:52:18 +0100 (Fri, 05 Nov 2010) $
 * $Revision: 2037 $
 * $LastChangedBy: bernhard.sputh $
 *******************************************************************************/

#ifndef L1_DRV_ISR_API_H_
#define L1_DRV_ISR_API_H_

/**
 * \defgroup  OCR_ISR_API Interrupt Service Routines in OpenComRTOS
 *
 * An IRQ (Interrupt ReQuest) is an event send by a hardware device to inform the
 * CPU that it requires the assistance of the CPU to proceed. Once the CPU receives
 * an IRQ it does stop the normal flow of execution and switches the CPU into
 * Interrupt Mode, calling a so called Interrupt Service Routine (ISR). In this ISR
 * the programmer normally does service the hardware and then leaves the Interrupt
 * Mode again. The critical thing is that the occurrence of an ISR must be passed to
 * the user space application / device driver Tasks / Hubs. This document explains
 * the chosen strategy for OpenComRTOS Device drivers.
 *
 * \section OCR_ISR_API_1 Application Diagram of an Interrupt Driven Device Driver
 *
 * \image html ISR-Interface.png "A Driver Task with two ISRs and a connected User Task." width=500px
 * \image latex ISR-Interface.png "A Driver Task with two ISRs and a connected User Task." width=\textwidth
 *
 * The Figure above shows a conceptual application / interaction diagram of an interrupt driven driver. It consists of the following entities:
 * - Hubs:
 *  - Isr1Event and Isr2Event are OpenComRTOS Event-Hubs, used to bridge the gap between ISR context and Task Context.
 *  - InputPort: This Port-Hub transfers requests from the UserTask to the DriverTask
 *  - OutputPort: This Port-Hub transfers replies from the DriveTask to the UserTask
 *  - Lock: This Resoruce-Hub guards the access to the DriverTask, to prevent that two Tasks try to interact with the DriverTask at the same time.
 * - Tasks:
 *  - Device: This represents the hardware device which triggers an interrupt. The tirggering of the Interrupt is represented in this diagram by the interaction `L1_ResumeTask_W'.
 *  - ISR1 and ISR2: These represent the Interrupt Service Routines which the device may trigger. Upon being triggered an ISR checks whether it is responsible for this Interrupt (there are shared interrupt lines on some bus systems, such as PCI), and if it is responsible it disables the interrupt in the device and raises its interrupt event, using non-waiting interaction semantics.
 *  - DriverTask: This is the Task that represents the device driver, it acts as a gatway, between the hardware device and the user application. In this example it waits, in parallel (Asynchronous Semantics) for the following Hubs to interact with:
 *   - Isr1Event, to become signaled, which then triggers what ever has to happen with respect to handle this interrupt and then reenable the interrupt in the device.
 *   - Isr2Event, to become signaled, which then triggers what ever has to happen with respect to handle this interrupt and then reenable the interrupt in the device.
 *   - InputPort, to contain a request from the UserTask(s), which then gets handled and replied to using the OutputPort.
 *  - UserTask: This represents one or more Tasks that want to interact with the DriverTask, i.e. the Device Driver.
 *
 * \section OCR_ISR_API_2 Interrupt Handling Flow (ISR to DriverTask)
 * -# ISR gets triggered.
 *  -# ISR, checks that the interrupt is from its device
 *  -# ISR, disables the interrupt on the device
 *  -# ISR sends a Packet to it's assigned ISR-Event, using the interaction L1_Drv_Isr_RaiseEvent_NW().
 *  -# ISR, returns with the return value `1'.
 * -# Driver-Task:
 *  -# Waits for the ISR-Events that have been assigned to it, using L1_TestEvent_A(), and L1_WaitForPacket_W()
 *  -# Once an ISR-Event has become signaled the Driver task performs the following operations:
 *   -# Handling of the Hardware requirements.
 *   -# If necessary send a reply to the User-Task
 *   -# Reenabling the interrupt.
 *   -# Wait again for the ISR-Events to become signaled with L1_TestEvent_A().
 *
 */


/**
 * This function initalises an L1_Packet to be used from an Interrupt Service Routine (ISR).
 * The following fields get initialised:
 * - RequestingTaskID: Is set to the Task ID of the currently running Task.
 * - ListElement.Next: NULL;
 * - ListElement.Prev: NULL;
 * - ListElement.Priority: Is set to 1.
 * - PendingRequestHandler: NULL;
 * - PendingRequestListElement.Prev: NULL;
 * - PendingRequestListElement.Next: NULL;
 * - PendingRequestListElement.Priority: Is set to 1.
 * - OwnerPool: NULL, because this packet is not part of a Packet Pool.
 * @param packet Pointer to the L1_Packet to initialise.
 * @return RC_OK if the operation was successful.
 * @return RC_FAIL if the operation was not successful.
 *
 * \ingroup OCR_ISR_API
 */
extern L1_Status L1_Drv_Isr_initialisePacket(L1_Packet * packet);

/**
 * This builds an L1_Packet and then inserts it into the Kernel Input Port.
 * It is meant to be used from within Interrupt Service Routines, and will only permit _NW (non waiting) semantics.
 * It is similar to the function L1_buildAndInsertPacket().
 *
 *
 * @param hubID The id of the Hub the Packet should be sent to.
 * @param packet Pointer to the L1_Packet to send.
 * @param ServiceID The ID of the service to trigger.
 * @return RC_OK If the Packet could be built and inserted.
 * @return RC_FAIL If the Packet could not be built or inserted. One reason why the Packet could not be built is that the Packet is still being used for a previous request.
 *
 * \warning Must not be used with Hubs that are located on another Node!
 * \warning Only to be used within an ISR, not within a Task!
 *
 * @sa L1_buildAndInsertPacket
 *
 * \ingroup OCR_ISR_API
 *
 */
extern L1_Status L1_Drv_Isr_buildAndInsertPacket_NW(L1_HubID hubID, L1_Packet *packet, L1_UINT16 ServiceID);


/**
 *
 * This interaction tries to raise an event from the ISR context. This function returns directly,
 * like an Asynchronous Interaction, but the packet will never be returned to the ISR.
 *
 * Parameters:
 * @param event ID of the Event-Hub that should be raised.
 * @param packet Pointer to the L1_Packet that will be used to represent the interaction.
 * This L1_Packet must have been once initialised using the function L1_Drv_Isr_initialisePacket().
 *
 * @return RC_OK The packet that raises the Event could be inserted into the Kernel Input Port.
 * @return RC_FAIL The packet that raises the Event could not be inserted into the Kernel Input Port.
 *
 * \warning Must not be used with Event-Hubs located at another Node.
 * \warning Only to be used within an ISR, not within a Task!
 *
 * @sa L1_Drv_Isr_initialisePacket
 *
 * \ingroup OCR_ISR_API
 */
static __inline__ L1_Status L1_Drv_Isr_RaiseEvent_NW(L1_HubID event, L1_Packet * packet)
{
    return L1_Drv_Isr_buildAndInsertPacket_NW(event, (packet), (L1_UINT16)(L1_SID_SEND_TO_HUB | (L1_EVENT << 8)));
}



/**
 * Signals a semaphore, i.e. increases the semaphore count. This function returns directly,
 * like an Asynchronous Interaction, but the packet will never be returned to the ISR.
 *
 * Parameters:
 * @param semaphore is the L1_HubID which identifies the Semaphore, that the calling ISR wants to signal/
 * @param packet Pointer to the L1_Packet that will be used to represent the interaction.
 * This L1_Packet must have been once initialized using the function L1_Drv_Isr_initialisePacket().
 *
 *
 * @return RC_OK The packet that raises the Event could be inserted into the Kernel Input Port.
 * @return RC_FAIL The packet that raises the Event could not be inserted into the Kernel Input Port.
 *
 * \warning Must not be used with Semaphore-Hubs located at another Node.
 * \warning Only to be used within an ISR, not within a Task!
 *
 * @sa L1_Drv_Isr_initialisePacket
 *
 * \ingroup OCR_ISR_API
 */
static __inline__  L1_Status L1_Drv_Isr_SignalSemaphore_NW(L1_HubID semaphore, L1_Packet * packet)
{
    return L1_Drv_Isr_buildAndInsertPacket_NW( semaphore, (packet), (L1_UINT16)(L1_SID_SEND_TO_HUB | (L1_SEMAPHORE << 8)));
}

/**
 * Enqueues a fifo. This function returns directly, like an Asynchronous Interaction, but the
 * packet will never be returned to the ISR.
 *
 * Parameters:
 * @param fifo is the L1_HubID which identifies the Fifo, that the calling ISR wants to enqueue.
 * @param packet Pointer to the L1_Packet that will be used to represent the interaction.
 * This L1_Packet must have been once initialized using the function L1_Drv_Isr_initialisePacket().
 *
 *
 * @return RC_OK The packet that enqueues the fifo could be inserted into the Kernel Input Port.
 * @return RC_FAIL The packet that enqueues the fifo could not be inserted into the Kernel Input Port.
 *
 * \warning Must not be used with Fifo-Hubs located at another Node.
 * \warning Only to be used within an ISR, not within a Task!
 *
 * @sa L1_Drv_Isr_initialisePacket
 *
 * \ingroup OCR_ISR_API
 */

static __inline__ L1_Status L1_Drv_Isr_EnqueueFifo_NW(L1_HubID fifo, L1_Packet * packet)
{
    return L1_Drv_Isr_buildAndInsertPacket_NW( fifo, (packet), (L1_UINT16)(L1_SID_SEND_TO_HUB | (L1_FIFO << 8)));
}

/**
 * Enqueues a fifo. This function returns directly, like an Asynchronous Interaction, but the
 * packet will never be returned to the ISR.
 *
 * Parameters:
 * @param hubId is the L1_HubID which identifies the Hub to which the ISR wants to send an IOCTL.
 * @param packet Pointer to the L1_Packet that will be used to represent the interaction.
 * This L1_Packet must have been once initialized using the function L1_Drv_Isr_initialisePacket().
 * @param ioctlCode The code that identified the operation the IOCTL should perform.
 *
 * @return RC_OK The packet could be inserted into the Kernel Input Port.
 * @return RC_FAIL The packet could not be inserted into the Kernel Input Port.
 *
 * \warning Must not be used with Hubs located on another Node.
 * \warning Only to be used within an ISR, not within a Task!
 *
 * @sa L1_Drv_Isr_initialisePacket
 *
 * \ingroup OCR_ISR_API
 */
static __inline__ L1_Status L1_Drv_Isr_IOCTL_NW(L1_HubID hubId, L1_Packet * packet, L1_UINT8 ioctlCode)
{
    return L1_Drv_Isr_buildAndInsertPacket_NW( hubId, (packet), (L1_UINT16)((ioctlCode << 8) | L1_SID_IOCTL_HUB) );
}


#endif /* L1_DRV_ISR_API_H_ */
