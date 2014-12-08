/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2013
 * www.Altreonic.com
 * Module name: L1_Drv_Version.h ($Path/$Filename)
 * Synopsis: Generic interface to query the version of the API of a driver and the version
 * of the Driver.
 *
 * $LastChangedDate: 2010-11-05 10:52:18 +0100 (Fri, 05 Nov 2010) $
 * $Revision: 2037 $
 * $LastChangedBy: bernhard.sputh $
 *******************************************************************************/

#ifndef L1_DRV_VERSION_H_
#define L1_DRV_VERSION_H_

/**
 * The version of the API the driver implements and the version of the driver.
 */
typedef struct
{
	/**
	 * This is the version of the API the driver implements. It has the following structure:
     * - MSByte: Major Version
	 * - 23--16: Minor Version
     * - 15--8 : Patch-level
	 * - LSByte : Release status:
	 * 			- 0: Alpha
	 * 			- 1: Beta
	 * 			- 2: Release Candidate
	 * 			- 3: Public Release
	 */
	L1_UINT32 apiVersion;
	/**
	 * This is the version of the driver implements. It has the following structure:
	 * - MSByte: Major Version
	 * - 23--16: Minor Version
     * - 15--8 : Patch-level
     * - LSByte : Release status:
	 * 			- 0: Alpha
	 * 			- 1: Beta
	 * 			- 2: Release Candidate
	 * 			- 3: Public Release
 	 */
	L1_UINT32 driverVersion;
}L1_Drv_Version;


/**
 * This is the prototype of a function which returns the version information for a specific driver implementation.
 *
 * @param[in] self Pointer to a structure of a L1_Drv_* class.
 * @param[out] pVersion Pointer to a variable of type L1_Drv_Version, which will contain the version of the driver and the API it implements.
 *
 * @return RC_OK The function completed successfully.
 * @return RC_FAIL The function failed.
 */
typedef L1_Status (*drv_api_get_version)(void * self, L1_Drv_Version * pVersion);

/**
 * This function returns the version information for a specific driver implementation.
 * Every OpenComRTOS Device Driver that utilises a device driver class must support this operation.
 *
 * @param[in] self Pointer to a structure of a L1_Drv_* class.
 * @param[out] pVersion Pointer to a variable of type L1_Drv_Version, which will contain the version of the driver and the API it implements.
 *
 * @return RC_OK The function completed successfully.
 * @return RC_FAIL The function failed.
 *
 * @warning This function is not yet supported by all driver classes. Only the UART, EthMac, and SPI driver classes implement it so far.
 */
#ifdef API_DOC
L1_Status L1_Drv_getVersion(void * self, L1_Drv_Version * pVersion);
#else
#define L1_Drv_getVersion(drvClassInstance, pVersion)\
    (drvClassInstance)->api->getVersion( (drvClassInstance->self), (pVersion) )
#endif /* API_DOC */



#endif /* L1_DRV_VERSION_H_ */
