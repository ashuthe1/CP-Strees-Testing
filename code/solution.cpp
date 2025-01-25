// Ashutosh Gautam
#include <bits/stdc++.h>
using namespace std;

#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template<class T> using IndexedSet = tree<T, null_type,less_equal<T>,rb_tree_tag,tree_order_statistics_node_update>;
// st.find_by_order(k)  returns iterator to kth element starting from 0;
// st.order_of_key(k) returns count of elements strictly smaller than k;

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
    int x, y; cin >> x >> y;
    int sum = x + y;
    // if(sum < 100) sum++;
    cout << sum << "\n";
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int testCases = 1;
    // cin >> testCases; 

    for(int testCase = 1; testCase <= testCases ; testCase++)  
        AshutoshGautam(); // Ping me for solving any issue
    return 0;
}