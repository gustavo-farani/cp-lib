#include "../../../data-structures/sparse-table/offline-subarray-minimum-query.cpp"
#include "longest-common-prefix-array.cpp"

template<class S>
struct SubstringComparison {
    int n;
    S s;
    RangeMin<int> st;
    vi ord;
    SubstringComparison (S&& s) :
        s(s), n(s.size()), st(n - 1)
    {
        vi lcp = longestCommonPrefixArray(s, ord);
        for (int i = 0; i < n - 1; i++) st.at(i) = lcp[i];
        st.build(n - 1);
    }
    // longest common prefix between suffixes starting at i and j
    int query (int i, int j) {
        if (i == j) {
            return n - i;
        } else {
            int l = ord[i], r = ord[j];
            if (l > r) swap(l, r);
            return st.query(l, r - 1);
        }
    }
    // compares substrings s[l1..r1] and s[l2..r2] lexicographically
    // return -1, if s[l1..r1] < s[l2..r2]
    // return 0, if s[l1..r1] == s[l2..r2]
    // return 1, if s[l1..r1] > s[l2..r2]
    int comp (int l1, int r1, int l2, int r2) {
        int k = min({r1 - l1 + 1, r2 - l2 + 1, query(l1, l2)});
        bool e1 = l1 + k > r1, e2 = l2 + k > r2;
        if (e1 && e2) {
            return 0;
        } else if (e1) {
            return -1;
        } else if (e2) {
            return 1;
        } else if (s[l1 + k] < s[l2 + k]) {
            return -1;
        } else {
            return 1;
        }
    }
};