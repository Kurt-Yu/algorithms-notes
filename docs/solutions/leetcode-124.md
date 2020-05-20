[Leetcode 124. Binary Tree Maximum Path Sum](https://leetcode.com/problems/binary-tree-maximum-path-sum/)

```cpp
int helper(TreeNode* root, int& res) {
    if (!root) return 0;
    int l = helper(root->left, res);
    int r = helper(root->right, res);
    l = max(l, 0), r = max(r, 0);
    res = max(res, l + r + root->val);
    return root->val += max(l, r);
}

int maxPathSum(TreeNode* root) {
    int res = INT_MIN;
    helper(root, res);
    return res;
}
```

[Go Back](tree/tree-path-sum?id=exercises)