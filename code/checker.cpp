#include <bits/stdc++.h>
using namespace std;

// Function to trim whitespace from both ends of a string
string trim(const string &str) {
    size_t first = str.find_first_not_of(" \n\r\t");
    size_t last = str.find_last_not_of(" \n\r\t");
    return (first == string::npos || last == string::npos) ? "" : str.substr(first, (last - first + 1));
}

void compare_files(const string &file1, const string &file2) {
    ifstream f1(file1), f2(file2);
    
    // Check if the files opened successfully
    if (!f1.is_open()) {
        cerr << "Failed to open actual output file: " << file1 << endl;
        return;
    }
    
    if (!f2.is_open()) {
        cerr << "Failed to open expected output file: " << file2 << endl;
        return;
    }

    string line1, line2;
    int line_number = 0;
    bool files_are_identical = true;

    while (getline(f1, line1) && getline(f2, line2)) {
        line_number++;
        if (trim(line1) != trim(line2)) {  // Compare trimmed lines
            files_are_identical = false;
            cout << "Mismatch at line " << line_number << ":\n";
            cout << "Expected: " << trim(line2) << "\n";
            cout << "Actual:   " << trim(line1) << "\n";
        }
    }

    if (files_are_identical) {
        cout << "Match\n";
    } else {
        cout << "Mismatch\n";
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Usage: ./checker <actual_output> <expected_output>\n";
        return 1;
    }
    
    compare_files(argv[1], argv[2]);
    return 0;
}
