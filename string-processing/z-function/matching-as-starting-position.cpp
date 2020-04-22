#include "z-function.cpp"

template<class S>
vi longestPrefixMatching (const S& s, const S& t) {
    int n = s.size(), m = t.size();
    vi z(zFunction(s));
    int l = 0, r = -1;
    vi len(m);
    for (int i = 0; i < m; i++) {
        if (i <= r) len[i] = min(r - i + 1, z[i - l]);
        while (len[i] < n && i + len[i] < m && s[len[i]] == t[i + len[i]]) {
            len[i]++;
            l = i;
            r++;
        }
    }
    return len; // len[i] = length of the longest prefix of s STARTING at t[i]
}

template<class S>
vector<bool> patternMatching (const S& s, const S& t) {
    int n = s.size(), m = t.size();
    vi len(longestPrefixMatching(s, t));
    vector<bool> match;
    for (int i = 0; i < m; i++) match[i] = (len[i] == n);
    return match;  // match at starting position: match[i] = (t.substr(i, n) == s)
}