#include "complex.cpp"
// using CX = complex<double>;

const double PI = acos(-1.0);

void fft (vector<CX>& a, bool inv) {
    int n = a.size();
    for (int i = 0; i < n; i++) {
        int j = 0;
        for (int bn = n, bi = i; bn >>= 1; bi >>= 1) {
            j <<= 1;
            j |= bi & 1;
        }
        if (i < j) swap(a[i], a[j]);
    }
    for (int h = 1, s = 2; h < n; h = s, s <<= 1) {
        CX wn = polar(1.0, (inv ? -2.0 : 2.0)*PI/s);
        for (int l = 0, m = h; l < n; l += s, m += s) {
            CX w = 1.0;
            for (int i = l, j = m; i < m; i++, j++) {
                CX u = a[i], v = a[j]*w;
                a[i] = u + v;
                a[j] = u - v;
                w *= wn;
            }
        }
    }
    if (inv) {
        for (CX& z : a) z /= n;
    }
}