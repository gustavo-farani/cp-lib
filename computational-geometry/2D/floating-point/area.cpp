#include "point.cpp"

ld area (PT a, PT b, PT c) {
    PT u = b - a, v = c - a;
    return abs(u ^ v)/2L;
}