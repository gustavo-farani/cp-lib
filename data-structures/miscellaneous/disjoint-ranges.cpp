#include "../../template.cpp"

template<class T>
struct DisjointRanges {
    struct Range {
        int l, r;
        T x;
        Range (int l, const pair<int, T>& p) :
            l(l), r(p.first), x(p.second)
        {}
    };
    map<int, pair<int, T>> s;
    vector<Range> update (int l, int r, T x) {  // closed intervals
        vector<Range> bye;
        auto last = s.upper_bound(r);
        if (last != s.begin()) {
            auto it = prev(last);
            if (it->second.first > r) {
                last = s.emplace_hint(last, r + 1, it->second);
                it->second.first = r;
            }
        }
        auto first = s.lower_bound(l);
        if (first != s.begin()) {
            auto it = prev(first);
            if (it->second.first >= l) {
                bye.emplace_back(l, it->second);
                it->second.first = l - 1;
            }
        }
        while (first != last) {
            bye.emplace_back(first->first, first->second);
            first = s.erase(first);
        }
        s.emplace_hint(last, l, make_pair(r, x));
        return bye;
    }
};