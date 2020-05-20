# Tree Path Sum Problems

When dealing with trees, we often care about the sum of a certain path. There are at least ten problems on leetcode that either asks the smallest sum of a certain path or the largest. This is an important topic and it is frequently occured in real technical interviews. Many of them share similar ideas, I thought it would nice to examine those problems all in once. Hopefully you could develop some systematic ways to deal with this kind of problems.

You can define the word `path` in different ways. A path can be defined as a `root-to-leaf` path, which is the simplest case. But in fact, it doesn't have to start with the `root`, or end with the `leaf`, it doesn't have to go downwards all the time. Those are much more harder senarios. We will start with the simplest case and gradually extend to harder versions.

## [Leetcode 112. Path Sum](https://leetcode.com/problems/path-sum/)
> Given a binary tree and a sum, determine if the tree has a root-to-leaf path such that adding up all the values along the path equals the given sum.

```cpp
bool hasPathSum(TreeNode* root, int sum) {
    if (!root) return false;
    if (root && !root->left && !root->right && root->val == sum) return true;
    return hasPathSum(root->left, sum - root->val) || hasPathSum(root->right, sum - root->val);
}
```
?> Notice that the terminate condition for recursion is `sum == root->val && root is leaf`. Some people might write it as `root == NULL && sum == 0`, but this condition would fail if the test case is `tree = [], sum = 0`. Think carefully about the corner case before actually coding, this is important in real interviews.

## [Leetcode 113. Path Sum II](https://leetcode.com/problems/path-sum-ii/)
> Given a binary tree and a sum, find all root-to-leaf paths where each path's sum equals the given sum.

This problem is essentially the same as the above. Instead of checking `root->val == sum` in the recursive call, we actually store each node value in the `temp` vector. If the condition meets, then we know this `temp` satisifies the problem requirement.

```cpp
void helper(TreeNode* root, int sum, vector<int>& temp, vector<vector<int>>& res) {
    if (!root) return;

    temp.push_back(root->val);
    if (!root->left && !root->right && sum == root->val) res.push_back(temp);
    helper(root->left, sum - root->val, temp, res);
    helper(root->right, sum - root->val, temp, res);
    temp.pop_back();
}

vector<vector<int>> pathSum(TreeNode* root, int sum) {
    vector<vector<int>> res;
    vector<int> temp;
    helper(root, sum, temp, res);
    return res;
}
```

## [Leetcode 437. Path Sum III](https://leetcode.com/problems/path-sum-iii/)
> You are given a binary tree in which each node contains an integer value.
> Find the number of paths that sum to a given value.
> The path does not need to start or end at the root or a leaf, but it must go downwards (traveling only from parent nodes to child nodes).


?> The following solution implemented a commonly used problem solving technique called `prefix sum`. This problem is different from the above two because the path doesn't have to start with root and end with leaf. Because of this, we can use a hashmap to helper us store the `current sum`. Then the number of path is `prefix[curr - sum]`, where `curr - sum` denotes prefix sum.

?> Notice that in the last line of `helper` function, don't forget to decrease the number of `prefix[curr]`. Because this node has been processed, and we pop this node and recusively call other branches. This is exactly the idea of **back-tracking**.

```cpp
void helper(TreeNode* root, int sum, int curr, int& res, unordered_map<int, int>& prefix) {
    if (!root) return;
    curr += root->val;
    res += prefix[curr - sum];
    
    prefix[curr]++;
    helper(root->left, sum, curr, res, prefix);
    helper(root->right, sum, curr, res, prefix);
    prefix[curr]--;
}

int pathSum(TreeNode* root, int sum) {
    int res = 0;
    unordered_map<int, int> prefix;
    prefix[0] = 1;
    helper(root, sum, 0, res, prefix);
    return res;
}
```

## [Leetcode 666. Path Sum IV](https://leetcode.com/problems/path-sum-iv/)

?> This is a standard tree traversal problem. The following solution uses `BFS` traversal. Insteading of checking `node->left and node->right`, we now use indexes to denote the parent-child relation. Left child should be `(level + 1) * 10 + pos * 2 - 1`, right child should be `(level + 1) * 10 + pos * 2`.

?> Accumulate the internal node value to its children, if the node has no children, then add this value to result.

```cpp
int pathSum(vector<int>& nums) {
    int res = 0;
    unordered_map<int, int> tree;
    for (auto& n : nums) tree[n / 10] = n % 10;
    
    for (auto& n : nums) {
        int level = n / 100, pos = (n / 10) % 10, val = n % 10;
        int left =  (level + 1) * 10 + pos * 2 - 1, right = (level + 1) * 10 + pos * 2;
        if (tree.find(left) != tree.end()) tree[left] += tree[n / 10];
        if (tree.find(right) != tree.end()) tree[right] += tree[n / 10];
        if (tree.find(left) == tree.end() && tree.find(right) == tree.end()) res += tree[n / 10];
    }
    return res;
}
```

## Exercises:
+ [Leetcode 129. Sum Root to Leaf Numbers](https://leetcode.com/problems/sum-root-to-leaf-numbers/), [[solution]](solutions/leetcode-129.md)
+ [Leetcode 124. Binary Tree Maximum Path Sum](https://leetcode.com/problems/binary-tree-maximum-path-sum/), [[solution]](solutions/leetcode-124.md)