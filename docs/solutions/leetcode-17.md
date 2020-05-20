[Leetcode 17. Letter Combinations of a Phone Number](https://leetcode.com/problems/letter-combinations-of-a-phone-number/)

```cpp
vector<string> letterCombinations(string digits) {
    if (digits.length() == 0) return {};
    
    unordered_map<char, string> m = {{'2', "abc"}, {'3', "def"}, {'4', "ghi"}, {'5', "jkl"}, {'6', "mno"}, {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"}};
    vector<string> res = {""};
    
    for (auto& d : digits) {
        vector<string> temp;
        for (auto& c : m[d]) {
            for (auto& r : res) temp.push_back(r + c);
        }
        res = temp;
    }
    return res;
}
```

[Go Back](tree/tree-traversal?id=exercises)