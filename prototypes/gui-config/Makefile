LINUX_WX_STATIC_DIR=/home/evert/wxWidgets-3.0.3/gtk-build-static
WINDOWS_WX_STATIC_DIR=/home/evert/wxWidgets-3.0.3/msw-static

linux-shared: src/hello.cpp
	mkdir -p build
	g++ src/hello.cpp `wx-config --libs --cxxflags` -o build/hello

linux-static: src/hello.cpp
	@#mkdir -p build
	@#g++ src/hello.cpp --static `${LINUX_WX_STATIC_DIR}/wx-config --static --libs --cxxflags` -o build/hello
	@echo Sorry, that does not, and will not work

windows-static: src/hello.cpp
	mkdir -p build
	i686-w64-mingw32-g++ src/hello.cpp --static `${WINDOWS_WX_STATIC_DIR}/wx-config --libs --cxxflags` -o build/hello.exe
