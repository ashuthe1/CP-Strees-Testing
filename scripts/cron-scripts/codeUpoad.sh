#!/bin/bash

# Set your paths
SRC_DIR="../../src"
CODE_TRAVEL_DIR="../codeTravel"
REPO_DIR="../../"  # Path to the root of the Local Git repository

# Navigate to the source directory
cd "$SRC_DIR" || exit 1

# Extract the first comment from solution.cpp
FILE_NAME=$(grep -m 1 "//" solution.cpp | sed 's/^\/\/ *//')

# Ensure a valid filename is generated
if [[ -z "$FILE_NAME" ]]; then
  echo "No comment found in solution.cpp. Exiting."
  exit 1
fi

# Replace spaces with underscores in the file name
FILE_NAME="${FILE_NAME// /_}"

# Create the codeTravel directory if it doesn't exist
mkdir -p "$CODE_TRAVEL_DIR"

# Create a new file inside the codeTravel directory
NEW_FILE_PATH="$CODE_TRAVEL_DIR/$FILE_NAME.cpp"
cp solution.cpp "$NEW_FILE_PATH"

cd .. # move back to root of the project

# Add the new file to git
git add .
git commit -m "Added $FILE_NAME.cpp from solution.cpp"
git push origin main
