#include "line.cpp"
#include "../vector/orthogonality.cpp"

Line Line::perpThrough (PT p) {
    PT u = perp(v);
    return Line(u, cross(u, p));
}
PT Line::proj (PT p) { return p - perp(v)*side(p)/dot(v, v); }
PT Line::reflect (PT p) { return p - perp(v)*side(p)*2.0/dot(v, v); }