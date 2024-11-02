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

void AshutoshGautam() {
    int n, m, k; cin >> n >> m >> k;
    vector<int> relOrder(m), ans(n+1, n+1);
    int heheCow = n+1;
    map<int, int> fixed;
    int cowHasPreference = false;
    for(int i = 0; i < m; i++) {
        cin >> relOrder[i];
        if(relOrder[i] == 1) {
            cowHasPreference = i;
        }
    }
    for(int i = 0; i < k; i++) {
        int c, p; cin >> c >> p;
        if(c == 1) {
            heheCow = p;
        }
        ans[p] = c;
        fixed[c] = p;
    }

    if(heheCow != n+1) {
        cout << heheCow << "\n";
        return;
    }

    if(cowHasPreference) {
        if(relOrder[0] == 1) {
            for(int i = 1; i <= n; i++) {
                if(ans[i] == n+1) {
                    cout << i << "\n";
                    return;
                }
            }
        }

        int l = 1, i = 0;
        for(i = cowHasPreference-1; i >= 0; i--) {
            if(fixed.find(relOrder[i]) != fixed.end()) {
                l = fixed[relOrder[i]];
                l++, i++;
                break;
            }
        }

        while(l <= n && i <= cowHasPreference) {
            if(ans[l] != n+1) l++;
            else {
                ans[l] = relOrder[i];
                l++, i++;
            }
        }

        cout << ans[1] << "\n";
        return;
    }

    deb(ans, fixed);
    deb("Yaha")

    int pos = n, i = m-1;
    while(pos >= 1 && i >= 0) {
        deb(i, relOrder[i], pos)
        if(fixed.find(relOrder[i]) != fixed.end()) {
            pos = fixed[relOrder[i]];
            ans[pos] = relOrder[i];
            deb(pos)
            pos--, i--;
        } else {
            if(ans[pos] != n+1) pos--;
            else {
                deb(relOrder[i], pos)
                ans[pos] = relOrder[i];
                pos--, i--;
            }
        }
    }

    deb(ans);

    for(int i = 1; i <= n; i++) {
        if(ans[i] == n+1) {
            cout << i << "\n";
            return;
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int testCases = 1;
    // freopen("milkorder.in", "r", stdin);
    // freopen("milkorder.out", "w", stdout);
    // cin >> testCases; 

    for(int testCase = 1; testCase <= testCases ; testCase++)  
        AshutoshGautam(); // Ping me for solving any issue ツ
    return 0;
}