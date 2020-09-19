#include "../../../../boilerplate.cpp"

// total length of regions where at least k segments in v overlap
// b == 0: segments are treated as line intervals
// b == 1: segments are treated as array ranges
int overlapLength (const vector<ii>& v, int k, bool b) {
    vector<pair<int, bool>> e;
    for (auto [l, r] : v) {
        e.emplace_back(l, false);
        e.emplace_back(r, true);
    }
    sort(e.begin(), e.end());
    int open = 0, total = 0, l;
    for (auto [r, close] : e) {
        if (close) {
            if (open-- == k) {
                total += r - l + b;
            }
        } else if (++open == k) {
            l = r;
        }
    }
    return total;
}