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

const int N = 1005;
const int MOD = 1e9 + 7;
char matrix[N][N];
vector<vector<int>> res(N, vector<int>(N, 0));

int main() {
    int row, col;
    scanf("%d%d", &row, &col);
    for (int i = 0; i < row; ++i) {
        scanf("%s", matrix[i]);
    }

    res[1][1] = 1;
    for (int i = 1; i <= row; ++i) {
        for (int j = 1; j <= col; ++j) {
            if (matrix[i - 1][j - 1] == '#') res[i][j] = 0;
            else res[i][j] += res[i - 1][j] + res[i][j - 1];
            res[i][j] %= MOD;
        }
    }

    printf("%d\n", res[row][col]);
}