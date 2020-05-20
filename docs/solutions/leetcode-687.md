[Leetcode 687. Longest Univalue Path](https://leetcode.com/problems/longest-univalue-path/)

```cpp
int helper(TreeNode* root, int& res) {
    int l = root->left ? helper(root->left, res) : 0;
    int r = root->right ? helper(root->right, res) : 0;
    int left = root->left && root->left->val == root->val ? l + 1 : 0;
    int right = root->right && root->right->val == root->val ? r + 1 : 0;
    res = max(res, left + right);
    return max(left, right);
}

int longestUnivaluePath(TreeNode* root) {
    int res = 0;
    if (root) helper(root, res);
    return res;
}
```

[Go Back](tree/tree-recursion?id=exercise)