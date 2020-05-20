# Minimum Spanning Tree

A **spanning tree** for some graph G is a subgraph of G that is a tree, and also connects (spans) all of the vertices of G.

A **minimum spanning tree (MST)** is a spanning tree with minimum sum of edge weights.

## Kruskal's algorithm

+ For each edge `e` in increasing order of weight, add `e` to the MST if the vertices it connects are not already in the same connected component.
+ Maintain connectedness with **union-find**.
+ Takes `O(E log E)` time to run, with the complexity dominated by the time needed to sort the edges in increasing order.

```cpp
struct edge {
  int u, v, w;
};

bool operator< (const edge& a, const edge& b) {
  return a.w < b.w;
};

edge edges[N];
int p[N];
int root (int u);           // union-find root with path compression
void join (int u, int v);   // union-find join with size heuristic

int mst() {
    sort(edges, edges+m); // sort by increasing weight
    int total_weight = 0;
    for (int i = 0; i < m; i++) {
        edge& e = edges[i];
        // if the endpoints are in different trees, join them
        if (root(e.u) != root(e.v)) {
            total_weight += e.w;
            join(e.u, e.v);
        }
    }
    return total_weight;
}
```