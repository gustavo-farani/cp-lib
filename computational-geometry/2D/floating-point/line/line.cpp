#include "../vector/point.cpp"

struct Line {
    PT v;
    double c;
    Line (PT v, double c) : v(v), c(c) {}
    Line (PT a, PT b) : v(b - a), c(cross(v, a)) {}
    double side (PT p) { return cross(v, p) - c; }
    bool contains (PT p) { return sgn(side(p)) == 0; }
    bool opposes (PT a, PT b) { return sgn(side(a))*sgn(side(b)) < 0; }
    double dist (PT p) { return abs(side(p))/abs(v); }
    // move.cpp
    void translate(PT u);
    void reverse();
    // orthogonality.cpp
    Line perpThrough(PT p);
    PT proj(PT p);
    PT reflect(PT p);
};