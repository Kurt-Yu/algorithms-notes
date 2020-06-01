# 链表

+ [Leetcode 19. Remove Nth Node From End of List](https://leetcode.com/problems/remove-nth-node-from-end-of-list/)
+ [Leetcode 83. Remove Duplicates from Sorted List](https://leetcode.com/problems/remove-duplicates-from-sorted-list/)
+ [Leetcode 206. Reverse Linked List](https://leetcode.com/problems/reverse-linked-list/)
+ [Leetcode 92. Reverse Linked List II](https://leetcode.com/problems/reverse-linked-list-ii/)
+ [Leetcode 61. Rotate List](https://leetcode.com/problems/rotate-list/)
+ [Leetcode 143. Reorder List](https://leetcode.com/problems/reorder-list/)
+ [Leetcode 21. Merge Two Sorted Lists](https://leetcode.com/problems/merge-two-sorted-lists/)
+ [Leetcode 160. Intersection of Two Linked Lists](https://leetcode.com/problems/intersection-of-two-linked-lists/)
+ [Leetcode 141. Linked List Cycle](https://leetcode.com/problems/linked-list-cycle/)
+ [Leetcode 147. Insertion Sort List](https://leetcode.com/problems/insertion-sort-list/)
+ [Leetcode 138. Copy List with Random Pointer](https://leetcode.com/problems/copy-list-with-random-pointer/description/)
+ [Leetcode 142. Linked List Cycle II](https://leetcode.com/problems/linked-list-cycle-ii/)

## 删除节点
### [Leetcode 19. Remove Nth Node From End of List](https://leetcode.com/problems/remove-nth-node-from-end-of-list/)
维护两个指针，t1 和 t2，先让 t2 走 n 个距离，然后 one pass 整个链表。最后 t1 停下来的地方就是我们需要的地方。

?>注意我们在代码里先创建了一个 dummy 节点。这样做的目的是为了处理边界条件，即 n == list.size() 的时候。这也是一个很常见的技巧，经常出现在链表题里。
```cpp
ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode* dummy = new ListNode(0);
    dummy->next = head;
    auto t1 = dummy, t2 = dummy;
    
    for (int i = 0; i < n; ++i) {
        t2 = t2->next;
    }
    
    while (t2->next) {
        t1 = t1->next;
        t2 = t2->next;
    }
    
    t1->next = t1->next->next;
    return dummy->next;
}
```

### [Leetcode 83. Remove Duplicates from Sorted List]((https://leetcode.com/problems/remove-duplicates-from-sorted-list/))
思路很简单，即遍历整个链表，如果当前 node 的 val 等于前一个 node 的 val，那么 skip 当前的 node，如果不等于，则把它添加到 result 链表里。实现起来要注意点与点之间的关系，不要搞混了。
```cpp
ListNode* deleteDuplicates(ListNode* head) {
    if (!head) return NULL;
    
    ListNode* res = head, *curr = head;
    head = head->next;
    while (head) {
        while (head && head->val == curr->val) head = head->next;
        curr->next = head;
        curr = curr->next;
    }
    return res;
}
```

## Reverse 链表

### [Leetcode 206. Reverse Linked List](https://leetcode.com/problems/reverse-linked-list/)
```cpp
ListNode* reverseList(ListNode* head) {
    ListNode* prev = NULL, *curr = head;
    while (curr) {
        auto next = curr->next;
        curr->next = prev;
        prev = curr, curr = next;
    }
    return prev;
}
```

### [Leetcode 92. Reverse Linked List II](https://leetcode.com/problems/reverse-linked-list-ii/)
```cpp
ListNode* reverseBetween(ListNode* head, int m, int n) {
    if (m == n || !head) return head;
    
    ListNode* res = new ListNode(0);
    res->next = head;
    auto curr = res;
    for (int i = 0; i < m - 1; ++i) {
        curr = curr->next;
    }
    auto tail = curr->next;
    
    for (int i = 0; i < n - m; ++i) {
        auto next = curr->next;
        curr->next = tail->next;
        tail->next = tail->next->next;
        curr->next->next = next;
    }
    
    return res->next;
}
```

### [Leetcode 61. Rotate List](https://leetcode.com/problems/rotate-list/)
```cpp
ListNode* rotateRight(ListNode* head, int k) {
    if (!head) return NULL;
    
    int cnt = 1;
    auto curr = head;
    while (curr && curr->next) {
        curr = curr->next;
        cnt++;
    }
    curr->next = head;
    k %= cnt;
    
    curr = head;
    for (int i = 0; i < cnt - k - 1; ++i) {
        curr = curr->next;
    }
    auto next = curr->next;
    curr->next = NULL;
    head = next;
    return head;
}
```

### [Leetcode 143. Reorder List](https://leetcode.com/problems/reorder-list/)
```cpp
void reorderList(ListNode* head) {
    if (!head || !head->next) return;
    
    // find the middle node
    ListNode* middle;
    auto fast = head, slow = head;
    while (fast && fast->next) {
        middle = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    middle->next = NULL;
    
    // reverse the second half
    ListNode* prev = NULL, *curr = slow;
    while (curr) {
        auto next = curr->next;
        curr->next = prev;
        prev = curr, curr = next;
    }
    
    // merge two lists
    while (head && prev) {
        auto first = head->next, second = prev->next;
        head->next = prev;
        if (first) prev->next = first;
        head = first, prev = second;
    }
}
```

### [Leetcode 21. Merge Two Sorted Lists](https://leetcode.com/problems/merge-two-sorted-lists/)
```cpp
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode* curr = new ListNode(0);
    auto res = curr;
    while (l1 && l2) {
        if (l1->val < l2->val) curr->next = l1, l1 = l1->next;
        else curr->next = l2, l2 = l2->next;
        curr = curr->next;
    } 
    if (l1) curr->next = l1;
    else curr->next = l2;
    return res->next;
}
```

### [Leetcode 160. Intersection of Two Linked Lists](https://leetcode.com/problems/intersection-of-two-linked-lists/)

```cpp
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
    if (!headA || !headB) return NULL;
    
    auto a = headA, b = headB;
    while (a != b) {
        a = a ? a->next : headB;
        b = b ? b->next : headA;
    }
    return a;
}
```

### [Leetcode 141. Linked List Cycle](https://leetcode.com/problems/linked-list-cycle/)
```cpp
bool hasCycle(ListNode *head) {
    if (!head) return false;
    
    auto slow = head, fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }
    return false;
}
```

### [Leetcode 147. Insertion Sort List](https://leetcode.com/problems/insertion-sort-list/)
```cpp
ListNode* insertionSortList(ListNode* head) {
    ListNode* dummy = new ListNode(0);
    dummy->next = head;
    auto curr = head, prev = dummy;
    
    while (curr) {
        if (curr->next && curr->next->val < curr->val) {
            while (prev->next && prev->next->val < curr->next->val) {
                prev = prev->next;
            }
            auto next = prev->next;
            prev->next = curr->next;
            curr->next = curr->next->next;
            prev->next->next = next;
            prev = dummy;
        } else {
            curr = curr->next;
        }
    }
    return dummy->next;
}
```

### [Leetcode 138. Copy List with Random Pointer](https://leetcode.com/problems/copy-list-with-random-pointer/description/)
```cpp
Node* copyRandomList(Node* head) {
    if (!head) return NULL;
    
    // step1: copy a duplicate node immediately after current node
    Node* curr = head;
    while (curr) {
        auto next = curr->next;
        curr->next = new Node(curr->val);
        curr->next->next = next;
        curr = next;
    }
    
    // step2: copy random pointer
    curr = head;
    while (curr) {
        if (curr->random) {
            curr->next->random = curr->random->next;
        }
        curr = curr->next->next;
    }
    
    // step3: re-store the original list and duplicated list
    curr = head;
    auto res = curr->next;
    auto temp = res;
    while (temp->next) {
        curr->next = curr->next->next;
        curr = curr->next;
        
        temp->next = temp->next->next;
        temp = temp->next;
    }
    curr->next = curr->next->next;
    
    return res;
}
```

### [Leetcode 142. Linked List Cycle II](https://leetcode.com/problems/linked-list-cycle-ii/)
```cpp
ListNode *detectCycle(ListNode *head) {
    auto slow = head, fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) break;
    }
    
    if (!fast || !fast->next) return NULL;
    
    slow = head;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }
    return slow;
}
```