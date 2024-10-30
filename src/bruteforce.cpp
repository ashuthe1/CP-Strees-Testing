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

int n;
void AshutoshGautam() {
    int q; cin >> n;
    vector<int> v(n+1, 0), b;
    for(int i = 1; i <= n; i++) {
        cin >> v[i];
    }
    b.push_back(0);
    for(int i = 1; i <= n; i++) {
        int curSum = 0;
        for(int j = i; j <= n; j++) {
            curSum += v[j];
            b.push_back(curSum);
        }
    }
    cin >> q;
    while(q--) {
        int l, r; cin >> l >> r;
        int ans = 0;
        for(int i = l; i <= r; i++) ans += b[i];
        cout << ans << "\n";
    }
}
signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int testCases = 1;
    // cin >> testCases; 

    for(int testCase = 1; testCase <= testCases ; testCase++)  
        AshutoshGautam(); // Ping me for solving any issue ツ
    return 0;
}