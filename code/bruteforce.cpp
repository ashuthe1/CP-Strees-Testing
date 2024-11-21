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
void AshutoshGautam() {
    int l, r, ans = 0; cin >> l >> r;
    for(int num = l; num <= r; num++) {
        string s = decToBinary(num);
        set<int> st;
        int cnt = 1;
        char prev = s[0];
        s += '&';
        for(int i = 1; i <= n; i++) {
            if(s[i] != prev) {
                mp[cnt]++;
                cnt = 1;
            } else cnt++;
        }
        if(st.size() == 1) ans++;
    }
    cout << ans << "\n";
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int testCases = 1;
    // cin >> testCases; 

    for(int testCase = 1; testCase <= testCases ; testCase++)  
        AshutoshGautam(); // Ping me for solving any issue ツ
    return 0;
}