typedef long long ll;

struct PT {
    ll x, y;
    PT operator+ (PT p) {
        return PT{x + p.x, y + p.y};
    }
    PT operator- (PT p) {
        return PT{x - p.x, y - p.y};
    }
    ll operator* (PT p) {
        return x*p.x + y*p.y;
    }
    ll operator^ (PT p) {
        return x*p.y - y*p.x;
    }
};

ll hyp (PT p) {
    return p*p;
}