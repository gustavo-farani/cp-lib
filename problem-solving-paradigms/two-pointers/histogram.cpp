#include "../../boilerplate.cpp"

// lim[i] = {l, r}, both inclusive pointers bounding the
// neighbourhood under the domain of v[i]
// l: the leftmost index j such that,
// for each k in [j, i], !leftStop(v[k], v[i])
// r: the rightmost index j such that,
// for each k in [i, j], !rightStop(v[k], v[i])
template<class S, class L, class R>
vector<ii> delimiters (const S& v, L leftStop, R rightStop) {
    int n = v.size();
    vector<ii> lim(n), s;
    for (int i = 0; i < n; i++) {
        while (!s.empty() && !leftStop(s.back().fi, v[i])) s.pop_back();
        lim[i].fi = s.empty() ? 0 : s.back().se + 1;
        s.emplace_back(v[i], i);
    }
    s.clear();
    for (int i = n - 1; i >= 0; i--) {
        while (!s.empty() && !rightStop(s.back().fi, v[i])) s.pop_back();
        lim[i].se = s.empty() ? n - 1 : s.back().se - 1;
        s.emplace_back(v[i], i);
    }
    return lim;
}