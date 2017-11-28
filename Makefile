CXX=g++
CXX_WIN=i686-w64-mingw32-g++
WINDRES=i686-w64-mingw32-windres

CXXFLAGS=-std=c++11 -g -I. -Werror -Wall -pedantic
SOURCE_FILES=src/data_manager.cpp src/main_frame.cpp src/prothesis_app.cpp \
src/panels/details_panel.cpp src/data_panel.cpp src/utilities.cpp
OBJECT_FILES_LINUX=build/linux/data_manager.o build/linux/main_frame.o \
build/linux/prothesis_app.o build/linux/details_panel.o \
build/linux/data_panel.o build/linux/utilities.o
WX_CONFIG_LINUX=`wx-config --libs --cxxflags`
RESOURCE_FILE=src/resources.rc

WIN_WX_STATIC_CONFIG=.win_wx_static_config

# WX_PATH should look like /home/evert/wxWidgets-3.0.3/msw-static
# Where wxWidgets-3.0.3 is the source extracted from the .tar.gz
WX_PATH=$(shell cat ${WIN_WX_STATIC_CONFIG} 2> /dev/null)

# TODO(egeldenhuys): Better way to manage the compilation process

linux_build_dir:
	mkdir -p build/linux

lint:
	./lint.sh

build/linux/data_manager.o: src/data_manager.cpp
	${CXX} ${CXXFLAGS} ${WX_CONFIG_LINUX} -c src/data_manager.cpp \
	-o build/linux/data_manager.o

build/linux/main_frame.o: src/main_frame.cpp
	${CXX} ${CXXFLAGS} ${WX_CONFIG_LINUX} -c src/main_frame.cpp \
	-o build/linux/main_frame.o

build/linux/prothesis_app.o: src/prothesis_app.cpp
	${CXX} ${CXXFLAGS} ${WX_CONFIG_LINUX} -c src/prothesis_app.cpp \
	-o build/linux/prothesis_app.o

build/linux/details_panel.o: src/panels/details_panel.cpp
	${CXX} ${CXXFLAGS} ${WX_CONFIG_LINUX} -c src/panels/details_panel.cpp \
	-o build/linux/details_panel.o

build/linux/data_panel.o: src/data_panel.cpp
	${CXX} ${CXXFLAGS} ${WX_CONFIG_LINUX} -c src/data_panel.cpp \
	-o build/linux/data_panel.o

build/linux/utilities.o: src/utilities.cpp
	${CXX} ${CXXFLAGS} -c src/utilities.cpp \
	-o build/linux/utilities.o

linux: linux_build_dir lint ${OBJECT_FILES_LINUX}
	mkdir -p build
	${CXX} ${OBJECT_FILES_LINUX} ${CXXFLAGS} ${WX_CONFIG_LINUX} \
	-o build/prothesis-2

# TODO(egeldenhuys): Compile Windows .o files
windows: lint ${SOURCE_FILES} build/resources.o
ifneq (${WX_PATH}, )
	mkdir -p build
	${CXX_WIN} ${CXXFLAGS} ${SOURCE_FILES} --static \
	`${WX_PATH}/wx-config --libs --cxxflags` \
	build/resources.o -o build/prothesis-2.exe
else
	@echo "Please add the path to the statically compiled wxWidgets \
	to the file '.win_wx_static_config'"
endif

build/resources.o: ${RESOURCE_FILE}
	mkdir -p build
	${WINDRES} ${RESOURCE_FILE} -I${WX_PATH}/../include -o build/resources.o

clean:
	rm -fr build/
