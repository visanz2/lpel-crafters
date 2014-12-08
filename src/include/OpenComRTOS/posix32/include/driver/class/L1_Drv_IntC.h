/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2012
 * www.Altreonic.com
 * Module name: L1_interruptControllerDriver.h
 * Synopsis: This file contains the data types to unify the interrupt controller API.
 *
 * $LastChangedDate$
 * $Revision$
 * $LastChangedBy$
 *******************************************************************************/


#ifndef L1_DRV_INTC_H_
#define L1_DRV_INTC_H_

#include<L1_types.h>
#include <driver/class/L1_Drv_Version.h>


/**
 * \defgroup OCR_DRV_CLASS_INTC OpenComRTOS Interrupt Controller Driver Interface
 *
 * This file gives the API that should be used for all Interrupt Controller
 * Drivers in OpenComRTOS v1.5 and later. The API has been developed while
 * implementing the interrupt controller drivers for the TMS320C6678 which has
 * a complex hierarchical structure of interrupt controllers.
 *
 * The driver interface is designed to give the developer maximum flexibility to
 * define driver specific data structures, while providing a well defined
 * interface for the different drivers.
 *
 *
 */


/**
 * This is the API-Version of the L1_Drv_INTC API. It has the following structure:
  * - MSByte: Major Version
  * - 23--16: Minor Version
  * - 15--8 : Patch-level
  * - LSByte: Release status:
  *             - 0: Alpha
  *             - 1: Beta
  *             - 2: Release Candidate
  *             - 3: Public Release
  * \ingroup OCR_DRV_CLASS_INTC
  */
#define L1_DRV_INTC_API_VERSION 0x01010001 // V1.1.0-BETA





/**
 * Declares that the ISR is only using ASM to handle the pending interrupt.
 * Which registers this mode saves depends on the concrete platform.
 *
 * @warning This type is not mandatory to be supported. Check the concrete
 * platform Interrupt Controller driver for details.
 *
 * \ingroup OCR_DRV_CLASS_INTC
 */
#define ISR_TYPE_ASM 0

/**
 * Declares that the ISR may use C to handle the pending interrupt.
 * Which registers this mode saves depends on the concrete platform.
 *
 * \note This is the default mode, and must be supported by any interrupt controller driver!
 *
 * \ingroup OCR_DRV_CLASS_INTC
 */
#define ISR_TYPE_C 1

/**
 * Declares that the ISR may use C and the FPU to handle the pending interrupt.
 * Which registers this mode saves depends on the concrete platform.
 *
 * @warning This type is not mandatory to be supported. Check the concrete
 * platform Interrupt Controller driver for details.
 *
 * \ingroup OCR_DRV_CLASS_INTC
 */
#define ISR_TYPE_C_FPU 2



/**
 * Prototype for an Interrupt routine.
 *
 * @param pData The pointer that was specified when registering the ISR.
 * @return L1_UINT32, specifies whether or not to switch to the Kernel-Task, or to switch to the interrupted Task.
 *  - 0: Switch to the interrupted Task
 *  - 1: Switch to the Kernel-Task.
 *
 * \ingroup OCR_DRV_CLASS_INTC
 */
typedef L1_UINT32 (*L1_ISR_CALLBACK) (void* pData);


/**
 * Represents an entry in an Interrupt Vector Table.
 * \ingroup OCR_DRV_CLASS_INTC
 */
typedef struct
{
        /**
         * The function to call when this Interrupt has fired.
         */
        L1_ISR_CALLBACK  isr;
        /**
         * The pointer to pass to the function in its parameter pData;
         */
        void *           pData;
        /**
         * The type of the ISR, can be any of the following three values:
         *  - ISR_TYPE_ASM
         *  - ISR_TYPE_C
         *  - ISR_TYPE_C_FPU
         *  @warning Not all Platforms will support all three types! It is the
         *  discretion of the interrupt controller driver to change the type.
         */
        L1_BYTE          isrType;
}L1_INTERRUPT_VECTOR;


/**
 * This represents a callback function and it's argument when an ISR calls function of another driver.
 * \ingroup OCR_DRV_CLASS_INTC
 */
typedef struct
{
        /**
         * The function to call when this Interrupt has fired.
         */
        L1_ISR_CALLBACK  function;
        /**
         * The pointer to pass to the function in its parameter pData;
         */
        void *           arg;
}ISR_Callback;



/**
 * Initialises the interrupt controller. Careful the interrupt controllers must be initialised in the correct order, i.e. the one closest to the CPU first, and so on. Otherwise interrupt handling will not work correctly! Thus the metamodels must contain information about the initialisation order.
 *
 * @param self: Pointer to the private data of the Interrupt Controller to initialise.
 *
 * @return L1_Status, indicates whether or not the operation was successful:
 *  - RC_OK: Operation was successful.
 *  - RC_FAIL: Operation failed.
 * \ingroup OCR_DRV_CLASS_INTC
 */
typedef L1_Status (*interrupt_controller_initialise)(void * self);

/**
 * This function does register the ISR with the interupt controller indicated by the parameter self, and configures any interrupt controllers between itself and the CPU core to route this interrupt.
 *
 * @param self: Pointer to the private data of the Interrupt Controller to register the ISR with.
 * @param eventNumber: The number of the event / IRQ that the ISR should be associated with.
 * @param isrType The type of the ISR to register, this determines on some platforms how much context gets solved when the interrupt occurs. The permitted values are:
 *  - ISR_TYPE_ASM
 *  - ISR_TYPE_C
 *  - ISR_TYPE_C_FPU
 * @param isr: Pointer to the ISR that should be associated with the event / IRQ. Must be of type L1_ISR_CALLBACK.
 * @param pIsrData: Pointer that gets passed to the ISR in the parameter pData. May be NULL if the ISR does not require any private data.
 * @return L1_Status, indicates whether or not the operation was successful:
 *  - RC_OK: Operation was successful.
 *  - RC_FAIL: Operation failed.
 *
 * \ingroup OCR_DRV_CLASS_INTC
 */
typedef L1_Status (*interrupt_controller_register_isr)(void * self, L1_UINT32 eventNumber, L1_BYTE isrType, L1_ISR_CALLBACK isr, void * pIsrData);


/**
 * This function will set the default handler for the specified interrupt, instead of the previously defined handler.
 *
 * @param self: Pointer to the private data of the Interrupt Controller to enable the interrupt on
 * @param interruptNumber: The number of the event / IRQ that the ISR should be associated with.
 * @return L1_Status, indicates whether or not the operation was successful:
 *  - RC_OK: Operation was successful.
 *  - RC_FAIL: Operation failed.
 *
 * \ingroup OCR_DRV_CLASS_INTC
 */
typedef L1_Status (*interrupt_controller_deregister_isr)(void * self, L1_UINT32 interruptNumber);


/**
 * This function enables the interrupt in the interrupt controller defined by self it also enables it in all interrupt controllers between itself and the CPU. On targets which employ event-combiners such as the TI-Keystone Architecture (CorePac C66x) or the Microblaze, this function must keep count how often it was enabled to avoid accidental disabling of interrupts.
 *
 * @param self: Pointer to the private data of the Interrupt Controller to enable the interrupt at.
 * @param interruptNumber: The number of the event / IRQ that should be enabled.
 * @return L1_Status, indicates whether or not the operation was successful:
 *  - RC_OK: Operation was successful.
 *  - RC_FAIL: Operation failed.
 *
 * \ingroup OCR_DRV_CLASS_INTC
 */
typedef L1_Status (*interrupt_controller_enable_interrupt)(void * self, L1_UINT32 interruptNumber);

/**
 * This function disables the interrupt in the interrupt controller defined by self it also disables it in all interrupt controllers between itself and the CPU. On targets which employ event-combiners such as the TI-Keystone Architecture (CorePac C66x) or the Microblaze, this function must check whether the enable count is equal to zero before disabling the interrupt.
 *
 * @param self:  Pointer to the private data of the Interrupt Controller to disable the interrupt at.
 * @param interruptNumber: The number of the event / IRQ that should be disabled.
 * @return L1_Status, indicates whether or not the operation was successful:
 *  - RC_OK: Operation was successful.
 *  - RC_FAIL: Operation failed.
 *
 * \ingroup OCR_DRV_CLASS_INTC
 */
typedef L1_Status (*interrupt_controller_disable_interrupt)(void * self, L1_UINT32 interruptNumber);


/**
 * This function maps an Event to an Interrupt of the next stage behind the current Interrupt Controller.
 * @param interruptNumber: The number of the event / IRQ which should bypass the interrupt controller indicated by self.
 * @param mappedInterrupt pointer to an L1_UINT32 which will contain the number of the interrupt this event has been mapped to in the next stage.
 * @return L1_Status, indicates whether or not the operation was successful:
 *  - RC_OK: Operation was successful.
 *  - RC_FAIL: Operation failed.
 *
 * @warning Not every Interrupt Controller supports this. Currently only supported on TI-C6000 INTB.
 *
 * \ingroup OCR_DRV_CLASS_INTC
 */
typedef L1_Status (*interrupt_controller_pass_through_interrupt)(void * self, L1_UINT32 interruptNumber);

/**
 * Return codes used by the Interrupt Controller API.
 *
 * \ingroup OCR_DRV_CLASS_INTC
 */
typedef enum
{
    /**
     * The specified operation was performed successfully.
     */
    INTC_RC_OK = 0,
    /**
     * The operation has failed for an unspecified reason. Failing parameter
     * checks fall into this category.
     */
    INTC_RC_FAIL = 1,
    /**
     * The desired operation is not supported by this implementation of the API.
     * Reasons for this can be that it has not been implemented yet, or the
     * hardware does not support it.
     */
    INTC_RC_FAIL_UNSUPPORTED = 2,
    /**
     * The passed interrupt number is out of bounds, i.e. not supported by the interrupt controller.
     */
    INTC_RC_FAIL_ILLEGAL_IRQ = 3
}INTC_Status;


/**
 * This function clears the given interrupt on the given interrupt controller.
 *
 * @param self:  Pointer to the private data of the Interrupt Controller to disable the interrupt at.
 * @param interruptNumber: The number of the interrupt that should be cleared.
 * @return INTC_RC_OK: Operation was successful.
 * @return INCT_RC_FAIL: Operation failed.
 * @return INTC_RC_UNSUPPORTED: The operation is not supported.
 * @return INTC_RC_FAIL_ILLEGAL_IRQ There is no IRQ with the specified interrupt number.
 *
 * \ingroup OCR_DRV_CLASS_INTC
 */
typedef INTC_Status (*interrupt_controller_clear_interrupt)(void * self, L1_UINT32 interruptNumber);



/**
 * Sets the priority of an IRQ at a specific interrupt controller.
 *
 * @param this is a pointer to a structure of type L1_Drv_IntC
 * @param interruptNumber the number of the interrupt to clear.
 * @param priority The priority of the Interrupt.
 *
 * @return INTC_RC_OK: Operation was successful.
 * @return INTC_RC_FAIL: Operation failed.
 * @return INTC_RC_UNSUPPORTED: The operation is not supported.
 * @return INTC_RC_FAIL_ILLEGAL_IRQ There is no IRQ with the specified interrupt number.
 *
 * \ingroup OCR_DRV_CLASS_INTC
 */
typedef INTC_Status (*interrupt_controller_set_irq_priority)(void * self, L1_UINT32 interruptNumber, L1_UINT32 priority);

/**
 * Each interrupt controller driver will provide the following data structure in
 * a preconfigured form, in its C or ASM file, and reference to it as external in
 * its header file. A pointer to this data structure can then be passed on device
 * drivers that want to use this device driver. Furthermore, each driver will
 * have to have a pointer to the private data of the interrupt controller. This
 * may be NULL if no private data has to be passed. This is for instance the case
 * for the lowest level interrupt controller integrated in the CPU, as this one
 * uses global data structures.
 *
 * \warning It is important that all the pointers to the callback functions are
 * set, even if the interrupt controller driver does not support the functionality.
 * If this is the case the corresponding function must return the correct error code.
 * For instance assume a driver which is not able to enable / disable interrupts, but
 * instead all interrupts are always enabled. In this case the callback function
 * for enableInterrupt() must always return RC_OK, because the interrupt will be
 * enabled. Correspondingly the function representing the callback
 * disableInterrupt() must always return RC_FAIL.
 *
 * \ingroup OCR_DRV_CLASS_INTC
 */
typedef struct
{
    drv_api_get_version getVersion;
    /**
     * @sa interrupt_controller_register_isr
     */
    interrupt_controller_initialise        initialise;
    /**
     * @sa interrupt_controller_enable_interrupt
     */
    interrupt_controller_enable_interrupt  enableInterrupt;
    /**
     * @sa interrupt_controller_disable_interrupt
     */
    interrupt_controller_disable_interrupt disableInterrupt;
    /**
     * @sa interrupt_controller_register_isr
     */
    interrupt_controller_register_isr      registerIsr;
    /**
     * @sa interrupt_controller_deregister_isr
     */
    interrupt_controller_deregister_isr    deregisterIsr;
    /**
     * @sa interrupt_controller_pass_through_interupt
     */
    interrupt_controller_pass_through_interrupt passThroughInterrupt;

    interrupt_controller_clear_interrupt clearPendingIrq;
    interrupt_controller_clear_interrupt triggerIrq;
    interrupt_controller_set_irq_priority setIrqPriority;
}L1_Drv_IntC_API;




/**
 * Represents an instance of an interrupt controller in OpenComRTOS.
 *
 * @warning This structure has to be initialised during the code generation
 * phase. Except for default CPU Interrupt controllers, such as INTA of the
 * TI-DSP C6000 CorePac C66x CPU Family. Or the ARM-NVIC. There the device
 * driver provides a readily available data structure which can be used by the
 * devices depending on it.
 *
 * \ingroup OCR_DRV_CLASS_INTC
 */
typedef struct
{
    /**
     * Points to a structure of L1_Drv_IntC_API. This structure
     * contains pointers to the functions that can be used to interface with
     * the driver that represents this interrupts controller.
     */
    L1_Drv_IntC_API * api;
    /**
     * Pointer to the private data associated with the interrupt controller
     * instance. This pointer may be NULL, if no parameter is necessary.
     */
    void                      * self;
}L1_Drv_IntC;



/**
 * Initialises an Interrupt Controller.
 *
 * @param pIntc is a pointer to a structure of type L1_Drv_IntC
 *
 * @return L1_Status, indicates whether or not the operation was successful:
 *  - RC_OK: Operation was successful.
 *  - RC_FAIL: Operation failed.
 *
 * @sa interrupt_controller_register_isr
 *
 * \ingroup OCR_DRV_CLASS_INTC
 */
#define L1_Drv_IntC_initialise(pIntc)\
    (pIntc)->api->initialise( (pIntc)->self)


/**
 * Registers an ISR from the interrupt controller identified with parameters pIntc.
 *
 * @param pIntc is a pointer to a structure of type L1_Drv_IntC
 * @param interruptNumber the interrupt from which to deregister the ISR.
 * @param isrType The type of the ISR to register, this determines on some platforms how much context gets solved when the interrupt occurs. The permitted values are:
 *  - ISR_TYPE_ASM
 *  - ISR_TYPE_C
 *  - ISR_TYPE_C_FPU
 * @param isr: Pointer to the ISR that should be associated with the event / IRQ. Must be of type L1_ISR_CALLBACK.
 * @param pIsrData: Pointer that gets passed to the ISR in the parameter pData. May be NULL if the ISR does not require any private data.
 *
 * @return L1_Status, indicates whether or not the operation was successful:
 *  - RC_OK: Operation was successful.
 *  - RC_FAIL: Operation failed.
 *
 * @sa interrupt_controller_register_isr
 *
 * \ingroup OCR_DRV_CLASS_INTC
 */
#define L1_Drv_IntC_registerIsr(pIntc, interruptNumber, isrType, isr, pIsrData)\
    (pIntc)->api->registerIsr( (pIntc)->self, interruptNumber, isrType, isr, pIsrData)

/**
 * Deregisters an ISR from the interrupt controller identified with parameters pIntc.
 *
 * @param pIntc is a pointer to a structure of type L1_Drv_IntC
 * @param interruptNumber the interrupt from which to deregister the ISR.
 *
 * @return L1_Status, indicates whether or not the operation was successful:
 *  - RC_OK: Operation was successful.
 *  - RC_FAIL: Operation failed.
 *
 * @sa interrupt_controller_deregister_isr
 *
 * \ingroup OCR_DRV_CLASS_INTC
 */
#define L1_Drv_IntC_deregisterIsr(pIntc, interruptNumber)\
    (pIntc)->api->deregisterIsr( (pIntc)->self, interruptNumber)

/**
 * Enables the interrupt with the number defined in interruptNumber at the interrupt controller identified with parameters pIntc.
 *
 * @param pIntc is a pointer to a structure of type L1_Drv_IntC
 * @param interruptNumber the number of the interrupt to enable.
 *
 * @return L1_Status, indicates whether or not the operation was successful:
 *  - RC_OK: Operation was successful.
 *  - RC_FAIL: Operation failed.
 *
 * @sa interrupt_controller_enable_interrupt
 *
 * \ingroup OCR_DRV_CLASS_INTC
 */
#define L1_Drv_IntC_enableInterrupt(pIntc, interruptNumber)\
    (pIntc)->api->enableInterrupt( (pIntc)->self, interruptNumber)

/**
 * Disables the interrupt with the number defined in interruptNumber at the interrupt controller identified with parameters pIntc.
 *
 * @param pIntc is a pointer to a structure of type L1_Drv_IntC
 * @param interruptNumber the number of the interrupt to disable.
 *
 * @return L1_Status, indicates whether or not the operation was successful:
 *  - RC_OK: Operation was successful.
 *  - RC_FAIL: Operation failed.
 *
 * @sa interrupt_controller_disable_interrupt
 *
 * \ingroup OCR_DRV_CLASS_INTC
 */
#define L1_Drv_IntC_disableInterrupt(pIntc, interruptNumber)\
    (pIntc)->api->disableInterrupt( (pIntc)->self, interruptNumber)



/**
 * Maps an Event directly to an Interrupt of the next Interrupt controller.
 *
 * @param pIntc is a pointer to a structure of type L1_Drv_IntC
 * @param interruptNumber the number of the interrupt to disable.
 *
 * @return L1_Status, indicates whether or not the operation was successful:
 *  - RC_OK: Operation was successful.
 *  - RC_FAIL: Operation failed.
 *
 * @sa interrupt_controller_disable_interrupt
 *
 * \ingroup OCR_DRV_CLASS_INTC
 */
#define L1_Drv_IntC_passThroughInterrupt(pIntc, interruptNumber)\
    (pIntc)->api->passThroughInterrupt( (pIntc)->self, interruptNumber)


/*
 * This is a marker to identify that these functions are only supported in
 * version 1.1 of the IntC-API. It is used to provide drivers which can be
 * compiled for both version 1.0 and 1.1.
 */
#define L1_DRV_INTC_API_V_1_1

/**
 * Triggers an IRQ at the given Interrupt Controller.
 *
 * @param self is a pointer to a structure of type L1_Drv_IntC
 * @param interruptNumber the number of the interrupt to trigger.
 *
 * @return INTC_Status, indicates whether or not the operation was successful:
 * @return INTC_RC_OK: Operation was successful.
 * @return INTC_RC_FAIL: Operation failed.
 * @return INTC_RC_FAIL_ILLEGAL_IRQ There is no IRQ with the specified interrupt number.
 *
 * \warning This function was introduced in version 1.1 of the Interrupt Controller API.
 * \ingroup OCR_DRV_CLASS_INTC
 */
#ifdef API_DOC
    INTC_Status L1_Drv_IntC_triggerIrq(struct L1_Drv_UART_t * self, L1_UINT32 interruptNumber);
#else
#define L1_Drv_IntC_triggerIrq(pIntc, interruptNumber)\
    (pIntc)->api->triggerIrq( (pIntc)->self, interruptNumber)
#endif /* API_DOC */


/**
 * Clears a pending Interrupt Request at the given Interrupt Controller.
 *
 * @param self is a pointer to a structure of type L1_Drv_IntC
 * @param interruptNumber the number of the interrupt to clear.
 *
 * @return INTC_Status, indicates whether or not the operation was successful:
 * @return INTC_RC_OK: Operation was successful.
 * @return INTC_RC_FAIL: Operation failed.
 * @return INTC_RC_FAIL_ILLEGAL_IRQ There is no IRQ with the specified interrupt number.
 *
 * \warning This function was introduced in version 1.1 of the Interrupt Controller API.
 * \ingroup OCR_DRV_CLASS_INTC
 */
#ifdef API_DOC
    INTC_Status L1_Drv_IntC_clearPendingIrq(struct L1_Drv_UART_t * self, L1_UINT32 interruptNumber);
#else
#define L1_Drv_IntC_clearPendingIrq(pIntc, interruptNumber)\
    (pIntc)->api->clearPendingIrq( (pIntc)->self, interruptNumber)
#endif /* API_DOC */



/**
 * Sets the priority of an IRQ at a specific interrupt controller.
 *
 * @param this is a pointer to a structure of type L1_Drv_IntC
 * @param interruptNumber the number of the interrupt to clear.
 * @param priority The priority of the Interrupt.
 *
 * @return INTC_RC_OK: Operation was successful.
 * @return INTC_RC_FAIL: Operation failed.
 * @return INTC_RC_UNSUPPORTED: The operation is not supported.
 * @return INTC_RC_FAIL_ILLEGAL_IRQ There is no IRQ with the specified interrupt number.
 *
 * \warning This function was introduced in version 1.1 of the Interrupt Controller API.
 * \ingroup OCR_DRV_CLASS_INTC
 */
#ifdef API_DOC
    INTC_Status L1_Drv_IntC_setIrqPriority(void * this, L1_UINT32 interruptNumber, L1_UINT32 priority)
#else
    #define L1_Drv_IntC_setPriority(pIntc, interruptNumber, priority)\
     (pIntc)->api->setIrqPriority( (pIntc)->self, interruptNumber)
 #endif /* API_DOC */




#endif /* L1_DRV_INTC_H_ */
