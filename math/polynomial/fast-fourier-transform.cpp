#include "complex.cpp"

const double PI = acos(-1.0);

// inv == false:
//   a: coefficients of the polynomial p(x) = 
//   a[0] + a[1]*x + a[2]*x^2 ... a[a.size()-1]*x^(a.size()-1),
//   with degree a.size()-1
//   return: the discrete fourier transformation applied of p(x),
//   i.e., the evaluation of p(x) to the n-th complex roots of unity
// inv == true:
//   applies the inverse fourier transformation, getting back the
//   real coefficients from the polynomial whose evalutaion in the
//   n-th roots of unity yields the complex values in a
// complexity: O(N lg N),
// either the direct, or the inverse transformation
// NOTE: a.size() must be a power of 2
// NOTE: this function could be also plugged-in with
// STL's built-in std::complex type, by defining:
//      typedef complex<double> CX;
// however, an user-defined complex type turns out to be
// more efficient in practice
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
        double t = (inv ? -2.0 : 2.0)*PI/s;
        CX wn(cos(t), sin(t));
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