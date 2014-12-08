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

    IF(DEFINED OCR_COMPILER_OPTIONS)
        IF(OCR_COMPILER_OPTIONS STREQUAL "O0")
            #Add flags to the compiler call below the current directory.
            ADD_DEFINITIONS(-O0)
        ENDIF(OCR_COMPILER_OPTIONS STREQUAL "O0")
        
        IF(OCR_COMPILER_OPTIONS STREQUAL "O3")
            #Add flags to the compiler call below the current directory.
            ADD_DEFINITIONS(-O3)
        ENDIF(OCR_COMPILER_OPTIONS STREQUAL "O3")
        IF(OCR_COMPILER_OPTIONS STREQUAL "Os")
            #Add flags to the compiler call below the current directory.
            MESSAGE(STATUS "Compiler Option Os set.")
            ADD_DEFINITIONS(-Os)
        ENDIF(OCR_COMPILER_OPTIONS STREQUAL "Os")
    ENDIF(DEFINED OCR_COMPILER_OPTIONS)

    #Default Compiler options to enforce better checking and enable all warnings

    ADD_DEFINITIONS(-Wall)
    ADD_DEFINITIONS(-Wextra)
    # Careful this one results in the build to be aborted immedeately.
    #ADD_DEFINITIONS(-Werror)
    #ADD_DEFINITIONS(-Wno-error=unused-parameter) # Not supported by MB compilers
    ADD_DEFINITIONS(-Wno-unused-parameter)
    ###ADD_DEFINITIONS(-Wfatal-errors)

    ADD_DEFINITIONS(-std=c99)
    #Alwasys include debug symbols in the code.
    ADD_DEFINITIONS(-g)
    # Compiler accepts .filedname notation in structure initialisation.
    ADD_DEFINITIONS(-DC99_STRUCTURE_INIT)    
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
    
    SET(CMAKE_C_LINK_EXECUTABLE "<CMAKE_C_COMPILER> <FLAGS> <CMAKE_C_LINK_FLAGS> <LINK_FLAGS>  <OBJECTS>  -o <TARGET> -L${OCR_DIR}/lib -l ${OpenComRTOS_KernelLib} -l ${OpenComRTOS_DriverLib} -l ${OpenComRTOS_PlatformKernelLib} -l ${OpenComRTOS_PlatformDriverLib} <LINK_LIBRARIES>")

ENDMACRO(OpenComRTOS_Application)


