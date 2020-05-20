# Dynamic Programming on Array

## House Robber Series

### [Leetcode 198. House Robber](https://leetcode.com/problems/house-robber/)

We can create a vector the same length as `nums`, each element is a vector contains two elements, which is the max value if current house is not robbed, and the max value if the current house is robbed. Then we can easliy derive the following relations:
+ `dp[i][0] = max(dp[i - 1][0], dp[i - 1][1])`
+ `dp[i][1] = dp[i - 1][0] + nums[i]`

```cpp
int rob(vector<int>& nums) {
    if (nums.size() == 0) return 0;
    int n = nums.size();
    vector<vector<int>> dp(n, vector<int>(2, 0)); // (not rob, rob)
    dp[0][0] = 0, dp[0][1] = nums[0];
    for (int i = 1; i < n; ++i) {
        dp[i][0] = max(dp[i - 1][0], dp[i - 1][1]);
        dp[i][1] = dp[i - 1][0] + nums[i];
    }
    
    return max(dp[n - 1][0], dp[n - 1][1]);
}
```

Notice that in `dp` vector, the only element we care about is the last one so far. So we don't have to use a vector to store all the information, just keeping track of the current value would be enough. `a` denotes the maximum value so far without robbing the current `nums[i]`, `b` denotes the maxumum value with current `nums[i]` robbed.

```cpp
int rob(vector<int>& nums) {
    if (nums.size() == 0) return 0;
    int a = 0, b = 0;
    for (int n : nums) {
        int t = a;
        a = max(a, b);
        b = n + t;
    }
    return max(a, b);
}
```

### [Leetcode 213. House Robber II](https://leetcode.com/problems/house-robber-ii/)
The only difference from the last question is that now all houses at this place are **arranged in a circle**. That means the first and last house cannot be robbed at the same time. We exclude first house and call the previous routine, then exclude the last house and call the previous routine, whichever larger gives the final result.

```cpp
int helper(vector<int>& nums, int i, int j) {
    if (i >= j) return 0;
    int a = 0, b = 0;
    for (int k = i; k < j; ++k) {
        int t = a;
        a = max(a, b);
        b = t + nums[k];
    }
    return max(a, b);
}

int rob(vector<int>& nums) {
    if (nums.size() == 0) return 0;
    if (nums.size() == 1) return nums[0] > 0 ? nums[0] : 0;
    int a = helper(nums, 1, nums.size()), b = helper(nums, 0, nums.size() - 1);
    return max(a, b);
}
```

### [Leetcode 337. House Robber III](https://leetcode.com/problems/house-robber-iii/)

This is a standard recursive solution. The only problem is that we need to store the cache in a map in order to reduce time complexity, otherwise we are re-computing the same node.
```cpp
class Solution {
private:
    unordered_map<TreeNode*, int> memo;
    
public:
    int rob(TreeNode* root) {
        if (!root) return 0;
        if (memo[root]) return memo[root];
        int val = 0;
        if (root->left) val += rob(root->left->left) + rob(root->left->right);
        if (root->right) val += rob(root->right->left) + rob(root->right->right);
        int res = max(val + root->val, rob(root->left) + rob(root->right));
        memo[root] = res;
        return res;
    }
};
```

## Buy & Sell Stock Series

### [Leetcode 121. Best Time to Buy and Sell Stock](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/)
> If you were only permitted to complete at most one transaction (i.e., buy one and sell one share of the stock), design an algorithm to find the maximum profit.

**Method 1:** Keep track of the minimum value so far, and calculate the difference with current stock price. The maximum difference would give us the result.
```cpp
int maxProfit(vector<int>& prices) {
    int min_price = INT_MAX, res = 0;
    for (auto p : prices) {
        min_price = min(min_price, p);
        res = max(res, p - min_price);
    }
    return res;
}
```


**Method 2:** We accumulate the `diff` to our `curr (current maximum value)`. If `curr` is less than 0, then there is no point buy and sell stocks, and we set it back to `0`. `res` is the maximum value found so far. 
```cpp
int maxProfit(vector<int>& prices) {
    int curr = 0, res = 0;
    for (int i = 1; i < prices.size(); ++i) {
        int diff = prices[i] - prices[i - 1];
        curr += diff;
        curr = max(curr, 0);
        res = max(res, curr);
    }
    return res;
}
```

**Method 3:** Dynamic Programming. Let `dp[i]` be maximum profit we can get until day `i`. Then `dp[i] = max(dp[i - 1], prices[i] - min_price)`.

Notice that there is no need for us to use the whole array to keep track of everyday's profit. What we only care about is the last day. That's why we can always omit the vector and use a variable instead. That would reduce our following code to *method 1*.
```cpp
int maxProfit(vector<int>& prices) {
    int n = prices.size();
    if (n == 0) return 0;
    vector<int> dp(n, 0);
    int min_price = prices[0];
    for (int i = 1; i < n; ++i) {
        min_price = min(min_price, prices[i]);
        dp[i] = max(dp[i - 1], prices[i] - min_price);
    }
    return dp[n - 1];
}
```

### [Leetcode 122. Best Time to Buy and Sell Stock II](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/)
Since now we can make as many transactions as we want, whenever the `diff` is greater than `0`, we take this transaction into account. This is equvilent to *method 2* of above question, but much easiler. 
```cpp
int maxProfit(vector<int>& prices) {
    int res = 0;
    for (int i = 1; i < prices.size(); ++i) {
        int diff = prices[i] - prices[i - 1];
        if (diff > 0) res += diff;
    }
    return res;
}
```

### [Leetcode ]




## Subarray Series

### [Leetcode 53. Maximum Subarray](https://leetcode.com/problems/maximum-subarray/)
> Given an integer array `nums`, find the contiguous subarray (containing at least one number) which has the largest sum and return its sum.

**Idea:** let `dp[i]` be the maximum sum so far ending with element `nums[i]`.
```cpp
int maxSubArray(vector<int>& nums) {
    vector<int> dp(nums.size());
    int res = dp[0] = nums[0];
    for (int i = 1; i < nums.size(); ++i) {
        dp[i] = nums[i] + (dp[i - 1] < 0 ? 0 : dp[i - 1]);
        res = max(res, dp[i]);
    }
    return res;
}
```

As always, we see that only the last element of `dp` was used, so we can instead use a variable to replace it.

```cpp
int maxSubArray(vector<int>& nums) {
    int curr = nums[0], res = nums[0];
    for (int i = 1; i < nums.size(); ++i) {
        curr = nums[i] + max(0, curr);
        res = max(res, curr);
    }
    return res;
}
```

### [Leetcode 152. Maximum Product Subarray](https://leetcode.com/problems/maximum-product-subarray/)
> Given an integer array `nums`, find the contiguous subarray within an array (containing at least one number) which has the largest product.

Unlike sum, product behaves differently when it comes to negative numbers. That's why we need keep track of both the minimum value and maximum value so far in our `dp` vector.
```cpp
int maxProduct(vector<int>& nums) {
    vector<pair<int, int>> dp(nums.size()); // (min, max)
    int res = dp[0].first = dp[0].second = nums[0];
    for (int i = 1; i < nums.size(); ++i) {
        if (nums[i] > 0) {
            dp[i].first = min(nums[i], nums[i] * dp[i - 1].first);
            dp[i].second = max(nums[i], nums[i] * dp[i - 1].second);
        } else {
            dp[i].second = max(nums[i], nums[i] * dp[i - 1].first);
            dp[i].first = min(nums[i], nums[i] * dp[i - 1].second);
        }
        res = max(res, dp[i].second);
    }
    return res;
}
```

As always, we see that only the last element of `dp` was used, so we can instead use two variables to replace it.

```cpp
int maxProduct(vector<int>& nums) {
    int mmin = nums[0], mmax = nums[0], res = nums[0];
    for (int i = 1; i < nums.size(); ++i) {
        if (nums[i] < 0) swap(mmin, mmax);
        mmin = min(nums[i], nums[i] * mmin);
        mmax = max(nums[i], nums[i] * mmax);
        res = max(res, mmax);
    }
    return res;
}
```

### [Leetcode ]