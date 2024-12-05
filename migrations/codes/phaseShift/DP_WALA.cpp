// Ashutosh Gautam
// tag: phaseShift/DP_WALA
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


int mul(int a, int b) {
    return ((a % MOD) * (b % MOD)) % MOD;
}
int add(int a, int b) {
    return ((a % MOD) + (b % MOD)) % MOD;
}
int sub(int a, int b) {
    return (a % MOD - b % MOD + MOD) % MOD;
}
int maxI, n, h;
int func(int idx, int prevCnt, int val) {
    if(idx == h) return 1;
    if(val > maxI) return 0;

    int ans = 0;
    if(prevCnt+1 <= n) ans = add(ans, func(idx+1, prevCnt+1, val));
    ans = add(ans, func(idx+1, 1, val+1));

    return ans;
}   
void AshutoshGautam() {
    cin >> maxI >> n >> h; 
    cout << func(0, 0, 1) << "\n";
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int testCases = 1;
    // cin >> testCases; 

    for(int testCase = 1; testCase <= testCases ; testCase++)  
        AshutoshGautam(); // Ping me for solving any issue
    return 0;
}