#include <cmath>

typedef double ld;

const ld EPS = 1e-9;

bool eq (ld x, ld y) { return abs(x - y) < EPS; }  // equal
bool eq0 (ld x) { return abs(x) < EPS; }  // equal zero
bool gt0 (ld x) { return x > -EPS; }  // greater than zero (positive)
bool lt0 (ld x) { return x < EPS; }  // less than zero (negative)

struct PT {
    ld x, y;
    PT (ld x = 0, ld y = 0) : x(x), y(y) {}
    PT operator+ (const PT& o) const {  // vector addition
        return PT(x + o.x, y + o.y);
    }
    PT operator- (const PT& o) const {  // vector between points
        return PT(x - o.x, y - o.y);
    }
    PT operator- () const {  // negative of a vector
        return PT(-x, -y);
    }
    PT operator* (ld t) const {  // scalar multiplication
        return PT(x*t, y*t);
    }
    PT operator/ (ld t) const {  // division by scalar
        return PT(x/t, y/t);
    }
    ld operator* (const PT& o) const {  // dot/inner product
        return x*o.x + y*o.y;
    }
    ld operator^ (const PT& o) const {  // cross product
        return x*o.y - y*o.x;
    }
    ld operator! () const {  // norm of a vector
        return hypot(x, y);
    }
    bool operator< (const PT& o) const {  // lexicographic sort
        return eq(x, o.x) ? y < o.y : x < o.x;
    }
    bool operator== (const PT& o) const {  // coincidence
        return eq(x, o.x) && eq(y, o.y);
    }
};