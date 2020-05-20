[Leetcode 543. Diameter of Binary Tree](https://leetcode.com/problems/diameter-of-binary-tree/)

> Given a binary tree, you need to compute the length of the diameter of the tree. The diameter of a binary tree is the length of the longest path between any two nodes in a tree. This path may or may not pass through the root.

```cpp
int helper(TreeNode* root, int& res) {
    if (!root) return 0;
    int left = helper(root->left, res);
    int right = helper(root->right, res);
    res = max(res, left + right);
    return 1 + max(left, right);
}

int diameterOfBinaryTree(TreeNode* root) {
    int res = 0;
    helper(root, res);
    return res;
}
```

[Go Back](tree/tree-recursion?id=exercise)