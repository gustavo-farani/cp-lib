#include "../vector/point.cpp"
#include "../vector/orientation.cpp"

struct LineSegment {  // TO BE TESTED
    pair<PT, PT> p;
    LineSegment (const PT& a, const PT& b) : p(a, b) {}
    bool contains (const PT& o) {
        return colinear(p.first, p.second, o)
        && (o - p.first)*(o - p.second) <= 0;
    }
};