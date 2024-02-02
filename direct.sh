#!/bin/bash

# Compile the C++ program
g++ main.cpp -lncurses -o main

# Get the current working directory
rootDir=$(pwd)

# Run your C++ program
./main

# Read the selected directory from the temporary file
selected_directory=$(<selected_directory.txt)

# Print the selected directory to the terminal
# echo "Selected Directory: $selected_directory"

# Change to the selected directory
cd "$selected_directory" || { echo "Error: Unable to change directory"; exit 1; }

# Print the root directory
echo "$rootDir"

# Remove the temporary file
rm -rf "$rootDir"/selected_directory.txt
