#include "line.cpp"
#include "../vector/orthogonality.cpp"

Line perpBisector (PT a, PT b) {
    PT m = (a + b)/2.0, v = perp(b - a);
    return Line(v, cross(v, m));
}
Line intBisector (Line l, Line r) {
    return Line(r.v/abs(r.v) + l.v/abs(l.v), r.c/abs(r.v) + l.c/abs(l.v));
}
Line extBisector (Line l, Line r) {
    return Line(r.v/abs(r.v) - l.v/abs(l.v), r.c/abs(r.v) - l.c/abs(l.v));
}