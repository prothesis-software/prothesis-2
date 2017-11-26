CXX=g++
CXX_WIN=i686-w64-mingw32-g++
WINDRES=i686-w64-mingw32-windres

CXXFLAGS=-std=c++11 -g -I. -Werror -Wall -pedantic
SOURCE_FILES=src/data_manager.cpp src/main_frame.cpp src/prothesis_app.cpp \
src/panels/details_panel.cpp src/data_panel.cpp
RESOURCE_FILE=src/resources.rc

WIN_WX_STATIC_CONFIG=.win_wx_static_config

# WX_PATH should look like /home/evert/wxWidgets-3.0.3/msw-static
# Where wxWidgets-3.0.3 is the source extracted from the .tar.gz
WX_PATH=$(shell cat ${WIN_WX_STATIC_CONFIG} 2> /dev/null)

# TODO: Compile sources individually

linux: ${SOURCE_FILES}
	mkdir -p build
	./lint.sh
	${CXX} ${SOURCE_FILES} ${CXXFLAGS} `wx-config --libs --cxxflags` \
	-o build/prothesis-2

windows: ${SOURCE_FILES} build/resources.o
ifneq (${WX_PATH}, )
	mkdir -p build
	./lint.sh
	${CXX_WIN} ${SOURCE_FILES} ${CXXFLAGS} --static \
	`${WX_PATH}/wx-config --libs --cxxflags` \
	build/resources.o -o build/prothesis-2.exe
else
	@echo "Please add the path to the statically compiled wxWidgets \
	to the file '.win_wx_static_config'"
endif

# TODO: Is this correct Makefile notation?
build/resources.o: ${RESOURCE_FILE}
	${WINDRES} ${RESOURCE_FILE} -I${WX_PATH}../include -o build/resources.o

clean:
	rm -fr build/
