# Prothesis v2

Prothesis software for Target Life

## Building
### Linux
#### wxWidgets
View the `build-wxwidgets.sh` for more information

```
./build-wxwidgets.sh <root_dir> linux
```
- wxWidgets will be installed at <root_dir>/wxWidgets/gtk2u
- wxWidgets source will be at <root_dir>/wxWidgets-3.0.3-linux
- wxWidgets source archive will be downloaded to <root_dir>/wxWidgets-3.0.3.tar.bz2

#### Prothesis-2
##### Dependencies
- [wxWidgets 3.0.3](https://github.com/prothesis-software/prothesis-2/wiki/Compiling-wxWidgets)
  - `gtk2`
  - `make`
  - `gcc`
  - `pkg-config`
  - `mingw-w64-gcc`
  - Shared gtk2 build of wxWidgets for Linux
  - Static msw build of wxWidgets for Windows cross compilation
- `python2` (for linting)
- `wget` (downloading dependencies)
- `cpplint.py` (run `make get-deps`)
- `cpptoml.h` (run `make get-deps`)

```
export WX_INTALL_PATH_LINUX=<root_dir>/wxWidgets/gtku2/
make linux -j $(nproc)
```

### Windows
#### wxWidgets
- Install MSYS2 (see wiki)

```
# Install dependencies
pacman -S git mingw-w64-i686-gcc python2 p7zip make patch

# Build wxWidgets
./build-wxdigets <root_dir> windows
```

#### Prothesis-2
##### Dependencies
```
pacman -S mingw-w64-i686-g++
```

##### Building
```
export WX_INSTALL_PATH_WINDOWS=<root_dir>/wxWidgets/mswu-static
make windows -j ($nproc)
```

## Deploying
### Linux
#### Dependencies
- `gtk2`
- `wxgtk2`

### Windows
#### Dependencies
- None!