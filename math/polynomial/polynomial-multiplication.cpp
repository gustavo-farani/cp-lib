#include "fast-fourier-transform.cpp"

// a, b: polynomials with integer coefficients
// a(x) = a[0] + a[1]*x + ... + a[a.size()-1]*x^(a.size()-1)
// b(x) = b[0] + b[1]*x + ... + b[b.size()-1]*x^(b.size()-1)
// return: coefficients of c(x) = a(x)*b(x)
// complexity: O(N lg N),
// N = degree of a + degree of b
vector<ll> multiply (const vi& a, const vi& b) {
    vector<ll> c(a.size() + b.size() - 1);
    int n = 1;
    while (n < c.size()) n <<= 1;
    vector<CX> ta(a.begin(), a.end()), tb(b.begin(), b.end()), tc(n);
    ta.resize(n);
    tb.resize(n);
    fft(ta, false);
    fft(tb, false);
    for (int i = 0; i < n; i++) tc[i] = ta[i]*tb[i];
    fft(tc, true);
    for (int i = 0; i < c.size(); i++) c[i] = llrint(tc[i].real());
    return c;
}