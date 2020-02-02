#include "point.cpp"

struct Line {
    PT p, v;
    Line (PT a, PT b) {
        p = a;
        v = b - a;
    }
    PT operator^ (Line o) {
        ld t = ((o.p - p) ^ o.v)/(v ^ o.v);
        return p + (v * t);
    }
};