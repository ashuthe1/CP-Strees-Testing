#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <bits/stdc++.h>

using namespace __gnu_pbds;
using namespace std;

using ll = long long;
using ld = long double;

<<<<<<< HEAD
#define int long long
const int N = 1e6+10;
const int INF = 1e16;
const int MOD = 1e9+7;
class Solution {
public:
class Sgtree{
    public:
    vector<int> segTree;
    Sgtree(int n)
    {
        segTree.resize(4 * n , 0);
    }
    void update(int ind , int i , int l , int r , int val){
        if(l == r){
            segTree[i] = val;
            return;
        }
        int mid = (l+r)/2;
        if(ind <= mid)update(ind , 2*i+1 , l , mid , val);
        else update(ind , 2*i+2 , mid+1 , r , val);
        segTree[i] = segTree[2*i+1] + segTree[2*i+2];
    }
    int query(int start , int end , int i , int l , int r){
        if(start > r || end < l)return 0;
        else if(start <= l && end >= r)return segTree[i];
        int mid = (l+r)/2;
        return query(start , end , 2*i+1 , l , mid) + query(start , end , 2*i+2 , mid+1 , r);
    }
};
    int depth[64];
    vector<int> popcountDepth(vector<long long>& nums, vector<vector<long long>>& queries) {
        int n = nums.size();
        depth[0] = -1;
        depth[1] = 0;
        depth[2] = 1;
        depth[3] = 2;
        vector<Sgtree> seg(6, Sgtree(n));
        for(int i = 4 ; i < 64 ; i++)
        {
            depth[i] = 1 + depth[__builtin_popcount(i)];
        }
        vector<int> count(n);
        for(int ind = 0 ; ind < n ; ind++)
        {
            int cnt = 0 ;
            long long i = nums[ind];
            if(i < 64)
            {
                cnt = depth[i];
            }
            else
            {
                cnt = depth[__builtin_popcountll(i)] + 1;
            }
            count[ind] = cnt;
            if(cnt < 6)
            {
                seg[cnt].update(ind , 0 , 0 , n - 1 , 1);
                for(int j = 0 ; j < 6 ; j++)
                {
                    if(j != cnt)seg[j].update(ind , 0 , 0 , n - 1 , 0);
                }
            }
        }
        vector<int> ans;
        for(auto &i : queries)
        {
            if(i[0] == 2)
            {
                int cnt;
                if(i[2] < 64)
                {
                    cnt = depth[i[2]];
                }
                else
                {
                    cnt = depth[__builtin_popcountll(i[2])] + 1;
                }
                if(count[i[1]] < 6)seg[count[i[1]]].update(i[1] , 0 , 0 , n - 1 , 0);
                if(cnt < 6)seg[cnt].update(i[1] , 0 , 0 , n - 1 , 1);
                count[i[1]] = cnt;
            }
            else
            {
                ans.push_back(seg[i[3]].query(i[1] , i[2] , 0 , 0 , n - 1));
            }
        }
        return ans;
    }
};
void AshutoshGautam() {
    int n, q; cin >> n >> q;
    vector<int> v(n);
    vector<vector<int>> queries;
    for(int &e: v) cin >> e;

    for(int i = 0; i < q; i++) {
        int type; cin >> type;
        int l, r, k, idx, val;
        if(type == 1) {
            cin >> l >> r >> k;
            queries.push_back({1, l, r, k});
        } else {
            cin >> idx >> val;
            queries.push_back({2, idx, val});
        }
    }

    Solution Test;
    vector<int> ans = Test.popcountDepth(v, queries);
    for(int &e: ans) cout << e << " ";
=======
typedef tree<
        pair<int, int>,
        null_type,
        less<pair<int, int>>,
        rb_tree_tag,
        tree_order_statistics_node_update>
        ordered_set;

#define mp make_pair
mt19937 rnd(time(0));

// 1. Overload the << operator for std::pair
template<typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) {
    os << p.first << ' ' << p.second << "|";
    return os;
>>>>>>> b46894dac8abad38ee97bf93025db05a00383850
}

// 2. Simple trait to detect if a type is a container
template<typename T, typename = void>
struct is_container : false_type {};

// Specialization: If T has begin() and end(), it's a container
template<typename T>
struct is_container<T, void_t<
        decltype(std::declval<T>().begin()),
        decltype(std::declval<T>().end())
>> : true_type {};

// 3. Generic print function
template<typename T>
void print(const T& element) {
    if constexpr (is_container<T>::value) {
        for(const auto& e : element) {
            print(e); // Recursive call for nested containers
        }
        cout << endl; // Newline after printing a container
    }
    else {
        cout << element << ' '; // Print non-container elements
    }
}


void solve()
{
    int n, m; cin>>n>>m;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin>>a[i];
    vector<int> b(m);
    for (int i = 0; i < m; i++) cin>>b[i];

    int prv = -1e9;
    set<int> B(b.begin(), b.end());
    for (int i = 0; i<n; i++)
    {
        auto pt = B.lower_bound(a[i] + prv);
        if (pt != B.end())
        {
            int res = (*pt) - a[i];
            if (a[i] < res && a[i] >= prv) res = a[i];
            prv = res;
        }
        else
        {
            if (a[i] < prv) {cout<<"NO"<<endl; return;}
            prv = a[i];
        }
        //need a[i] = b - a[i] >= prv, b >= prv + a[i];
    }
    cout<<"YES"<<endl;
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);

    int t = 1;
     // cin>>t;
    while (t--) solve();
}