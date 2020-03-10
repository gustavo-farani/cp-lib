#include <cmath>
#include "point.cpp"

typedef long double ld;

PT rotateCCW (PT p, ld t) {
    return PT{p.x*cos(t) - p.y*sin(t), p.x*sin(t) + p.y*cos(t)};
}

PT rotateCW (PT p, ld t) {
    return PT{p.x*cos(t) + p.y*sin(t), p.x*sin(t) - p.y*cos(t)};
}