[Leetcode 230. Kth Smallest Element in a BST](https://leetcode.com/problems/kth-smallest-element-in-a-bst/)


Standard in-order traversal
```cpp
void helper(TreeNode* root, vector<int>& res) {
    if (!root) return;
    helper(root->left, res);
    res.push_back(root->val);
    helper(root->right, res);
}

int kthSmallest(TreeNode* root, int k) {
    vector<int> res;
    helper(root, res);
    return res[k - 1];
}
```

[Go Back](tree/tree-traversal?id=exercises)