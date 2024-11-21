// Ashutosh Gautam ツ
// path: usaco/digit_dp
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

string decToBinary(int n)
{
    string ans = "";
    for (int i = 31; i >= 0; i--) {
        int k = n >> i;
        if (k & 1)
            ans += "1";
        else
            ans += "0";
    }
    string hehe = "";
    bool gotOne = false;
    for(auto &e: ans) {
        if(e == '1') gotOne = true;
        if(gotOne) hehe += e;
    }
    return hehe;
}

int dp[19][2][2][200];
int func(string& num, int idx, int tight, int leadingZero, int prevLen) {
    if (idx == num.size()) return prevLen == 1;
    
    // if (dp[idx][tight][leadingZero][prevLen] != -1) return ans;
    int ans = 0;
    int limit = tight ? num[idx] - '0' : 1;
    for (int digit = 0; digit <= limit; digit++) {
        int newLeadingZero = leadingZero && (digit == 0);
        int newLen = (prevLen == 0 || digit == num[idx] - '0') ? prevLen + 1 : 1;
        ans += func(num, idx + 1, tight && digit == num[idx] - '0', newLeadingZero, newLen);
    }

    // dp[idx][tight][leadingZero][prevLen] = ans;

    return ans;
}
void solve(string l, string r) {
    memset(dp, -1, sizeof(dp));
    int ans = func(r, 0, 1, 1, 0);
    memset(dp, -1, sizeof(dp));
    int extra = func(l, 0, 1, 1, 0);
    ans -= extra;
    cout << ans << "\n";
}
void AshutoshGautam() {
    int l, r; cin >> l >> r;
    string L = decToBinary(l), R = decToBinary(r);
    deb(l, L);
    deb(r, R)
    solve(L, R);
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int testCases = 1;
    cin >> testCases; 

    for(int testCase = 1; testCase <= testCases ; testCase++)  
        AshutoshGautam(); // Ping me for solving any issue ツ
    return 0;
}