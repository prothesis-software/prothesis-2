#!/bin/bash

# DESCRIPTION:
# Downloads and builds wxWidgets-3.0.3 for Linux and Windows (MSYS2)

# USAGE:
# ./build-wxwidgets.sh <root_dir> <windows|windows-cross|linux>
#
# Example:
# ./build-wxwidgets.sh $HOME linux

# OUTPUTS in $ROOT_DIR:
# - wxWidgets-3.0.3-source-<linux|windows>
# - wxWidgets/<gtk2u|mswu-static|mswu-static-cross>
# - wxWidgets-3.0.3.<tar.bz2|7z>

# DEPENDENCIES:
# ## Common:
# - wget
# - patch
# - autotools
# - make
#
# ## linux:
# - tar
# - gcc
#
# ## windows:
# - p7zip
# - mingw-w64-x86_x64-gcc
# - mingw-w64-i686-gcc
#
# ## windows-cross:
# - mingw-w64-gcc

# POSITIONAL ARGS
ROOT_DIR=$1
TARGET=$2

# DEFAULTS
if [ -z ${TRAVIS_BUILD_DIR+x} ]; then
    TRAVIS_BUILD_DIR=$PWD
fi

if [ -z ${CROSS_BUILD+x} ]; then
    CROSS_BUILD=x86_64-unknown-linux-gnu
fi

if [ -z ${CROSS_HOST+x} ]; then
    CROSS_HOST=i686-w64-mingw32
fi

# '-linux' or '-windows' is later appended depending on target
SOURCE_DIR=$ROOT_DIR/wxWidgets-3.0.3-source
LINUX_INSTALL_DIR=$ROOT_DIR/wxWidgets/gtk2u
WINDOWS_INSTALL_DIR=$ROOT_DIR/wxWidgets/mswu-static
WINDOWS_CROSS_INSTALL_DIR=$ROOT_DIR/wxWidgets/mswu-static-cross

cd $ROOT_DIR

if [ "$TARGET" == "linux" ]; then
    # Check if cache exists
    if ! [ -d $LINUX_INSTALL_DIR ]; then
        SOURCE_DIR=$SOURCE_DIR-linux
        BUILD_DIR=build-gtk2u

        # Download and extract source
        wget -nc https://github.com/wxWidgets/wxWidgets/releases/download/v3.0.3/wxWidgets-3.0.3.tar.bz2
        echo "Extracting wxWidgets-3.0.3.tar.bz2"
        mkdir -p $SOURCE_DIR
        tar -xf wxWidgets-3.0.3.tar.bz2 --strip 1 -C $SOURCE_DIR

        # Patch extra ;
        patch --forward --force $SOURCE_DIR/include/wx/filefn.h $TRAVIS_BUILD_DIR/wxwidgets.patch

        cd $SOURCE_DIR

        # Build and Install
        mkdir -p $BUILD_DIR
        cd $BUILD_DIR
        ../configure --prefix=$LINUX_INSTALL_DIR \
                     --enable-unicode \
                     --with-gtk=2
        make -j $(nproc)
        make install
    else
        echo "wxWidgets has already been build for Windows"
    fi
elif [ "$TARGET" == "windows" ]; then
    # Check if cache exists
    if ! [ -d $WINDOWS_INSTALL_DIR ]; then
        SOURCE_DIR=$SOURCE_DIR-windows
        BUILD_DIR=build-mswu-static

        # Download and extract source
        wget -nc https://github.com/wxWidgets/wxWidgets/releases/download/v3.0.3/wxWidgets-3.0.3.7z
        # p7zip deletes original file, so preserve it
        cp wxWidgets-3.0.3.7z wxWidgets-3.0.3-tmp.7z
        mkdir -p $SOURCE_DIR
        cd $SOURCE_DIR
        echo "Extracting wxWidgets-3.0.3-tmp.7z ..."
        # Overwrite existing files
        echo "A" | p7zip -d ../wxWidgets-3.0.3-tmp.7z &> /dev/null
        cd ../

        # Patch extra ;
        patch --forward --force $SOURCE_DIR/include/wx/filefn.h $TRAVIS_BUILD_DIR/wxwidgets.patch

        cd $SOURCE_DIR

        # Build and Install
        mkdir -p $BUILD_DIR
        cd $BUILD_DIR
        ../configure --prefix=$WINDOWS_INSTALL_DIR \
                     --enable-unicode \
                     --disable-shared \
                     --with-msw
        make -j $(nproc)
        make install
    else
        echo "wxWidgets has already been build for Windows"
    fi
elif [ "$TARGET" == "windows-cross" ]; then
    # Check if cache exists
    if ! [ -d $WINDOWS_CROSS_INSTALL_DIR ]; then
        SOURCE_DIR=$SOURCE_DIR-linux
        BUILD_DIR=build-mswu-static-cross

        # Download and extract source
        wget -nc https://github.com/wxWidgets/wxWidgets/releases/download/v3.0.3/wxWidgets-3.0.3.tar.bz2
        echo "Extracting wxWidgets-3.0.3.tar.bz2"
        mkdir -p $SOURCE_DIR
        tar -xf wxWidgets-3.0.3.tar.bz2 --strip 1 -C $SOURCE_DIR

        # Patch extra ;
        patch --forward --force $SOURCE_DIR/include/wx/filefn.h $TRAVIS_BUILD_DIR/wxwidgets.patch

        cd $SOURCE_DIR

        # Build and Install
        mkdir -p $BUILD_DIR
        cd $BUILD_DIR
        ../configure --prefix=$WINDOWS_CROSS_INSTALL_DIR \
                     --build=$CROSS_BUILD \
                     --host=$CROSS_HOST \
                     --enable-unicode \
                     --disable-shared \
                     --with-msw \
                     CFLAGS=-I/usr/$CROSS_HOST/include
        make -j $(nproc)
        make install
    else
        echo "wxWidgets has already been build for windows-cross"
    fi
else
    echo "ERROR: Unknown target!"
fi
