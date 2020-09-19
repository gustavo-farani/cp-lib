#include "../vector/point.cpp"

struct Polygon {
    int sides;
    vector<PT> p;
    Polygon (const vector<PT>& v) : p(v), sides(v.size()) {}
    int next (int i) { return i == sides - 1 ? 0 : i + 1; }
    // convexity.cpp
    int convex();
    // area.cpp
    ld shoelace();
    ld area();
    bool ccw();
    bool cw();
    // cut.cpp
    Polygon cut(Line l);
    // contains-point.cpp
    int contains(PT q);
    // largest-circle.cpp
    Circle largestCircle();
};