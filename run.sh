#!/bin/bash
clear

EXEC="main.out"
BUILD_DIR="build"
SRC_DIRS="dp graphs tree"
SOURCES="main.cpp"

# Create build directory
mkdir -p "$BUILD_DIR"

# Collect all source files
ALL_SOURCES="$SOURCES"
for dir in $SRC_DIRS; do
    if [ -d "$dir" ]; then
        ALL_SOURCES="$ALL_SOURCES $dir/*.cpp"
    fi
done

# Expand to actual file list
SOURCE_FILES=()
for pattern in $ALL_SOURCES; do
    for file in $pattern; do
        [ -f "$file" ] && SOURCE_FILES+=("$file")
    done
done

# Check for '-e' flag
if [ "$1" == "-e" ]; then
    if [ -f "$EXEC" ]; then
        echo "Executing existing program..."
        echo "----------------------------Program Output-------------------------------------"
        ./"$EXEC"
        echo "----------------------------Execution Finished---------------------------------"
    else
        echo "Error: Executable '$EXEC' not found. Please compile first."
    fi
    exit 0
fi

needs_build=0

# Check if executable exists
if [ ! -f "$EXEC" ]; then
    echo "No executable found. Full build required."
    needs_build=1
else
    echo "Checking for changes..."
    for src in "${SOURCE_FILES[@]}"; do
        obj="$BUILD_DIR/$(basename "$src" .cpp).o"
        if [ "$src" -nt "$EXEC" ] || [ ! -f "$obj" ] || [ "$src" -nt "$obj" ]; then
            echo "Changed: $src"
            needs_build=1
        fi
    done
fi

if [ $needs_build -eq 0 ]; then
    echo "Everything up to date. Skipping build."
else
    echo "Building changed files..."
    # Compile only changed files to objects
    for src in "${SOURCE_FILES[@]}"; do
        obj="$BUILD_DIR/$(basename "$src" .cpp).o"
        if [ "$src" -nt "$obj" ] || [ ! -f "$obj" ]; then
            echo "Compiling $src -> $obj"
            g++ -Wall -Wextra -std=c++17 -O2 -c "$src" -o "$obj"
            if [ $? -ne 0 ]; then
                echo "Compilation failed."
                exit 1
            fi
        fi
    done

    # Link all objects
    echo "Linking..."
    g++ $BUILD_DIR/*.o -o "$EXEC"
    if [ $? -ne 0 ]; then
        echo "Linking failed."
        exit 1
    fi
    echo "Build successful!"
fi

echo ""
echo "Executing Program..."
echo "----------------------------Program Output-------------------------------------"
./"$EXEC"
echo "----------------------------Execution Finished---------------------------------"