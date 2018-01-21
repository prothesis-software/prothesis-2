####################
# ARGS
######
#	DEBUG=[0|1]

PROTHESIS_VERSION=2.0.0-dev.2

CXXFLAGS=-std=c++11 -stdlib=libc++ -I. -Werror -Wall -pedantic -Wno-write-strings

DEBUG=1

ifeq ($(DEBUG),1)
        CXXFLAGS+=-g
endif

CXXFLAGS+=-DPROTHESIS_VERSION=\"${PROTHESIS_VERSION}\"

WINDRES=windres
SOURCE_FILES=$(shell find . -name '*.cpp' | sed 's/\.\///g')
OBJECT_FILES_LINUX=${SOURCE_FILES:src/%.cpp=build/linux/%.o}
RESOURCE_FILE=src/resources.rc

OBJECT_FILES_WINDOWS=${SOURCE_FILES:src/%.cpp=build/windows/%.o}

PACKAGE_LINUX_NAME=prothesis-linux-x86_64-${PROTHESIS_VERSION}
PACKAGE_WINDOWS_NAME=prothesis-windows-32bit-${PROTHESIS_VERSION}


#######################
# Enviornment Variables
###########
# - WX_INSTALL_PATH_LINUX  	// Path where wxWidgets is installed to for linux builds
# - WX_INSTALL_PATH_WINDOWS	// Path where wxWidgets is installed for Windows and windows-cross
# - WX_INSTALL_PATH_WINDOWS_CROSS	// Path where wxWidgets is installed for windows-cross
#					// Used only for triggering the wxWidgets build
WX_INSTALL_PATH_WINDOWS=${WX_INSTALL_PATH_WINDOWS_CROSS}

WX_CONFIG_FLAGS_COMPILE_LINUX=`${WX_INSTALL_PATH_LINUX}/bin/wx-config --unicode=yes --cxxflags`
WX_CONFIG_FLAGS_LINK_LINUX=`${WX_INSTALL_PATH_LINUX}/bin/wx-config --unicode=yes --libs`

WX_CONFIG_FLAGS_COMPILE_WINDOWS=`${WX_INSTALL_PATH_WINDOWS}/bin/wx-config --unicode=yes --cxxflags`
WX_CONFIG_FLAGS_LINK_WINDOWS=`${WX_INSTALL_PATH_WINDOWS}/bin/wx-config --unicode=yes --libs`

##############################################
# COMMON
############

clang-format:
	-clang-format -i --style=file src/* src/panels/*

package: package-linux package-windows
	@echo "Done"

get-deps:
	#./get-cpplint.sh
	./get-cpptoml.sh

apply_gui_config:
	mkdir -p build
	cp -f gui.toml build/

lint:
	@echo "Remember to set the WX_INSTALL_PATH_LINUX and WX_INSTALL_PATH_WINDOWS"
	# ./lint.sh

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

package-linux: build/prothesis-2 gui.toml
	mkdir -p /tmp/${PACKAGE_LINUX_NAME}
	cp build/prothesis-2 gui.toml CHANGELOG.md LICENSE.md /tmp/${PACKAGE_LINUX_NAME}
	cd build && tar -czvf ${PACKAGE_LINUX_NAME}.tar.gz  -C /tmp ${PACKAGE_LINUX_NAME}
	rm -fr /tmp/${PACKAGE_LINUX_NAME}

################################################
# WINDOWS
#########################
# Example:
# 	export WX_INSTALL_PATH_WINDOWS=...
# 	make windows CXX=x86_64-w64-mingw32-g++ WINDRES=x86_64-w64-mingw32-windres

build/windows/%.o: src/%.cpp
	@mkdir -p $(@D)
	${CXX} ${CXXFLAGS} ${WX_CONFIG_FLAGS_COMPILE_WINDOWS} -c $< -o $@

build/resources.o: ${RESOURCE_FILE}
	mkdir -p build
	${WINDRES} -I${WX_INSTALL_PATH_WINDOWS}/include/wx-3.0 ${RESOURCE_FILE} -o build/resources.o

windows: lint apply_gui_config ${SOURCE_FILES} build/resources.o ${OBJECT_FILES_WINDOWS}
	mkdir -p build
	${CXX} ${CXXFLAGS} ${OBJECT_FILES_WINDOWS} ${WX_CONFIG_FLAGS_LINK_WINDOWS} --static \
	build/resources.o -o build/prothesis-2.exe

package-windows: build/prothesis-2.exe gui.toml
	mkdir -p /tmp/${PACKAGE_WINDOWS_NAME}
	cp build/prothesis-2.exe gui.toml CHANGELOG.md LICENSE.md /tmp/${PACKAGE_WINDOWS_NAME}
	cd build && bsdtar -acf ${PACKAGE_WINDOWS_NAME}.zip -C /tmp ${PACKAGE_WINDOWS_NAME}
	rm -fr /tmp/${PACKAGE_WINDOWS_NAME}
