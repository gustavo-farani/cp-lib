#include "point.cpp"

const ld PI = acos(-1.0);

// angle from p to q (counterclockwise), measured in radians
ld angle (const PT& p, const PT& q) {
    ld a = atan2(p % q, p*q);
    return a < 0 ? a + 2*PI : a;
}

ld polarAngle (const PT& v) {
    ld a = atan2(v.y, v.x);
    return a < 0 ? a + 2*PI : a;
}