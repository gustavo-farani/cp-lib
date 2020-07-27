#include "fast-fourier-transform.cpp"

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