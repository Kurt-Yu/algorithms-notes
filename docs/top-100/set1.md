# Set 1 (Problem 1 -- 20)

1. [Leetcode 1. Two Sum](https://leetcode.com/problems/two-sum/)
2. [Leetcode 2. Add Two Numbers](https://leetcode.com/problems/add-two-numbers/)
3. [Leetcode 3. Longest Substring Without Repeating Characters](https://leetcode.com/problems/longest-substring-without-repeating-characters/)
4. [Leetcode 4. Median of Two Sorted Arrays](https://leetcode.com/problems/median-of-two-sorted-arrays)
5. [Leetcode 5. Longest Palindromic Substring](https://leetcode.com/problems/longest-palindromic-substring/)
6. [Leetcode 10. Regular Expression Matching](https://leetcode.com/problems/regular-expression-matching)
7. [Leetcode 11. Container With Most Water](https://leetcode.com/problems/container-with-most-water)
8. [Leetcode 15. 3Sum](https://leetcode.com/problems/3sum/)
9. [Leetcode 17. Letter Combinations of a Phone Number](https://leetcode.com/problems/letter-combinations-of-a-phone-number)
10. [Leetcode 19. Remove Nth Node From End of List](https://leetcode.com/problems/remove-nth-node-from-end-of-list)
11. [Leetcode 20. Valid Parentheses](https://leetcode.com/problems/valid-parentheses/)
12. [Leetcode 21. Merge Two Sorted Lists](https://leetcode.com/problems/merge-two-sorted-lists/)
13. [Leetcode 22. Generate Parentheses](https://leetcode.com/problems/generate-parentheses)
14. [Leetcode 23. Merge k Sorted Lists](https://leetcode.com/problems/merge-k-sorted-lists/submissions/)
15. [Leetcode 31. Next Permutation](https://leetcode.com/problems/next-permutation)
16. [Leetcode 32. Longest Valid Parentheses](https://leetcode.com/problems/longest-valid-parentheses)
17. [Leetcode 33. Search in Rotated Sorted Array](https://leetcode.com/problems/search-in-rotated-sorted-array)
18. [Leetcode 34. Find First and Last Position of Element in Sorted Array](https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array)
19. [Leetcode 39. Combination Sum](https://leetcode.com/problems/combination-sum)
20. [Leetcode 41. First Missing Positive](https://leetcode.com/problems/first-missing-positive)


---
### 1. [Leetcode 1. Two Sum](https://leetcode.com/problems/two-sum/)
```cpp
vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> m;
    for (int i = 0; i < nums.size(); ++i) {
        if (m.find(target - nums[i]) != m.end()) return {m[target - nums[i]], i};
        m[nums[i]] = i;
    }
    return {};
}
```

--- 
### 2. [Leetcode 2. Add Two Numbers](https://leetcode.com/problems/add-two-numbers/)
```cpp
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    int carry = 0;
    ListNode* curr = new ListNode(0);
    ListNode* res = curr;

    while (l1 || l2) {
        if (l1) carry += l1->val, l1 = l1->next;
        if (l2) carry += l2->val, l2 = l2->next;
        
        curr->next = new ListNode(carry % 10);
        carry /= 10;
        curr = curr->next;
    }
    if (carry == 1) curr->next = new ListNode(1);
    return res->next;
}
```

---
### 3. [Leetcode 3. Longest Substring Without Repeating Characters](https://leetcode.com/problems/longest-substring-without-repeating-characters/)
```cpp
int lengthOfLongestSubstring(string S) {
    unordered_map<char, int> m;
    
    int start = -1, res = 0;
    for (int i = 0; i < S.length(); ++i) {
        if (m.find(S[i]) != m.end()) start = max(start, m[S[i]]);
        m[S[i]] = i;
        res = max(res, i - start);
    }
    return res;
}
```




--- 
### 2. [Leetcode 42. Trapping Rain Water](https://leetcode.com/problems/trapping-rain-water/)
```cpp
int trap(vector<int>& height) {
    if (height.size() <= 2) return 0;
    int i = 0, j = height.size() - 1;
    int leftmax = height[i], rightmax = height[j];
    int res = 0;
    while (i <= j) {
        if (height[i] < height[j]) {
            if (height[i] < leftmax) res += leftmax - height[i];
            else leftmax = height[i];
            i++;
        } else {
            if (height[j] < rightmax) res += rightmax - height[j];
            else rightmax = height[j];
            j--;
        }
    }
    return res;
}
```

--- 
### 3. [Leetcode 2. Add Two Numbers](https://leetcode.com/problems/add-two-numbers/)
```cpp
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    int carry = 0;
    ListNode* curr = new ListNode(0);
    ListNode* res = curr;

    while (l1 || l2) {
        if (l1) carry += l1->val, l1 = l1->next;
        if (l2) carry += l2->val, l2 = l2->next;
        
        curr->next = new ListNode(carry % 10);
        carry /= 10;
        curr = curr->next;
    }
    if (carry == 1) curr->next = new ListNode(1);
    return res->next;
}
```

--- 
### 5. [Leetcode 200. Number of Islands](https://leetcode.com/problems/number-of-islands/)
```cpp
void helper(vector<vector<char>>& grid, vector<vector<int>>& seen, int i, int j) {
    if (grid[i][j] == '0' || seen[i][j] == 1) return;
    seen[i][j] = 1;
    if (i > 0) helper(grid, seen, i - 1, j);
    if (i < grid.size() - 1) helper(grid, seen, i + 1, j);
    if (j > 0) helper(grid, seen, i, j - 1);
    if (j < grid[0].size() - 1) helper(grid, seen, i, j + 1);
}

int numIslands(vector<vector<char>>& grid) {
    int row = grid.size();
    if (row == 0) return 0;
    int col = grid[0].size();
    
    int res = 0;
    vector<vector<int>> seen(row, vector<int>(col, 0));
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            if (grid[i][j] == '1' && seen[i][j] == 0) res++, helper(grid, seen, i, j);
        }
    }
    return res;
}
```

---
### 6. [Leetcode 5. Longest Palindromic Substring](https://leetcode.com/problems/longest-palindromic-substring/)
```cpp
string longestPalindrome(string s) {
    int n = s.length();
    if (n == 0) return "";
    vector<vector<int>> dp(n, vector<int>(n, 0));
    int len = 0, lower = 0, upper = 0;
    for (int i = n - 1; i >= 0; --i) {
        for (int j = i; j < n; ++j) {
            if (j == i) dp[i][j] = 1;
            else if (j - i == 1) dp[i][j] = (s[i] == s[j] ? 1 : 0);
            else dp[i][j] = (s[i] == s[j] && dp[i + 1][j - 1] == 1 ? 1 : 0);
            
            if (j - i + 1 > len && dp[i][j] == 1) len = j - i + 1, lower = i, upper = j;
        }
    }
    return s.substr(lower, upper - lower + 1);
}
```

---
### 8. [Leetcode 20. Valid Parentheses](https://leetcode.com/problems/valid-parentheses/)
```cpp
bool isValid(string S) {
    stack<char> s;
    for (char c : S) {
        if (c == ')' || c == ']' || c == '}') {
            if (s.size() == 0) return false;
            if (c == ')' && s.top() != '(') return false;
            if (c == ']' && s.top() != '[') return false;
            if (c == '}' && s.top() != '{') return false;
            s.pop();
        } else {
            s.push(c);
        }
    }
    return s.size() == 0;
}
```

--- 
### 9. [Leetcode 21. Merge Two Sorted Lists](https://leetcode.com/problems/merge-two-sorted-lists/)
```cpp
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode* res = new ListNode(0);
    ListNode* curr = res;
    while (l1 && l2) {
        if (l1->val < l2->val) curr->next = l1, l1 = l1->next;
        else curr->next = l2, l2 = l2->next;
        curr = curr->next;
    }
    if (!l1) curr->next = l2;
    else curr->next = l1;
    
    return res->next;
}
```

---
### 10. [Leetcode 53. Maximum Subarray](https://leetcode.com/problems/maximum-subarray/)
```cpp
int maxSubArray(vector<int>& nums) {
    int res = nums[0], curr = nums[0];
    for (int i = 1; i < nums.size(); ++i) {
        curr = nums[i] + max(0, curr);
        res = max(res, curr);
    }
    return res;
}
```

---
### 11. [Leetcode 15. 3Sum](https://leetcode.com/problems/3sum/)
```cpp
vector<vector<int>> threeSum(vector<int>& nums) {
    if (nums.size() <= 2) return {};
    sort(nums.begin(), nums.end());
    vector<vector<int>> res;
    
    for (int i = 0; i < nums.size() - 2; ++i) {
        if (i > 0 && nums[i] == nums[i - 1]) continue;
        
        int left = i + 1, right = nums.size() - 1;
        while (left < right) {
            int sum = nums[i] + nums[left] + nums[right];
            if (sum > 0) right--;
            else if (sum < 0) left++;
            else {
                res.push_back({nums[i], nums[left], nums[right]});
                while (left + 1 < right && nums[left] == nums[left + 1]) left++;
                while (right - 1 > left && nums[right] == nums[right - 1]) right--;
                left++; right--;
            }
        }
    }
    return res;
}
```

---
### 12. [Leetcode 3. Longest Substring Without Repeating Characters](https://leetcode.com/problems/longest-substring-without-repeating-characters/)
```cpp
int lengthOfLongestSubstring(string S) {
    unordered_map<char, int> m;
    
    int start = -1, res = 0;
    for (int i = 0; i < S.length(); ++i) {
        if (m.find(S[i]) != m.end()) start = max(start, m[S[i]]);
        m[S[i]] = i;
        res = max(res, i - start);
    }
    return res;
}
```

---
### 13. [Leetcode 238. Product of Array Except Self](https://leetcode.com/problems/product-of-array-except-self/)
```cpp
vector<int> productExceptSelf(vector<int>& nums) {
    if (nums.size() == 0) return {};
    vector<int> res(nums.size(), 1);
    
    int left = 1, right = 1;
    for (int i = 0; i < nums.size(); ++i) {
        res[i] *= left;
        left *= nums[i];
    }
    for (int i = nums.size() - 1; i >= 0; --i) {
        res[i] *= right;
        right *= nums[i];
    }
    return res;
}
```

---

### 14. [Leetcode 23. Merge k Sorted Lists](https://leetcode.com/problems/merge-k-sorted-lists/submissions/)

**Method 1: Divide & Conquer**
```cpp
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode* curr = new ListNode(0);
    ListNode* res = curr;
    while (l1 && l2) {
        if (l1->val < l2->val) curr->next = l1, l1 = l1->next;
        else curr->next = l2, l2 = l2->next;
        curr = curr->next;
    }
    if (!l1) curr->next = l2;
    else curr->next = l1;
    return res->next;
}

ListNode* helper(vector<ListNode*>& lists, int i, int j) {
    if (i > j) return NULL;
    if (i == j) return lists[i];
    int mid = i + (j - i) / 2;
    ListNode* left = helper(lists, i, mid);
    ListNode* right = helper(lists, mid + 1, j);
    return mergeTwoLists(left, right);
}

ListNode* mergeKLists(vector<ListNode*>& lists) {
    return helper(lists, 0, lists.size() - 1);
}
```

**Method 2: Priority Queue**

```cpp
ListNode* mergeKLists(vector<ListNode*>& lists) {
    auto cmp = [](const ListNode* l1, const ListNode* l2) {return l1->val > l2->val; };
    priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> pq(cmp);
    
    ListNode* curr = new ListNode(0);
    ListNode* res = curr;
    for (auto& node : lists) if (node) pq.push(node);
    while (!pq.empty()) {
        auto node = pq.top();
        pq.pop();
        curr->next = node;
        curr = curr->next;
        if (node->next) pq.push(node->next);
    }
    return res->next;
}
```

---
### 15. [Leetcode 138. Copy List with Random Pointer](https://leetcode.com/problems/copy-list-with-random-pointer/)

---

### 16. [Leetcode 56. Merge Intervals](https://leetcode.com/problems/merge-intervals/)
```cpp
vector<vector<int>> merge(vector<vector<int>>& intervals) {
    sort(intervals.begin(), intervals.end());
    vector<vector<int>> res;
    for (auto& i : intervals) {
        if (res.size() == 0) res.push_back(i);
        else {
            if (i[0] <= res.back()[1]) {
                auto last = res.back();
                res.pop_back();
                res.push_back({last[0], max(i[1], last[1])});
            } else {
                res.push_back(i);
            }
        }
    }
    return res;
}
```

--- 

### 17. [Leetcode 76. Minimum Window Substring](https://leetcode.com/problems/minimum-window-substring/)

---
### 18. [Leetcode 253. Meeting Rooms II](https://leetcode.com/problems/meeting-rooms-ii/)
```cpp
int minMeetingRooms(vector<vector<int>>& intervals) {
    int res = 0;
    sort(intervals.begin(), intervals.end());
    priority_queue<int, vector<int>, greater<int>> pq;

    for (auto& a : intervals) {
        if (!pq.empty() && a[0] >= pq.top()) {
            pq.pop();
            pq.push(a[1]);
        } else {
            pq.push(a[1]);
        }
    }
    return pq.size();
}
```

---
### 19. [Leetcode 206. Reverse Linked List](https://leetcode.com/problems/reverse-linked-list/)

**Method 1: Iterative**
```cpp
ListNode* reverseList(ListNode* head) {
    ListNode* curr = head, *prev = NULL;
    while (curr) {
        auto next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    
    return prev;
}
```

**Method 2: Recusive**
```cpp
ListNode* reverseList(ListNode* head) {
    if (!head || !head->next) return head;
    auto node = reverseList(head->next);
    head->next->next = head;
    head->next = NULL;
    return node;
}
```

---
### 20. [Leetcode 297. Serialize and Deserialize Binary Tree](https://leetcode.com/problems/serialize-and-deserialize-binary-tree/)
```cpp
class Codec {
private:
    void encode(TreeNode* root, ostringstream& out) {
        if (root) {
            out << root->val << " ";
            encode(root->left, out);
            encode(root->right, out);
        } else {
            out << "# ";
        }
    }
    
    TreeNode* decode(istringstream& in) {
        string val;
        in >> val;
        if (val == "#") return nullptr;
        TreeNode* root = new TreeNode(stoi(val));
        root->left = decode(in);
        root->right = decode(in);
        return root;
    }
    
public:

    // Encodes a tree to a single string.   
    string serialize(TreeNode* root) {
        ostringstream out;
        encode(root, out);
        return out.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        istringstream in(data);
        return decode(in); 
    }
};
```
