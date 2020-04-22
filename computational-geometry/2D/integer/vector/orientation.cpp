#include "point.cpp"

bool colinear (const PT& a, const PT& b, const PT& c) {
    return (b-a ^ c-a) == 0;
}

bool ccw (const PT& u, const PT& v) {
    return (u ^ v) > 0;
}  // whether v is counter-clock-wise w.r.t. u

bool cw (const PT& u, const PT& v) {
    return (u ^ v) < 0;
}  // whether v is clock-wise w.r.t. u