#include "../../../boilerplate.cpp"

struct Rect {
    ii x, y;
    Rect (int l, int r, int d, int u) : x(l, r), y(d, u) {}
    bool empty () { return x.first > x.second || y.first > y.second; }
};

ii intervalIntersection (ii a, ii b) {
    if (b.first < a.first) swap(a, b);
    return {b.first, min(a.second, b.second)};
}

Rect rectanglesIntersection (Rect a, Rect b) {
    auto [l, r] = intervalIntersection(a.x, b.x);
    auto [d, u] = intervalIntersection(a.y, b.y);
    return Rect(l, r, d, u);
}