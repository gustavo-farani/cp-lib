#include "point.cpp"

// comparator functor for sorting points in the plane,
// based on their polar angle in the coordinate system
// with origin at point o, following a conterclockwise
// order starting from direction of vector s - o
// NOTE: if two points are colinear with the origin,
// it is guaranteed that the point closest to the origin
// comes before the farthest one
struct PolarSort {
    PT o, d;
    PolarSort (PT o, PT s) : o(o), d(s - o) {}
    bool half (PT v) {
        int aux = sgn(cross(d, v));
        return aux < 0 || aux == 0 && sgn(dot(d, v)) < 0;
    }
    bool operator() (PT p, PT q) {
        PT u = p - o, v = q - o;
        return make_tuple(half(u), 0, sgn(dot(u, u) - dot(v, v)))
        < make_tuple(half(v), sgn(cross(u, v)), 0);
    }
};