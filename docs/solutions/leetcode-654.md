[Leetcode 654. Maximum Binary Tree](https://leetcode.com/problems/maximum-binary-tree/)

```cpp
TreeNode* helper(vector<int>& nums, int i, int j) {
    if (i > j) return NULL;
    if (i == j) return new TreeNode(nums[i]);
    int index = 0, m = INT_MIN;
    for (int p = i; p <= j; ++p) {
        if (nums[p] > m) index = p, m = nums[p];
    }
    auto root = new TreeNode(m);
    root->left = helper(nums, i, index - 1);
    root->right = helper(nums, index + 1, j);
    return root;
}   

TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
    return helper(nums, 0, nums.size() - 1);
}
```

?> The solution is pretty straightforward, find the max value and recurisvely call the left and right half. One thing worth noticing is that we are not finding maximum element in the entire array, since the array start and end indexes are changing in each recursive iteration.
 
[Go Back](tree/tree-recursion?id=exercise)