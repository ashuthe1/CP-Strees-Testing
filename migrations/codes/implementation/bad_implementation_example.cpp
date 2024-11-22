// Ashutosh Gautam ツ
// tag: implementation/bad_implementation_example
// links: https://codeforces.com/contest/2030/problem/D
// wasn't able to implement the solution even after 2 hrs, got idea in 30 mins, to check min/max of each segment, but it't too complicated

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
    int mini = INT_MAX, maxx = INT_MIN;
    node(){}
    node(int val) {
        this->mini = val;
        this->maxx = val
    }
    void merge(const node &leftChild, const node &rightChild) { 
        mini = min(leftChild.mini, rightChild.mini);
        maxx = max(leftChild.maxx, rightChild.maxx);
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
    vector<int> v(n+1, 0);
    map<pair<int, int>, int> mp; // {{l, r}, true/false} 
    for(int i = 1; i <= n; i++) cin >> v[i];
    string s; cin >> s;
    s = '@' + s;

    lazySegmentTree st(n+1);
    st.build(v);
    set<pair<int, int>> segments; // {l, r}
    int prevStart = 1;
    char prevChar = s[1];
    for(int i = 2; i <= n; i++) {
        if(s[i] == 'R' && prevChar == 'L') {
            segments.insert({prevStart, i - 1});
            prevStart = i;
        }
        prevChar = s[i];
    }
    segments.insert({prevStart, n});

    auto change = [&](int idx) {
        if(s[idx] == 'R') s[idx] = 'L';
        else s[idx] = 'R';
    };

    auto printAns = [&]() {
        string ans = "YES";
        if(issue > 0) ans = "NO";
        prev = ans;
        cout << ans << "\n";
    };

    auto outOfRange = [&](int l, int r, int mini, int maxx) {
        if(mini < l || mini > r || maxx < l || maxx > r) {
            issue++;
            mp[{l, r}] = 1;
        }
    }

    int issue = 0;
    for(const auto &e: segments) {
        int l = e.first, r = e.second;
        int mini = st.query(l, r).mini;
        int maxx = st.query(l, r).maxx;
        if(mini < l || mini > r || maxx < l || maxx > r) {
            issue++;
            mp[{l, r}] = 1;
        }
    }
    string prev = "YES";
    while(q--) {
        int idx; cin >> idx;

        bool leftExist = true, rightExist = true;
        auto itRight = segments.upper_bound({idx, INT_MIN});
        if(itRight == segments.end()) rightExist = false;
        auto it = itRight; it--;
        auto itLeft = it; 
        if(it == st.begin()) leftExist = false;
        else itLeft--;

        int mini, maxx;
        if(idx == 1) {
            if(s[idx] == 'L' && s[idx+1] == 'R') {
                int l1 = it->first, r1 = it->second;
                int l2 = itRight->first, r2 = itRight->second;
                if(mp.find({l1, r1}) != mp.end()) issue--;
                if(mp.find({l2, r2}) != mp.end()) issue--;

                segments.erase(it);
                segments.erase(itRight);

                segments.insert({l1, r2});
                mini = st.query(l1, r2).mini;
                maxx = st.query(l1, r2).maxx;

                if(mini < l || mini > r || maxx < l || maxx > r) {
                    issue++;
                    mp[{l, r}] = 1;
                }

                printAns();
                change(idx);
                continue;
            }
            printAns();
            change(idx);
            continue;
        } else if(idx == n) {
            if(s[idx-1] == 'L' && s[idx] == 'R') {
                int l1 = itLeft->first, r1 = itLeft->second;
                int l2 = it->first, r2 = it->second;

                if(mp.find({l1, r1}) != mp.end()) issue--;
                if(mp.find({l2, r2}) != mp.end()) issue--;

                segments.erase(itLeft);
                segments.erase(it);

                segments.insert({l1, r2});
                mini = st.query(l1, r2).mini;
                maxx = st.query(l1, r2).maxx;

                if(mini < l || mini > r || maxx < l || maxx > r) {
                    issue++;
                    mp[{l, r}] = 1;
                }

                printAns();
                change(idx);
                continue;
            }
            printAns();
            change(idx);
            continue;
        }
        string temp = s.substr(idx-1, 3);
        if(temp == "RRL" || temp == "RLL") {
            change(idx);
            printAns();
            continue;
        }
        if(s == "LLL") {
            int l1 = it->first, r1 = it->second;
            if(mp.find({l1, r1}) != mp.end()) {
                issue--;
                mp.erase({l, r});
            }
            segments.erase(it);
            segments.insert(l, idx-1);
            mini = st.query(l, idx-1).mini
            maxx = st.query(l, idx-1).maxx;
            outOfRange(l, idx-1, mini, maxx);
            segments.insert(idx, r);
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int testCases = 1;
    cin >> testCases; 

    for(int testCase = 1; testCase <= testCases ; testCase++)  
        AshutoshGautam(); // Ping me for solving any issue ツ
    return 0;
}
