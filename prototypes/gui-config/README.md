# GUI Config Prototype

- [Hello World source](https://wiki.wxwidgets.org/Hello_World)

## Goals
- GUI config in TOML
- TOML parser
- Create some basic GUI components in the gui-config-driver
- Build a GUI based on the GUI config

## Development Environment
### Base
```
sudo pacman -S gcc pkg-config gtk2 make
```

### [Meson](http://mesonbuild.com/index.html)
```
sudo pacman -S ninja
sudo pacman -S python-pip
sudo pip install meson
```


### [wxWidgets](https://www.wxwidgets.org/)
- [Compiling and Getting Started - Wiki](https://wiki.wxwidgets.org/Compiling_and_getting_started)
- Download [wxWidgets-3.0.3.tar.bz2](https://github.com/wxWidgets/wxWidgets/releases/download/v3.0.3/wxWidgets-3.0.3.tar.bz2)

```
tar -xf wxWidgets-3.0.3.tar.bz2
cd wxWidgets-3.0.3
mkdir gtk-build
cd gtk-build
../configure --enable-unicode
make -j4 # use 4 cores
```

## Compiling
```
meson build
cd build/
ninja
./main
```