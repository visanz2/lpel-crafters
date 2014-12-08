/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2013
 * www.Altreonic.com
 * Module name: L1_Drv_SPI.h ($Path/$Filename)
 * Synopsis: SPI driver API for OpenComRTOS.
 *
 * $LastChangedDate: 2010-11-05 10:52:18 +0100 (Fri, 05 Nov 2010) $
 * $Revision: 2037 $
 * $LastChangedBy: bernhard.sputh $
 *******************************************************************************/

#ifndef L1_DRV_SPI_H_
#define L1_DRV_SPI_H_

#include <L1_types.h>
#include <driver/class/L1_Drv_Version.h>
#include <driver/class/L1_Drv_IntC.h>

/**
 * \defgroup SPI SPI Driver API
 *
 * Information for the user of the API.
 */

/**
 * \defgroup SPI_DEVEL SPI MAC Driver Developer Information
 *
 * These information are meant for developers of SPI drivers.
 */


/**
 * The return codes of SPI drivers.
 *
 * \ingroup SPI
 */
typedef enum
{
    /**
     * The function was performed successfully.
     */
    SPI_RC_OK = 0,
    /**
     * The function failed.
     */
    SPI_RC_FAIL = 1,
    /**
     * The operation is unsupported by the device driver.
     */
    SPI_RC_FAIL_UNSUPPORTED,
    /**
      * The function cannot register the callback because there is no event of the specified type.
      */
    SPI_RC_FAIL_CALLBACK_EVENT_UNSUPPORTED,

}SPI_Status;

#if 0
// Template

/**
 * Prototype of a function which
 * @param[in] this Pointer to a structure of type L1_Drv_SPI, which represents the SPI driver class instance.
 * @return SPI_OK The function has completed successfully.
 * @return SPI_FAIL The function failed.
 * @ingroup SPI_DEVEL
 */
typedef SPI_Status (*spi_api_)(struct L1_Drv_SPI_t * this,);

/**
 * This function
 * @param[in] this Pointer to a structure of type L1_Drv_SPI, which represents the SPI driver class instance.
 * @return SPI_OK The function has completed successfully.
 * @return SPI_FAIL The function failed.
 * @ingroup SPI
 */
#ifdef API_DOC
SPI_Status L1_Drv_SPI_(struct L1_Drv_SPI_t * this, );
#else
#define L1_Drv_SPI_(this,)\
    (this)->api->( (this), () )
#endif /* API_DOC */

#endif /* 0 */


/**
 * Prototype of a function that has no additional parameters.
 * @param[in] this Pointer to a structure of type L1_Drv_SPI, which represents the SPI driver class instance.
 * @return SPI_OK The function has completed successfully.
 * @return SPI_FAIL The function failed.
 * @ingroup SPI_DEVEL
 */
typedef SPI_Status (*spi_api_no_args)(struct L1_Drv_SPI_t * this);

/**
 * This function initialises an SPI device driver.
 * @param[in] this Pointer to a structure of type L1_Drv_SPI, which represents the SPI driver class instance.
 * @return SPI_OK The function has completed successfully.
 * @return SPI_FAIL The function failed.
 * @ingroup SPI
 */
#ifdef API_DOC
SPI_Status L1_Drv_SPI_init(struct L1_Drv_SPI_t * this);
#else
#define L1_Drv_SPI_init(this)\
    (this)->api->init( (this) )
#endif /* API_DOC */


/**
 * This function aborts an ongoing transfer that was initiated either with the function L1_Drv_SPI_sendData() or the function L1_Drv_SPI_receiveData().
 * @param[in] this Pointer to a structure of type L1_Drv_SPI, which represents the SPI driver class instance.
 * @return SPI_OK The function has completed successfully.
 * @return SPI_FAIL The function failed.
 * @ingroup SPI
 */
#ifdef API_DOC
SPI_Status L1_Drv_SPI_abortTransfer(struct L1_Drv_SPI_t * this);
#else
#define L1_Drv_SPI_abortTransfer(this)\
    (this)->api->abortTransfer( (this) )
#endif /* API_DOC */



/**
 * Prototype of a function that sets the speed of the SPI-Bus.
 * @param[in] this Pointer to a structure of type L1_Drv_SPI, which represents the SPI driver class instance.
 * @param[in] bps The speed of the bus in bits per second (bps).
 *
 * @return SPI_OK The function has completed successfully.
 * @return SPI_FAIL The function failed.
 * @return SPI_RC_FAIL_UNSUPPORTED If the device does not support the chosen bus-speed.
 *
 * @ingroup SPI_DEVEL
 */
typedef SPI_Status (*spi_api_setBusSpeed)(struct L1_Drv_SPI_t * this, L1_UINT32 bps);

/**
 * This function sets the speed of the SPI-Bus.
 * @param[in] this Pointer to a structure of type L1_Drv_SPI, which represents the SPI driver class instance.
 * @param[in] bps The speed of the bus in bits per second (bps).
 *
 * @return SPI_OK The function has completed successfully.
 * @return SPI_FAIL The function failed.
 * @return SPI_RC_FAIL_UNSUPPORTED If the device does not support the chosen bus-speed.
 * @ingroup SPI
 */
#ifdef API_DOC
SPI_Status L1_Drv_SPI_setBusSpeed(struct L1_Drv_SPI_t * this, L1_UINT32 bps);
#else
#define L1_Drv_SPI_setBusSpeed(this,bps)\
    (this)->api->setBusSpeed( (this), (bps) )
#endif /* API_DOC */


#if 0
/**
 * Specifies the polarity of the clock and the phase for the SPI-data transmissions.
 */
typedef enum
{
	/**
	 * Clock Polarity 0, Clock Phase 0
	 */
	L1_Drv_SPI_CPOL0_CPHA0 = 1,
	/**
	 * Clock Polarity 0, Clock Phase 1
	 */
	L1_Drv_SPI_CPOL0_CPHA1,
	/**
	 * Clock Polarity 1, Clock Phase 0
	 */
	L1_Drv_SPI_CPOL1_CPHA0,
	/**
	 * Clock Polarity 1, Clock Phase 1
	 */
	L1_Drv_SPI_CPOL1_CPHA1,
}L1_Drv_SPI_frameFormat;
#endif /* 0 */
typedef enum
{
	/**
	 * Clock starts low, data read on clock's rising edge, data changes on falling edge.
	 */
	L1_Drv_SPI_FF_MODE0 = 1,
	/**
	 * Clock starts low, data read on clock's falling edge, data changes on rising edge.
	 */
	L1_Drv_SPI_FF_MODE1,
	/**
	 * Clock starts high, data read on clock's falling edge, data changes on rising edge.
	 */
   L1_Drv_SPI_FF_MODE2,
   /**
    * Clock starts high, data read on clock's rising edge, data changes on falling edge.
    */
   L1_Drv_SPI_FF_MODE3,
}L1_Drv_SPI_frameFormat;

/**
 * Specifies whether SPI data transmissions start with the least signification
 * bit (LSB) or the most signification bit (MSB).
 */
typedef enum
{
	/**
	 * Transmission starts with the least significant bit (LSB).
	 */
	L1_Drv_SPI_LSB,
	/**
	 * Transmission starts with the most significant bit (MSB).
	 */
	L1_Drv_SPI_MSB,
}L1_Drv_SPI_bitOrder;

/**
 * Prototype of a function that configures the data transmission parameters of the SPI Interface..
 * @param[in] this Pointer to a structure of type L1_Drv_SPI, which represents the SPI driver class instance.
 * @param[in] frameFormat Defines the frame format to use when transmitting data.
 * @param[in] bitOrder defines whether to start transmission with the least or most significant bit.
 * @return SPI_OK The function has completed successfully.
 * @return SPI_FAIL The function failed.
 * @ingroup SPI_DEVEL
 */
typedef SPI_Status (*spi_api_configure)(struct L1_Drv_SPI_t * this, L1_UINT32 slaveNumber, L1_Drv_SPI_frameFormat frameFormat, L1_Drv_SPI_bitOrder bitOrder);

/**
 * This function configures the data transmission parameters of the SPI Interface.
 * @param[in] this Pointer to a structure of type L1_Drv_SPI, which represents the SPI driver class instance.
 * @param[in] frameFormat Defines the frame format to use when transmitting data.
 * @param[in] bitOrder defines whether to start transmission with the least or most significant bit.
 * @return SPI_OK The function has completed successfully.
 * @return SPI_FAIL The function failed.
 * @ingroup SPI
 */
#ifdef API_DOC
SPI_Status L1_Drv_SPI_configure(struct L1_Drv_SPI_t * this, L1_UINT32 slaveNumber, L1_Drv_SPI_frameFormat frameFormat, L1_Drv_SPI_bitOrder bitOrder);
#else
#define L1_Drv_SPI_configure(this, slaveNumber, frameFormat, bitOrder)\
    (this)->api->configure( (this), (slaveNumber), (frameFormat), (bitOrder) )
#endif /* API_DOC */

/**
 * Different possible callbacks that can be registered for a SPI, using the registerCallBack operation of the driver.
 * \ingroup L1_DRV_UART
 */
typedef enum
{
	/**
	 * Gets called every time a frame has been received.
	 */
	SPI_CB_RX_FRAME  = 1,
	/**
	 * Gets called every time the MAC has returned a free TX-Descriptor, i.e. a new MAC-Frame can be sent.
	 */
	SPI_CB_TX_FRAME  = 2,

}L1_Drv_SPI_CallBackEvents;

/**
 * Prototype of a function which registers a callback function for a specific event.
 * @param[in] this Pointer to a structure of type L1_Drv_SPI, which represents the SPI driver class instance.
 * @param[in] event The type of call-back to register. Please note not all drivers support all types of call-backs.
 * @param[in] callBack The call back function to register.
 * @param[in] pParam The parameter to pass to the call-back function when calling it.
 * @return SPI_RC_OK The function could be performed successfully.
 * @return SPI_RC_FAIL The function failed.
 * @return SPI_RC_FAIL_CALLBACK_EVENT_UNSUPPORTED The type of call-back is not supported by the UART-Driver.
 *
 * \ingroup SPI_DEVEL
 */
typedef SPI_Status (*spi_api_registerCallBack)(struct L1_Drv_SPI_t * this, L1_Drv_SPI_CallBackEvents event, L1_ISR_CALLBACK callBack, void * pParam);


/**
 * This function which registers a callback function for a specific event.
 * @param[in] this Pointer to a structure of type L1_Drv_SPI, which represents the SPI driver class instance.
 * @param[in] event The type of call-back to register. Please note not all drivers support all types of call-backs.
 * @param[in] callBack The call back function to register.
 * @param[in] pParam The parameter to pass to the call-back function when calling it.
 * @return SPI_RC_OK The function could be performed successfully.
 * @return SPI_RC_FAIL The function failed.
 * @return SPI_RC_FAIL_CALLBACK_EVENT_UNSUPPORTED The type of call-back is not supported by the UART-Driver.
 *
 * \ingroup SPI
 */
#ifdef API_DOC
SPI_Status L1_Drv_SPI_registerCallBack(struct L1_Drv_SPI_t * this, L1_Drv_SPI_CallBackEvents event, L1_ISR_CALLBACK callBack, void * pParam);
#else
#define L1_Drv_SPI_registerCallBack(this, event, callBack, pParam)\
    (this)->api->registerCallBack( (this), (event), (callBack), (pParam) )
#endif /* API_DOC */



/**
 * Prototype of a function which sends one byte and at the same time receives one byte. This is the basic SPI data transfer mode.
 * @param[in] this Pointer to a structure of type L1_Drv_SPI, which represents the SPI driver class instance.
 * @param[in] byteToSend The byte to be send over the SPI Interface.
 * @param[out] pReceivedByte Pointer to a variable of L1_BYTE which will contain the byte that was received from the bus due to the send operation.
 * @return SPI_OK The function has completed successfully.
 * @return SPI_FAIL The function failed.
 * @ingroup SPI_DEVEL
 */
typedef SPI_Status (*spi_api_transferByte)(struct L1_Drv_SPI_t * this, L1_BYTE byteToSend, L1_BYTE * pReceivedByte);

/**
 * Prototype of a function which sends one buffer and at the same time receives one buffer. This is the basic SPI data transfer mode.
 * @param[in] this
 * @param[in] txBuffer
 * @param[in] txBufferSize
 * @param[out] rxBuffer
 * @param[in] rxBufferSize
 * @return SPI_RC_OK The function ended successfully.
 * @return SPI_RC_FAIL The function failed.
 */
typedef SPI_Status (*spi_api_transferBlock)(struct L1_Drv_SPI_t * this, const L1_UINT8 * txBuffer, L1_UINT16 txBufferSize, L1_UINT8 * rxBuffer, L1_UINT16 rxBufferSize);

#ifdef API_DOC
SPI_Status L1_Drv_SPI_transferBlock(struct L1_Drv_SPI_t * this, const L1_UINT8 * txBuffer, L1_UINT16 txBufferSize, L1_UINT8 * rxBuffer, L1_UINT16 rxBufferSize);
#else
#define L1_Drv_SPI_transferBlock(this, txBuffer, txBufferSize, rxBuffer, rxBufferSize) \
	(this)->api->transferBlock((this), (txBuffer), (txBufferSize), (rxBuffer), (rxBufferSize))
#endif /* API_DOC*/

/**
 * This function sends one byte and at the same time receives one byte. This is the basic SPI data transfer mode.
 * @param[in] this Pointer to a structure of type L1_Drv_SPI, which represents the SPI driver class instance.
 * @param[in] byteToSend The byte to be send over the SPI Interface.
 * @param[out] pReceivedByte Pointer to a variable of L1_BYTE which will contain the byte that was received from the bus due to the send operation.
 * @return SPI_OK The function has completed successfully.
 * @return SPI_FAIL The function failed.
 * @ingroup SPI
 */
#ifdef API_DOC
SPI_Status L1_Drv_SPI_transferByte(struct L1_Drv_SPI_t * this, L1_BYTE byteToSend, L1_BYTE * pReceivedByte);
#else
#define L1_Drv_SPI_transferByte(this, byteToSend, pReceivedByte)\
    (this)->api->transferByte( (this), (byteToSend), (pReceivedByte) )
#endif /* API_DOC */

/**
 * Prototype of a function which enables or disables an option.
 * @param[in] this Pointer to a structure of type L1_Drv_SPI, which represents the SPI driver class instance.
 * @param[in] flag Boolean value which determines whether to enable (L1_TRUE) or disable (L1_FALSE) the option.
 * @return SPI_OK The function has completed successfully.
 * @return SPI_FAIL The function failed.
 * @ingroup SPI_DEVEL
 */
typedef SPI_Status (*spi_api_enable)(struct L1_Drv_SPI_t * this, L1_BOOL flag);

/**
 * BSP: Document me.
 * @param this
 * @param slaveNumber
 * @return
 */
typedef SPI_Status (*spi_api_slave_select)(struct L1_Drv_SPI_t * this, L1_UINT8 slaveNumber);

/**
 * This function enables the generation of the Slave Select Signal in the SPI Interface device.
 * @param[in] this Pointer to a structure of type L1_Drv_SPI, which represents the SPI driver class instance.
 * @param[in] slaveNumber The number of the slave to enable. SPI-Controller dependent.
 * @return SPI_OK The function has completed successfully.
 * @return SPI_FAIL The function failed.
 * @return SPI_RC_FAIL_UNSUPPORTED If the device does not support this functionality.
 * @ingroup SPI
 */
#ifdef API_DOC
SPI_Status L1_Drv_SPI_generateSlaveSelectSignal(struct L1_Drv_SPI_t * this, L1_UINT8 slaveNumber);
#else
#define L1_Drv_SPI_generateSlaveSelectSignal(this, slaveNumber)\
    (this)->api->generateSlaveSelectSignal( (this), (slaveNumber) )
#endif /* API_DOC */



/**
 * The Interface of the SPI device driver class.
 * \ingroup SPI_DEVEL
 */
typedef struct{
        drv_api_get_version getVersion;
        spi_api_no_args init;
        spi_api_setBusSpeed setBusSpeed;
        spi_api_configure configure;
        spi_api_registerCallBack registerCallBack;
        spi_api_transferByte transferByte;
        spi_api_transferBlock transferBlock;
        spi_api_slave_select generateSlaveSelectSignal;
}L1_Drv_SPI_API;


typedef struct L1_Drv_SPI_t{
        L1_Drv_SPI_API * api;
        void * self;
}L1_Drv_SPI;

/**
 * This is the API-Version of the L1_Drv_SPI API. It has the following structure:
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
#define L1_DRV_SPI_API_VERSION 0x00010002



#endif /* L1_DRV_SPI_H_ */
