#include "point.cpp"

// unique representation of a line in the plane
struct Line {
    ll a, b, c;
    Line (PT p, PT q) {  // credits to josecruz
        PT v = q - p;
        a = v.y, b = -v.x, c = p % q;
        ll g = gcd(gcd(a, b), c);  // C++ 17 only
        if (a < 0 || a == 0 && b < 0) g = -g;
        a /= g, b /= g, c /= g;
    }
    bool contains (PT p) {
        return PT(a, b)*p == c;
    }
    bool operator< (const Line& o) {
        return make_tuple(a, b, c) < make_tuple(o.a, o.b, o.c);
    }
};