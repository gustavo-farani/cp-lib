#include "longest-common-prefix-array.cpp"
#include "sort-suffixes.cpp"

// lexicographically smallest longest common substring
string longestCommonSubstring (const string& s, const string& t) {
    string c = s + '$' + t;
    int m = c.length();
    vi ord, sa, lcp = longestCommonPrefixArray(c, ord, sa);
    // 0: starting position of a suffix from s
    // 1: starting position of a suffix from t
    auto who = [&] (int i) { return i > s.length(); };
    ii ans = {0, 0};
    // ignore i == 0: there will be the suffix ('$' + t)
    for (int k = 1; k < m - 1; k++) {
        int i = sa[k], j = sa[k + 1];
        if (who(i) ^ who(j) && lcp[k] > ans.second) {
            ans.second = lcp[k];
            ans.first = who(i) ? j : i;
        }
    }
    return s.substr(ans.first, ans.second);
}