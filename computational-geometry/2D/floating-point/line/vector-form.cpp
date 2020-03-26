#include <tuple>
#include "../vector/point.cpp"
using namespace std;

struct Line {
    PT p, d;  // position and direction vectors
    Line (const PT& a, const PT& b) : p(a), d(b - a) {}
    bool contains (const PT& q) const {
        return eq0(q - p ^ d);
    }
    bool operator== (const Line& o) const {
        return eq0(d ^ o.d) && o.contains(p);
    }  // whether the lines coincide (have all of their points in commom)
    bool concurrent (const Line &o) const {
        return !eq0(d ^ o.d);
    }  // whether the lines intersect in a single point
    PT operator& (const Line& o) const {
        if (concurrent(o)) {
            ld t = (o.p - p ^ o.d)/(d ^ o.d);
            return p + d*t;
        } else throw -1;
    }  // compute single point intersection of concurrent lines
};