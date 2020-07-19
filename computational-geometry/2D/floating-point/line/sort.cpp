#include "line.cpp"

// sorting points following direction vector of a line
struct LineSort {
    Line l;
    bool operator() (PT p, PT q) {
        return sgn(dot(l.v, p) - dot(l.v, q)) < 0;
    }
};