#include <bits/stdc++.h>
using namespace std;

const int N = 25;
string generate_test() {
    int n = rand() % 20 + 1;  // Number of integers between 1 and 100
    int q = rand() % 12 + 1;

    stringstream ss;
    ss << n << " " << q << "\n";
    for(int i = 0; i < n; i++) {
        int x = rand() % N + 1;
        ss << x;
        if(i < n-1) ss << " ";
    }
    ss << "\n";
    for(int i = 0; i < q; i++) {
        int t = rand()%2 + 1, l = rand()%n + 1, r = rand()%n + 1;
        if(l > r) swap(l, r);
        ss << t << " " << l << " " << r << "\n";
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