#include "point.cpp"

const ld PI = acos(-1.0L);
ld angle (PT p) { return atan2(p.y, p.x); }
ld angle (PT u, PT v) { return atan2(cross(u, v), dot(u, v)); }
PT rotate (PT v, ld a) {  // CCW
    return {v.x*cos(a) - v.y*sin(a), v.x*sin(a) + v.y*cos(a)};
}