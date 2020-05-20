## Vector
```cpp
// functions
vec.size(); -> int
vec.empty(); -> bool 
reverse(vec.begin(), vec.end());
sort(vec.begin(), vec.end());   // increasing
sort(vec.begin(), vec.end(), greater<int>()); // decreasing
sort(vec.begin(), vec.end(), [](const int a, const int b){
    return a < b;
});     // own compare function

// element access
vec.front();    // first element
vec.back();     // last element
vec[i]; vec.at(i);  // at index i

// modifiers
vec.push_back();
vec.pop_bakc();
vec.insert(vec.begin(), 5); // insert 5 at beginning
vec.clear(); // remove all elements from container
vec.erase(vec.begin()); // remove the first element
```

## Stack
```cpp
s.empty();
s.size();
s.top();
s.push(x);
s.pop();
```

## Queue
```cpp
q.empty();
q.size();
q.front();
q.back();
q.push(x);
q.pop();
```

## Priority Queue
```cpp
pq.top();
pq.push(x);
pq.pop();

priority_queue<int> pq; // default is max heap
priority_queue<int, vector<int>, greater<int>> pq; // min heap
```

## Set / Multiset
```cpp
set<int> set;
multiset<int, greater<int>> set;

set.begin();
set.end();
set.size();
set.empty();

set.insert(x);
set.erase(iterator pos); // erase by iterator
set.erase(const g);      // erase by value
set.clear();
set.lower_bound(x);
set.upper_bound(x);
```

## Map / unordered_map
```cpp
map<int, int> map;
unordered_map<int, int> map;

map.begin();
map.end();
map.size();
map.empty();
map.clear();

map.insert({key, val});
map.count(x);
```

## Union-Find
```cpp
int parent[N], ranking[N];  

void init(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        ranking[i] = 1;
    }
}

int root(int x) {
    return parent[x] == x ? x : parent[x] = root(parent[x]);
}

void join(int x, int y) {
    x = root(x); y = root(y);
    if (x == y) return;
    if (subtree_size[x] < subtree_size[y]) {
        parent[x] = y;
        ranking[y] += ranking[x];
    } else {
        parent[y] = x;
        ranking[x] += ranking[y];
    }
}
```

## Range Queries and Updates
```cpp
#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;
#define fst first
#define snd second
#define all(c) begin(c), end(c)

struct UndoableUnionFind {
    vector<int> parent; 
    vector<tuple<int,int,int>> history;
    UndoableUnionFind(int n) : parent(n, -1) { };
    bool unite(int u, int v) { 
        u = root(u); v = root(v);
        if (u == v) {
            history.push_back(make_tuple(-1,-1,-1));
            return false;
        } else {
        if (parent[u] > parent[v]) swap(u, v);
            history.push_back(make_tuple(u, v, parent[v]));
            parent[u] += parent[v]; parent[v] = u;
            return true;
        }
    }
    void undo() {
        int u, v, w; 
        tie(u, v, w) = history.back();
        history.pop_back();
        if (u == -1) return;
        parent[v] = w;
        parent[u] -= parent[v];
    }
    bool find(int u, int v) { return root(u) == root(v); }
    int root(int u) { while (parent[u] >= 0) u = parent[u]; return u; }
    int size(int u) { return -parent[root(u)]; }
};

struct OfflineDynamicConnectivity {
    int n;
    UndoableUnionFind uf;
    OfflineDynamicConnectivity(int n) : n(n), uf(n) { }

    typedef pair<int,int> Edge;
    vector<Edge> query;
    vector<int> ans;
    map<Edge, vector<pair<int,int>>> appear;

    void addEdge(int u, int v) {
        if (u > v) swap(u, v);
        appear[{u,v}].push_back({query.size(), 1<<30});
    }
    void eraseEdge(int u, int v) {
        if (u > v) swap(u, v);
        appear[{u,v}].back().snd = query.size();
    }
    int isConnected(int u, int v) {
        query.push_back({u,v});
        return query.size()-1;
    }
    vector<set<Edge>> edges;
    void insert(int l, int r, int k, int s, int t, Edge e) {
        s = max(s, l); t = min(r, t);
        if (s >= t) return;
        if (s == l && t == r) {
            edges[k].insert(e);
        } else {
            insert(l, (l+r)/2, 2*k+1, s, t, e);
            insert((l+r)/2, r, 2*k+2, s, t, e);
            if (edges[2*k+1].count(e) && edges[2*k+2].count(e)) {
                edges[2*k+1].erase(e);
                edges[2*k+2].erase(e);
                edges[k].insert(e);
            }
        }
    }
    void rec(int l, int r, int k) {
        if (l >= r) return;
        for (Edge e: edges[k]) uf.unite(e.fst, e.snd);
        if (l+1 == r) {
            ans[l] = uf.find(query[l].fst, query[l].snd);
        } else {
            rec(l, (l+r)/2, 2*k+1);
            rec((l+r)/2, r, 2*k+2);
        }
        for (Edge e: edges[k]) uf.undo();
    }
    void solve() {
        int q = query.size();
        edges.resize(4*q);
        for (auto a: appear) 
            for (auto b: a.snd) 
                insert(0, q, 0, b.fst, b.snd, a.fst);
        ans.assign(q, 0);
        rec(0, q, 0);
    }
};

int main() {
    OfflineDynamicConnectivity solver(3);     // number of vertices
    solver.isConnected(0,1);                  // check if connected
    solver.addEdge(0,1);                      // add edge
    solver.isConnected(0,1);
    solver.isConnected(1,2);
    solver.addEdge(1,2);
    solver.isConnected(0,2);
    solver.eraseEdge(0,1);                    // erase edge 
    solver.isConnected(0,2);
    solver.solve();
    for (int i = 0; i < solver.query.size(); ++i) {
        cout << solver.query[i].fst << " " << solver.query[i].snd << " " << solver.ans[i] << endl;
    }
}
```