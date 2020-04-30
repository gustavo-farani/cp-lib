#include "../../template.cpp"

template<class T>
struct DisjointRanges {
    map<int, pair<int, T>> s;
    vector<tuple<int, int, T>> update (int l, int r, T x) {  // closed intervals
        vector<tuple<int, int, T>> bye;
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
                bye.pb({l, it->second.first, it->second.second});
                it->second.first = l - 1;
            }
        }
        for (auto it = first; it != last; it = s.erase(it)) {
            bye.pb({it->first, it->second.first, it->second.second});
        }
        s.emplace_hint(last, l, make_pair(r, x));
        return bye;
    }
};