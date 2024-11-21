#include <bits/stdc++.h>
using namespace std;

// Function to trim whitespace from both ends of a string
string trim(const string &str) {
    size_t first = str.find_first_not_of(" \n\r\t");
    size_t last = str.find_last_not_of(" \n\r\t");
    return (first == string::npos || last == string::npos) ? "" : str.substr(first, (last - first + 1));
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Usage: ./validator <input_file> <output_file>\n";
        return 1;
    }

    // Open input file and read x
    ifstream input_file(argv[1]);
    if (!input_file.is_open()) {
        cerr << "Failed to open input file: " << argv[1] << endl;
        return 1;
    }
    
    int x;
    input_file >> x;  // Read the target sum
    input_file.close();

    // Open output file and validate the solution output
    ifstream output_file(argv[2]);
    if (!output_file.is_open()) {
        cerr << "Failed to open output file: " << argv[2] << endl;
        return 1;
    }

    int noOfNumbers;
    output_file >> noOfNumbers;  // Read the number of numbers provided
    if (noOfNumbers <= 0) {
        cout << "Invalid: Number of values should be positive\n";
        return 1;
    }

    vector<int> numbers;
    int sum = 0;

    for (int i = 0; i < noOfNumbers; i++) {
        int num;
        if (!(output_file >> num)) {  // Read each number
            cout << "Invalid: Insufficient numbers provided\n";
            return 1;
        }
        numbers.push_back(num);
        sum += num;
    }

    // Check if sum matches x
    if (sum != x) {
        cout << "Invalid: Sum mismatch. Expected sum " << x << ", got " << sum << "\n";
        return 1;
    }

    // // Check for extra output beyond the expected numbers
    // string remaining;
    // if (getline(output_file, remaining) && !trim(remaining).empty()) {
    //     cout << "Invalid: Extra output found after expected numbers\n";
    //     return 1;
    // }

    cout << "Valid\n";  // Output is valid if all checks pass
    return 0;
}
