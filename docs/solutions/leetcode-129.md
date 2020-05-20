[Leetcode 129. Sum Root to Leaf Numbers](https://leetcode.com/problems/sum-root-to-leaf-numbers/)

**Idea:** BFS traversal, and accumulate (sum up) current node value to their children.

```cpp
int sumNumbers(TreeNode* root) {
    if (!root) return 0;
    queue<TreeNode*> q;
    q.push(root);
    int res = 0;
    
    while (!q.empty()) {
        for (int i = q.size(); i > 0; --i) {
            auto node = q.front();
            q.pop();
            if (node->left) {
                node->left->val += node->val * 10;
                q.push(node->left);
            }
            if (node->right) {
                node->right->val += node->val * 10;
                q.push(node->right);
            }
            if (!node->left && !node->right) res += node->val;
        }
    }
    return res;
}
```

[Go Back](tree/tree-path-sum?id=exercises)