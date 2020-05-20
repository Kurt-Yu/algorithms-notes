[Leetcode 429. N-ary Tree Level Order Traversal](https://leetcode.com/problems/n-ary-tree-level-order-traversal/)

```cpp
vector<vector<int>> levelOrder(Node* root) {
    if (!root) return {};
    queue<Node*> q;
    vector<vector<int>> res;
    q.push(root);
    
    while (!q.empty()) {
        vector<int> children;
        for (int i = q.size(); i > 0; --i) {
            auto node = q.front();
            q.pop();
            children.push_back(node->val);
            for (auto& c : node->children) q.push(c);
        }
        res.push_back(children);
    }
    return res;
}
```

[Go Back](tree/tree-traversal?id=exercises)