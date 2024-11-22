// Ashutosh Gautam ツ
// tag: special/convexhull/DSU_ConvexHullTechnique_optimization
// Problem link: https://drive.google.com/file/d/1yMXm2GZLMkKSqu0cUJiTZeXSuk8xd4aN/view?usp=drive_link
// CHT Best Template: https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/LineContainer.h
#include<bits/stdc++.h>
using namespace std;
#define nl '\n'
#define int long long

int n, m, k, p, q, u, v, w, l, r, x, y, z;
using ll = long long;
using ull = unsigned long long;
const int N = 2e5 + 10, inf = 1e9;
int mod = 1e9 + 7;
const ll linf = 1e18;

mt19937_64 randll(chrono::steady_clock::now().time_since_epoch().count());

struct Line {
    mutable ll k, m, p; // k -> slope :: m -> intercept
    bool operator<(const Line& o) const { return k < o.k; }
    bool operator<(ll x) const { return p < x; }
};

struct hull : multiset<Line, less<>> {
    // (for doubles, use inf = 1/.0, div(a,b) = a/b)
    static const ll inf = LLONG_MAX;
    ll div(ll a, ll b) { // floored division
        return a / b - ((a ^ b) < 0 && a % b); }
    bool isect(iterator x, iterator y) {
        if (y == end()) return x->p = inf, 0;
        if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
        else x->p = div(y->m - x->m, x->k - y->k);
        return x->p >= y->p;
    }
    void add(ll k, ll m) {
        auto z = insert({k, m, 0}), y = z++, x = y;
        while (isect(y, z)) z = erase(z);
        if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p >= y->p)
            isect(x, erase(y));
    }
    ll query(ll x) {
        assert(!empty());
        auto l = *lower_bound(x);
        return l.k * x + l.m;
    }
};

vector<hull> lhul(N), rhul(N);
vector<int> cl(N), cr(N), cc(N);
set<vector<int>> st; // cst, c1, c2

int find(int i) {
    return i == cc[i]? i : cc[i] = find(cc[i]);
}

int res;

void merge(hull &a, hull &b) {
    if (a.size() < b.size()) {
        swap(a, b);
    }
    for (Line l : b) {
        a.add(l.k, l.m);
    }
}
vector<pair<int, int>> vec;

void merge(int a, int b, int c) {
    a = find(a), b = find(b);
    if (a == b) return;
    res += c;
    if (a > b) swap(a, b);
    cc[b] = a;
    merge(rhul[a], rhul[b]);
    merge(lhul[a], lhul[b]);
    cl[a] = min(cl[a], cl[b]);  
    cr[a] = max(cr[a], cr[b]);
    if (cl[a]) {
        vector<int> v = {-lhul[a].query(vec[cl[a] - 1].first), a, find(cl[a] - 1)};
        st.insert(v);
    } if (cr[a] + 1 < n) {
        vector<int> v = {-rhul[a].query(vec[cr[a] + 1].first), a, find(cr[a] + 1)};
        st.insert(v);
    }
}

void solve (int tc = 1) {
    cin >> n;
    st.clear();
    for (int i = 0; i < n; i++) {
        lhul[i].clear();
        rhul[i].clear();
        cl[i] = cr[i] = cc[i] = i;
    }
    vec.resize(n);
    for (int i = 0; i < n; i++) cin >> vec[i].first;
    for (int i = 0; i < n; i++) cin >> vec[i].second;
    sort(vec.begin(), vec.end());
    for (int i = 0; i < n; i++) {
        auto [x, y] = vec[i];
        rhul[i].add(-y, x * y);
        lhul[i].add(y, -x * y);
        if (i + 1 < n) {
            vector<int> v = {-rhul[i].query(vec[i + 1].first), i, i + 1};
            st.insert(v);
        }
        if (i) {
            vector<int> v = {-lhul[i].query(vec[i - 1].first), i, i - 1};
            st.insert(v);
        }
    }
    res = 0;
    while (!st.empty()) {
        vector<int> v = *st.begin();
        st.erase(v);
        merge(v[1], v[2], v[0]);
    }
    for (int i = 0; i < n; i++) assert(find(i) == find(0));
    cout << res;
}
    
#undef int

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);
    int tc = 1;
    cin >> tc;
    // scanf("%d", &tc);
    while (tc--) {
        solve(tc);
        if (tc) cout << nl;
        // if (tc) printf("\n");
    }
}