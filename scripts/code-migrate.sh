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

# Step 1: Extract the last word after the last '/'
FILE_NAME=$(echo "$TAG_VALUE" | awk -F'/' '{print $NF}')

# Ensure the file name is non-empty
if [[ -z "$FILE_NAME" ]]; then
  echo "File name could not be extracted. Exiting."
  exit 1
fi

# Debugging: Print the extracted file name
echo "Extracted file name: '$FILE_NAME'"

# Step 2: Extract the folder structure (everything before the last '/')
FOLDER_STRUCTURE=$(echo "$TAG_VALUE" | sed "s|/$FILE_NAME||")

# Debugging: Print the folder structure
echo "Folder structure: '$FOLDER_STRUCTURE'"

# Step 3: Create the nested folder structure inside the target directory
FINAL_FOLDER="$CODE_TRAVEL_DIR/$FOLDER_STRUCTURE"
mkdir -p "$FINAL_FOLDER"

# Debugging: Print the final folder path
echo "Final folder path: '$FINAL_FOLDER'"

# Add `.cpp` to the file name
FILE_NAME="${FILE_NAME}.cpp"

# Full path for the new file
NEW_FILE_PATH="$FINAL_FOLDER/$FILE_NAME"

# Debugging: Print the final file path
echo "Final file path: '$NEW_FILE_PATH'"

# Step 4: Copy the solution.cpp to the new file location
cp solution.cpp "$NEW_FILE_PATH"

# Navigate back to the repository directory
cd "$REPO_DIR" || exit 1

# Step 5: Add the new file to git and commit the changes
git add "."
git commit -m "Added $FILE_NAME from solution.cpp to $FOLDER_STRUCTURE folder"
git push origin main
