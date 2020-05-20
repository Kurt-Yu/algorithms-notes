# Prefix Sum

### [Leetcode 1248. Count Number of Nice Subarrays](https://leetcode.com/problems/count-number-of-nice-subarrays/submissions/)
If we represent the array as binary (0 or 1 based on oddness), then the original problems transforms to `the number subarrays that their sum equals to k`. And this can be easily solved by prefix sum.
```cpp
int numberOfSubarrays(vector<int>& nums, int k) {
    for (auto& n : nums) n &= 1;
    
    unordered_map<int, int> m;
    int total = 0, res = 0;
    m[0] = 1;
    for (auto n : nums) {
        total += n;
        m[total]++;
        res += m[total - k];
    }
    return res;
}
```

### []