#include <tuple>
#include "../vector/point.cpp"
using namespace std;

struct Line {
    PT p, d;  // position and direction vectors
    Line (const PT& a, const PT& b) : p(a), d(b - a) {}
    bool contains (const PT& q) const {
        return eq0(q - p ^ d);
    }
};