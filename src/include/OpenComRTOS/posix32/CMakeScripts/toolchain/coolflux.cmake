# OpenComRTOS
# Copyright Altreonic NV, 2005-2008
# www.Altreonic.com
# Module name: $Path/$Filename 
# Synopsis: This file configures the build system for building OpenComRTOS.
# 
# $LastChangedDate: 2010-12-22 17:14:40 +0100 (Wed, 22 Dec 2010) $
# $Revision: 2153 $
# $LastChangedBy: bernhard.sputh $

MACRO(OpenComRTOS_CompilerOptions)
    IF(COMPOPT)
        SET(OCR_COMPILER_OPTIONS ${COMPOPT})
        MESSAGE(STATUS "The parameter COMPOPT is deprecated and will be removed in future versions of the Build System, please change your scripts to use OCR_COMPILER_OPTIONS, the value must be defined without underscore")
    ENDIF(COMPOPT)
ENDMACRO(OpenComRTOS_CompilerOptions)

MACRO(OpenComRTOS_Application)

    #Set compile Option Os as default compile option.
    IF(NOT DEFINED OCR_COMPILER_OPTIONS)
        SET(OCR_COMPILER_OPTIONS "Os")
    ENDIF(NOT DEFINED OCR_COMPILER_OPTIONS)

    OpenComRTOS_KernelSettings()
    string(TOLOWER ${OCR_PLATFORM} PLATFORM_INSTALL)
    
    #Determining whether or not the OpenComRTOS installation directory refered to by ${OCR_INSTALL_DIR} exists.
    IF(NOT EXISTS ${OCR_INSTALL_DIR}/${PLATFORM_INSTALL})
        MESSAGE(SEND_ERROR "OpenComRTOS installation not found at: ${OCR_INSTALL_DIR}/Targets/${PLATFORM_INSTALL}")
    ENDIF(NOT EXISTS ${OCR_INSTALL_DIR}/${PLATFORM_INSTALL})
    SET(OCR_DIR ${OCR_INSTALL_DIR}/${PLATFORM_INSTALL})
    
    #Setting kernel Include directory.
    INCLUDE_DIRECTORIES(${OCR_DIR}/include)
    
    #Setting the directory where CMake should look for libraries:
    LINK_DIRECTORIES(${OCR_DIR}/lib)
    SET(CMAKE_SYSTEM_LIBRARY_PATH "${OCR_DIR}/lib")
    #Searching the necessary libraries and telling the linker about that.
    
    MESSAGE(STATUS "CMAKE_SYSTEM_LIBRARY_PATH: " ${CMAKE_SYSTEM_LIBRARY_PATH})
    MESSAGE(STATUS "OCR_DIR: " ${OCR_DIR})
    MESSAGE(STATUS "KernelLib: lib${OpenComRTOS_KernelLib}.a")
    
    SET(CMAKE_C_LINK_EXECUTABLE "<CMAKE_C_COMPILER> <FLAGS> <CMAKE_C_LINK_FLAGS> <LINK_FLAGS>  <OBJECTS>  -o <TARGET> -L\"${OCR_DIR}/lib\" -l ${OpenComRTOS_KernelLib} -l ${OpenComRTOS_DriverLib} -l ${OpenComRTOS_PlatformKernelLib} -l ${OpenComRTOS_PlatformDriverLib} <LINK_LIBRARIES> +Wbridge,-m")
ENDMACRO(OpenComRTOS_Application)


