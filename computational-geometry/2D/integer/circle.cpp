#include "point.cpp"

struct Circle {
    PT c;
    ll r;
    Circle (PT c, ll r) : c(c), r(r) {}
    bool contains (PT p) { return norm(p - c) <= r*r; }
};

bool circlesIntersect (Circle a, Circle b) {
    PT v = b.c - a.c;
    return norm(v) <= a.r*a.r + (a.r*b.r << 1) + b.r*b.r;
}