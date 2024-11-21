#!/bin/bash

# Set your paths
SRC_DIR="/home/ashuthe1/cp/code"
CODE_TRAVEL_DIR="/home/ashuthe1/cp/migrations/codes"
REPO_DIR="/home/ashuthe1/cp"  # Path to the root of the Local Git repository

# Navigate to the source directory
cd "$SRC_DIR" || exit 1

# Extract the second line from solution.cpp
SECOND_LINE=$(sed -n '2p' solution.cpp)

# Ensure a valid second line is extracted
if [[ -z "$SECOND_LINE" ]]; then
  echo "No second line found in solution.cpp. Exiting."
  exit 1
fi

# Extract the value after "tag:" in the second line
TAG_VALUE=$(echo "$SECOND_LINE" | sed -n 's/.*tag: *\([^ ]*\).*/\1/p')

# Ensure a valid tag value is extracted
if [[ -z "$TAG_VALUE" ]]; then
  echo "No valid tag value found in the second line. Exiting."
  exit 1
fi

# Debugging: Print the extracted tag value
echo "Extracted tag value: '$TAG_VALUE'"

# Step 1: Extract the second word (e.g., 'dp')
SECOND_WORD=$(echo "$TAG_VALUE" | awk -F'/' '{print $2}')

# Ensure the second word is non-empty
if [[ -z "$SECOND_WORD" ]]; then
  echo "Second word could not be extracted. Exiting."
  exit 1
fi

# Step 2: Extract the last word before the final '/'
LAST_WORD=$(echo "$TAG_VALUE" | awk -F'/' '{print $NF}')

# Ensure the last word is non-empty
if [[ -z "$LAST_WORD" ]]; then
  echo "Last word could not be extracted. Exiting."
  exit 1
fi

# Step 3: Combine second word and last word for the file name
FILE_NAME="${SECOND_WORD}_${LAST_WORD}.cpp"

# Debugging: Print the extracted file name
echo "Extracted file name: '$FILE_NAME'"

# Step 4: Extract the subfolder structure by removing the last segment
SUBFOLDER_PATH=$(echo "$TAG_VALUE" | sed "s|/$LAST_WORD$||")

# Debugging: Print the subfolder path
echo "Subfolder path: '$SUBFOLDER_PATH'"

# Step 5: Replace slashes with dashes for the folder name
FOLDER_NAME=$(echo "$SUBFOLDER_PATH" | sed 's|/|-|g')

# Debugging: Print the folder name
echo "Final folder name (slashes replaced with dashes): '$FOLDER_NAME'"

# Step 6: Check if the folder exists in the CODE_TRAVEL_DIR
TARGET_DIR="$CODE_TRAVEL_DIR"
if [[ ! -d "$TARGET_DIR" ]]; then
  echo "Target directory '$TARGET_DIR' not found. Exiting."
  exit 1
fi

# Step 7: Create the folder structure and the file path
FINAL_FOLDER="$TARGET_DIR/$FOLDER_NAME"
mkdir -p "$FINAL_FOLDER"

# Debugging: Print the final folder path
echo "Final folder path: '$FINAL_FOLDER'"

# Full path for the new file
NEW_FILE_PATH="$FINAL_FOLDER/$FILE_NAME"

# Debugging: Print the final file path
echo "Final file path: '$NEW_FILE_PATH'"

# Step 8: Copy the solution.cpp to the new file location
cp solution.cpp "$NEW_FILE_PATH"

# Navigate back to the repository directory
cd "$REPO_DIR" || exit 1

# Step 9: Add the new file to git and commit the changes
git add "."
git commit -m "Added $FILE_NAME from solution.cpp to $FOLDER_NAME folder"
git push origin main
