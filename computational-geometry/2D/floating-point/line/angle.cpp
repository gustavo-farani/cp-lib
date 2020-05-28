#include "line.cpp"

const ld PI = acos(-1.0);

// angle of a line directed by d,
// measured counterclockwise from the x-axis
// return value ranges in [0, PI)
ld angle (const PT& d) {
    ld a = atan2(d.x, d.y);
    return a < 0 ? a + PI : a;
}