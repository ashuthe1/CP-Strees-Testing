#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <bits/stdc++.h>

using namespace __gnu_pbds;
using namespace std;

using ll = long long;
using ld = long double;

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