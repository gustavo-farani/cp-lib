typedef double ld;

struct PT {
    ld x, y;
    PT operator+ (PT o) {
        return PT{x + o.x, y + o.y};
    }
    PT operator- (PT o) {
        return PT{x - o.x, y - o.y};
    }
    PT operator/ (ld t) {
        return PT{x/t, y/t};
    }
    PT operator* (ld t) {
        return PT{x*t, y*t};
    }
    ld operator* (PT o) {
        return x*o.x + y*o.y;
    }
    ld operator^ (PT o) {
        return x*o.y - y*o.x;
    }
};