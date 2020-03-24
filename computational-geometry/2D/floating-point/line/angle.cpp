#include "../point.cpp"

const ld PI = acos(-1.0);

// v: direction vector of 2D line touching the origin
// returns the counter-clock-wise angle [0, PI) w.r.t. the x-axis
ld angle (const PT& v) {
    ld a = atan2(v.x, v.y);
    return (a < 0 ? a + PI : a);
}
// NOTE: angle(v) == angle(-v), for any 2D vector v