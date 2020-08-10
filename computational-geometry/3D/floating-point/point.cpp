#include "../../../boilerplate.cpp"

struct PT {
    double x, y, z;
    PT (double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}
    // vector between two points
    PT operator- (const PT& o) const {
        return {x - o.x, y - o.y, z - o.z};
    }
    // vector addition
    PT operator+ (const PT& o) const {
        return {x + o.x, y + o.y, z + o.z};
    }
    // multiplication by scalar
    PT operator* (double k) const {
        return {x*k, y*k, z*k};
    }
    // division by scalar
    PT operator/ (double k) const {
        return {x/k, y/k, z/k};
    }
    // dot/inner product
    double operator* (const PT& o) const {
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

// magnitude of vector v
double abs (PT v) { return sqrt(v*v); }

// returned angle will be in interval [0, PI]
double angle (PT u, PT v) {
    return acos(clamp(u*v/abs(u)/abs(v), -1.0, 1.0));  // C++17 only
}

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
double orient (PT a, PT b, PT c, PT p) {
    return (b - a) % (c - a) * (p - a);
}

// tests whether there is some plane containing points abcd
bool coplanar (PT a, PT b, PT c, PT d) {
    return sgn(orient(a, b, c, d)) == 0;
}

// given the lines
// r: through p and directed by u
// s: through q and directed by v
// tests whether lines r and s are skew
bool skew (PT p, PT u, PT q, PT v) {
    return sgn(u % v * (q - p)) != 0;
}

// volume of the tetrahedron determined by points abcd
double vol (PT a, PT b, PT c, PT d) {
    return abs(orient(a, b, c, d))/6.0;
}