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
            #ADD_DEFINITIONS(--opt_level=0)
        ENDIF(OCR_COMPILER_OPTIONS STREQUAL "O0")
        
        IF(OCR_COMPILER_OPTIONS STREQUAL "O3")
            #Add flags to the compiler call below the current directory.
            ADD_DEFINITIONS(--opt_level=3)
            ADD_DEFINITIONS(--remove_hooks_when_inlining)
            ADD_DEFINITIONS(--single_inline)
            #Generate a verbose optimisation report
            ADD_DEFINITIONS(--gen_opt_info=2)
        ENDIF(OCR_COMPILER_OPTIONS STREQUAL "O3")
        IF(OCR_COMPILER_OPTIONS STREQUAL "Os")
            #Add flags to the compiler call below the current directory.
            MESSAGE(STATUS "Compiler Option Os set.")
            ADD_DEFINITIONS(--opt_level=3)
            ADD_DEFINITIONS(--opt_for_space=3)
            #ADD_DEFINITIONS(--opt_for_speed=5)
            ADD_DEFINITIONS(--remove_hooks_when_inlining)            
            ADD_DEFINITIONS(--single_inline)
            #Generate a verbose optimisation report
            ADD_DEFINITIONS(--gen_opt_info=2)             
        ENDIF(OCR_COMPILER_OPTIONS STREQUAL "Os")
    ENDIF(DEFINED OCR_COMPILER_OPTIONS)

    #Default Compiler options to enforce better checking and enable all warnings

    ADD_DEFINITIONS(--issue_remarks)
    #Alwasys include debug symbols in the code.
    ADD_DEFINITIONS(-g)
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
    
    IF(NOT TI_DSP_LINKER_SCRIPT)
        SET(TI_DSP_LINKER_SCRIPT "")
    ENDIF(NOT TI_DSP_LINKER_SCRIPT)
    
    
    #SET(CMAKE_C_LINK_EXECUTABLE "<CMAKE_C_COMPILER> <FLAGS>  --run_linker <CMAKE_C_LINK_FLAGS> <LINK_FLAGS>  --output_file=<TARGET> --search_path=\"${OCR_DIR}/lib\" -llib${OpenComRTOS_KernelLib}.lib -llib${OpenComRTOS_DriverLib}.lib -llib${OpenComRTOS_PlatformKernelLib}.lib -llib${OpenComRTOS_PlatformDriverLib}.lib <LINK_LIBRARIES> <OBJECTS> ")
    #SET(CMAKE_C_LINK_EXECUTABLE "<CMAKE_C_COMPILER> <FLAGS>  --run_linker <CMAKE_C_LINK_FLAGS> <LINK_FLAGS>  --output_file=<TARGET> --search_path=\"${OCR_DIR}/lib\"  <LINK_LIBRARIES> <OBJECTS> ")
#    SET(CMAKE_C_LINK_EXECUTABLE
#    "<CMAKE_C_COMPILER> <FLAGS> <CMAKE_C_LINK_FLAGS> <LINK_FLAGS> --abi=${TI_DSP_ABI} --run_linker --search_path=\"${CMAKE_FIND_ROOT_PATH}/lib\" -i\"${CMAKE_FIND_ROOT_PATH}/include\" --${TI_DSP_VARIABLE_INITIALISATION} --output_file=<TARGET> -l${OpenComRTOS_KernelLib} -l${OpenComRTOS_DriverLib} -l${OpenComRTOS_PlatformKernelLib} -l${OpenComRTOS_PlatformDriverLib}  <LINK_LIBRARIES> <OBJECTS>")

    #SET(CMAKE_C_LINK_EXECUTABLE
    #"<CMAKE_C_COMPILER> -i\"${CMAKE_FIND_ROOT_PATH}/lib\" <FLAGS> <CMAKE_C_LINK_FLAGS> <LINK_FLAGS> --abi=${TI_DSP_ABI} --run_linker --reread_libs  --${TI_DSP_VARIABLE_INITIALISATION} --output_file=<TARGET> -l${OpenComRTOS_KernelLib} -l${OpenComRTOS_DriverLib} -l${OpenComRTOS_PlatformKernelLib} -l${OpenComRTOS_PlatformDriverLib}  <LINK_LIBRARIES> <OBJECTS>")
    #SET(CMAKE_C_LINK_EXECUTABLE "<CMAKE_C_COMPILER> <FLAGS>  --run_linker <CMAKE_C_LINK_FLAGS> <LINK_FLAGS>  --output_file=<TARGET>  -i\"${CMAKE_FIND_ROOT_PATH}/lib\" -i\"${CMAKE_FIND_ROOT_PATH}/include\" --search_path=\"${OCR_DIR}/lib\" -llib${OpenComRTOS_KernelLib}.lib -llib${OpenComRTOS_DriverLib}.lib -llib${OpenComRTOS_PlatformKernelLib}.lib -llib${OpenComRTOS_PlatformDriverLib}.lib <LINK_LIBRARIES> <OBJECTS> ")
#    SET(CMAKE_C_LINK_EXECUTABLE "<CMAKE_C_COMPILER> <FLAGS>  --run_linker <CMAKE_C_LINK_FLAGS> <LINK_FLAGS>  -i\"${CMAKE_FIND_ROOT_PATH}/lib\" -i\"${CMAKE_FIND_ROOT_PATH}/include\" --search_path=\"${OCR_DIR}/lib\" -llib${OpenComRTOS_KernelLib}.lib -llib${OpenComRTOS_DriverLib}.lib -llib${OpenComRTOS_PlatformKernelLib}.lib -llib${OpenComRTOS_PlatformDriverLib}.lib <LINK_LIBRARIES> --output_file=<TARGET> --${TI_DSP_VARIABLE_INITIALISATION} --reread_libs <OBJECTS> ${TI_DSP_LINKER_SCRIPT}")

    SET(CMAKE_C_LINK_EXECUTABLE "<CMAKE_C_COMPILER> <FLAGS>  --run_linker <CMAKE_C_LINK_FLAGS> <LINK_FLAGS>  -i\"${CMAKE_FIND_ROOT_PATH}/lib\" -i\"${CMAKE_FIND_ROOT_PATH}/include\" --search_path=\"${OCR_DIR}/lib\" -llib${OpenComRTOS_KernelLib}.lib -llib${OpenComRTOS_DriverLib}.lib -llib${OpenComRTOS_PlatformKernelLib}.lib -llib${OpenComRTOS_PlatformDriverLib}.lib <LINK_LIBRARIES> --output_file=<TARGET> --map_file=<TARGET>.map --${TI_DSP_VARIABLE_INITIALISATION} --reread_libs <OBJECTS> ${TI_DSP_LINKER_SCRIPT}")
    SET(CMAKE_CXX_LINK_EXECUTABLE "<CMAKE_C_COMPILER> <FLAGS>  --run_linker <CMAKE_C_LINK_FLAGS> <LINK_FLAGS>  -i\"${CMAKE_FIND_ROOT_PATH}/lib\" -i\"${CMAKE_FIND_ROOT_PATH}/include\" --search_path=\"${OCR_DIR}/lib\" -llib${OpenComRTOS_KernelLib}.lib -llib${OpenComRTOS_DriverLib}.lib -llib${OpenComRTOS_PlatformKernelLib}.lib -llib${OpenComRTOS_PlatformDriverLib}.lib <LINK_LIBRARIES> --output_file=<TARGET> --map_file=<TARGET>.map --${TI_DSP_VARIABLE_INITIALISATION} --reread_libs <OBJECTS> ${TI_DSP_LINKER_SCRIPT}")
ENDMACRO(OpenComRTOS_Application)


