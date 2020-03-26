#include <tuple>
#include "../vector/point.cpp"
#include "../line/vector-form.cpp"
#include "../vector/orientation.cpp"
using namespace std;

struct LineSegment {  // TO BE TESTED
    pair<PT, PT> p;
    LineSegment (const PT& a, const PT& b) : p(a, b) {}
    bool contains (const PT& q) const {
        return collinear(p.first, p.second, q) && lt0((q - p.first)*(q - p.second));
    }   // wheter the point is contained in the line segment
    PT operator& (const Line& r) const {
        Line l(p.first, p.second);
        PT o = l & r;
        if (contains(o)) return o;
        else throw -1;
    }  // compute single point intersection of line segment and (infinite) line
    PT operator& (const LineSegment& o) const {
        Line r(p.first, p.second), s(o.p.first, o.p.second);
        PT q = r & s;
        if (contains(q) && o.contains(q)) return q;
        else throw -1;
    }  // computes single point intersection of two line segments
};