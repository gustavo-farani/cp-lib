#include "polygon.cpp"

double Polygon::shoelace () {
    double sum = 0;
    for (int i = 0; i < sides; i++) sum += cross(p[i], p[next(i)]);
    return sum;
}

double area (PT a, PT b, PT c) { return abs(cross(b - a, c - a))/2.0; }
// area of a polygon (it may be concave)
double Polygon::area () { return abs(shoelace())/2.0; }

// whether vertices are listed counterclockwise
bool Polygon::ccw () { return sgn(shoelace()) > 0; }

// whether vertices are listed clockwise
bool Polygon::cw () { return sgn(shoelace()) < 0; }