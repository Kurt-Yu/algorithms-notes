[Leetcode 101. Symmetric Tree](https://leetcode.com/problems/symmetric-tree/submissions/)

```cpp
bool helper(TreeNode* root1, TreeNode* root2) {
    if (!root1 && !root2) return true;
    if (!root1 || !root2) return false;
    return root1->val == root2->val && helper(root1->left, root2->right) && helper(root1->right, root2->left);
}

bool isSymmetric(TreeNode* root) {
    if (!root) return true;
    return helper(root->left, root->right);
}
```

[Go Back](tree/tree-recursion?id=exercise)
