#!/bin/bash

WX_WIDGETS_SOURCE_DIR=$HOME/wxWidgets-3.0.3

WX_WIDGETS_LINUX_INSTALL_DIR=$HOME/wxwidgets/gtk2
WX_WIDGETS_WIN_INSTALL_DIR=$HOME/wxwidgets/msw

cd $HOME
wget https://github.com/wxWidgets/wxWidgets/releases/download/v3.0.3/wxWidgets-3.0.3.tar.bz2
tar -xf wxWidgets-3.0.3.tar.bz2

# Patch
patch $WX_WIDGETS_SOURCE_DIR/include/wx/filefn.h $TRAVIS_BUILD_DIR/wxwidgets.patch

###################
# LINUX (GTK2)
##############
cd $WX_WIDGETS_SOURCE_DIR

# Check if cache exists
if ! [ -d $WX_WIDGETS_LINUX_INSTALL_DIR ]; then
    mkdir build-gtk2
    cd build-gtk2
    ../configure --prefix=$WX_WIDGETS_LINUX_INSTALL_DIR --disable-unicode --with-gtk=2
    make
    make install
fi

####################
# WINDOWS (MSW)
###############
cd $WX_WIDGETS_SOURCE_DIR

# Check if cache exists
if ! [ -d $WX_WIDGETS_WIN_INSTALL_DIR ]; then
    mkdir build-msw-static
    cd build-msw-static
    ls /usr
    ../configure --prefix=$WX_WIDGETS_WIN_INSTALL_DIR --host=i686-w64-mingw32 --disable-unicode --with-msw --without-subdirs --disable-shared CFLAGS=-I/usr/i686-w64-mingw32/include
    ../configure --prefix=$WX_WIDGETS_WIN_INSTALL_DIR --host=i586-mingw32msvc --disable-unicode --with-msw --without-subdirs --disable-shared CFLAGS=-I/i586-mingw32msvc/include
    ../configure --prefix=$WX_WIDGETS_WIN_INSTALL_DIR --host=amd64-mingw32msvc --disable-unicode --with-msw --without-subdirs --disable-shared CFLAGS=-I/amd64-mingw32msvc/include
    make
    make install
fi
