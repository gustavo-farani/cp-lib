#include "../vector/orientation.cpp"
#include "../line/vector-form.cpp"
#include "../line/intersection.cpp"
#include "polygon.cpp"

// whether points a and b are in separate half-planes w.r.t. line l
bool oppose (const Line& l, const PT& a, const PT& b) {
    return !l.contains(a) && !l.contains(b)
    && lt0((a - l.p ^ l.d)*(b - l.p ^ l.d));
}

// cuts the part of this convex (fails if concave)
// polygon situated in the counterclockwise
// half-plane w.r.t. the direction vector of line l
Polygon cut (const Polygon& p, const Line& l) {
    vector<PT> c;
    for (int i = 0; i < p.sides; i++) {
        if (ccw(l.d, p[i] - l.p)) c.pb(p[i]);
        if (oppose(l, p[i], p[i + 1])) {
            c.pb(l & Line(p[i], p[i + 1]));
        }
    }
    return c;
}