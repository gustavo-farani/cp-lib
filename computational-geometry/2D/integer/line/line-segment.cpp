#include "../vector/point.cpp"

namespace LineSegment {
    bool rect (const PT& a, const PT& b, const PT& p) {
        ll l, r, u, d;
        tie(l, r) = minmax(a.x, b.x);
        tie(d, u) = minmax(a.y, b.y);
        return l <= p.x && p.x <= r && d <= p.y && p.y <= u;
    }
    bool intersect (const PT& a, const PT& b, const PT& c, const PT& d) {
        PT u = b - a, v = d - c;
        ll ca = v % (a - c), cb = v % (b - c), cc = u % (c - a), cd = u % (d - a);
        return ca*cb < 0 && cc*cd < 0
        || ca == 0 && rect(c, d, a) || cb == 0 && rect(c, d, b)
        || cc == 0 && rect(a, b, c) || cd == 0 && rect(a, b, d);
    }
};