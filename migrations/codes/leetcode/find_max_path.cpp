// Ashutosh Gautam ツ
// tag: leetcode/find_max_path
// link: https://leetcode.com/problems/network-recovery-pathways/description/
#include <bits/stdc++.h>
using namespace std;

#ifdef AshutoshOS // It works on my machine.
#include "../algo/debug.hpp" 
#else
#define deb(...)
#endif

#define int long long
// const int N = 1e6+10;
const int INF = 1e16;
const int MOD = 1e9+7;

using ll = long long;
const int N = 5e4 + 10;
vector<pair<int, int>> adj[N];
class Solution {
public:
    int findMaxPathScore(vector<vector<int>>& edges, vector<bool>& online, long long k) {
        int n = online.size();
        for(int i = 0; i < n; i++) adj[i].clear();

        for(auto &e: edges) {
            adj[e[0]].push_back({e[1], e[2]});
        }

        function<bool(int)> BFS = [&](int pathMin) {
            queue<array<ll, 3>> q; // {node, totalCost, pathMin}
            q.push({0, 0, INT_MAX});
            int foundPathMin = INT_MIN;
            while(!q.empty()) {
                auto top = q.front(); q.pop();
                ll par = top[0], prevCost = top[1], curMin = top[2];            
                if(par == (n-1)) {
                    // if(pathMin == 23) deb(curMin);
                    foundPathMin = max(foundPathMin, (int)curMin);
                }
                for(auto &e: adj[par]) {
                    int child = e.first, wt = e.second;
                    ll curCost = prevCost + wt;
                    if(curCost > k || (!online[child])) continue;

                    // if(pathMin == 23) deb(par, child, curCost, curMin)
                    q.push({child, curCost, min(curMin, (ll)wt)});
                }
            }
            // deb(pathMin, foundPathMin)
            if(foundPathMin >= pathMin) return true;
            return false;
        };

        int low = 0, high = 40, ans = -1;
        while(low <= high) {
            int midCost = low + (high - low) / 2;
            bool isOk = BFS(midCost);
            // deb(midCost, isOk);
            if(isOk) ans = midCost, low = midCost + 1;
            else high = midCost - 1;
        }
        return ans;
    }
};
void AshutoshGautam() {
    int n, m, k; cin >> n >> m >> k;
    vector<bool> online(n);
    vector<vector<int>> edges;
    for(int i = 0; i < m; i++) {
        int u, v, cost; cin >> u >> v >> cost;
        edges.push_back({u, v, cost});
    }
    for(int i = 0; i < n; i++) {
        bool ok; cin >> ok;
        online[i] = ok;
    }

    Solution st;
    cout << st.findMaxPathScore(edges, online, k) << "\n";
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int testCases = 1;
    // cin >> testCases; 

    for(int testCase = 1; testCase <= testCases ; testCase++)  
        AshutoshGautam(); // Ping me for solving any issue
    return 0;
}