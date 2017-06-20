#!/bin/bash

#
# Clears all temporary files used by npm.
#

# Clean node_modules
rm -r -f ./node_modules/*

# Clean builds
rm -r -f ./build/*

# Clean logs
rm -r -f ~/.npm

# Clean files in temp directory ( sort of redundant but stop abusing my disk )
sudo rm -r -f /tmp/npm-*
sudo rm -r -f /tmp/electron-*
