#include "../../../../boilerplate.cpp"

const ld EPS = 1e-22L;
int sgn (ld t) { return abs(t) < EPS ? 0 : (t > 0) - (t < 0); }

struct PT {
    ld x, y;
    PT (ld x = 0.0L, ld y = 0.0L) : x(x), y(y) {}
    PT operator- (PT o) { return {x - o.x, y - o.y}; }
    PT operator* (ld t) { return {x*t, y*t}; }
    PT operator/ (ld t) { return {x/t, y/t}; }
    PT operator+ (PT o) { return {x + o.x, y + o.y}; }
};

ld dot (PT u, PT v) { return u.x*v.x + u.y*v.y; }
ld cross (PT u, PT v) { return u.x*v.y - v.x*u.y; }
ld orient (PT a, PT b, PT c) { return cross(b - a, c - a); }
ld abs (PT p) { return hypot(p.x, p.y); }