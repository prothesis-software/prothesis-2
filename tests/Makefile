CXX=g++
CXX_WIN=i686-w64-mingw32-g++
CXXFLAGS=-I. -I./../ --std=c++11 -g

all: cpptoml
	@echo "Done."

build_dir:
	mkdir -p build

cpptoml_windows: build_dir cpptoml.cpp
	${CXX_WIN} ${CXXFLAGS} --static cpptoml.cpp -o build/cpptoml.exe

cpptoml_linux: build_dir cpptoml.cpp
	${CXX} ${CXXFLAGS} cpptoml.cpp -o build/cpptoml

cpptoml: cpptoml_linux cpptoml_windows
	@echo "Made cpptoml for linux and windows"

clean:
	rm -fr build/
