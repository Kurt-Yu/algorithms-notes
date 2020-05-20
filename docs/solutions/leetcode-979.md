[Leetcode 979. Distribute Coins in Binary Tree](https://leetcode.com/problems/distribute-coins-in-binary-tree/)

> Given the root of a binary tree with N nodes, each node in the tree has node.val coins, and there are N coins total.

> In one move, we may choose two adjacent nodes and move one coin from one node to another.  (The move may be from parent to child, or from child to parent.)

> Return the number of moves required to make every node have exactly one coin.

Standard recusive problem.
```cpp
int helper(TreeNode* root, int& res) {
    if (!root) return 0;
    int left = helper(root->left, res);
    int right = helper(root->right, res);
    res += abs(left) + abs(right);
    return root->val + left + right - 1;
}


int distributeCoins(TreeNode* root) {
    int res = 0;
    helper(root, res);
    return res;
}
```

[Go Back](tree/tree-recursion?id=exercise)