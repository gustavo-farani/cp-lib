#include <vector>
#include "prefix-function.cpp"
using namespace std;

typedef vector<int> vi;

template<class S>
vi longestPrefixMatching (const S& s, const S& t) {
    int n = s.size(), m = t.size();
    vi pi(prefixFunction(s)), len(m);
    int prev = 0;
    for (int i = 0; i < m; i++) {
        int j = (prev == n ? pi[n - 1] : prev);
        while (j > 0 && t[i] != s[j]) {
            j = pi[j - 1];
        }
        int cur = (t[i] == s[j] ? j + 1 : 0);
        prev = len[i] = cur;
    }
    return len;   // len[i] = length of the longest prefix of s ENDING at t[i]
}

template<class S>
vector<bool> patternMatching (const S& s, const S& t) {
    int n = s.size(), m = t.size();
    vi len(longestPrefixMatching(s, t));
    vector<bool> match(m);
    for (int i = 0; i < m; i++) match[i] = (len[i] == n);
    return match; // match at ending positions: match[i] = (t.substr(i - n + 1, n) == s)
}