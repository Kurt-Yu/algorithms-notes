# Tree Recursion

When we talk about trees, we commonly refer to binary tree, in which every node of the tree can have two children maximum. This property brings some interesting problems that can be naturallu solved by recursion, such as computing the height of the tree, mirror a binary tree. We will examine some common recusive pattern on trees in this article, hopefully this can help you get familiar with tree recursion.

## Height & Depth & Check Properties

### [Leetcode 104. Maximum Depth of Binary Tree](https://leetcode.com/problems/maximum-depth-of-binary-tree/)
> Given a binary tree, find its maximum depth.
```cpp
int maxDepth(TreeNode* root) {
    return root? 1 + max(maxDepth(root->left), maxDepth(root->right)) : 0;
}
```

### [Leetcode 226. Invert Binary Tree](https://leetcode.com/problems/invert-binary-tree/)
> Invert a binary tree.
```cpp
TreeNode* invertTree(TreeNode* root) {
    if (!root) return NULL;
    auto temp = invertTree(root->left);
    root->left = invertTree(root->right);
    root->right = temp;
    return root;
}
```

## Construct/Build Tree

### [Leetcode 617. Merge Two Binary Trees](https://leetcode.com/problems/merge-two-binary-trees/)
> Merge two binary trees into a new binary tree.
```cpp
TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
    if (!t1 && !t2) return NULL;
    else if (!t1) return t2;
    else if (!t2) return t1;
    TreeNode* root = new TreeNode(t1->val + t2->val);
    root->left = mergeTrees(t1->left, t2->left);
    root->right = mergeTrees(t1->right, t2->right);
    return root;
}
```

### [Leetcode 108. Convert Sorted Array to Binary Search Tree](https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/)
> Given an array where elements are sorted in ascending order, convert it to a height balanced BST.
```cpp
TreeNode* helper(vector<int>& nums, int i, int j) {
    if (i > j) return NULL;
    else if (i == j) return new TreeNode(nums[i]);
    int mid = i + (j - i) / 2;
    auto root = new TreeNode(nums[mid]);
    root->left = helper(nums, i, mid - 1);
    root->right = helper(nums, mid + 1, j);
    return root;
}


TreeNode* sortedArrayToBST(vector<int>& nums) {
    return helper(nums, 0, nums.size() - 1);
}
```

### [Leetcode 106. Construct Binary Tree from Inorder and Postorder Traversal](https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/)
> Given inorder and postorder traversal of a tree, construct the binary tree.
```cpp
TreeNode* helper(vector<int>& inorder, vector<int>& postorder, int i, int j) {
    if (i > j) return NULL;
    
    auto root = new TreeNode(postorder.back());
    postorder.pop_back();
    int p = find(inorder.begin(), inorder.end(), root->val) - inorder.begin();
    root->right = helper(inorder, postorder, p + 1, j);
    root->left = helper(inorder, postorder, i, p - 1);
    return root;
}

TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
    return helper(inorder, postorder, 0, inorder.size() - 1);
}
```
?> We used a small trick here. If we would write recursive relation clearly, then the indexes of `postorder` would also change correspondingly. But here we process `root->right` first instead of `root->left`, after that, the only thing we need to do is popping the last element off. This is a much easier and cleaner implementation. 


### [Leetcode 222. Count Complete Tree Nodes](https://leetcode.com/problems/count-complete-tree-nodes/)
> Given a complete binary tree, count the number of nodes.

This problem requires a bit extra thinking. Instead of naively recursive on the left and right subtree, we also need to keep track of the current height. Compare the left height and right height, calculate the number of nodes using `pow(2, height) - 1` (due to the property of complete binary trees).

```cpp
int countNodes(TreeNode* root) {
    if (!root) return 0;
    int lh = 0, rh = 0;     // left height, right height
    TreeNode* left = root, *right = root;
    while (left) {
        lh++;
        left = left->left;
    }
    while (right) {
        rh++;
        right = right->right;
    }
    
    if (lh == rh) return pow(2, lh) - 1;
    return 1 + countNodes(root->left) + countNodes(root->right);
}
```

## Exercise:
+ [Leetcode 100. Same Tree](https://leetcode.com/problems/same-tree/), [[solution]](solutions/leetcode-100.md)
+ [Leetcode 101. Symmetric Tree](https://leetcode.com/problems/symmetric-tree/submissions/), [[solution]](solutions/leetcode-101.md)
+ [Leetcode 687. Longest Univalue Path](https://leetcode.com/problems/longest-univalue-path/), [[solution]](solutions/leetcode-687.md)
+ [Leetcode 105. Construct Binary Tree from Preorder and Postorder Traversal](https://leetcode.com/problems/construct-binary-tree-from-preorder-and-postorder-traversal/), [[solution]](solutions/leetcode-106.md)
+ [Leetcode 654. Maximum Binary Tree](https://leetcode.com/problems/maximum-binary-tree/), [[solution]](solutions/leetcode-654.md)
+ [Leetcode 110. Balanced Binary Tree](https://leetcode.com/problems/balanced-binary-tree/), [[solution]](solutions/leetcode-110.md)
+ [Leetcode 543. Diameter of Binary Tree](https://leetcode.com/problems/diameter-of-binary-tree/), [[solution]](solutions/leetcode-543.md)
+ [Leetcode 979. Distribute Coins in Binary Tree](https://leetcode.com/problems/distribute-coins-in-binary-tree/), [[solution]](solutions/leetcode-979.md)
