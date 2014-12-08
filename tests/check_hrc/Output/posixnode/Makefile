OCR_PLATFORM_DIR=/mnt/OpenComRTOS/s-net_distribution/lpel-master/src/include/OpenComRTOS
OCR_PLATFORM_NAME=posix32
NODE_NAME=posixnode
NODE_NUM=0
OCR_VARIANT=SP
CURRENT_DIR="`pwd`/.."
CMAKE_GENERATOR="Unix Makefiles"
MKDIR =mkdir
RMDIR =rm -rf
CD    =cd
CHAIN =;

CMAKE_TOOLCHAIN="$(CURRENT_DIR)/toolchain/posix32.cmake"

PROJECT="/mnt/OpenComRTOS/s-net_distribution/lpel-master/tests/check_hrc//posixnode/posixnode.ove"
XALAN=$(OCR_PLATFORM_DIR)/bin/Xalan
XSLT_DIR="$(OCR_PLATFORM_DIR)/$(OCR_PLATFORM_NAME)/XSLT"

all: generate build

generate: builddir
	$(XALAN) -o src/CMakeLists.txt tmp$(NODE_NAME).xml $(XSLT_DIR)/CMakeLists2.xslt
	$(XALAN) -o CMakeLists.txt tmp$(NODE_NAME).xml $(XSLT_DIR)/CMakeLists1.xslt
	$(XALAN) -o toolchain/$(OCR_PLATFORM_NAME).cmake tmp$(NODE_NAME).xml $(XSLT_DIR)/toolchain.xslt
	$(XALAN) -o ../bin/OpenComRTOS_Node$(NODE_NUM).entities tmp$(NODE_NAME).xml $(XSLT_DIR)/nodeIDxml.xslt
	$(XALAN) -o ../include/L1_$(NODE_NAME)_data.h tmp$(NODE_NAME).xml $(XSLT_DIR)/L1_node_data_H.xslt
	$(XALAN) -o src/L1_node_config.c tmp$(NODE_NAME).xml $(XSLT_DIR)/L1_node_config_C.xslt
	$(XALAN) -o include/L1_node_config.h tmp$(NODE_NAME).xml $(XSLT_DIR)/L1_node_config_H.xslt
	$(XALAN) -o include/L1_node_id_mapping.h tmp$(NODE_NAME).xml $(XSLT_DIR)/L1_node_id_mapping_H.xslt
	$(XALAN) -o ../bin/$(NODE_NAME).xml tmp$(NODE_NAME).xml $(XSLT_DIR)/debugger.xslt

builddir: src/.dir include/.dir toolchain/.dir ../bin/.dir

src/.dir include/.dir toolchain/.dir ../bin/.dir:
	$(MKDIR) "$(subst /.dir,,$@)"
	echo > "$@"

build: force
	${RMDIR} Build
	${MKDIR} Build
	${CD} Build ${CHAIN} cmake ../ -G ${CMAKE_GENERATOR} -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN}
	${CD} Build ${CHAIN} ${MAKE} all install

force:
