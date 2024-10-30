#include <bits/stdc++.h>
using namespace std;

string generate_test() {
    int n = rand() % 100 + 1;  // Number of integers between 1 and 100
    stringstream ss;
    ss << n << "\n";
    for (int i = 0; i < n; i++) {
        ss << (rand() % 1000 + 1) << " ";  // Numbers between 1 and 1000
    }
    ss << "\n";
    return ss.str();
}

int main() {
    srand(time(0));
    for (int i = 0; i < 10; i++) {
        ofstream outfile("../tests/input/test_" + to_string(i) + ".txt");
        outfile << generate_test();
        outfile.close();
    }
    return 0;
}
