#include "knuth-morris-pratt.cpp"
#include <vector>
#include <string>
using namespace std;

typedef vector<int> vi;

string shortestPalindromicExtension (const string& t) {
    string s(t);
    reverse(s.begin(), s.end());
    vi len(longestPrefixMatching(s, t));
    int n = t.length();
    bool parity = 0;
    int mid = n - 1, l = n << 1;
    for (int i = 0; i < n; i++) {
        int m = n - (i + 1);
        if (len[i] >= m + 1 && l > ((n - m) << 1) - 1) {
            l = ((n - m) << 1) - 1;
            mid = i;
            parity = 1;
        }
        if (len[i] >= m && l > (n - m) << 1) {
            l = (n - m) << 1;
            mid = i;
            parity = 0;
        }
    }
    int m = n - (mid + 1);
    switch (parity) {
        case 0:
            return t.substr(0, mid + 1) + s.substr(m, n - m);
            break;
        case 1:
           return t.substr(0, mid + 1) + s.substr(m + 1, n - (m + 1));
    }
}