#include "../vector/point.cpp"
#include "../vector/orientation.cpp"

struct LineSegment {
    PT a, b;
    LineSegment (const PT& a, const PT& b) : a(a), b(b) {}
    bool contains (const PT& o) const {
        ll l, r, u, d;
        tie(l, r) = minmax(a.x, b.x);
        tie(d, u) = minmax(a.y, b.y);
        return l <= o.x && o.x <= r && d <= o.y && o.y <= u;
    }  // point o is assumed to be colinear with a and b
    bool operator&& (const LineSegment& o) {
        PT u = b - a, v = o.b - o.a;
        ll ua = u ^ o.a-a, ub = u ^ o.b-a;
        ll va = v ^ a-o.a, vb = v ^ b-o.b;
        return ua*ub < 0 && va*vb < 0
        || ua == 0 && contains(o.a)
        || ub == 0 && contains(o.b)
        || va == 0 && o.contains(a)
        || vb == 0 && o.contains(b);
    }  // test line-segment intersection
};