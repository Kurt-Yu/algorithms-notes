[Leetcode 105. Construct Binary Tree from Preorder and Postorder Traversal](https://leetcode.com/problems/construct-binary-tree-from-preorder-and-postorder-traversal/)

```cpp
TreeNode* helper(queue<int>& preorder, vector<int>& inorder, int i, int j) {
    if (i > j) return NULL;
    
    auto root = new TreeNode(preorder.front());
    preorder.pop();
    int p = find(inorder.begin(), inorder.end(), root->val) - inorder.begin();
    root->left = helper(preorder, inorder, i, p -1);
    root->right = helper(preorder, inorder, p + 1, j);
    return root;
}

TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    queue<int> temp;
    for (auto& p : preorder) temp.push(p);
    return helper(temp, inorder, 0, inorder.size() - 1);
}
```

Since `vector` doesn't have `pop_front()` function. 
We first convert it to a `queue` and pass it to further process.

[Go Back](tree/tree-recursion?id=exercise)