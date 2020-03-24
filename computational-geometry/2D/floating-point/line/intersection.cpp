#include "../point.cpp"

struct Line {
    PT p, v;
    Line (const PT& a, const PT& b) {
        p = a;
        v = b - a;
    }
    // assumes v and o.v are not parallel, that is, (v ^ o.v) != 0
    PT operator^ (const Line &o) {
        ld t = ((o.p - p) ^ o.v)/(v ^ o.v);
        return p + v*t;
    }
};