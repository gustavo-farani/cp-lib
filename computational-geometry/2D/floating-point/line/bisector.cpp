#include "line.cpp"
#include "../vector/orthogonality.cpp"

Line perpBisector (PT a, PT b) {
    PT m = (a + b)/2.0L, v = perp(b - a);
    return Line(v, cross(v, m));
}

// angle bissector whose direction vector
// points between the direction vectos of l, r
Line intBisector (Line l, Line r) {
    return Line(r.v/abs(r.v) + l.v/abs(l.v), r.c/abs(r.v) + l.c/abs(l.v));
}
// the other angle bissector, perpendicular to the intBisector
Line extBisector (Line l, Line r) {
    return Line(r.v/abs(r.v) - l.v/abs(l.v), r.c/abs(r.v) - l.c/abs(l.v));
}