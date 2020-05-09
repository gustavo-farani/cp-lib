#include "../vector/point.cpp"

struct Circle {
    PT c;
    ll r;
    bool operator&& (const Circle& o) const {
        PT v = c - o.c;
        return v*v <= r*r + o.r*o.r + (r*o.r << 1);
    }  // whether two circles are tangent or secant
};