#include "../vector/point.cpp"

struct Polygon {
    int sides;
    vector<PT> p;
    Polygon (vector<PT>&& v) : sides(v.size()), p(v) {
        p.pb(p.front()); // facilitates iteration through edges
    }
    PT operator[] (int i) { return p[i]; }  // acess ith vertex
};