#!/bin/bash

# Script to build wxWidgets based on the set environment variables
# Used for Travis CI

# Variables to watch for:
# - WX_INSTALL_PATH_LINUX
# - WX_INSTALL_PATH_WINDOWS
# - WX_INSTALL_PATH_WINDOWS_CROSS

echo "Starting build-wxwidgets-init.sh ..."

if ! [ -z ${WX_INSTALL_PATH_LINUX+x} ]; then
    echo "WX_INSTALL_PATH_LINUX has been set, building wxWidgets for Linux"
    ./build-wxwidgets.sh $HOME linux
fi

if ! [ -z ${WX_INSTALL_PATH_WINDOWS_CROSS+x} ]; then
    echo "WX_INSTALL_PATH_WINDOWS_CROSS has been set, building wxWidgets for windows-cross"
    ./build-wxwidgets.sh $HOME windows-cross
fi

if ! [ -z ${WX_INSTALL_PATH_WINDOWS+x} ]; then
    echo "WX_INSTALL_PATH_WINDOWS has been set, building wxWidgets for Windows"
    ./build-wxwidgets.sh $HOME windows
fi
