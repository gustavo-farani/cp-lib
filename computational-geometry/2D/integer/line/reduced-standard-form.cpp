#include "../vector/point.cpp"

struct Line {
    ll a, b, c;
    Line (const PT& p, const PT& q) {  // credits to josecruz
        PT v = q - p;
        a = v.y, b = -v.x, c = p ^ q;
        ll g = gcd(gcd(a, b), c);  // C++ 17 only
        if (a < 0 || a == 0 && b < 0) g = -g;
        a /= g, b /= g, c /= g;
    }
    bool contains (const PT& p) {
        return PT(a, b)*p == c;
    }
};