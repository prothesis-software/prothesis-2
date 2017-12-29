#!/bin/bash

# Dependencies
# p7zip
# patch

set -e

WX_WIDGETS_SOURCE_DIR=$HOME/wxWidgets-3.0.3

WX_WIDGETS_WIN_INSTALL_DIR=$HOME/wxwidgets/msw

cd $HOME
wget -nc https://github.com/wxWidgets/wxWidgets/releases/download/v3.0.3/wxWidgets-3.0.3.7z
cp wxWidgets-3.0.3.7z wxWidgets-3.0.3-tmp.7z
mkdir -p wxWidgets-3.0.3
cd wxWidgets-3.0.3
echo "Extracting wxWidgets-3.0.3-tmp.7z ..."
echo "A" | p7zip -d ../wxWidgets-3.0.3-tmp.7z &> /dev/null
cd ../

# TODO:
TRAVIS_BUILD_DIR=$HOME/github/prothesis-2

patch --forward --force $WX_WIDGETS_SOURCE_DIR/include/wx/filefn.h $TRAVIS_BUILD_DIR/wxwidgets.patch

####################
# WINDOWS (MSW)
###############
cd $WX_WIDGETS_SOURCE_DIR

# Check if cache exists
if ! [ -d $WX_WIDGETS_WIN_INSTALL_DIR ]; then
    mkdir -p build-msw-static
    cd build-msw-static
	../configure --prefix=$WX_WIDGETS_WIN_INSTALL_DIR --disable-unicode --disable-shared --with-msw 
    make -j6
    make install
else
	echo "wxWidgets has already been build for Windows"
fi
