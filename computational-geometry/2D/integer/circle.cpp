#include "../../../boilerplate.cpp"

struct Circle {
    ll x, y, r;
    Circle (ll x = 0, ll y = 0, ll r = 0) : x(x), y(y), r(r) {}
    bool contains (ll px, ll py) {
        ll d2 = (x - px)*(x - px) + (y - py)*(y - py);
        return d2 <= r*r;
    }
};

bool intersect (Circle a, Circle b) {
    ll d2 = (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
    return d2 <= a.r*a.r + (a.r*b.r << 1) + b.r*b.r;
}