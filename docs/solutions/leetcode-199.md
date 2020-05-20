[Leetcode 199. Binary Tree Right Side View](https://leetcode.com/problems/binary-tree-right-side-view/)

```cpp
vector<int> rightSideView(TreeNode* root) {
    if (!root) return {};
    vector<int> res;
    queue<TreeNode*> q;
    q.push(root);
    
    while (!q.empty()) {
        vector<int> temp;
        for (int i = q.size(); i > 0; --i) {
            auto node = q.front();
            q.pop();
            temp.push_back(node->val);
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        res.push_back(temp.back());
    }
    return res;
}
```

[Go Back](tree/tree-traversal?id=exercises)