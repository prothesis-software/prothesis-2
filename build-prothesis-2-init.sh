#!/bin/bash

# Script to build prothesis-2 based on the set environment variables
# Used for Travis CI

# Variables to watch for:
# - WX_INSTALL_PATH_LINUX
# - WX_INSTALL_PATH_WINDOWS
# - WX_INSTALL_PATH_WINDOWS_CROSS

echo "Starting build-prothesis-2-init.sh ..."

if ! [ -z ${WX_INSTALL_PATH_LINUX+x} ]; then
    echo "WX_INSTALL_PATH_LINUX has been set, building prothesis-2 for Linux"
    make linux -j $(nproc)
fi

if ! [ -z ${WX_INSTALL_PATH_WINDOWS_CROSS+x} ]; then
    echo "WX_INSTALL_PATH_WINDOWS_CROSS has been set, building prothesis-2 for windows-cross"
    make windows CXX=x86_64-w64-mingw32-g++ WINDRES=x86_64-w64-mingw32-windres -j $(nproc)
fi

if ! [ -z ${WX_INSTALL_PATH_WINDOWS+x} ]; then
    echo "WX_INSTALL_PATH_WINDOWS has been set, building prothesis-2 for Windows"
    make windows -j $(nproc)
fi
