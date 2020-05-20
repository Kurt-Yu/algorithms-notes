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

const int N = 101;
const ll MAX_LL = 1e18L + 5;

int n, w;
int weight, value;
vector<ll> dp(N * 1000 + 1, MAX_LL);

// dp[i] is the minimum total weight of items with total value exactly i
int main() {
    scanf("%d%d", &n, &w);

    int total_value = N * 1000 + 1;
    dp[0] = 0;
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", &weight, &value);
        for (int value_already = total_value - value; value_already >= 0; --value_already) {
            chmin(dp[value_already + value], dp[value_already] + weight);
        }
    }

    ll res = 0;
    for (ll i = 0; i < total_value; ++i) {
        if (dp[i] <= w) res = max(res, i);
    }
    printf("%lld\n", res);
}