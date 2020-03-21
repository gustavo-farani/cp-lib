#include <cmath>

typedef double ld;

struct PT {
    ld x, y;
    PT operator+ (const PT& o) const {
        return PT{x + o.x, y + o.y};
    }
    PT operator- (const PT& o) const {
        return PT{x - o.x, y - o.y};
    }
    PT operator- () {
        return PT{-x, -y};
    }
    PT operator/ (ld t) {
        return PT{x/t, y/t};
    }
    PT operator* (ld t) {
        return PT{x*t, y*t};
    }
    ld operator* (const PT& o) const {
        return x*o.x + y*o.y;
    }
    ld operator^ (const PT& o) const {
        return x*o.y - y*o.x;
    }
    ld operator! () {
        return sqrt(*this * *this);
    }
};