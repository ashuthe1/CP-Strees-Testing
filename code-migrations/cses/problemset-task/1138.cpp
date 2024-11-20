// Ashutosh Gautam ツ
// path: https://cses.fi/problemset/task/1138
#include <bits/stdc++.h>
using namespace std;
 
#ifdef AshutoshOS // It works on my machine.
#include "../algo/debug.hpp" 
#else
#define deb(...)
#endif
 
#define int long long
const int N = 2e5+10;
const int INF = 1e16;
const int MOD = 1e9+7;
 
int n, q;
vector<int> adj[N], val, subSize, dfsArray, pathSum, indexx;
 
struct node {
    int val = 0;
    node(){}
    node(int val) {
        this->val = val;
    }
    void merge(const node &leftChild, const node &rightChild) { 
        val = leftChild.val + rightChild.val;
    }
};
struct update {
    int pending = 0; 
    update(){}
    update(int val) {
        this->pending = val; 
    }
    void combine(update &newUpdate, const int &tl, const int &tr) {
        pending += newUpdate.pending; 
    }
    // store the correct information in the node x
    void apply(node &cur, const int &tl, const int &tr){
        cur.val += (tr - tl + 1) * pending;  // Adding value v in range from L to R
    }
};
 
// template<typename node,typename update>
struct lazySegmentTree {
    int len;
    vector<node> segTree;
    vector<update> updates;
    vector<bool> lazy;
    node identity_element;
    update identity_transformation;
    void lazyInit(int l = 100000) {
        len = l;
        segTree.resize(4 * len);
        updates.resize(4 * len);
        lazy.resize(4 * len);
        identity_element = node();
        identity_transformation = update();
    }
    lazySegmentTree() {lazyInit();}
    lazySegmentTree(int l) {lazyInit(l);}
    
    void pushdown(const int &idx, const int &tl, const int &tr) {
        if(!lazy[idx]) return;
        int tm = (tl + tr) >> 1;
        apply(idx << 1, tl, tm, updates[idx]);
        apply((idx << 1) | 1, tm + 1, tr, updates[idx]);
        updates[idx] = identity_transformation;
        lazy[idx] = 0;
    }
    
    void apply(const int &idx, const int &tl, const int &tr, update upd) {
        if(tl != tr) {
            lazy[idx] = 1;
            updates[idx].combine(upd, tl, tr);
        }
        upd.apply(segTree[idx], tl, tr);
    }
 
    template<typename T>
    void build(const T &arr, const int &idx, const int &tl, const int &tr) {
        if(tl == tr) {
            segTree[idx] = arr[tl];
            return;
        }
        int tm = (tl + tr) >> 1;
        build(arr, idx << 1, tl, tm);
        build(arr, (idx << 1) | 1, tm + 1, tr);
        segTree[idx].merge(segTree[idx << 1], segTree[(idx << 1) | 1]);
    }
    node query(const int &idx, const int &tl, const int &tr, const int &l, const int &r) {
        if(l > tr || r < tl){
            return identity_element;
        }
        if(tl >= l && tr <= r){
            return segTree[idx];
        }
        pushdown(idx, tl, tr);
        int tm = (tl + tr) >> 1;
        node a = query(idx << 1, tl, tm, l, r), b = query((idx << 1) | 1, tm + 1, tr, l, r), ans;
        ans.merge(a, b);
        return ans;
    }
    void rangeUpdate(const int &idx, const int &tl, const int &tr, const int &l, const int &r, const update &upd) {
        if(l > tr || r < tl){
            return;
        }
        if(tl >= l && tr <= r){
            apply(idx, tl, tr, upd);
            return;
        }
        pushdown(idx, tl, tr);
        int tm = (tl + tr) >> 1;
        rangeUpdate(idx << 1, tl, tm, l, r, upd);
        rangeUpdate((idx << 1) | 1, tm + 1, tr, l, r, upd);
        segTree[idx].merge(segTree[idx<<1], segTree[(idx << 1) | 1]);
    }
 
    public:
    template<typename T> void build(const T &arr) {
        build(arr, 1, 0, len-1);
    }
    node query(const int &l, const int &r) { // st.query(i, i).val || 0 based indexing :)
        return query(1, 0, len - 1, l, r); 
    }
    void rangeUpdate(const int &l, const int &r, const update &upd) { // st.rangeUpdate(l, r, val)
        rangeUpdate(1, 0, len - 1, l, r, upd);
    }
};
 
void dfs(int node, int par, int sum) {
    dfsArray.push_back(node);
    indexx[node] = dfsArray.size() - 1;
    subSize[node] = 1;
    int curSum = sum + val[node];
    pathSum.push_back(curSum);
    for(int child: adj[node]) {
        if(child == par) continue;
        dfs(child, node, curSum);
        subSize[node] += subSize[child];
    }
}
 
void AshutoshGautam() {
    cin >> n >> q;
    val.resize(n+1);
    subSize.resize(n+1, 0);
    indexx.resize(n+1, 0);
    for(int i = 1; i <= n; i++) cin >> val[i];
    for(int i = 0; i < n-1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
 
    dfs(1, 1, 0);
    deb(dfsArray, subSize, pathSum, indexx)
 
    lazySegmentTree st(n+1);
    st.build(pathSum);
 
    while(q--) {
        int type; cin >> type;
        if(type == 1) {
            int node, newVal; cin >> node >> newVal;
            int diff = - (val[node] - newVal);
            val[node] = newVal;
            int subNodes = subSize[node];
            int l = indexx[node], r = l + subNodes - 1;
            deb(l, r, diff);
            st.rangeUpdate(l, r, diff);
        } else {
            int node; cin >> node;
            int idx = indexx[node];
            deb(idx);
            cout << st.query(idx, idx).val << "\n";
        }
    }
}
 
signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int testCases = 1;
    // cin >> testCases; 
 
    for(int testCase = 1; testCase <= testCases ; testCase++)  
        AshutoshGautam(); // Ping me for solving any issue ツ
    return 0;
