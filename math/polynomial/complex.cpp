struct CX {
    double x, y;
    CX (double x = 0.0, double y = 0.0) : x(x), y(y) {}
    CX operator+ (const CX& o) const { return {x + o.x, y + o.y}; }
    CX operator- (const CX& o) const { return {x - o.x, y - o.y}; }
    CX operator* (const CX& o) const { return {x*o.x - y*o.y, x*o.y + y*o.x}; }
    void operator*= (const CX& o) { *this = *this * o; }
    void operator/= (double t) { x /= t, y /= t; }
    double real () { return x; }
};

CX polar (double t, double a) { return {t*cos(a), t*sin(a)}; }