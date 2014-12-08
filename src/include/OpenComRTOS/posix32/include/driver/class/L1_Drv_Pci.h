/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2008
 * www.Altreonic.com
 * Module name: pciDevice.h ($Path/$Filename)
 * Synopsis: Data structures Describing a PCI Device in OpenComRTOS. Based on Marvell
 * 64430 BSP code.
 *
 * $LastChangedDate: 2010-11-05 10:52:18 +0100 (Fri, 05 Nov 2010) $
 * $Revision: 2037 $
 * $LastChangedBy: bernhard.sputh $
 *******************************************************************************/

#ifndef L1_DRV_PCI_HEADER
#define L1_DRV_PCI_HEADER

#include <L1_types.h>

/**
 * \defgroup PCI_Class PCI Bus Driver Class
 *
 * This is a collection of functions that are used to operate on PCI devices in a
 * consistent way throughout OpenComRTOS.
 */



/* PCI base address low bar mask */
#define PCI_ERROR_CODE        0xffffffff

/* DEFINES */
#define PCI_ANY_ID            (~0)
/**
 * Identifies an Invalid PCI Handle, this is used when searching for devices to indicate
 * that the search should start at the start of the list of detected PCI-Devices.
 * \ingroup PCI_Class
 */
#define INVALID_PCI_HANDLE    ((void*)(~0))
#define PCI_BAR_QTY           6     /**< number of BARs in a PCI device (PCI standard) */



/**
 * Enumeration describing which type of memory the Base Address Registers describes.
 * \ingroup PCI_Class
 */
typedef enum
{
    L1_PCI_MEMORY_BAR,
    L1_PCI_IO_BAR,
    L1_PCI_NO_MAPPING
} L1_Drv_Pci_BarMapping;

/**
 * Description of the address type the BAR uses, 32 or 64Bit.
 * \ingroup PCI_Class
 */
typedef enum
{
    L1_PCI_32BIT_BAR,
    L1_PCI_64BIT_BAR,
    L1_PCI_BAR_UNUSED
} PciBarType;

/**
 * Enumerations of the four possible interrupt pins a device may use on the PCI bus.
 * \ingroup PCI_Class
 */
typedef enum
{
    L1_PCI_INTA = 1,
    L1_PCI_INTB = 2,
    L1_PCI_INTC = 3,
    L1_PCI_INTD = 4
} L1_Drv_Pci_InterruptPin;

/**
 * What type of device is this, can be either an end-point device or a bridge device.
 * \ingroup PCI_Class
 */
typedef enum
{
    L1_PCI_STANDARD,
    L1_PCI_PCI2PCI_BRIDGE

} L1_Drv_Pci_DeviceType;

/**
 * Detailed information about a single BAR of a PCI Device.
 * \ingroup PCI_Class
 */
typedef struct
{
    L1_UINT32 barOffset;
    L1_UINT32 barBaseLow;
    L1_UINT32 barBaseHigh;
    L1_UINT32 barSizeLow;
    L1_UINT32 barSizeHigh;
    /** The 'barBaseAddr' is a 64-bit variable
     that will contain the TOTAL base address
     value achived by combining both the 'barBaseLow'
     and the 'barBaseHigh' parameters as follows:

     BIT: 63          31         0
     |           |         |
     barBaseHigh barBaseLow */
    L1_UINT64 barBaseAddr;
    /** The 'barSize' is a 64-bit variable
     that will contain the TOTAL size achived
     by combining both the 'barSizeLow' and
     the 'barSizeHigh' parameters as follows:

     BIT: 63          31         0
     |           |         |
     barSizeHigh barSizeLow

     NOTE: The total size described above
     is AFTER the size calculation as
     described in PCI spec rev2.2 */
    L1_UINT64 barSize;
    L1_BOOL isPrefetchable;
    PciBarType barType;
    L1_Drv_Pci_BarMapping barMapping;
} L1_Drv_Pci_Bar;

struct L1_Drv_Pci_DeviceInfo_t;

/**
 * This is the signature of the callback function every PCI-Bus driver must provide. It's
 * task is to read the PCI configuration memory of a PCI-Device / PCI-Function.
 * @param self Pointer to the PCI-Device / PCI-Function of which to read the configuration memory space off.
 * @param regOff Offset of the register to read in the configuration space. The offset is given in bytes, but must be aligned to 32 bits (4 bytes).
 * @param pValue Pointer to the 32Bit unsigned integer in which to store the read out  value.
 * @return RC_OK The value could be read out.
 * @return RC_FAIL The value could not be read out.
 * \ingroup PCI_Class
 */
typedef  L1_Status (*pciDevice_ConfigRead_t)(struct L1_Drv_Pci_DeviceInfo_t * self, L1_UINT32 regOff, L1_UINT32 * pValue);


/**
 * This is the signature of the callback function every PCI-Bus driver must provide. It's
 * task is to write to the PCI configuration memory of a PCI-Device / PCI-Function.
 * @param self Pointer to the PCI-Device / PCI-Function of which to write to.
 * @param regOff Offset of the register to write to in the configuration space. The offset is given in bytes, but must be aligned to 32 bits (4 bytes).
 * @param value The value to write to the configuration space.
 * @return RC_OK The value could be written.
 * @return RC_FAIL The value could not be written.
 * \ingroup PCI_Class
 */
typedef  L1_Status (*pciDevice_ConfigWrite_t)(struct L1_Drv_Pci_DeviceInfo_t * self, L1_UINT32 regOff, L1_UINT32  value);

/**
 * This structure contains PCI-Host Controller specific functions.
 * \ingroup PCI_Class
 */
typedef struct
{
        /**
         * Callback for the function which reads the configuration space of a PCI-Device / PCI-Function.
         */
        pciDevice_ConfigRead_t  readConfig;
        /**
         * Callback for the function which writes the configuration space of a PCI-Device / PCI-Function.
         */
        pciDevice_ConfigWrite_t writeConfig;
}L1_Drv_Pci_DeviceOperations;



/**
 * PCI-Device / PCI-Function specific information.
 * \ingroup PCI_Class
 */
typedef struct
{
    /* Device specific information */
    L1_UINT32 busNumber; /* Pci agent bus number */
    L1_UINT32 deviceNum; /* Pci agent device number */
    L1_UINT32 function; /* Pci agent function number */

    L1_UINT32 venID; /* Pci agent Vendor ID */
    L1_UINT32 deviceID; /* Pci agent Device ID */

    L1_BOOL isFastB2BCapable; /* Capability of Fast Back to Back
     transactions */
    L1_BOOL isCapListSupport; /* Support of Capability list */
    L1_BOOL is66MHZCapable; /* 66MHZ support */

    L1_UINT32 baseClassCode; /* Pci agent base Class Code */
    L1_UINT32 subClassCode; /* Pci agent sub Class Code */
    L1_UINT32 progIf; /* Pci agent Programing interface */
    L1_UINT32 revisionID;

    L1_Drv_Pci_Bar pciBar[6]; /* Pci agent bar list */

    L1_UINT32 pciCacheLine; /* Pci agent cache line */
    L1_UINT32 pciLatencyTimer; /* Pci agent Latency timer  */
    L1_Drv_Pci_DeviceType pciHeader; /* Pci agent header type*/
    L1_BOOL isMultiFunction; /* Multi function support */
    L1_BOOL isBISTCapable; /* Self test capable */

    L1_UINT32 subSysID; /* Sub System ID */
    L1_UINT32 subSysVenID; /* Sub System Vendor ID */

    L1_BOOL isExpRom; /* Expantion Rom support */
    L1_UINT32 expRomAddr; /* Expantion Rom pointer */

    L1_UINT32 capListPointer; /* Capability list pointer */

    L1_UINT32 irqLine; /* IRQ line  */
    L1_Drv_Pci_InterruptPin intPin; /* Interrupt pin */
    L1_UINT32 minGrant; /* Minimum grant*/
    L1_UINT32 maxLatency; /* Maximum latency*/

    L1_UINT32 funtionsNum; /* pci agent total functions number */

    L1_UINT32 barsNum;
    L1_BYTE type[60]; /* class name of the pci agent */
    /**
     * This is used for the PMC-704 to allow read and write accessed to the device.
     */
    L1_BYTE pciInterface;
    /**
     * Pointer to the functions to use when operating on the device.
     */
    L1_Drv_Pci_DeviceOperations * operations;
} L1_Drv_Pci_Device, *L1_Drv_Pci_DeviceHandle;


/**
 * Information about a PCI device
 * Remark that most cannot be used full 32-bit, but simpler to use it as such
 * for the moment (read struct). Also more optimized towards cpu usage.
 * \ingroup PCI_Class
 */
typedef struct L1_Drv_Pci_DeviceInfo_t {
   /* uniquely defines hardware location on platform (selects device) */
   L1_UINT32  selPciRootId;     /**< if host has multiple PCI root complexes */
   L1_UINT32  selBus;
   L1_UINT32  selDevice;
   L1_UINT32  selFunction;

   /* retrieved device information */
   L1_UINT32  pciHeaderType;  /**< PCI header type */
   L1_UINT32  vendorId;
   L1_UINT32  deviceId;
   L1_UINT32  subVendorId;
   L1_UINT32  subDeviceId;
   L1_UINT32  pciClass;       /**< PCI class of device */
   L1_UINT32  pciSubClass;    /**< PCI subclass of device */
   L1_UINT32  revisionId;     /**< revision ID of the device */

   /* The Base Address Regions (BAR) */
   L1_Drv_Pci_Bar     pciBARs[6];
   /**
    * Pointer to the functions to use when operating on the device.
    */
   L1_Drv_Pci_DeviceOperations * operations;
}L1_Drv_Pci_DeviceInfo;


/**
 * Pci Controller Description.
 * \ingroup PCI_Class
 */
typedef struct
{
    /**
     * The total number of PCI devices that can be stored in the array devices.
     */
    L1_UINT32 maxQtyPciDevices;
    /**
     * This array will hold information about all devices that were detected on the PCI bus.
     * Each function of a physical device will be present as an individual device in this array.
     *
     * @warning Must not be NULL!
     */
    L1_Drv_Pci_Device * devices; /**< all detected devices */
    /**
     * Total number of detected devices.
     */
    L1_UINT32 lastDevice; /**< last valid devices in array */

    /**
     * Driver specific state information.
     */
    void * private;
} L1_Drv_Pci_Bus;

/**
 * This function checks whether or not there is a device / function with the given vendorId
 * and deviceId connected to the PCI-Bus represented by self. It starts the search for the
 * device at the location indicated by previousHandle. The result, if any, is stored in
 * pDeviceHandle, which is passed to this function in the parameter previousHandle to find
 * the next device with the same vendorId and deviceId. To detect the first device with
 * the given vendorId and deviceId the user must set the parameter previousHandle to
 * INVALID_PCI_HANDLE.
 *
 * @param self pointer to a structure of type L1_Drv_Pci_Bus, which has been previously
 * initialised using the PCI-Host Controller specific function.
 * @param vendorId The ID of the vendor that produced the PCI-Device.
 * @param deviceId The ID of the device which identifies the PCI-Device, together with the
 * vendorID.
 * @param pDeviceHandle Pointer to a variable of type L1_Drv_Pci_DeviceHandle which will
 * contain the handle if there is a device with this given vendorId and deviceId located
 * in the PCI-Bus after the device identified by previousHandle.
 * @param previousHandle Handle of the PCI-Device / PCI-Function after which the function
 * should search for the PCI-Device / PCI-Function with the given vendorId and deviceId.
 * @return RC_OK A device with the desired vendorId and deviceId was found.
 * @return RC_FAIL Otherwise.
 *
 * \ingroup PCI_Class
 */
extern L1_Status L1_Drv_Pci_Bus_findDevice(L1_Drv_Pci_Bus * self, L1_UINT32 vendorId,
                                L1_UINT32 deviceId,
                                L1_Drv_Pci_DeviceHandle * pDeviceHandle,
                                const L1_Drv_Pci_DeviceHandle previousHandle);
/**
 * Retrieve detailled information about a PCI device based on the L1_Drv_Pci_DeviceHandle
 * returned by the function L1_Drv_Pci_Bus_findDevice.
 * @param self pointer to a structure of type L1_Drv_Pci_Bus, which has been previously
 * initialised using the PCI-Host Controller specific function.
 * @param deviceHandle Handle to the PCI-Device / PCI-Function of which detailed
 * information should be acquired for.
 * @param pDeviceInfo Pointer to a variable of type L1_Drv_Pci_DeviceInfo which will
 * contain the detailed information regarding the PCI-Device / PCI-Function identified by
 * the given deviceHandle.
 * @return RC_OK If the device information could be located.
 * @return RC_FAIL Otherwise.
 * \ingroup PCI_Class
 */
extern L1_Status L1_Drv_Pci_Bus_getDeviceInfo(L1_Drv_Pci_Bus * self, L1_Drv_Pci_DeviceHandle deviceHandle,
                               L1_Drv_Pci_DeviceInfo * pDeviceInfo);


/**
 * Writes the given value into the PCI-Configuration space register indicated by `reg'.
 * The parameter width defines how many bytes are being written of the value. The function
 * can thus write 8, 16, or 32 bits into the register.
 * @param self Pointer to the PCI-Device whose PCI-Configuration space should be written to.
 * @param reg Address of the register to modify. The granularity is byte wise.
 * @param value The value to write, depending on width only the lower 8 or 16 bits are used.
 * @param width The number of bytes to write, valid values are 1,2, and 4.
 * @return RC_OK If the value could be written.
 * @return RC_FAIL If the operation was not successful.
 * \ingroup PCI_Class
 *
 */
extern L1_Status L1_Drv_Pci_Device_writeConfig(L1_Drv_Pci_DeviceInfo * self, L1_UINT32 reg,
                                L1_UINT32 value, L1_UINT32 width);

/**
 * Reads 8, 16, or 32 bits from the PCI-Configuration space at the offset ref, of the
 * PCI-Device indicated by self.
 * @param self Pointer to the PCI-Device whose PCI-Configuration space should be read from.
 * @param reg Address of the register to read. The granularity is byte wise.
 * @param width The number of bytes to read, valid values are 1,2, and 4.
 * @param pValue Pointer to a variable of type L1_UINT32, which will contain the value
 * which was read out, after the operation was successful. Depending on the parameter
 * width only the lower 8,16, or 32 bits are being used.
 * @return RC_OK If the operation was successful.
 * @return RC_FAIL If the operation was not successful.
 * \ingroup PCI_Class
 */
extern L1_Status L1_Drv_Pci_Device_readConfig(L1_Drv_Pci_DeviceInfo * self, L1_UINT32 reg,
                               L1_UINT32 width, L1_UINT32 * pValue);

#endif /* #ifndef PCIDEVICE_HEADER */
