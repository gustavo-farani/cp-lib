const double EPS = 1e-9;
int sgn (double t) { return abs(t) < EPS ? 0 : (t > 0) - (t < 0); }

struct PT {
    double x, y;
    PT (double x = 0, double y = 0) : x(x), y(y) {}
    PT operator- (PT o) { return PT(x - o.x, y - o.y); }

    // vector space
    PT operator* (double t) { return PT(x*t, y*t); }
    PT operator/ (double t) { return PT(x/t, y/t); }
    PT operator+ (PT o) { return PT(x + o.x, y + o.y); }

    // lexicographic order
    bool operator< (PT o) {
        return sgn(x - o.x) == 0 ? y < o.y : x < o.x;
    }
    bool operator== (PT o) {
        return sgn(x - o.x) == 0 && sgn(y - o.y) == 0;
    }
};

double dot (PT u, PT v) { return u.x*v.x + u.y*v.y; }
double cross (PT u, PT v) { return u.x*v.y - v.x*u.y; }
double orient (PT a, PT b, PT c) { return cross(b - a, c - a); }
double abs (PT p) { return hypot(p.x, p.y); }

// orthogonality
bool perp (PT u, PT v) { return sgn(dot(u, v)) == 0; }
PT perp (PT v) { return PT(-v.y, v.x); }  // CCW

// angles and rotations
const double PI = acos(-1.0);
double arg (PT p) { return atan2(p.y, p.x); }
PT rot (PT v, double a) {  // CCW
    return PT(v.x*cos(a) - v.y*sin(a), v.x*sin(a) + v.y*cos(a));
}