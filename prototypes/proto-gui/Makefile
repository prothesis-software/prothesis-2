WINDOWS_WX_STATIC_DIR=/home/evert/wxWidgets-3.0.3/msw-static
SOURCE=src/proto_gui_app.cpp src/welcome_frame.cpp src/gui_generator.cpp

# Correct const name?
CC_FLAGS=-std=c++11 -g

linux-shared: ${SOURCE}
	mkdir -p build
	g++ ${SOURCE} ${CC_FLAGS} -Iinclude `wx-config --libs --cxxflags` -o build/proto-gui

windows-static: ${SOURCE}
	mkdir -p build
	i686-w64-mingw32-g++ --std=c++11  ${SOURCE} -Iinclude --static `${WINDOWS_WX_STATIC_DIR}/wx-config --libs --cxxflags` -o build/proto-gui.exe

run:
	./build/proto-gui
