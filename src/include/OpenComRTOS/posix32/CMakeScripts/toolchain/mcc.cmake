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
            ## Trying to reduce codesizes
            ADD_DEFINITIONS(-Hon=Each_function_in_own_section)
            #ADD_DEFINITIONS(-Hnocrt)
            #ADD_DEFINITIONS(-Hno_default_include)
            #ADD_DEFINITIONS(-I C:/ARC/MetaWare/arc/inc)
            #ADD_DEFINITIONS(-Hnolib)
        ENDIF(OCR_COMPILER_OPTIONS STREQUAL "Os")
    ENDIF(DEFINED OCR_COMPILER_OPTIONS)

    #Default Compiler options to enforce better checking and enable all warnings

    #ADD_DEFINITIONS(-Hgcc)
    ADD_DEFINITIONS(-Hcplus)
    ADD_DEFINITIONS(-Hnosdata)
    #ADD_DEFINITIONS(-m)
   
    #Alwasys include debug symbols in the code.
    ADD_DEFINITIONS(-g)
    # Compiler accepts .filedname notation in structure initialisation.
    ADD_DEFINITIONS(-DC99_STRUCTURE_INIT)
    # For TI-TivaWare / StellarisWare
    ADD_DEFINITIONS(-Dgcc)
    
    ADD_DEFINITIONS(-DMCC)
    
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
    
#    SET(CMAKE_C_LINK_EXECUTABLE "<CMAKE_C_COMPILER> <FLAGS> <CMAKE_C_LINK_FLAGS> <LINK_FLAGS>  <OBJECTS>  -o <TARGET> -L${OCR_DIR}/lib -Xlinker --start-group -l ${OpenComRTOS_KernelLib} -l ${OpenComRTOS_DriverLib} -l ${OpenComRTOS_PlatformKernelLib} -l ${OpenComRTOS_PlatformDriverLib} <LINK_LIBRARIES> -Xlinker --end-group ")
   SET(CMAKE_C_LINK_EXECUTABLE "<CMAKE_C_COMPILER> -v <FLAGS> <CMAKE_C_LINK_FLAGS> <LINK_FLAGS>  <OBJECTS> -o <TARGET> -L${OCR_DIR}/lib -Bgrouplib -l ${OpenComRTOS_KernelLib} -Bgrouplib -l ${OpenComRTOS_DriverLib} -Bgrouplib -l ${OpenComRTOS_PlatformKernelLib} -Bgrouplib -l ${OpenComRTOS_PlatformDriverLib} <LINK_LIBRARIES>")
#   SET(CMAKE_C_LINK_EXECUTABLE "<CMAKE_C_COMPILER> -v <FLAGS> <CMAKE_C_LINK_FLAGS> <LINK_FLAGS>  <OBJECTS> ${OCR_DIR}/linker_scripts/nsim.ld -o <TARGET> -L${OCR_DIR}/lib -Bgrouplib -l ${OpenComRTOS_KernelLib} -Bgrouplib -l ${OpenComRTOS_DriverLib} -Bgrouplib -l ${OpenComRTOS_PlatformKernelLib} -Bgrouplib -l ${OpenComRTOS_PlatformDriverLib} <LINK_LIBRARIES>")
    SET(CMAKE_CXX_LINK_EXECUTABLE "<CMAKE_CXX_COMPILER> <FLAGS> <CMAKE_C_LINK_FLAGS> <LINK_FLAGS>  <OBJECTS>  -o <TARGET> -L${OCR_DIR}/lib -Xlinker --start-group -l ${OpenComRTOS_KernelLib} -l ${OpenComRTOS_DriverLib} -l ${OpenComRTOS_PlatformKernelLib} -l ${OpenComRTOS_PlatformDriverLib} <LINK_LIBRARIES> -Xlinker --end-group -Wl,-Map,<TARGET>.map")

ENDMACRO(OpenComRTOS_Application)

MACRO(OpenComRTOS_UnitTest)
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
    
    SET(CMAKE_C_LINK_EXECUTABLE "<CMAKE_C_COMPILER> <FLAGS> <CMAKE_C_LINK_FLAGS> <LINK_FLAGS>  <OBJECTS>  -o <TARGET> -L${OCR_DIR}/lib -Xlinker --start-group -l ${OpenComRTOS_KernelLib} -l ${OpenComRTOS_DriverLib} -l ${OpenComRTOS_PlatformKernelLib} -l ${OpenComRTOS_PlatformDriverLib} <LINK_LIBRARIES> -Xlinker --end-group ")
    SET(CMAKE_C_LINK_EXECUTABLE "<CMAKE_C_COMPILER> <FLAGS> <CMAKE_C_LINK_FLAGS> <LINK_FLAGS>  <OBJECTS>  -o <TARGET> -L${OCR_DIR}/lib -Xlinker --start-group -l ${OpenComRTOS_KernelLib} -l ${OpenComRTOS_DriverLib} -l ${OpenComRTOS_PlatformKernelLib} -l ${OpenComRTOS_PlatformDriverLib} <LINK_LIBRARIES> -Xlinker --end-group -Wl,-Map,<TARGET>.map")
    SET(CMAKE_CXX_LINK_EXECUTABLE "<CMAKE_CXX_COMPILER> <FLAGS> <CMAKE_C_LINK_FLAGS> <LINK_FLAGS>  <OBJECTS>  -o <TARGET> -L${OCR_DIR}/lib -Xlinker --start-group -l ${OpenComRTOS_KernelLib} -l ${OpenComRTOS_DriverLib} -l ${OpenComRTOS_PlatformKernelLib} -l ${OpenComRTOS_PlatformDriverLib} <LINK_LIBRARIES> -Xlinker --end-group -Wl,-Map,<TARGET>.map")


ENDMACRO(OpenComRTOS_UnitTest)




