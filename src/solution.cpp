#include<bits/stdc++.h>
using namespace std;
#define gc getchar_unlocked
#define fo(i,n) for(i=0;i<n;i++)
#define Fo(i,k,n) for(i=k;k<n?i<n:i>n;k<n?i+=1:i-=1)
#define ll long long
#define si(x)    scanf("%d",&x)
#define sl(x)    scanf("%lld",&x)
#define ss(s)    scanf("%s",s)
#define pi(x)    printf("%d\n",x)
#define pl(x)    printf("%lld\n",x)
#define ps(s)    printf("%s\n",s)
#define deb(x) cout << #x << "=" << x << endl
#define deb2(x, y) cout << #x << "=" << x << "," << #y << "=" << y << endl
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define al(a)           a.begin(),a.end()
#define alg(a)          a.rbegin(),a.rend()
#define getunique(v)    {sort(al(v)); v.erase(unique(al(v)),v.end());}
#define input(a,n)      for(int i=0;i<n;i++)cin>>a[i]
#define print(a)        for(auto it:a){cout<<it<<" ";}cout<<endl
#define sll             set<long long>
#define msll            multiset<long long>
#define inmap(x,mymap)  mymap.find(x)!=mymap.end()
#define mll             map<ll,ll>
#define mmll            multimap<ll,ll>
#define uset            unordered_set<ll>
#define lb              lower_bound
#define ub              upper_bound
#define Inf             1e18
#define YES             cout << "YES" << endl;
#define NO              cout << "NO" << endl;
#define yes             cout << "YES" << endl;
#define no              cout << "NO" << endl;
/*--- bit-stuff ----*/
#define setbits(a)      (__builtin_popcountll(a))  // to count 1 bits
#define right(a)        (__builtin_ctzll(a))       // to count trailing 0s
#define left(a)         (__builtin_clzll(a))       // to count leading 0s
#define parity(a)       (__builtin_parityll(a))    // to check even odd
#define all(x) x.begin(), x.end()
#define clr(x) memset(x, 0, sizeof(x))
#define sortall(x) sort(all(x))
#define tr(it, a) for(auto it = a.begin(); it != a.end(); it++)
#define PI 3.1415926535897932384626
typedef pair<int, int>    pii;
typedef pair<ll, ll>    pl;
typedef vector<int>        vi;
typedef vector<ll>        vl;
typedef vector<pii>        vpii;
typedef vector<pl>        vpl;
typedef vector<vi>        vvi;
typedef vector<vl>        vvl;
mt19937_64 rang(chrono::high_resolution_clock::now().time_since_epoch().count());
int rng(int lim) {
    uniform_int_distribution<int> uid(0,lim-1);
    return uid(rang);
}
ll mpow(ll base, ll exp); 
ll NCR(ll n,ll r, ll M);
ll gcdExtended(ll a, ll b, ll* x, ll* y);
ll modinverse(ll A, ll M);
void linear_sieve();
bool is_ancestor(ll u, ll v);
ll lca(ll u, ll v);

const int mod = 1'000'000'007;
const int mod2 = 998244353;
const int N = 3e5, M = N;
const int N1 = 10000000;
//=======================

template <int MOD=mod>
struct Modular {
  int value;
  static const int MOD_value = MOD;

  Modular(long long v = 0) { value = v % MOD; if (value < 0) value += MOD;}
  Modular(long long a, long long b) : value(0){ *this += a; *this /= b;}

  Modular& operator+=(Modular const& b) {value += b.value; if (value >= MOD) value -= MOD; return *this;}
  Modular& operator-=(Modular const& b) {value -= b.value; if (value < 0) value += MOD;return *this;}
  Modular& operator*=(Modular const& b) {value = (long long)value * b.value % MOD;return *this;}

  friend Modular mexp(Modular a, long long e) {
    Modular res = 1; while (e) { if (e&1) res *= a; a *= a; e >>= 1; }
    return res;
  }
  friend Modular inverse(Modular a) { return mexp(a, MOD - 2); }

  Modular& operator/=(Modular const& b) { return *this *= inverse(b); }
  friend Modular operator+(Modular a, Modular const b) { return a += b; }
  friend Modular operator-(Modular a, Modular const b) { return a -= b; }
  friend Modular operator-(Modular const a) { return 0 - a; }
  friend Modular operator*(Modular a, Modular const b) { return a *= b; }
  friend Modular operator/(Modular a, Modular const b) { return a /= b; }
  friend std::ostream& operator<<(std::ostream& os, Modular const& a) {return os << a.value;}
  friend bool operator==(Modular const& a, Modular const& b) {return a.value == b.value;}
  friend bool operator!=(Modular const& a, Modular const& b) {return a.value != b.value;}
};

struct segtree{
        ll size;
        vector<long long> tree; 
        void init(ll n){
                size=1;
                while(size<n) size*=2;
                vl v;
                ll val = 0;
                tree.assign(2*size,val);

        }
        void build(vl &a,ll x,ll lx,ll rx){
                if(rx-lx==1){
                        if(lx<a.size()) tree[x] = a[lx];
                        return;
                }
                else{
                    ll m = (lx+rx)/2;
                    build (a,2*x+1,lx,m);
                    build (a,2*x+2,m,rx);
                    tree[x] = tree[2*x+1] +  tree[2*x+2];
                }
        }
        void build(vl &a){
                build(a,0,0,size);
        }
        ll todo(ll l, ll r, ll x,ll lx,ll rx){
                if(l>=rx || r<=lx) return 0;
                if(lx>=l && rx<=r){
                      return tree[x];  
                }
                else{
                        ll m=(lx+rx)/2;
                        return todo(l,r,2*x+1,lx,m) + todo(l,r,2*x+2,m,rx);
                }
        }
        ll todo(ll l, ll r){
                ll p = todo(l,r,0,0,size);
                return p;
        }
        
};


// =================================================================

vvl g(N);
vl depth(N),tot(N),par(N); 
vector<ll> lp(N1+1),pr;
ll ans, n ;

void df(ll c, ll p, bool b){
    if(p!=-1) depth[c] = 1 + depth[p];
    ll cur = 0;
    bool pp = b;
    tot[c] = 1;
    par[c] = p;
    for(ll t : g[c]){
        if(t!=p){
            b = (b || (t==n-1));
            cur++;
        }
    }
    if(!pp) ans+=cur;
    for(ll t : g[c]){
        if(t!=p){
            df(t,c,b);
            tot[c] += tot[t];
        }
    }
}

void solve(){
    ll i,j,k,m;
    cin>>n>>k;
    fo(i,n){
        g[i].clear();
        depth[i] = 1;
        tot[i]  = 0;
        par[i] = -1;
    }
    fo(i,n-1){
        ll x,y;
        cin>>x>>y;
        x--;y--;
        g[x].pb(y);
        g[y].pb(x);
    }
    ans = 1;
    df(0,-1,0);

    if(k>= n-depth[n-1]+1){
        cout<<depth[n-1]<<endl;
        return;
    }

    ll l = k+1, r = n-depth[n-1]+1;


    ll rem = n-1;

    ll cur = n-1;
    while(cur != 0){
        for(ll t : g[par[cur]]){
            if(t!= par[par[cur]]) rem--;
        }
        cur = par[cur];
    }


    if(r-l+1<=rem) cout<<depth[n-1]<<endl;
    else{
        ll cur = n-1;
        vl v;
        while(cur != 0){
            for(ll t : g[par[cur]]){
                if(t!=cur) v.pb(tot[t]);
            }
            cur = par[cur];
        }
        sortall(v);
        ans = 0;
        fo(i,r-l+1-rem) ans += v[i];
        cout<<depth[n-1]+ans<<endl;
    }
}

int main(){
    // linear_sieve();
    int t = 1;
    cin>>t;
    while(t--) solve();
    return 0;
}

void linear_sieve()
{
    for (int i=2; i <= N1; ++i) {
    if (lp[i] == 0) {
        lp[i] = i;
        pr.push_back(i);
    }
    for (int j=0; j < (int)pr.size() && pr[j] <= lp[i] && i*pr[j] <= N1; ++j) {
        lp[i * pr[j]] = pr[j];
    }
  }
}

ll modinverse(ll A, ll M)
{
    ll x, y;
    ll g = gcdExtended(A, M, &x, &y);
    if (g != 1)
        return -1;
    else {
 
        // m is added to handle negative x
        ll res = (x % M + M) % M;
        return res;
    }
}

ll gcdExtended(ll a, ll b, ll* x, ll* y)
{
 
    // Base Case
    if (a == 0) {
        *x = 0, *y = 1;
        return b;
    }
 
    // To store results of recursive call
    ll x1, y1;
    ll gcd = gcdExtended(b % a, a, &x1, &y1);
 
    // Update x and y using results of recursive
    // call
    *x = y1 - (b / a) * x1;
    *y = x1;
 
    return gcd;
}

ll NCR(ll n,ll r, ll M){
        if(r>n) return 0ll;
        if(r== n || r==0 ) return 1ll;
        ll a1=1,a2=1,a3=1,i;
        for(i=1;i<=n;i++) a1=(a1*i)%M;
        for(i=1;i<=r;i++) a2=(a2*i)%M;
        for(i=1;i<=n-r;i++) a3=(a3*i)%M;
        a2=(a2*(a3))%M;
        a2=modinverse(a2,M);
        a1=(a1*a2)%M;
        return a1;
}

ll mpow(ll base, ll exp) {
  base %= mod;
  ll result = 1;
  while (exp > 0) {
    if (exp & 1) result = ((ll)result * base) % mod;
    base = ((ll)base * base) % mod;
    exp >>= 1;
  }
  return result;
}

void ipgraph(ll n, ll m){
    ll i, u, v;
    while(m--){
        cin>>u>>v;
    u--, v--;
        g[u].pb(v);
        g[v].pb(u);
    }
}

void dfs(ll u, ll par){
    for(ll v:g[u]){
        if (v == par) continue;
        dfs(v, u);
    }
}