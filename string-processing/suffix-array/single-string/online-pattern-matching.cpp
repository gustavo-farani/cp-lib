#include "sort-suffixes.cpp"
#include "../../../problem-solving-paradigms/binary-search/monotonically-increasing.cpp"

template<class S>
struct PatternMatching {
    int n;
    S t;
    vi sa;
    PatternMatching (S&& t) : n(t.size()), t(t), sa(sortSuffixes(t)) {}
    int comp (int k, const S& s) {
        auto mis = mismatch(s.begin(), s.end(), t.begin() + sa[k]);
        if (mis.fi == s.end()) {
            return 0;
        } else if (mis.se == t.end()) {
            return -1;
        } else {
            return *mis.se - *mis.fi;
        }
    };
    // returns start positions for matchings of s in t
    // (may not be in ascending order)
    vi match (const S& s) {
        int first = search(0, n - 1, [&] (int k) { return comp(k, s) >= 0; });
        int last = search(0, n - 1, [&] (int k) { return comp(k, s) > 0; });
        vi ans;
        for (int i = first; i < last; i++) ans.pb(sa[i]);
        return ans;
    }
    // counts how many times s appears as substring in t
    int count (const S& s) {
        int first = search(0, n - 1, [&] (int k) { return comp(k, s) >= 0; });
        int last = search(0, n - 1, [&] (int k) { return comp(k, s) > 0; });
        return last - first;
    }
};