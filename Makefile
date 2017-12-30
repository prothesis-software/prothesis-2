CXX=g++
CXXFLAGS=-std=c++11 -g -I. -Werror -Wall -pedantic
WINDRES=windres

SOURCE_FILES=$(shell find -name '*.cpp' | sed 's/\.\///g')
OBJECT_FILES_LINUX=${SOURCE_FILES:src/%.cpp=build/linux/%.o}
RESOURCE_FILE=src/resources.rc

OBJECT_FILES_WINDOWS=${SOURCE_FILES:src/%.cpp=build/windows/%.o}

#####################3
# Enviornment Variables
###########
# - WX_INSTALL_PATH  // Path where wxWidgets is installed to

WX_CONFIG_FLAGS_COMPILE_LINUX=`${WX_INSTALL_PATH}/bin/wx-config --toolkit=gtk2 --cxxflags`
WX_CONFIG_FLAGS_LINK_LINUX=`${WX_INSTALL_PATH}/bin/wx-config --toolkit=gtk2 --libs`

WX_CONFIG_FLAGS_COMPILE_WIN=`${WX_INSTALL_PATH}/bin/wx-config --cxxflags`
WX_CONFIG_FLAGS_LINK_WIN=`${WX_INSTALL_PATH}/bin/wx-config --libs`

##############################################
# COMMON
############

get-deps:
	./get-cpplint.sh
	./get-cpptoml.sh

apply_gui_config:
	mkdir -p build
	cp gui.toml build/

lint:
	@echo "-------------------------------------------------------------------"
	@echo "Remember to set the WX_INSTALL_PATH!
	@echo "-------------------------------------------------------------------"
	./lint.sh

clean:
	rm -fr build/

############################################
# LINUX
####################
build/linux/%.o: src/%.cpp
	@mkdir -p $(@D)
	${CXX} ${CXXFLAGS} ${WX_CONFIG_FLAGS_COMPILE_LINUX} -c $< -o $@

linux: lint apply_gui_config ${OBJECT_FILES_LINUX}
	@echo ${SOURCE_FILES}
	mkdir -p build
	${CXX} ${CXXFLAGS} ${OBJECT_FILES_LINUX} ${WX_CONFIG_FLAGS_LINK_LINUX} \
	-o build/prothesis-2

################################################
# WINDOWS
#########################

build/windows/%.o: src/%.cpp
	@mkdir -p $(@D)
	${CXX} ${CXXFLAGS} ${WX_CONFIG_FLAGS_COMPILE_WIN} -c $< -o $@

build/resources.o: ${RESOURCE_FILE}
	mkdir -p build
	${WINDRES} -I${WX_INSTALL_PATH}/include ${RESOURCE_FILE} -o build/resources.o

windows: lint apply_gui_config ${SOURCE_FILES} build/resources.o ${OBJECT_FILES_WINDOWS}
	mkdir -p build
	${CXX} ${CXXFLAGS} ${OBJECT_FILES_WINDOWS} ${WX_CONFIG_FLAGS_LINK_WIN} --static \
	build/resources.o -o build/prothesis-2.exe
