#include "point.cpp"

const ld PI = acos(-1.0);

// conversion from degrees to radians
ld degtorad (ld deg) { return deg*PI/180.0; }

namespace CCW {
    // rotate 2D vector p by t radians counter-clock-wise around the origin
    PT rotate (const PT& p, ld t) {
        return PT(p.x*cos(t) - p.y*sin(t), p.x*sin(t) + p.y*cos(t));
    }
}

namespace CW {
    // rotate 2D vector p by t radians clock-wise around the origin
    PT rotate (const PT& p, ld t) {
        return PT(p.x*cos(t) + p.y*sin(t), p.x*sin(t) - p.y*cos(t));
    }
}