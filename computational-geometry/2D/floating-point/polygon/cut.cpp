#include "polygon.cpp"
#include "../line/line.cpp"

// cuts the part of this convex (fails if concave) polygon
// situated in the counterclockwise half-plane
// with relation to the line directed by v and containing q
Polygon Polygon::cut (const PT& q, const PT& v) {
    vector<PT> c;
    for (int i = 0; i < sides; i++) {
        if (gt0(v % (p[i] - q))) c.pb(p[i]);
        if (Line::oppose(q, v, p[i], p[i + 1])) {
            c.pb(Line::intersection(q, v, p[i], p[i + 1] - p[i]));
        }
    }
    return c;
}