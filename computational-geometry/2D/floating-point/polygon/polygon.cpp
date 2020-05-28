#include "../vector/point.cpp"

struct Polygon {
    int sides;
    vector<PT> p;
    Polygon (vector<PT>&& v) : sides(v.size()), p(v) {
        p.pb(p.front()); // facilitates iteration through edges
    }
    ld shoelace();
    ld area();
    bool ccw();
    bool cw();
    int contains (const PT& q);
    Polygon cut (const PT& q, const PT& v);
};