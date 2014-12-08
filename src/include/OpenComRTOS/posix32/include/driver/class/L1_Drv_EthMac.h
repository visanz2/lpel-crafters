/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2013
 * www.Altreonic.com
 * Module name: L1_Drv_EthMac.h ($Path/$Filename)
 * Synopsis: Ethernet MAC driver API for OpenComRTOS.
 *
 * $LastChangedDate: 2010-11-05 10:52:18 +0100 (Fri, 05 Nov 2010) $
 * $Revision: 2037 $
 * $LastChangedBy: bernhard.sputh $
 *******************************************************************************/

#ifndef L1_DRV_ETHMAC_H_
#define L1_DRV_ETHMAC_H_

#include <L1_types.h>
#include <driver/class/L1_Drv_Version.h>
#include <driver/class/L1_Drv_IntC.h>

/**
 * \defgroup ETHMAC Ethernet MAC Driver API
 *
 * Information for the user of the API.
 */

/**
 * \defgroup ETHMAC_DEVEL Ethernet MAC Driver Developer Information
 *
 * These information are meant for developers of Ethernet MAC drivers.
 */


/**
 * The return codes of Ethernet MAC drivers.
 *
 * \ingroup ETHMAC
 */
typedef enum
{
    /**
     * The function was performed successfully.
     */
    ETH_MAC_RC_OK = 0,
    /**
     * The function failed.
     */
    ETH_MAC_RC_FAIL = 1,
    /**
     * The desired function is not supported.
     */
    ETH_MAC_RC_FAIL_UNSUPPORTED = 2,
    /**
     * The function failed, because the frame is too large.
     */
    ETH_MAC_RC_FAIL_INVALID_FRAME_LENGTH = 3,
    /**
     * The function failed because there is not enough space in the frame-buffer to store the complete frame.
     */
    ETH_MAC_RC_FAIL_BUFFER_TOO_SMALL = 4,
    /**
     * The function failed, because the RX-Engine is disabled.
     */
    ETH_MAC_RC_FAIL_RX_DISABLED = 5,
    /**
     * Invalid PHY-Device address.
     */
    ETH_MAC_RC_FAIL_INVALID_PHY_DEVICE = 6,
    /**
     * Invalid register address.
     */
    ETH_MAC_RC_FAIL_INVALID_REGISTER = 7,
    /**
      * The function cannot register the callback because there is no event of the specified type.
      */
    ETH_MAC_RC_FAIL_CALLBACK_EVENT_UNSUPPORTED = 8,
    /**
     * There is no data available
     */
    ETH_MAC_RC_FAIL_RX_EMPTY = 9,
    /**
     * Cannot send a frame as there is no available buffer for it.
     */
    ETH_MAC_RC_FAIL_TX_FULL = 10,

}EthMac_Status;


/**
 *  Ethernet The Ethernet MAC Address structure.
 *  \ingroup ETHMAC
 */
typedef struct{
        /**
         * The 48 bit MAC-Address
         */
        L1_BYTE address[6];
}L1_Drv_EthMac_MacAddress;

/**
 * Forward declaration of the device structure.
 */
struct L1_Drv_EthMac_t;


#if 0
// Template

typedef EthMac_Status (*ethmac_)(struct L1_Drv_EthMac_t * this,);

#ifdef API_DOC
EthMac_Status L1_Drv_EthMac_(struct L1_Drv_EthMac_t * this, );
#else
#define L1_Drv_EthMac_(this,)\
    (this)->api->close( (this), () )
#endif /* API_DOC */

#endif /* 0 */


/**
 * Prototype of a function which either sets or gets a MAC-Address.
 * @param this Pointer to the EthernetMac driver instance to work on.
 * @param pMacAddress Pointer to a variable of type  EthMac_MacAddress which contains the MAC-Address to set as multicast address.
 * @return EthMac_Status depending on the individual call-back.
 * \ingroup ETHMAC_DEVEL
 */
typedef EthMac_Status (*ethmac_api_with_mac)(struct L1_Drv_EthMac_t * this, L1_Drv_EthMac_MacAddress * pMacAddress);

/**
 * Initialises an Ethernet MAC device driver.
 * @param this Pointer to the EthernetMac driver instance to work on.
 * @param pMacAddress Pointer to the MAC-Address to set to the device. If the device allows the setting of the MAC-Address, otherwise it may be NULL.
 * @return ETH_MAC_RC_OK The function could be performed successfully.
 * @return ETH_MAC_FAIL The function failed.
 * @warning Not all devices allow the setting of the MAC-Address. Check the documentation of the MAC device.
 * \ingroup ETHMAC
 */
#ifdef API_DOC
EthMac_Status L1_Drv_EthMac_init(struct L1_Drv_EthMac_t * this, L1_Drv_EthMac_MacAddress * pMacAddress);
#else
#define L1_Drv_EthMac_init(this, pMacAddress)\
    (this)->api->init( (this), (pMacAddress) )
#endif /* API_DOC */


/**
 * Retrieves the MAC-Address of the device.
 * @param this Pointer to the EthernetMac driver instance to work on.
 * @param pMacAddress Pointer to a variable of type  EthMac_MacAddress which will hold the MAC-Address after this function returned successfully.
 * @return ETH_MAC_RC_OK The function could be performed successfully.
 * @return ETH_MAC_RC_FAIL The function failed.
 * \ingroup ETHMAC
 */
#ifdef API_DOC
EthMac_Status L1_Drv_EthMac_getMacAddress(struct L1_Drv_EthMac_t * this, L1_Drv_EthMac_MacAddress * pMacAddress);
#else
#define L1_Drv_EthMac_getMacAddress(this, pMacAddress)\
    (this)->api->getMacAddress( (this), (pMacAddress) )
#endif /* API_DOC */

/**
 * Configures Ethernet multicast address filtering.
 * @param this Pointer to the EthernetMac driver instance to work on.
 * @param pMacAddress Pointer to a variable of type  EthMac_MacAddress which contains the MAC-Address to set as multicast address.
 * @return ETH_MAC_RC_OK The function could be performed successfully.
 * @return ETH_MAC_RC_FAIL The function failed.
 * @return ETH_MAC_RC_FAIL_UNSUPPORTED The driver does not support setting of a multicast addresss.
 * \ingroup ETHMAC
 */
#ifdef API_DOC
EthMac_Status L1_Drv_EthMac_setMulticastAddr(struct L1_Drv_EthMac_t * this, L1_Drv_EthMac_MacAddress * pMacAddress);
#else
#define L1_Drv_EthMac_setMulticastAddr(this, pMacAddress)\
    (this)->api->setMulticastAddr( (this), (pMacAddress) )
#endif /* API_DOC */



/**
 * Prototype of a function which sets a flag.
 * @param this Pointer to the EthernetMac driver instance to work on.
 * @param flag Boolean value with indicates whether or not set or erase a flag.
 * @return EthMac_Status depending on the individual call-back.
 * \ingroup ETHMAC_DEVEL
 */
typedef EthMac_Status (*ethmac_api_with_bool)(struct L1_Drv_EthMac_t * this, L1_BOOL flag);

/**
 * Enables or disables the TX-Engine of the Ethernet-MAC.
 * @param this Pointer to the EthernetMac driver instance to work on.
 * @param enable Boolean value with indicates whether to enable (L1_TRUE) or disable (L1_FALSE) the engine.
 * @return ETH_MAC_RC_OK The function could be performed successfully.
 * @return ETH_MAC_RC_FAIL The function failed.
 * \ingroup ETHMAC
 */
#ifdef API_DOC
EthMac_Status L1_Drv_EthMac_enableTx(struct L1_Drv_EthMac_t * this, L1_BOOL enable);
#else
#define L1_Drv_EthMac_enableTx(this, enable)\
    (this)->api->enableTx( (this), (enable) )
#endif /* API_DOC */


/**
 * Enables or disables the RX-Engine of the Ethernet-MAC.
 * @param this Pointer to the EthernetMac driver instance to work on.
 * @param enable Boolean value with indicates whether to enable (L1_TRUE) or disable (L1_FALSE) the engine.
 * @return ETH_MAC_RC_OK The function could be performed successfully.
 * @return ETH_MAC_RC_FAIL The function failed.
 * \ingroup ETHMAC
 */
#ifdef API_DOC
EthMac_Status L1_Drv_EthMac_enableRx(struct L1_Drv_EthMac_t * this, L1_BOOL enable);
#else
#define L1_Drv_EthMac_enableRx(this, enable)\
    (this)->api->enableRx( (this), (enable) )
#endif /* API_DOC */





/**
 * Prototype of a function which sends a MAC-Frame to the Ethernet Device.
 * @param this Pointer to the EthernetMac driver instance to work on.
 * @param frame Pointer to the MAC-Frame to send.
 * @param length Length of the MAC-Frame in bytes.
 * @return ETH_MAC_RC_OK The function could be performed successfully.
 * @return ETH_MAC_RC_FAIL The function failed.
 * @return ETH_MAC_RC_FAIL_INVALID_FRAME_LENGTH The function failed, because the frame is too large.
 * @return ETH_MAC_RC_FAIL_TX_DISABLED The function failed, because the TX-Engine is disabled.
 * @return ETH_MAC_RC_FAIL_TX_FULL The frame could not be send because there is no space available in the TX-Buffer.
 * \ingroup ETHMAC_DEVEL
 */
typedef EthMac_Status (*ethmac_api_putFrame)(struct L1_Drv_EthMac_t * this, L1_BYTE * frame, L1_UINT32 length);

/**
 * Sends a MAC-Frame to the Ethernet Device.
 * @param this Pointer to the EthernetMac driver instance to work on.
 * @param frame Pointer to the MAC-Frame to send.
 * @param length Length of the MAC-Frame in bytes.
 * @return ETH_MAC_RC_OK The function could be performed successfully.
 * @return ETH_MAC_RC_FAIL The function failed.
 * @return ETH_MAC_RC_FAIL_INVALID_FRAME_LENGTH The function failed, because the frame is too large.
 * @return ETH_MAC_RC_FAIL_TX_DISABLED The function failed, because the TX-Engine is disabled.
 * @return ETH_MAC_RC_FAIL_TX_FULL The frame could not be send because there is no space available in the TX-Buffer.
 *
 * \ingroup ETHMAC
 */
#ifdef API_DOC
EthMac_Status L1_Drv_EthMac_putFrame_W(struct L1_Drv_EthMac_t * this, L1_BYTE * frame, L1_UINT32 length);
#else
#define L1_Drv_EthMac_putFrame_W(this, frame, length)\
    (this)->api->putFrame_W( (this), (frame), (length) )
#endif /* API_DOC */


/**
 * Sends a MAC-Frame to the Ethernet Device. This function waits until it could send the MAC-Frame. This is only meant to be used durign the bringup of a link driver.
 * @param this Pointer to the EthernetMac driver instance to work on.
 * @param frame Pointer to the MAC-Frame to send.
 * @param length Length of the MAC-Frame in bytes.
 * @return ETH_MAC_RC_OK The function could be performed successfully.
 * @return ETH_MAC_RC_FAIL The function failed.
 * @return ETH_MAC_RC_FAIL_INVALID_FRAME_LENGTH The function failed, because the frame is too large.
 * @return ETH_MAC_RC_FAIL_TX_DISABLED The function failed, because the TX-Engine is disabled.
 *
 * \ingroup ETHMAC
 */
#ifdef API_DOC
EthMac_Status L1_Drv_EthMac_putFrame_NW(struct L1_Drv_EthMac_t * this, L1_BYTE * frame, L1_UINT32 length);
#else
#define L1_Drv_EthMac_putFrame_NW(this, frame, length)\
    (this)->api->putFrame_NW( (this), (frame), (length) )
#endif /* API_DOC */


/**
 * Prototype of a function which reads a MAC-Frame from an Ethernet Device.
 * @param this Pointer to the EthernetMac driver instance to work on.
 * @param frame Pointer to the buffer where to store the read MAC-Frame.
 * @param length Length of the MAC-Frame buffer in bytes.
 * @param pFrameLength pointer to a variable of type L1_UINT32 which will contain the length of the read MAC-Frame in bytes.
 * @return ETH_MAC_RC_OK The function could be performed successfully.
 * @return ETH_MAC_FAIL The function failed.
 * @return ETH_MAC_FAIL_BUFFER_TOO_SMALL The function failed because there is not enough space in the frame-buffer to store the complete frame.
 * @return ETH_MAC_FAIL_RX_DISABLED The function failed, because the RX-Engine is disabled.
 * @return ETH_MAC_RC_FAIL_RX_EMPTY Currently there is no frame available.
 * \ingroup ETHMAC_DEVEL
 */
typedef EthMac_Status (*ethmac_api_getFrame)(struct L1_Drv_EthMac_t * this, L1_BYTE * frame, L1_UINT32 length, L1_UINT32 * pFrameLength);

/**
 * Reads a MAC-Frame from the Ethernet Device.
 * @param this Pointer to the EthernetMac driver instance to work on.
 * @param frame Pointer to the buffer where to store the read MAC-Frame.
 * @param length Length of the MAC-Frame buffer in bytes.
 * @param pFrameLength pointer to a variable of type L1_UINT32 which will contain the length of the read MAC-Frame in bytes.
 * @return ETH_MAC_RC_OK The function could be performed successfully.
 * @return ETH_MAC_RC_FAIL The function failed.
 * @return ETH_MAC_RC_FAIL_BUFFER_TOO_SMALL The function failed because there is not enough space in the frame-buffer to store the complete frame.
 * @return ETH_MAC_RC_FAIL_RX_DISABLED The function failed, because the RX-Engine is disabled.
 * @return ETH_MAC_RC_FAIL_RX_EMPTY Currently there is no frame available.
 *
 * \ingroup ETHMAC
 */
#ifdef API_DOC
EthMac_Status L1_Drv_EthMac_getFrame_NW(struct L1_Drv_EthMac_t * this, L1_BYTE * frame, L1_UINT32 length, L1_UINT32 * pFrameLength);
#else
#define L1_Drv_EthMac_getFrame_NW(this, frame, length, pFrameLength)\
    (this)->api->getFrame_NW( (this), (frame), (length), (pFrameLength))
#endif /* API_DOC */


/**
 * Reads a MAC-Frame from the Ethernet Device. This function blocks until a frame was received. This is only meant to be used in Link-Drivers.
 * @param this Pointer to the EthernetMac driver instance to work on.
 * @param frame Pointer to the buffer where to store the read MAC-Frame.
 * @param length Length of the MAC-Frame buffer in bytes.
 * @param pFrameLength pointer to a variable of type L1_UINT32 which will contain the length of the read MAC-Frame in bytes.
 * @return ETH_MAC_RC_OK The function could be performed successfully.
 * @return ETH_MAC_RC_FAIL The function failed.
 * @return ETH_MAC_RC_FAIL_BUFFER_TOO_SMALL The function failed because there is not enough space in the frame-buffer to store the complete frame.
 * @return ETH_MAC_RC_FAIL_RX_DISABLED The function failed, because the RX-Engine is disabled.
 *
 * \ingroup ETHMAC
 */
#ifdef API_DOC
EthMac_Status L1_Drv_EthMac_getFrame_W(struct L1_Drv_EthMac_t * this, L1_BYTE * frame, L1_UINT32 length, L1_UINT32 * pFrameLength);
#else
#define L1_Drv_EthMac_getFrame_W(this, frame, length, pFrameLength)\
    (this)->api->getFrame_W( (this), (frame), (length), (pFrameLength))
#endif /* API_DOC */


/**
 * Prototype of a function which writes a value to a PHY Register of the MAC through the Management Interface.
 * @param this Pointer to the EthernetMac driver instance to work on.
 * @param phyAddr 5-bit PHY-Device address
 * @param regAddress 5-bit PHY register address
 * @param value 16-bit value to be written to the register.
 * @return ETH_MAC_RC_OK The function could be performed successfully.
 * @return ETH_MAC_RC_FAIL The function failed.
 * @return ETH_MAC_RC_FAIL_INVALID_PHY_DEVICE Invalid PHY-Device address.
 * @return ETH_MAC_RC_FAIL_INVALID_REGISTER Invalid register address.
 *
 * \ingroup ETHMAC_DEVEL
 */
typedef EthMac_Status (*ethmac_api_phy_reg_write)(struct L1_Drv_EthMac_t * this, L1_UINT8 phyAddr, L1_UINT8 regAddress, L1_UINT16 value);

/**
 * This function writes a value to a PHY Register of the MAC through the Management Interface.
 * @param this Pointer to the EthernetMac driver instance to work on.
 * @param phyAddr 5-bit PHY-Device address
 * @param regAddress 5-bit PHY register address
 * @param value 16-bit value to be written to the register.
 * @return ETH_MAC_RC_OK The function could be performed successfully.
 * @return ETH_MAC_RC_FAIL The function failed.
 * @return ETH_MAC_RC_FAIL_INVALID_PHY_DEVICE Invalid PHY-Device address.
 * @return ETH_MAC_RC_FAIL_INVALID_REGISTER Invalid register address.
 *
 * \ingroup ETHMAC
 */
#ifdef API_DOC
EthMac_Status L1_Drv_EthMac_phyRegWrite(struct L1_Drv_EthMac_t * this, L1_UINT8 phyAddr, L1_UINT8 regAddress, L1_UINT16 value);
#else
#define L1_Drv_EthMac_phyRegWrite(this, phyAddr, regAddress, value)\
    (this)->api->phyRegWrite( (this), (phyAddr), (regAddress), (value) )
#endif /* API_DOC */


/**
 * Prototype of a function which reads the content of a PHY Register of the MAC through the Management Interface.
 * @param this Pointer to the EthernetMac driver instance to work on.
 * @param phyAddr 5-bit PHY-Device address
 * @param regAddress 5-bit PHY register address
 * @param pValue Pointer to a variable of type L1_UINT16 where the register content should be stored.
 * @return ETH_MAC_RC_OK The function could be performed successfully.
 * @return ETH_MAC_RC_FAIL The function failed.
 * @return ETH_MAC_RC_FAIL_INVALID_PHY_DEVICE Invalid PHY-Device address.
 * @return ETH_MAC_RC_FAIL_INVALID_REGISTER Invalid register address.
 *
 * \ingroup ETHMAC_DEVEL
 */
typedef EthMac_Status (*ethmac_api_phy_reg_read)(struct L1_Drv_EthMac_t * this, L1_UINT8 phyAddr, L1_UINT8 regAddress, L1_UINT16 * pValue);

/**
 * This function reads the content of a PHY Register of the MAC through the Management Interface.
 * @param this Pointer to the EthernetMac driver instance to work on.
 * @param phyAddr 5-bit PHY-Device address
 * @param regAddress 5-bit PHY register address
 * @param pValue Pointer to a variable of type L1_UINT16 where the register content should be stored.
 * @return ETH_MAC_RC_OK The function could be performed successfully.
 * @return ETH_MAC_RC_FAIL The function failed.
 * @return ETH_MAC_RC_FAIL_INVALID_PHY_DEVICE Invalid PHY-Device address.
 * @return ETH_MAC_RC_FAIL_INVALID_REGISTER Invalid register address.
 *
 * \ingroup ETHMAC
 */
#ifdef API_DOC
EthMac_Status L1_Drv_EthMac_phyRegRead(struct L1_Drv_EthMac_t * this, L1_UINT8 phyAddr, L1_UINT8 regAddress, L1_UINT16 * pValue);
#else
#define L1_Drv_EthMac_phyRegRead(this, phyAddr, regAddress, pValue)\
    (this)->api->phyRegRead( (this), (phyAddr), (regAddress), (pValue) )
#endif /* API_DOC */


/**
 * Different possible callbacks that can be registered for a Ethernet-MAC, using the registerCallBack operation of the driver.
 * \ingroup L1_DRV_UART
 */
typedef enum
{
	/**
	 * Gets called every time a frame has been received.
	 */
	ETH_MAC_CB_RX_FRAME  = 1,
	/**
	 * Gets called every time the MAC has returned a free TX-Descriptor, i.e. a new MAC-Frame can be sent.
	 */
	ETH_MAC_CB_TX_FRAME  = 2,

}L1_Drv_EthMac_CallBackEvents;

/**
 * Prototype of a function which registers a callback function for a specific event.
 * @param this Pointer to the EthernetMac driver instance to work on.
 * @param event The type of call-back to register. Please note not all drivers support all types of call-backs.
 * @param callBack The call back function to register.
 * @param pParam The parameter to pass to the call-back function when calling it.
 * @return ETH_MAC_RC_OK The function could be performed successfully.
 * @return ETH_MAC_RC_FAIL The function failed.
 * @return ETH_MAC_RC_FAIL_CALLBACK_EVENT_UNSUPPORTED The type of call-back is not supported by the UART-Driver.
 *
 * \ingroup ETHMAC_DEVEL
 */
typedef EthMac_Status (*ethmac_api_register_callback)(struct L1_Drv_EthMac_t * this, L1_Drv_EthMac_CallBackEvents event, L1_ISR_CALLBACK callBack, void * pParam);


/**
 * This function which registers a callback function for a specific event.
 * @param this Pointer to the EthernetMac driver instance to work on.
 * @param event The type of call-back to register. Please note not all drivers support all types of call-backs.
 * @param callBack The call back function to register.
 * @param pParam The parameter to pass to the call-back function when calling it.
 * @return ETH_MAC_RC_OK The function could be performed successfully.
 * @return ETH_MAC_RC_FAIL The function failed.
 * @return ETH_MAC_RC_FAIL_CALLBACK_EVENT_UNSUPPORTED The type of call-back is not supported by the UART-Driver.
 *
 * \ingroup ETHMAC
 */
#ifdef API_DOC
EthMac_Status L1_Drv_EthMac_registerCallBack(struct L1_Drv_EthMac_t * this, L1_Drv_EthMac_CallBackEvents event, L1_ISR_CALLBACK callBack, void * pParam);
#else
#define L1_Drv_EthMac_registerCallBack(this, event, callBack, pParam)\
    (this)->api->registerCallBack( (this), (event), (callBack), (pParam) )
#endif /* API_DOC */






typedef enum
{
	/**
	 * 	Half duplex link mode.
	 */
	ETH_MAC_DUPLEX_HALF = 1,
	/**
	 * Full duplex link mode.
	 */
	ETH_MAC_DUPLEX_FULL = 2,
}L1_Drv_EthMac_Duplex;

typedef enum
{
	/**
	 * 10 Mbps link speed
	 */
	ETH_SPEED_10M = 10,
	/**
	 * 100 Mbps link speed
	 */
	ETH_SPEED_100M = 100,
	/**
	 * 1 Gpbs link speed
	 */
	ETH_SPEED_1G = 1000,
}L1_Drv_EthMac_Speed;


/**
 * Prototype of a function which registers a callback function for a specific event.
 * @param this Pointer to the EthernetMac driver instance to work on.
 * @param duplex The duplex mode of the Ethernet-MAC.
 * @param speed The communication speed of the Ethernet-MAC.
 * @return ETH_MAC_RC_OK The function could be performed successfully.
 * @return ETH_MAC_RC_FAIL The function failed.
 *
 * \ingroup ETHMAC_DEVEL
 */
typedef EthMac_Status (*ethmac_api_set_mode)(struct L1_Drv_EthMac_t * this, L1_Drv_EthMac_Duplex duplex, L1_Drv_EthMac_Speed speed);


/**
 * This function which registers a callback function for a specific event.
 * @param this Pointer to the EthernetMac driver instance to work on.
 * @param duplex The duplex mode of the Ethernet-MAC.
 * @param speed The communication speed of the Ethernet-MAC.
 * @return ETH_MAC_RC_OK The function could be performed successfully.
 * @return ETH_MAC_RC_FAIL The function failed.
 *
 * \ingroup ETHMAC
 */
#ifdef API_DOC
EthMac_Status L1_Drv_EthMac_setMode(struct L1_Drv_EthMac_t * this, L1_Drv_EthMac_Duplex duplex, L1_Drv_EthMac_Speed speed);
#else
#define L1_Drv_EthMac_setMode(this, duplex, speed)\
    (this)->api->setMode( (this), (duplex), (speed) )
#endif /* API_DOC */



/**
 * The Interface of the Ethernet-MAC device driver class.
 * \ingroup ETHMAC_DEVEL
 */
typedef struct{
        drv_api_get_version getVersion;
        ethmac_api_with_mac init;
        ethmac_api_with_mac getMacAddress;
        ethmac_api_with_mac setMulticastAddr;
        ethmac_api_with_bool enableTx;
        ethmac_api_with_bool enableRx;
        ethmac_api_putFrame putFrame_NW;
        ethmac_api_getFrame getFrame_NW;
        ethmac_api_phy_reg_write phyRegWrite;
        ethmac_api_phy_reg_read phyRegRead;
        ethmac_api_register_callback registerCallBack;
        ethmac_api_set_mode setMode;
#ifdef MP
        ethmac_api_putFrame putFrame_W;
        ethmac_api_getFrame getFrame_W;
#endif /* MP */
}L1_Drv_EthMac_API;


typedef struct L1_Drv_EthMac_t{
        L1_Drv_EthMac_API * api;
        void * self;
}L1_Drv_EthMac;


/**
 * This is the API-Version of the L1_Drv_EthMac API. It has the following structure:
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
#define L1_DRV_ETHMAC_API_VERSION 0x00010201



#endif /* L1_DRV_ETHMAC_H_ */
