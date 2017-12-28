#!/bin/bash


cd $HOME

###############
# LINUX
#######
wget https://github.com/wxWidgets/wxWidgets/releases/download/v3.0.3/wxWidgets-3.0.3.tar.bz2
tar -xf wxWidgets-3.0.3.tar.bz2

cd wxWidgets-3.0.3

# Patch
patch include/wx/filefn.h $TRAVIS_BUILD_DIR/wxwidgets.patch

#------------
# GTK2
#-----

if ! [ -d $HOME/wxwidgets/gtk2 ]; then
    mkdir build-gtk2
    cd build-gtk2
    ../configure --prefix=$HOME/wxwidgets/gtk2 --disable-unicode --with-gtk=2
    make
    make install
fi

# cd ../
# mkdir build-msw-static
# cd build-msw-static
# ../configure --prefix=$(pwd) --host=i686-w64-mingw32 --disable-unicode --with-msw --without-subdirs --disable-shared
# make
