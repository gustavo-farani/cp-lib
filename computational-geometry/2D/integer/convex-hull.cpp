#include "point.cpp"

// v: two points never coincide, but the points may be all colinear
// (v is modified)
// return: convex-hull of v, with vertices in counterclockwise order,
// without contiguous colinear edges
// NOTE: at the first position of the outputed hull, there will
// be the lexicographically smallest point in v - the point with
// minimal x coordinate (and minimal y coordinate, in case of a tie)
// NOTE: raises RunTime Error is v is empty
// NOTE: if v contains only a single point, the hull will contain
// just that point
// NOTE: if the points in v are all colinear, the computed hull
// will be simply a line segment (the extreme points)
// PT operators required:
// lexicographic order, cross product, vector between points
vector<PT> convexHull (vector<PT>& v) {
    iter_swap(v.begin(), min_element(v.begin(), v.end()));
    sort(next(v.begin()), v.end(), [&] (PT p, PT q) {
        PT u = p - v[0], w = q - v[0];
        ll c = u % w;
        return c == 0 ? u < w : c > 0;
    });
    vector<PT> h(v.size());
    int sz = 0;
    for (PT p : v) {
        while (sz > 1 && (p - h[sz - 1]) % (h[sz - 1] - h[sz - 2]) >= 0) sz--;
        h[sz++] = p;
    }
    h.resize(sz);
    return h;
}

// "Onion Layers"
// Nested convex hulls of a set of points
// complexity: O(N^2)
// NOTE: v is NOT modified
vector<vector<PT>> convexLayers (vector<PT>& v) {
    int cnt = 0, n = v.size();
    vector<bool> taken(n);
    vector<vector<PT>> layer;
    while (cnt < n) {
        vi t;
        for (int i = 0; i < n; i++) {
            if (!taken[i]) {
                t.pb(i);
                if (v[i] < v[t[0]]) {
                    swap(t.back(), t[0]);
                }
            }
        }
        sort(next(t.begin()), t.end(), [&] (int i, int j) {
            PT u = v[i] - v[t[0]], w = v[j] - v[t[0]];
            ll c = u % w;
            if (c == 0) {
            	return u.x == 0 ? w < u : u < w;
            } else {
                return c >= 0;
            }
        });
        vi h(t.size());
        int sz = 0;
        for (int i : t) {
            while (sz > 1 && (v[i] - v[h[sz - 1]])
            % (v[h[sz - 1]] - v[h[sz - 2]]) > 0) sz--;
            h[sz++] = i;
        }
        h.resize(sz);
        layer.pb(vector<PT>());
        for (int i : h) {
            layer.back().pb(v[i]);
            taken[i] = true;
            cnt++;
        }
    }
    return layer;
}