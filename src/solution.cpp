#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    int max_val = INT_MIN, min_val = INT_MAX;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        max_val = max(max_val, x);
        min_val = min(min_val, x);
    }
    cout << max_val << endl;
    cout << min_val << endl;
    return 0;
}
