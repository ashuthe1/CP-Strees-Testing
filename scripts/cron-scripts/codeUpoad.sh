#!/bin/bash

# Set your paths
SRC_DIR="../../src"
CODE_TRAVEL_DIR="../codeTravel"
REPO_DIR="../../"  # Path to the root of the Local Git repository

# Navigate to the source directory
cd "$SRC_DIR" || exit 1

# Extract the second line from solution.cpp
SECOND_LINE=$(sed -n '2p' solution.cpp)

# Ensure a valid second line is extracted
if [[ -z "$SECOND_LINE" ]]; then
  echo "No second line found in solution.cpp. Exiting."
  exit 1
fi

# Extract the value after "path:" in the second line
PATH_VALUE=$(echo "$SECOND_LINE" | sed -n 's/.*path: *\([^ ]*\).*/\1/p')

# Ensure a valid path value is extracted
if [[ -z "$PATH_VALUE" ]]; then
  echo "No valid path value found in the second line. Exiting."
  exit 1
fi

# Split the path value into directory name and file name based on '/'
DIR_NAME=$(echo "$PATH_VALUE" | cut -d'/' -f1)
FILE_NAME=$(echo "$PATH_VALUE" | cut -d'/' -f2)

# Ensure both directory name and file name are valid
if [[ -z "$DIR_NAME" || -z "$FILE_NAME" ]]; then
  echo "Invalid path value in solution.cpp. Exiting."
  exit 1
fi

# Check if DIR_NAME matches any folder name in CODE_TRAVEL_DIR
TARGET_DIR="$CODE_TRAVEL_DIR/$DIR_NAME"
if [[ ! -d "$TARGET_DIR" ]]; then
  TARGET_DIR="$CODE_TRAVEL_DIR/unspecified"
fi

# Replace spaces with underscores in the file name
FILE_NAME="${FILE_NAME// /_}.cpp"

# Full path of the new file
NEW_FILE_PATH="$TARGET_DIR/$FILE_NAME"

# Create the file in the appropriate directory
cp solution.cpp "$NEW_FILE_PATH"

cd ..

# Add the new file to git
git add "."
git commit -m "Added $FILE_NAME from solution.cpp to $DIR_NAME folder"
git push origin main
