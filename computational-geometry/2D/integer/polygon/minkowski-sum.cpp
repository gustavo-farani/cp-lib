#include "polygon.cpp"

// Reflects this polygon with relation to the origin
// NOTE: if the vertices in this polygon are listed
// counterclockwise, the vertices in the outputed polygon
// will be listed counterclockwise too (the same holds for
// the clockwise order)
Polygon Polygon::operator- () {
    vector<PT> o;
    for (int i = 0; i < sides; i++) o.pb(p[i]*-1);
    return o;
}

// auxiliar function for minkowskiSum
vector<PT> Polygon::getEdges () {
    vector<PT> ans(sides);
    rotate(p.begin(), min_element(p.begin(), p.end()), p.end());
    for (int i = 0; i < sides; i++) ans[i] = p[next(i)] - p[i];
    return ans;
}

// Computes the polygon representing the Minkowski sum of a, b
// Pre-conditions for a, b:
// -> non-empty (at least one vertex)
// -> convex, strictly or not
// (there may be three consecutive vertices that are colinear)
// -> vertices listed counterclockwise
// -> vertices pairwise distinct
// Post-conditions for returned polygon:
// -> exactly the same as for a, b
// complexity: O(sides)
// NOTE: the number of vertices in the outputed polygon won't
// exceed a.sides + b.sides
Polygon minkowskiSum (Polygon &a, Polygon &b) {
    auto ea = a.getEdges(), eb = b.getEdges();
    vector<PT> ans(ea.size() + eb.size());
    auto half = [&] (const PT& v) {
        return v.x < 0 || v.x == 0 && v.y < 0;
    };
    merge(ea.begin(), ea.end(), eb.begin(), eb.end(), ans.begin(),
    [&] (const PT& u, const PT& v) {
        return make_pair(half(u), 0LL) < make_pair(half(v), u % v);
    });
    ans[0] = ans[0] + a.p[0] + b.p[0];
    partial_sum(ans.begin(), ans.end(), ans.begin());
    if (ans[0] == ans.back()) ans.pop_back();
    return ans;
}