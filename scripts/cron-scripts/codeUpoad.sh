#!/bin/bash

# Set your paths
SRC_DIR="../../src"
CODE_TRAVEL_DIR="../codeTravel"
REPO_DIR="../../"  # Path to the root of the Local Git repository

# Navigate to the source directory
cd "$SRC_DIR" || exit 1

# Extract the first comment from solution.cpp
COMMENT=$(grep -m 1 "//" solution.cpp | sed 's/^\/\/ *//')

# Ensure a valid comment is extracted
if [[ -z "$COMMENT" ]]; then
  echo "No comment found in solution.cpp. Exiting."
  exit 1
fi

# Split the comment into words
FIRST_WORD=$(echo "$COMMENT" | awk '{print $1}')
SECOND_WORD=$(echo "$COMMENT" | awk '{print $2}')

# Ensure valid words are extracted
if [[ -z "$FIRST_WORD" || -z "$SECOND_WORD" ]]; then
  echo "Invalid comment format in solution.cpp. Exiting."
  exit 1
fi

# Check if FIRST_WORD matches any folder name in CODE_TRAVEL_DIR
TARGET_DIR="$CODE_TRAVEL_DIR/$FIRST_WORD"
if [[ ! -d "$TARGET_DIR" ]]; then
  TARGET_DIR="$CODE_TRAVEL_DIR/unspecified"
fi

# Replace spaces with underscores in the second word for the filename
FILE_NAME="${SECOND_WORD// /_}.cpp"

# Full path of the new file
NEW_FILE_PATH="$TARGET_DIR/$FILE_NAME"

# Create the file in the appropriate directory
cp solution.cpp "$NEW_FILE_PATH"

cd ..

# Add the new file to git
git add "."
git commit -m "Added $FILE_NAME from solution.cpp to $FIRST_WORD folder"
git push origin main
