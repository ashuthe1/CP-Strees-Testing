#include <bits/stdc++.h>
using namespace std;

const int maxN = 300;
const int maxV = 1e9;
string generate_test() {
    int n = rand()%maxN + 1;
    // int k = rand()%n;
    // if(k == 0) k++;
    if(n < 3) n = 10;
    stringstream ss;
    ss << n << "\n";
    // ss << "1";
    for(int i = 0; i < n; i++) {
        int cur = rand()%maxV + 1;
        ss << cur;
        if(i != n-1) ss << " ";
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