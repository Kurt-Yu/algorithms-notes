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

const int N = 1e5 + 5;

int n;
vector<int> A(N), B(N), C(N);
vector<vector<int>> dp(N, vector<int>(3));

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d%d%d", &A[i], &B[i], &C[i]);
    }
    dp[0][0] = A[0], dp[0][1] = B[0], dp[0][2] = C[0];
    for (int i = 1; i < n; ++i) {
        dp[i][0] = A[i] + max(dp[i - 1][1], dp[i - 1][2]);
        dp[i][1] = B[i] + max(dp[i - 1][0], dp[i - 1][2]);
        dp[i][2] = C[i] + max(dp[i - 1][0], dp[i - 1][1]);
    }

    printf("%d\n", max({dp[n - 1][0], dp[n - 1][1], dp[n - 1][2]}));
}