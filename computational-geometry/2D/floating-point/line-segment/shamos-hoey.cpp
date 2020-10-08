#include "intersection.cpp"

// auxiliar function for intersect
// determines the y-position of line segment [a, b]
// with relation to the vertical line sweep at x
ld ord (pair<PT, PT>& s, ld x) {
    auto [a, b] = s;
    ld dx = b.x - a.x, ans = a.y;
    if (sgn(dx) != 0) ans += (b.y - a.y)/dx*(x - a.x);
    return ans;
}
    
// tests if there is any pair of intersecting segments in v,
// saving their indices into ans
// complexity: O(N lg N)
bool intersect (vector<pair<PT, PT>>& v, ii& ans) {
    vector<tuple<ld, bool, ld, int>> e;
    for (int i = 0; i < v.size(); i++) {
        if (v[i].second < v[i].first) swap(v[i].first, v[i].second);
        e.emplace_back(v[i].first.x, false, v[i].first.y, i);
        e.emplace_back(v[i].second.x, true, v[i].second.y, i);
    }
    sort(e.begin(), e.end());
    set<int, function<bool(int, int)>> s([&] (int i, int j) {
        ld x = max(v[i].first.x, v[j].first.x);
        return sgn(ord(v[i], x) - ord(v[j], x)) < 0;
    });
    for (auto [x, close, y, i] : e) {
        auto suc = s.upper_bound(i);
        if (close) {
            auto it = s.find(i);
            if (suc != s.end() && it != s.begin()) {
                auto pre = prev(it);
                if (intersect(v[*pre], v[*suc])) {
                    ans = {*pre, *suc};
                    return true;
                }
            }
            s.erase(it);
        } else {
            auto pre = suc == s.begin() ? s.end() : prev(suc);
            if (pre != s.end() && intersect(v[*pre], v[i])) {
                ans = {*pre, i};
                return true;
            }
            if (suc != s.end() && intersect(v[*suc], v[i])) {
                ans = {*suc, i};
                return true;
            }
            s.insert(suc, i);
        }
    }
    return false;
}
// tested sucessfully in Codeforces problem 1359F
//https://codeforces.com/contest/1359/submission/93639470