#include "point.cpp"

PT norm (PT v) {
    ll g = abs(gcd(gcd(v.x, v.y), v.z));
    if (g != 0) {
        v.x /= g;
        v.y /= g;
        v.z /= g;
    }
    return v;
}

// tests whether point p is inside triangle abc
bool contains (PT a, PT b, PT c, PT p) {
    PT u = b - a, v = c - b, w = a - c, fa = p - a;
    if (u % v * fa == 0LL) {
        set<PT> s({norm(u % fa), norm(v % (p - b)), norm(w % (p - c))});
        s.erase(PT());
        return s.size() == 1;
    } else {
        return false;
    }
}