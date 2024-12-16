#!/bin/bash

echo
echo "=========================="
echo "Building blockchain project..."
echo "=========================="
echo

# Create directories if they do not exist
mkdir -p ../bin
mkdir -p ../bin-int

# Change directory to src
cd ..

# Compile the project
echo "Compiling source files..."
gcc -o bin-int/main.o src/main.c -lssl -lcrypto -c

if [ $? -ne 0 ]; then
    echo
    echo "Compilation failed!"
    exit 1
fi

# Link object files
echo "Linking object files..."
gcc -o bin/blockchain bin-int/main.o -lssl -lcrypto

if [ $? -ne 0 ]; then
    echo
    echo "Linking failed!"
    exit 1
fi

echo
echo "=========================="
echo "Build successful!"
echo "=========================="
echo "Running blockchain..."
echo

./bin/blockchain
