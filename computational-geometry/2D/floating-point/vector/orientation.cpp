#include "point.cpp"

bool collinear (const PT& a, const PT& b, const PT& c) {
    return eq0(b - a ^ c - a);
}

bool ccw (const PT& u, const PT& v) {
    return gt0(u ^ v);
}  // whether v is counter-clock-wise w.r.t. u

bool cw (const PT& u, const PT& v) {
    return lt0(u ^ v);
}  // whether v is clock-wise w.r.t. u