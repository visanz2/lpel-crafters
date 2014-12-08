/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2013
 * www.Altreonic.com
 * Module name: L1_Drv_I2C.h ($Path/$Filename)
 * Synopsis: I2C driver API for OpenComRTOS.
 *
 * $LastChangedDate: 2010-11-05 10:52:18 +0100 (Fri, 05 Nov 2010) $
 * $Revision: 2037 $
 * $LastChangedBy: bernhard.sputh $
 *******************************************************************************/

#ifndef L1_DRV_I2C_H_
#define L1_DRV_I2C_H_

#include <L1_types.h>
#include <driver/class/L1_Drv_Version.h>
#include <driver/class/L1_Drv_IntC.h>

/*
 * Forward declaration.
 */
struct L1_Drv_I2C_t;

/**
 * \defgroup I2C I2C Driver API
 *
 * Information for the user of the API.
 */

/**
 * \defgroup I2C_DEVEL I2C MAC Driver Developer Information
 *
 * These information are meant for developers of I2C drivers.
 */


/**
 * The return codes of I2C drivers.
 *
 * \ingroup I2C
 */
typedef enum
{
    /**
     * The function was performed successfully.
     */
    I2C_RC_OK = 0,
    /**
     * The function failed.
     */
    I2C_RC_FAIL = 1,
    /**
     * The operation is unsupported by the device driver.
     */
    I2C_RC_FAIL_UNSUPPORTED,
    /**
      * The function cannot register the callback because there is no event of the specified type.
      */
    I2C_RC_FAIL_CALLBACK_EVENT_UNSUPPORTED,
    /**
     * The I2C-Bus is busy with another transaction.
     */
    I2C_RC_FAIL_BUS_BUSY,

}I2C_Status;

#if 0
// Template

/**
 * Prototype of a function which
 * @param[in] this Pointer to a structure of type L1_Drv_I2C, which represents the I2C driver class instance.
 * @return I2C_OK The function has completed successfully.
 * @return I2C_FAIL The function failed.
 * @ingroup I2C_DEVEL
 */
typedef I2C_Status (*I2C_api_)(struct L1_Drv_I2C_t * this,);

/**
 * This function
 * @param[in] this Pointer to a structure of type L1_Drv_I2C, which represents the I2C driver class instance.
 * @return I2C_OK The function has completed successfully.
 * @return I2C_FAIL The function failed.
 * @ingroup I2C
 */
#ifdef API_DOC
I2C_Status L1_Drv_I2C_(struct L1_Drv_I2C_t * this, );
#else
#define L1_Drv_I2C_(this,)\
    (this)->api->( (this), () )
#endif /* API_DOC */

#endif /* 0 */


/**
 * Prototype of a function that has no additional parameters.
 * @param[in] this Pointer to a structure of type L1_Drv_I2C, which represents the I2C driver class instance.
 * @return I2C_OK The function has completed successfully.
 * @return I2C_FAIL The function failed.
 * @ingroup I2C_DEVEL
 */
typedef I2C_Status (*I2C_api_no_args)(struct L1_Drv_I2C_t * this);


/**
 * The type of addresses the I2C-Device uses.
 */
typedef enum
{
	/**
	 * The device uses 7Bit addressing.
	 */
	I2C_7_ADDRESS_BITS = 0,
	/**
	 * The device uses 10Bit Addressing.
	 */
	I2C_10_ADDRESS_BITS = 1,
}L1_Drv_I2C_AddressType;

/**
 * I2C Slave Device address.
 */
typedef struct
{
	/**
	 * The address of the I2C-device.
	 */
	L1_UINT16 address;
	/**
	 * The address type, i.e. is it a 7bit or 10bit address.
	 */
	L1_Drv_I2C_AddressType type;
	/**
	 * Indicates whether or not to use register addressing.
	 */
	L1_BOOL registerAddressing;
	/**
	 * 16bit Register Addresses
	 */
	L1_BOOL wideRegisterAddresses;
}L1_Drv_I2C_Address;

typedef L1_BOOL (*I2C_callback)(void * pArg, I2C_Status status);

typedef I2C_Status (*I2C_read)(struct L1_Drv_I2C_t * this, L1_Drv_I2C_Address address, L1_UINT16 reg, L1_UINT8 * buffer, L1_UINT16 nbrOfBytesToRead, I2C_callback callback, void * pArg);

typedef I2C_Status (*I2C_write)(struct L1_Drv_I2C_t * this, L1_Drv_I2C_Address address, L1_UINT16 reg, L1_UINT8 * buffer, L1_UINT16 nbrOfBytesToWrite, I2C_callback callback, void * pArg);


/**
 * The Interface of the I2C device driver class.
 * \ingroup I2C_DEVEL
 */
typedef struct{
        //drv_api_get_version getVersion;
        I2C_api_no_args init;
        I2C_read read;
        I2C_write write;
}L1_Drv_I2C_API;


typedef struct L1_Drv_I2C_t{
        L1_Drv_I2C_API * api;
        void * self;
}L1_Drv_I2C;




/**
 * This function initialises an I2C device driver.
 * @param[in] this Pointer to a structure of type L1_Drv_I2C, which represents the I2C driver class instance.
 * @return I2C_RC_OK The function has completed successfully.
 * @return I2C_RC_FAIL The function failed.
 * @ingroup I2C
 */
static inline I2C_Status L1_Drv_I2C_init(struct L1_Drv_I2C_t * this)
{
    if(NULL == this)
    {
        return I2C_RC_FAIL;
    }
    return this->api->init(this);
}
/**
 * This function enqueues a read request at the I2C-Driver.
 * The function may return before the read request has been completed.
 * In case an error is encountered or the read operation completed the
 * function calls the indicated callback routine with the argument pArg.
 *
 * @param[in] this Pointer to a structure of type L1_Drv_I2C, which represents the I2C driver class instance.
 * @param[in] address The I2C-Address of the device.
 * @param[in] reg The address of the register to read from, in case the device requires register access.
 * @param[inout] buffer Pointer to the buffer where to store the read bytes.
 * @param[in] nbrOfBytesToRead How many bytes to read from the device.
 * @param[in] callback Function to call when the operation completed.
 * @param[in] pArg Argument to pass to the callback function.
 * @return
 */
static inline I2C_Status L1_Drv_I2C_read(struct L1_Drv_I2C_t * this, L1_Drv_I2C_Address address, L1_UINT16 reg, L1_UINT8 * buffer, L1_UINT16 nbrOfBytesToRead, I2C_callback callback, void * pArg)
{
    if(NULL == this)
    {
        return I2C_RC_FAIL;
    }
    return this->api->read(this, address, reg, buffer, nbrOfBytesToRead, callback, pArg);
}

/**
 * This function enqueues a write request at the I2C-Driver.
 * The function may return before the read request has been completed.
 * In case an error is encountered or the read operation completed the
 * function calls the indicated callback routine with the argument pArg.
 *
 * @param[in] this Pointer to a structure of type L1_Drv_I2C, which represents the I2C driver class instance.
 * @param[in] address The I2C-Address of the device.
 * @param[in] reg The address of the register to write to, in case the device requires register access.
 * @param[inout] buffer Pointer to the buffer where the bytes are stored that should be written to the device.
 * @param[in] nbrOfBytesToWrite How many bytes should be written to the device.
 * @param[in] callback Function to call when the operation completed.
 * @param[in] pArg Argument to pass to the callback function.
 * @return
 */
static inline I2C_Status L1_Drv_I2C_write(struct L1_Drv_I2C_t * this, L1_Drv_I2C_Address address, L1_UINT16 reg, L1_UINT8 * buffer, L1_UINT16 nbrOfBytesToWrite, I2C_callback callback, void * pArg)
{
    if(NULL == this)
    {
        return I2C_RC_FAIL;
    }
    return this->api->write(this, address, reg, buffer, nbrOfBytesToWrite, callback, pArg);
}

/**
 * This is the API-Version of the L1_Drv_I2C API. It has the following structure:
 * - MSByte: Major Version
 * - 23--16: Minor Version
 * - 15--8 : Release status:
 * 			- 0: Alpha
 * 			- 1: Beta
 * 			- 2: Release Candidate
 * 			- 3: Public Release
 * - LSByte: Patch-level
 * \ingroup ETHMAC_DEVEL
 */
#define L1_DRV_I2C_API_VERSION 0x00010002

#endif /* L1_DRV_I2C_H_ */
