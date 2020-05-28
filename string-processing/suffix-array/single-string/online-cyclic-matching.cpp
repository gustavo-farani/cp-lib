#include "sort-cyclic-shifts.cpp"
#include "../../../problem-solving-paradigms/binary-search/monotonically-increasing.cpp"

template<class S>
struct CyclicMatching {  // match as cyclic substring
    int n;
    S t;
    vi sa;
    CyclicMatching (S&& t) : n(t.size()), t(t), sa(sortCyclicShifts(t)) {}
    int comp (int k, const S& s) {
        int ans = 0, i = sa[k], j = 0;
        do {
            ans = t[i] - s[j];
            if (++i == n) i = 0;
            j++;
        } while (ans == 0 && i != sa[k] && j < s.size());
        return ans;
    }
    // returns start positions for all matchings of s as cyclic substring of t
    vi match (const S& s) {
        int first = search(0, n - 1, [&] (int k) { return comp(k, s) >= 0; });
        int last = search(0, n - 1, [&] (int k) { return comp(k, s) > 0; });
        vi ans;
        for (int i = first; i < last; i++) ans.pb(sa[i]);
        return ans;
    }
    // counts how many times s appears as cyclic substring of t
    int count (const S& s) {
        int first = search(0, n - 1, [&] (int i) { return comp(i, s) >= 0; });
        int last = search(0, n - 1, [&] (int i) { return comp(i, s) > 0; });
        return last - first;
    }
};