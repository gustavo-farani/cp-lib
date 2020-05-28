#include "line.cpp"

namespace LineSegment {
    // tests if p is inside or is an extreme point of line segment (a, b)
    bool contains (const PT& a, const PT& b, const PT& p) {
        PT u = p - a, v = p - b;
        return eq0(u % v) && lt0(u*v);
    }
    // tests whether line segments (a, b) and (c, d) have any point in common
    bool intersect (const PT& a, const PT& b, const PT& c, const PT& d) {
        PT u = b - a, v = d - c;
        return Line::oppose(c, v, a, b) && Line::oppose(a, u, c, d)
        || contains(c, d, a) || contains(c, d, b)
        || contains(a, b, c) || contains(a, b, d);
    }
    // ans: vector with intersection points of line segments (a, b) and (c, d),
    // sorted in lexicographic order
    // if line segments (a, b) and (c, d)...
    //   don't have any point in common, ans is empty;
    //   have a single point in common, ans contains just that point;
    //   intersect at a whole line segment, ans holds its extreme points;
    vector<PT> intersection (const PT& a, const PT& b, const PT& c, const PT& d) {
        vector<PT> ans;
        PT u = b - a, v = d - c;
        if (Line::oppose(c, v, a, b) && Line::oppose(a, u, c, d)) {
            ans.pb(Line::intersection(a, u, c, v));
        } else {
            if (contains(c, d, a)) ans.pb(a);
            if (contains(c, d, b)) ans.pb(b);
            if (contains(a, b, c)) ans.pb(c);
            if (contains(a, b, d)) ans.pb(d);
            sort(ans.begin(), ans.end());
            ans.resize(unique(ans.begin(), ans.end()) - ans.begin());
        }
        return ans;
    }
}