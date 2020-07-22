#include "circle.cpp"
#include "../vector/orthogonality.cpp"

// computes the circumference spanning the triangle a-b-c
Circle circumcircle (PT a, PT b, PT c) {
    PT u = b - a, v = c - a;
    PT w = perp(u*dot(v, v) - v*dot(u, u))/cross(u, v)/2.0;
    return Circle(a + w, abs(w));
}