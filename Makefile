CXX=g++
CXX_WIN=i686-w64-mingw32-g++
WINDRES=i686-w64-mingw32-windres

CXXFLAGS=-std=c++11 -g -I. -Werror -Wall -pedantic

SOURCE_FILES=$(shell find -name '*.cpp' | sed 's/\.\///g')
OBJECT_FILES_LINUX=${SOURCE_FILES:src/%.cpp=build/linux/%.o}

OBJECT_FILES_WINDOWS=${SOURCE_FILES:src/%.cpp=build/windows/%.o}
RESOURCE_FILE=src/resources.rc

# NOTE: trailing dash is required!
# export WX_PATH_LINUX=$HOME/wxwidgets/gtk2/bin/
#
WX_CONFIG_LINUX=`${WX_PATH_LINUX}wx-config --toolkit=gtk2 --libs --cxxflags`

# WX_PATH_WINDOWS=$HOME/wxwidgets/msw

# export WX_SOURCE_PATH=$HOME/wxWidgets-3.0.3

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
	@mkdir -p $(@D)
	${CXX} ${CXXFLAGS} ${WX_CONFIG_LINUX} -c $< -o $@

linux: lint apply_gui_config ${OBJECT_FILES_LINUX}
	@echo ${SOURCE_FILES}
	mkdir -p build
	${CXX} ${OBJECT_FILES_LINUX} ${CXXFLAGS} ${WX_CONFIG_LINUX} \
	-o build/prothesis-2

################################################
# WINDOWS
#########################

build/windows/%.o: src/%.cpp
	@mkdir -p $(@D)
	${CXX_WIN} ${CXXFLAGS} ${WX_CONFIG_WINDOWS} -c $< -o $@

build/resources.o: ${RESOURCE_FILE}
	mkdir -p build
	${WINDRES} ${RESOURCE_FILE} -I${WX_SOURCE_PATH}/include -o build/resources.o

windows: lint apply_gui_config ${SOURCE_FILES} build/resources.o ${OBJECT_FILES_WINDOWS}
ifneq (${WX_PATH}, )
	mkdir -p build
	${CXX_WIN} ${CXXFLAGS} ${OBJECT_FILES_WINDOWS} ${WX_CONFIG_WINDOWS_LINK} --static \
	build/resources.o -o build/prothesis-2.exe
else
	@echo "Please add the path to the statically compiled wxWidgets \
	to the file '.win_wx_static_config'"
endif
