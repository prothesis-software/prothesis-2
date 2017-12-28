#!/bin/bash

cd ~

###############
# LINUX
#######
wget https://github.com/wxWidgets/wxWidgets/releases/download/v3.0.3/wxWidgets-3.0.3.tar.bz2
tar -xf wxWidgets-3.0.3.tar.bz2

cd wxWidgets-3.0.3

#------------
# GTK2
#-----
mkdir build-gtk2
cd build-gtk2
../configure --prefix=~/wxwidgets/gtk2 --disable-unicode --with-gtk=2
make
make install

# cd ../
# mkdir build-msw-static
# cd build-msw-static
# ../configure --prefix=$(pwd) --host=i686-w64-mingw32 --disable-unicode --with-msw --without-subdirs --disable-shared
# make
