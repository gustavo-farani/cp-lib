#include "../../../../template.cpp"

ii inter (ii a, ii b) {
    if (b.first < a.first) swap(a, b);
    return {b.first, min(a.second, b.second)};
}

struct Rect {
    ii x, y;
    Rect operator^ (Rect o) {
        return Rect{inter(x, o.x), inter(y, o.y)};
    }
    bool empty () {
        return (x.first > x.second || y.first > y.second);
    }
};