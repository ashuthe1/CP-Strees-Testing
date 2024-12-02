// Ashutosh Gautam ツ
// tag: special/segmentTree/addition_of_ap_in_range
// Link: https://cses.fi/problemset/task/1736/
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
    // Overloading << for printing
    friend std::ostream& operator<<(std::ostream& os, const node& n) {
        os << "{val: " << n.val << "}";
        return os;
    }
};
struct update {
    int a = 0, d = 0;
    update(){}
    update(int a, int d) {
        this->a = a; 
        this->d = d;
    }
    void combine(update &newUpdate, const int &tl, const int &tr) {
        a += newUpdate.a;
        d += newUpdate.d;
    }
    // store the correct information in the node x
    void apply(node &cur, const int &tl, const int &tr){
        int terms = (tr - tl + 1);
        int extraSum = terms * a + (terms * (terms - 1) * d) / 2;
        cur.val += extraSum;
    }
     // Overloading << for printing
    friend std::ostream& operator<<(std::ostream& os, const update& u) {
        os << "{a: " << u.a << ", d: " << u.d << "}";
        return os;
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

        int terms = (tm - tl + 1);
        update updRight = updates[idx];
        updRight.a = updates[idx].a + terms * updates[idx].d;
        updRight.d = updates[idx].d;

        apply(idx << 1, tl, tm, updates[idx]);
        apply((idx << 1) | 1, tm + 1, tr, updRight);
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

        int terms = max(0LL, tm - max(l, tl) + 1); // did one type here and stuck for 2 hrs :(
        update updRight = upd;
        update updLeft = upd;

        updRight.a = upd.a + terms * upd.d;
        updRight.d = upd.d;

        rangeUpdate(idx << 1, tl, tm, l, r, updLeft);
        rangeUpdate((idx << 1) | 1, tm + 1, tr, l, r, updRight);
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
    void debug() {
        for(int i = 1; i < 2*len; i++) {
            deb(i, segTree[i]);
            if(lazy[i]) {
                deb(updates[i]);
            }
        }
    }
};

void AshutoshGautam() {
    int n, q; cin >> n >> q;
    vector<int> v(n+1, 0);
    for(int i = 1; i <= n; i++) cin >> v[i];

    lazySegmentTree st(n+1);
    st.build(v);

    while(q--) {
        int t, l, r; cin >> t >> l >> r;
        // deb(t, l, r);
        // st.debug();
        if(t == 1) {
            st.rangeUpdate(l, r, update(1, 1));
        } else {
            int sum = st.query(l, r).val;
            cout << sum << "\n";
        }
        deb(t, l, r);
        st.debug();
        deb("over")
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