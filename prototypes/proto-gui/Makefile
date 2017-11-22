SOURCE=src/proto_gui_app.cpp src/welcome_frame.cpp

linux-shared: ${SOURCE}
	mkdir -p build
	g++ ${SOURCE} `wx-config --libs --cxxflags` -o build/proto-gui

run:
	./build/proto-gui
