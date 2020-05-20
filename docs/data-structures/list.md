# List

+ [Leetcode 2. Add Two Numbers](https://leetcode.com/problems/add-two-numbers/)
+ [Leetcode 21. Merge Two Sorted Lists](https://leetcode.com/problems/merge-two-sorted-lists/)
+ [Leetcode 23. Merge k Sorted Lists](https://leetcode.com/problems/merge-k-sorted-lists/)
+ [Leetcode 206. Reverse Linked List](https://leetcode.com/problems/reverse-linked-list/) 


+ [Leetcode 141. Linked List Cycle](https://leetcode.com/problems/linked-list-cycle/)
+ [Leetcode 142. Linked List Cycle II](https://leetcode.com/problems/linked-list-cycle-ii/)
+ [Leetcode 287. Find the Duplicate Number](https://leetcode.com/problems/find-the-duplicate-number/)
+ [Leetcode 202. Happy Number](https://leetcode.com/problems/happy-number/)


 
## List Traversal

### [Leetcode 2. Add Two Numbers](https://leetcode.com/problems/add-two-numbers/)
```cpp
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    int t = 0;
    ListNode *curr = new ListNode(0);
    ListNode *res = curr;
    while (l1 || l2) {
        if (l1) t += l1->val, l1 = l1->next;
        if (l2) t += l2->val, l2 = l2->next;
        ListNode *newNode = new ListNode(t % 10);
        curr->next = newNode;
        curr = newNode;
        t /= 10;
    }
    
    if (t) curr->next = new ListNode(1);
    return res->next;
}
```

### [Leetcode 21. Merge Two Sorted Lists](https://leetcode.com/problems/merge-two-sorted-lists/)
```cpp
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode *curr = new ListNode(0);
    ListNode *res = curr;
    
    while (l1 && l2) {
        if (l1->val <= l2->val) {
            curr->next = l1;
            l1 = l1->next;
        } else {
            curr->next = l2;
            l2 = l2->next;
        }
        curr = curr->next;
    }
    
    if (l1) curr->next = l1;
    else curr->next = l2;
    
    return res->next;
}
```

### [Leetcode 23. Merge k Sorted Lists](https://leetcode.com/problems/merge-k-sorted-lists/)

**Method 1:**
This problem can be solved by divide and conquer. Use the `merge two sorted lists` as a subtask and recursively call on the `k` lists.
```cpp
ListNode* mergeTwoLists(ListNode *l1, ListNode* l2) {
    ListNode *curr = new ListNode(0);
    ListNode *res = curr;
    while (l1 && l2) {
        if (l1->val <= l2->val) curr->next = l1, l1 = l1->next;
        else curr->next = l2, l2 = l2->next;
        curr = curr->next;
    }
    
    if (l1) curr->next = l1;
    else curr->next = l2;
    return res->next;
}

ListNode* helper(vector<ListNode*>& lists, int i, int j) {
    if (i == j) return lists[i];
    int mid = i + (j - i) / 2;
    auto left = helper(lists, i, mid);
    auto right = helper(lists, mid + 1, j);
    return mergeTwoLists(left, right);
}

ListNode* mergeKLists(vector<ListNode*>& lists) {
    if (lists.size() == 0) return NULL;
    return helper(lists, 0, lists.size() - 1);
}
```

**Method 2:**
We can also use a heap (priority queue), store the head nodes of all lists and gradually update the heap based on their values.
```cpp
ListNode* mergeKLists(vector<ListNode*>& lists) {
    auto cmp = [](const ListNode* a, const ListNode* b) { return a->val > b->val; };
    priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> pq(cmp);
    
    for (auto node : lists) if (node) pq.push(node);
    
    auto curr = new ListNode(0);
    auto res = curr;
    while (pq.size()) {
        auto first = pq.top();
        pq.pop();
        curr->next = first;
        curr = curr->next;
        if (first->next) pq.push(first->next);
    }
    
    return res->next;
}
```


### [Leetcode 206. Reverse Linked List](https://leetcode.com/problems/reverse-linked-list/) 
```cpp
ListNode* reverseList(ListNode* head) {
    ListNode *prev = NULL, *curr = head;
    while (curr) {
        ListNode *next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    
    return prev;
}
```

## Add / Delete / Sort Linked List

### [Leetcode ]
```cpp

```

## Cycle Detection

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

### [Leetcode 142. Linked List Cycle II](https://leetcode.com/problems/linked-list-cycle-ii/)
```cpp
ListNode *detectCycle(ListNode *head) {
    if (!head) return NULL;
    auto slow = head, fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) break;
    }
    
    if (!fast || !fast->next) return NULL;
    
    while (head != fast) {
        head = head->next;
        fast = fast->next;
    }
    return head;
}
```

### [Leetcode 287. Find the Duplicate Number](https://leetcode.com/problems/find-the-duplicate-number/)
```cpp
int findDuplicate(vector<int>& nums) {
    if (nums.size() == 0) return 0;
    int slow = nums[0], fast = nums[nums[0]];
    while (slow != fast) {
        slow = nums[slow];
        fast = nums[nums[fast]];
    }
    
    int head = 0;
    while (head != slow) {
        head = nums[head];
        slow = nums[slow];
    }
    return slow;
}
```

### [Leetcode 202. Happy Number](https://leetcode.com/problems/happy-number/)
**Method 1: the ugly way**
Using a set to store the cache and check if this number occurs before. Space complexity: `O(n)`.
```cpp
bool isHappy(int n) {
    set<int> s;
    while (true) {
        s.insert(n);
        int temp = 0;
        while (n) {
            temp += (n % 10) * (n % 10);
            n /= 10;
        }
        n = temp;
        if (n == 1) return true;
        if (s.find(n) != s.end()) return false;
    }
    return true;
}
```

**Method 2: Cycle Detection**
Space complexity: `O(1)`
```cpp
int compute(int n) {
    int res = 0;
    while (n) {
        res += (n % 10) * (n % 10);
        n /= 10;
    }
    return res;
}

bool isHappy(int n) {
    int slow = n, fast = n;
    while (true) {
        slow = compute(slow);
        fast = compute(compute(fast));
        if (slow == 1) return true;
        if (slow == fast) return false;
    } 
    return true;
}
```