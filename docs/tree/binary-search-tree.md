# Binary Search Tree

**Binary Search Tree (BST)** is a special kind of binary tree which has the following properties:
+ The left subtree only contains nodes with value smaller than the root value.
+ The right subtree only contains nodes with value larger than the root value.
+ The left and right subtree are BSTs as well.

Due to this fact, there exist some interesting problems, such as determine if a given tree is a BST, or what's the lowest common ancestor (LCA) of two nodes in BST. We will examine some of the problems below and hopefully you can derive some insights/techniques for solving BST problems.

+ [Leetcode 98. Validate Binary Search Tree](https://leetcode.com/problems/validate-binary-search-tree/)

---
## Check Properties

### [Leetcode 98. Validate Binary Search Tree](https://leetcode.com/problems/validate-binary-search-tree/)
> Given a binary tree, determine if it is a valid binary search tree (BST).
```cpp
bool helper(TreeNode* root, TreeNode* left, TreeNode* right) {
    if (!root) return true;
    if ((left && root->val <= left->val) || (right && root->val >= right->val)) return false;
    return helper(root->left, left, root) && helper(root->right, root, right);
}

bool isValidBST(TreeNode* root) {
    return helper(root->left, NULL, NULL);
}
```

?> Note that if you are comparing `root->val` with `INT_MIN` and `INT_MAX`, that leads to a wrong answer. It is buggy becuase it fails the case when the input is just `[INT_MAX] or [INT_MIN]`. Here it's more natrual to use `TreeNode` instead of value.

Also, since the inorder traversal of a binary search tree is a increasing sequence. We can use this property to solve many BST problems.

```cpp
void helper(TreeNode* root, vector<int>& res) {
    if (!root) return;
    helper(root->left, res);
    res.push_back(root->val);
    helper(root->right, res);
}

bool isValidBST(TreeNode* root) {
    vector<int> res;
    helper(root, res);
    for (int i = 1; i < res.size(); ++i) if (res[i] <= res[i - 1]) return false;
    return true;
}
```

### [Leetcode 235. Lowest Common Ancestor of a Binary Search Tree](https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/)
> Given a binary search tree (BST), find the lowest common ancestor (LCA) of two given nodes in the BST.
```cpp
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root) return NULL;
    if (p->val > q->val) swap(p, q);
    if (root->val >= p->val && root->val <= q->val) return root;
    else if (root->val < p->val) return lowestCommonAncestor(root->right, p, q);
    return lowestCommonAncestor(root->left, p, q);
}
```
?> Note that `p` and `q` are not necessarily in order, we have to chech which one is smaller and which one is larger. That's why we need a *swap* in the second line.

### [Leetcode 669. Trim a Binary Search Tree](https://leetcode.com/problems/trim-a-binary-search-tree/)
> Given a binary search tree and the lowest and highest boundaries as L and R, trim the tree so that all its elements lies in `[L, R] (R >= L)`. You might need to change the root of the tree, so the result should return the new root of the trimmed binary search tree.

```cpp
TreeNode* trimBST(TreeNode* root, int L, int R) {
    if (!root) return NULL;
    if (root->val >= L && root->val <= R) {
        root->left = trimBST(root->left, L, R);
        root->right = trimBST(root->right, L, R);
    } else if (root->val < L) {
        return trimBST(root->right, L, R);
    } else {
        return trimBST(root->left, L, R);
    }
    return root;
}
```
Code is straightforward. Recursive relation should be easy to derive.

### [Leetcode 538. Convert BST to Greater Tree](https://leetcode.com/problems/convert-bst-to-greater-tree/)
> Given a Binary Search Tree (BST), convert it to a Greater Tree such that every key of the original BST is changed to the original key plus sum of all keys greater than the original key in BST.

This could be easily solve by inorder traversal. Chech [previous article](./tree/tree-traversal.md) if you are not familiar with it.
```cpp
void helper(TreeNode* root, vector<TreeNode*>& res) {
    if (!root) return;
    helper(root->left, res);
    res.push_back(root);
    helper(root->right, res);
}

TreeNode* convertBST(TreeNode* root) {
    vector<TreeNode*> res;
    helper(root, res);
    for (int i = res.size() - 2; i >= 0; --i) {
        res[i]->val += res[i + 1]->val;
    }
    return root;
}
```

However this is a bad version. It takes two passes. By adding a global variable `curr_sum`, we can get a nice one pass solution.

```cpp
int curr = 0;

void helper(TreeNode* root) {
    if (!root) return;
    helper(root->right);
    root->val += curr;
    curr = root->val;
    helper(root->left);
}

TreeNode* convertBST(TreeNode* root) {
    helper(root);
    return root;
}
```

## Construct/Build Tree

### [Leetcode 96. Unique Binary Search Trees](https://leetcode.com/problems/unique-binary-search-trees/)
> Given `n`, how many structurally unique `BST's` (binary search trees) that store values `1 ... n`?

**Idea:** Using this formular: `f(n) = f(1) + f(2) + ... + f(n)`, where `f(i)` is the total number of trees if the root is value `i`. 

For exmple, given `n = 3`, then there are three cases: 
1. root value is 1, there is only 1 tree: `1->right = 2, 2->right = 3`.
2. root value is 2, there is only 1 tree: `2->left = 1, 2->right = 3`.
3. root value is 3, there is only 1 tree: `3->left = 2, 2->left = 1`.

Thus, `f(3) = f(1) + f(2) + f(3) = 1 + 1 + 1 = 3`.

```cpp
int numTrees(int n) {
    int f[n + 1];
    f[0] = f[1] = 1;
    for (int i = 2; i <= n; ++i) {
        int res = 0;
        for (int j = 1; j <= i; ++j) res += f[j - 1] * f[i - j];
        f[i] = res;
    }
    return f[n];
}
```

### [Leetcode 95. Unique Binary Search Trees II](https://leetcode.com/problems/unique-binary-search-trees-ii/)
> Given an integer `n`, generate all structurally unique BST's (binary search trees) that store values `1 ... n`.

**Idea:** 
 
## Modify Node


## Exercise
+ [Leetcode 938. Range Sum of BST](https://leetcode.com/problems/range-sum-of-bst/), [[solution]](solutions/leetcode-938.md)
