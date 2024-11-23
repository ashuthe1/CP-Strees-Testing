// Ashutosh Gautam ツ
// tag: special/convexhull/DSU_convexHull
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
 
    bool isMax = false;
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
 
    // explicit ConvexHullDynamic(bool isMax): isMax(isMax) {}
 
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

set<vector<int>> st;
vector<ConvexHullDynamic> lHull(N), rHull(N);
vector<pair<int, int>> v;
vector<int> lId(N), rId(N), pId(N);
int minCost = 0, n;

void init(int n) {
    st.clear();
    minCost = 0;
    v.clear(); v.resize(n);
    for(int i = 0; i < n; i++) {
        lHull[i].isMax = false;
        lHull[i].hull.clear();
        rHull[i].isMax = false;
        rHull[i].hull.clear();
        lId[i] = rId[i] = pId[i] = i;
    }
}

int findParent(int cur) {
    if(pId[cur] == cur) return cur;
    return pId[cur] = findParent(pId[cur]);
}
void mergeHull(ConvexHullDynamic &lH, ConvexHullDynamic &rH) {
    if(lH.hull.size() < rH.hull.size()) swap(lH, rH);
    for(auto &e: rH.hull) {
        lH.addLine(e.a, e.b);
    }
}
void mergeComponents(int l, int r, int cost) {
    l = findParent(l);
    r = findParent(r);
    if(l == r) return;

    if(l > r) swap(l, r);
    pId[r] = l;
    lId[l] = min(lId[l], lId[r]);
    rId[l] = max(rId[l], rId[r]);

    minCost += cost;
    mergeHull(lHull[l], lHull[r]);
    mergeHull(rHull[l], rHull[r]);

    if (lId[l]) {
        auto curEdge = {lHull[l].getBest(v[lId[l] - 1].first), l, findParent(lId[l] - 1)};
        st.insert(curEdge);
    } if (rId[l] + 1 < n) {
        auto curEdge = {rHull[l].getBest(v[rId[l] + 1].first), l, findParent(rId[l] + 1)};
        st.insert(curEdge);    
    }
}

void AshutoshGautam() {
    cin >> n;
    init(n);
    for(int i = 0; i < n; i++) cin >> v[i].first;
    for(int i = 0; i < n; i++) cin >> v[i].second;

    sort(v.begin(), v.end());
    for(int idx = 0; idx < n; idx++) {
        int x = v[idx].first, y = v[idx].second;
        deb(x, y)
        lHull[idx].addLine(-y, x * y);
        rHull[idx].addLine(y, -x * y);
        if(idx > 0) {
            auto curEdge = {lHull[idx].getBest(v[idx-1].first), idx, idx-1};
            st.insert(curEdge);
        }
        if(idx + 1 < n) {
            auto curEdge = {rHull[idx].getBest(v[idx+1].first), idx, idx+1};
            st.insert(curEdge);
        }
    } 

    while(!st.empty()) {
        auto top = *st.begin();
        int cost = top[0], l = top[1], r = top[2];
        mergeComponents(l, r, cost);
        st.erase(st.begin());
    }

    cout << minCost << "\n";
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int testCases = 1;
    cin >> testCases; 

    for(int testCase = 1; testCase <= testCases ; testCase++)  
        AshutoshGautam(); // Ping me for solving any issue ツ
    return 0;
}