#include "suffix-array.cpp"

template<class S>
struct PatternMatching {
    int n;
    S t;
    vi cyc;
    PatternMatching (S&& t) :   // move constructor
        n(t.size()), t(t), cyc(suffixArray(t))
    {}
    int compare (int k, const S& s) {
        int ans = 0, i = cyc[k], j = 0;
        do {
            ans = t[i] - s[j];
            if (++i == n) i = 0;
            j++;
        } while (ans == 0 && i != cyc[k] && j < s.size());
        return ans;
    }
    int count (const S& s) {  // cylic substrings are included
        int l = 0, r = n;
        while (l != r) {
            int m = (l + r) >> 1;
            if (compare(m, s) < 0) l = m + 1;
            else r = m;
        }
        int first = l;
        l = 0, r = n;
        while (l != r) {
            int m = (l + r) >> 1;
            if (compare(m, s) <= 0) l = m + 1;
            else r = m;
        }
        int last = l;
        return last - first;
    }
};