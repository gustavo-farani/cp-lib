#include "point.cpp"

struct Line {
    PT v;
    double c;
    Line (PT v, double c) : v(v), c(c) {}
    Line (PT a, PT b) : v(b - a), c(cross(v, a)) {}

    // point location
    double side (PT p) { return cross(v, p) - c; }
    bool contains (PT p) { return sgn(cross(v, p) - c) == 0; }
    bool opposes (PT a, PT b) { return sgn(side(a))*sgn(side(b)) < 0; }

    // distances
    double dist (PT p) { return abs(side(p))/abs(v); }

    // movements
    void translate (PT u) { c += cross(v, u); }
    void reverse () { v.x = -v.x, v.y = -v.y, c = -c; }
};

// sorting points following direction vector of a line
struct LineSort {
    Line l;
    bool operator() (PT p, PT q) {
        return sgn(dot(l.v, p) - dot(l.v, q)) < 0;
    }
};

// single-point intersection
PT inter (Line l, Line r) { return (r.v*l.c - l.v*r.c)/cross(l.v, r.v); }

// orthogonality
Line perpThrough (Line l, PT p) { return Line(p, p + perp(l.v)); }
PT proj (Line l, PT p) {
    return p - perp(l.v)*l.side(p)/dot(l.v, l.v);
}
PT reflect (Line l, PT p) {
    return p - perp(l.v)*l.side(p)*2.0/dot(l.v, l.v);
}
Line perpBisector (PT a, PT b) { return perpThrough(Line(a, b), (a + b)/2.0); }

// bissectors
Line intBisector (Line l, Line r) {
    return Line(r.v/abs(r.v) + l.v/abs(l.v), r.c/abs(r.v) + l.c/abs(l.v));
}
Line extBisector (Line l, Line r) {
    return Line(r.v/abs(r.v) - l.v/abs(l.v), r.c/abs(r.v) - l.c/abs(l.v));
}