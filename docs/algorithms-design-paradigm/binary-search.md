# Binary Search

Binary search is the most fundamental algorithm in the area of computer science. It describes the process of searching a given value in a (often sorted) vector. Most of programming languges have some built-in function performing binary search (for example, we have `binary_search(), lower_bound(), upper_bound()` in C++ STL), but for the purpose of coding interview and exercising, we will still write the underlying algorithm in this post.

We will see some standard binary search problems, as well as some variants. General coding tmeplate will be provide along the way.

+ [Leetcode 704. Binary Search](https://leetcode.com/problems/binary-search/)
+ [Leetcode 69. Sqrt(x)](https://leetcode.com/problems/sqrtx/)
+ [Leetcode 374. Guess Number Higher or Lower](https://leetcode.com/problems/guess-number-higher-or-lower/)
+ [Leetcode 33. Search in Rotated Sorted Array](https://leetcode.com/problems/search-in-rotated-sorted-array/)
+ [Leetcode 278. First Bad Version](https://leetcode.com/problems/first-bad-version/)
+ [Leetcode 162. Find Peak Element](https://leetcode.com/problems/find-peak-element/)
+ [Leetcode 153. Find Minimum in Rotated Sorted Array](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/)
+ [Leetcode 658 Find K Closest Elements](https://leetcode.com/problems/find-k-closest-elements)

**Exercise:**
+ [Leetcode 270. Closest Binary Search Tree Value](https://leetcode.com/problems/closest-binary-search-tree-value/)
+ [Leetcode 702. Search in a Sorted Array of Unknown Size](https://leetcode.com/problems/search-in-a-sorted-array-of-unknown-size/)
+ [Leetcode 50. Pow(x, n)](https://leetcode.com/problems/powx-n/)
+ [Leetcode 367. Valid Perfect Square](https://leetcode.com/problems/valid-perfect-square/)
+ [Leetcode 744. Find Smallest Letter Greater Than Target](https://leetcode.com/problems/find-smallest-letter-greater-than-target/)
+ [Leetcode 154. Find Minimum in Rotated Sorted Array II](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array-ii/)

---
## Template 1
The most frequently used template was the following one (leetcode 704):

```
Initial Condition: low = 0, high = nums.size() - 1
while loop: while(low <= high)
Go Left: high = mid - 1
Go Right: low = mid + 1
```

###  [Leetcode 704. Binary Search](https://leetcode.com/problems/binary-search/)
```cpp
int search(vector<int>& nums, int target) {
    int low = 0, high = nums.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (target == nums[mid]) return mid;
        else if (target < nums[mid]) high = mid - 1;
        else low = mid + 1;
    }
    return -1;
}
```

### [Leetcode 69. Sqrt(x)](https://leetcode.com/problems/sqrtx/)
**Method 1:** Binary Search
Notice that `mid * mid` might overflow, we need to store it with `long long` type.
```cpp
int mySqrt(int x) {
    int low = 0, high = x;
    while (low <= high) {
        long long mid = low + (high - low) / 2;
        if (mid * mid <= x && (mid + 1) * (mid + 1) > x) return mid;
        else if (mid * mid < x) low = mid + 1;
        else high = mid - 1;
    }
    return 0;
}
```

**Method 2:** [Netwon's Method](https://en.wikipedia.org/wiki/Newton%27s_method)
```cpp
int mySqrt(int x) {
    if (x < 2) return x;

    double x0 = x, x1 = (x0 + x / x0) / 2.0;
    while (abs(x0 - x1) >= 1) {
        x0 = x1;
        x1 = (x0 + x / x0) / 2.0;
    }
    return (int)x1;
}
```

### [Leetcode 374. Guess Number Higher or Lower](https://leetcode.com/problems/guess-number-higher-or-lower/)
```cpp
// Forward declaration of guess API.
// @param num, your guess
// @return -1 if my number is lower, 1 if my number is higher, otherwise return 0
int guess(int num);

class Solution {
public:
    int guessNumber(int n) {
        int low = 1, high = n;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (guess(mid) == 0) return mid;
            else if (guess(mid) < 0) high = mid - 1;
            else low = mid + 1;
        }
        return 0;
    }
};
```

### [Leetcode 33. Search in Rotated Sorted Array](https://leetcode.com/problems/search-in-rotated-sorted-array/)
```cpp
int search(vector<int>& nums, int target) {
    int n = nums.size();
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - mid) / 2;
        if (nums[mid] == target) return mid;
        else if (nums[mid] >= nums[low]) {
            if (target >= nums[low] && target < nums[mid]) high = mid - 1;
            else low = mid + 1;
        } else {
            if (target > nums[mid] && target <= nums[high]) low = mid + 1;
            else high = mid - 1;
        }
    }
    return -1;
}
```

---
## Template 2
This is an advanced version of the basic binary search algorithm. Here we are facing the situation that current element needs to compare with its right neighbor, and the search space is at least 2 elements. So we now need to change a few syntax from the previous one:

```
Initial Condition: low = 0, high = nums.size() - 1
while loop: while(low < high)
Go Left: high = mid
Go Right: low = mid + 1
```

### [Leetcode 278. First Bad Version](https://leetcode.com/problems/first-bad-version/)
```cpp
int firstBadVersion(int n) {
    int low = 0, high = n;
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (!isBadVersion(mid)) low = mid + 1;
        else high = mid;
    }
    return low;
}
```

### [Leetcode 162. Find Peak Element](https://leetcode.com/problems/find-peak-element/)
```cpp
int findPeakElement(vector<int>& nums) {
    int low = 0, high = nums.size() - 1;
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (nums[mid] < nums[mid + 1]) low = mid + 1;
        else high = mid;
    }
    return low;
}
```

### [Leetcode 153. Find Minimum in Rotated Sorted Array](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/)
```cpp
int findMin(vector<int>& nums) {
    int low = 0, high = nums.size() - 1;
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (nums[mid] >= nums[low]) {
            if (nums[mid] < nums[high]) high = mid;
            else low = mid + 1;
        } else high = mid;
    }
    return nums[low];
}
```

### [Leetcode 34. Find First and Last Position of Element in Sorted Array](https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/)
```cpp
int lower_bound(vector<int>& nums, int target) {
    int low = 0, high = nums.size();
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (nums[mid] >= target) high = mid;
        else low = mid + 1;
    }
    return low;
}

vector<int> searchRange(vector<int>& nums, int target) {
    int i = lower_bound(nums, target);
    int j = lower_bound(nums, target + 1);
    if (i < nums.size() && nums[i] == target) return {i, j - 1};
    return {-1, -1};
}
```
?> Note that in C++, `lower_bound` is already a built-in function (in STL). Here we implement it just for the sake of exercising.

`lower_bound` returns the index of the first value that is equal or greater that `target`  in a non-decreasing range `[first, second)`; `upper_bound` returns the index of the first value that is greater that `target`  in a non-decreasing range `[first, second)`; 

### [Leetcode 658 Find K Closest Elements](https://leetcode.com/problems/find-k-closest-elements)
```cpp
vector<int> findClosestElements(vector<int>& nums, int k, int x) {
    int low = 0, high = nums.size() - k;
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (x - nums[mid] > nums[mid + k] - x) low = mid + 1;
        else high = mid;
    }
    return vector<int>(nums.begin() + low, nums.begin() + low + k);
}
```

---
## Exercise

### [Leetcode 270. Closest Binary Search Tree Value](https://leetcode.com/problems/closest-binary-search-tree-value/)
```cpp
int closestValue(TreeNode* root, double target) {
    int res = root->val;
    while (root) {
        res = abs(root->val - target) < abs(res - target) ? root->val : res;
        root =  target < root->val ? root->left : root->right;
    }
    return res;
}
```

### [Leetcode 702. Search in a Sorted Array of Unknown Size](https://leetcode.com/problems/search-in-a-sorted-array-of-unknown-size/)
```cpp
int search(const ArrayReader& reader, int target) {
    int low = 0, high = 10000;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (reader.get(mid) == target) return mid;
        else if (reader.get(mid) > target) high = mid - 1;
        else low = mid + 1;
    }
    return -1;
}
```

### [Leetcode 50. Pow(x, n)](https://leetcode.com/problems/powx-n/)
**Iterative Approach**
```cpp
double myPow(double x, int n) {
    long long N = n;
    if (n < 0) x = 1 / x, N = -N;
    double res = 1;
    double curr = x;
    for (long long i = N; i != 0; i = i >> 1) {
        if (i % 2) res *= curr;
        curr *= curr;
    }
    return res;
}
```

**Recursive Approach**
```cpp
double helper(double x, long long N) {
    if (N == 0) return 1.0;
    double half = helper(x, N / 2);
    if (N % 2) return half * half * x;
    else return half * half;
}

double myPow(double x, int n) {
    long long N = n;
    if (N < 0) x = 1 / x, N = -N;
    return helper(x, N);
}
```

### [Leetcode 367. Valid Perfect Square](https://leetcode.com/problems/valid-perfect-square/)
```cpp
bool isPerfectSquare(int num) {
    long long low = 0, high = num;
    while (low <= high) {
        long mid = low + (high - low) / 2;
        if (mid * mid == num) return true;
        else if (mid * mid < num) low = mid + 1;
        else high = mid - 1;
    }
    return false;
}
```

### [Leetcode 744. Find Smallest Letter Greater Than Target](https://leetcode.com/problems/find-smallest-letter-greater-than-target/)
```cpp
char nextGreatestLetter(vector<char>& letters, char target) {
    int low = 0, high = letters.size();
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (letters[mid] <= target) low = mid + 1;
        else high = mid;
    }
    if (low == letters.size()) return letters.front();
    return letters[low];
}
```
**Note:** there is a built-in function `upper_bound` in STL that does the same thing, so we could just use that.
```cpp
char nextGreatestLetter(vector<char>& letters, char target) {
    auto it = upper_bound(letters.begin(), letters.end(), target);
    if (it == letters.end()) return letters.front();
    return *it;
}
```

### [Leetcode 154. Find Minimum in Rotated Sorted Array II](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array-ii/)
```cpp
int findMin(vector<int>& nums) {
    int low = 0, high = nums.size() - 1;
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (nums[mid] < nums[high]) high = mid;
        else if (nums[mid] > nums[high]) low = mid + 1;
        else high--;
    }
    return nums[low];
}
```

Reference: [Leetcode Binary Search Artical](https://leetcode.com/explore/learn/card/binary-search/)