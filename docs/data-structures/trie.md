# Trie (Prefix Tree)

+ [Leetcode 208. Implement Trie (Prefix Tree)](https://leetcode.com/problems/implement-trie-prefix-tree/)

### [Leetcode 208. Implement Trie (Prefix Tree)](https://leetcode.com/problems/implement-trie-prefix-tree/)
```cpp
class Node {
public:
    Node* next[26];
    bool isword;
    
    Node() {
        memset(next, 0, sizeof(next));
        isword = false;
    }
};

class Trie {
public:
    Node* root;
    
    /** Initialize your data structure here. */
    Trie() {
        root = new Node();
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        Node* p = root;
        for (auto w : word) {
            if (p->next[w - 'a'] == NULL) p->next[w - 'a'] = new Node();
            p = p->next[w - 'a'];
        }
        p->isword = true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        Node* p = root;
        for (auto w : word) {
            if (p->next[w - 'a'] == NULL) return false;
            p = p->next[w - 'a'];
        }
        return p->isword;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        Node* p = root;
        for (auto w : prefix) {
            if (p->next[w - 'a'] == NULL) return false;
            p = p->next[w - 'a'];
        }
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
```

?> Note that the `Node* next[26]` array can also be replaced by a map: `unordered_map<int, Node*> next;`. But this would be about `30%` slower.

