#!/bin/bash

# Set your paths
SRC_DIR="../../src"
CODE_TRAVEL_DIR="../codeTravel"
REPO_DIR="../../"  # Path to the root of the Local Git repository

# Navigate to the source directory
cd "$SRC_DIR" || exit 1

# Extract the second line from solution.cpp
SECOND_LINE=$(sed -n '2p' solution.cpp)

# Print the second line for debugging
echo "Extracted second line: '$SECOND_LINE'"

# Ensure a valid second line is extracted
if [[ -z "$SECOND_LINE" ]]; then
  echo "No second line found in solution.cpp. Exiting."
  exit 1
fi

# Extract the value after "path:" in the second line
PATH_VALUE=$(echo "$SECOND_LINE" | sed -n 's/.*path: *\([^ ]*\).*/\1/p')

# Print the extracted path value for debugging
echo "Extracted path value: '$PATH_VALUE'"

# Ensure a valid path value is extracted
if [[ -z "$PATH_VALUE" ]]; then
  echo "No valid path value found in the second line. Exiting."
  exit 1
fi

# Step 1: Extract the file name (last segment of the path, after the last "/")
FILE_NAME=$(echo "$PATH_VALUE" | awk -F'/' '{print $NF}')

# Print the extracted file name for debugging
echo "Extracted file name: '$FILE_NAME'"

# Ensure the file name is non-empty
if [[ -z "$FILE_NAME" ]]; then
  FILE_NAME="default"
  echo "File name was empty. Defaulting to 'default.cpp'."
fi

# Step 2: Remove the file name from the URL to get the folder path
# The remaining path is the part before the file name
RELATIVE_PATH=$(echo "$PATH_VALUE" | sed -E 's|https?://[^/]+/||')

# Print the relative path for debugging
echo "Relative path (without domain): '$RELATIVE_PATH'"

# Step 3: Remove the file name from the relative path to get the subfolder path
# We are now removing the part of the URL that corresponds to the file name, so we don't keep it
SUBFOLDER_PATH=$(echo "$RELATIVE_PATH" | sed "s|/$TEMP_FILE_NAME$||")

# Replace spaces with underscores in the file name
FILE_NAME="${FILE_NAME// /_}.cpp"

# Print the folder path (before converting slashes to dashes) for debugging
echo "Subfolder path (without file name): '$SUBFOLDER_PATH'"

# Step 4: Replace slashes with dashes for the folder name
FOLDER_NAME=$(echo "$SUBFOLDER_PATH" | sed 's|/|-|g')

# Print the final folder name for debugging
echo "Final folder name (slashes replaced with dashes): '$FOLDER_NAME'"

# Step 5: Extract the main folder (e.g., "codeforces", "cses", etc.) from the URL
POSSIBLE_FOLDER=$(echo "$PATH_VALUE" | awk -F'/' '{print $3}' | awk -F'.' '{print $1}')

# Print the possible folder for debugging
echo "Possible folder (main directory): '$POSSIBLE_FOLDER'"

# Step 6: Check if the folder exists in the CODE_TRAVEL_DIR
TARGET_DIR="$CODE_TRAVEL_DIR/$POSSIBLE_FOLDER"
if [[ ! -d "$TARGET_DIR" ]]; then
  TARGET_DIR="$CODE_TRAVEL_DIR/unspecified"
  echo "Folder '$POSSIBLE_FOLDER' not found. Using 'unspecified' folder."
fi

# Print the target directory for debugging
echo "Target directory: '$TARGET_DIR'"

# Step 7: Create the folder structure and the file path
FINAL_FOLDER="$TARGET_DIR/$FOLDER_NAME"
mkdir -p "$FINAL_FOLDER"

# Print the final folder path for debugging
echo "Final folder path: '$FINAL_FOLDER'"

# Full path for the new file
NEW_FILE_PATH="$FINAL_FOLDER/$FILE_NAME"

# Print the final file path for debugging
echo "Final file path: '$NEW_FILE_PATH'"

# Step 8: Copy the solution.cpp to the new file location
cp solution.cpp "$NEW_FILE_PATH"

# Navigate back to the repository directory
cd ..

# Step 9: Add the new file to git and commit the changes
git add "."
git commit -m "Added $FILE_NAME from solution.cpp to $POSSIBLE_FOLDER/$FOLDER_NAME folder"
git push origin main
