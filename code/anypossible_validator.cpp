#include <bits/stdc++.h>
using namespace std;

string xorOfString(string s, string x) {
    int n = s.size(), m = x.size();
    string ans = "";
    int dif = n - m, i = 0;
    while(i < dif) {
        ans += s[i];
        i++;
    }

    for( ; i < n; i++) {
        if(s[i] != x[i - dif]) ans += '1';
        else ans += '0';
    }

    return ans;
}

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
    
    string s; input_file >> s;

    int n = s.size(), len;
    vector<pair<string, pair<int, int>>> v;
    for(int i = 0; i < n; i++) {
        string cur = "";
        for(int j = i; j < n; j++) {
            cur += s[j];
            v.push_back({cur, {i+1, j+1}});
        }
    }

    string maxXor = "";
    // int l = 1, r = 1;
    len = v.size();
    for(int i = 0; i < len; i++) {
        string curXor = xorOfString(s, v[i].first);
        if(curXor > maxXor) {
            maxXor = curXor;
            // l = v[i].second.first;
            // r = v[i].second.second;
        }
    }
    // int x;
    // input_file >> x;  // Read the target sum
    input_file.close();

    // Open output file and validate the solution output
    ifstream output_file(argv[2]);
    if (!output_file.is_open()) {
        cerr << "Failed to open output file: " << argv[2] << endl;
        return 1;
    }

    int l1, r1, l, r;
    output_file >> l1 >> r1 >> l >> r;

    string cur = "";
    cur = s.substr(l-1, r - l + 1);

    string curXor = xorOfString(s, cur);
    if(curXor != maxXor) {
        cout << "Wrong Aswer\n";
        cout << "Exp: " << maxXor << "\n";
        cout << "Got: " << curXor << "\n";
        return 1;
    }

    cout << "Valid\n";  // Output is valid if all checks pass
    return 0;
}
