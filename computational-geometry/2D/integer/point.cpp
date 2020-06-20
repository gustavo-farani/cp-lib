#include "../../../template.cpp"

struct PT {
    ll x, y;
    PT (ll x = 0, ll y = 0) : x(x), y(y) {}
    PT operator- (PT o) { return PT(x - o.x, y - o.y); }

    // vector space
    PT operator+ (PT o) {  return PT(x + o.x, y + o.y); }
    PT operator* (ll k) { return PT(k*x, k*y); }

    // products
    ll operator* (PT o) { return x*o.x + y*o.y; }
    ll operator% (PT o) { return x*o.y - y*o.x; }

    // sorting
    bool operator< (PT o) const { return x == o.x ? y < o.y : x < o.x; }
    bool operator== (PT o) const { return x == o.x && y == o.y; }
};

// square of norm
ll norm (PT v) { return v*v; }