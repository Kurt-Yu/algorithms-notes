# Graph Traversals

## Graph Representations

+ Adjacency List
+ Adjacency Matrix

```cpp
#include <iostream>
#include <vector>

int N = 1e6 + 5;        // number of vertices in graph
vector<int> edges[N];   // each vertex has a list of connected vertices

void add(int u, int v) {
    edges[u].push_back(v);
    // Warning: If the graph has self-loops, you need to check this.
    if (v != u) {
        edges[v].push_back(u);
    }
}

// iterate over edges from u (since C++11)
for (int v : edges[u]) cout << v << '\n';

// iterate over edges from u (before C++11)
vector<int>::iterator it = edges[u].begin();
for (; it != edges[u].end(); ++it) {
    int v = *it;
    cout << v << '\n';
}

// or just a regular for loop will work too
for (unsigned int i = 0; i < edges[u].size(); i++) {
    cout << edges[u][i] << '\n';
}
```

## BFS
```cpp
vector<int> edges[N];
// dist from start. -1 if unreachable.
int dist[N];
// previous node on a shortest path to the start
// Useful for reconstructing shortest paths
int prev[N];

void bfs(int start) {
    fill(dist, dist+N, -1);
    dist[start] = 0;
    prev[start] = -1;

    queue<int> q;
    q.push(start);
    while (!q.empty()) {
        int c = q.front();
        q.pop();
        for (int nxt : edges[c]) {
            // Push if we have not seen it already.
            if (dist[nxt] == -1) {
                dist[nxt] = dist[c] + 1;
                prev[nxt] = c;
                q.push(nxt);
            }
        }
    }
}
```


## DFS
```cpp
// global arrays are initialised to zero for you
bool seen[N];

void dfs(int u) {
    if (seen[u]) return;
    seen[u] = true;
    for (int v : edges[u]) dfs(v);
}
```


## Bridge Finding

A bridge of `G` is an edge `e` whose removal disconnects `G`.

Claims:
+ Back edges cannot be bridges.
+ A tree edge is a bridge iff there is no back edge going "pass" it.

```cpp
void dfs(int u, int from = -1) {
    low[u] = preorder[u] = T++;
    for (int v : edges[u]) {
        // ignore the edge to our parent in the dfs
        if (v == from) continue;
        // update the lowest value in the preorder sequence that we can reach
        if (preorder[v] != -1) low[u] = min(low[u], preorder[v]);
        else {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            // if we haven't visited v before, check to see if we have a bridge
            if (low[v] == preorder[v]) bridges.insert(make_pair(min(u, v), max(u, v)));
        }
    }
}
```

## Cycle Detection

If the graph is **undirected**, we can simply run a DFS on the graph, and return true if any vertex marked seen is visited again.

However, **this doesn't work for directed graphs**, such as the diamond graph (1 -> 2 -> 3 <- 4 <- 1).

Algorithm: just mark each vertex "active" in a table during its preorder step (when we first reach `u`), and unmark it during its postorder step (when we return from `u`). Then check if any edge visits a vertex we are still recursing from.

```cpp
bool has_cycle(int u) {
    if (seen[u]) return false;
    seen[u] = true;
    active[u] = true;
    for (int v : edges[u]) {
        if (active[v] || has_cycle(v)) return true;
    }
    active[u] = false;
    return false;
}
```

## Topological Sort

```cpp
void dfs(int u, vector<int>& postorder) {
    if (seen[u]) return;
    seen[u] = true;
    for (int v : edges[u]) dfs(v);
    postorder.push_back(u);
} 

vector<int> topsort() {
    vector<int> res;
    for (int i = 0; i < n; i++) dfs(i, res);
    reverse(res.begin(), res.end()); // #include <algorithm>
    return res;
}
```

## Tree Representation

To represent a tree, we generally like to know what the parent of each node is, what the children of each node is and problem-specific additional metadata on its subtree (e.g: size).

```cpp
const int N = 1e6 + 5;

// We need the list of edges to construct our representation
// But we don't use it afterwards.
vector<int> edges[N];

int par[N]; // Parent. -1 for the root.
vector<int> children[N]; // Your children in the tree.
int size[N]; // As an example: size of each subtree.

void constructTree(int c, int cPar = -1) {
    par[c] = cPar;
    size[c] = 1;
    for (int nxt : edges[c]) {
        if (nxt == par[c]) continue;
        constructTree(nxt, c);
        children[c].push_back(nxt);
        size[c] += size[nxt];
    }
}
```





