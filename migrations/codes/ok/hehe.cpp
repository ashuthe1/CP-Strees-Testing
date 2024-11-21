// Ashutosh Gautam ツ
// path: ok/hehe
#include <bits/stdc++.h>
using namespace std;

#ifdef AshutoshOS // It works on my machine.
#include "../algo/debug.hpp" 
#else
#define deb(...)
#endif

#define int long long
const int N = 3010;
const int INF = 1e16;
const int MOD = 1e9+7;

vector<int> adj[N], subSize, papa, depth;
vector<pair<int, int>> subChild[N];
vector<bool> jammed;
void init(int n) {
    for(int i = 1; i <= n; i++) {
        adj[i].clear();
        subChild[i].clear();
    }
    depth.clear();
    depth.resize(n+1, 0);
    papa.clear();
    papa.resize(n+1, 0);
    jammed.clear();
    jammed.resize(n+1, false);
    subSize.clear();
    subSize.resize(n+1, 0);
}

void dfs(int node, int par) {
    papa[node] = par;
    subSize[node] = 1;
    for(int &child: adj[node]) {
        if(child == par) continue;
        dfs(child, node);
        subSize[node] += subSize[child];
        subChild[node].push_back({subSize[child], child});
        depth[child] = depth[node] + 1;
    }

}
void AshutoshGautam() {
    int n, k; cin >> n >> k;
    init(n);

    if(n == 1) {
        cout << "1\n";
        return;
    }
    for(int i = 0; i < n-1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    depth[1] = 1;
    dfs(1, -1);
    deb(subSize);
    for(int i = 1; i <= n; i++) {
        sort(subChild[i].begin(), subChild[i].end(), greater<pair<int, int>>());
        deb(i, subChild[i])
    }

    int rem = k-1, total = 0;
    vector<pair<int, int>> possibleSubtree;
    int curNode = n;
    while(curNode != 1) {
        int par = papa[curNode];
        for(auto &e: subChild[par]) {
            int child = e.second;
            if(child == curNode) continue;
            possibleSubtree.push_back({e.first, e.second});
            total += e.first;
        }
        curNode = par;
    }
    sort(possibleSubtree.begin(), possibleSubtree.end(), greater<pair<int, int>>());
    // deb(possibleSubtree)
    int idx = 0, sz = possibleSubtree.size();
    while(rem && idx < sz) {
        int node = possibleSubtree[idx].second;
        total -= possibleSubtree[idx].first;
        rem--;
        idx++;
    }
    cout << total + depth[n] << "\n";
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int testCases = 1;
    cin >> testCases; 

    for(int testCase = 1; testCase <= testCases ; testCase++)  
        AshutoshGautam(); // Ping me for solving any issue ツ
    return 0;
}