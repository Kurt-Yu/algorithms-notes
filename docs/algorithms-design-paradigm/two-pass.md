# Two Pass

### [Leetcode 821. Shortest Distance to a Character](https://leetcode.com/problems/shortest-distance-to-a-character/)
```cpp
vector<int> shortestToChar(string S, char C) {
    int n = S.size(), pos = -n;
    vector<int> res(n);
    
    for (int i = 0; i < n; ++i) {
        if (S[i] == C) pos = i;
        res[i] = i - pos;
    }

    for (int i = pos - 1; i >= 0; --i) {
        if (S[i] == C) pos = i;
        res[i] = min(res[i], pos - i);
    }
    return res;
}
```
