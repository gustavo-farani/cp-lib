#include "polygon.cpp"
#include "../line/intersection.cpp"

// cuts the part of this convex (fails if concave) polygon
// situated in the counterclockwise half-plane
// with relation to the directed line l
Polygon Polygon::cut (Line l) {
    vector<PT> c;
    for (int i = 0; i < sides; i++) {
        if (sgn(l.side(p[i])) >= 0) c.pb(p[i]);
        if (l.opposes(p[i], p[next(i)])) {
            c.pb(intersection(l, Line(p[i], p[next(i)])));
        }
    }
    return c;
}