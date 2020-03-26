#include "../vector/point.cpp"
#include <tuple>
using namespace std;

struct LineSegment {  // TO BE TESTED
    pair<PT, PT> p;
    LineSegment (const PT& a, const PT& b) : p(a, b) {}
    bool contains (const PT& o) {
        return collinear(p.first, p.second, o)
        && (o - p.first)*(o - p.second) <= 0;
    }
};