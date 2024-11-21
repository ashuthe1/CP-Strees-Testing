#include <bits/stdc++.h>
using namespace std;

// Function to generate random test cases for the AshutoshGautam function
string generate_test() {
    int l = rand() % 1000000000 + 1; // Random l between 1 and 10^9
    int r = l + rand() % 1000;       // Random r between l and l + 1000 to keep the range small for performance

    stringstream ss;
    ss << l << " " << r << "\n";
    return ss.str();
}

int main(int argc, char* argv[]) {
    srand(time(0));

    // Default number of test cases
    int num_tests = 10;

    // Update num_tests if an argument is provided
    if (argc > 1) {
        num_tests = stoi(argv[1]);
    }

    // Generate the specified number of test cases
    for (int i = 0; i < num_tests; i++) {
        ofstream outfile("../tests/input/test_" + to_string(i) + ".txt");
        outfile << generate_test();
        outfile.close();
    }

    return 0;
}