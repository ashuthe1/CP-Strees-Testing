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
void AshutoshGautam() {
    string s; cin >> s;
    int n = s.size();
    vector<pair<string, pair<int, int>>> v;
    for(int i = 0; i < n; i++) {
        string cur = "";
        for(int j = i; j < n; j++) {
            cur += s[j];
            v.push_back({cur, {i+1, j+1}});
        }
    }

    string maxXor = "";
    int l = 1, r = 1;
    int len = v.size();
    for(int i = 0; i < len; i++) {
        string curXor = xorOfString(s, v[i].first);
        if(curXor > maxXor) {
            deb(curXor, maxXor)
            maxXor = curXor;
            l = v[i].second.first;
            r = v[i].second.second;
        }
    }
    deb(maxXor)
    cout << "1 " << n << " " << l << " " << r << "\n";
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int testCases = 1;
    // cin >> testCases; 

    for(int testCase = 1; testCase <= testCases ; testCase++)  
        AshutoshGautam(); // Ping me for solving any issue
    return 0;
}