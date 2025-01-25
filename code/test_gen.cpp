#include <bits/stdc++.h>
using namespace std;

const int maxN = 100;
string generate_test() {
    int n = rand()%maxN + 1;  // Number of integers between 1 and 100
    // int k = rand()%n;
    // if(k == 0) k++;
    stringstream ss;
    // ss << n << " " << k << "\n";
    ss << "1";
    for(int i = 1; i < n; i++) {
        int cur = rand()%2;
        ss << cur;
        // if(i != n-1) ss << " ";
    }
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