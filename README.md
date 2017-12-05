# Prothesis v2

## Building
### Linux
```
make linux -j4

./build/prothesis-2
```

### Windows
- **NOTE:* A Windows build using 4 cores may use up to 2 GB of RAM

```
# Set config used in makefile
echo "path/to/static/msw-wxwidgets" > .win_wx_static_config

make windows -j4

./build/prothesis-2.exe
```

## Linter
The source is automatically linted when using the makefile.
It will stop compiling if there is a linting error.

```
./get-cpplint.sh
./lint.sh
```

## Development
### Dependencies
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
- `cpplint.py` (run `get-cpplint.sh`)
- `cpptoml.h` (run `get-cpptoml.sh`)

## Deploying

### Linux
#### Dependencies
- `gtk2`
- `wxgtk2`

### Windows
#### Dependencies
- None!