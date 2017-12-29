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
# - WX_SOURCE_PATH  // Path where the wxWidgets source is

# export WX_PATH_WINDOWS=$HOME/wxwidgets/msw/
WX_CONFIG_WINDOWS = `${WX_PATH_WINDOWS}/wx-config --cxxflags`
WX_CONFIG_WINDOWS_LINK = `${WX_PATH_WINDOWS}/wx-config --libs`

all: linux windows
	@echo "Build done for Linux and Windows"

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
	./lint.sh

clean:
	rm -fr build/

############################################
# LINUX
####################
build/linux/%.o: src/%.cpp
	# TODO: FIX
	WX_CONFIG_FLAGS_COMPILE=`${WX_INSTALL_PATH}/bin/wx-config --toolkit=gtk2 --cxxflags`

	@mkdir -p $(@D)
	${CXX} ${CXXFLAGS} ${WX_CONFIG_FLAGS_COMPILE} -c $< -o $@

linux: lint apply_gui_config ${OBJECT_FILES_LINUX}
	WX_CONFIG_FLAGS_LINK=`${WX_INSTALL_PATH}/bin/wx-config --tookit=gtk2 --libs`

	@echo ${SOURCE_FILES}
	mkdir -p build
	${CXX} ${OBJECT_FILES_LINUX} ${CXXFLAGS} ${WX_CONFIG_FLAGS_LINK} \
	-o build/prothesis-2

################################################
# WINDOWS
#########################

build/windows/%.o: src/%.cpp
	WX_CONFIG_FLAGS_COMPILE=`${WX_INSTALL_PATH}/bin/wx-config --cxxflags`

	@mkdir -p $(@D)
	${CXX_WIN} ${CXXFLAGS} ${WX_CONFIG_WINDOWS} -c $< -o $@

build/resources.o: ${RESOURCE_FILE}
	mkdir -p build
	${WINDRES} ${RESOURCE_FILE} -I${WX_SOURCE_PATH}/include -o build/resources.o

windows: lint apply_gui_config ${SOURCE_FILES} build/resources.o ${OBJECT_FILES_WINDOWS}
	WX_CONFIG_FLAGS_LINK=`${WX_INSTALL_PATH}/bin/wx-config --libs`

	mkdir -p build
	${CXX_WIN} ${CXXFLAGS} ${OBJECT_FILES_WINDOWS} ${WX_CONFIG_FLAGS_LINK} --static \
	build/resources.o -o build/prothesis-2.exe
