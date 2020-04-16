#include <cmath>
#include "vector-form.cpp"

const ld PI = acos(-1.0);

// angle of a line measured counter-clock-wise from the x-axis
// return value ranges in [0, PI)
ld Line::angle () const {
    ld a = atan2(d.x, d.y);
    return a < 0 ? a + PI : a;
}