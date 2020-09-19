#include "../point.cpp"

// Andrew's Monotone Chain Algorithm
// v: points ALREADY SORTED lexicographically and pairwise distinct
// return: convex-hull of v, with vertices in counterclockwise order,
// without contiguous colinear edges
// NOTE: if v is empty, it won't raise an exception
// NOTE: if v contains only a single point, the hull will contain
// just that point
// NOTE: if the points in v are all colinear, the computed hull
// will be simply a line segment (the extreme points)
vector<PT> convexHull (const vector<PT>& v) {
    int n = v.size();
    if (n <= 1) {
        return v;
    } else {
        vector<PT> h;
        int i = 0, j = 1;
        for (int k = 0; k < n; k++) {
            while (i > j && orient(h[i - 2], v[k], h[i - 1]) >= 0) {
                h.resize(--i);
            }
            h.resize(++i, v[k]);
        }
        j += --i;
        for (int k = n; k--;) {  // same loop as before (copy and paste it!)
            while (i > j && orient(h[i - 2], v[k], h[i - 1]) >= 0) {
                h.resize(--i);
            }
            h.resize(++i, v[k]);
        }
        h.pop_back();  // h.back() == h.front()
        return h;
    }
}