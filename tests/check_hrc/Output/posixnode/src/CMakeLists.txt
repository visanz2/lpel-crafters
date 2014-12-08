# Configure an Executable, `posixnode' is the name of the executable without any extensions.
ADD_EXECUTABLE(posixnode
    L1_node_config.c
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Source/posixnode/posixnode.c
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Source/check_hrc.c
)
# Forcing the compiler and linker to generate 32bit binaries.
set_target_properties(posixnode PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")

#Where to install the generated target
INSTALL(TARGETS posixnode RUNTIME DESTINATION bin)