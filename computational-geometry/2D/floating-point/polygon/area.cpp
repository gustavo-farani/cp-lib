#include "polygon.cpp"

ld Polygon::shoelace () {
    ld sum = 0;
    for (int i = 0; i < sides; i++) sum += cross(p[i], p[next(i)]);
    return sum;
}

ld area (PT a, PT b, PT c) { return abs(cross(b - a, c - a))/2.0L; }
// area of a polygon (it may be concave)
ld Polygon::area () { return abs(shoelace())/2.0L; }

// whether vertices are listed counterclockwise
bool Polygon::ccw () { return sgn(shoelace()) > 0; }

// whether vertices are listed clockwise
bool Polygon::cw () { return sgn(shoelace()) < 0; }