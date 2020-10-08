#include "../../../boilerplate.cpp"

struct Rect {
    ii x, y;
    Rect (int l, int r, int d, int u) : x(l, r), y(d, u) {}
    bool empty () { return x.fi > x.se || y.fi > y.se; }
};

ii intervalIntersection (ii a, ii b) {
    if (b.fi < a.fi) swap(a, b);
    return {b.fi, min(a.se, b.se)};
}

Rect rectanglesIntersection (Rect a, Rect b) {
    auto [l, r] = intervalIntersection(a.x, b.x);
    auto [d, u] = intervalIntersection(a.y, b.y);
    return Rect(l, r, d, u);
}