#include "polygon.cpp"

// returns 0, if polygon is not simple, or concave
// returns 1, if polygon is convex, with vertices
// listed counterclockwise
// returns -1, if polygon is convex, with vertices
// listed clockwise
int Polygon::convex () {
    bool pos = false, neg = false;
    for (int i = 0; i < sides; i++) {
        int j = next(i), k = next(j);
        int s = sgn(orient(p[i], p[j], p[k]));
        neg |= s < 0;
        pos |= s > 0;
    }
    return !(pos && neg) ? pos - neg : 0;
}