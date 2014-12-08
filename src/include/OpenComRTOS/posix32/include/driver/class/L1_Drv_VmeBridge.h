/*
 * L1_Drv_VmeBridge.h
 *
 *  Created on: 25 Dec 2012
 *      Author: Bernhard.Sputh
 */

#ifndef L1_DRV_VMEBRIDGE_H_
#define L1_DRV_VMEBRIDGE_H_

#include "L1_Drv_IntC.h"


typedef enum
{
    /**
     * Bus Address of type:
     * - Address Mode: A24
     * - User Level Program
     */
    VME_AM_STD_USR_DATA,
    /**
     * Bus Address of type:
     * - Address Mode: A24
     * - User Level Program
     */
    VME_AM_STD_USR_PGM,
    /**
     * Bus Address of type:
     * - Address Mode: A24
     * - Kernel Level Program (Supervisor)
     */
    VME_AM_STD_SUP_DATA,
    /**
     * Bus Address of type:
     * - Address Mode: A24
     * - Kernel Level Program (Supervisor)
     */
    VME_AM_STD_SUP_PGM,
    /**
     * Bus Address of type:
     * - Address Mode: A16
     * - User Level Program
     * - IO
     */
    VME_AM_USR_SHORT_IO,
    /**
     * Bus Address of type:
     * - Address Mode: A16
     * - Kernel Level Program (Supervisor)
     * - IO
     */
    VME_AM_SUP_SHORT_IO,
    /**
     * Bus Address of type:
     * - Address Mode: A32
     * - User Level Program
     */
    VME_AM_EXT_USR_DATA,
    /**
     * Bus Address of type:
     * - Address Mode: A32
     * - User Level Program
     */
    VME_AM_EXT_USR_PGM,
    /**
     * Bus Address of type:
     * - Address Mode: A32
     * - Kernel Level Program (Supervisor)
     */
    VME_AM_EXT_SUP_DATA,
    /**
     * Bus Address of type:
     * - Address Mode: A32
     * - Kernel Level Program (Supervisor)
     */
    VME_AM_EXT_SUP_PGM,
}L1_Drv_VmeAddressSpace;

/**
 * Converts a given VME-Bus Address to the corresponding CPU address, based on the address space the busAddress utilises.
 *
 * @param self Pointer to the private data of the bride device driver.
 * @param adressSpace The address space the address resides in.
 * @param busAddress The address on the selected address space that should be converted to a CPU address.
 * @param pCpuAddress Pointer to an char pointer where to store the converted address.
 *
 * @return RC_OK if the operation was successful.
 * @return RC_FAIL if the operation failed.
 */
typedef L1_Status (*vme_bridge_convert_bus_to_cpu_address)(void * self, L1_Drv_VmeAddressSpace addressSpace, char * busAddress, char ** pCpuAddress);

/**
 * Converts a given CPU dddress to the corresponding VME-Bus address, based on the address space the busAddress utilises.
 *
 * @param self Pointer to the private data of the bride device driver.
 * @param adressSpace The address space the address resides in.
 * @param cpuAddress The CPU address to convert to the corresponding VME address.
 * @param pBusAddress Pointer to a char pointer where to store the converted address.
 *
 * @return RC_OK if the operation was successful.
 * @return RC_FAIL if the operation failed.
 */
typedef L1_Status (*vme_bridge_convert_cpu_to_bus_address)(void * self, L1_Drv_VmeAddressSpace addressSpace, char * cpuAddress, char ** pBusAddress);


/**
 * Enables the specified interrupt level on the VME-Bus.
 *
 * @param self Pointer to the private data of the bride device driver.
 * @param intLevel The interrupt level (1--7) to enable.
 *
 * @return RC_OK if the operation was successful.
 * @return RC_FAIL if the operation failed.
 */
typedef L1_Status (*vme_bridge_enable_vme_interrupt_level)(void * self, L1_UINT32 intLevel);

/**
 * Disables the specified interrupt level on the VME-Bus.
 *
 * @param self Pointer to the private data of the bride device driver.
 * @param intLevel The interrupt level (1--7) to disable.
 *
 * @return RC_OK if the operation was successful.
 * @return RC_FAIL if the operation failed.
 */
typedef L1_Status (*vme_bridge_disable_vme_interrupt_level)(void * self, L1_UINT32 intLevel);


typedef L1_Status (*vme_bridge_register_isr)(void * self, L1_UINT32 intVector, L1_ISR_CALLBACK isr, void * arg);


typedef struct
{
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
    vme_bridge_register_isr      registerIsr;
    /**
     * @sa interrupt_controller_deregister_isr
     */
    interrupt_controller_deregister_isr    deregisterIsr;
    /**
     * @sa vme_bridge_convert_bus_to_cpu_address
     */
    vme_bridge_convert_bus_to_cpu_address convertBusToCpuAddress;
    /**
     * @sa vme_bridge_convert_cpu_to_bus_address
     */
    vme_bridge_convert_cpu_to_bus_address convertCpuToBusAddress;
    /**
     * @sa vme_bridge_enable_vme_interrupt_level
     */
    vme_bridge_enable_vme_interrupt_level enableVmeInterruptLevel;
    /**
     * @sa vme_bridge_disable_vme_interrupt_level
     */
    vme_bridge_disable_vme_interrupt_level disableVmeInterruptLevel;
}L1_Drv_VmeBridge_API;

/*
 * TODO: Document these functions, and then implement additional Defines which cater for the inherited interrupt related functions.
 */


typedef struct _L1_Drv_VmeBridge
{
    /**
     * Points to a structure of L1_Drv_VmeBridge_API. This structure
     * contains pointers to the functions that can be used to interface with
     * the driver that represents this interrupts controller.
     */
    L1_Drv_VmeBridge_API * api;
    /**
     * Pointer to the private data associated with the interrupt controller
     * instance. This pointer may be NULL, if no parameter is necessary.
     */
    void                 * self;
}L1_Drv_VmeBridge;





#define L1_Drv_VmeBridge_convertBusToCpuAddress(pVmeBridge, addressSpace, busAddress, pCpuAddress)\
    (pVmeBridge)->api->convertBusToCpuAddress( (pVmeBridge)->self, addressSpace, busAddress, pCpuAddress)

#define L1_Drv_VmeBridge_convertCpuToBusAddress(pVmeBridge, addressSpace, cpuAddress, pBusAddress)\
    (pVmeBridge)->api->convertBusToCpuAddress( (pVmeBridge)->self, addressSpace, cpuAddress, pBuAddress)

#define L1_Drv_VmeBridge_enableVmeInterruptLevel(pVmeBridge, vmeInterruptLevel)\
    (pVmeBridge)->api->enableVmeInterruptLevel( (pVmeBridge)->self, vmeInterruptLevel)

#define L1_Drv_VmeBridge_disableVmeInterruptLevel(pVmeBridge, vmeInterruptLevel)\
    (pVmeBridge)->api->disableVmeInterruptLevel( (pVmeBridge)->self, vmeInterruptLevel)

/**
 * This registers an ISR with a VME-Bride
 * @param self Pointer to the VME-Bridge device to use.
 * @param intVector The Interrupt Vector as defined by the specific VME-Bridge-Driver.
 * @param isr Pointer to the function to call when the interrupt occurs.
 * @param arg The argument to be passed to teh function indicated by isr.
 * @return RC_OK The ISR could be registered.
 * @return RC_FAIL The ISR could not be registered.
 *
 */
static inline L1_Status L1_Drv_VmeBridge_registerIsr(L1_Drv_VmeBridge * self, L1_UINT32 intVector, L1_ISR_CALLBACK isr, void * arg)
{
    if(NULL == self)
    {
        return RC_FAIL;
    }
    if(NULL == self->api->registerIsr)
    {
        return RC_FAIL;
    }
    return self->api->registerIsr(self->self, intVector, isr, arg);
}

/**
 * This function enables a VME-Bridge specific interrupt with the VME-Bridge driver.
 * This has nothing to do with VME-Bus-Interrupt-Vectors!
 * @param self Pointer to the VME-Bridge device to use.
 * @param intVector The Interrupt Vector must not be in the range 0x00--0xFF.
 * @return RC_OK The VME-Bridge specific interrupt could be enabled.
 * @return RC_FAIL The VME-Bridge specific interrupt could not be enabled.
 */
static inline L1_Status L1_Drv_VmeBridge_enableBridgeInterrupt(L1_Drv_VmeBridge * self, L1_UINT32 intVector)
{
    if(NULL == self)
    {
        return RC_FAIL;
    }
    return self->api->enableInterrupt(self->self, intVector);
}

/**
 * This function disables a VME-Bridge specific interrupt with the VME-Bridge driver.
 * This has nothing to do with VME-Bus-Interrupt-Vectors!
 * @param self Pointer to the VME-Bridge device to use.
 * @param intVector The Interrupt Vector must not be in the range 0x00--0xFF.
 * @return RC_OK The VME-Bridge specific interrupt could be disabled.
 * @return RC_FAIL The VME-Bridge specific interrupt could not be disabled.
 */
static inline L1_Status L1_Drv_VmeBridge_disableBridgeInterrupt(L1_Drv_VmeBridge * self, L1_UINT32 intVector)
{
    if(NULL == self)
    {
        return RC_FAIL;
    }
    return self->api->disableInterrupt(self->self, intVector);
}

/**
 * Prototype for an VME Error Interrupt routine.
 *
 * @param pData The pointer that was specified when registering the ISR.
 * @param intVector The interrupt vector that caused the error.
 *
 * @return L1_UINT32, specifies whether or not to switch to the Kernel-Task, or to switch to the interrupted Task.
 *  - 0: Switch to the interrupted Task
 *  - 1: Switch to the Kernel-Task.
 *
 * \ingroup OCR_DRV_CLASS_INTC
 */
typedef L1_UINT32 (*VME_ERROR_CALLBACK) (void * pData, L1_UINT32 intVector);




#endif /* L1_DRV_VMEBRIDGE_H_ */
