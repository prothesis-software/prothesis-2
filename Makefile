CXX=g++
CXX_WIN=i686-w64-mingw32-g++
WINDRES=i686-w64-mingw32-windres

CXXFLAGS=-std=c++11 -g -I. -Werror -Wall -pedantic
SOURCE_FILES=src/data_manager.cpp src/main_frame.cpp src/prothesis_app.cpp \
src/panels/details_panel.cpp src/data_panel.cpp src/utilities.cpp
OBJECT_FILES_LINUX=build/linux/data_manager.o build/linux/main_frame.o \
build/linux/prothesis_app.o build/linux/details_panel.o \
build/linux/data_panel.o build/linux/utilities.o
OBJECT_FILES_WINDOWS=build/windows/data_manager.o build/windows/main_frame.o \
build/windows/prothesis_app.o build/windows/details_panel.o \
build/windows/data_panel.o build/windows/utilities.o
WX_CONFIG_LINUX=`wx-config --libs --cxxflags`
RESOURCE_FILE=src/resources.rc

WIN_WX_STATIC_CONFIG=.win_wx_static_config

# WX_PATH should look like /home/evert/wxWidgets-3.0.3/msw-static
# Where wxWidgets-3.0.3 is the source extracted from the .tar.gz
WX_PATH=$(shell cat ${WIN_WX_STATIC_CONFIG} 2> /dev/null)
WX_CONFIG_WINDOWS = `${WX_PATH}/wx-config --cxxflags`
WX_CONFIG_WINDOWS_LINK = `${WX_PATH}/wx-config --libs`

windows_build_dir:
	mkdir -p build/windows

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

build/windows/data_manager.o: src/data_manager.cpp
	${CXX_WIN} ${CXXFLAGS} ${WX_CONFIG_WINDOWS} -c src/data_manager.cpp \
	-o build/windows/data_manager.o

build/windows/main_frame.o: src/main_frame.cpp
	${CXX_WIN} ${CXXFLAGS} ${WX_CONFIG_WINDOWS} -c src/main_frame.cpp \
	-o build/windows/main_frame.o

build/windows/prothesis_app.o: src/prothesis_app.cpp
	${CXX_WIN} ${CXXFLAGS} ${WX_CONFIG_WINDOWS} -c src/prothesis_app.cpp \
	-o build/windows/prothesis_app.o

build/windows/details_panel.o: src/panels/details_panel.cpp
	${CXX_WIN} ${CXXFLAGS} ${WX_CONFIG_WINDOWS} -c src/panels/details_panel.cpp \
	-o build/windows/details_panel.o

build/windows/data_panel.o: src/data_panel.cpp
	${CXX_WIN} ${CXXFLAGS} ${WX_CONFIG_WINDOWS} -c src/data_panel.cpp \
	-o build/windows/data_panel.o

build/windows/utilities.o: src/utilities.cpp
	${CXX_WIN} ${CXXFLAGS} -c src/utilities.cpp \
	-o build/windows/utilities.o

build/resources.o: ${RESOURCE_FILE}
	mkdir -p build
	${WINDRES} ${RESOURCE_FILE} -I${WX_PATH}/../include -o build/resources.o

windows: windows_build_dir lint ${SOURCE_FILES} build/resources.o ${OBJECT_FILES_WINDOWS}
ifneq (${WX_PATH}, )
	mkdir -p build
	${CXX_WIN} ${CXXFLAGS} ${OBJECT_FILES_WINDOWS} ${WX_CONFIG_WINDOWS_LINK} --static \
	build/resources.o -o build/prothesis-2.exe
else
	@echo "Please add the path to the statically compiled wxWidgets \
	to the file '.win_wx_static_config'"
endif

clean:
	rm -fr build/
