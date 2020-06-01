[Leetcode 84. Largest Rectangle in Histogram](https://leetcode.com/problems/largest-rectangle-in-histogram/)

?> 题解：对于每一个 bar，如果它在我们的最大的长方体内，那么我们把它往两旁边延伸，找到它左边的离它最近的且高度小于它的 bar (把它的 index 记为 l)，再找到它右边的离它最近的且高度小于它的 bar (把它的 index 记为 r)，那么我们很容易得到：包含当前这个 bar 的最大长方形为 `heights[i] * (r - l - 1)`。

?>对于**找左边/右边最近的最大/最小的元素**，这类问题通常用单调栈来解决。
```cpp
int largestRectangleArea(vector<int>& heights) {
    int n = heights.size();
    if (!n) return 0;
    
    vector<int> left(n), right(n);
    stack<pair<int, int>> s1, s2;   // val, idx
    
    for (int i = 0; i < n; ++i) {
        if (i == 0) left[i] = -1;
        else {
            while (!s1.empty() && s1.top().first >= heights[i]) s1.pop();
            if (s1.empty()) left[i] = -1;
            else left[i] = s1.top().second;
        }
        s1.push({heights[i], i});
    }
    
    for (int i = n - 1; i >= 0; --i) {
        if (i == n - 1) right[i] = n;
        else {
            while (!s2.empty() && s2.top().first >= heights[i]) s2.pop();
            if (s2.empty()) right[i] = n;
            else right[i] = s2.top().second;
        }
        s2.push({heights[i], i});
    }
    
    int res = 0;
    for (int i = 0; i < n; ++i) {
        res = max(res, heights[i] * (right[i] - left[i] - 1));
    }
    return res;
}
```

[Go Back](data-structures/栈.md)