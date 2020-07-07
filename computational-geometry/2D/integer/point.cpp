#include "../../../template.cpp"

struct PT {
    ll x, y;
    PT (ll x = 0, ll y = 0) : x(x), y(y) {}
    PT operator- (const PT& o) const { return PT(x - o.x, y - o.y); }

    // vector space
    PT operator+ (const PT& o) const { return PT(x + o.x, y + o.y); }
    PT operator* (ll k) const { return PT(k*x, k*y); }

    // products
    ll operator* (const PT& o) const { return x*o.x + y*o.y; }
    ll operator% (const PT& o) const { return x*o.y - y*o.x; }

    // sorting
    bool operator< (const PT& o) const { return x == o.x ? y < o.y : x < o.x; }
    bool operator== (const PT& o) const { return x == o.x && y == o.y; }
};

// square of norm
ll norm (PT v) { return v*v; }