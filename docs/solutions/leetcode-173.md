[Leetcode 173. Binary Search Tree Iterator](https://leetcode.com/problems/binary-search-tree-iterator/)

```cpp
class BSTIterator {
    vector<int> inorder;
    int index = 0;
    
public:
    void helper(TreeNode* root, vector<int>& inorder) {
        if (!root) return;
        helper(root->left, inorder);
        inorder.push_back(root->val);
        helper(root->right, inorder);
    }
    
    BSTIterator(TreeNode* root) {
        helper(root, inorder);
    }
    
    /** @return the next smallest number */
    int next() {
        return inorder[index++];
    }
    
    /** @return whether we have a next smallest number */
    bool hasNext() {
        return index < inorder.size();
    }
};
```

[Go Back](tree/tree-traversal?id=exercises)