typedef long long ll;

struct PT {
    ll x, y;
    PT operator+ (PT p) {   // vector addition
        return PT{x + p.x, y + p.y};
    }
    PT operator- (PT p) {
        return PT{x - p.x, y - p.y};
    }
    ll operator* (PT p) {   // dot product
        return x*p.x + y*p.y;
    }
    ll operator^ (PT p) {   // cross product
        return x*p.y - y*p.x;
    }
    ll operator! () {       // square of norm
        return *this * *this;
    }
};