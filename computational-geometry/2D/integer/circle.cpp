#include "point.cpp"

bool circlesIntersect (PT c1, ll r1, PT c2, ll r2) {
    PT v = c2 - c1;
    return norm(v) <= r1*r1 + (r1*r2 << 1) + r2*r2;
}