# Dynamic Programming on Strings

## Palindrome Series


### [Leetcode 5. Longest Palindromic Substring](https://leetcode.com/problems/longest-palindromic-substring/)

> Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.

Let `dp[i][j]` be **TRUE** if substring `s[i .. j]` is a palindrome.
`s[i .. j]` is a palindrome if `s[i] == s[j] && dp[i + 1][j - 1] == true`.
`left & right` are the lower and upper bound of result substring.

Time Complexity: `O(n^2)`.
```cpp
string longestPalindrome(string s) {
    int n = s.length();
    vector<vector<bool>> dp(n, vector<bool>(n));
    int left = 0, right = 0;
    for (int i = n - 1; i >= 0; --i) {
        for (int j = i; j < n; ++j) {
            if (i == j) dp[i][j] = true;
            else if (j - i == 1) dp[i][j] = (s[i] == s[j]);
            else dp[i][j] = (s[i] == s[j] && dp[i + 1][j - 1]);
            
            if (dp[i][j] && j - i > right - left) left = i, right = j;
        }
    }
    return s.substr(left, right - left + 1);
}
```

### [Leetcode 516. Longest Palindromic Subsequence](https://leetcode.com/problems/longest-palindromic-subsequence/)

> Given a string s, find the longest palindromic subsequence's length in s. You may assume that the maximum length of s is 1000.

Exactly the same as above problem, instead of storing whether `dp[i][j]` is a palindrome or not, we store the maximum length so far. The dp relation is described in the `for` loop, which is pretty straight forward.

```cpp
int longestPalindromeSubseq(string s) {
    int n = s.length();
    vector<vector<int>> dp(n, vector<int>(n, 0));
    int res = 0;
    for (int i = n - 1; i >= 0; --i) {
        for (int j = i; j < n; ++j) {
            if (i == j) dp[i][j] = 1;
            else if (j - i == 1) dp[i][j] = (s[i] == s[j]) ? 2 : 1;
            else dp[i][j] = (s[i] == s[j] && dp[i + 1][j - 1]) ? 2 + dp[i + 1][j - 1] : max(dp[i + 1][j], dp[i][j - 1]);
            
            res = max(res, dp[i][j]);
        }
    }
    return res;
}
```

### [Leetcode ]()




### [Leetcode 139. Word Break](https://leetcode.com/problems/word-break/)
> Given a non-empty string s and a dictionary wordDict containing a list of non-empty words, determine if s can be segmented into a space-separated sequence of one or more dictionary words.

`dp[i]` is true if substring `s[0 ... i]` can be formed using words from the dictionary.
```cpp
bool wordBreak(string s, vector<string>& wordDict) {
    int n = s.length();
    vector<bool> dp(n + 1);
    dp[0] = true;
    set<string> wordSet;
    for (auto& word : wordDict) wordSet.insert(word);
    
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (dp[j] && wordSet.count(s.substr(j, i - j))) dp[i] = true;
        }
    }
    return dp[n];
}
```