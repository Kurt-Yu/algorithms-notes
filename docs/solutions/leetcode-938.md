[Leetcode 938. Range Sum of BST](https://leetcode.com/problems/range-sum-of-bst/)

> Given the `root` node of a binary search tree, return the sum of values of all nodes with value between `L` and `R` (inclusive).

```cpp
int rangeSumBST(TreeNode* root, int L, int R) {
    if (!root) return 0;
    if (root->val < L) return rangeSumBST(root->right, L, R);
    else if (root->val > R) return rangeSumBST(root->left, L, R);
    return root->val + rangeSumBST(root->left, L, R) + rangeSumBST(root->right, L, R);
}
```

[Go Back](tree/binary-search-tree?id=exercise)