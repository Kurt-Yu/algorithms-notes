[Leetcode 107. Binary Tree Level Order Traversal II](https://leetcode.com/problems/binary-tree-level-order-traversal-ii/)

```cpp
vector<vector<int>> levelOrderBottom(TreeNode* root) {
    if (!root) return {};
    queue<TreeNode*> q;
    vector<vector<int>> res;
    q.push(root);
    
    while (!q.empty()) {
        vector<int> children;
        for (int i = q.size(); i > 0; --i) {
            auto node = q.front();
            q.pop();
            children.push_back(node->val);
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        res.push_back(children);
    }
    reverse(res.begin(), res.end());
    return res;
}
```

[Go Back](tree/tree-traversal?id=exercises)