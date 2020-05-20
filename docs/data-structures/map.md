# Map

### [Leetcode 266. Palindrome Permutation](https://leetcode.com/problems/palindrome-permutation/)
> Given a string, determine if a permutation of the string could form a palindrome.
```cpp
bool canPermutePalindrome(string s) {
    map<char, int> cnt;
    for (auto c : s) cnt[c]++;
    int odd = 0;
    for (auto c : cnt) {
        if (c.second % 2 == 1) odd++;
        if (odd > 1) return false;
    }
    return true;
}
```


### [Leetcode 697. Degree of an Array](https://leetcode.com/problems/degree-of-an-array/)

For each number in the array, store their indices in a vector. Compute the most frequently element and calculate the maximum length.
```cpp
int findShortestSubArray(vector<int>& nums) {
    unordered_map<int, vector<int>> cnt;
    int freq = 0;
    for (int i = 0; i < nums.size(); ++i) {
        cnt[nums[i]].push_back(i);
        freq = max(freq, (int)cnt[nums[i]].size());
    }
    
    int res = INT_MAX;
    for (auto& c : cnt) {
        if (c.second.size() == freq) res = min(res, c.second.back() - c.second.front() + 1);
    }
    return res; 
}
```