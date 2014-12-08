# OpenComRTOS
# Copyright Altreonic NV, 2005-2008
# www.Altreonic.com
# Module name: $Path/$Filename
# Synopsis: This file configures the build system for building OpenComRTOS.
#
# $LastChangedDate: 2014-03-25 14:48:04 +0100 (Tue, 25 Mar 2014) $
# $Revision: 4213 $
# $LastChangedBy: bernhard.sputh $

# Version Number of the Kernel, so users can check in their build scripts what version they are compiling against.

SET(OCR_VERSION 0x01060100)


# Convert OCR_PLATFORM to lower case, in order for the following if-clauses to work.
string(TOLOWER ${OCR_PLATFORM} OCR_PLATFORM)

IF(OCR_PLATFORM STREQUAL "arm-cortex-m3")
    INCLUDE(toolchain/gnu)
ENDIF (OCR_PLATFORM STREQUAL "arm-cortex-m3")

IF(OCR_PLATFORM STREQUAL "arc600")
    INCLUDE(toolchain/mcc)
ENDIF (OCR_PLATFORM STREQUAL "arc600")

IF(OCR_PLATFORM STREQUAL "arm-cortex-m4f")
    INCLUDE(toolchain/gnu)
ENDIF (OCR_PLATFORM STREQUAL "arm-cortex-m4f")

IF(OCR_PLATFORM STREQUAL "arm-cortex-r4")
    INCLUDE(toolchain/gnu)
ENDIF (OCR_PLATFORM STREQUAL "arm-cortex-r4")


IF(OCR_PLATFORM STREQUAL "coolflux")
    INCLUDE(toolchain/coolflux)
ENDIF (OCR_PLATFORM STREQUAL "coolflux")

IF(OCR_PLATFORM STREQUAL "leon3")
    INCLUDE(toolchain/gnu)
ENDIF (OCR_PLATFORM STREQUAL "leon3")

IF(OCR_PLATFORM STREQUAL "microblaze")
    INCLUDE(toolchain/gnu)
ENDIF (OCR_PLATFORM STREQUAL "microblaze")

IF(OCR_PLATFORM STREQUAL "mlx16")
    INCLUDE(toolchain/gnu)
ENDIF (OCR_PLATFORM STREQUAL "mlx16")

IF(OCR_PLATFORM STREQUAL "posix32")
    INCLUDE(toolchain/gnu)
ENDIF (OCR_PLATFORM STREQUAL "posix32")

IF(OCR_PLATFORM STREQUAL "macosx")
    INCLUDE(toolchain/macosx)
ENDIF (OCR_PLATFORM STREQUAL "macosx")

IF(OCR_PLATFORM STREQUAL "powerpc_e600")
    INCLUDE(toolchain/ppc_gnu)
ENDIF (OCR_PLATFORM STREQUAL "powerpc_e600")

IF(OCR_PLATFORM STREQUAL "tidsp_c6000")
    INCLUDE(toolchain/tidsp_c6000)
ENDIF (OCR_PLATFORM STREQUAL "tidsp_c6000")

IF(OCR_PLATFORM STREQUAL "win32")
    INCLUDE(toolchain/gnu)
ENDIF (OCR_PLATFORM STREQUAL "win32")

IF(OCR_PLATFORM STREQUAL "xmos")
    INCLUDE(toolchain/xmos)
ENDIF (OCR_PLATFORM STREQUAL "xmos")




MACRO(OpenComRTOS_Platform)
    #IF platform is not defined then check whether or not OCR_PLATFORM is defined
    IF(NOT OCR_PLATFORM)
        MESSAGE(ERROR "The parameter OCR_PLATFORM has to be set.")
    ENDIF(NOT OCR_PLATFORM)



#    ADD_DEFINITIONS(-D${OCR_PLATFORM})
    string(TOUPPER ${OCR_PLATFORM} PLATFORM_DEFINE)
    string(REPLACE "-" "_" PLATFORM_DEFINE ${PLATFORM_DEFINE})
    ADD_DEFINITIONS(-D${PLATFORM_DEFINE})

    MESSAGE(STATUS "OpenComRTOS will be compiled for: " ${PLATFORM_DEFINE})
    string(TOLOWER ${OCR_PLATFORM} OCR_PLATFORM)
    MESSAGE(STATUS "OpenComRTOS platform set to: " ${OCR_PLATFORM})

ENDMACRO(OpenComRTOS_Platform)

MACRO(OpenComRTOS_Name)
    #Catching RTOSNAME and defining OCR_NAME
    IF(NOT RTOSNAME)
        IF(NOT OCR_NAME)
            #Set default name
            SET(OCR_NAME "OpenComRTOS")
        ENDIF(NOT OCR_NAME)
    ELSE(NOT RTOSNAME)
        SET(OCR_NAME ${RTOSNAME})
        MESSAGE(STATUS "The parameter RTOSNAME is deprecated and will be removed in future versions of the Build System, please change your scripts to use OCR_NAME")
    ENDIF(NOT RTOSNAME)
#    MESSAGE(STATUS "The libaray will be called: " ${OCR_NAME})
ENDMACRO(OpenComRTOS_Name)

MACRO(OpenComRTOS_Variant)
    #Catching definitions of RTOSVARIANT and defining OCR_VARIANT
    IF(NOT RTOSVARIANT)
        IF(NOT OCR_VARIANT)
            #Set default variant of OpenComRTOS to build
            SET(OCR_VARIANT "SP")
        ENDIF(NOT OCR_VARIANT)
    ELSE(NOT RTOSVARIANT)
        # Todo figure out a way to remove present preceeding underscores in the RTOSVARIANT.
        SET(OCR_VARIANT ${RTOSVARIANT})
        MESSAGE(STATUS "The parameter RTOSVARIANT is deprecated and will be removed in future versions of the Build System, please change your scripts to use OCR_VARIANT, the value must be defined without underscore")
    ENDIF(NOT RTOSVARIANT)

    # Testing Compilation with ASYNC_SERVICES
    ADD_DEFINITIONS(-DASYNC_SERVICES)

	# Testing L1_PRIO_INHERITANCE
	ADD_DEFINITIONS(-DL1_PRIO_INHERITANCE)

    IF(OCR_VARIANT STREQUAL "SP")
        #Add flags to the compiler call below the current directory.
        #ADD_DEFINITIONS(-DNOWAIT_SERVICES)
        #ADD_DEFINITIONS(-DWT_SERVICES)
        #ADD_DEFINITIONS(-DL1_SERVICES)
        #ADD_DEFINITIONS(-DNO_SENDRCV)
        #ADD_DEFINITIONS(-DNO_L1_KERNELPACKETPOOL)
    ENDIF(OCR_VARIANT STREQUAL "SP")


    IF(OCR_VARIANT STREQUAL "MP")
        #Add flags to the compiler call below the current directory.
        ADD_DEFINITIONS(-DMP)
        #ADD_DEFINITIONS(-DNOWAIT_SERVICES)
        #ADD_DEFINITIONS(-DWT_SERVICES)
        #ADD_DEFINITIONS(-DL1_SERVICES)
        #ADD_DEFINITIONS(-DNO_SENDRCV)
        #ADD_DEFINITIONS(-DNO_L1_KERNELPACKETPOOL)
        #ADD_DEFINITIONS(-DL1_MOVEDATA)
        ADD_DEFINITIONS(-DPENDING_REQUESTS_QUEUE)
    ENDIF(OCR_VARIANT STREQUAL "MP")
#    MESSAGE(STATUS "The following variant of OpenComRTOS will be used: " ${OCR_VARIANT})
ENDMACRO(OpenComRTOS_Variant)




MACRO(OpenComRTOS_DebugOptions)
    IF(DEBUGOPT)
        SET(OCR_DEBUG_OPTIONS ${DEBUGOPT})
        MESSAGE(STATUS "The parameter DEBUGOPT is deprecated and will be removed in future versions of the Build System, please change your scripts to use OCR_DEBUG_OPTIONS, the value must be defined without underscore")
    ENDIF(DEBUGOPT)



    IF(OCR_DEBUG_OPTIONS STREQUAL "1")
	   #Enable Open System Inspector specific code
	   ADD_DEFINITIONS(-DL1_OSI)
	   ADD_DEFINITIONS(-DL1_ALLOW_TRACE)
    ENDIF(OCR_DEBUG_OPTIONS STREQUAL "1")


    IF(OCR_DEBUG_OPTIONS STREQUAL "2")
	   #Enable Open System Inspector specific code
	   ADD_DEFINITIONS(-DL1_OSI)
	   ADD_DEFINITIONS(-DL1_ALLOW_TRACE)
       ADD_DEFINITIONS(-DL1_TRACE_LEVEL_2)
       #ADD_DEFINITIONS(-DL1_DBG_OS_ALLOW_ASSERT)
    ENDIF(OCR_DEBUG_OPTIONS STREQUAL "2")

    IF(OCR_DEBUG_OPTIONS STREQUAL "3")
        ADD_DEFINITIONS(-DL1_DEBUG)
        #ADD_DEFINITIONS(-DL1_POST_MORTEM_SERVICE)
        ADD_DEFINITIONS(-DL1_DBG_OS_ALLOW_ASSERT)
    ENDIF(OCR_DEBUG_OPTIONS STREQUAL "3")

    IF(OCR_DEBUG_OPTIONS STREQUAL "4")
        ADD_DEFINITIONS(-DL1_DEBUG)
        ADD_DEFINITIONS(-DL1_POST_MORTEM_SERVICE)
        #ADD_DEFINITIONS(-DL1_DBG_OS_ALLOW_ASSERT)
    ENDIF(OCR_DEBUG_OPTIONS STREQUAL "4")

    IF(OCR_DEBUG_OPTIONS STREQUAL "5")
        ADD_DEFINITIONS(-DL1_DEBUG)
        ADD_DEFINITIONS(-DL1_POST_MORTEM_SERVICE)
        ADD_DEFINITIONS(-DL1_DBG_OS_ALLOW_ASSERT)
    ENDIF(OCR_DEBUG_OPTIONS STREQUAL "5")

ENDMACRO(OpenComRTOS_DebugOptions)


MACRO(OpenComRTOS_KernelSettings)
    # These macros check input values and set global variables.
    OpenComRTOS_Platform()
    OpenComRTOS_Name()
    OpenComRTOS_Variant()
    OpenComRTOS_CompilerOptions()
    OpenComRTOS_DebugOptions()


    SET(OpenComRTOS_BaseName "${OCR_NAME}_${OCR_VARIANT}")
    IF(DEFINED OCR_COMPILER_OPTIONS)
        IF(NOT OCR_COMPILER_OPTIONS STREQUAL "")
            SET(OpenComRTOS_BaseName "${OpenComRTOS_BaseName}_C${OCR_COMPILER_OPTIONS}")
        ENDIF(NOT OCR_COMPILER_OPTIONS STREQUAL "")
    ENDIF(DEFINED OCR_COMPILER_OPTIONS)

    IF(DEFINED OCR_DEBUG_OPTIONS)
        IF(NOT OCR_DEBUG_OPTIONS STREQUAL "")
            SET(OpenComRTOS_BaseName "${OpenComRTOS_BaseName}_D${OCR_DEBUG_OPTIONS}")
        ENDIF(NOT OCR_DEBUG_OPTIONS STREQUAL "")
    ENDIF(DEFINED OCR_DEBUG_OPTIONS)

    MESSAGE(STATUS "OpenComRTOS_BaseName: " ${OpenComRTOS_BaseName})

IF(OCR_PLATFORM STREQUAL "arc600")
    SET(OpenComRTOS_KernelLib "${OpenComRTOS_BaseName}_K")
    SET(OpenComRTOS_DriverLib "${OpenComRTOS_BaseName}_D")
    SET(OpenComRTOS_PlatformKernelLib "${OpenComRTOS_BaseName}_PK")
    SET(OpenComRTOS_PlatformDriverLib "${OpenComRTOS_BaseName}_PD")
ELSE (OCR_PLATFORM STREQUAL "arc600")
    SET(OpenComRTOS_KernelLib "${OpenComRTOS_BaseName}_Kernel")
    SET(OpenComRTOS_DriverLib "${OpenComRTOS_BaseName}_Driver")
    SET(OpenComRTOS_PlatformKernelLib "${OpenComRTOS_BaseName}_PlatformKernel")
    SET(OpenComRTOS_PlatformDriverLib "${OpenComRTOS_BaseName}_PlatformDriver")
ENDIF (OCR_PLATFORM STREQUAL "arc600")


    MESSAGE(STATUS "OpenComRTOS_KernelLib: " ${OpenComRTOS_KernelLib})

ENDMACRO(OpenComRTOS_KernelSettings)


MACRO(OpenComRTOS_BuildAndInstallKernel)
    OpenComRTOS_KernelSettings()

    #Name of the target gets converted to lower case for the installation directory.
    string(TOLOWER ${OCR_PLATFORM} PLATFORM_INSTALL)
    #Set Installation Prefix to the previously created directory.
    SET(CMAKE_INSTALL_PREFIX ${OCR_INSTALL_DIR}/targets/${PLATFORM_INSTALL}/)
ENDMACRO(OpenComRTOS_BuildAndInstallKernel)


MACRO(OpenComRTOS_UnitTest)
    # These macros check input values and set global variables.
    OpenComRTOS_Platform()
    OpenComRTOS_Name()
    OpenComRTOS_Variant()
    OpenComRTOS_CompilerOptions()
    OpenComRTOS_DebugOptions()

    add_definitions(-DL1_UNIT_TEST)

    SET(OpenComRTOS_BaseName "${OCR_NAME}_${OCR_VARIANT}")
    IF(DEFINED OCR_COMPILER_OPTIONS)
        IF(NOT OCR_COMPILER_OPTIONS STREQUAL "")
            SET(OpenComRTOS_BaseName "${OpenComRTOS_BaseName}_C${OCR_COMPILER_OPTIONS}")
        ENDIF(NOT OCR_COMPILER_OPTIONS STREQUAL "")
    ENDIF(DEFINED OCR_COMPILER_OPTIONS)

    IF(DEFINED OCR_DEBUG_OPTIONS)
        IF(NOT OCR_DEBUG_OPTIONS STREQUAL "")
            SET(OpenComRTOS_BaseName "${OpenComRTOS_BaseName}_D${OCR_DEBUG_OPTIONS}")
        ENDIF(NOT OCR_DEBUG_OPTIONS STREQUAL "")
    ENDIF(DEFINED OCR_DEBUG_OPTIONS)

ENDMACRO(OpenComRTOS_UnitTest)






FUNCTION(OpenComRTOS_GenLibName _libname)
    MESSAGE(STATUS "libname: " ${${_libname}} " variant: " ${OCR_VARIANT})
    SET( postfixedLibName "${${_libname}}_${OCR_VARIANT}")

    IF(DEFINED OCR_COMPILER_OPTIONS)
        IF(NOT OCR_COMPILER_OPTIONS STREQUAL "")
            SET(postfixedLibName "${postfixedLibName}_C${OCR_COMPILER_OPTIONS}")
        ENDIF(NOT OCR_COMPILER_OPTIONS STREQUAL "")
    ENDIF(DEFINED OCR_COMPILER_OPTIONS)

    IF(DEFINED OCR_DEBUG_OPTIONS)
        IF(NOT OCR_DEBUG_OPTIONS STREQUAL "")
            SET(postfixedLibName "${postfixedLibName}_D${OCR_DEBUG_OPTIONS}")
        ENDIF(NOT OCR_DEBUG_OPTIONS STREQUAL "")
    ENDIF(DEFINED OCR_DEBUG_OPTIONS)

    MESSAGE(STATUS "postfixedLibName: " ${postfixedLibName})
    SET(${_libname} "${postfixedLibName}" PARENT_SCOPE)
ENDFUNCTION()


MACRO(LINK_OCR_LIB libname)
    SET(ocr_libname "${libname}_${OCR_VARIANT}")
    IF(DEFINED OCR_COMPILER_OPTIONS)
        IF(NOT OCR_COMPILER_OPTIONS STREQUAL "")
            SET( ocr_libname "${ocr_libname}_C${OCR_COMPILER_OPTIONS}")
        ENDIF(NOT OCR_COMPILER_OPTIONS STREQUAL "")
    ENDIF(DEFINED OCR_COMPILER_OPTIONS)

    IF(DEFINED OCR_DEBUG_OPTIONS)
        IF(NOT OCR_DEBUG_OPTIONS STREQUAL "")
            SET( ocr_libname "${ocr_libname}_D${OCR_DEBUG_OPTIONS}")
        ENDIF(NOT OCR_DEBUG_OPTIONS STREQUAL "")
    ENDIF(DEFINED OCR_DEBUG_OPTIONS)
    
    IF(OCR_PLATFORM STREQUAL "tidsp_c6000")
        SET( ocr_libname "lib${ocr_libname}.lib")
    ENDIF (OCR_PLATFORM STREQUAL "tidsp_c6000")
    
    LINK_LIBRARIES(${ocr_libname})
ENDMACRO(LINK_OCR_LIB libname)

