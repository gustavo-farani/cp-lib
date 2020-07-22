#include "point.cpp"

const double PI = acos(-1.0);
double angle (PT p) { return atan2(p.y, p.x); }
double angle (PT u, PT v) { return atan2(cross(u, v), dot(u, v)); }
PT rotate (PT v, double a) {  // CCW
    return PT(v.x*cos(a) - v.y*sin(a), v.x*sin(a) + v.y*cos(a));
}