# Shortest Paths

Given a weighted directed graph `G` with two specific vertices `s` and `t`, we want to find the shortest path that goes between `s` and `t` on the graph.

**Note**: It's very important to distinguish between graphs where all edges are positive and graphs with negative weight edges!

## Dijkstra's algorithm
```cpp
#include <queue>

typedef pair<int, int> edge; // (distance, vertex)
priority_queue<edge, vector<edge>, greater<edge>> pq;

// put the source s in the queue
pq.push(edge(0, s));
while (!pq.empty()) {
    // choose (d, v) so that d is minimal,
    // i.e. the closest unvisited vertex
    edge cur = pq.top();
    pq.pop();
    int v = cur.second, d = cur.first;
    if (seen[v]) continue;

    dist[v] = d;
    seen[v] = true;

    // relax all edges from v
    for (int i = 0; i < edges[v].size(); i++) {
        edge next = edges[v][i];
        int u = next.second, weight = next.first;
        if (!seen[u]) pq.push(edge(d + weight, u));
    }
}
```

**Note:** dijstra's algorithm doesn't work on graphs with negatice edges.

## Bellman-Ford Algorithm

```cpp
/*
 * bellman ford relax
 */

struct edge {
  int u, v, w;
  edge(int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}
};
vector<int> dist(n);
vector<edge> edges;

// global relaxation: try to relax every edge in the graph
// Returns if any distance was updated.
bool relax() {
    bool relaxed = false;
    for (auto e = edges.begin(); e != edges.end(); ++e) {
        // we don't want to relax an edge from an unreachable vertex
        if (dist[e->u] != INF && dist[e->v] > dist[e->u] + e->w) {
        relaxed = true;
        dist[e->v] = dist[e->u] + e->w;
        }
    }
    return relaxed;
}

/*
 * bellman ford main
 */

// Puts distances from source (n-1) in dist
// Returns true if there is a negative cycle, false otherwise.
// NOTE: You can't trust the dist array if this function returns True.
vector<int> find_dists_and_check_neg_cycle() {
    fill(dist.begin(), dist.end(), INF);
    dist[n-1] = 0;
    // |V|-1 global relaxations
    for (int i = 0; i < n - 1; i++) relax();

    // If any edge can be relaxed further, there is a negative cycle
    for (auto e = edges.begin(); e != edges.end(); ++e) {
        if (dist[e->u] != INF &&
            dist[e->v] > dist[e->u] + e->w) {
            return true;
        }
    }
    // Otherwise, no negative cycle, that condition is actually a iff
    return false;
}
```

## All Pairs Shortest Paths (Floyd-Warshall algorithm)

The all pairs shortest path problem involves finding the shortest path between every pair of vertices in the graph.

This can be find in <code>$O(V^3)$</code> time and <code>$O(V^2)$</code> memory.


**Note**: if there are negative-weight edges, but no negative cycles, Flody-Warshall will correctly find all distances.
```cpp
// the distance between everything is infinity
for (int u = 0; u < n; ++u) for (int v = 0; v < n; ++v) {
    dist[u][v] = 2e9;
}

// update the distances for every directed edge
for (/* each edge u -> v with weight w */) dist[u][v] = w;

// every vertex can reach itself
for (int u = 0; u < n; ++u) dist[u][u] = 0;

for (int i = 0; i < n; i++) {
    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            // dist[u][v] is the length of the shortest path from u to v 
            // using only 0 to i-1 as intermediate vertices
            // now that we're allowed to also use i
            // the only new path that could be shorter is u -> i -> v
            dist[u][v] = min(dist[u][v], dist[u][i] + dist[i][v]);
        }
    }
}
```

## Related Problems

TODO

## Shortest Distance on a Tree

Given a weighted tree, answer `Q` queries of shortest distance between vertex <code>$u_{i}$</code> and <code>$v_{i}$</code>.

This is suffices to find the **Lowest Common Ancestor (LCA)**.

```cpp
#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <functional>

using namespace std;

#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())
#define TEST(s) if (!(s)) { cout << __LINE__ << " " << #s << endl; exit(-1); }

struct tree {
    int n;
    vector<vector<int>> adj;
    tree(int n) : n(n), adj(n) { }
    void add_edge(int s, int t) {
        adj[s].push_back(t);
        adj[t].push_back(s);
    }
    vector<int> pos, tour, depth;
    vector<vector<int>> table;
    int argmin(int i, int j) { return depth[i] < depth[j] ? i : j; }
    void rootify(int r) {
        pos.resize(n);
        function<void (int,int,int)> dfs = [&](int u, int p, int d) {
            pos[u] = depth.size();
            tour.push_back(u);
            depth.push_back(d);
            for (int v: adj[u]) {
                if (v != p) {
                    dfs(v, u, d+1);
                    tour.push_back(u);
                    depth.push_back(d);
                }
            }
        }; dfs(r, r, 0);
        int logn = sizeof(int)*__CHAR_BIT__-1-__builtin_clz(tour.size()); // log2
        table.resize(logn+1, vector<int>(tour.size()));
        iota(all(table[0]), 0);

        for (int h = 0; h < logn; ++h) 
            for (int i = 0; i+(1<<h) < tour.size(); ++i)
                table[h+1][i] = argmin(table[h][i], table[h][i+(1<<h)]);
    }
    int lca(int u, int v) {
        int i = pos[u], j = pos[v]; if (i > j) swap(i, j);
        int h = sizeof(int)*__CHAR_BIT__-1-__builtin_clz(j-i); // = log2
        return i == j ? u : tour[argmin(table[h][i], table[h][j-(1<<h)])];
    }
};

int main() {
    int n;
    scanf("%d", &n);
    tree T(n);
    for (int u = 0; u < n ; ++u) {
        int k; 
        scanf("%d", &k);
        for (int j = 0; j < k; ++j) {
            int v;
            scanf("%d", &v);
            T.add_edge(u, v);
        }
    }
    T.rootify(0);
    int q;
    scanf("%d", &q);
    for (int i = 0; i < q; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        printf("%d\n", T.lca(u, v));
    }
}
```