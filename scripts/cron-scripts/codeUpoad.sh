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

# Extract possible folder name from the URL (e.g., "codeforces" from "https://codeforces.com")
POSSIBLE_FOLDER=$(echo "$PATH_VALUE" | awk -F'/' '{print $3}' | awk -F'.' '{print $1}')

# Check if POSSIBLE_FOLDER matches any folder name in CODE_TRAVEL_DIR
TARGET_DIR="$CODE_TRAVEL_DIR/$POSSIBLE_FOLDER"
if [[ ! -d "$TARGET_DIR" ]]; then
  TARGET_DIR="$CODE_TRAVEL_DIR/unspecified"
fi

# Extract the path after the domain
RELATIVE_PATH=$(echo "$PATH_VALUE" | sed -E 's|https?://[^/]+/||')

# Replace `/` with `-` in the remaining path to create a simplified folder name
FOLDER_NAME=$(echo "$RELATIVE_PATH" | sed 's|/|-|g')

# Extract the file name:
# - Use the last segment (after the last `/`), or if empty, use the segment before that
LAST_SEGMENT=$(echo "$RELATIVE_PATH" | awk -F'/' '{print $NF}')
if [[ -z "$LAST_SEGMENT" ]]; then
  LAST_SEGMENT=$(echo "$RELATIVE_PATH" | awk -F'/' '{print $(NF-1)}')
fi

# Replace spaces with underscores in the file name
FILE_NAME="${LAST_SEGMENT// /_}.cpp"

# Create the folder inside the target directory
FINAL_FOLDER="$TARGET_DIR/$FOLDER_NAME"
mkdir -p "$FINAL_FOLDER"

# Full path of the new file
NEW_FILE_PATH="$FINAL_FOLDER/$FILE_NAME"

# Copy the file to the target directory and subfolder
cp solution.cpp "$NEW_FILE_PATH"

cd ..

# Add the new file to git
git add "."
git commit -m "Added $FILE_NAME from solution.cpp to $POSSIBLE_FOLDER/$FOLDER_NAME folder"
git push origin main
