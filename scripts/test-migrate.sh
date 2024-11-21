#!/bin/bash

# Define the source directories and the target history directory
LOGS_DIR="../logs"
TESTS_DIR="../tests"
MIGRATION_DIR="../migrations/stress-tests"
CODE_FILE="../code/solution.cpp"

# Define color codes for terminal output
CYAN='\033[0;36m'
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'  # No Color

# Function to display help
show_help() {
    echo "Usage: ./migrate.sh [--clear]"
    echo "Options:"
    echo "  --clear    Clear all contents of the history folder before migration"
}

# Check for the --clear flag
if [[ "$1" == "--clear" ]]; then
    echo -e "Clearing contents of the history folder..."
    rm -rf "${MIGRATION_DIR}/"
    echo -e "Cleanup complete."
fi

# Create a timestamped migration directory
timestamp=$(date +"%Y%m%d_%H%M%S")
migration_dir="$MIGRATION_DIR/migration_$timestamp"
mkdir -p "$migration_dir"


cp "$CODE_FILE" "$migration_dir/" 2>/dev/null

# Copy logs to the migration directory
echo -e "Migrating logs..."
cp -r "$LOGS_DIR/"* "$migration_dir/" 2>/dev/null
echo -e "${GREEN}Logs migrated to $migration_dir.${NC}"

# Copy tests to the migration directory
echo -e "Migrating tests..."
cp -r "$TESTS_DIR/"* "$migration_dir/" 2>/dev/null
echo -e "${GREEN}Tests migrated to $migration_dir.${NC}"

# Show completion message
echo -e "Migration completed!"
