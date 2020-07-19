#include "../vector/point.cpp"

struct Circle {
    PT c;
    double r;
    bool contains (PT p) {
        PT v = c - p;
        return sgn(dot(v, v) - r*r) <= 0;
    }
    // tangent.cpp
    pair<PT, PT> pointsOfTangency(PT p);
    pair<PT, PT> innerPointsOfTangency (Circle o);
    pair<PT, PT> outerPointsOfTangency(Circle o);
};