#!/bin/bash
# Sets up developer dependancies.

if !(wget --help &> /dev/null)
then
    echo "Please install wget"
    exit 1
fi
# Check if wget is installed
   
for file in get-*.sh
do
    bash $file
done
# Bash magics to execute
# all shell scripts prefixed with get-
