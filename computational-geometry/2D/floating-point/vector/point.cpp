#include "../../../../template.cpp"

const ld EPS = 1e-9;

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
    PT operator* (ld t) const {  // scalar multiplication
        return PT(x*t, y*t);
    }
    ld operator* (const PT& o) const {  // dot/inner product
        return x*o.x + y*o.y;
    }
    ld operator% (const PT& o) const {  // cross product
        return x*o.y - y*o.x;
    }
    bool operator< (const PT& o) const {  // lexicographic sort
        return eq0(x - o.x) ? y < o.y : x < o.x;
    }
    bool operator== (const PT& o) const {  // overlapping
        return eq0(x - o.x) && eq0(y - o.y);
    }
};

ld norm (const PT& v) {
    return hypot(v.x, v.y);
}