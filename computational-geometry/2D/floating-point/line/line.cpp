#include "../vector/reflection.cpp"

namespace Line {
    // compute single-point intersection between
    // the line through p directed by u and the line through q directed by v
    // lines are assumed to be concurrent
    PT intersection (const PT& p, const PT& u, const PT& q, const PT& v) {
        ld t = ((q - p) % v)/(u % v);
        return p + u*t;
    }
    // tests if points a and b are strictly in separate half-planes
    // with relation to the line through p directed by v
    bool oppose (const PT& p, const PT& v, const PT& a, const PT& b) {
        return ((a - p) % v)*((b - p) % v) < 0;
    }
    // reflects point q with relation to the line through p directed by v
    PT reflect (const PT& p, const PT& v, const PT& q) {  // TO BE TESTED
        return p + reflect(q - p, v);
    }
};