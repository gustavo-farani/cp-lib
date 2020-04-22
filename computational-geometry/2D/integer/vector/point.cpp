#include "../../../../template.cpp"

struct PT {
    ll x, y;
    PT (ll x = 0, ll y = 0) : x(x), y(y) {}
    PT operator+ (const PT& o) const {  // vector addition
        return PT(x + o.x, y + o.y);
    }
    PT operator- (const PT& o) const {  // vector between two points
        return PT(x - o.x, y - o.y);
    }
    PT operator- () const {  // negative of a vector
        return PT(-x, -y);
    }
    PT operator* (ll k) const {  // scalar multiplication
        return PT(k*x, k*y);
    }
    ll operator* (const PT& o) const {  // dot/inner product
        return x*o.x + y*o.y;
    }
    ll operator^ (const PT& o) const {  // cross product
        return x*o.y - y*o.x;
    }
    ll operator! () const {  // square of norm
        return *this**this;
    }
    bool operator== (const PT& o) const {  // coincidence
        return x == o.x && y == o.y;
    }
    bool operator< (const PT& o) const {  // lexicographic order
        return x == o.x ? y < o.y : x < o.x;
    }
};