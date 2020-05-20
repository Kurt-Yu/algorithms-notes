# Network Flow Algorithms

```c++
//
// Ford-Fulkerson's maximum flow
//
// Description:
//   Given a directed network G = (V, E) with edge capacity c: E->R.
//   The algorithm finds a maximum flow.
//
// Algorithm:
//   Ford-Fulkerson's augmenting path algorithm
//
// Complexity:
//   O(m F), where F is the maximum flow value.
//
// Verified:
//   AOJ GRL_6_A: Maximum Flow
//
// Reference:
//   B. H. Korte and J. Vygen (2008):
//   Combinatorial Optimization: Theory and Algorithms.
//   Springer Berlin Heidelberg.
//


#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <functional>

using namespace std;

#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())

const int INF = 1 << 30;
struct graph {
    typedef long long flow_type;
    struct edge {
        int src, dst;
        flow_type capacity, flow;
        size_t rev;
    };
    int n;
    vector<vector<edge>> adj;
    graph(int n) : n(n), adj(n) { }
    void add_edge(int src, int dst, flow_type capacity) {
        adj[src].push_back({src, dst, capacity, 0, adj[dst].size()});
        adj[dst].push_back({dst, src, 0, 0, adj[src].size()-1});
    }
    int max_flow(int s, int t) {
        vector<bool> visited(n);

        function<flow_type(int,flow_type)> augment = [&](int u, flow_type cur) {
            if (u == t) return cur;
            visited[u] = true;
            for (auto &e: adj[u]) {
                if (!visited[e.dst] && e.capacity > e.flow) {
                    flow_type f = augment(e.dst, min(e.capacity - e.flow, cur));
                    if (f > 0) {
                        e.flow += f;
                        adj[e.dst][e.rev].flow -= f;
                        return f;
                    }
                }
            }
            return flow_type(0);
        };

        for (int u = 0; u < n; ++u)
            for (auto &e: adj[u]) e.flow = 0;

        flow_type flow = 0;
        while (1) {
            fill(all(visited), false);
            flow_type f = augment(s, INF);
            if (f == 0) break;
            flow += f;
        }
        return flow;
    }
};

int main() {
    for (int n, m; scanf("%d %d", &n, &m) == 2; ) {
        graph g(n);
        for (int i = 0; i < m; ++i) {
            int u, v, w;
            scanf("%d %d %d", &u, &v, &w);
            g.add_edge(u, v, w);
        }
        printf("%d\n", g.max_flow(0, n-1));
    }
}
```

```c++
//
// Maximum Flow (Edmonds-Karp)
//
// Description:
//   Given a directed network G = (V, E) with edge capacity c: E->R.
//   The algorithm finds a maximum flow.
//
// Algorithm:
//   Edmonds-Karp shortest augmenting path algorithm.
//
// Complexity:
//   O(n m^2)
//
// Verified:
//   AOJ GRL_6_A: Maximum Flow
//
// Reference:
//   B. H. Korte and J. Vygen (2008):
//   Combinatorial Optimization: Theory and Algorithms.
//   Springer Berlin Heidelberg.
//

#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>
#include <algorithm>
#include <functional>

using namespace std;

#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())

const int INF = 1 << 30;
struct graph {
    int n;
    struct edge {
        int src, dst;
        int capacity, residue;
        size_t rev;
    };
    edge &rev(edge e) { return adj[e.dst][e.rev]; };

    vector<vector<edge>> adj;
    graph(int n) : n(n), adj(n) { }
    void add_edge(int src, int dst, int capacity) {
        adj[src].push_back({src, dst, capacity, 0, adj[dst].size()});
        adj[dst].push_back({dst, src, 0, 0, adj[src].size()-1});
    }

    int max_flow(int s, int t) {
        for (int u = 0; u < n; ++u)
            for (auto &e: adj[u]) e.residue = e.capacity;
        int total = 0;
        while (1) {
            vector<int> prev(n, -1); prev[s] = -2;
            queue<int> que; que.push(s);
            while (!que.empty() && prev[t] == -1) {
                int u = que.front(); que.pop();
                for (edge &e: adj[u]) {
                    if (prev[e.dst] == -1 && e.residue > 0) {
                        prev[e.dst] = e.rev;
                        que.push(e.dst);
                    }
                }
            }
            if (prev[t] == -1) break;
            int inc = INF;
            for (int u = t; u != s; u = adj[u][prev[u]].dst)
                inc = min(inc, rev(adj[u][prev[u]]).residue);
            for (int u = t; u != s; u = adj[u][prev[u]].dst) {
                adj[u][prev[u]].residue += inc;
                rev(adj[u][prev[u]]).residue -= inc;
            }
            total += inc;
        } // { u : visited[u] == true } is s-side
        return total;
    }
};

int main() {
    for (int n, m; scanf("%d %d", &n, &m) == 2; ) {
        graph g(n);
        for (int i = 0; i < m; ++i) {
            int u, v, w;
            scanf("%d %d %d", &u, &v, &w);
            g.add_edge(u, v, w);
        }
        printf("%d\n", g.max_flow(0, n-1));
    }
}
```

```c++
//
// Dinic's maximum flow
//
// Description:
//   Given a directed network G = (V, E) with edge capacity c: E->R.
//   The algorithm finds a maximum flow.
//
// Algorithm:
//   Dinic's blocking flow algorithm.
//
// Complexity:
//   O(n^2 m), but very fast in practice.
//   In particular, for a unit capacity graph,
//   it runs in O(m min{m^{1/2}, n^{2/3}}).
//
// Verified:
//   SPOJ FASTFLOW
//
// Reference:
//   E. A. Dinic (1970):
//   Algorithm for solution of a problem of maximum flow in networks with power estimation.
//   Soviet Mathematics Doklady, vol. 11, pp. 1277-1280.
//
//   B. H. Korte and J. Vygen (2008):
//   Combinatorial Optimization: Theory and Algorithms.
//   Springer Berlin Heidelberg.
//

#include <iostream>
#include <vector>
#include <cstdio>
#include <queue>
#include <algorithm>
#include <functional>

using namespace std;

#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())

const long long INF = (1ll << 50);
struct graph {
    typedef long long flow_type;
    struct edge {
        int src, dst;
        flow_type capacity, flow;
        size_t rev;
    };
    int n;
    vector<vector<edge>> adj;
    graph(int n) : n(n), adj(n) { }
    void add_edge(int src, int dst, flow_type capacity) {
        adj[src].push_back({src, dst, capacity, 0, adj[dst].size()});
        adj[dst].push_back({dst, src, 0, 0, adj[src].size()-1});
    }
    flow_type max_flow(int s, int t) {
        vector<int> level(n), iter(n);
        function<int(void)> levelize = [&]() { // foward levelize
            level.assign(n, -1); level[s] = 0;
            queue<int> Q; Q.push(s);
            while (!Q.empty()) {
                int u = Q.front(); Q.pop();
                if (u == t) break;
                for (auto &e: adj[u]) {
                    if (e.capacity > e.flow && level[e.dst] < 0) {
                        Q.push(e.dst);
                        level[e.dst] = level[u] + 1;
                    }
                }
            }
            return level[t];
        };

        function<flow_type(int, flow_type)> augment = [&](int u, flow_type cur) {
            if (u == t) return cur;
            for (int &i = iter[u]; i < adj[u].size(); ++i) {
                edge &e = adj[u][i], &r = adj[e.dst][e.rev];
                if (e.capacity > e.flow && level[u] < level[e.dst]) {
                    flow_type f = augment(e.dst, min(cur, e.capacity - e.flow));
                    if (f > 0) {
                        e.flow += f;
                        r.flow -= f;
                        return f;
                    }
                }
            }
            return flow_type(0);
        };

        for (int u = 0; u < n; ++u) // initialize
            for (auto &e: adj[u]) e.flow = 0;

        flow_type flow = 0;
        while (levelize() >= 0) {
            fill(all(iter), 0);
            for (flow_type f; (f = augment(s, INF)) > 0; )
                flow += f;
        }
        return flow;
    }
};

int main() {
    for (int n, m; scanf("%d %d", &n, &m) == 2; ) {
        graph g(n);
        for (int i = 0; i < m; ++i) {
            int u, v, w;
            scanf("%d %d %d", &u, &v, &w);
            //g.add_edge(u, v, w);
            g.add_edge(u-1, v-1, w);
        }
        printf("%lld\n", g.max_flow(0, n-1));
    }
}
```

## Min-Cut Problem

To get the value of the minimum cut, just run max flow.

To extract the actual edges in the minimum cut, we use the fact that all of them must be saturated.

We do a graph traversal starting from `s` and only traversal edges that have positive remaining capacity and record which vertices we visited.

The edges which have a visited vertex on one end and an unvisited vertex on the other will form the minimum cut (compare to the definition of a `s-t` cut).

## Variants

### Project Selection

See `project_selection.cc` file.

### Vertex Capacities

A graph has vertex capacities if there are also capacity restrictions on how much flow can go through a vertex.

This is solved by splitting each vertex into two vertices: `in` vertex and `out` vertex.

For some vertex `u` with capacity <code>$c_{u}$</code>, we add an edge <code>$in_{c}$</code> to <code>$out_{c}$</code> with capacity <code>$c_{u}$</code>.

Incoming edges go to <code>$in_{c}$</code> and outgoing edges leave from <code>$out_{c}$</code> with their original capacities.

### Multiple Sources and Sinks

Sometimes a problem will naturally have multiple sources or sinks.

Just make all the sources into regular nodes and connect them with infinite edges to a "supersource", the actual source of the flow graph. Same with sinks.

### Undirected Graphs

Sometimes you want to find flow or min cut in a undirected graph.

Just duplicate each edge, one going forwards, one going backwards.

### Maximum edge-disjoint paths in a graph

A set of paths is edge-disjoint if no two paths use the same edge.

To find the maximum number of edge-disjoint paths from `s` to `t`, make a flow graph where all edges have capacity 1.

The maximum flow of this graph will give the answer.

### Minimum vertex cover in a bipartite graph

A vertex cover in a graph is a set of vertices which touches at least one endpoint of every edge.

By *Konig's theorem*, the size of the maximum matching is equal to the number of vertices in a minimum vertex cover.

Actually this is just min-cut max-flow. Using our earlier construction of a flow network for bipartite graphs, the min cut corresponds to a max vertex cover.

## Example Problems

When solve real problems, consider these two parts:
+ recognizing they are flow problems
+ constructing the right flow graph

