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

int n, v;
vector<int> P, Q;

bool check(vector<int>& T, vector<int>& temp) {
    for (int i = 0; i < T.size(); ++i) {
        if (T[i] != temp[i]) return false;
    }
    return true;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &v);
        P.push_back(v);
    }
    for (int i = 0; i < n; ++i) {
        scanf("%d", &v);
        Q.push_back(v);
    }
    vector<int> temp;
    for (int i = 1; i <= n; ++i) temp.push_back(i);

    int p = 0, q = 0, i = 1;
    do {
        if (check(P, temp)) p = i;
        if (check(Q, temp)) q = i;
        if (p != 0 && q != 0) break;
        i++;
    } while(next_permutation(temp.begin(), temp.end()));
    printf("%d\n", abs(p - q));
}