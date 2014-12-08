/*******************************************************************************
 * OpenComRTOS
 * Copyright Altreonic NV, 2005-2008
 * www.Altreonic.com
 * Module name: StdioHostClient.h ($Path/$Filename)
 * Synopsis:
 *
 * $LastChangedDate: 2010-03-11 18:13:11$
 * $Revision: 3634 $
 * $LastChangedBy: bernhard.sputh $
 *******************************************************************************/

#ifndef STDIO_HOST_CLIENT_HEADER
#define STDIO_HOST_CLIENT_HEADER

#ifndef SVM
/*
 * The SVM-Platform does not support tracing as of version 0.1
 */
    #include <kernel/L1_trace_api.h>
    #include <StdioHostService/TraceHostClient.h>
#endif /* SVM */
#include <L1_types.h>

/**
 * The L1_UINT32 value of is formatted the following way:
 * - MSByte: Major Version of the Kernel
 * - 23--16: Minor Version
 * - 15--8 : Release status:
 * 			- 0: Alpha
 * 			- 1: Beta
 * 			- 2: Release Candidate
 * 			- 3: Public Release
 * - LSByte: Patch-level
 *
 * This number is loosly associated with the OpenVE version number.
 */

#define SHS_VERSION 0x01000309 // 1.0 Public Release Patchlevel 9

/**
 * This service returns the Kernel version of OpenComRTOS.
 *
 * @return L1_UINT32, the value of is formatted the following way:
 * - MSByte: Major Version of the Kernel
 * - 23--16: Minor Version
 * - 15--8 : Release status:
 *          - 0: Alpha
 *          - 1: Beta
 *          - 2: Release Candidate
 *          - 3: Public Release
 * - LSByte: Patch-level
 *
 */

#define ShsGetVersion() ((L1_UINT32) SHS_VERSION)


/**
 * Writes one character value onto the console associated with the Stdio Host Server.
 *
 * @param shs is the ID of the ShsInputPort of the Stdio Host Server.
 * @param charValue is the character to write onto the console.
 * @return L1_Status
 *  - RC_OK: The request was successful
 *  - RC_FAIL: The request failed.
 */
L1_Status Shs_putChar_W(L1_HubID shs, L1_BYTE charValue);

/**
 * Retrieves one Character from the Stdio Host Server console. The retrieved
 * character is returned to the user in the character value at pChar.
 *
 * @param shs is the ID of the ShsInputPort of the Stdio Host Server.
 * @param pChar is the Pointer to a variable of type L1_BYTE which should hold the
 *   retrieved character.
 * @return L1_Status
 *  - RC_OK: The request was successful
 *  - RC_FAIL: The request failed.
 */
L1_Status Shs_getChar_W(L1_HubID shs, L1_BYTE* pChar);

/**
 * This function outputs an integer (intValue) into the console associated with the
 * Stdio Host Server. The output format (octal, decimal, hexa-decimal) must
 * be specified using the character format.
 *
 * @param shs is the ID of the ShsInputPort of the Stdio Host Server.
 * @param intValue is the integer to output into the console.
 * @param format is the character specifying in which format the integer should be written onto the console. The following are permitted:
 *  - 'o' -- Octal output
 *  - 'd' -- Decimal output
 *  - 'x' -- Hexa-decimal output.
 *  @return L1_Status
 *  - RC_OK: The request was successful
 *  - RC_FAIL: The request failed.
 */
L1_Status Shs_putInt_W(L1_HubID shs, L1_INT32 intValue, L1_BYTE format);

/**
 * Retrieves an integer from the Stdio Host Server console. The retrieved
 * integer is returned to the user in the character value at pInt.
 *
 * @param shs is the ID of the ShsInputPort of the Stdio Host Server.
 * @param pInt is the pointer to a variable of type int which should hold the
 *   retrieved integer value.
 * @return L1_Status
 *  - RC_OK: The request was successful
 *  - RC_FAIL: The request failed.
 */
L1_Status Shs_getInt_W(L1_HubID shs, L1_INT32* pInt);

#if SHS_FLOAT
/**
 * This function outputs a float value (floatValue) into the console associated with the
 * Stdio Host Server. The precision of output of a float value  must
 * be specified using the prec parameter.
 *
 * @param shs is the ID of the ShsInputPort of the Stdio Host Server.
 * @param floatValue is the float value to output into the console.
 * @param prec is the character specifying the precision of output of a float value onto the console.
 * @return L1_Status
 *  - RC_OK: The request was successful
 *  - RC_FAIL: The request failed.
 *
 *  @warning This does not work when running inside the SVM.
 */
L1_Status Shs_putFloat_W(L1_HubID shs, float floatValue, L1_BYTE prec);

/**
 * Retrieves a float value from the Stdio Host Server console. The retrieved
 * float value is returned to the user as a pointer.
 *
 * @param shs is the ID of the ShsInputPort of the Stdio Host Server.
 * @param pFloat is the pointer to a variable of the float type which holds the retrieved float value.
 * @return L1_Status
 *  - RC_OK: The request was successful
 *  - RC_FAIL: The request failed.
 *
 * @warning This does not work when running inside the SVM.
 */
L1_Status Shs_getFloat_W(L1_HubID shs, float* pFloat);
#endif /* SHS_FLOAT */

/**
 * Prints the string str with onto the console, only length characters are written on to the console.
 *
 * @param shs is the ID of the ShsInputPort of the Stdio Host Server.
 * @param str is the C-string to write onto the console.
 * @return L1_Status
 *  - RC_OK: The request was successful
 *  - RC_FAIL: The request failed.
 */
L1_Status Shs_putString_W(L1_HubID shs, const char* str);


/**
 * Retrieved a string value from the Stdio Host Server.
 *
 * @param shs is the ID of the ShsInputPort of the Stdio Host Server.
 * @param maxLength is the the number of characters the buffer (pStr) can hold.
 * @param pStr is the pointer to character array which should be filled with the retrieved string.
 * @param pRealLength is the pointer to an integer which will hold number of returned characters, including the terminating zero.
 * @return L1_Status
 *  - RC_OK: The request was successful
 *  - RC_FAIL: The request failed.
 */
L1_Status Shs_getString_W(L1_HubID shs, L1_UINT32 maxLength, char* pStr, L1_UINT32 *pRealLength) ;

/* File input-output functions declarations */

/**
 * Opens a file on the Stdio Host Server file system.
 * @param shs is the ID of the ShsInputPort of the Stdio Host Server.
 * @param fileName is the name of a file to open.
 * @param mode is the mode in which the file should be opened. It can contain 1 or 2 symbols.
 * @param fileHandle is the pointer to file handle associated with the opened file. This handle in generated by the StdioHostService.
 * @return L1_Status
 *  - RC_OK: The request was successful.
 *  - RC_FAIL: The request failed.
 */
L1_Status Shs_openFile_W(L1_HubID shs, const char* fileName, const char *mode, L1_UINT32* fileHandle);


/**
 * Closes a file previously opened using the function Shs_openFile().
 * @param shs is the ID of the ShsInputPort of the Stdio Host Server.
 * @param fileHandle is the file-handle previously acquired from the Stdio Host Server using the function Shs_openFile().
 * @return L1_Status
 *  - RC_OK: The request was successful
 *  - RC_FAIL: The request failed.
 */
L1_Status Shs_closeFile_W(L1_HubID shs, L1_UINT32 fileHandle);


/**
 * This function writes the number of bytes (toWrite) of the byte array at buffer
 * into the file indicated by fileHandle. 
 * @param shs is the ID of the ShsInputPort of the Stdio Host Server.
 * @param fileHandle is the file-handle previously acquired from the Stdio Host Server using the function Shs_openFile().
 * @param buffer - the pointer to the first byte of the memory block to be written to the file.
 * @param toWrite - the number of bytes to be written into the file.
 * @param pWritten - pointer to an unsigned integer which contain the number of bytes that were actually written.
 * @return L1_Status
 *  - RC_OK: The request was successful
 *  - RC_FAIL: The request failed.
 */
L1_Status Shs_writeToFile_W(L1_HubID shs, L1_UINT32 fileHandle, L1_BYTE* buffer, L1_UINT32 toWrite, L1_UINT32* pWritten);


/**
 * Reads from a file opened by the server.
 * @param shs - is the ID of the ShsInputPort of the Stdio Host Server.
 * @param fileHandle - is the file-handle previously acquired from the Stdio Host Server using the function Shs_openFile().
 * @param buffer is the pointer to the location where the retrieved data should be stored.
 * @param toRead - how many bytes should be read from the file.
 * @param pRead - how many bytes were actually retrieved from the file.
 * @return L1_Status
 *  - RC_OK: The request was successful
 *  - RC_FAIL: The request failed.
 */
L1_Status Shs_readFromFile_W(L1_HubID shs, L1_UINT32 fileHandle, L1_BYTE* buffer, L1_UINT32 toRead, L1_UINT32* pRead);

#endif /*STDIO_HOST_CLIENT_HEADER*/

