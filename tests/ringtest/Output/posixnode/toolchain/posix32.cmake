# the name of the target operating system
SET(CMAKE_SYSTEM_NAME posix32)

# which compilers to use for C and C++
SET(CMAKE_C_COMPILER "gcc")

SET(CMAKE_ASM_COMPILER "gcc")

# adjust the default behavior of the FIND_XXX() commands:
# search headers and libraries in the target environment, search 
# programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM LAST)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

SET(OCR_PLATFORM "posix32")
ADD_DEFINITIONS(-DL1_GLOBALID_SIZE=32)

INCLUDE_DIRECTORIES(${OCR_INSTALL_DIR}/../../src/platforms/${OCR_PLATFORM}/include)
INCLUDE_DIRECTORIES(${OCR_INSTALL_DIR}/../../include)