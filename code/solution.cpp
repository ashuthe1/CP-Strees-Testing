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

string WeightedPath(string stringArr[], int arrLength) {
    string ans = "-1";
    int n = stoi(stringArr[0]);
    string src = stringArr[1], dest = stringArr[n];

    map<string, vector<pair<int, string>>> adj;
    map<string, int> dist;
    map<string, string> par;
    set<pair<int, string>> st;

    for(int i = 1; i < arrLength; i++) {
        if (i <= n) {
            dist[stringArr[i]] = INT_MAX;
            continue;
        }
        string u = "", v = "", wt = "";
        int idx = 0, len = stringArr[i].size();
        while(idx < len && stringArr[i][idx] != '|') {
            u += stringArr[i][idx];
            idx++;
        }
        idx++;
        while(idx < len && stringArr[i][idx] != '|') {
            v += stringArr[i][idx];
            idx++;
        }
        idx++;
        while(idx < len) {
            wt += stringArr[i][idx];
            idx++;
        }

        int curWt = stoi(wt);
        adj[u].push_back({curWt, v});
        adj[v].push_back({curWt, u});
    }

    par[src] = "-1";
    st.insert({0, src});
    dist[src] = 0;
    while(!st.empty()) {
        auto top = st.begin();
        string curNode = top->second;
        int curWt = top->first;
        st.erase(st.begin());

        for(auto &e: adj[curNode]) {
            string child = e.second;
            int wt = e.first;

            if(dist[child] > curWt + wt) {
                par[child] = curNode;
                dist[child] = curWt + wt;
                st.insert({curWt + wt, child});
            }
        }
    }

    if(dist[dest] == INT_MAX) return ans;
    vector<string> path;
    string curNode = dest;
    while(curNode != "-1") {
        path.push_back(curNode);
        curNode = par[curNode];
    }
    reverse(path.begin(), path.end());
    ans = "";
    for(string &e: path) {
        ans += e;
        ans += "-";
    }
    if(ans.size() > 0) ans.pop_back();
    return ans;
}
void AshutoshGautam() {
    int arrLength; cin >> arrLength;
    string stringArr[arrLength];
    for(int i = 0; i < arrLength; i++) {
        cin >> stringArr[i];
    }
    auto ans = WeightedPath(stringArr, arrLength);
    deb(ans);
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int testCases = 1;
    // cin >> testCases; 

    for(int testCase = 1; testCase <= testCases ; testCase++)  
        AshutoshGautam(); // Ping me for solving any issue
    return 0;
}