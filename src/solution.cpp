// Ashutosh Gautam ツ
#include <bits/stdc++.h>
using namespace std;

#ifdef AshutoshOS // It works on my machine.
#include "../algo/debug.hpp" 
#else
#define deb(...)
#endif

#define int long long
const int N = 1e6+10;

void AshutoshGautam() {
    int n;
    cin >> n;
    int max_val = INT_MIN, min_val = INT_MAX;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        max_val = max(max_val, x);
        if(i < n-1) min_val = min(min_val, x);
    }
    cout << max_val << endl;
    cout << min_val<< endl;
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int testCases = 1;
    // cin >> testCases; 

    for(int testCase = 1; testCase <= testCases ; testCase++)  
        AshutoshGautam(); // Ping me for solving any issue ツ
    return 0;
}