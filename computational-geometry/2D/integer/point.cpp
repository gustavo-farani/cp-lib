#include "../../../boilerplate.cpp"

struct PT {
    ll x, y;
    PT (ll x = 0, ll y = 0) : x(x), y(y) {}
    PT operator- (const PT& o) const { return {x - o.x, y - o.y}; }

    // vector space
    PT operator+ (const PT& o) const { return {x + o.x, y + o.y}; }
    PT operator* (ll k) const { return {k*x, k*y}; }

    // products
    ll operator* (const PT& o) const { return x*o.x + y*o.y; }
    ll operator% (const PT& o) const { return x*o.y - y*o.x; }

    // sorting
    bool operator< (const PT& o) const { return x == o.x ? y < o.y : x < o.x; }
    bool operator== (const PT& o) const { return x == o.x && y == o.y; }

    // input/output
    friend ostream& operator<< (ostream& os, PT& o) {
        return os << o.x << ' ' << o.y;
    }
    friend istream& operator>> (istream& is, PT& o) {
        return is >> o.x >> o.y;
    }
};

ll orient (PT a, PT b, PT c) { return (b - a) % (c - a); }
PT perp (PT v) { return {-v.y, v.x}; }

// square of norm
ll norm (PT v) { return v*v; }