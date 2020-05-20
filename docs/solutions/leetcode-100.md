[Leetcode 100. Same Tree](https://leetcode.com/problems/same-tree/)
> Given two binary trees, write a function to check if they are the same or not.

```cpp
bool isSameTree(TreeNode* p, TreeNode* q) {
    if (!p && !q) return true;
    if (!p || !q) return false;
    return p->val == q->val ? isSameTree(p->left, q->left) && isSameTree(p->right, q->right) : false;      
}
```

[Go Back](tree/tree-recursion?id=exercise)