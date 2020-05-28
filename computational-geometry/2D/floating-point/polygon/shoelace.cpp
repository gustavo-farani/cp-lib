#include "polygon.cpp"

ld Polygon::shoelace () {
    ld sum = 0;
    for (int i = 0; i < sides; i++) sum += p[i] % p[i + 1];
    return sum;
}
// computes area for either concave or convex polygons,
// with vertices listed either clockwise or counterclockwise
ld Polygon::area () { return abs(shoelace())/2.0; }
// tests if polygon vertices are listed counterclockwise
bool Polygon::ccw () { return shoelace() > 0; }
// tests if polygon vertices are listed clockwise
bool Polygon::cw () { return shoelace() < 0; }