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

int n;
vector<int> justSum, v;
int findBlockIdx(int val) {
    int lo = 1, hi = n, blockIdx = n;
    while(lo <= hi) {
        int mid = (lo+hi)/2;
        if(justSum[mid] >= val) {
            blockIdx = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    return blockIdx;
}
void AshutoshGautam() {
    int q; 
    cin >> n;
    vector<int> pre(n+1, 0), prefKaPref(n+1, 0), blockSum(n+1, 0), preBlockSum(n+1, 0);
    v.push_back(0);
    for(int i = 1; i <= n; i++) {
        int x; cin >> x;
        v.push_back(x);
    }
    for(int i = 1; i <= n; i++) {
        pre[i] = pre[i-1] + v[i];
        prefKaPref[i] = prefKaPref[i-1] + pre[i];
    }
    for(int i = 1; i <= n; i++) {
        int sum = prefKaPref[n] - prefKaPref[i-1];
        int rem = (n - i + 1) * pre[i-1];
        blockSum[i] = sum - rem;
        preBlockSum[i] = preBlockSum[i-1] + blockSum[i];
    }
    int prevSum = 0;
    justSum.push_back(0);
    for(int i = n; i >= 1; i--) {
        prevSum += i;
        justSum.push_back(prevSum);
    }
    cin >> q;
    vector<int> output, calculatedOutput;
    while(q--) {
        int l, r; 
        cin >> l >> r;
        int lBlockIdx = findBlockIdx(l), rBlockIdx = findBlockIdx(r);
        int lTerms = l - justSum[lBlockIdx-1] - 1, rExtra = justSum[rBlockIdx] - r;
        int completelyOverlapped = (lBlockIdx == rBlockIdx)? 0: preBlockSum[rBlockIdx-1] - preBlockSum[lBlockIdx]; // lBlockIdx+1 to rBlockIdx-1 sum
        int lRemove = ((prefKaPref[lBlockIdx + (lTerms - 1)] - prefKaPref[lBlockIdx - 1]) - lTerms * pre[lBlockIdx - 1]);
        int rRemove = ((prefKaPref[n] - prefKaPref[n - rExtra]) - rExtra * pre[rBlockIdx - 1]);
        int leftPortion = blockSum[lBlockIdx] - lRemove;
        int rightPortion = blockSum[rBlockIdx] - rRemove;
        if(lBlockIdx == rBlockIdx) {
            int ans = blockSum[lBlockIdx];
            ans = ans - lRemove - rRemove;
            output.push_back(ans);
            continue;
        }
        int finalAns = completelyOverlapped + leftPortion + rightPortion;
        output.push_back(finalAns);
    }
    q = output.size();
    bool wrongFlag = false;
    for(int i = 0; i < q; i++) {
        cout << output[i] << "\n";
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