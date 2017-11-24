#!/bin/bash

python2 cpplint.py --headers=hpp --extensions=cpp,hpp --root=src/ --filter=-legal/copyright src/* include/*
