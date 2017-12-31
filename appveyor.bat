rem SOURCE: https://github.com/mypaint/libmypaint/blob/master/appveyor.bat

rem Matrix-driven Appveyor CI script for libmypaint
rem Currently only does MSYS2 builds.
rem https://www.appveyor.com/docs/installed-software#mingw-msys-cygwin
rem Needs the following vars:
rem    MSYS2_ARCH:  x86_64 or i686
rem    MSYSTEM:  MINGW64 or MINGW32

rem Set the paths appropriately
PATH C:\msys64\mingw32\bin;C:\msys64\usr\bin;%PATH%

rem Upgrade the MSYS2 platform
bash -lc "pacman --noconfirm --sync --refresh --refresh pacman"
bash -lc "pacman --noconfirm --sync --refresh --refresh --sysupgrade --sysupgrade"

rem Install required tools
bash -xlc "pacman --noconfirm -S --needed base-devel patch p7zip mingw-w64-i686-gcc make autotools"

rem Invoke subsequent bash in the build tree
cd %APPVEYOR_BUILD_FOLDER%
set CHERE_INVOKING=yes

rem Build/test scripting
bash -xlc "set pwd"
bash -xlc "env"

bash -xlc "./build-wxwidgets-init.sh"
bash -xlc "./build-prothesis-2-init.sh"
