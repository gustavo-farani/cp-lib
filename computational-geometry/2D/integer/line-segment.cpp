#include "point.cpp"

bool diag (PT a, PT b, PT p) {
    auto [l, r] = minmax(a.x, b.x);
    auto [d, u] = minmax(a.y, b.y);
    return l <= p.x && p.x <= r && d <= p.y && p.y <= u;
}

bool intersect (PT a, PT b, PT c, PT d) {
    PT u = b - a, v = d - c;
    ll ca = v % (a - c), cb = v % (b - c), cc = u % (c - a), cd = u % (d - a);
    return ca*cb < 0 && cc*cd < 0
    || ca == 0 && diag(c, d, a) || cb == 0 && diag(c, d, b)
    || cc == 0 && diag(a, b, c) || cd == 0 && diag(a, b, d);
}

bool onSegment (PT a, PT b, PT p) {
    PT u = p - a, v = p - b;
    return u % v == 0 && u*v <= 0;
}