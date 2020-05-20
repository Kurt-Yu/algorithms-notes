[Leetcode 110. Balanced Binary Tree](https://leetcode.com/problems/balanced-binary-tree/)

```cpp
int helper(TreeNode* root) {
    if (!root) return 0;
    int left = helper(root->left);
    int right = helper(root->right);
    if (left == -1 || right == -1 || abs(left - right) > 1) return -1;
    return 1 + max(left, right); 
}


bool isBalanced(TreeNode* root) {
    return helper(root) != -1;
}
```

[Go Back](tree/tree-recursion?id=exercise)