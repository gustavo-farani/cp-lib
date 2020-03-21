#include <cmath>
#include "../floating-point/point.cpp"

typedef double ld;

const ld PI = acos(-1.0L);

ld angleCCW (const PT& p, const PT& q) {
    ld a = atan2(p ^ q, p*q);
    return (a < 0 ? a + 2*PI : a);
}

ld polarAngle (const PT& p) {
    ld a = atan2(p.y, p.x);
    return (a < 0 ? a + 2*PI : a);
}