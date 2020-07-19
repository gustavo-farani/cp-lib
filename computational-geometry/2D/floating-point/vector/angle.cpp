#include "point.cpp"

const double PI = acos(-1.0);
double arg (PT p) { return atan2(p.y, p.x); }
PT rot (PT v, double a) {  // CCW
    return PT(v.x*cos(a) - v.y*sin(a), v.x*sin(a) + v.y*cos(a));
}