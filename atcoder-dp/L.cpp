#include <iostream>
#include <sstream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cctype>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <unordered_map>
#include <queue>
#include <stack>
#include <algorithm>
#include <functional>
#include <numeric> 
using namespace std; 
#define DEBUG(x) cout << '>' << #x << ':' << x << endl;
#define REP(i,n) for(int i=0;i<(n);i++)
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define FORD(i,a,b) for(int i=(a);i>=(b);i--)
inline bool EQ(double a, double b) { return fabs(a-b) < 1e-9; }
const int INF = 1e9 + 5;
typedef long long ll;
inline int two(int n) { return 1 << n; }
inline int test(int n, int b) { return (n>>b)&1; }
inline void set_bit(int & n, int b) { n |= two(b); }
inline void unset_bit(int & n, int b) { n &= ~two(b); }
inline int last_bit(int n) { return n & (-n); }
inline int ones(int n) { int res = 0; while(n && ++res) n-=n&(-n); return res; }
template<class T> void chmax(T & a, const T & b) { a = max(a, b); }
template<class T> void chmin(T & a, const T & b) { a = min(a, b); }
///////////////////////////////////////////////////////////////////////

map<pair<int, int>, ll> memo;

ll helper(vector<int>& a, int i, int j) {
    if (memo.count({i, j}) != 0) return memo[{i, j}];
    if (i > j) return 0;
    if (i == j) return a[i];
    ll res = max(a[i] + min(helper(a, i + 2, j), helper(a, i + 1, j - 1)), a[j] + min(helper(a, i + 1, j - 1), helper(a, i, j - 2)));
    memo[{i, j}] = res;
    return res;
}

int main() {
    int n;
    scanf("%d", &n);
    vector<int> a(n);
    for (int& x : a) scanf("%d", &x);

    ll res = helper(a, 0, a.size() - 1);
    ll total = 0;
    for (int x : a) total += x;
    printf("%lld\n", 2 * res - total);
}