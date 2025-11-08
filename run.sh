#!/bin/bash
clear

EXEC="main.out"
echo "Compiling your code..."
g++ main.cpp */*.cpp -o "$EXEC"
echo "Compilation completed..."
echo ""
echo ""
if [ $? -eq 0 ]; then
    echo "Executing Program..."
    echo "----------------------------Program Output-------------------------------------"
    ./"$EXEC"
    echo "----------------------------Execution Finished---------------------------------"
else
    echo "Compilation failed!"
fi
