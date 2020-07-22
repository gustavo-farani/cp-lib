#include "polygon.cpp"

// Pick's Theorem
// computes the number of points with integer coordinates in this polygon
// polygon must not be self-intersecting
// boolean parameter border: whether the points lying on the boundary
// (on edges or vertices) should be counted or not
ll Polygon::latticePoints (bool border) {
    ll b = 0;
    for (int i = 0; i < sides; i++) {
        PT v = p[next(i)] - p[i];
        b += abs(gcd(v.x, v.y));  // C++ 17 only
    }
    return ((abs(shoelace()) - b + 2) >> 1) + border*b;
}