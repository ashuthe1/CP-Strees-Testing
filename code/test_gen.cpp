#include <bits/stdc++.h>
using namespace std;

string generate_test() {
    int n = rand() % 20 + 1;  // Number of integers between 1 and 100
    int m = rand() % n + 1;
    int k = rand() % n + 1;

    if(m >= n) m = n-1;
    if(k >= ) k = n-1;

    stringstream ss;
    ss << n << " " << m << " " << k << "\n";
    for(int i = 0; i < n; i++) {
        int x = rand() % 2;
        ss << x;
    }
    ss << "\n";
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