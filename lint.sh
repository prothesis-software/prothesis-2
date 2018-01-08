#!/bin/bash

clang-format -i src/*.*pp -style=Google
clang-format -i src/panels/*.*pp -style=Google


python2 cpplint.py --headers=hpp --extensions=cpp,hpp \
        --root=src/ --filter=-legal/copyright \
        src/* include/* src/panels/*
