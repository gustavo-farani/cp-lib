#include "../vector/point.cpp"

struct Circle {
    PT c;
    ld r;
    Circle (ld x = 0, ld y = 0, ld r = 0) : c(x, y), r(r) {}
    Circle (PT c, ld r) : c(c), r(r) {}
    bool contains (PT p) {
        PT v = c - p;
        return sgn(dot(v, v) - r*r) <= 0;
    }
    // tangent.cpp
    pair<PT, PT> pointsOfTangency(PT p);
    pair<PT, PT> innerPointsOfTangency (Circle o);
    pair<PT, PT> outerPointsOfTangency(Circle o);
};