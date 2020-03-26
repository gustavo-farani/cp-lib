#include <cmath>
#include "../vector-form.cpp"

typedef double ld;

const ld PI = acos(-1.0);

// angle of a line measured counter-clock-wise from the x-axis
// return value ranges in [0, PI)
ld angle (const Line& l) {
    ld a = atan2(l.d.x, l.d.y);
    return (a < 0 ? a + PI : a);
}