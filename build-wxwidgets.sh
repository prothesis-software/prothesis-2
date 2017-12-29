#!/bin/bash

# Usage:
# ./build-wxwidgets.sh <root_dir> <win|linux>
#
# ./build-wxwidgets.sh $HOME linux

# Dependencies:
#
# ## Common:
# - wget
# - sed
# - autotools
# - make
#
# ## Linux:
# - tar
#
# ## Windows:
# - p7zip

ROOT_DIR=$2
# '-linux' or '-win' is appended depending on target
SOURCE_DIR=$1/wxWidgets-3.0.3-source
LINUX_INSTALL_DIR=$1/wxWidgets/3.0.3/gtk2
WIN_INSTALL_DIR=$1/wxWidgets/3.0.3/msw-static

cd $ROOT_DIR

# Download and extract source
if [ "$2" == "linux" ]; then
    SOURCE_DIR=$SOURCE_DIR-linux

    wget -nc https://github.com/wxWidgets/wxWidgets/releases/download/v3.0.3/wxWidgets-3.0.3.tar.bz2
    mkdir -p $SOURCE_DIR
    echo "Extracting wxWidgets-3.0.3.tar.bz2"
    tar -xf wxWidgets-3.0.3.tar.bz2 -C $SOURCE_DIR

elif [ "$2" == "win" ]; then
    SOURCE_DIR=$SOURCE_DIR-win

    wget -nc https://github.com/wxWidgets/wxWidgets/releases/download/v3.0.3/wxWidgets-3.0.3.7z
    # p7zip deletes original file, so preserve it
    cp wxWidgets-3.0.3.7z wxWidgets-3.0.3-tmp.7z
    mkdir -p $SOURCE_DIR
    cd $SOURCE_DIR
    echo "Extracting wxWidgets-3.0.3-tmp.7z ..."
    # Overwrite existing files
    echo "A" | p7zip -d ../wxWidgets-3.0.3-tmp.7z &> /dev/null
    cd ../
fi

# Patch extra ;
sed -i '220s/wxDECL_FOR_STRICT_MINGW32\(int, fseeko64, \(FILE*, long long, int\)\);\
/wxDECL_FOR_STRICT_MINGW32\(int, fseeko64, \(FILE*, long long, int\)\);/' $SOURCE_DIR/include/wx/filefn.h

cd $SOURCE_DIR
# Build and Install
if [ "$2" == "linux" ]; then
    # Check if cache exists
    if ! [ -d $LINUX_INSTALL_DIR ]; then
        mkdir build-gtk2
        cd build-gtk2
        ../configure --prefix=$LINUX_INSTALL_DIR --disable-unicode --with-gtk=2
        make
        make install
    else
        echo "wxWidgets has already been build for Linux"
    fi
elif [ "$2" == "win" ]; then
    # Check if cache exists
    if ! [ -d $WIN_INSTALL_DIR ]; then
        mkdir build-msw-static
        cd build-msw-static
        ../configure --prefix=$WX_WIDGETS_WIN_INSTALL_DIR --disable-unicode --disable-shared --with-msw 
        make
        make install
    else
        echo "wxWidgets has already been build for Windows"
    fi
fi
