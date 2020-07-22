#include "../point.cpp"

struct Polygon {
    int sides;
    vector<PT> p;
    Polygon (vector<PT>&& v) : sides(v.size()), p(v) {}
    int next (int i) { return i == sides - 1 ? 0 : i + 1; }
    // area.cpp
    ll shoelace();
    bool cw();
    bool ccw();
    // lattice-points.cpp
    ll latticePoints(bool border);
    // contains-point.cpp
    int contains(PT p);
    // minkowski-sum.cpp
    vector<PT> getEdges();
    Polygon operator-();
};