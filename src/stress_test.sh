#!/bin/bash

# Compile all necessary programs with error checking
g++ solution.cpp -o solution || { echo "Failed to compile solution.cpp"; exit 1; }
g++ naive.cpp -o naive || { echo "Failed to compile naive.cpp"; exit 1; }
g++ test_gen.cpp -o test_gen || { echo "Failed to compile test_gen.cpp"; exit 1; }
g++ checker.cpp -o checker || { echo "Failed to compile checker.cpp"; exit 1; }

# Generate test cases
./test_gen || { echo "Failed to generate test cases"; exit 1; }

# Create logs directory and subdirectories for checker logs and test logs if they don't exist
mkdir -p ../logs/checker_logs
mkdir -p ../logs/test_logs

# Define color codes for terminal output
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'  # No Color

# Run stress tests
for input in ../tests/input/*.txt; do
    test_name=$(basename "$input" .txt)
    actual_output="../tests/actual_output/${test_name}_actual.txt"
    expected_output="../tests/expected_output/${test_name}_expected.txt"
    log_file="../logs/test_logs/${test_name}_log.txt"         # Updated log file location
    checker_log="../logs/checker_logs/${test_name}_checker_log.txt"  # Updated checker log location

    # Truncate the log files at the start of each test run
    > "$log_file"
    > "$checker_log"

    # Generate expected output using naive solution
    ./naive < "$input" > "$expected_output" || { echo "Failed to generate expected output"; exit 1; }

    # Run solution and save actual output
    ./solution < "$input" > "$actual_output" || { echo "Failed to generate actual output"; exit 1; }

    # Debug: Print output lengths and contents for comparison
    echo "Debug Info for Test $test_name:"
    echo "Expected Output:"
    cat "$expected_output"
    echo "Actual Output:"
    cat "$actual_output"
    echo ""

    # Compare outputs and log details
    if ./checker "$actual_output" "$expected_output" | tee -a "$checker_log" | grep -q "Mismatch"; then
        # Log details for a failing test case
        echo "Test $test_name: FAILED" >> "$log_file"
        echo "Input:" >> "$log_file"
        cat "$input" >> "$log_file"
        echo -e "\nExpected Output:" >> "$log_file"
        cat "$expected_output" >> "$log_file"
        echo -e "\nActual Output:" >> "$log_file"
        cat "$actual_output" >> "$log_file"

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

        # Show "Passed" status in green
        echo -e "Test $test_name: ${GREEN}Passed${NC}"
    fi
done
