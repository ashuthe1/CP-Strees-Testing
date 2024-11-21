// Ashutosh Gautam ツ
// path: DP/atcoder_prefix_suffix_segmentTree
// link: https://atcoder.jp/contests/abc353/tasks/abc353_g
#include <bits/stdc++.h>
using namespace std;

#ifdef AshutoshOS // It works on my machine.
#include "../algo/debug.hpp" 
#else
#define deb(...)
#endif

#define int long long
const int N = 1e6+10;
const int INF = 1e15;
const int MOD = 1e9+7;

struct node {
    int val = -INF;
    node(){}
    node(int val) {
        this->val = val;
    }
    void merge(const node &leftChild, const node &rightChild) { 
        val = max(leftChild.val, rightChild.val);
    }
};
struct update {
    int pending = 0; 
    update(){}
    update(int val) {
        this->pending = val; 
    }
    void combine(update &newUpdate, const int &tl, const int &tr) {
        pending = newUpdate.pending; 
    }
    // store the correct information in the node x
    void apply(node &cur, const int &tl, const int &tr){
        cur.val = (tr - tl + 1) * pending;  // Adding value v in range from L to R
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

void AshutoshGautam() {
    int n, m, c; cin >> n >> c >> m;
    vector<pair<int, int>> v(m); // {Town, Profit}
    for(auto &e: v) cin >> e.first >> e.second;
    deb(n, c, m, v);
    vector<int> values(n+1, -INF);
    lazySegmentTree left(n+1), right(n+1);
    left.build(values); right.build(values);

    int ans = 0;
    for(int i = 0; i < m; i++){
        int curTown = v[i].first, curProfit = v[i].second;
        int leftMAX = left.query(1, curTown).val;
        int rightMAX = right.query(curTown, n).val;

        int leftDP = curProfit - curTown * c + leftMAX;
        int rightDP = curProfit + curTown * c + rightMAX;

        int curDP = max({leftDP, rightDP, curProfit - (curTown - 1) * c});
        ans = max(ans, curDP);
        left.rangeUpdate(curTown, curTown, curDP + curTown * c);
        right.rangeUpdate(curTown, curTown, curDP - curTown * c);
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