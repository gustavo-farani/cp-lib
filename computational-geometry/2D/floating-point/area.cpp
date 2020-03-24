#include "point.cpp"

ld area (const PT& a, const PT& b, const PT& c) {
    PT u = b - a, v = c - a;
    return abs(u ^ v)/2.0;
}