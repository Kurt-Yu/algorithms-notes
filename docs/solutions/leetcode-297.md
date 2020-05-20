[Leetcode 297. Serialize and Deserialize Binary Tree](https://leetcode.com/problems/serialize-and-deserialize-binary-tree/)

```cpp
class Codec {
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        ostringstream out;
        preorder(root, out);
        return out.str();
    }
    
    
    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        istringstream in(data);
        return build(in);
    }
    
private:
    void preorder(TreeNode* root, ostringstream& out) {
        if (!root) out << "# ";
        else {
            out << root->val << ' ';
            preorder(root->left, out);
            preorder(root->right, out);
        }
    }
    
    TreeNode* build(istringstream& in) {
        string val;
        in >> val;
        if (val == "#") return nullptr;
        TreeNode* root = new TreeNode(stoi(val));
        root->left = build(in);
        root->right = build(in);
        return root;
    }
};
```

**Idea:** Preorder traversal and use space as delimeter to split strings.

[Go Back](tree/tree-traversal?id=exercises)