#include <bits/stdc++.h>
using namespace std;

// Function to generate a random tree using Prüfer sequence
vector<pair<int, int>> generate_random_tree(int n) {
    vector<int> prufer_sequence(n - 2);
    for (int i = 0; i < n - 2; ++i) {
        prufer_sequence[i] = rand() % n + 1;
    }

    vector<int> degree(n + 1, 1);
    for (int node : prufer_sequence) {
        ++degree[node];
    }

    set<int> leaves;
    for (int i = 1; i <= n; ++i) {
        if (degree[i] == 1) {
            leaves.insert(i);
        }
    }

    vector<pair<int, int>> edges;
    for (int node : prufer_sequence) {
        int leaf = *leaves.begin();
        leaves.erase(leaves.begin());

        edges.emplace_back(leaf, node);

        if (--degree[node] == 1) {
            leaves.insert(node);
        }
    }

    // Connect the last two nodes
    int u = *leaves.begin();
    leaves.erase(leaves.begin());
    int v = *leaves.begin();
    edges.emplace_back(u, v);

    return edges;
}

string generate_test() {
    const int MAX_N = 25; // Maximum number of nodes
    const int T = 1;      // Fixed number of test cases

    stringstream ss;

    // Output T
    ss << T << "\n";

    // Generate test case
    for (int t = 0; t < T; ++t) {
        // Randomize N (1 ≤ N ≤ MAX_N)
        int n = rand() % MAX_N + 2;

        // Randomize K (1 ≤ K ≤ N)
        int k = rand() % n + 1;

        ss << n << " " << k << "\n";

        // Generate random tree
        vector<pair<int, int>> edges = generate_random_tree(n);

        for (const auto& edge : edges) {
            ss << edge.first << " " << edge.second << "\n";
        }
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
