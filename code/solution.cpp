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

void AshutoshGautam() {
    int n, q; cin >> n >> q;
    vector<int> v(n+1, 0), ans(q+1), arr(n+1, 0);
    vector<vector<int>> que[n+1];

    for(int i = 1; i <= n; i++) {
        cin >> v[i];
    }
    for(int i = 1; i <= q; i++) {
        int l, r; cin >> l >> r;
        que[l].push_back({l, r, i});
    }
 
    lazySegmentTree st(n+1);
    int prev = -1;
    for(int i = 1; i <= n; i++) {
        int cur = 0;
        if(v[i] <= prev) {
            cur = prev - v[i];
        } 
        arr[i] = cur;
        prev = v[i] + cur;
    }
    st.build(arr);
    deb(arr);

    int prevExtra = 0;
    for(int l = 1; l <= n; l++) {
        deb(l, que[l]);
        for(auto e: que[l]) {
            int r = e[1], idx = e[2];
            int sumTillR = st.query(l, r).val;
            int operations = sumTillR + (r - l + 1) * prevExtra;
            ans[idx] = operations;
        }
        if(v[l] >= v[l-1]) continue;
        prevExtra += (v[l-1] - v[l]);
    }
 
    for(int i= 1; i <= q; i++) cout << ans[i] << "\n";
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int testCases = 1;
    // cin >> testCases; 

    for(int testCase = 1; testCase <= testCases ; testCase++)  
        AshutoshGautam(); // Ping me for solving any issue ツ
    return 0;
}