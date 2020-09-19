#include "sort-suffixes.cpp"

// sa: suffix array of string s
// lcp[i]: length of the longest common prefix between
// suffixes starting at indices sa[i] and sa[i + 1]
// ord may come as an empty vector
template<class S>
vi longestCommonPrefixArray (const S& s, vi& ord, vi& sa) {
    int n = s.size(), len = 0;
    sa = sortSuffixes(s, ord);
    vi lcp(n - 1);
    for (int i = 0; i < n; i++) {
        if (ord[i] == n - 1) {
            len = 0;
        } else {
            int j = sa[ord[i] + 1];
            while (i + len < n && j + len < n
            && s[i + len] == s[j + len]) len++;
            lcp[ord[i]] = len;
            len = max(0, len - 1);
        }
    }
    return lcp;
}

template<class S>
vi longestCommonPrefixArray (const S& s) {
    vi ord, sa;
    return longestCommonPrefixArray(s, ord, sa);
}