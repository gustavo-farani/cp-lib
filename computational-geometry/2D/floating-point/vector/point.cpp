#include "../../../../boilerplate.cpp"

const double EPS = 1e-9;
int sgn (double t) { return abs(t) < EPS ? 0 : (t > 0) - (t < 0); }

struct PT {
    double x, y;
    PT (double x = 0, double y = 0) : x(x), y(y) {}
    PT operator- (PT o) { return PT(x - o.x, y - o.y); }
    PT operator* (double t) { return PT(x*t, y*t); }
    PT operator/ (double t) { return PT(x/t, y/t); }
    PT operator+ (PT o) { return PT(x + o.x, y + o.y); }
};

double dot (PT u, PT v) { return u.x*v.x + u.y*v.y; }
double cross (PT u, PT v) { return u.x*v.y - v.x*u.y; }
double orient (PT a, PT b, PT c) { return cross(b - a, c - a); }
double abs (PT p) { return hypot(p.x, p.y); }