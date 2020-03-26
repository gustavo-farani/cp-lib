#include "point.cpp"

bool collinear (const PT& a, const PT& b, const PT& c) {
    return (b - a ^ c - a) == 0;
}

bool ccw (const PT& u, const PT& v) {
    return (u ^ v) > 0;
}  // whether v is counter-clock-wise w.r.t. u

bool cw (const PT& u, const PT& v) {
    return (u ^ v) < 0;
}  // whether v is clock-wise w.r.t. u

bool operator< (const PT& a, const PT& b) {   // TO BE TESTED
    if (b.y > 0) {
        return !((a ^ b) <= 0 || a.y < 0);
    } else if (b.y < 0) {
        return ((a ^ b) > 0 || a.y >= 0);
    } else {
        ll c = a ^ b;
        return (c > 0 || c == 0 && a*b < 0);
    }
}  // counter-clock-wise sorting vectors based on their polar angle