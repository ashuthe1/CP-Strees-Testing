#!/bin/bash

# Compile all necessary programs with error checking
g++ ../code/solution.cpp -o ../code/exec/solution || { echo "Failed to compile solution.cpp"; exit 1; }
g++ ../code/bruteforce.cpp -o ../code/exec/bruteforce || { echo "Failed to compile bruteforce.cpp"; exit 1; }
g++ ../code/test_gen.cpp -o ../code/exec/test_gen || { echo "Failed to compile test_gen.cpp"; exit 1; }
g++ ../code/checker.cpp -o ../code/exec/checker || { echo "Failed to compile checker.cpp"; exit 1; }

# Clean up previous logs and test files while preserving .gitkeep files
echo "Cleaning up previous logs and test files..."
find ../logs -type f ! -name '.gitkeep' -delete
find ../tests/input -type f ! -name '.gitkeep' -delete
find ../tests/actual_output -type f ! -name '.gitkeep' -delete
find ../tests/expected_output -type f ! -name '.gitkeep' -delete
echo "Cleanup complete."

# Default number of test cases
num_tests=${1:-10}  # Use the first argument if provided, otherwise default to 10

# Generate test cases
../code/exec/test_gen "$num_tests" || { echo "Failed to generate test cases"; exit 1; }

# Create logs directory and subdirectories for checker logs and test logs if they don't exist
mkdir -p ../logs/checker_logs
mkdir -p ../logs/test_logs

# Define color codes for terminal output
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'  # No Color

# Initialize counters
passed_tests=0
failed_tests=0

# Run stress tests
for input in ../tests/input/*.txt; do
    test_name=$(basename "$input" .txt)
    actual_output="../tests/actual_output/${test_name}_actual.txt"
    expected_output="../tests/expected_output/${test_name}_expected.txt"
    log_file="../logs/test_logs/${test_name}_log.txt"
    checker_log="../logs/checker_logs/${test_name}_checker_log.txt"

    # Truncate the log files at the start of each test run
    > "$log_file"
    > "$checker_log"

    # Generate expected output using bruteforce solution
    ../code/exec/bruteforce < "$input" > "$expected_output" || { echo "Failed to generate expected output"; exit 1; }

    # Run solution and save actual output
    ../code/exec/solution < "$input" > "$actual_output" || { echo "Failed to generate actual output"; exit 1; }

    # Compare outputs and log details
    if ../code/exec/checker "$actual_output" "$expected_output" | tee -a "$checker_log" | grep -q "Mismatch"; then
        # Log details for a failing test case
        echo "Test $test_name: FAILED" >> "$log_file"
        echo "Input:" >> "$log_file"
        cat "$input" >> "$log_file"
        echo -e "\nExpected Output:" >> "$log_file"
        cat "$expected_output" >> "$log_file"
        echo -e "\nActual Output:" >> "$log_file"
        cat "$actual_output" >> "$log_file"

        # Increment failed test counter
        ((failed_tests++))

        # Show "Failed" status in red
        echo -e "Test $test_name: ${RED}Failed${NC}"
    else
        # Log details for a passing test case
        echo "Test $test_name: PASSED" >> "$log_file"
        echo "Input:" >> "$log_file"
        cat "$input" >> "$log_file"
        echo -e "\nExpected Output:" >> "$log_file"
        cat "$expected_output" >> "$log_file"
        echo -e "\nActual Output:" >> "$log_file"
        cat "$actual_output" >> "$log_file"

        # Increment passed test counter
        ((passed_tests++))

        # Show "Passed" status in green
        echo -e "Test $test_name: ${GREEN}Passed${NC}"
    fi
done

# Display summary of results
total_tests=$((passed_tests + failed_tests))
if [ $failed_tests -gt 0 ]; then
    echo -e "\n${RED}$failed_tests tests failed out of $total_tests total tests.${NC}"
else
    echo -e "\n${GREEN}All test cases passed!${NC}"
fi
