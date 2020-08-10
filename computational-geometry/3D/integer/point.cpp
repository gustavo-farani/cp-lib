#include "../../../boilerplate.cpp"

struct PT {
    ll x, y, z;
    PT (ll x = 0, ll y = 0, ll z = 0) : x(x), y(y), z(z) {}
    // vector between two points
    PT operator- (const PT& o) const {
        return {x - o.x, y - o.y, z - o.z};
    }
    // vector addition
    PT operator+ (const PT& o) const {
        return {x + o.x, y + o.y, z + o.z};
    }
    // scalar multiplication
    PT operator* (ll k) const {
        return {x*k, y*k, z*k};
    }
    // dot/inner product
    ll operator* (const PT& o) const {
        return x*o.x + y*o.y + z*o.z;
    }
    // cross product
    PT operator% (const PT& o) const {
        return {y*o.z - z*o.y, z*o.x - x*o.z, x*o.y - y*o.x};
    }
    // coincidence
    bool operator== (const PT& o) const {
        return x == o.x && y == o.y && z == o.z;
    }
    // lexicographic order
    bool operator< (const PT& o) const {
        return make_tuple(x, y, z) < make_tuple(o.x, o.y, o.z);
    }
    // input
    friend istream& operator>> (istream& is, PT& p) {
        return is >> p.x >> p.y >> p.z;
    }
    // output
    friend ostream& operator<< (ostream& os, PT& p) {
        return os << p.x << ' ' << p.y << ' ' << p.z;
    }
};

// squared norm of vector v
ll norm (PT v) { return v*v; }

// Mixed Product
// return:
// == 0, if abc are colinear or plane abc contains p
// now, consider the plane determined by points abc
// this plane splits the space into two half-spaces
// upper half-space: following the direction of (ab x ac)
// lower half-space: contrary to the direction of (ab x ac)
// > 0, if p is in upper half-space
// < 0, if p is in lower half-space
// NOTE: swaping any two arguments, the result is multiplied by -1
ll orient (PT a, PT b, PT c, PT p) {
    return (b - a) % (c - a) * (p - a);
}

// tests whether there is some plane containing points abcd
bool coplanar (PT a, PT b, PT c, PT d) {
    return orient(a, b, c, d) == 0;
}

// given the lines
// r: through p and directed by u
// s: through q and directed by v
// tests whether lines r and s are skew
bool skew (PT p, PT u, PT q, PT v) {
    return u % v * (q - p) != 0;
}