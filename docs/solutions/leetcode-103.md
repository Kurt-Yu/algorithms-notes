[Leetcode 103. Binary Tree Zigzag Level Order Traversal](https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/)

```cpp
vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    if (!root) return {};
    queue<TreeNode*> q;
    vector<vector<int>> res;
    q.push(root);
    
    int level = 0;
    while (!q.empty()) {
        vector<int> children;
        for (int i = q.size(); i > 0; --i) {
            auto node = q.front();
            q.pop();
            children.push_back(node->val);
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        if (level & 1) reverse(children.begin(), children.end());
        res.push_back(children);
        ++level;
    }
    return res;
}
```

[Go Back](tree/tree-traversal?id=exercises)