# As minimum version 2.6 of CMake must be used.
cmake_minimum_required(VERSION 2.6)

#For verbose output during the build process, this is the same as `make VERBOSE=1'
set( CMAKE_VERBOSE_MAKEFILE on )

#The following variables have been moved over from the Makefile
# Where the different OpenComRTOS installation images are located
SET(OCR_INSTALL_DIR "/mnt/OpenComRTOS/s-net_distribution/lpel-master/src/include/OpenComRTOS")

# Name of the Platform (win32, posix32, leon3, microblaze)
SET(OCR_PLATFORM posix32)

#The variant of OpenComRTOS to compile for (OLD: RTOSVARIANT)
SET(OCR_VARIANT SP)

# Setting predefined compiler options
SET(OCR_COMPILER_OPTIONS "Os")

#OLD: DBGOPT, comment it out if not used.
# Not used here hence commented out.
SET(OCR_DEBUG_OPTIONS "2")

#include custom CMake scripts directory
SET(CMAKE_MODULE_PATH ${OCR_INSTALL_DIR}/${OCR_PLATFORM}/CMakeScripts)
MESSAGE(STATUS ${CMAKE_MODULE_PATH})
# Include OpenComRTOS definitions, similar to the config.mk files, but  more powerful
INCLUDE(OpenComRTOS)

PROJECT(posixnode C CXX)

enable_language(ASM)

#Configure the build system for OpenComRTOS.
OpenComRTOS_Application()

# Base directory for installing anything (headers, executable).
SET(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/.. )

SET(LINKER_LANGUAGE "C")
#Setting Project include directory as additional include directory.
INCLUDE_DIRECTORIES(${OCR_INSTALL_DIR}/${OCR_PLATFORM}/include)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../include)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES(${OCR_INSTALL_DIR}/${OCR_PLATFORM}/include/driver)
INCLUDE_DIRECTORIES(${OCR_INSTALL_DIR}/${OCR_PLATFORM}/include/GraphicalHostService)
INCLUDE_DIRECTORIES(${OCR_INSTALL_DIR}/${OCR_PLATFORM}/include/StdioHostService)
INCLUDE_DIRECTORIES(${OCR_INSTALL_DIR}/${OCR_PLATFORM}/include/kernel)
INCLUDE_DIRECTORIES(${OCR_INSTALL_DIR}/${OCR_PLATFORM}/include/sockf)
SET(CMAKE_C_LINK_FLAGS "-Wl,--no-as-needed")
include(FindPkgConfig)
pkg_check_modules (GTK3 gtk+-3.0)
message(STATUS "inc: -${GTK3_INCLUDE_DIRS}")
message(STATUS "link flags: -${GTK3_LDFLAGS}")
message(STATUS "cflags: -${GTK3_CFLAGS}")
message(STATUS "link dir: -${GTK3_LINK_DIR}")
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
LINK_LIBRARIES(${GTK3_LIBRARIES})
LINK_LIBRARIES(pthread)


# Additional library paths
LINK_LIBRARIES(rt)
LINK_LIBRARIES(lpel_hrc)
LINK_LIBRARIES(lpel_mon)
LINK_OCR_LIB(PthreadAbstractionLayer)

# User defined CFLAGS 

#Tell CMake to look in these directories for further CMakeLists.txt files
ADD_SUBDIRECTORY(src)