# Two Pointers

There are some problems that require us to *find the longest subsquence such that it satisfies some property*. This kind of question can often be solved by maintain **two pointers**. It is a useful algorithm design techinique that allows you to keep track of informations about a certain range `[j, i]` (**sliding window** is another name). The core idea is as follows:

```cpp
for (int i = 0, j = 0; i < n; ++i) {
    while (j < i && check(j, i)) j++;       // or j <= i, depends on cases
    
    // --------------------------------
    // the logic that deals with problem.
    // --------------------------------

    res = max(res, i - j + 1);
}
```

We use a pointer `i` to iterate through this sequence, initially `j = 0`. At some time, the condition that question gives us no longer holdes when `i` point to some middle value. We can then use the `while` loop to increase `j` and make the condition valid again. This might be too abstract, but we will exam some concreate problems below and see how this template applies to them.

---
## 2Sum / 3Sum / 4Sum Series

+ [Leetcode 1. Two Sum](https://leetcode.com/problems/two-sum/)

### [Leetcode 1. Two Sum](https://leetcode.com/problems/two-sum/)
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
+ [Leetcode 485. Max Consecutive Ones](https://leetcode.com/problems/max-consecutive-ones/)
+ [Leetcode 487. Max Consecutive Ones II](https://leetcode.com/problems/max-consecutive-ones-ii/)
+ [Leetcode 1004. Max Consecutive Ones III](https://leetcode.com/problems/max-consecutive-ones-iii/)
+ [Leetcode 209. Minimum Size Subarray Sum](https://leetcode.com/problems/minimum-size-subarray-sum/)
+ [Leetcode 1358. Number of Substrings Containing All Three Characters](https://leetcode.com/problems/number-of-substrings-containing-all-three-characters/)
+ [Leetcode 1248. Count Number of Nice Subarrays](https://leetcode.com/problems/count-number-of-nice-subarrays/)
+ [Leetcode 930. Binary Subarrays With Sum](https://leetcode.com/problems/binary-subarrays-with-sum/)
+ [Leetcode 1234. Replace the Substring for Balanced String](https://leetcode.com/problems/replace-the-substring-for-balanced-string/)
+ [Leetcode 159. Longest Substring with At Most Two Distinct Characters](https://leetcode.com/problems/longest-substring-with-at-most-two-distinct-characters/)


### [Leetcode 485. Max Consecutive Ones](https://leetcode.com/problems/max-consecutive-ones/)
```cpp
int findMaxConsecutiveOnes(vector<int>& nums) {
    int res = 0, cnt = 0;
    for (int i = 0, j = 0; i < nums.size(); ++i) {
        if (nums[i] == 0) cnt++;
        while (j <= i && cnt > 0) {
            if (nums[j] == 0) cnt--;
            j++;
        }
        res = max(res, i - j + 1);
    }
    return res;
}
```

### [Leetcode 487. Max Consecutive Ones II](https://leetcode.com/problems/max-consecutive-ones-ii/)
```cpp
int findMaxConsecutiveOnes(vector<int>& nums) {
    int res = 0, cnt = 0;
    for (int i = 0, j = 0; i < nums.size(); ++i) {
        if (nums[i] == 0) cnt++;
        while (j <= i && cnt > 1) {
            if (nums[j] == 0) cnt--;
            j++;
        }
        res = max(res, i - j + 1);
    }
    return res;
}
```

### [Leetcode 1004. Max Consecutive Ones III](https://leetcode.com/problems/max-consecutive-ones-iii/)
```cpp
int longestOnes(vector<int>& A, int K) {
    int res = 0, cnt = 0;
    for (int i = 0, j = 0; i < A.size(); ++i) {
        if (A[i] == 0) cnt++;
        while (j <= i && cnt > K) {
            if (A[j] == 0) cnt--;
            j++;
        }
        res = max(res, i - j + 1);
    }
    return res;
}
```
?> Note that the condition for the `while` loop is `j <= i`. In other words, the while loop breaks only when `j > i`. Otherwise the code would fail this case: `A = [0, 0, 0, 0], K = 0`.


### [Leetcode 209. Minimum Size Subarray Sum](https://leetcode.com/problems/minimum-size-subarray-sum/)
```cpp
int minSubArrayLen(int s, vector<int>& nums) {
    int res = INT_MAX, total = 0;
    for (int i = 0, j = 0; i < nums.size(); ++i) {
        total += nums[i];
        while (total >= s) {
            res = min(res, i - j + 1);
            total -= nums[j++];
        }
    }
    return res == INT_MAX ? 0 : res;
}
```


### [Leetcode 1358. Number of Substrings Containing All Three Characters](https://leetcode.com/problems/number-of-substrings-containing-all-three-characters/)
```cpp
int numberOfSubstrings(string s) {
    int res = 0;
    vector<int> cnt = {0, 0, 0};
    for (int i = 0, j = 0; i < s.size(); ++i) {
        cnt[s[i] - 'a']++;
        while (j < i && cnt[0] != 0 && cnt[1] != 0 && cnt[2] != 0) {
            cnt[s[j] - 'a']--;
            j++;
        }
        res += j;
    }
    return res;
}
```

### [Leetcode 1248. Count Number of Nice Subarrays](https://leetcode.com/problems/count-number-of-nice-subarrays/)
```cpp
int numberOfSubarrays(vector<int>& nums, int k) {
    int res = 0, cnt = 0, temp = 0;
    for (int i = 0, j = 0; i < nums.size(); ++i) {
        if (nums[i] & 1) cnt++, temp = 0;
        while (j <= i && cnt == k) {
            cnt -= nums[j] & 1;
            temp++;
            j++;
        }
        res += temp;
    }
    return res;
}
```
?> Note that `cnt` represents the number of odd number in current range. `temp` stores the number of valid subarrays. This problem can also be solved by **prefix sum**. Please see the prefix sum chapter, there is a nice solution.

### [Leetcode 930. Binary Subarrays With Sum](https://leetcode.com/problems/binary-subarrays-with-sum/)
```cpp
int numSubarraysWithSum(vector<int>& nums, int S) {
    int res = 0, cnt = 0;
    for (int i = 0, j = 0; i < nums.size(); ++i) {
        cnt += nums[i];
        while (j < i && cnt > S) cnt -= nums[j++];
        if (cnt < S) continue;
        if (cnt == S) res++;
        int t = j;
        while (t < i && nums[t] == 0) t++, res++;
    }
    return res;
}
```

### [Leetcode 1234. Replace the Substring for Balanced String](https://leetcode.com/problems/replace-the-substring-for-balanced-string/)
```cpp
bool check(unordered_map<char, int>& temp) {
    for (auto& t : temp) if (t.second > 0) return false;
    return true;
} 

int balancedString(string s) {
    int n = s.size();
    unordered_map<char, int> freq, temp;
    for (char c : s) freq[c]++;
    for (auto& f : freq) if (f.second > n / 4) temp[f.first] = f.second - n / 4;
    if (temp.size() == 0) return 0;
    
    int res = INT_MAX;
    for (int i = 0, j = 0; i < n; ++i) {
        if (temp.find(s[i]) != temp.end()) temp[s[i]]--;
        while (j <= i && check(temp)) {
            res = min(res, i- j + 1);
            if (temp.find(s[j]) != temp.end()) temp[s[j]]++;
            j++;
        }
    }
    return res == INT_MAX ? 0 : res;
}
```

### [Leetcode 159. Longest Substring with At Most Two Distinct Characters](https://leetcode.com/problems/longest-substring-with-at-most-two-distinct-characters/)
```cpp
int lengthOfLongestSubstringTwoDistinct(string s) {
    int res = 0;
    unordered_map<char, int> m;
    for (int i = 0, j = 0; i < s.size(); ++i) {
        m[s[i]]++;
        while (j < i && m.size() > 2) {
            if (m.find(s[j]) != m.end()) {
                m[s[j]]--;
                if (m[s[j]] == 0) m.erase(s[j]);
            }
            j++;
        }
        res = max(res, i - j + 1);
    }
    return res;
}
```

### [Leetcode 845. Longest Mountain in Array](https://leetcode.com/problems/longest-mountain-in-array/)
This problem can be solved by keeping two pointers to maintain the range. But the code below didn't use the template I provide above, just because writting in the following way could be more informative. The code is pretty self-explatory.
```cpp
int longestMountain(vector<int>& A) {
    int n = A.size();
    if (n < 3) return 0;
    
    int i = 0, j = 0, res = 0;
    while (i < n - 2) {
        while (i < n - 1 && A[i] >= A[i + 1]) i++;
        j = i + 1;
        
        // mountain up
        while (j < n - 1 && A[j] < A[j + 1]) j++;
        
        // mountain down
        while (j < n - 1 && A[j] > A[j + 1]) {
            j++;
            res = max(res, j - i + 1);
        }
        i = j;
    } 
    return res;
}
```

