[Leetcode 116. Populating Next Right Pointers in Each Node](https://leetcode.com/problems/populating-next-right-pointers-in-each-node/)

```cpp
Node* connect(Node* root) {
    Node *prev = root, *curr;
    while (prev) {
        curr = prev;
        while (curr && curr->left) {
            curr->left->next = curr->right;
            if (curr->next) curr->right->next = curr->next->left;
            curr = curr->next;
        }
        prev = prev->left;
    }
    
    return root;
}
```

[Go Back](tree/tree-traversal?id=exercises)