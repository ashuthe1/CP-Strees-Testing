// Ashutosh Gautam ツ
// tag: special/convexhull/usage_example
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

struct ConvexHullDynamic
{
    struct Line
    {
        int a, b; //y = ax + b
        double xLeft; //Stores the intersection wiith previous line in the convex hull. First line has -INF
 
        enum Type {line, maxQuery, minQuery} type;
        int val;
 
        explicit Line(int aa=0, int bb=0): a(aa), b(bb), xLeft(-INF), type(Type::line), val(0) {}
 
        int valueAt(int x) const
        {
            return a*x + b;
        }
        friend bool isParallel(const Line &l1, const Line &l2)
        {
            return l1.a == l2.a;
        }
        friend double intersectX(const Line &l1, const Line &l2)
        {
            return isParallel(l1, l2)?INF:1.0*(l2.b-l1.b)/(l1.a-l2.a);
        }
        bool operator<(const Line& l2) const
        {
            if(l2.type == line)
                return this->a < l2.a;
            if(l2.type == maxQuery)
                return this->xLeft < l2.val;
            if(l2.type == minQuery)
                return this->xLeft > l2.val;

            return false; // just adding to remove warning
        }
        // Overloading << operator
        friend ostream& operator<<(ostream& os, const Line& line) {
            os << "Line(a: " << line.a << ", b: " << line.b 
               << ", xLeft: " << line.xLeft << ")";
            return os;
        }
    };
 
    bool isMax;
    set<Line> hull;
 
    bool hasPrev(set<Line>::iterator it)
    {
        return it!=hull.begin();
    }   
    bool hasNext(set<Line>::iterator it)
    {
        return it!=hull.end() && next(it)!=hull.end();
    }
    bool irrelevant(const Line &l1, const Line &l2, const Line &l3)
    {
        return intersectX(l1, l3) <= intersectX(l1, l2);
    }
    bool irrelevant(set<Line>::iterator it)
    {
        return hasPrev(it) && hasNext(it) && ( 
            (isMax && irrelevant(*prev(it), *it, *next(it))) 
            || (!isMax && irrelevant(*next(it), *it, *prev(it))));
    }
    //Updates xValue of line pointed by it
    set<Line>::iterator updateLeftBorder(set<Line>::iterator it)
    {
        if(isMax && !hasPrev(it) || !isMax && !hasNext(it))
            return it;
        double val=intersectX(*it, isMax?(*prev(it)):(*next(it)));
        Line temp(*it);
        it=hull.erase(it);
        temp.xLeft=val;
        it=hull.insert(it, temp);
        return it;
    }
 
    explicit ConvexHullDynamic(bool isMax): isMax(isMax) {}
 
    void addLine(int a, int b) //Add ax + b in logN time
    {
        Line l3=Line(a, b);
        auto it=hull.lower_bound(l3);
 
        //If parallel liune is already in set, one of the lines becomes irrelevant
        if(it!=hull.end() && isParallel(*it, l3))
        {
            if(isMax && it->b<b || !isMax && it->b>b)
                it=hull.erase(it);
            else
                return;
        }
 
        it=hull.insert(it, l3);
        if(irrelevant(it))
        {
            hull.erase(it);
            return;
        }
 
        //Remove lines which became irrelevant after inserting
        while(hasPrev(it) && irrelevant(prev(it)))
            hull.erase(prev(it));
        while(hasNext(it) && irrelevant(next(it)))
            hull.erase(next(it));
 
        //Update xLine
        it=updateLeftBorder(it);
        if(hasPrev(it))
            updateLeftBorder(prev(it));
        if(hasNext(it))
            updateLeftBorder(next(it));
    }
 
    int getBest(int x)
    {
        Line q;
        q.val=x;
        q.type = isMax?Line::Type::maxQuery : Line::Type::minQuery;
 
        auto bestLine=hull.lower_bound(q);
        if(isMax)
            --bestLine;
        return bestLine->valueAt(x);
    }
};

void AshutoshGautam() {
    int n, ans = 0, maxDelta = 0; cin >> n;
    vector<pair<int, int>> v(n+1); // {value, index}
    vector<int> pre(n+1, 0);
    for(int i = 1; i <= n; i++) {
        cin >> v[i].first;
        v[i].second = i;
        pre[i] = pre[i-1] + v[i].first;
        ans += (v[i].first * i);
    }
    // sort(v.begin(), v.end(), greater<pair<int, int>>()); // sort according to (m --> value) for convex hull

    ConvexHullDynamic left(1), right(1); //1 for maximum convex hull
    // delta for left-cyclic shift = (al . r - sum(r)) + constant and simillar for right
    // left.addLine(0, 0);
    // right.addLine(0, 0);
    // for(int i = 1; i <= n; i++) {
    //     left.addLine(i, -pre[i]);
    //     right.addLine(i, -pre[i-1]);
    // }
    left.addLine(n, -pre[n]);
    for(int i = n-1; i >= 1; i--) {
        int val = v[i].first, idx = v[i].second;
        int delta1 = left.getBest(val) + pre[idx] - val * idx;
        // int delta2 = right.getBest(val) + pre[idx-1] - val * idx;
        maxDelta = max({maxDelta, delta1});
        left.addLine(i, -pre[i]);
    }
    right.addLine(1, -pre[0]);
    for(int i = 2; i <= n; i++) {
        int val = v[i].first, idx = v[i].second;
        // int delta1 = left.getBest(val) + pre[idx] - val * idx;
        int delta2 = right.getBest(val) + pre[idx-1] - val * idx;
        maxDelta = max({maxDelta, delta2});
        right.addLine(i, -pre[i-1]);
    }
    deb(ans, maxDelta)
    cout << ans + maxDelta << "\n";
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int testCases = 1;
    // cin >> testCases; 

    for(int testCase = 1; testCase <= testCases ; testCase++)  
        AshutoshGautam(); // Ping me for solving any issue ツ
    return 0;
}