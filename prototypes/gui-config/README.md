# GUI Config Prototype

- [Hello World source](https://wiki.wxwidgets.org/Hello_World)

## Goals
- GUI config in TOML
- TOML parser
- Create some basic GUI components in the gui-config-driver
- Build a GUI based on the GUI config

## Development Environment
### [Meson](http://mesonbuild.com/index.html)
- Follow the Quick Guide

### [wxWidgets]()
- Get wxWidgets:
  - [Compile from source](https://wiki.wxwidgets.org/Compiling_and_getting_started)
  - Download binary somewhere?
  - `pacman -S wxgtk3` or wxgtk2
## Compiling
```
meson build
cd build/
ninja
./main
```