#!/bin/bash

# DESCRIPTION:
# Downloads and builds wxWidgets-3.0.3 for Linux and Windows (MSYS2)

# Usage:
# ./build-wxwidgets.sh <root_dir> <win|linux> <cores>
#
# ./build-wxwidgets.sh $HOME linux 6

# Dependencies:
#
# ## Common:
# - wget
# - sed
# - autotools
# - make
# - gcc
#
# ## Linux:
# - tar
#
# ## Windows:
# - p7zip

ROOT_DIR=$1
TARGET=$2
MAKE_CORES=$3

if [ -z ${var+x} ]; then
    TRAVIS_BUILD_DIR=$PWD
fi

# '-linux' or '-win' is appended depending on target
SOURCE_DIR=$ROOT_DIR/wxWidgets-3.0.3-source
LINUX_INSTALL_DIR=$ROOT_DIR/wxWidgets/3.0.3/gtk2
WIN_INSTALL_DIR=$ROOT_DIR/wxWidgets/3.0.3/msw-static

cd $ROOT_DIR

# Download and extract source
if [ "$TARGET" == "linux" ]; then
    SOURCE_DIR=$SOURCE_DIR-linux

    wget -nc https://github.com/wxWidgets/wxWidgets/releases/download/v3.0.3/wxWidgets-3.0.3.tar.bz2
    echo "Extracting wxWidgets-3.0.3.tar.bz2"
    tar -xf wxWidgets-3.0.3.tar.bz2
    mv wxWidgets-3.0.3 $SOURCE_DIR

elif [ "$TARGET" == "win" ]; then
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
patch --forward --force $WX_WIDGETS_SOURCE_DIR/include/wx/filefn.h $TRAVIS_BUILD_DIR/wxwidgets.patch

cd $SOURCE_DIR
# Build and Install
if [ "$TARGET" == "linux" ]; then
    # Check if cache exists
    if ! [ -d $LINUX_INSTALL_DIR ]; then
        mkdir -p build-gtk2
        cd build-gtk2
        ../configure --prefix=$LINUX_INSTALL_DIR --disable-unicode --with-gtk=2
        make -j $MAKE_CORES
        make install
    else
        echo "wxWidgets has already been build for Linux"
    fi
elif [ "$TARGET" == "win" ]; then
    # Check if cache exists
    if ! [ -d $WIN_INSTALL_DIR ]; then
        mkdir -p build-msw-static
        cd build-msw-static
        ../configure --prefix=$WIN_INSTALL_DIR --disable-unicode --disable-shared --with-msw 
        make -j $MAKE_CORES
        make install
    else
        echo "wxWidgets has already been build for Windows"
    fi
fi
