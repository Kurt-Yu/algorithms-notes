#include <bits/stdc++.h>

using namespace std;

int main() {
    string n;
    cin >> n;
    for (auto c : n) if (c == '7') {
        cout << "Yes" << endl;
        return 0;
    }
    cout << "No" << endl;
    return 0;
}