#include "vector-form.cpp"

bool operator== (const Line &r, const Line& s) {
    return eq0(r.d ^ s.d) && r.contains(s.p);
}  // whether the lines coincide (have all of their points in commom)

bool concurrent (const Line& r, const Line& s) {
    return !eq0(r.d ^ s.d);
}  // whether the lines intersect in a single point

PT operator& (const Line& r, const Line &s) {
    ld t = (s.p - r.p ^ s.d)/(r.d ^ s.d);
    return r.p + r.d*t;
}  // compute single point intersection of assumed concurrent lines