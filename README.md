# Prothesis v2

## Building
```
make linux

# Set config used in makefile
echo "path/to/static/msw-wxwidgets" > .win_wx_static_config
make windows
```

## Linter
```
./get-cpplint.sh
./lint.sh
```

## Development
### Dependencies
- [wxWidgets 3.0.3](https://github.com/prothesis-software/prothesis-2/wiki/Compiling-wxWidgets)
  - `gtk3`
  - `make`
  - `gcc`
  - `pkg-config`
  - `mingw-w64-gcc`
  - Shared gtk3 build of wxWidgets for Linux
  - Static msw build of wxWidgets for Windows cross compilation
- `python2` (for linting)
- `wget` (downloading dependencies)
- `cpplint.py` (run `get-cpplint.sh`)
- `cpptoml.h` (run `get-cpptoml.sh`)

## Deploying
### Linux
#### Dependencies
- `wxgtk3`
### Windows
#### Dependencies
- None!