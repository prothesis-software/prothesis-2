SOURCE=src/proto_gui_app.cpp src/welcome_frame.cpp src/gui_generator.cpp

# Correct const name?
CC_FLAGS=-std=c++11 -g

linux-shared: ${SOURCE}
	mkdir -p build
	g++ ${SOURCE} ${CC_FLAGS} -Iinclude `wx-config --libs --cxxflags` -o build/proto-gui

run:
	./build/proto-gui
