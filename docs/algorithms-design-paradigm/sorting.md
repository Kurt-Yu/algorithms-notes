# Sorting

+ [Leetcode 912. Sort an Array](https://leetcode.com/problems/sort-an-array/)
+ [Leetcode 215. Kth Largest Element in an Array](https://leetcode.com/problems/kth-largest-element-in-an-array/)

---
## Quick Sort
```cpp
#include<iostream> 
#include<vector>

using namespace std;

const int N = 1e5 + 5;
vector<int> q(N);

void quick_sort(int l, int r) {
    if (l >= r) return;
    int i = l - 1, j = r + 1, x = q[l + (r - l) / 2];
    while (i < j) {
        while(q[++i] < x);
        while(q[--j] > x);
        if (i < j) swap(q[i], q[j]);
    }
    quick_sort(l, j);
    quick_sort(j + 1, r);
}

int main() {
    int n;
    scanf("%d", &n);
    
    for (int i = 0; i < n; ++i) scanf("%d", &q[i]);
    quick_sort(0, n - 1);
    for (int i = 0; i < n; ++i) printf("%d ", q[i]);
    return 0;
}
```

### [Leetcode 215. Kth Largest Element in an Array](https://leetcode.com/problems/kth-largest-element-in-an-array/)
```cpp
int quick_sort(vector<int> nums, int l, int r, int k) {
    if (l >= r) return nums[l];
    int i = l - 1, j = r + 1, x = nums[l + (r - l ) / 2];
    while (i < j) {
        while (nums[++i] > x);
        while (nums[--j] < x);
        if (i < j) swap(nums[i], nums[j]);
    }
    if (j - l + 1 >= k) return quick_sort(nums, l, j, k);
    return quick_sort(nums, j + 1, r, k - (j - l + 1));
}

int findKthLargest(vector<int>& nums, int k) {
    return quick_sort(nums, 0, nums.size() - 1, k);
}
```

## Merge Sort
```cpp
#include <iostream>
#include <vector>

using namespace std;

const int N = 1e5 + 5;
vector<int> q(N), temp(N);

void merge_sort(int l, int r) {
    if (l >= r) return;
    int mid = l + (r - l) / 2;
    merge_sort(l, mid);
    merge_sort(mid + 1, r);
    
    int i = l, j = mid + 1, k = 0;
    while (i <= mid && j <= r) {
        if (q[i] <= q[j]) temp[k++] = q[i++];
        else temp[k++] = q[j++];
    }
    
    while (i <= mid) temp[k++] = q[i++];
    while (j <= r) temp[k++] = q[j++];
    
    for (int i = l, j = 0; i <= r; ++i, ++j) q[i] = temp[j];
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%d", &q[i]);
    merge_sort(0, n - 1);
    for (int i = 0; i < n; ++i) printf("%d ", q[i]);
}
```