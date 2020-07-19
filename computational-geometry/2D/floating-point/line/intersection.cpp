#include "line.cpp"

// computes single-point intersection between lines
// assumes lines intersect properly
PT intersection (Line l, Line r) {
    return (r.v*l.c - l.v*r.c)/cross(l.v, r.v);
}