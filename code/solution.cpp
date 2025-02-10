// Ashutosh Gautam
#include <bits/stdc++.h>
using namespace std;

#ifdef AshutoshOS // It works on my machine.
#include "../algo/debug.hpp" 
#else
#define deb(...)
#endif

#define int long long
const int N = 1e6+10;
const int INF = 1e16;
const int MOD = 1e9+7;

int n, m;
vector<int> a, b;
vector<vector<int>> dp;
void init(int n, int m) {
    a.clear();
    b.clear();
    a.resize(n);
    b.resize(m);
    dp.clear();
    dp.resize(n, vector<int>(2, -1));
}

// prevState = 0 --> no changes in a[idx] otherwise a[idx-1] = b[j] - a[idx-1]
bool func(int idx, int prevState) {
    if(idx == n) return true;
    if(dp[idx][prevState] != -1) return dp[idx][prevState];
    int ans = false;

    if(prevState) {
        if((idx == 0) || a[idx] >= b[0] - a[idx-1]) ans |= func(idx+1, 0);
        if((idx == 0) ||b[0] - a[idx] >= b[0] - a[idx-1]) ans |= func(idx+1, 1);
    } else {
        if((idx == 0) || a[idx] >= a[idx-1]) ans |= func(idx+1, 0);
        if((idx == 0) || b[0] - a[idx] >= a[idx-1]) ans |= func(idx+1, 1);
    }

    return dp[idx][prevState] = ans;
}
void AshutoshGautam() {
    cin >> n >> m;
    init(n, m);
    for(int &e: a) cin >> e;
    for(int &e: b) cin >> e;

    sort(b.begin(), b.end());
    a[0] = min(a[0], b[0] - a[0]);

    for(int i = 1; i < n; i++) {
        int lo = 0, hi = m-1, idx = -1;
        int ans = INT_MAX;
        while(lo <= hi) {
            int mid = (lo + hi) / 2;
            if(b[mid] - a[i] >= a[i-1]) ans = min(ans, b[mid] - a[i]), hi = mid - 1;
            else lo = mid + 1;
        }
        
        deb(a[i-1], a[i], ans)
        if(a[i] >= a[i-1] && ans != INT_MAX) a[i] = min(a[i], ans);
        else if(a[i] >= a[i-1]);
        else if(ans != INT_MAX) a[i] = ans;

        if(a[i] < a[i-1]) {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int testCases = 1;
    // cin >> testCases; 

    for(int testCase = 1; testCase <= testCases ; testCase++)  
        AshutoshGautam(); // Ping me for solving any issue
    return 0;
}