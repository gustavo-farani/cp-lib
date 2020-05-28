#include "manacher.cpp"
#include "../../data-structures/sparse-table/offline-subarray-maximum-query.cpp"
#include "../../problem-solving-paradigms/binary-search/monotonically-decreasing.cpp"

struct LongestSubPalindrome {  // TO BE TESTED
    vector<RangeMax<int>> st;
    template<class S>
    LongestSubPalindrome (const S& s) : st(2, RangeMax<int>(s.size())) {
        array<vi, 2> d(manacher(s));
        for (int z = 0; z < 2; z++) {
            for (int i = 0; i < s.size(); i++) {
                st[z].at(i) = d[z][i];
            }
            st[z].build(s.size());
        }
    }
    int query (int l, int r) {
        int x = r - l + 1;
        int e = search(1, x >> 1,
        [&] (int k) { return st[0].query(l + k, r - k + 1) >= k; });
        int o = search(0, (x >> 1) + 1,
        [&] (int k) { return st[1].query(l + k - 1, r - k + 1) >= k; });
        return max(e << 1, (o << 1) - 1);
    }
};