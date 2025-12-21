#!/bin/bash

# Clear screen
clear

# Compile all source files with debug symbols
g++ -std=c++17 -g main.cpp */*.cpp -o main.out

if [ $? -eq 0 ]; then
    echo "Compilation successful!"
else
    echo "Compilation failed!"
    exit 1
fi
