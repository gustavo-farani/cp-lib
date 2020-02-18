#include <vector>
#include <algorithm>
using namespace std;

typedef vector<int> vi;

template<class S>
vi zFunction (const S& s) {
    int n = s.size();
    vi z(n);
    int l, r = -1;   // boundaries of the right-most segment match
    for (int i = 1; i < n; i++) {  // iteration starts from 1 because z[0] is irrelevant
        if (i <= r) z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
            l = i;
            r++;
        }
    }
    return z;
}

#include <bits/stdc++.h>

int main () {
    string s;
    cin >> s;
    vi z(zFunction(s));
    for (int i = 0; i < s.size(); i++) {
        cout << z[i] << ' ';
    }
    cout << '\n';
}