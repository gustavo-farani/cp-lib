#include "../polygon.cpp"

// v: two points never coincide, but the points may be all colinear
// (v is modified)
// return: convex-hull of v, with vertices in counterclockwise order,
// without contiguous colinear edges
// NOTE: at the first position of the outputed hull, there will
// be the lexicographically smallest point in v - the point with
// minimal x coordinate (and minimal y coordinate, in case of a tie)
// NOTE: if v contains only a single point, the hull will contain
// just that point
// NOTE: if the points in v are all colinear, the computed hull
// will be simply a line segment (the extreme points)
// PT operators required:
// lexicographic order, cross product, vector between points
vector<PT> convexHull (vector<PT>& v) {
    iter_swap(v.begin(), min_element(v.begin(), v.end()));
    sort(next(v.begin()), v.end(), [&] (const PT& p, const PT& q) {
        PT u = p - v[0], w = q - v[0];
        ll c = u ^ w;
        return c == 0 ? u < w : c > 0;
    });
    vector<PT> h(v.size());
    int sz = 0;
    for (const PT& p : v) {
        while (sz > 1 && (h[sz-1]-h[sz-2] ^ p-h[sz-1]) <= 0) sz--;
        h[sz++] = p;
    }
    h.resize(sz);
    return h;
}