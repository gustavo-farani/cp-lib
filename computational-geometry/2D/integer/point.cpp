typedef long long ll;

struct PT {
    ll x, y;
    PT operator+ (const PT& o) const {     // vector addition
        return PT{x + o.x, y + o.y};
    }
    PT operator- (const PT& o) const {  // vector subtraction
        return PT{x - o.x, y - o.y};
    }
    PT operator- () const {           // negative of a vector
        return PT{-x, -y};
    }
    PT operator* (ll k) const {      // scalar multiplication
        return PT{k*x, k*y};
    }
    ll operator* (const PT& o) const {         // dot product
        return x*o.x + y*o.y;
    }
    ll operator^ (const PT& o) const {       // cross product
        return x*o.y - y*o.x;
    }
    ll operator! () const {                 // square of norm
        return *this * *this;
    }
    /*bool operator< (const PT& o) const {   TO BE TESTED
        if (o.y > 0) {
            return !(operator^(o) <= 0 || y < 0);
        } else if (o.y < 0) {
            return (operator^(o) > 0 || y >= 0);
        } else {
            ll cross = operator^(o);
            return (cross > 0 || cross == 0 && operator*(o) < 0);
        }
    }       // counter-clock-wise sorting based on polar angle */
};