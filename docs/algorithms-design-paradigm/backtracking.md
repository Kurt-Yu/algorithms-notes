# Backtracking

Backtracking is the process of finding (or manipulating) something in a `DFS` manner. It allows you to go back to previous state if current branch has already been considered. Below are the problems that I encountered on leetcode that share the same idea and can be solved with similar backtracking templates. Hope you can find some insights from those questions.

**Note:** This post is referenced from [this aritical](https://leetcode.com/problems/combination-sum/discuss/16502/A-general-approach-to-backtracking-questions-in-Java-(Subsets-Permutations-Combination-Sum-Palindrome-Partitioning)). The Original artical is written in Java, here I provide the C++ version.

+ [Leetcode 78. Subsets](https://leetcode.com/problems/subsets/)
+ [Leetcode 90. Subsets II](https://leetcode.com/problems/subsets-ii/)
+ [Leetcode 46. Permutations](https://leetcode.com/problems/permutations/)
+ [Leetcode 47. Permutations II](https://leetcode.com/problems/permutations-ii/)
+ [Leetcode 39. Combination Sum](https://leetcode.com/problems/combination-sum/)
+ [Leetcode 40. Combination Sum II](https://leetcode.com/problems/combination-sum-ii/)
+ [Leetcode 131. Palindrome Partitioning](https://leetcode.com/problems/palindrome-partitioning/)


---
## [Leetcode 78. Subsets](https://leetcode.com/problems/subsets/)
```cpp
void backtracking(vector<int>& nums, vector<vector<int>>& res, vector<int> temp, int start) {
    res.push_back(temp);
    for (int i = start; i < nums.size(); ++i) {
        temp.push_back(nums[i]);
        backtracking(nums, res, temp, i + 1);
        temp.pop_back();
    }
}

vector<vector<int>> subsets(vector<int>& nums) {
    vector<vector<int>> res;
    backtracking(nums, res, {}, 0);
    return res;
}
```

---
## [Leetcode 90. Subsets II](https://leetcode.com/problems/subsets-ii/)
```cpp
void backtracking(vector<int>& nums, vector<vector<int>>& res, vector<int> temp, int start) {
    res.push_back(temp);
    for (int i = start; i < nums.size(); ++i) {
        if (i > start && nums[i] == nums[i - 1]) continue;
        temp.push_back(nums[i]);
        backtracking(nums, res, temp, i + 1);
        temp.pop_back();
    }
}

vector<vector<int>> subsetsWithDup(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    vector<vector<int>> res;
    backtracking(nums, res, {}, 0);
    return res;
}
```

---
## [Leetcode 46. Permutations](https://leetcode.com/problems/permutations/)
```cpp
void backtracking(vector<int>& nums, vector<vector<int>>& res, vector<int> temp, int start) {
    if (temp.size() == nums.size()) res.push_back(temp);
    else {
        for (int i = 0; i < nums.size(); ++i) {
            if (find(temp.begin(), temp.end(), nums[i]) != temp.end()) continue;
            temp.push_back(nums[i]);
            backtracking(nums, res, temp, i + 1);
            temp.pop_back();
        }
    }
}

vector<vector<int>> permute(vector<int>& nums) {
    vector<vector<int>> res;
    backtracking(nums, res, {}, 0);
    return res;
}
```

---
## [Leetcode 47. Permutations II](https://leetcode.com/problems/permutations-ii/)
```cpp
void backtracking(vector<int>& nums, vector<vector<int>>& res, vector<int> temp, vector<bool>& seen) {
    if (temp.size() == nums.size()) res.push_back(temp);
    else {
        for (int i = 0; i < nums.size(); ++i) {
            if (seen[i] || i > 0 && nums[i] == nums[i - 1] && !seen[i - 1]) continue;
            seen[i] = true;
            temp.push_back(nums[i]);
            backtracking(nums, res, temp, seen);
            seen[i] = false;
            temp.pop_back();
        }
    }
}


vector<vector<int>> permuteUnique(vector<int>& nums) {
    vector<vector<int>> res;
    sort(nums.begin(), nums.end());
    vector<bool> seen(nums.size(), false);
    backtracking(nums, res, {}, seen);
    return res;
}
```

---
## [Leetcode 39. Combination Sum](https://leetcode.com/problems/combination-sum/)
```cpp
void backtracking(vector<int>& nums, vector<vector<int>>& res, vector<int> temp, int remaining, int start) {
    if (remaining < 0) return;
    else if (remaining == 0) res.push_back(temp); 
    for (int i = start; i < nums.size(); ++i) {
        temp.push_back(nums[i]);
        backtracking(nums, res, temp, remaining - nums[i], i); // not i + 1 because we can re-use element
        temp.pop_back();
    }
}

vector<vector<int>> combinationSum(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());
    vector<vector<int>> res;
    backtracking(nums, res, {}, target, 0);
    return res;
}
```

---
## [Leetcode 40. Combination Sum II](https://leetcode.com/problems/combination-sum-ii/)
```cpp
void backtracking(vector<int>& nums, vector<vector<int>>& res, vector<int> temp, int remaining, int start) {
    if (remaining < 0) return;
    else if (remaining == 0) res.push_back(temp);
    for (int i = start; i < nums.size(); ++i) {
        if (i > start && nums[i] == nums[i - 1]) continue;
        temp.push_back(nums[i]);
        backtracking(nums, res, temp, remaining - nums[i], i + 1);
        temp.pop_back();
    }
}

vector<vector<int>> combinationSum2(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());
    vector<vector<int>> res;
    backtracking(nums, res, {}, target, 0);
    return res;
}
```

---
## [Leetcode 131. Palindrome Partitioning](https://leetcode.com/problems/palindrome-partitioning/)
```cpp
void backtracking(string& s, vector<vector<string>>& res, vector<string> temp, int start) {
    if (start == s.length()) res.push_back(temp);
    for (int i = start; i < s.length(); ++i) {
        if (isPalindrome(s, start, i)) {
            temp.push_back(s.substr(start, i - start + 1));
            backtracking(s, res, temp, i + 1);
            temp.pop_back();
        }
    }
}

bool isPalindrome(string& s, int i, int j) {
    while (i < j) if (s[i++] != s[j--]) return false;
    return true;
}

vector<vector<string>> partition(string s) {
    vector<vector<string>> res;
    backtracking(s, res, {}, 0);
    return res;
}
```