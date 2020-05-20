# Lowest Common Ancestor

According to the [definition of LCA on Wikipedia](https://en.wikipedia.org/wiki/Lowest_common_ancestor): “The lowest common ancestor is defined between two nodes `p` and `q` as the lowest node in `T` that has both `p` and `q` as descendants (where we allow a node to be a descendant of itself).”

This is an important topic in tree data structure and it occurs frequently in interviews and competitive programming contest. That's why I decided to write a seperate article about it. We will not only examine the standard recursive and iterative `O(n)` space and `O(n)` time solution, but also much more effecient approaches (`O(n logn) preprocessing and O(logn) per query`).

We start from the easiest case: find LCA in a binary search tree.
## [Leetcode 235. Lowest Common Ancestor of a Binary Search Tree](https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/)

Due to the property of BST, we can easily come up with the following recursive solution. Notice that there's no guarantee `p->val` is smaller than `q->val`, that's why we need a `swap` statement.
```cpp
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root) return NULL;
    if (p->val > q->val) swap(p, q);
    if (root->val >= p->val && root->val <= q->val) return root;
    else if (root->val < p->val) return lowestCommonAncestor(root->right, p, q);
    return lowestCommonAncestor(root->left, p, q);
}
```

## [Leetcode 236. Lowest Common Ancestor of a Binary Tree](https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/)
> Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.

Since a general binary tree doesn't have the above property, we cannot simply recursive on the left and right subtree based on their node value. 

The naive iterative solution would be using a `DFS` or `BFS` traversal, find the parent of each node. Then start from `p` and `q`, trace back to their parent, they will meet at some node in the end. That would gives us result.

Consider the following example tree:
![example tree](https://assets.leetcode.com/uploads/2018/12/14/binarytree.png)

*Example Input 1*: `p = 5, q = 1`.
`parent[5] = 3, parent[1] = 3, result = 3`.

*Example Input 2*: `p = 5, q = 4`.
`parent[4] = 2, parent[parent[4]] = 5 = p, result = 5`
 
Below is the `BFS` C++ implementation:
```cpp
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    unordered_map<TreeNode*, TreeNode*> parent;
    parent[root] = nullptr;
    queue<TreeNode*> qu;
    qu.push(root);
    
    while (!parent.count(p) || !parent.count(q)) {
        for (int i = qu.size(); i > 0; --i) {
            auto node = qu.front();
            qu.pop();
            if (node->left) qu.push(node->left), parent[node->left] = node;
            if (node->right) qu.push(node->right), parent[node->right] = node;
        }
    }
    
    unordered_set<TreeNode*> s;
    while (p) s.insert(p), p = parent[p];
    while (q && !s.count(q)) q = parent[q];
    return q;
}
```

We can also try to use recursion. The following code is pretty self-explantory:
```cpp
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root || root == p || root == q) return root;
    auto left = lowestCommonAncestor(root->left, p, q);
    auto right = lowestCommonAncestor(root->right, p, q);
    if (left && right) return root;
    if (!left && !right) return NULL;
    return left ? left : right;
}
```

Both iterative and recursive solution gives `O(n)` space complexity and `O(n)` time complexity. That's good enough in most cases (you will certainly get **accept** in leetcode). But their exists more efficient approaches, for the purpose of fun :), we will examine them in the next section.

## LCA in competitive programming

In competitive programming contest, you will often handle large inputs. Instead of finding the LCA of `p` and `q` (we call this **one query**), you will need to handle many such queries. If we simply use the above approach, each query takes `O(n)` time (say there are `m` such queries), that would take `O(nm)`, which is too slow.

However, we can improve our algorithm to `O(logn)` per query.

// TODO

```cpp
// parent[u][k] is the 2^k-th parent of u
void preprocess() {
    for (int i = 0; i < n; i++) {
        // assume parent[i][0] (the parent of i) is already filled in
        for (int j = 1; (1<<j) < n; j++) {
            parent[i][j] = -1;
        }
    }

    // fill in the parent for each power of two up to n
    for (int j = 1; (1<<j) < n; j++) {
        for (int i = 0; i < n; i++) {
            if (parent[i][j-1] != -1) {
                // the 2^j-th parent is the 2^(j-1)-th parent of the 2^(j-1)-th parent
                parent[i][j] = parent[parent[i][j-1]][j-1];
            }
        }
    }
}


int lca (int u, int v) {
    // make sure u is deeper than v
    if (depth[u] < depth[v]) swap(u,v);
    
    // log[i] holds the largest k such that 2^k <= i
    for (int i = log[depth[u]]; i >= 0; i--) {
        // repeatedly raise u by the largest possible power of two until it is the same depth as v
        if (depth[u] - (1<<i) >= depth[v]) u = parent[u][i]; 
    }

    if (u == v) return u;

    for (i = log[depth[u]]; i >= 0; i--)
        if (parent[u][i] != -1 && parent[u][i] != parent[v][i]) {
            // raise u and v as much as possible without having them coincide
            // this is important because we're looking for the lowest common ancestor, not just any
            u = parent[u][i];
            v = parent[v][i];
    }

    // u and v are now distinct but have the same parent, and that parent is the LCA
    return parent[u][0];
}
```
