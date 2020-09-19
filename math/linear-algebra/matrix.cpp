#include "../../boilerplate.cpp"

const ld EPS = 1e-22L;
int sgn (ld t) { return abs(t) < EPS ? 0 : (t > 0) - (t < 0); }
 
typedef valarray<ld> VR;
 
struct MX : public vector<VR> {
    int m, n;
    MX (int m, int n) : m(m), n(n), vector<VR>(m, VR(n)) {}
};
 
// identity matrix of order n, scaled by k
MX identity (int n, ld k = 1.0L) {
    MX a(n, n);
    for (int i = 0; i < n; i++) a[i][i] = k;
    return a;
}