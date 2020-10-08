#include "../../boilerplate.cpp"

template<class T>
struct DisjointRanges {
    map<int, pair<int, T>> s;
    vector<tuple<int, int, T>> update (int l, int r, T x) {  // closed intervals
        vector<tuple<int, int, T>> bye;
        auto last = s.upper_bound(r);
        if (last != s.begin()) {
            auto it = prev(last);
            if (it->se.fi > r) {
                last = s.emplace_hint(last, r + 1, it->se);
                it->se.fi = r;
            }
        }
        auto init = s.lower_bound(l);
        if (first != s.begin()) {
            auto it = prev(init);
            if (it->se.fi >= l) {
                bye.pb({l, it->se.fi, it->se.se});
                it->se.fi = l - 1;
            }
        }
        for (auto it = init; it != last; it = s.erase(it)) {
            bye.pb({it->fi, it->se.fi, it->se.se});
        }
        s.emplace_hint(last, l, make_pair(r, x));
        return bye;
    }
};